/*
Copyright (C) 2013 BMW Group

Author: Guido Ostkamp     (guido.ostkamp@de.bertrandt.com)
Author: Bernhard Singer   (bernhard.singer@partner.bmw.de)
Author: Matthias Freundel (matthias.freundel@partner.bmw.de)

This Source Code Form is subject to the terms of the Mozilla Public

License, v. 2.0. If a copy of the MPL was not distributed with this file,

You can obtain one at http://mozilla.org/MPL/2.0/.
*/
/*
 * MyFileIO -
 *
 * this class deals with reading the station configuration from disk files
 * and keeping lookup tables for all stations. AMFM and DAB stations are
 * at the moment kept seperately; there is also special storage for
 * generic stations (one per AMFM PI-code or DAB service id which are
 * expected to be identical for the same station).
 *
 * A station record is never removed once it has been stored, only the
 * 'receivable' attribute is modified. This is important, since
 * additional lookup maps for frequency and PI-code / Service id
 * use pointers into the AMFM or DAB station record vectors.
 *
 * There is also support to set the 'permanent' attribute and for
 * getting a list of stations with attribute 'receivable' or 'permanent'.
 *
 * Additional methods allow the comparison of an old and new list
 * in order to create a list with the differences, for sending
 * updates to an HMI client.
 */

#include <memory>
#include <iostream>
#include <unistd.h>
#include <map>
#include <set>
#include <algorithm>
#include <exception>

#include <TunerStation/TunerStationStubDefault.h>
#include <TunerTypes/TunerTypes.h>
#include <TunerStationTypes/TunerStationTypes.h>
#include <CommonAPI/Runtime.h>

#include "MyFileIO.h"
#include "MyTerminalIO.h"

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>

using namespace std;

static int verbose = 0;

MyFileIO * MyFileIO::instance = NULL;

MyFileIO::MyFileIO()
{
}

MyFileIO::~MyFileIO()
{
    // delete all station objects from vector
    for (auto it = stationsAMFM.cbegin(); it != stationsAMFM.cend(); it++) {
        delete *it;
    }
    for (auto it = stationsDAB.cbegin(); it != stationsDAB.cend(); it++) {
        delete *it;
    }

    // following is not really required
    stationsAMFM.clear();
    stationsDAB.clear();
    stationsTimeAMFM.clear();
    stationsTimeDAB.clear();
    freqMapAMFM.clear();
    piCodeMapAMFM.clear();
    freqMapDAB.clear();
    serviceIdMapDAB.clear();
}

MyFileIO *
MyFileIO::getInstance()
{
    static Guard g;
    if (instance == NULL) {
        instance = new MyFileIO();
    }
    return instance;
}

MyFileIO::Guard::~Guard()
{
    if (MyFileIO::instance != NULL) {
        delete MyFileIO::instance;
    }
}

// assign Component ID to PiCode or service id
uint32_t
MyFileIO::assignComponentID(uint32_t code)
{
    auto ret = codeToComponentIDMap.equal_range(code);
    for (auto codeToComponentIDIt = ret.first; codeToComponentIDIt != ret.second; codeToComponentIDIt++) {
        uint32_t componentID = (*codeToComponentIDIt).second;
        if (verbose) {
            printf("Code %d has got assigned existing componentID %d\n", code, componentID);
        }
        return componentID;
    }
    // not found, assign new id
    codeToComponentIDMap[code] = nextComponentID++;
    if (verbose) {
        printf("Code %d has got assigned new componentID %d\n", code, codeToComponentIDMap[code]);
    }
    return codeToComponentIDMap[code];
}

TunerStationTypes::TunerStationTypes::Station
MyFileIO::readFile(string filename)
{
    ifstream myfile(filename);
    string line;
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    TunerStationTypes::TunerStationTypes::Station myStation;

    // General
    int deviceTypePresent = 0;
    int sourceTypePresent = 0;
    int metaTypePresent = 0;
    int metaStringPresent = 0;
    int flagsPresent = 0;
    int idFrequencyPresent = 0;
    int idServicePresent = 0;

    // AMFM only
    int idProgramIdentifierPresent = 0;
    int namePSCodePresent = 0;
    int nameHDLabelPresent = 0;
    int nameRadiotextPresent = 0;
    int qualityFieldstrengthPresent = 0;
    int qualityMultipathPresent = 0;
    int qualityDigitalPresent = 0;
    int genrePtyPresent = 0;

    // DAB specific
    int idEnsemblePresent = 0;
    int idComponentPresent = 0;
    int nameSubcomponentLabelPresent = 0;
    int nameSubcomponentAbbrevPresent = 0;
    int nameDynamicLabelPresent = 0;
    int nameServiceLabelPresent = 0;
    int nameServiceAbbrevPresent = 0;
    int nameEnsembleLabelPresent = 0;
    int nameEnsembleAbbrevPresent = 0;
    int nameFrequencyLabelPresent = 0;
    int genreStaticPtyPresent = 0;
    int genreDynamicPtyPresent = 0;
    int qualityBitErrorRatePresent = 0;
    int qualityServicePresent = 0;
    int qualityAudioPresent = 0;

    if (!myfile.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        throw invalid_argument("unable to open file");
    }

    // resize vector's to whatever is MAX needed in AMFM + DAB + UNDEF
    // later we will reduce to what is actually needed once we know the
    // final deviceType

    myStation.sel.id.resize(5);
    myStation.flags.resize(1);
    myStation.name.resize(8);
    myStation.meta.resize(1);
    myStation.genre.resize(2);
    myStation.quality.resize(3);
    myStation.stationType = (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_AUTOSTORED |
        (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;

    // It is theoretically possible to override some values in vectors
    // with wrong entries, since at the moment we do not check correctly
    // for all entries whether device type is correct. E.g. DAB entries
    // might still overrider AMFM values when deviceType is set to AMFM.
    // Checks should be added later to fix this.

    while(myfile.good()) {
        size_t pos;
        string sValue = "";
        unsigned long uVal;

        getline(myfile, line);

        // assume AMFM for now
        //
        if ((pos = line.find("DeviceType: ")) != string::npos) {
            // Generic
            sValue = line.substr(strlen("DeviceType: "));
            myStation.sel.deviceType = (uint32_t)tio->setDeviceType(sValue);
            deviceTypePresent++;
        } else if ((pos = line.find("SourceType: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            sValue = line.substr(strlen("SourceType: "));
            // no storage for this one
            sourceTypePresent++;
        } else if ((pos = line.find("Id Frequency: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }

            // set dummy value for ID_KEY field
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] = 0;
            } else if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] = 0;
            } else {
                // error
            }

            sValue = line.substr(strlen("Id Frequency: "));
            uVal = stoul (sValue, nullptr, 0);
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = uVal;
            } else if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY] = uVal;
            } else {
                // error
            }

            idFrequencyPresent++;
            // Range check required here for AMFM vs. DAB
        } else if ((pos = line.find("Id Program Identifier: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                cerr << "ID Program identifier is only allowed for AMFM!" << endl;
                throw invalid_argument("ID Program identifier is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Id Program Identifier: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI] = uVal;
            idProgramIdentifierPresent++;
        } else if ((pos = line.find("Id Service: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            sValue = line.substr(strlen("Id Service: "));
            uVal = stoul (sValue, nullptr, 0);
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = uVal;
            } else if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE] = uVal;
            } else {
                // error
            }
            idServicePresent++;
        } else if ((pos = line.find("Id Ensemble: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "ID Ensemble is only allowed for DAB!" << endl;
                throw invalid_argument("ID Ensemble is only allowed for DAB");
            }
            sValue = line.substr(strlen("Id Ensemble: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = uVal;
            idEnsemblePresent++;
        } else if ((pos = line.find("Id Component: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "ID Component is only allowed for DAB!" << endl;
                throw invalid_argument("ID Component is only allowed for DAB");
            }
            sValue = line.substr(strlen("Id Component: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_COMPONENT] = uVal;
            idComponentPresent++;
        } else if ((pos = line.find("Name PS Code: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                cerr << "Name PS Code is only allowed for AMFM!" << endl;
                throw invalid_argument("Name PS Code is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Name PS Code: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_PS] = sValue;
            namePSCodePresent++;
        } else if ((pos = line.find("Name HD Label: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                cerr << "Name HD Label is only allowed for AMFM!" << endl;
                throw invalid_argument("Name HD Label is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Name HD Label: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_HD] = sValue;
            nameHDLabelPresent++;
        } else if ((pos = line.find("Name Radiotext: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                cerr << "Name Radiotext is only allowed for AMFM!" << endl;
                throw invalid_argument("Name Radiotext is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Name Radiotext: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_RT] = sValue;
            nameRadiotextPresent++;
        } else if ((pos = line.find("Name Subcomponent Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Name Subcomponent Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Subcomponent Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Subcomponent Label: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_CLONG] = sValue;
            nameSubcomponentLabelPresent++;
        } else if ((pos = line.find("Name Subcomponent Abbreviation: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Name Subcomponent Abbreviation is only allowed for DAB!" << endl;
                throw invalid_argument("Name Subcomponent Abbreviation is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Subcomponent Abbreviation: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_CSHORT] = sValue;
            nameSubcomponentAbbrevPresent++;
        } else if ((pos = line.find("Name Dynamic Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Name Dynamic Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Dynamic Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Dynamic Label: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_DYNAMIC] = sValue;
            nameDynamicLabelPresent++;
        } else if ((pos = line.find("Name Service Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Name Service Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Service Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Service Label: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SLONG] = sValue;
            nameServiceLabelPresent++;
        } else if ((pos = line.find("Name Service Abbreviation: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Name Service Abbreviation is only allowed for DAB!" << endl;
                throw invalid_argument("Name Service Abbreviation is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Service Abbreviation: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SSHORT] = sValue;
            nameServiceAbbrevPresent++;
        } else if ((pos = line.find("Name Ensemble Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Name Ensemble Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Ensemble Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Ensemble Label: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_ELONG] = sValue;
            nameEnsembleLabelPresent++;
        } else if ((pos = line.find("Name Ensemble Abbreviation: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Name Ensemble Abbreviation is only allowed for DAB!" << endl;
                throw invalid_argument("Name Ensemble Abbreviation is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Ensemble Abbreviation: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_ESHORT] = sValue;
            nameEnsembleAbbrevPresent++;
        } else if ((pos = line.find("Name Frequency Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Name Frequency Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Frequency Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Frequency Label: "));
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_FREQUENCY] = sValue;
            nameFrequencyLabelPresent++;
        } else if ((pos = line.find("Meta Type: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            sValue = line.substr(strlen("Meta Type: "));
            uVal = stoul (sValue, nullptr, 0);
            // need better code here!
            myStation.meta[0].type = uVal;
            metaTypePresent++;
        } else if ((pos = line.find("Meta String: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            sValue = line.substr(strlen("Meta String: "));
            myStation.meta[0].str = sValue;
            metaStringPresent++;
        } else if ((pos = line.find("Genre Pty: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                cerr << "Genre Pty is only allowed for AMFM!" << endl;
                throw invalid_argument("Genre Pty is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Genre Pty: "));
            myStation.genre[0] = tio->setGenre(sValue);
            genrePtyPresent++;
        } else if ((pos = line.find("Genre Static Pty: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Genre Static Pty is only allowed for DAB!" << endl;
                throw invalid_argument("Genre Static Pty is only allowed for DAB");
            }
            sValue = line.substr(strlen("Genre Static Pty: "));
            myStation.genre[0] = tio->setGenre(sValue);
            genreStaticPtyPresent++;
        } else if ((pos = line.find("Genre Dynamic Pty: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Genre Dynamic Pty is only allowed for DAB!" << endl;
                throw invalid_argument("Genre Dynamic Pty is only allowed for DAB");
            }
            sValue = line.substr(strlen("Genre Dynamic Pty: "));
            myStation.genre[1] = tio->setGenre(sValue);
            genreDynamicPtyPresent++;
        } else if ((pos = line.find("Flags: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            sValue = line.substr(strlen("Flags: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.flags[0] = uVal;
            flagsPresent++;
        } else if ((pos = line.find("Quality Fieldstrength: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                cerr << "Quality Fieldstrength is only allowed for AMFM!" << endl;
                throw invalid_argument("Quality Fieldstrength is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Quality Fieldstrength: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_FIELDSTRENGTH] = uVal;
            qualityFieldstrengthPresent++;
        } else if ((pos = line.find("Quality Multipath: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                cerr << "Quality Multipath is only allowed for AMFM!" << endl;
                throw invalid_argument("Quality Multipath is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Quality Multipath: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_MULTIPATH] = uVal;
            qualityMultipathPresent++;
        } else if ((pos = line.find("Quality Digital: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                cerr << "Quality Digital is only allowed for AMFM!" << endl;
                throw invalid_argument("Quality Digital is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Quality Digital: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_DIGITAL] = uVal;
            qualityDigitalPresent++;
        } else if ((pos = line.find("Quality Bit Error Rate: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Quality Bit Error Rate is only allowed for DAB!" << endl;
                throw invalid_argument("Quality Bit Error Rate is only allowed for DAB");
            }
            sValue = line.substr(strlen("Quality Bit Error Rate: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_BER] = uVal;
            qualityBitErrorRatePresent++;
        } else if ((pos = line.find("Quality Service: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Quality Service is only allowed for DAB!" << endl;
                throw invalid_argument("Quality Service is only allowed for DAB");
            }
            sValue = line.substr(strlen("Quality Service: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_SERVICE] = uVal;
            qualityServicePresent++;
        } else if ((pos = line.find("Quality Audio: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType !=
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                cerr << "Quality Audio is only allowed for DAB!" << endl;
                throw invalid_argument("Quality Audio is only allowed for DAB");
            }
            sValue = line.substr(strlen("Quality Audio: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_AUDIO] = uVal;
            qualityAudioPresent++;
        } else {
            //cerr << "Nothing found in line [" << line << "]" << endl;
        }
    }
    myfile.close();

    // must have device entry so that other stuff can be dynamically checked accordingly
    // most likely this has been checked earlier, but you'll never know ...
    if (!deviceTypePresent) {
        if (!deviceTypePresent) cerr << "Device entry missing" << endl;
        throw invalid_argument("device type not defined in file at start");
    }

    // check for missing entries in configfile depending on deviceType

    if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
        TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
        if (!(sourceTypePresent && idFrequencyPresent && idProgramIdentifierPresent &&
            idServicePresent && namePSCodePresent && nameHDLabelPresent && nameRadiotextPresent &&
            metaTypePresent && metaStringPresent && genrePtyPresent && flagsPresent &&
            qualityFieldstrengthPresent && qualityMultipathPresent && qualityDigitalPresent)) {
            if (!sourceTypePresent) cerr << "SourceType entry missing" << endl;
            if (!idFrequencyPresent) cerr << "Id Frequency entry missing" << endl;
            if (!idProgramIdentifierPresent) cerr << "Id Program Identifier entry missing" << endl;
            if (!idServicePresent) cerr << "Id Service entry missing" << endl;
            if (!namePSCodePresent) cerr << "Name PS code entry missing" << endl;
            if (!nameHDLabelPresent) cerr << "Namem HD label entry missing" << endl;
            if (!nameRadiotextPresent) cerr << "Name Radiotext entry missing" << endl;
            if (!metaTypePresent) cerr << "Meta type entry missing" << endl;
            if (!metaStringPresent) cerr << "Meta String entry missing" << endl;
            if (!genrePtyPresent) cerr << "Genre Pty entry missing" << endl;
            if (!flagsPresent) cerr << "Flags entry missing" << endl;
            if (!qualityFieldstrengthPresent) cerr << "Quality fieldstrength entry missing" << endl;
            if (!qualityMultipathPresent) cerr << "Quality Multipath entry missing" << endl;
            if (!qualityDigitalPresent) cerr << "Quality Digital  entry missing" << endl;
            throw invalid_argument("missing mandatory entries in file");
        }

        // resize for AMFM
        myStation.sel.id.resize(4);
        myStation.name.resize(3);
        myStation.meta.resize(1);
        myStation.genre.resize(1);
        myStation.quality.resize(3);
    } else if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
        TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
        if (!(sourceTypePresent && idFrequencyPresent && idEnsemblePresent && idComponentPresent &&
            idServicePresent && nameSubcomponentLabelPresent && nameSubcomponentAbbrevPresent &&
            nameDynamicLabelPresent && nameServiceLabelPresent && nameServiceAbbrevPresent &&
            nameEnsembleLabelPresent && nameEnsembleAbbrevPresent &&
            nameEnsembleAbbrevPresent && metaTypePresent && metaStringPresent &&
            genreStaticPtyPresent && genreDynamicPtyPresent && flagsPresent &&
            qualityBitErrorRatePresent && qualityServicePresent && qualityAudioPresent)) {
            if (!sourceTypePresent) cerr << "SourceType entry missing" << endl;
            if (!idFrequencyPresent) cerr << "Id Frequency entry missing" << endl;
            if (!idEnsemblePresent) cerr << "Id Ensemble Identifier entry missing" << endl;
            if (!idComponentPresent) cerr << "Id Component entry missing" << endl;
            if (!idServicePresent) cerr << "Id Service entry missing" << endl;
            if (!nameSubcomponentLabelPresent) cerr << "Name Subcomponent Label entry missing" << endl;
            if (!nameSubcomponentAbbrevPresent) cerr << "Name Subcomponent Abbrevation entry missing" << endl;
            if (!nameDynamicLabelPresent) cerr << "Name Dynamic Label entry missing" << endl;
            if (!nameServiceLabelPresent) cerr << "Name Service Label entry missing" << endl;
            if (!nameServiceAbbrevPresent) cerr << "Name Service Abbreviation entry missing" << endl;
            if (!nameEnsembleLabelPresent) cerr << "Name Ensemble Label entry missing" << endl;
            if (!nameEnsembleAbbrevPresent) cerr << "Name Ensemble Abbreviation entry missing" << endl;
            if (!metaTypePresent) cerr << "Meta type entry missing" << endl;
            if (!metaStringPresent) cerr << "Meta String entry missing" << endl;
            if (!genreStaticPtyPresent) cerr << "Genre Static entry missing" << endl;
            if (!genreDynamicPtyPresent) cerr << "Genre Dynamic entry missing" << endl;
            if (!flagsPresent) cerr << "Flags entry missing" << endl;
            if (!qualityBitErrorRatePresent) cerr << "Quality Bit error rate entry missing" << endl;
            if (!qualityServicePresent) cerr << "Quality Service entry missing" << endl;
            if (!qualityAudioPresent) cerr << "Quality Audio entry missing" << endl;
            throw invalid_argument("missing mandatory entries in file");
        }

        // resize for DAB
        myStation.sel.id.resize(5);
        myStation.name.resize(8);
        myStation.meta.resize(1);
        myStation.genre.resize(2);
        myStation.quality.resize(3);

        myStation.stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_ENSEMBLE |
            (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_SERVICE |
            (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PRIMARY;
    } else if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType ==
        TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE) {
        // some stuff to be added here
    } else {
        cerr << "Device type currently not handled." << endl;
        throw invalid_argument("device type currently not handled");
    }

    // debug
    //dumpStation(myStation);

    return myStation;
}

vector<TunerStationTypes::TunerStationTypes::Station *>
MyFileIO::scanFiles(string dirname, TunerStationTypes::TunerStationTypes::DeviceType deviceType)
{
    DIR *dir;
    struct dirent *dirent;
    vector<TunerStationTypes::TunerStationTypes::Station *> stations;
    TunerStationTypes::TunerStationTypes::Station *station;
    string filename;
    struct stat statBuf;

    if ((dir = opendir(dirname.c_str())) == NULL) {
        throw invalid_argument("cannot open directory");
    }

    // assume there are only config files in the directory
    while((dirent = readdir(dir)) != NULL) {
        // d_ino, d_off, d_reclen, d_type, d_name[256]
        if (strcmp(dirent->d_name, ".") == 0 ||
            strcmp(dirent->d_name, "..") == 0) {
            continue;
        }

        filename = dirname + "/" + dirent->d_name;

        if (lstat(filename.c_str(), &statBuf) == -1) {
            cerr << "Stat for file " << filename << " failed." << endl;
            // add error handling
        }
        if (!(statBuf.st_mode & S_IFREG)) {
            // not a regular file, skip it
            continue;
        }
        if (access(filename.c_str(), R_OK)) {
            // not a regular file, skip it
            cerr << "Skipping file " << filename << " due to lack of permissions." << endl;
            continue;
        }

        if (verbose) {
            printf("Checking file %s\n", dirent->d_name);
        }

        // string filename(filename);
        try {
            station = new TunerStationTypes::TunerStationTypes::Station();
            *station = readFile(filename);

            if (station->sel.deviceType == (uint32_t)deviceType) {
                stations.push_back(station);
            } else {
                // cerr << "Skipping file " << filename << " due to not matching deviceType of station." << endl;
                delete station;
            }
        } catch (exception& e) {
            cerr << "Got exception ..." << e.what() << endl;
        }
    }

    closedir(dir);

    return stations;
}

struct MyStationFrequencyComparator
{
    bool operator() (TunerStationTypes::TunerStationTypes::Station* const& a, TunerStationTypes::TunerStationTypes::Station* const& b)
    {
        return (a->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] <
           b->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
    }
} MyStationFrequencyComparatorObject;

void
MyFileIO::scanStations(string dirname, TunerStationTypes::TunerStationTypes::DeviceType deviceType)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    MyFileIO *x = new MyFileIO;
    vector<TunerStationTypes::TunerStationTypes::Station *> result;
    struct timeval tv;
    set<int> notFoundAMFM;
    set<int> notFoundDAB;
    set<int> notFoundUndef;

    gettimeofday(&tv, NULL);

    for (int i = 0; i < stationsAMFM.size(); i++) {
        notFoundAMFM.insert(i);
    }
    for (int i = 0; i < stationsDAB.size(); i++) {
        notFoundDAB.insert(i);
    }
    // insert all PIcode + SID seen yet into set
    for (int i = 0; i < stationsUndef.size(); i++) {
        notFoundUndef.insert(stationsUndef[i]->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY]);
    }

    result = x->scanFiles(dirname, deviceType);

    if (verbose) {
        // it is not really required to sort the list, just for debugging purposes
        sort(result.begin(), result.end(), MyStationFrequencyComparatorObject);

        for (auto it = result.cbegin(); it != result.cend(); ++it) {
            tio->printStation(*(*it));
        }
    }

    for (auto it = result.cbegin(); it != result.cend(); ++it) {
        TunerStationTypes::TunerStationTypes::Station *myStation = *it;

        if (verbose) {
            // debug
            cout << "CHECKING STATION ... " << myStation << endl;
            tio->printStation(*myStation);
        }

        // check for FM or DAB
        if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation->sel.deviceType ==
            TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
            if (verbose) {
                cout << "STATION IS AMFM ..." << endl;
            }
            // check whether entry already exists, if yes, replace it in case it has changed
            // check for entries with the same pi code, then check frequency for all entries
            // found.
            int notused = 0;
            int found = -1;
            int piCode = myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI];
            pair<StationMapType::iterator, StationMapType::iterator> ret;
            //pair<multimap<int, TunerStationTypes::TunerStationTypes::Station *>::iterator, multimap<int, TunerStationTypes::TunerStationTypes::Station *>::iterator> ret;

            ret = piCodeMapAMFM.equal_range(piCode);
            for (auto piCodeIt = ret.first; piCodeIt != ret.second; piCodeIt++) {
                TunerStationTypes::TunerStationTypes::Station *cmpStation = (*piCodeIt).second;

                // same PI code found, check frequency
                if (myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] ==
                    cmpStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]) {
                    found = cmpStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY];
                    break;
                }
            }

            if (found == -1) {
                // entry not found, insert it
                stationsAMFM.push_back(myStation);
                stationsTimeAMFM.push_back(tv);

                // get the vector index and store it inside the record
                myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] = stationsAMFM.size()-1;
                if (verbose) {
                    cout << "AMFM STATION NOT FOUND, ADDING IT AT INDEX " << myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] << " at " << myStation << endl;
                }
                // now store the record to both maps
                freqMapAMFM.insert(
                    StationValuePair(
                        myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY],
                        myStation
                    )
                );
                piCodeMapAMFM.insert(
                    StationValuePair(
                        myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI],
                        myStation
                    )
                );
                assignComponentID(myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI]);
            } else {
                // entry found, replace it
                if (verbose) {
                    cout << "AMFM ENTRY FOUND AT OFFSET " << found << ", CHECKING DETAILS at " << stationsAMFM[found] << endl;
                }
                if ((uint32_t)stationsAMFM[found]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
                    // it was already receivable
                    // there might have been a change in quality

                    // take over ID_KEY field for later comparison since new records cannot have correct id value
                    myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] =
                        stationsAMFM[found]->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY];

                    // preserve ST_PERMANENT flag
                    if (stationsAMFM[found]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT) {
                        myStation->stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT;
                        cout << "ST_PERMANENT flag preserved" << endl;
                    }

                    if (*(stationsAMFM[found]) == *myStation) {
                        if (verbose) {
                            cout << "Nothing changed within record" << endl;
                        }
                        // nothing to do
                    } else {
                        if (verbose) {
                            cout << "Something changed within record, replacing it" << endl;
                            cout << "New record" << endl;
                            tio->printStation(*myStation);
                            cout << "Old record" << endl;
                            tio->printStation(*(stationsAMFM[found]));
                        }
                        *(stationsAMFM[found]) = *myStation;
                        stationsTimeAMFM[found] = tv;
                    }
                } else {
                    // it is again receivable
                    if (verbose) {
                        cout << "Station was already known, but not receivable. Replacing it." << endl;
                    }

                    // take over ID_KEY field for later comparison since new records cannot have correct id value
                    myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] =
                        stationsAMFM[found]->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY];

                    // preserve ST_PERMANENT flag
                    if (stationsAMFM[found]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT) {
                        myStation->stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT;
                        cout << "ST_PERMANENT flag preserved" << endl;
                    }

                    *(stationsAMFM[found]) = *myStation;
                    stationsTimeAMFM[found] = tv;
                }
                notused++;
                notFoundAMFM.erase(found);
            }

            // stuff for undef map
            // check whether we already know about the PI-code
            pair<StationMapType::iterator, StationMapType::iterator> undefRet;
            undefRet = idMapUndef.equal_range(piCode);
            found = -1;
            for (auto undefIdIt = undefRet.first; undefIdIt != undefRet.second; undefIdIt++) {
                // TunerStationTypes::TunerStationTypes::Station *cmpStation = (*undefIdIt).second;
                found++;
                break;
            }
            if (found == -1) {
                // add some fake entry
                TunerStationTypes::TunerStationTypes::Station *undefStation = new TunerStationTypes::TunerStationTypes::Station;

                undefStation->sel.id.resize(2);
                undefStation->name.resize(3);
                undefStation->flags.resize(1);
                undefStation->meta.resize(1);
                undefStation->genre.resize(2);
                undefStation->quality.resize(1);

                undefStation->sel.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE;
                // use PI code as key
                undefStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] =
                    myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI];
                undefStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_PARENT] = 0;

                undefStation->stationType = (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;

                // take HD as LONG and PS as SHORT label for now
                undefStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_LONG] =
                    myStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_HD];
                undefStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_SHORT] =
                    myStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_PS];
                // undefStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_DYNAMIC] = "";

                // meta missing

                undefStation->genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexUndef::UNDEF_GEN_STATIC] = 0;
                undefStation->genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexUndef::UNDEF_GEN_DYNAMIC] = 0;

                undefStation->flags[0] = 0;

                undefStation->quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexUndef::UNDEF_QAL_AUDIO] = 0;

                stationsUndef.push_back(undefStation);
                stationsTimeUndef.push_back(tv);
                idMapUndef.insert(
                    StationValuePair(
                        undefStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY],
                        undefStation
                    )
                );
            } else {
                // entry already existing in stationsUndef vector. Unfortunately because we have used the
                // id field for the sid here, we have no direct index into the vector. Thus we have to perform
                // some linear search here. Doing it the traditional way for now as we need the index as well
                // to update the time vector.
                for (int k = 0; k < stationsUndef.size(); k++) {
                    if (stationsUndef[k]->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] == piCode) {
                        stationsUndef[k]->stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;
                        stationsTimeUndef[k] = tv;
                        break;
                    }
                }

                // entry already found; try to remove it
                try {
                    notFoundUndef.erase(piCode);
                } catch (exception& e) {
                    //
                }
            }

            // cannot remove unused mystation record earlier than here, since we needed to copy some values
            if (notused) {
                delete myStation;
            }
        } else if ((TunerStationTypes::TunerStationTypes::DeviceType)myStation->sel.deviceType ==
            TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
            if (verbose) {
                cout << "STATION IS DAB ..." << endl;
            }
            // check whether entry already exists, if yes, replace it in case it has changed
            // check for entries with the same pi code, then check frequency for all entries
            // found.
            int notused = 0;
            int found = -1;
            int sid = myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE];
            pair<StationMapType::iterator, StationMapType::iterator> ret;
            //pair<multimap<int, TunerStationTypes::TunerStationTypes::Station *>::iterator, multimap<int, TunerStationTypes::TunerStationTypes::Station *>::iterator> ret;

            ret = serviceIdMapDAB.equal_range(sid);
            for (auto serviceIdIt = ret.first; serviceIdIt != ret.second; serviceIdIt++) {
                TunerStationTypes::TunerStationTypes::Station *cmpStation = (*serviceIdIt).second;

                // same PI code found, check frequency
                if (myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY] ==
                    cmpStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY]) {
                    found = cmpStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY];
                    break;
                }
            }

            if (found == -1) {
                // entry not found, insert it
                stationsDAB.push_back(myStation);
                stationsTimeDAB.push_back(tv);

                // get the vector index and store it inside the record
                myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] = stationsDAB.size()-1;
                if (verbose) {
                    cout << "DAB STATION NOT FOUND, ADDING IT AT INDEX " << myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] << " at " << myStation << endl;
                }
                // now store the record to both maps
                freqMapDAB.insert(
                    StationValuePair(
                        myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY],
                        myStation
                    )
                );
                serviceIdMapDAB.insert(
                    StationValuePair(
                        myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE],
                        myStation
                    )
                );
                assignComponentID(myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE]);
            } else {
                // entry found, replace it
                if (verbose) {
                    cout << "DAB ENTRY FOUND AT OFFSET " << found << ", GOING TO REPLACE IT WITH CURRENT VALUES" << endl;
                }
                if ((uint32_t)stationsDAB[found]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
                    // it was already receivable
                    // there might have been a change in quality

                    // take over ID_KEY field for later comparison since new records cannot have correct id value
                    myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] =
                        stationsDAB[found]->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY];

                    // preserve ST_PERMANENT flag
                    if (stationsDAB[found]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT) {
                        myStation->stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT;
                        cout << "ST_PERMANENT flag preserved" << endl;
                    }

                    if (*(stationsDAB[found]) == *myStation) {
                        if (verbose) {
                            cout << "Nothing changed within record" << endl;
                        }
                        // nothing to do
                    } else {
                        if (verbose) {
                            cout << "Something changed within record, replacing it" << endl;
                            cout << "New record" << endl;
                            tio->printStation(*myStation);
                            cout << "Old record" << endl;
                            tio->printStation(*(stationsDAB[found]));
                        }
                        *(stationsDAB[found]) = *myStation;
                        stationsTimeDAB[found] = tv;
                    }
                } else {
                    // it is again receivable
                    if (verbose) {
                        cout << "Station was already known, but not receivable. Replacing it." << endl;
                    }

                    // take over ID_KEY field for later comparison since new records cannot have correct id value
                    myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] =
                        stationsDAB[found]->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY];

                    // preserve ST_PERMANENT flag
                    if (stationsDAB[found]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT) {
                        myStation->stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT;
                        cout << "ST_PERMANENT flag preserved" << endl;
                    }

                    *(stationsDAB[found]) = *myStation;
                    stationsTimeDAB[found] = tv;
                }
                notused++;
                notFoundDAB.erase(found);
            }
            //
            // stuff for undef map
            // check whether we already know about the PI-code
            pair<StationMapType::iterator, StationMapType::iterator> undefRet;
            undefRet = idMapUndef.equal_range(sid);
            found = -1;
            for (auto undefIdIt = undefRet.first; undefIdIt != undefRet.second; undefIdIt++) {
                // TunerStationTypes::TunerStationTypes::Station *cmpStation = (*undefIdIt).second;
                found++;
                break;
            }
            if (found == -1) {
                // add some fake entry
                TunerStationTypes::TunerStationTypes::Station *undefStation = new TunerStationTypes::TunerStationTypes::Station;

                undefStation->sel.id.resize(2);
                undefStation->name.resize(3);
                undefStation->flags.resize(1);
                undefStation->meta.resize(1);
                undefStation->genre.resize(2);
                undefStation->quality.resize(1);

                undefStation->sel.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE;
                // use PI code as key
                undefStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] =
                    myStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE];
                undefStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_PARENT] = 0;

                undefStation->stationType = (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;

                // take Service label as LONG and Service abbrev. as SHORT label for now
                undefStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_LONG] =
                    myStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SLONG];
                undefStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_SHORT] =
                    myStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SSHORT];
                undefStation->name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_DYNAMIC] = "";

                // meta missing

                undefStation->genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexUndef::UNDEF_GEN_STATIC] = 0;
                undefStation->genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexUndef::UNDEF_GEN_DYNAMIC] = 0;

                undefStation->flags[0] = 0;

                undefStation->quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexUndef::UNDEF_QAL_AUDIO] = 0;

                stationsUndef.push_back(undefStation);
                stationsTimeUndef.push_back(tv);
                idMapUndef.insert(
                    StationValuePair(
                        undefStation->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY],
                        undefStation
                    )
                );
            } else {
                // entry already existing in stationsUndef vector. Unfortunately because we have used the
                // id field for the sid here, we have no direct index into the vector. Thus we have to perform
                // some linear search here. Doing it the traditional way for now as we need the index as well
                // to update the time vector.
                for (int k = 0; k < stationsUndef.size(); k++) {
                    if (stationsUndef[k]->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] == sid) {
                        stationsUndef[k]->stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;
                        stationsTimeUndef[k] = tv;
                        break;
                    }
                }

                // entry already found; try to remove it from list of currently not found sid's
                try {
                    notFoundUndef.erase(sid);
                } catch (exception& e) {
                    //
                }
            }

            // cannot remove unused mystation record earlier than here, since we needed to copy some values
            if (notused) {
                delete myStation;
            }
        } else {
            // error
        }
    }

    // here we know which entries of the vector were not seen during last scan
    // those entries can no longer be received
    // However make sure to remove only those stations of the deviceType we are
    // scanning.

    if (deviceType == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
        for (auto it = notFoundAMFM.cbegin(); it != notFoundAMFM.cend(); it++) {
            if ((uint32_t)stationsAMFM[*it]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
                if (verbose) {
                    cout << "AMFM ENTRY AT OFFSET" << *it << " NOT FOUND THIS RUN, NO LONGER RECEIVABLE" << endl;
                }
                stationsAMFM[*it]->stationType &= ~(uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;
                stationsTimeAMFM[*it] = tv;
            }
        }
    }

    if (deviceType == TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
        for (auto it = notFoundDAB.cbegin(); it != notFoundDAB.cend(); it++) {
            if (verbose) {
                cout << "DAB ENTRY AT OFFSET" << *it << " NOT FOUND THIS RUN, NO LONGER RECEIVABLE" << endl;
            }
            if ((uint32_t)stationsDAB[*it]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
                stationsDAB[*it]->stationType &= ~(uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;
                stationsTimeDAB[*it] = tv;
            }
        }
    }

    // Since the seek is no longer for both DAB and AMFM at the same time,
    // we do not know which undef entries are probably no longer receivable
    // since there can still be a station of devicetype that we have not checked
    // during this run.

    for (auto it = notFoundUndef.cbegin(); it != notFoundUndef.cend(); it++) {
        if (deviceType == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
            // scan was for AMFM, so check in DAB
            if (getReceivableDABStationByServiceId(*it) != NULL) {
                continue;
            }
        } else if (deviceType == TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
            // scan was for DAB, so check in AMFM
            if (getReceivableAMFMStationByPICode(*it) != NULL) {
                continue;
            }
        }

        if (verbose) {
            cout << "UNDEF ENTRY WITH PI-Code/Service Key " << *it << " NOT FOUND THIS RUN, NO LONGER RECEIVABLE" << endl;
        }

        // find entry
        for (int k = 0; k < stationsUndef.size(); k++) {
            if (stationsUndef[k]->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] == *it) {
                if ((uint32_t)stationsUndef[k]->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
                    stationsUndef[k]->stationType &= ~(uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;
                    stationsTimeUndef[k] = tv;
                }
                break;
            }
        }
    }

    // might do some sanity checks here, for example it is not allowed to have to active stations
    // on the same frequency at the same time. We can't know which stations are no longer receivable
    // until end of the files are reached, hence this check cannot be done much earlier.
}

TunerStationTypes::TunerStationTypes::Station *
MyFileIO::getReceivableAMFMStationByFrequency(int frequency)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = freqMapAMFM.equal_range(frequency);
    for (auto frequencyIt = ret.first; frequencyIt != ret.second; frequencyIt++) {
        TunerStationTypes::TunerStationTypes::Station *cmpStation = (*frequencyIt).second;
        if ((uint32_t)cmpStation->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

// Following function returns ANY station that satisfies the PI code criteria.
// This might be enhanced by returning one with the best quality.
TunerStationTypes::TunerStationTypes::Station *
MyFileIO::getReceivableAMFMStationByPICode(int piCode)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = piCodeMapAMFM.equal_range(piCode);
    for (auto piCodeIt = ret.first; piCodeIt != ret.second; piCodeIt++) {
        TunerStationTypes::TunerStationTypes::Station *cmpStation = (*piCodeIt).second;
        if ((uint32_t)cmpStation->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

TunerStationTypes::TunerStationTypes::Station
MyFileIO::getReceivableAMFMStationByIndex(int index)
{
    return *(stationsAMFM[index]);
}

TunerStationTypes::TunerStationTypes::Station *
MyFileIO::getReceivableDABStationByFrequency(int frequency)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = freqMapDAB.equal_range(frequency);
    for (auto frequencyIt = ret.first; frequencyIt != ret.second; frequencyIt++) {
        TunerStationTypes::TunerStationTypes::Station *cmpStation = (*frequencyIt).second;
        if ((uint32_t)cmpStation->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

TunerStationTypes::TunerStationTypes::Station *
MyFileIO::getReceivableDABStationByServiceId(int sid)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = serviceIdMapDAB.equal_range(sid);
    for (auto serviceIdIt = ret.first; serviceIdIt != ret.second; serviceIdIt++) {
        TunerStationTypes::TunerStationTypes::Station *cmpStation = (*serviceIdIt).second;

        if ((uint32_t)cmpStation->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

TunerStationTypes::TunerStationTypes::Station
MyFileIO::getReceivableDABStationByIndex(int index)
{
    return *(stationsDAB[index]);
}

TunerStationTypes::TunerStationTypes::Station *
MyFileIO::getReceivableUndefStationById(int id)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = idMapUndef.equal_range(id);
    for (auto idIt = ret.first; idIt != ret.second; idIt++) {
        TunerStationTypes::TunerStationTypes::Station *cmpStation = (*idIt).second;

        if ((uint32_t)cmpStation->stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

void
MyFileIO::dumpStations()
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    for (auto it = stationsAMFM.cbegin(); it != stationsAMFM.cend(); it++) {
        tio->printStation(**it);
    }
    for (auto it = stationsDAB.cbegin(); it != stationsDAB.cend(); it++) {
        tio->printStation(**it);
    }
    fflush(stdout);
    cout << fflush;
}


vector<TunerStationTypes::TunerStationTypes::Station>
MyFileIO::getFilteredAMFMStations(uint32_t filter)
{
    vector<TunerStationTypes::TunerStationTypes::Station> result;
    set <TunerStationTypes::TunerStationTypes::StationType> allValues;

    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_AUTOSTORED);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_ENSEMBLE);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_SERVICE);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_PRIMARY);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_SECONDARY);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED);

    for (auto it = stationsAMFM.cbegin(); it != stationsAMFM.cend(); it++) {
        int failed = 0;

        for (auto valIt = allValues.cbegin(); valIt != allValues.cend(); valIt++) {
            if ((filter & (uint32_t)(*valIt)) &&
                !((uint32_t)(*it)->stationType & (uint32_t)(*valIt))) {
                failed++;
            }
        }

        if (!failed) {
            result.push_back(**it);
        }
    }
    return result;
}

vector<TunerStationTypes::TunerStationTypes::Station>
MyFileIO::getFilteredDABStations(uint32_t filter)
{
    vector<TunerStationTypes::TunerStationTypes::Station> result;
    set <TunerStationTypes::TunerStationTypes::StationType> allValues;

    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_AUTOSTORED);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_ENSEMBLE);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_SERVICE);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_PRIMARY);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_SECONDARY);
    allValues.insert(TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED);

    for (auto it = stationsDAB.cbegin(); it != stationsDAB.cend(); it++) {
        int failed = 0;

        for (auto valIt = allValues.cbegin(); valIt != allValues.cend(); valIt++) {
            if ((filter & (uint32_t)(*valIt)) &&
                !((uint32_t)(*it)->stationType & (uint32_t)(*valIt))) {
                failed++;
            }
        }

        if (!failed) {
            result.push_back(**it);
        }
    }
    return result;
}

vector<TunerStationTypes::TunerStationTypes::Station>
MyFileIO::getCompleteAMFMStationList()
{
    vector<TunerStationTypes::TunerStationTypes::Station> result;

    for (auto it = stationsAMFM.cbegin(); it != stationsAMFM.cend(); it++) {
        result.push_back(**it);
    }
    return result;
}


vector<TunerStationTypes::TunerStationTypes::Station>
MyFileIO::getCompleteDABStationList()
{
    vector<TunerStationTypes::TunerStationTypes::Station> result;

    for (auto it = stationsDAB.cbegin(); it != stationsDAB.cend(); it++) {
        result.push_back(**it);
    }
    return result;
}

vector<TunerStationTypes::TunerStationTypes::Station>
MyFileIO::getCompleteUndefStationList()
{
    vector<TunerStationTypes::TunerStationTypes::Station> result;

    for (auto it = stationsUndef.cbegin(); it != stationsUndef.cend(); it++) {
        result.push_back(**it);
    }
    return result;
}

// get special update list, oldList is a complete snapshot from before!
vector<TunerStationTypes::TunerStationTypes::Station>
MyFileIO::getUpdateStationList(const vector<TunerStationTypes::TunerStationTypes::Station>& oldList, const vector<TunerStationTypes::TunerStationTypes::Station>& newList)
{
    /*
     * Cases that can happen:
     * - a receivable station is not included in oldList
     * - a now again already unreceivable station is not included in oldlist
     * - a once receivable station that was included in oldList is no longer receivable
     * - a once receivable station that was included in oldList has some other attribute change,
     *   e.g. quality
     *
     * Note that:
     * - any new records have been always added at the end of the vector
     */
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    vector<TunerStationTypes::TunerStationTypes::Station> result;

    int oldsize = oldList.size();
    int newsize = newList.size();

    cout << "Old list contains " << oldsize << " records." << endl;
    cout << "New list contains " << newsize << " records." << endl;
    // check for changes in old records
    for (int i = 0; i < oldsize; i++) {
        if (oldList[i] != newList[i]) {
            cout << "Old list has changed ..." << endl;
            result.push_back(newList[i]);
            result[result.size()-1].stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED;
        }
    }

    // any new records? If yes, add everything that is receivable
    if (newsize > oldsize) {
        for (int i = oldsize; i < newsize; i++) {
            if ((uint32_t)newList[i].stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
                cout << "Adding entry from new list ..." << endl;
                result.push_back(newList[i]);
                result[result.size()-1].stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED;
            }
        }
    }
    return result;
}

void
MyFileIO::setPermanentFlagAMFM(int index, bool flag)
{
    if (flag == true) {
        stationsAMFM[index]->stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT;
    } else {
        stationsAMFM[index]->stationType &= ~((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT);
    }
}

void
MyFileIO::setPermanentFlagDAB(int index, bool flag)
{
    if (flag == true) {
        stationsDAB[index]->stationType |= (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT;
    } else {
        stationsDAB[index]->stationType &= ~((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT);
    }
}
