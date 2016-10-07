/*
Copyright (C) 2013 BMW Group

Author: Guido Ostkamp     (guido.ostkamp@de.bertrandt.com)
Author: Bernhard Singer   (bernhard.singer@partner.bmw.de)
Author: Matthias Freundel (matthias.freundel@partner.bmw.de)

This Source Code Form is subject to the terms of the Mozilla Public

License, v. 2.0. If a copy of the MPL was not distributed with this file,

You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef MY_FILE_IO_H
#define MY_FILE_IO_H

#include <memory>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <map>

#include <TunerStation/TunerStationStubDefault.h>
#include <TunerTypes/TunerTypes.h>
#include <TunerStationTypes/TunerStationTypes.h>
#include <CommonAPI/Runtime.h>

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

using namespace std;

typedef multimap<int, TunerStationTypes::TunerStationTypes::Station *> StationMapType;
typedef StationMapType::value_type StationValuePair;
typedef vector<TunerStationTypes::TunerStationTypes::Station *> StationVectorType;
typedef vector<struct timeval> StationTimeVectorType;

class MyFileIO
{
public:
    static MyFileIO *getInstance();
    vector <TunerStationTypes::TunerStationTypes::Station *> scanFiles(string dirname, TunerStationTypes::TunerStationTypes::DeviceType deviceType);
    TunerStationTypes::TunerStationTypes::Station readFile(string filename);
    void dumpStation(TunerStationTypes::TunerStationTypes::Station myStation);
    void dumpStations();
    void scanStations(string dirname, TunerStationTypes::TunerStationTypes::DeviceType deviceType);
    TunerStationTypes::TunerStationTypes::Station *getReceivableAMFMStationByFrequency(int frequency);
    TunerStationTypes::TunerStationTypes::Station *getReceivableAMFMStationByPICode(int piCode);
    TunerStationTypes::TunerStationTypes::Station getReceivableAMFMStationByIndex(int index);
    TunerStationTypes::TunerStationTypes::Station *getReceivableDABStationByFrequency(int frequency);
    TunerStationTypes::TunerStationTypes::Station *getReceivableDABStationByServiceId(int sid);
    TunerStationTypes::TunerStationTypes::Station getReceivableDABStationByIndex(int index);
    TunerStationTypes::TunerStationTypes::Station *getReceivableUndefStationById(int id);
    vector<TunerStationTypes::TunerStationTypes::Station> getFilteredAMFMStations(uint32_t filter);
    vector<TunerStationTypes::TunerStationTypes::Station> getFilteredDABStations(uint32_t filter);
    vector<TunerStationTypes::TunerStationTypes::Station> getUpdateStationList(const vector<TunerStationTypes::TunerStationTypes::Station>& oldList, const vector<TunerStationTypes::TunerStationTypes::Station>& newList);
    vector<TunerStationTypes::TunerStationTypes::Station> getCompleteDABStationList();
    vector<TunerStationTypes::TunerStationTypes::Station> getCompleteAMFMStationList();
    vector<TunerStationTypes::TunerStationTypes::Station> getCompleteUndefStationList();
    void setPermanentFlagAMFM(int index, bool flag);
    void setPermanentFlagDAB(int index, bool flag);
    uint32_t assignComponentID(uint32_t code);

private:
    static MyFileIO *instance;
    MyFileIO();
    MyFileIO(const MyFileIO&);
    ~MyFileIO();

    StationMapType freqMapAMFM;
    StationMapType piCodeMapAMFM;
    StationVectorType stationsAMFM;
    StationTimeVectorType stationsTimeAMFM;

    StationMapType freqMapDAB;
    StationMapType serviceIdMapDAB;
    StationVectorType stationsDAB;
    StationTimeVectorType stationsTimeDAB;

    StationMapType idMapUndef;
    StationVectorType stationsUndef;
    StationTimeVectorType stationsTimeUndef;

    uint32_t nextComponentID = 0;
    map<uint32_t, uint32_t> codeToComponentIDMap;

    class Guard {
        public:
            ~Guard();
    };

    friend class Guard;
};
#endif // MY_FILE_IO_H
