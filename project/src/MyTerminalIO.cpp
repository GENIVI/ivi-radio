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
 * MyTerminalIO -
 *
 * this class deals with everything required to read input from console
 * terminal for the parameters required by the different methods, as well
 * as for printing parameters or general special and enumeration types
 * to console.
 *
 * The method prefixes used for this purpose are
 *    'enter...' (for input)
 *    'get...'   (for translation from value to string for use in print)
 *    'print...' (for actually performing print to console)
 *
 * Internally, the class contains mapping table (in both direction) from
 * enumeration values to strings and vice versa. If values are not existing
 * within an enumeration, the 'get...' method returns the string
 * 'undefined value' to avoid a crash on lookup.
 */

#include <memory>
#include <iostream>
#include <unistd.h>
#include <map>
#include <exception>
#include <set>

#include <TunerStation/TunerStationStubDefault.h>
#include <TunerTypes/TunerTypes.h>
#include <TunerStationTypes/TunerStationTypes.h>
#include <CommonAPI/Runtime.h>

#include "MyTerminalIO.h"

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

using namespace std;

MyTerminalIO::MyTerminalIO()
{
    // populate maps for reverse lookup
    for (auto it = nameToStationType.cbegin(); it != nameToStationType.cend(); ++it) {
        stationTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToSeekMode.cbegin(); it != nameToSeekMode.cend(); ++it) {
        seekModeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToSelectionMode.cbegin(); it != nameToSelectionMode.cend(); ++it) {
        selectionModeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToUpdateElement.cbegin(); it != nameToUpdateElement.cend(); ++it) {
        updateElementToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToSourceType.cbegin(); it != nameToSourceType.cend(); ++it) {
        sourceTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToDeviceType.cbegin(); it != nameToDeviceType.cend(); ++it) {
        deviceTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToFeedback.cbegin(); it != nameToFeedback.cend(); ++it) {
        feedbackToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToUpdateType.cbegin(); it != nameToUpdateType.cend(); ++it) {
        updateTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToFlagsDefUndef.cbegin(); it != nameToFlagsDefUndef.cend(); ++it) {
        flagsDefUndefToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToFlagsDefAmFm.cbegin(); it != nameToFlagsDefAmFm.cend(); ++it) {
        flagsDefAmFmToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToFlagsDefDab.cbegin(); it != nameToFlagsDefDab.cend(); ++it) {
        flagsDefDabToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToQualityIndexUndef.cbegin(); it != nameToQualityIndexUndef.cend(); ++it) {
        qualityIndexUndefToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToQualityIndexAmFm.cbegin(); it != nameToQualityIndexAmFm.cend(); ++it) {
        qualityIndexAmFmToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToQualityIndexDab.cbegin(); it != nameToQualityIndexDab.cend(); ++it) {
        qualityIndexDabToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToNameIndexDab.cbegin(); it != nameToNameIndexDab.cend(); ++it) {
        nameIndexDabToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToNameIndexAmFm.cbegin(); it != nameToNameIndexAmFm.cend(); ++it) {
        nameIndexAmFmToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToNameIndexUndef.cbegin(); it != nameToNameIndexUndef.cend(); ++it) {
        nameIndexUndefToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToIdIndexDab.cbegin(); it != nameToIdIndexDab.cend(); ++it) {
        idIndexDabToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToIdIndexAmFm.cbegin(); it != nameToIdIndexAmFm.cend(); ++it) {
        idIndexAmFmToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToIdIndexUndef.cbegin(); it != nameToIdIndexUndef.cend(); ++it) {
        idIndexUndefToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToCallStatus.cbegin(); it != nameToCallStatus.cend(); ++it) {
        callStatusToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToSeekReturnValue.cbegin(); it != nameToSeekReturnValue.cend(); ++it) {
        seekReturnValueToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToAnnouncementType.cbegin(); it != nameToAnnouncementType.cend(); ++it) {
        AnnouncementTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToComponentType.cbegin(); it != nameToComponentType.cend(); ++it) {
        ComponentTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToActivation.cbegin(); it != nameToActivation.cend(); ++it) {
        ActivationToName[(*it).second] = (*it).first;
    }
}

MyTerminalIO *MyTerminalIO::instance = NULL;

MyTerminalIO::~MyTerminalIO()
{
}

MyTerminalIO *
MyTerminalIO::getInstance()
{
    static Guard g;
    if (instance == NULL) {
        instance = new MyTerminalIO();
    }
    return instance;
}

MyTerminalIO::Guard::~Guard()
{
    if (MyTerminalIO::instance != NULL) {
        delete MyTerminalIO::instance;
    }
}

void MyTerminalIO::printMaps()
{
    // DEBUG only
    cout << "nameToStationType:" << endl;
    for (auto it = nameToStationType.cbegin(); it != nameToStationType.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "stationTypeToName:" << endl;
    for (auto it = stationTypeToName.cbegin(); it != stationTypeToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToSeekMode:" << endl;
    for (auto it = nameToSeekMode.cbegin(); it != nameToSeekMode.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "seekModeToName:" << endl;
    for (auto it = seekModeToName.cbegin(); it != seekModeToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToSelectionMode:" << endl;
    for (auto it = nameToSelectionMode.cbegin(); it != nameToSelectionMode.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "selectionModeToName:" << endl;
    for (auto it = selectionModeToName.cbegin(); it != selectionModeToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToUpdateElement:" << endl;
    for (auto it = nameToUpdateElement.cbegin(); it != nameToUpdateElement.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "updateElemenToName:" << endl;
    for (auto it = updateElementToName.cbegin(); it != updateElementToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToSourceType:" << endl;
    for (auto it = nameToSourceType.cbegin(); it != nameToSourceType.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "sourceTypeToName:" << endl;
    for (auto it = sourceTypeToName.cbegin(); it != sourceTypeToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToDeviceType:" << endl;
    for (auto it = nameToDeviceType.cbegin(); it != nameToDeviceType.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "deviceTypeToName:" << endl;
    for (auto it = deviceTypeToName.cbegin(); it != deviceTypeToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToFeedback:" << endl;
    for (auto it = nameToFeedback.cbegin(); it != nameToFeedback.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "feedbackToName:" << endl;
    for (auto it = feedbackToName.cbegin(); it != feedbackToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToUpdateType:" << endl;
    for (auto it = nameToUpdateType.cbegin(); it != nameToUpdateType.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "updateTypeToName:" << endl;
    for (auto it = updateTypeToName.cbegin(); it != updateTypeToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToFlagsDefUndef:" << endl;
    for (auto it = nameToFlagsDefUndef.cbegin(); it != nameToFlagsDefUndef.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "flagsDefUndefToName:" << endl;
    for (auto it = flagsDefUndefToName.cbegin(); it != flagsDefUndefToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToFlagsDefAmFm:" << endl;
    for (auto it = nameToFlagsDefAmFm.cbegin(); it != nameToFlagsDefAmFm.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "flagsDefAmFmToName:" << endl;
    for (auto it = flagsDefAmFmToName.cbegin(); it != flagsDefAmFmToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToFlagsDefDab:" << endl;
    for (auto it = nameToFlagsDefDab.cbegin(); it != nameToFlagsDefDab.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "flagsDefUndefToName:" << endl;
    for (auto it = flagsDefDabToName.cbegin(); it != flagsDefDabToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToQualityIndexUndef:" << endl;
    for (auto it = nameToQualityIndexUndef.cbegin(); it != nameToQualityIndexUndef.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "qualityIndexUndefToName:" << endl;
    for (auto it = qualityIndexUndefToName.cbegin(); it != qualityIndexUndefToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToQualityIndexUndef:" << endl;
    for (auto it = nameToQualityIndexAmFm.cbegin(); it != nameToQualityIndexAmFm.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "qualityIndexAmFmToName:" << endl;
    for (auto it = qualityIndexAmFmToName.cbegin(); it != qualityIndexAmFmToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToQualityIndexUndef:" << endl;
    for (auto it = nameToQualityIndexDab.cbegin(); it != nameToQualityIndexDab.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "qualityIndexDabToName:" << endl;
    for (auto it = qualityIndexDabToName.cbegin(); it != qualityIndexDabToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToNameIndexDab:" << endl;
    for (auto it = nameToNameIndexDab.cbegin(); it != nameToNameIndexDab.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "nameIndexDabToName:" << endl;
    for (auto it = nameIndexDabToName.cbegin(); it != nameIndexDabToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToNameIndexAmFm:" << endl;
    for (auto it = nameToNameIndexAmFm.cbegin(); it != nameToNameIndexAmFm.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "nameIndexAmFmToName:" << endl;
    for (auto it = nameIndexAmFmToName.cbegin(); it != nameIndexAmFmToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToNameIndexUndef:" << endl;
    for (auto it = nameToNameIndexUndef.cbegin(); it != nameToNameIndexUndef.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "nameIndexUndefToName:" << endl;
    for (auto it = nameIndexUndefToName.cbegin(); it != nameIndexUndefToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToIdIndexDab:" << endl;
    for (auto it = nameToIdIndexDab.cbegin(); it != nameToIdIndexDab.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "idIndexDabToName:" << endl;
    for (auto it = idIndexDabToName.cbegin(); it != idIndexDabToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToIdIndexAmFm:" << endl;
    for (auto it = nameToIdIndexAmFm.cbegin(); it != nameToIdIndexAmFm.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "idIndexAmFmToName:" << endl;
    for (auto it = idIndexAmFmToName.cbegin(); it != idIndexAmFmToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }

    cout << "nameToIdIndexUndef:" << endl;
    for (auto it = nameToIdIndexUndef.cbegin(); it != nameToIdIndexUndef.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    cout << "idIndexUndefToName:" << endl;
    for (auto it = idIndexUndefToName.cbegin(); it != idIndexUndefToName.cend(); ++it) {
        cout << " [" << (*it).first << ':' << (*it).second << ']' << endl;
    }
    // END DEBUG
}

/*
 * read a number inside given interval (minval-maxval) with prompt.
 */

unsigned int
MyTerminalIO::readNumber(unsigned int minval, unsigned int maxval, string question, string menu)
{
    int base;
    char *endptr, *str;
    unsigned long val;
    char buf[24];

    while(1) {
        if (menu != "") {
            printf("%s", menu.c_str());
        }
        printf("\n%s [%u-%u]: ", question.c_str(), minval, maxval);
        fflush(stdout);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            continue;
        }
        buf[strlen(buf)-1] = '\0';
        if (buf[0] == '\0') {
            continue;
        }

        base = 0;
        errno = 0;    /* To distinguish success/failure after call */
        val = strtoul(buf, &endptr, base);

        if ((errno == ERANGE && (val == ULONG_MAX || val == 0))
            || (errno != 0 && val == 0)) {
            printf("Invalid value. Please try again!\n");
            continue;
        }

        if (endptr == str) {
            printf("Invalid value. Please try again!\n");
            continue;
        }

        if (*endptr != '\0') {
            printf("Invalid value. Please try again!\n");
            continue;
        }

        if (val >= minval && val <= maxval) {
            return(val);
        }
        printf("Value out of range [%u-%u]. Please try again!\n", minval, maxval);
    }
    // NOTREACHED
}

bool
MyTerminalIO::readBoolean(string question)
{
    uint32_t result;
    printf("0 FALSE\n");
    printf("1 TRUE\n");
    result = readNumber(0, 1, question);
    printf("Selected value: %s\n", result ? "TRUE" : "FALSE");
    return result ? true : false;
}

TunerStationTypes::TunerStationTypes::StationType
MyTerminalIO::enterStationType()
{
    vector<TunerStationTypes::TunerStationTypes::StationType> x;
    uint32_t current = (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF;
    int result;
    int i;
    printf("\n");

    do {
        x.clear();
        i = 0;
        for (auto it = nameToStationType.cbegin(); it != nameToStationType.cend(); ++it, i++) {
            x.push_back((TunerStationTypes::TunerStationTypes::StationType)(*it).second);
            printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
        }
        printf("\nAlready selected: %s\n", getStationType((TunerStationTypes::TunerStationTypes::StationType)current).c_str());
        printf("Select ST_UNDEF from menu to end selection.\n");
        result = readNumber(0, x.size()-1, "Enter StationType");
        printf("Selected value: %d, meaning %s\n", result,
            stationTypeToName[(uint32_t)x[result]].c_str());
        current |= (uint32_t)x[result];
    } while(x[result] != TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF);

    return (TunerStationTypes::TunerStationTypes::StationType)current;
}

TunerStationTypes::TunerStationTypes::SeekMode
MyTerminalIO::enterSeekMode()
{
    vector<TunerStationTypes::TunerStationTypes::SeekMode> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToSeekMode.cbegin(); it != nameToSeekMode.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::SeekMode)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter SeekMode");
    printf("Selected value: %d, meaning %s\n", result,
        seekModeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::SelectionMode
MyTerminalIO::enterSelectionMode()
{
    vector<TunerStationTypes::TunerStationTypes::SelectionMode> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToSelectionMode.cbegin(); it != nameToSelectionMode.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::SelectionMode)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter SelectionMode");
    printf("Selected value: %d, meaning %s\n", result,
        selectionModeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


TunerStationTypes::TunerStationTypes::UpdateElement
MyTerminalIO::enterUpdateElement()
{
    vector<TunerStationTypes::TunerStationTypes::UpdateElement> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToUpdateElement.cbegin(); it != nameToUpdateElement.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::UpdateElement)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter UpdateElement");
    printf("Selected value: %d, meaning %s\n", result,
        updateElementToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


TunerStationTypes::TunerStationTypes::SourceType
MyTerminalIO::enterSourceType()
{
    vector<TunerStationTypes::TunerStationTypes::SourceType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToSourceType.cbegin(); it != nameToSourceType.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::SourceType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter SourceType");
    printf("Selected value: %d, meaning %s\n", result,
        sourceTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


TunerStationTypes::TunerStationTypes::DeviceType
MyTerminalIO::enterDeviceType()
{
    vector<TunerStationTypes::TunerStationTypes::DeviceType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToDeviceType.cbegin(); it != nameToDeviceType.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::DeviceType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter DeviceType");
    printf("Selected value: %d, meaning %s\n", result,
        deviceTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


TunerTypes::TunerTypes::Feedback
MyTerminalIO::enterFeedback()
{
    vector<TunerTypes::TunerTypes::Feedback> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFeedback.cbegin(); it != nameToFeedback.cend(); ++it, i++) {
        x.push_back((TunerTypes::TunerTypes::Feedback)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter Feedback");
    printf("Selected value: %d, meaning %s\n", result,
        feedbackToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::UpdateType
MyTerminalIO::enterUpdateType()
{
    vector<TunerStationTypes::TunerStationTypes::UpdateType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToUpdateType.cbegin(); it != nameToUpdateType.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::UpdateType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter UpdateType");
    printf("Selected value: %d, meaning %s\n", result,
        updateTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


TunerStationTypes::TunerStationTypes::FlagsDefUndef
MyTerminalIO::enterFlagsDefUndef()
{
    vector<TunerStationTypes::TunerStationTypes::FlagsDefUndef> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFlagsDefUndef.cbegin(); it != nameToFlagsDefUndef.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::FlagsDefUndef)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter FlagsDefUndef");
    printf("Selected value: %d, meaning %s\n", result,
        flagsDefUndefToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::FlagsDefAmFm
MyTerminalIO::enterFlagsDefAmFm()
{
    vector<TunerStationTypes::TunerStationTypes::FlagsDefAmFm> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFlagsDefAmFm.cbegin(); it != nameToFlagsDefAmFm.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::FlagsDefAmFm)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter FlagsDefAmFm");
    printf("Selected value: %d, meaning %s\n", result,
        flagsDefAmFmToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::FlagsDefDab
MyTerminalIO::enterFlagsDefDab()
{
    vector<TunerStationTypes::TunerStationTypes::FlagsDefDab> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFlagsDefDab.cbegin(); it != nameToFlagsDefDab.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::FlagsDefDab)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter FlagsDefDab");
    printf("Selected value: %d, meaning %s\n", result,
        flagsDefDabToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


TunerStationTypes::TunerStationTypes::QualityIndexUndef
MyTerminalIO::enterQualityIndexUndef()
{
    vector<TunerStationTypes::TunerStationTypes::QualityIndexUndef> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToQualityIndexUndef.cbegin(); it != nameToQualityIndexUndef.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::QualityIndexUndef)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter QualityIndexUndef");
    printf("Selected value: %d, meaning %s\n", result,
        qualityIndexUndefToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::QualityIndexAmFm
MyTerminalIO::enterQualityIndexAmFm()
{
    vector<TunerStationTypes::TunerStationTypes::QualityIndexAmFm> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToQualityIndexAmFm.cbegin(); it != nameToQualityIndexAmFm.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::QualityIndexAmFm)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter QualityIndexAmFm");
    printf("Selected value: %d, meaning %s\n", result,
        qualityIndexAmFmToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::QualityIndexDab
MyTerminalIO::enterQualityIndexDab()
{
    vector<TunerStationTypes::TunerStationTypes::QualityIndexDab> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToQualityIndexDab.cbegin(); it != nameToQualityIndexDab.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::QualityIndexDab)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter QualityIndexDab");
    printf("Selected value: %d, meaning %s\n", result,
        qualityIndexDabToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


TunerStationTypes::TunerStationTypes::NameIndexDab
MyTerminalIO::enterNameIndexDab()
{
    vector<TunerStationTypes::TunerStationTypes::NameIndexDab> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToNameIndexDab.cbegin(); it != nameToNameIndexDab.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::NameIndexDab)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter NameIndexDab");
    printf("Selected value: %d, meaning %s\n", result,
        nameIndexDabToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::NameIndexAmFm
MyTerminalIO::enterNameIndexAmFm()
{
    vector<TunerStationTypes::TunerStationTypes::NameIndexAmFm> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToNameIndexAmFm.cbegin(); it != nameToNameIndexAmFm.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::NameIndexAmFm)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter NameIndexAmFm");
    printf("Selected value: %d, meaning %s\n", result,
        nameIndexAmFmToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::NameIndexUndef
MyTerminalIO::enterNameIndexUndef()
{
    vector<TunerStationTypes::TunerStationTypes::NameIndexUndef> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToNameIndexUndef.cbegin(); it != nameToNameIndexUndef.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::NameIndexUndef)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter NameIndexUndef");
    printf("Selected value: %d, meaning %s\n", result,
        nameIndexUndefToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::IdIndexDab
MyTerminalIO::enterIdIndexDab()
{
    vector<TunerStationTypes::TunerStationTypes::IdIndexDab> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToIdIndexDab.cbegin(); it != nameToIdIndexDab.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::IdIndexDab)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter IdIndexDab");
    printf("Selected value: %d, meaning %s\n", result,
        idIndexDabToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::IdIndexAmFm
MyTerminalIO::enterIdIndexAmFm()
{
    vector<TunerStationTypes::TunerStationTypes::IdIndexAmFm> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToIdIndexAmFm.cbegin(); it != nameToIdIndexAmFm.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::IdIndexAmFm)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter IdIndexAmFm");
    printf("Selected value: %d, meaning %s\n", result,
        idIndexAmFmToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerStationTypes::TunerStationTypes::IdIndexUndef
MyTerminalIO::enterIdIndexUndef()
{
    vector<TunerStationTypes::TunerStationTypes::IdIndexUndef> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToIdIndexUndef.cbegin(); it != nameToIdIndexUndef.cend(); ++it, i++) {
        x.push_back((TunerStationTypes::TunerStationTypes::IdIndexUndef)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter IdIndexUndef");
    printf("Selected value: %d, meaning %s\n", result,
        idIndexUndefToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerTypes::TunerTypes::Activation
MyTerminalIO::enterActivation()
{
    vector<TunerTypes::TunerTypes::Activation> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToActivation.cbegin(); it != nameToActivation.cend(); ++it, i++) {
        x.push_back((TunerTypes::TunerTypes::Activation)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter Activation");
    printf("Selected value: %d, meaning %s\n", result,
        ActivationToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

uint32_t
MyTerminalIO::enterHandle()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter handle");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterFrequencyFM()
{
    uint32_t result;
    result = readNumber(87500, 108000, "Enter AM/FM frequency (khz)");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterPi()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter PI");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterFrequencyDAB()
{
    uint32_t result;
    result = readNumber(172000, 230000, "Enter DAB frequency (khz)");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterUniqueKey()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Unique Key");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterParent()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Parent");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterService()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Service");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterEnsemble()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Ensemble");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterComponent()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Component");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint8_t
MyTerminalIO::enterGenre()
{
    uint8_t result;
    result = (uint8_t)readNumber(0, 255, "Enter Genre");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

TunerTypes::TunerTypes::UInt32s
MyTerminalIO::enterFlags()
{
    TunerTypes::TunerTypes::UInt32s result;
    result.clear();
    result.resize(1);
    result[0] = readNumber(0, UINT_MAX, "Enter Flag 0");
    return result;
}

bool
MyTerminalIO::enterPermanent()
{
    return readBoolean("Enter Permanent");
}

TunerStationTypes::TunerStationTypes::StationSelector
MyTerminalIO::enterStationSelector(
    TunerStationTypes::TunerStationTypes::SelectionMode selectionMode,
    const TunerStationTypes::TunerStationTypes::StationList& stationsAMFM,
    const TunerStationTypes::TunerStationTypes::StationList& stationsDAB,
    const TunerStationTypes::TunerStationTypes::StationList& stationsUndef
)
{
    TunerStationTypes::TunerStationTypes::StationSelector x;
    TunerStationTypes::TunerStationTypes::DeviceType deviceType;

    deviceType = enterDeviceType();
    x.deviceType = (uint32_t)deviceType;
    switch(deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
            // sanity cleanup
            x.id.resize(2, 0);
            if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_DIRECT) {
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_PARENT] = enterParent();
            } else if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_LIST) {
                if (stationsUndef.stations.size() == 0) {
                    throw invalid_argument("Undef station list is empty.");
                }
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] = enterFromStationList(stationsUndef);
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_PARENT] = enterParent();
            } else {
                // anything else is unsupported
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_PARENT] = enterParent();
            }
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            // sanity cleanup
            x.id.resize(4, 0);
            if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_DIRECT) {
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = enterFrequencyFM();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = 0;
            } else if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_LIST) {
                if (stationsAMFM.stations.size() == 0) {
                    throw invalid_argument("AMFM station list is empty.");
                }
                //x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] = enterFromStationList(stationsAMFM);
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = 0;
            } else {
                // unknown
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = enterFrequencyFM();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI] = enterPi();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = enterService();
            }
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            // sanity cleanup
            x.id.resize(5, 0);
            if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_DIRECT) {
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY] = enterFrequencyDAB();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_COMPONENT] = 0;
            } else if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_LIST) {
                if (stationsDAB.stations.size() == 0) {
                    throw invalid_argument("DAB station list is empty.");
                }
                //x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] = enterFromStationList(stationsDAB);
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE] = 0;
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_COMPONENT] = 0;
            } else {
                // unknown
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY] = enterFrequencyDAB();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = enterEnsemble();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE] = enterService();
                x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_COMPONENT] = enterComponent();
            }
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::SDARS:
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::TV:
            break;
        default:
            // error
            fprintf(stderr, "Illegal device Type %d", (uint32_t)x.deviceType);
            exit(1);
    }

    return x;
}

TunerStationTypes::TunerStationTypes::StationSelector
MyTerminalIO::enterStationSelector()
{
    TunerStationTypes::TunerStationTypes::StationSelector x;
    TunerStationTypes::TunerStationTypes::DeviceType deviceType;

    deviceType = enterDeviceType();
    x.deviceType = (uint32_t)deviceType;
    switch(deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
            // sanity cleanup
            x.id.resize(2, 0);
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] = enterUniqueKey();
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_PARENT] = enterParent();
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            // sanity cleanup
            x.id.resize(4, 0);
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] = enterUniqueKey();
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = enterFrequencyFM();
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI] = enterPi();
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = enterService();
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            // sanity cleanup
            x.id.resize(5, 0);
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] = enterUniqueKey();
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY] = enterFrequencyDAB();
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = enterEnsemble();
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE] = enterService();
            x.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_COMPONENT] = enterComponent();
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::SDARS:
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::TV:
            break;
        default:
            // error
            fprintf(stderr, "Illegal device Type %d", (uint32_t)x.deviceType);
            exit(1);
    }

    return x;
}




// no return here, just use by reference parameters
void
MyTerminalIO::enterStartTuneParameters(
    TunerStationTypes::TunerStationTypes::StationSelector &station,
    TunerStationTypes::TunerStationTypes::SelectionMode &selectionMode,
    const TunerStationTypes::TunerStationTypes::StationList& stationsAMFM,
    const TunerStationTypes::TunerStationTypes::StationList& stationsDAB,
    const TunerStationTypes::TunerStationTypes::StationList& stationsUndef,
    uint32_t &handle
)
{
    printf("\nEntering StartTuneParameters:\n");
    selectionMode = enterSelectionMode();
    station = enterStationSelector(selectionMode, stationsAMFM, stationsDAB, stationsUndef);
    //handle = enterHandle();
}

// no return here, just use by reference parameters
void
MyTerminalIO::enterAbortTuneParameters(
    TunerStationTypes::TunerStationTypes::DeviceType &deviceType,
    uint32_t &handle
)
{
    printf("\nEntering AbortTuneParameters:\n");
    deviceType = enterDeviceType();
    //handle = enterHandle();
}

// no return here, just use by reference parameters
void
MyTerminalIO::enterSeekParameters(
    TunerStationTypes::TunerStationTypes::DeviceType &deviceType,
    TunerStationTypes::TunerStationTypes::SeekMode &seekMode,
    uint8_t &genre,
    TunerTypes::TunerTypes::UInt32s &flags,
    uint32_t &handle
)
{
    printf("\nEntering SeekParameters:\n");
    deviceType = enterDeviceType();
    seekMode = enterSeekMode();
    genre = enterGenre();
    flags = enterFlags();
    //handle = enterHandle();
}

// no return here, just use by reference parameters
void
MyTerminalIO::enterMakePermanentParameters(
    TunerStationTypes::TunerStationTypes::StationSelector &stationSelector,
    bool &permanent,
    const TunerStationTypes::TunerStationTypes::StationList& stationsAMFM,
    const TunerStationTypes::TunerStationTypes::StationList& stationsDAB,
    const TunerStationTypes::TunerStationTypes::StationList& stationsUndef,
    uint32_t &handle
)
{
    TunerStationTypes::TunerStationTypes::SelectionMode selectionMode =
        TunerStationTypes::TunerStationTypes::SelectionMode::SM_LIST;
    printf("\nEntering MakePermanentParameters:\n");
    //selectionMode = enterSelectionMode();
    stationSelector = enterStationSelector(selectionMode, stationsAMFM, stationsDAB, stationsUndef);
    //stationSelector = enterStationSelector();
    permanent = enterPermanent();
    //handle = enterHandle();
}

// no return here, just use by reference parameters
void
MyTerminalIO::enterControlUpdateParameters(
    TunerStationTypes::TunerStationTypes::UpdateElement &updateElement,
    TunerStationTypes::TunerStationTypes::UpdateType &updateType,
    uint32_t &sourceType,
    uint32_t &stationType,
    uint32_t &handle
)
{
    printf("\nEntering ControlUpdateParameters:\n");
    updateElement = enterUpdateElement();
    updateType = enterUpdateType();
    sourceType = (uint32_t)enterSourceType();
    stationType = (uint32_t)enterStationType();
    //handle = enterHandle();
}

TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType
MyTerminalIO::enterAnnouncementType()
{
    vector<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToAnnouncementType.cbegin(); it != nameToAnnouncementType.cend(); ++it, i++) {
        x.push_back((TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter AnnouncementType");
    printf("Selected value: %d, meaning %s\n", result,
        AnnouncementTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType
MyTerminalIO::enterComponentType()
{
    vector<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToComponentType.cbegin(); it != nameToComponentType.cend(); ++it, i++) {
        x.push_back((TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter Componenttype");
    printf("Selected value: %d, meaning %s\n", result,
        ComponentTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

uint32_t
MyTerminalIO::enterComponentID()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Component ID");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t
MyTerminalIO::enterComponentIDFromList(vector<uint32_t>& list)
{
    vector<uint32_t> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = list.cbegin(); it != list.cend(); ++it, i++) {
        x.push_back(*it);
        printf("%2d %d\n", i, *it);
    }
    result = readNumber(0, x.size()-1, "Enter ComponentID");
    printf("Selected value: %d, meaning %d\n", result, x[result]);
    return(x[result]);
}

bool
MyTerminalIO::enterComponentParameter()
{
    return readBoolean("Enter ComponentParameter.announcement.abort");
}


TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions
MyTerminalIO::enterComponentTypeOptions()
{
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions options;
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions dummy;
    bool r;

    dummy.active = enterActivation();
    if (dummy.active == TunerTypes::TunerTypes::Activation::ACTIVE) {
        uint32_t n = readNumber(0, 11, "How many announcementtypes", "");
        set<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> annTypesSeen;
        dummy.typeConfiguration.resize(n);

        for (int i = 0; i < n; i++) {
            int done = 0;
            do {
                printf("Entry %d\n", i);
                dummy.typeConfiguration[i].type = enterAnnouncementType();
                try {
                    annTypesSeen.insert(dummy.typeConfiguration[i].type);
                    done++;
                } catch (exception e) {
                    printf("Sorry, this announcement type is already included.\n");
                }
		
	        dummy.typeConfiguration[i].active = enterActivation();
	
                dummy.typeConfiguration[i].priority = readNumber(0, 15, "Enter priority", "");
            } while(!done);
        }
    } else {
        dummy.typeConfiguration.resize(0);
    }

    options = dummy;
    return options;
}

string
MyTerminalIO::getStationType(TunerStationTypes::TunerStationTypes::StationType x)
{
    string out;

    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_AUTOSTORED) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_AUTOSTORED);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_ENSEMBLE) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_ENSEMBLE);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_SERVICE) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_SERVICE);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PRIMARY) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PRIMARY);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_SECONDARY) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_SECONDARY);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED);
        out += " ";
    }

    // special case for ST_UNDEF which is 0, where & does not work
    if (x == TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF) {
        out += stationTypeToName.at((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF);
    }

    return out;
}

string
MyTerminalIO::getSeekMode(TunerStationTypes::TunerStationTypes::SeekMode x)
{
    try {
        return seekModeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getSeekReturnValue(TunerStationTypes::TunerStationTypes::SeekReturnValue x)
{
    try {
        return seekReturnValueToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getSelectionMode(TunerStationTypes::TunerStationTypes::SelectionMode x)
{
    try {
        return selectionModeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getUpdateElement(TunerStationTypes::TunerStationTypes::UpdateElement x)
{
    try {
        return updateElementToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getSourceType(TunerStationTypes::TunerStationTypes::SourceType x)
{
    try {
        return sourceTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getDeviceType(TunerStationTypes::TunerStationTypes::DeviceType x)
{
    try {
        return deviceTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getFeedback(TunerTypes::TunerTypes::Feedback x)
{
    try {
        return feedbackToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getUpdateType(TunerStationTypes::TunerStationTypes::UpdateType x)
{
    try {
        return updateTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getFlagsDefUndef(TunerStationTypes::TunerStationTypes::FlagsDefUndef x)
{
    try {
        return flagsDefUndefToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getFlagsDefAmFm(TunerStationTypes::TunerStationTypes::FlagsDefAmFm x)
{
    try {
        return flagsDefAmFmToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getFlagsDefDab(TunerStationTypes::TunerStationTypes::FlagsDefDab x)
{
    try {
        return flagsDefDabToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getQualityIndexUndef(TunerStationTypes::TunerStationTypes::QualityIndexUndef x)
{
    try {
        return qualityIndexUndefToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getQualityIndexAmFm(TunerStationTypes::TunerStationTypes::QualityIndexAmFm x)
{
    try {
        return qualityIndexAmFmToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getQualityIndexDab(TunerStationTypes::TunerStationTypes::QualityIndexDab x)
{
    try {
        return qualityIndexDabToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getNameIndexDab(TunerStationTypes::TunerStationTypes::NameIndexDab x)
{
    try {
        return nameIndexDabToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getNameIndexAmFm(TunerStationTypes::TunerStationTypes::NameIndexAmFm x)
{
    try {
        return nameIndexAmFmToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getNameIndexUndef(TunerStationTypes::TunerStationTypes::NameIndexUndef x)
{
    try {
        return nameIndexUndefToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getIdIndexUndef(TunerStationTypes::TunerStationTypes::IdIndexUndef x)
{
    try {
        return idIndexUndefToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getIdIndexAmFm(TunerStationTypes::TunerStationTypes::IdIndexAmFm x)
{
    try {
        return idIndexAmFmToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getIdIndexDab(TunerStationTypes::TunerStationTypes::IdIndexDab x)
{
    try {
        return idIndexDabToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getPermanent(bool x)
{
    return (x == true) ? "TRUE" : "FALSE";
}

string
MyTerminalIO::getFrequency(bool x)
{
    return (x == true) ? "TRUE" : "FALSE";
}

string
MyTerminalIO::getGenre(uint8_t x)
{
    char buffer[24];

    sprintf(buffer, "%d", x);
    string result(buffer);

    return result;
}

string
MyTerminalIO::getFlags(uint32_t x)
{
    char buffer[24];

    sprintf(buffer, "%u", x);
    string result(buffer);

    return result;
}

string
MyTerminalIO::getCallStatus(CommonAPI::CallStatus x)
{
    try {
        return callStatusToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}


string
MyTerminalIO::getAnnouncementType(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType x)
{
    try {
        return AnnouncementTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getComponentType(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType x)
{
    try {
        return ComponentTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string
MyTerminalIO::getActivation(TunerTypes::TunerTypes::Activation x)
{
    try {
        return ActivationToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

// setter
//

TunerStationTypes::TunerStationTypes::StationType
MyTerminalIO::setStationType(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::StationType)nameToStationType.at(x);
    }
    catch (int e) {
        throw invalid_argument("StationType value out or range");
    }
}

TunerStationTypes::TunerStationTypes::SeekMode
MyTerminalIO::setSeekMode(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::SeekMode)nameToSeekMode.at(x);
    }
    catch (int e) {
        throw invalid_argument("SeekMode value out or range");
    }
}

TunerStationTypes::TunerStationTypes::SelectionMode
MyTerminalIO::setSelectionMode(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::SelectionMode)nameToSelectionMode.at(x);
    }
    catch (int e) {
        throw invalid_argument("SelectionMode value out or range");
    }
}

TunerStationTypes::TunerStationTypes::UpdateElement
MyTerminalIO::setUpdateElement(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::UpdateElement)nameToUpdateElement.at(x);
    }
    catch (int e) {
        throw invalid_argument("UpdateElement value out or range");
    }
}

TunerStationTypes::TunerStationTypes::SourceType
MyTerminalIO::setSourceType(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::SourceType)nameToSourceType.at(x);
    }
    catch (int e) {
        throw invalid_argument("SourceType value out or range");
    }
}

TunerStationTypes::TunerStationTypes::DeviceType
MyTerminalIO::setDeviceType(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::DeviceType)nameToDeviceType.at(x);
    }
    catch (int e) {
        throw invalid_argument("DeviceType value out or range");
    }
}

TunerTypes::TunerTypes::Feedback
MyTerminalIO::setFeedback(string x)
{
    try {
        return (TunerTypes::TunerTypes::Feedback)nameToFeedback.at(x);
    }
    catch (int e) {
        throw invalid_argument("Feedback value out or range");
    }
}

TunerStationTypes::TunerStationTypes::UpdateType
MyTerminalIO::setUpdateType(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::UpdateType)nameToUpdateType.at(x);
    }
    catch (int e) {
        throw invalid_argument("UpdateType value out or range");
    }
}

TunerStationTypes::TunerStationTypes::FlagsDefUndef
MyTerminalIO::setFlagsDefUndef(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::FlagsDefUndef)nameToFlagsDefUndef.at(x);
    }
    catch (int e) {
        throw invalid_argument("FlagsDefUndef value out or range");
    }
}

TunerStationTypes::TunerStationTypes::FlagsDefAmFm
MyTerminalIO::setFlagsDefAmFm(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::FlagsDefAmFm)nameToFlagsDefAmFm.at(x);
    }
    catch (int e) {
        throw invalid_argument("FlagsDefAmFm value out or range");
    }
}

TunerStationTypes::TunerStationTypes::FlagsDefDab
MyTerminalIO::setFlagsDefDab(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::FlagsDefDab)nameToFlagsDefDab.at(x);
    }
    catch (int e) {
        throw invalid_argument("FlagsDefDab value out or range");
    }
}

TunerStationTypes::TunerStationTypes::QualityIndexUndef
MyTerminalIO::setQualityIndexUndef(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::QualityIndexUndef)nameToQualityIndexUndef.at(x);
    }
    catch (int e) {
        throw invalid_argument("QualityIndexUndef value out or range");
    }
}

TunerStationTypes::TunerStationTypes::QualityIndexAmFm
MyTerminalIO::setQualityIndexAmFm(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::QualityIndexAmFm)nameToQualityIndexAmFm.at(x);
    }
    catch (int e) {
        throw invalid_argument("QualityIndexAmFm value out or range");
    }
}

TunerStationTypes::TunerStationTypes::QualityIndexDab
MyTerminalIO::setQualityIndexDab(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::QualityIndexDab)nameToQualityIndexDab.at(x);
    }
    catch (int e) {
        throw invalid_argument("QualityIndexDab value out or range");
    }
}

TunerStationTypes::TunerStationTypes::NameIndexDab
MyTerminalIO::setNameIndexDab(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::NameIndexDab)nameToNameIndexDab.at(x);
    }
    catch (int e) {
        throw invalid_argument("NameIndexDab value out or range");
    }
}

TunerStationTypes::TunerStationTypes::NameIndexAmFm
MyTerminalIO::setNameIndexAmFm(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::NameIndexAmFm)nameToNameIndexAmFm.at(x);
    }
    catch (int e) {
        throw invalid_argument("NameIndexAmFm value out or range");
    }
}

TunerStationTypes::TunerStationTypes::NameIndexUndef
MyTerminalIO::setNameIndexUndef(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::NameIndexUndef)nameToNameIndexUndef.at(x);
    }
    catch (int e) {
        throw invalid_argument("NameIndexUndef value out or range");
    }
}

TunerStationTypes::TunerStationTypes::IdIndexUndef
MyTerminalIO::setIdIndexUndef(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::IdIndexUndef)nameToIdIndexUndef.at(x);
    }
    catch (int e) {
        throw invalid_argument("IdIndexUndef value out or range");
    }
}

TunerStationTypes::TunerStationTypes::IdIndexAmFm
MyTerminalIO::setIdIndexAmFm(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::IdIndexAmFm)nameToIdIndexAmFm.at(x);
    }
    catch (int e) {
        throw invalid_argument("IdIndexAmFm value out or range");
    }
}

TunerStationTypes::TunerStationTypes::IdIndexDab
MyTerminalIO::setIdIndexDab(string x)
{
    try {
        return (TunerStationTypes::TunerStationTypes::IdIndexDab)nameToIdIndexDab.at(x);
    }
    catch (int e) {
        throw invalid_argument("IdIndexDab value out or range");
    }
}

bool
MyTerminalIO::setPermanent(string x)
{
    if (x == "TRUE") {
        return true;
    } else if (x == "FALSE") {
        return false;
    } else {
        throw invalid_argument("setPermanent value out or range");
    }
}

bool
MyTerminalIO::setFrequency(string x)
{
    if (x == "TRUE") {
        return true;
    } else if (x == "FALSE") {
        return false;
    } else {
        throw invalid_argument("setFrequency value out or range");
    }
}

uint32_t
MyTerminalIO::setGenre(string x)
{
    uint32_t result;

    try {
        result = stoul (x, nullptr, 0);
        return result;
    } catch (int e) {
        throw invalid_argument("setGenre value out or range");
    }
}

uint32_t
MyTerminalIO::setFlags(string x)
{
    uint32_t result;

    try {
        result = stoul (x, nullptr, 0);
        return result;
    } catch (int e) {
        throw invalid_argument("setFlags value out or range");
    }
}

CommonAPI::CallStatus
MyTerminalIO::setCallStatus(string x)
{
    try {
        return (CommonAPI::CallStatus)nameToCallStatus.at(x);
    }
    catch (int e) {
        throw invalid_argument("CallStatus value out or range");
    }
}

void
MyTerminalIO::printStation(const TunerStationTypes::TunerStationTypes::Station& myStation)
{
    MyTerminalIO *tio = new MyTerminalIO();

    // debug
    printf("StationSelector:\n");
    printf("DeviceType: %s\n", tio->getDeviceType((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType).c_str());
    printf("Id:\n");
    switch((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
            printf("\tUNDEF_ID_KEY: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY]);
            if (myStation.sel.id.size() < 2) {
                printf("\tUNDEF_ID_PARENT: - not provided -\n");
            } else {
                printf("\tUNDEF_ID_PARENT: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_PARENT]);
            }
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            printf("\tAMFM_ID_KEY: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY]);
            printf("\tAMFM_ID_FREQUENCY: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
            printf("\tAMFM_ID_PI: %u, 0x%08x\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI], myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI]);
            printf("\tAMFM_ID_SERVICE %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_SERVICE]);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            printf("\tDAB_ID_KEY: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY]);
            printf("\tDAB_ID_FREQUENCY: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY]);
            printf("\tDAB_ID_ENSEMBLE: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_ENSEMBLE]);
            printf("\tDAB_ID_SERVICE: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE]);
            printf("\tDAB_ID_COMPONENT: %u\n", myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_COMPONENT]);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::SDARS:
            fprintf(stderr, "SDARS not handled - sorry\n");
            exit(1);
        case TunerStationTypes::TunerStationTypes::DeviceType::TV:
            fprintf(stderr, "TV not handled - sorry\n");
            exit(1);
        default:
            // error
            fprintf(stderr, "Illegal device Type %d", (uint32_t)myStation.sel.deviceType);
            exit(1);
    }

    printf("StationType: %s\n", tio->getStationType((TunerStationTypes::TunerStationTypes::StationType)myStation.stationType).c_str());

    printf("Name:\n");
    switch((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
            printf("\tUNDEF_NAM_LONG: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_LONG].c_str());
            printf("\tUNDEF_NAM_SHORT: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_SHORT].c_str());
            printf("\tUNDEF_NAM_DYNAMIC: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_DYNAMIC].c_str());
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            printf("\tAMFM_NAM_PS: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_PS].c_str());
            printf("\tAMFM_NAM_HD: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_HD].c_str());
            printf("\tAMFM_NAM_RT: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_RT].c_str());
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            printf("\tDAB_NAM_CLONG: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_CLONG].c_str());
            printf("\tDAB_NAM_CSHORT: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_CSHORT].c_str());
            printf("\tDAB_NAM_DYNAMIC: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_DYNAMIC].c_str());
            printf("\tDAB_NAM_SLONG: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SLONG].c_str());
            printf("\tDAB_NAM_SSHORT: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SSHORT].c_str());
            printf("\tDAB_NAM_ELONG: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_ELONG].c_str());
            printf("\tDAB_NAM_ESHORT: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_ESHORT].c_str());
            printf("\tDAB_NAM_FREQUENCY: %s\n", myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_FREQUENCY].c_str());
            break;
        // need no default since this has been checked before
    }

    // there are currently no specific enums for meta stuff, so we just output
    // the complete vector here
    printf("Meta:\n");
    int k = 0;
    for (auto meta = myStation.meta.cbegin(); meta != myStation.meta.cend(); ++meta, k++) {
        printf("\tMeta[%d].type: %u\n", k, (*meta).type);
        printf("\tMeta[%d].name: %s\n", k, (*meta).str.c_str());
    }

    printf("Genre:\n");
    switch((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
            printf("\tUNDEF_GEN_STATIC: %u\n", myStation.genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexUndef::UNDEF_GEN_STATIC]);
            printf("\tUNDEF_GEN_DYNAMIC: %u\n", myStation.genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexUndef::UNDEF_GEN_DYNAMIC]);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            printf("\tAMFM_GEN_PTY: %u\n", myStation.genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexAmFm::AMFM_GEN_PTY]);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            printf("\tDAB_GEN_STATIC_PTY: %u\n", myStation.genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexDab::DAB_GEN_STATIC_PTY]);
            printf("\tDAB_GEN_DYNAMIC_PTY: %u\n", myStation.genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexDab::DAB_GEN_DYNAMIC_PTY]);
            break;
        // need no default since this has been checked before
    }

    k = 0;
    for (auto flag = myStation.flags.cbegin(); flag != myStation.flags.cend(); ++flag, k++) {
        printf("Flags[%d]: %u\n", k, (*flag));
    }

    printf("Quality:\n");
    switch((TunerStationTypes::TunerStationTypes::DeviceType)myStation.sel.deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
            printf("\tUNDEF_QAL_AUDIO: %u\n", myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexUndef::UNDEF_QAL_AUDIO]);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            printf("\tAMFM_QAL_FIELDSTRENGTH: %u\n", myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_FIELDSTRENGTH]);
            printf("\tAMFM_QAL_MULTIPATH: %u\n", myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_MULTIPATH]);
            printf("\tAMFM_QAL_DIGITAL: %u\n", myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_DIGITAL]);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            printf("\tDAB_QAL_BER: %u\n", myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_BER]);
            printf("\tDAB_QAL_SERVICE: %u\n", myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_SERVICE]);
            printf("\tDAB_QAL_AUDIO: %u\n", myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_AUDIO]);
            break;
        // need no default since this has been checked before
    }
}

void
MyTerminalIO::printStationSelector(const TunerStationTypes::TunerStationTypes::StationSelector& station)
{
    // print id's here depending on value
    switch((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
            printf("UNDEF_ID_KEY: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY]);
            if (station.id.size() < 2) {
                printf("UNDEF_ID_PARENT: - not provided -\n");
            } else {
                printf("UNDEF_ID_PARENT: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_PARENT]);
            }
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            printf("AMFM_ID_KEY: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY]);
            printf("AMFM_ID_FREQUENCY: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
            printf("AMFM_ID_PI: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI]);
            printf("AMFM_ID_SERVICE %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_SERVICE]);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            printf("DAB_ID_KEY: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY]);
            printf("DAB_ID_FREQUENCY: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY]);
            printf("DAB_ID_ENSEMBLE: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY]);
            printf("DAB_ID_SERVICE: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY]);
            printf("DAB_ID_COMPONENT: %u\n", station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY]);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::SDARS:
            fprintf(stderr, "TV currently not handled - sorry\n");
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::TV:
            fprintf(stderr, "TV currently not handled - sorry\n");
            break;
        default:
            // error
            fprintf(stderr, "Illegal device Type %d", (uint32_t)station.deviceType);
            exit(1);
    }
}

string
MyTerminalIO::getStationTypeShort(uint32_t x)
{
    string result;

    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE) {
        result += "R";
    } else {
        result += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_PERMANENT) {
        result += "P";
    } else {
        result += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_AUTOSTORED) {
        result += "A";
    } else {
        result += " ";
    }
    if ((uint32_t)x & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED) {
        result += "C";
    } else {
        result += " ";
    }
    return result;
}


void
MyTerminalIO::printStationListShort(const TunerStationTypes::TunerStationTypes::StationList& list)
{
    int i = 0;

    for (auto it = list.stations.cbegin(); it != list.stations.cend(); it++, i++) {
        switch((TunerStationTypes::TunerStationTypes::DeviceType)(*it).sel.deviceType) {
            case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
                printf("%3d %s\n", i,
                    (*it).name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::UNDEF_NAM_LONG].c_str());
                break;
            case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
                printf("%3d [%s] %6d khz %s\n", i,
                    getStationTypeShort((*it).stationType).c_str(),
                    (*it).sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY],
                    (*it).name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_HD].c_str());
                break;
            case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
                printf("%3d [%s] %6d khz %s\n", i,
                    getStationTypeShort((*it).stationType).c_str(),
                    (*it).sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY],
                    (*it).name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SLONG].c_str());
                break;
            default:
                break;
        }
    }
}

void
MyTerminalIO::printComponentTypeOptions(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions)
{
    if (!componentTypeOptions.isType<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>()) {
        printf("componenTypeOptions not of type Announcement_TypeOptions\n");
        printf("not implemented\n");
        return;
    }

    printf("componentTypeOptions.announcement_configuration.active: %s\n", getActivation(componentTypeOptions.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().active).c_str());

    int k = 0;
    for (auto it = componentTypeOptions.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().typeConfiguration.cbegin();
        it != componentTypeOptions.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().typeConfiguration.cend(); it++, k++) {
        //printf("componentTypeOptions.announcement_configuration.typeConfiguration[%d].active: %s\n", k, ((*it).active == true) ? "TRUE" : "FALSE");
//	printf("componentTypeOptions.announcement_configuration.typeConfiguration[%d].active: %s\n", k, getActivation((*it).active));        
	printf("componentTypeOptions.announcement_configuration.typeConfiguration[%d].priority: %u\n", k, (*it).priority);
        printf("componentTypeOptions.announcement_configuration.typeConfiguration[%d].type: %s\n", k, getAnnouncementType((*it).type).c_str());
    }
}

int
MyTerminalIO::enterFromStationList(const TunerStationTypes::TunerStationTypes::StationList& list)
{
    int ret;
    int index;
    int sz;

    printStationListShort(list);

    // count elements
    sz = 0;
    for (auto it = list.stations.cbegin(); it != list.stations.cend(); it++, sz++);
    index = readNumber(0, sz-1, "Enter station number");

    // check entry and return correct id
    switch((TunerStationTypes::TunerStationTypes::DeviceType)list.stations[index].sel.deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
            ret = list.stations[index].sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY];
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            ret = list.stations[index].sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY];
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            ret = list.stations[index].sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY];
            break;
        default:
            // error
            break;
    }

    return ret;
}
