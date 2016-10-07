///////////////////////////////////////////////////////////
//  FileIO.h
//  Implementation of the Class FileIO
//  Created on:      16-Jul-2013 16:47:52
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_B979F634_F263_4c95_A357_1902656BA7B1__INCLUDED_)
#define EA_B979F634_F263_4c95_A357_1902656BA7B1__INCLUDED_

#include "IVIRadio/Station/StationStubDefault.h"
#include "IVIRadio/Types/Types.h"
#include "IVIRadio/Station/StationTypes.h"
#include <CommonAPI/Runtime.h>

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <set>
#include <algorithm>
#include <exception>
#include <memory>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <map>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stddef.h>

#include "TerminalIO.h"

using namespace std;

typedef multimap<int, IVIRadio::Station::StationTypes::Station *> StationMapType;
typedef StationMapType::value_type StationValuePair;
typedef vector<IVIRadio::Station::StationTypes::Station *> StationVectorType;
typedef vector<struct timeval> StationTimeVectorType;

/** \class FileIO
 *
 * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2013/11/14 14:16:20
 *
 * Contact: bernhard.singer@partner.bmw.de
 *
 *  * Copyright
 * Copyright (C) 2013, GENIVI Alliance, Inc.
 * Copyright (C) 2013, BMW AG
 *
 * Contributions are licensed to the GENIVI Alliance under one or more
 * Contribution License Agreements or MPL 2.0 .
 *
 * (C) Copyright
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
 * this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
class FileIO
{

public:
    static FileIO *getInstance();
    vector <IVIRadio::Station::StationTypes::Station *> scanFiles(string dirname, IVIRadio::Types::Types::DeviceType deviceType);
    IVIRadio::Station::StationTypes::Station readFile(string filename);
    void dumpStation(IVIRadio::Station::StationTypes::Station myStation);
    void dumpStations();
    void scanStations(string dirname, IVIRadio::Types::Types::DeviceType deviceType);

    IVIRadio::Station::StationTypes::Station *getReceivableAMFMStationByFrequency	(int frequency);
    IVIRadio::Station::StationTypes::Station *getReceivableAMFMStationByPICode		(int piCode);
    IVIRadio::Station::StationTypes::Station  getReceivableAMFMStationByIndex		(int index);
    IVIRadio::Station::StationTypes::Station *getReceivableDABStationByFrequency	(int frequency);
    IVIRadio::Station::StationTypes::Station *getReceivableDABStationByServiceId	(int sid);
    IVIRadio::Station::StationTypes::Station  getReceivableDABStationByIndex		(int index);
    IVIRadio::Station::StationTypes::Station *getReceivableUndefStationById		(int id);

    vector<IVIRadio::Station::StationTypes::Station> getFilteredAMFMStations(uint32_t filter);
    vector<IVIRadio::Station::StationTypes::Station> getFilteredDABStations(uint32_t filter);
    vector<IVIRadio::Station::StationTypes::Station> getUpdateStationList(const vector<IVIRadio::Station::StationTypes::Station>& oldList, const vector<IVIRadio::Station::StationTypes::Station>& newList);
    vector<IVIRadio::Station::StationTypes::Station> getCompleteDABStationList();
    vector<IVIRadio::Station::StationTypes::Station> getCompleteAMFMStationList();
    vector<IVIRadio::Station::StationTypes::Station> getCompleteUndefStationList();
    void setPermanentFlagAMFM(int index, bool flag);
    void setPermanentFlagDAB(int index, bool flag);
    uint32_t assignComponentID(uint32_t code);

private:
    static FileIO *instance;
    FileIO();
    FileIO(const FileIO&);
    ~FileIO();

    TerminalIO *terminalIO;

    StationMapType 			freqMapAMFM;
    StationMapType 			piCodeMapAMFM;
    StationVectorType 		stationsAMFM;
    StationTimeVectorType 	stationsTimeAMFM;

    StationMapType 			freqMapDAB;
    StationMapType 			serviceIdMapDAB;
    StationVectorType 		stationsDAB;
    StationTimeVectorType 	stationsTimeDAB;

    StationMapType 			idMapUndef;
    StationVectorType 		stationsUndef;
    StationTimeVectorType 	stationsTimeUndef;

    uint32_t nextComponentID = 0;
    map<uint32_t, uint32_t> codeToComponentIDMap;

    class Guard {
        public:
            ~Guard();
    };

    friend class Guard;

};
#endif // !defined(EA_B979F634_F263_4c95_A357_1902656BA7B1__INCLUDED_)
