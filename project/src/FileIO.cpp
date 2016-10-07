/*
 * FileIO -
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

#include "includes/FileIO.h"

using namespace std;

static int verbose = 0;

FileIO * FileIO::instance = NULL;

FileIO::FileIO()
{
	terminalIO = TerminalIO::getInstance();
}

FileIO::~FileIO()
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

FileIO *FileIO::getInstance()
{
    static Guard g;
    if (instance == NULL) {
        instance = new FileIO();
    }
    return instance;
}

FileIO::Guard::~Guard()
{
    if (FileIO::instance != NULL) {
        delete FileIO::instance;
    }
}

// assign Component ID to PiCode or service id
uint32_t FileIO::assignComponentID(uint32_t code)
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

IVIRadio::Station::StationTypes::Station FileIO::readFile(string filename)
{
    ifstream myfile(filename);
    string line;
    TerminalIO *tio = TerminalIO::getInstance();
    IVIRadio::Station::StationTypes::Station myStation;

    // General
    int deviceTypePresent 	= 0;
    int sourceTypePresent 	= 0;
    int metaTypePresent 	= 0;
    int metaStringPresent 	= 0;
    int flagsPresent 		= 0;
    int idFrequencyPresent 	= 0;
    int idServicePresent 	= 0;

    // AMFM only
    int idProgramIdentifierPresent 	= 0;
    int namePSCodePresent 			= 0;
    int nameHDLabelPresent 			= 0;
    int nameRadiotextPresent 		= 0;
    int qualityFieldstrengthPresent = 0;
    int qualityMultipathPresent 	= 0;
    int qualityDigitalPresent 		= 0;
    int genrePtyPresent 			= 0;

    // DAB specific
    int idEnsemblePresent 				= 0;
    int idComponentPresent 				= 0;
    int nameSubcomponentLabelPresent 	= 0;
    int nameSubcomponentAbbrevPresent 	= 0;
    int nameDynamicLabelPresent 		= 0;
    int nameServiceLabelPresent 		= 0;
    int nameServiceAbbrevPresent 		= 0;
    int nameEnsembleLabelPresent 		= 0;
    int nameEnsembleAbbrevPresent 		= 0;
    int nameFrequencyLabelPresent 		= 0;
    int genreStaticPtyPresent	 		= 0;
    int genreDynamicPtyPresent 			= 0;
    int qualityBitErrorRatePresent 		= 0;
    int qualityServicePresent 			= 0;
    int qualityAudioPresent 			= 0;

    if (!myfile.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        throw invalid_argument("unable to open file");
    }

    // resize vector's to whatever is MAX needed in AMFM + DAB + UNDEF
    // later we will reduce to what is actually needed once we know the
    // final deviceType

    myStation.sel.id.resize(5);
    //myStation.flags.resize(1);
    myStation.name.resize(8);
    //myStation.meta.resize(1);
    myStation.genre.resize(2);
    myStation.quality.resize(3);
    myStation.stationType = (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_AUTOSTORED |
        (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE;

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
        //myStation.sel.deviceType = getTag( "DeviceType: " );
        if ((pos = line.find("DeviceType: ")) != string::npos) {
            // Generic
            sValue = line.substr(strlen("DeviceType: "));
            myStation.sel.deviceType = (uint32_t)tio->setDeviceType(sValue);
            deviceTypePresent++;
        }
        else if ((pos = line.find("SourceType: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            sValue = line.substr(strlen("SourceType: "));
            // no storage for this one
            sourceTypePresent++;
        }
        else if ((pos = line.find("Id Frequency: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }

            // set dummy value for ID_KEY field
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
                IVIRadio::Types::Types::DeviceType::AMFM) {
                myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] = 0;
            } else if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
                IVIRadio::Types::Types::DeviceType::DAB) {
                myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] = 0;
            } else {
                // error
            }

            sValue = line.substr(strlen("Id Frequency: "));
            uVal = stoul (sValue, nullptr, 0);
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
                IVIRadio::Types::Types::DeviceType::AMFM) {
                myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = uVal;
            } else if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
                IVIRadio::Types::Types::DeviceType::DAB) {
                myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] = uVal;
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
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::AMFM) {
                cerr << "ID Program identifier is only allowed for AMFM!" << endl;
                throw invalid_argument("ID Program identifier is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Id Program Identifier: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI] = uVal;
            idProgramIdentifierPresent++;
        } else if ((pos = line.find("Id Service: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            sValue = line.substr(strlen("Id Service: "));
            uVal = stoul (sValue, nullptr, 0);
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
                IVIRadio::Types::Types::DeviceType::AMFM) {
                myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = uVal;
            } else if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
                IVIRadio::Types::Types::DeviceType::DAB) {
                myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE] = uVal;
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
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "ID Ensemble is only allowed for DAB!" << endl;
                throw invalid_argument("ID Ensemble is only allowed for DAB");
            }
            sValue = line.substr(strlen("Id Ensemble: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = uVal;
            idEnsemblePresent++;
        } else if ((pos = line.find("Id Component: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "ID Component is only allowed for DAB!" << endl;
                throw invalid_argument("ID Component is only allowed for DAB");
            }
            sValue = line.substr(strlen("Id Component: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT] = uVal;
            idComponentPresent++;
        } else if ((pos = line.find("Name PS Code: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::AMFM) {
                cerr << "Name PS Code is only allowed for AMFM!" << endl;
                throw invalid_argument("Name PS Code is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Name PS Code: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_PS] = sValue;
            namePSCodePresent++;
        } else if ((pos = line.find("Name HD Label: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::AMFM) {
                cerr << "Name HD Label is only allowed for AMFM!" << endl;
                throw invalid_argument("Name HD Label is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Name HD Label: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_HD] = sValue;
            nameHDLabelPresent++;
        } else if ((pos = line.find("Name Radiotext: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::AMFM) {
                cerr << "Name Radiotext is only allowed for AMFM!" << endl;
                throw invalid_argument("Name Radiotext is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Name Radiotext: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_RT] = sValue;
            nameRadiotextPresent++;
        } else if ((pos = line.find("Name Subcomponent Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Name Subcomponent Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Subcomponent Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Subcomponent Label: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_CLONG] = sValue;
            nameSubcomponentLabelPresent++;
        } else if ((pos = line.find("Name Subcomponent Abbreviation: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Name Subcomponent Abbreviation is only allowed for DAB!" << endl;
                throw invalid_argument("Name Subcomponent Abbreviation is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Subcomponent Abbreviation: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_CSHORT] = sValue;
            nameSubcomponentAbbrevPresent++;
        } else if ((pos = line.find("Name Dynamic Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Name Dynamic Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Dynamic Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Dynamic Label: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_DYNAMIC] = sValue;
            nameDynamicLabelPresent++;
        } else if ((pos = line.find("Name Service Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Name Service Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Service Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Service Label: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SLONG] = sValue;
            nameServiceLabelPresent++;
        } else if ((pos = line.find("Name Service Abbreviation: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Name Service Abbreviation is only allowed for DAB!" << endl;
                throw invalid_argument("Name Service Abbreviation is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Service Abbreviation: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SSHORT] = sValue;
            nameServiceAbbrevPresent++;
        } else if ((pos = line.find("Name Ensemble Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Name Ensemble Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Ensemble Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Ensemble Label: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_ELONG] = sValue;
            nameEnsembleLabelPresent++;
        } else if ((pos = line.find("Name Ensemble Abbreviation: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Name Ensemble Abbreviation is only allowed for DAB!" << endl;
                throw invalid_argument("Name Ensemble Abbreviation is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Ensemble Abbreviation: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_ESHORT] = sValue;
            nameEnsembleAbbrevPresent++;
        } else if ((pos = line.find("Name Frequency Label: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Name Frequency Label is only allowed for DAB!" << endl;
                throw invalid_argument("Name Frequency Label is only allowed for DAB");
            }
            sValue = line.substr(strlen("Name Frequency Label: "));
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_FREQUENCY] = sValue;
            nameFrequencyLabelPresent++;
        }
        // here I need to read a list of component types the station transmits. therefore two vectors are saved
        // in the database. One contains the ComponentTypes and the other a unique ID
        else if ((pos = line.find("Meta Type: ")) != string::npos) {
            // Generic
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            IVIRadio::Station::StationTypes::Metadata tmp_meta;
            sValue = line.substr(strlen("Meta Type: "));
            int i = 1;

			while ( sValue.find(",") != string::npos ) {
				string stmp = sValue.substr( 0 , sValue.find(",") );
				uVal = stoul ( stmp, nullptr, 0 );
				sValue = sValue.substr( sValue.find(",") + 1 );
				IVIRadio::Station::StationTypes::Metadata tmp_meta;
				tmp_meta.type = uVal;
				myStation.meta.push_back( tmp_meta );
				i++;
			}
			if ( sValue.length() > 0 ) {//push last value into list
				uVal = stoul (sValue, nullptr, 0);
				IVIRadio::Station::StationTypes::Metadata tmp_meta;
				tmp_meta.type = uVal;
				myStation.meta.push_back( tmp_meta );
			}
            metaTypePresent++;
        } else if ( ( pos = line.find("Meta String: ")) != string::npos ) { //1,2,3
            // Generic
        	vector < string > vtmp;
            if ( !deviceTypePresent ) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            sValue = line.substr( strlen( "Meta String: " ) );
            int i = 0;

            while ( sValue.find(",") != string::npos ){
            	string tmp = sValue.substr( 0 , sValue.find(",") );
            	sValue = sValue.substr( sValue.find(",") + 1 );
            	vtmp.push_back(tmp);
            	i++;
            }
            int len_tmp = sValue.length();
            if ( len_tmp > 0) { //push last value into list
            	vtmp.push_back( sValue );
            }
            i = 0;
            for ( auto ittmp = vtmp.cbegin(); ittmp != vtmp.cend(); ++ittmp) {
            	myStation.meta.at(i).str = ( *ittmp );
            	i++;
			}
            metaStringPresent++;
        } else if ( ( pos = line.find("Genre Pty: ") ) != string::npos ) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::AMFM) {
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
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
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
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
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
            //myStation.flags[0] = uVal;
            myStation.flags = uVal;
            flagsPresent++;
        } else if ((pos = line.find("Quality Fieldstrength: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::AMFM) {
                cerr << "Quality Fieldstrength is only allowed for AMFM!" << endl;
                throw invalid_argument("Quality Fieldstrength is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Quality Fieldstrength: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_FIELDSTRENGTH] = uVal;
            qualityFieldstrengthPresent++;
        } else if ((pos = line.find("Quality Multipath: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::AMFM) {
                cerr << "Quality Multipath is only allowed for AMFM!" << endl;
                throw invalid_argument("Quality Multipath is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Quality Multipath: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_MULTIPATH] = uVal;
            qualityMultipathPresent++;
        } else if ((pos = line.find("Quality Digital: ")) != string::npos) {
            // AMFM only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::AMFM) {
                cerr << "Quality Digital is only allowed for AMFM!" << endl;
                throw invalid_argument("Quality Digital is only allowed for AMFM");
            }
            sValue = line.substr(strlen("Quality Digital: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_DIGITAL] = uVal;
            qualityDigitalPresent++;
        } else if ((pos = line.find("Quality Bit Error Rate: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Quality Bit Error Rate is only allowed for DAB!" << endl;
                throw invalid_argument("Quality Bit Error Rate is only allowed for DAB");
            }
            sValue = line.substr(strlen("Quality Bit Error Rate: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_BER] = uVal;
            qualityBitErrorRatePresent++;
        } else if ((pos = line.find("Quality Service: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Quality Service is only allowed for DAB!" << endl;
                throw invalid_argument("Quality Service is only allowed for DAB");
            }
            sValue = line.substr(strlen("Quality Service: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_SERVICE] = uVal;
            qualityServicePresent++;
        } else if ((pos = line.find("Quality Audio: ")) != string::npos) {
            // DAB only
            if (!deviceTypePresent) {
                cerr << "Device type must be defined first!" << endl;
                throw invalid_argument("device type not defined in file at start");
            }
            if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType !=
                IVIRadio::Types::Types::DeviceType::DAB) {
                cerr << "Quality Audio is only allowed for DAB!" << endl;
                throw invalid_argument("Quality Audio is only allowed for DAB");
            }
            sValue = line.substr(strlen("Quality Audio: "));
            uVal = stoul (sValue, nullptr, 0);
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_AUDIO] = uVal;
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

    if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
        IVIRadio::Types::Types::DeviceType::AMFM) {
        if ( ! ( sourceTypePresent && idFrequencyPresent && idProgramIdentifierPresent &&
        		 idServicePresent  && namePSCodePresent  && nameHDLabelPresent 	&& nameRadiotextPresent &&
        		 metaTypePresent   && metaStringPresent  && genrePtyPresent 	&& flagsPresent &&
        		 qualityFieldstrengthPresent && qualityMultipathPresent 		&& qualityDigitalPresent)) {
            if (!sourceTypePresent) 		 cerr << "SourceType entry missing" 			<< endl;
            if (!idFrequencyPresent) 		 cerr << "Id Frequency entry missing" 			<< endl;
            if (!idProgramIdentifierPresent) cerr << "Id Program Identifier entry missing" 	<< endl;
            if (!idServicePresent) 			 cerr << "Id Service entry missing" 			<< endl;
            if (!namePSCodePresent) 		 cerr << "Name PS code entry missing" 			<< endl;
            if (!nameHDLabelPresent) 		 cerr << "Namem HD label entry missing" 		<< endl;
            if (!nameRadiotextPresent)		 cerr << "Name Radiotext entry missing" 		<< endl;
            if (!metaTypePresent)			 cerr << "Meta type entry missing" 				<< endl;
            if (!metaStringPresent)			 cerr << "Meta String entry missing" 			<< endl;
            if (!genrePtyPresent)			 cerr << "Genre Pty entry missing" 				<< endl;
            if (!flagsPresent)				 cerr << "Flags entry missing" 					<< endl;
            if (!qualityFieldstrengthPresent)cerr << "Quality fieldstrength entry missing" 	<< endl;
            if (!qualityMultipathPresent) 	 cerr << "Quality Multipath entry missing" 		<< endl;
            if (!qualityDigitalPresent)		 cerr << "Quality Digital  entry missing" 		<< endl;
            throw invalid_argument("missing mandatory entries in file");
        }

        // resize for AMFM
        myStation.sel.id.resize(4);
        myStation.name.resize(3);
      //  myStation.meta.resize( sizeOfGenre );
        myStation.genre.resize(1);
        myStation.quality.resize(3);
    } else if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
        IVIRadio::Types::Types::DeviceType::DAB) {
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
 //       myStation.meta.resize( sizeOfGenre );
        myStation.genre.resize(2);
        myStation.quality.resize(3);

        myStation.stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_ENSEMBLE |
            (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_SERVICE |
            (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PRIMARY;
    } else if ((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType ==
        IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE) {
        // some stuff to be added here
    } else {
        cerr << "Device type currently not handled." << endl;
        throw invalid_argument("device type currently not handled");
    }

    return myStation;
}

vector<IVIRadio::Station::StationTypes::Station *>
FileIO::scanFiles(string dirname, IVIRadio::Types::Types::DeviceType deviceType)
{
    DIR *dir;
    struct dirent *dirent;
    vector<IVIRadio::Station::StationTypes::Station *> stations;
    IVIRadio::Station::StationTypes::Station *station;
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
            station = new IVIRadio::Station::StationTypes::Station();
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
    bool operator() (IVIRadio::Station::StationTypes::Station* const& a, IVIRadio::Station::StationTypes::Station* const& b)
    {
        return (a->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] <
           b->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
    }
} MyStationFrequencyComparatorObject;

void FileIO::scanStations(string dirname, IVIRadio::Types::Types::DeviceType deviceType)
{

    FileIO *x = new FileIO;
    vector<IVIRadio::Station::StationTypes::Station *> result;
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
        notFoundUndef.insert(stationsUndef[i]->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY]);
    }

    result = x->scanFiles(dirname, deviceType);

    if (verbose) {
        // it is not really required to sort the list, just for debugging purposes
        sort(result.begin(), result.end(), MyStationFrequencyComparatorObject);

        for (auto it = result.cbegin(); it != result.cend(); ++it) {
        	terminalIO->printStation(*(*it));
        }
    }

    for (auto it = result.cbegin(); it != result.cend(); ++it) {
        IVIRadio::Station::StationTypes::Station *myStation = *it;

        if (verbose){
			// debug
			cout << "CHECKING STATION ... " << myStation << endl;
			terminalIO->printStation(*myStation);
        }

        // check for FM or DAB
        if ((IVIRadio::Types::Types::DeviceType)myStation->sel.deviceType ==
            IVIRadio::Types::Types::DeviceType::AMFM) {
            if (verbose) {
                cout << "STATION IS AMFM ..." << endl;
            }
            // check whether entry already exists, if yes, replace it in case it has changed
            // check for entries with the same pi code, then check frequency for all entries
            // found.
            int notused = 0;
            int found = -1;
            int piCode = myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI];
            pair<StationMapType::iterator, StationMapType::iterator> ret;
            //pair<multimap<int, IVIRadio::Station::StationTypes::Station *>::iterator, multimap<int, IVIRadio::Station::StationTypes::Station *>::iterator> ret;

            ret = piCodeMapAMFM.equal_range(piCode);
            for (auto piCodeIt = ret.first; piCodeIt != ret.second; piCodeIt++) {
                IVIRadio::Station::StationTypes::Station *cmpStation = (*piCodeIt).second;

                // same PI code found, check frequency
                if (myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] ==
                    cmpStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]) {
                    found = cmpStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY];
                    break;
                }
            }

            if (found == -1) {
                // entry not found, insert it
                stationsAMFM.push_back(myStation);
                stationsTimeAMFM.push_back(tv);

                // get the vector index and store it inside the record //have some changes here
                myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] = stationsAMFM.size() - 1 + stationsDAB.size();
                if (verbose) {
                    cout << "AMFM STATION NOT FOUND, ADDING IT AT INDEX " << myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] << " at " << myStation << endl;
                }
                // now store the record to both maps
                freqMapAMFM.insert(
                    StationValuePair(
                        myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY],
                        myStation
                    )
                );
                piCodeMapAMFM.insert(
                    StationValuePair(
                        myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI],
                        myStation
                    )
                );
                assignComponentID(myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI]);
            } else {
                // entry found, replace it
                if (verbose) {
                    cout << "AMFM ENTRY FOUND AT OFFSET " << found << ", CHECKING DETAILS at " << stationsAMFM[found] << endl;
                }
                if ((uint32_t)stationsAMFM[found]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
                    // it was already receivable
                    // there might have been a change in quality

                    // take over ID_KEY field for later comparison since new records cannot have correct id value
                    myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] =
                        stationsAMFM[found]->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY];

                    // preserve ST_PERMANENT flag
                    if (stationsAMFM[found]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT) {
                        myStation->stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT;
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
                            terminalIO->printStation(*myStation);
                            cout << "Old record" << endl;
                            terminalIO->printStation(*(stationsAMFM[found]));
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
                    myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] =
                        stationsAMFM[found]->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY];

                    // preserve ST_PERMANENT flag
                    if (stationsAMFM[found]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT) {
                        myStation->stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT;
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
                // IVIRadio::Station::StationTypes::Station *cmpStation = (*undefIdIt).second;
                found++;
                break;
            }
            if (found == -1) {
                // add some fake entry
                IVIRadio::Station::StationTypes::Station *undefStation = new IVIRadio::Station::StationTypes::Station;

                undefStation->sel.id.resize(2);
                undefStation->name.resize(3);
                //undefStation->flags.resize(1);
                undefStation->meta.resize(1);
                undefStation->genre.resize(2);
                undefStation->quality.resize(1);

                undefStation->sel.deviceType = (uint32_t)IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE;
                // use PI code as key
                undefStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] =
                    myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI];
                undefStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_PARENT] = 0;

                undefStation->stationType = (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE;

                // take HD as LONG and PS as SHORT label for now
                undefStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_LONG] =
                    myStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_HD];
                undefStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_SHORT] =
                    myStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_PS];
                // undefStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_DYNAMIC] = "";

                // meta missing

                undefStation->genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexUndef::UNDEF_GEN_STATIC] = 0;
                undefStation->genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexUndef::UNDEF_GEN_DYNAMIC] = 0;

                //undefStation->flags[0] = 0;
                undefStation->flags = 0;

                undefStation->quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexUndef::UNDEF_QAL_AUDIO] = 0;

                stationsUndef.push_back(undefStation);
                stationsTimeUndef.push_back(tv);
                idMapUndef.insert(
                    StationValuePair(
                        undefStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY],
                        undefStation
                    )
                );
            } else {
                // entry already existing in stationsUndef vector. Unfortunately because we have used the
                // id field for the sid here, we have no direct index into the vector. Thus we have to perform
                // some linear search here. Doing it the traditional way for now as we need the index as well
                // to update the time vector.
                for (int k = 0; k < stationsUndef.size(); k++) {
                    if (stationsUndef[k]->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] == piCode) {
                        stationsUndef[k]->stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE;
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
        } else if ((IVIRadio::Types::Types::DeviceType)myStation->sel.deviceType ==
            IVIRadio::Types::Types::DeviceType::DAB) {
            if (verbose) {
                cout << "STATION IS DAB ..." << endl;
            }
            // check whether entry already exists, if yes, replace it in case it has changed
            // check for entries with the same pi code, then check frequency for all entries
            // found.
            int notused = 0;
            int found = -1;
            int sid = myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE];
            pair<StationMapType::iterator, StationMapType::iterator> ret;
            //pair<multimap<int, IVIRadio::Station::StationTypes::Station *>::iterator, multimap<int, IVIRadio::Station::StationTypes::Station *>::iterator> ret;

            ret = serviceIdMapDAB.equal_range(sid);
            for (auto serviceIdIt = ret.first; serviceIdIt != ret.second; serviceIdIt++) {
                IVIRadio::Station::StationTypes::Station *cmpStation = (*serviceIdIt).second;

                // same PI code found, check frequency
                if (myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] ==
                    cmpStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY]) {
                    found = cmpStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY];
                    break;
                }
            }

            if (found == -1) {
                // entry not found, insert it
                stationsDAB.push_back(myStation);
                stationsTimeDAB.push_back(tv);

                // get the vector index and store it inside the record //have some changes here
                myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] = stationsDAB.size()-1 + stationsAMFM.size();
                if (verbose) {
                    cout << "DAB STATION NOT FOUND, ADDING IT AT INDEX " << myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] << " at " << myStation << endl;
                }
                // now store the record to both maps
                freqMapDAB.insert(
                    StationValuePair(
                        myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY],
                        myStation
                    )
                );
                serviceIdMapDAB.insert(
                    StationValuePair(
                        myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE],
                        myStation
                    )
                );
                assignComponentID(myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE]);
            } else {
                // entry found, replace it
                if (verbose) {
                    cout << "DAB ENTRY FOUND AT OFFSET " << found << ", GOING TO REPLACE IT WITH CURRENT VALUES" << endl;
                }
                if ((uint32_t)stationsDAB[found]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
                    // it was already receivable
                    // there might have been a change in quality

                    // take over ID_KEY field for later comparison since new records cannot have correct id value
                    myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] =
                        stationsDAB[found]->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY];

                    // preserve ST_PERMANENT flag
                    if (stationsDAB[found]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT) {
                        myStation->stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT;
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
                            terminalIO->printStation(*myStation);
                            cout << "Old record" << endl;
                            terminalIO->printStation(*(stationsDAB[found]));
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
                    myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] =
                        stationsDAB[found]->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY];

                    // preserve ST_PERMANENT flag
                    if (stationsDAB[found]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT) {
                        myStation->stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT;
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
                // IVIRadio::Station::StationTypes::Station *cmpStation = (*undefIdIt).second;
                found++;
                break;
            }
            if (found == -1) {
                // add some fake entry
                IVIRadio::Station::StationTypes::Station *undefStation = new IVIRadio::Station::StationTypes::Station;

                undefStation->sel.id.resize(2);
                undefStation->name.resize(3);
                //undefStation->flags.resize(1);
                undefStation->meta.resize(1);
                undefStation->genre.resize(2);
                undefStation->quality.resize(1);

                undefStation->sel.deviceType = (uint32_t)IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE;
                // use PI code as key
                undefStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] =
                    myStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE];
                undefStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_PARENT] = 0;

                undefStation->stationType = (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE;

                // take Service label as LONG and Service abbrev. as SHORT label for now
                undefStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_LONG] =
                    myStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SLONG];
                undefStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_SHORT] =
                    myStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SSHORT];
                undefStation->name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_DYNAMIC] = "";

                // meta missing

                undefStation->genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexUndef::UNDEF_GEN_STATIC ] = 0;
                undefStation->genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexUndef::UNDEF_GEN_DYNAMIC] = 0;

                //undefStation->flags[0] = 0;
                undefStation->flags = 0;

                undefStation->quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexUndef::UNDEF_QAL_AUDIO] = 0;

                stationsUndef.push_back(undefStation);
                stationsTimeUndef.push_back(tv);
                idMapUndef.insert(
                    StationValuePair(
                        undefStation->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY],
                        undefStation
                    )
                );
            } else {
                // entry already existing in stationsUndef vector. Unfortunately because we have used the
                // id field for the sid here, we have no direct index into the vector. Thus we have to perform
                // some linear search here. Doing it the traditional way for now as we need the index as well
                // to update the time vector.
                for (int k = 0; k < stationsUndef.size(); k++) {
                    if (stationsUndef[k]->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] == sid) {
                        stationsUndef[k]->stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE;
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

    if (deviceType == IVIRadio::Types::Types::DeviceType::AMFM) {
        for (auto it = notFoundAMFM.cbegin(); it != notFoundAMFM.cend(); it++) {
            if ((uint32_t)stationsAMFM[*it]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
                if (verbose) {
                    cout << "AMFM ENTRY AT OFFSET" << *it << " NOT FOUND THIS RUN, NO LONGER RECEIVABLE" << endl;
                }
                stationsAMFM[*it]->stationType &= ~(uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE;
                stationsTimeAMFM[*it] = tv;
            }
        }
    }

    if (deviceType == IVIRadio::Types::Types::DeviceType::DAB) {
        for (auto it = notFoundDAB.cbegin(); it != notFoundDAB.cend(); it++) {
            if (verbose) {
                cout << "DAB ENTRY AT OFFSET" << *it << " NOT FOUND THIS RUN, NO LONGER RECEIVABLE" << endl;
            }
            if ((uint32_t)stationsDAB[*it]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
                stationsDAB[*it]->stationType &= ~(uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE;
                stationsTimeDAB[*it] = tv;
            }
        }
    }

    // Since the seek is no longer for both DAB and AMFM at the same time,
    // we do not know which undef entries are probably no longer receivable
    // since there can still be a station of devicetype that we have not checked
    // during this run.

    for (auto it = notFoundUndef.cbegin(); it != notFoundUndef.cend(); it++) {
        if (deviceType == IVIRadio::Types::Types::DeviceType::AMFM) {
            // scan was for AMFM, so check in DAB
            if (getReceivableDABStationByServiceId(*it) != NULL) {
                continue;
            }
        } else if (deviceType == IVIRadio::Types::Types::DeviceType::DAB) {
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
            if (stationsUndef[k]->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] == *it) {
                if ((uint32_t)stationsUndef[k]->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
                    stationsUndef[k]->stationType &= ~(uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE;
                    stationsTimeUndef[k] = tv;
                }
                break;
            }
        }
    }
    cout << "Scan station successfully"  << endl;
    //dumpStations();

    // might do some sanity checks here, for example it is not allowed to have to active stations
    // on the same frequency at the same time. We can't know which stations are no longer receivable
    // until end of the files are reached, hence this check cannot be done much earlier.
}

IVIRadio::Station::StationTypes::Station * FileIO::getReceivableAMFMStationByFrequency(int frequency)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = freqMapAMFM.equal_range(frequency);
    for (auto frequencyIt = ret.first; frequencyIt != ret.second; frequencyIt++) {
        IVIRadio::Station::StationTypes::Station *cmpStation = (*frequencyIt).second;
        if ((uint32_t)cmpStation->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

// Following function returns ANY station that satisfies the PI code criteria.
// This might be enhanced by returning one with the best quality.
IVIRadio::Station::StationTypes::Station *
FileIO::getReceivableAMFMStationByPICode(int piCode)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = piCodeMapAMFM.equal_range(piCode);
    for (auto piCodeIt = ret.first; piCodeIt != ret.second; piCodeIt++) {
        IVIRadio::Station::StationTypes::Station *cmpStation = (*piCodeIt).second;
        if ((uint32_t)cmpStation->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

IVIRadio::Station::StationTypes::Station
FileIO::getReceivableAMFMStationByIndex(int index)
{
    return *(stationsAMFM[index]);
}

IVIRadio::Station::StationTypes::Station *
FileIO::getReceivableDABStationByFrequency(int frequency)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = freqMapDAB.equal_range(frequency);
    for (auto frequencyIt = ret.first; frequencyIt != ret.second; frequencyIt++) {
        IVIRadio::Station::StationTypes::Station *cmpStation = (*frequencyIt).second;
        if ((uint32_t)cmpStation->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

IVIRadio::Station::StationTypes::Station *
FileIO::getReceivableDABStationByServiceId(int sid)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = serviceIdMapDAB.equal_range(sid);
    for (auto serviceIdIt = ret.first; serviceIdIt != ret.second; serviceIdIt++) {
        IVIRadio::Station::StationTypes::Station *cmpStation = (*serviceIdIt).second;

        if ((uint32_t)cmpStation->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }

    return NULL;
}

IVIRadio::Station::StationTypes::Station
FileIO::getReceivableDABStationByIndex(int index)
{
    return *(stationsDAB[index]);
}

IVIRadio::Station::StationTypes::Station *
FileIO::getReceivableUndefStationById(int id)
{
    pair<StationMapType::iterator, StationMapType::iterator> ret;
    ret = idMapUndef.equal_range(id);
    for (auto idIt = ret.first; idIt != ret.second; idIt++) {
        IVIRadio::Station::StationTypes::Station *cmpStation = (*idIt).second;

        if ((uint32_t)cmpStation->stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
            return cmpStation;
        }
    }
    return NULL;
}

void
FileIO::dumpStations()
{
    for (auto it = stationsAMFM.cbegin(); it != stationsAMFM.cend(); it++) {
    	terminalIO->printStation(**it);
    }
    for (auto it = stationsDAB.cbegin(); it != stationsDAB.cend(); it++) {
    	terminalIO->printStation(**it);
    }
    cout << fflush;
}


vector<IVIRadio::Station::StationTypes::Station>
FileIO::getFilteredAMFMStations(uint32_t filter)
{
    vector <IVIRadio::Station::StationTypes::Station>     result;
    set    <IVIRadio::Station::StationTypes::StationType> allValues;

    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_PERMANENT);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_AUTOSTORED);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_ENSEMBLE);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_SERVICE);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_PRIMARY);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_SECONDARY);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_CHANGED);

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

vector<IVIRadio::Station::StationTypes::Station>
FileIO::getFilteredDABStations(uint32_t filter)
{
    vector<IVIRadio::Station::StationTypes::Station> result;
    set <IVIRadio::Station::StationTypes::StationType> allValues;

    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_PERMANENT);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_AUTOSTORED);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_ENSEMBLE);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_SERVICE);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_PRIMARY);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_SECONDARY);
    allValues.insert(IVIRadio::Station::StationTypes::StationType::ST_CHANGED);

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

vector<IVIRadio::Station::StationTypes::Station>
FileIO::getCompleteAMFMStationList()
{
    vector<IVIRadio::Station::StationTypes::Station> result;

    for (auto it = stationsAMFM.cbegin(); it != stationsAMFM.cend(); it++) {
        result.push_back(**it);
    }
    return result;
}


vector<IVIRadio::Station::StationTypes::Station>
FileIO::getCompleteDABStationList()
{
    vector<IVIRadio::Station::StationTypes::Station> result;

    for (auto it = stationsDAB.cbegin(); it != stationsDAB.cend(); it++) {
        result.push_back(**it);
    }
    return result;
}

vector<IVIRadio::Station::StationTypes::Station>
FileIO::getCompleteUndefStationList()
{
    vector<IVIRadio::Station::StationTypes::Station> result;

    for (auto it = stationsUndef.cbegin(); it != stationsUndef.cend(); it++) {
        result.push_back(**it);
    }
    return result;
}

// get special update list, oldList is a complete snapshot from before!
vector<IVIRadio::Station::StationTypes::Station>
FileIO::getUpdateStationList(const vector<IVIRadio::Station::StationTypes::Station>& oldList, const vector<IVIRadio::Station::StationTypes::Station>& newList)
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

    vector<IVIRadio::Station::StationTypes::Station> result;

    int oldsize = oldList.size();
    int newsize = newList.size();

    cout << "Old list contains " << oldsize << " records." << endl;
    cout << "New list contains " << newsize << " records." << endl;
    // check for changes in old records
    for (int i = 0; i < oldsize; i++) {
        if (oldList[i] != newList[i]) {
            cout << "Old list has changed ..." << endl;
            result.push_back(newList[i]);
            result[result.size()-1].stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_CHANGED;
        }
    }

    // any new records? If yes, add everything that is receivable
    if (newsize > oldsize) {
        for (int i = oldsize; i < newsize; i++) {
            if ((uint32_t)newList[i].stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
                cout << "Adding entry from new list ..." << endl;
                result.push_back(newList[i]);
                result[result.size()-1].stationType |= (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_CHANGED;
            }
        }
    }
    return result;
}

void FileIO::setPermanentFlagAMFM(int index, bool flag)
{
	//dumpStations();
    if (flag == true) {
        stationsAMFM[index]->stationType |=   (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT;
    } else {
        stationsAMFM[index]->stationType &= ~((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT);
    }
}

void FileIO::setPermanentFlagDAB(int index, bool flag)
{
    if (flag == true) {
        stationsDAB[index]->stationType |=   (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT;
    } else {
        stationsDAB[index]->stationType &= ~((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT);
    }
}
