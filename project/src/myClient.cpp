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
 * myClient -
 *
 * This module represents a simulated HMI client and can be invoked
 * multiple times in parallel with different id number starting from 0.
 * The maximum number of supported clients depends on the Tuner middleware.
 *
 * After setting up the environment it will present a menu to the user
 * to choose from the methods of the interface defined in Franca or to
 * exit the program gracefully.
 *
 * If an interface method has been chosen, its parameter are queried
 * from the user interactively by selecting possible values from a list.
 * It is thus not possible to enter values out of range for a parameter,
 * however it is still possible to enter combinations that make no sense
 * and will thus be refused by the Tuner middleware (myProvider).
 *
 * In some situations the selection of parameters will be aborted when
 * certain conditions are not met, e.g. user selects to choose from a
 * list of known stations, but this list is empty.
 *
 * The aforementioned station lists are the only data which is stored
 * as a kind of state info within the client. They must be retrieved
 * using controlUpdate in stationlist mode before startTune can use
 * them.
 *
 * Each method of the Franca interface is represented by its own function
 * of the same name, additionally for all broadcasts of the interface,
 * a callback function is registered with the underlying CommonAPI
 * framework on startup.
 *
 * All API parameters used for calling an interface, or those which
 * are received within an asynchonous broadcast or as result of an interface
 * call are printed on the console immediately before performing the call
 * or after reception, respectively.
 */

#include <memory>
#include <iostream>
#include <set>
#include <tuple>
#include <map>
#include <functional>
#include <unistd.h>

#include <TunerStation/TunerStationProxy.h>
#include <TunerAdditionalService/TunerAdditionalServiceProxy.h>
#include <CommonAPI/Runtime.h>
#include "MyTerminalIO.h"

int hmiId;
int currentJobId = 0;
TunerStationTypes::TunerStationTypes::StationList stationListAMFM;
TunerStationTypes::TunerStationTypes::StationList stationListDAB;
TunerStationTypes::TunerStationTypes::StationList stationListUndef;
// since Announcement has no operator < and no hash function, we cannot
// use it for a set or unordered_set. Hence we need to work with tuples of
// the elements.
//map<TunerTypes::TunerTypes::UInt32,
map<uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> activeAnnouncements;
uint32_t lastHandleForUndefSeek = 0;

void
mergeLists(const TunerStationTypes::TunerStationTypes::StationList& changes)
{
    TunerStationTypes::TunerStationTypes::StationList *currentList;
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    if ((TunerStationTypes::TunerStationTypes::DeviceType)changes.deviceType ==
        TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
        //printf("mergeLists: found AMFM list\n");
        currentList = &stationListAMFM;
    } else if ((TunerStationTypes::TunerStationTypes::DeviceType)changes.deviceType ==
        TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
        //printf("mergeLists: found DAB list\n");
        currentList = &stationListDAB;
    } else {
        //printf("mergeLists: found unknown list - ignoring it\n");
        // other lists are not handled
        return;
    }

    if (changes.stations.size() == 0) {
        //printf("mergeLists: list is empty - nothing to do\n");
        return;
    }
    if (!(changes.stations[0].stationType & (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED)) {
        //printf("mergeLists: this is not a list with changes - ignoring it\n");
        return;
    }

    for (auto it = changes.stations.cbegin(); it != changes.stations.cend(); it++) {
        TunerStationTypes::TunerStationTypes::Station station;
        station = (*it);
        station.stationType &= ~((uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_CHANGED);
        // check if key already exists
        int found = 0;
        for (auto it2 = currentList->stations.begin(); it2 != currentList->stations.end(); it2++) {
            if ((TunerStationTypes::TunerStationTypes::DeviceType)changes.deviceType ==
                TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                if (station.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] ==
                    (*it2).sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY]) {
                    found++;

                    // replace it
                    //printf("Replacing existing station:\n");
                    //tio->printStation(station);
                    (*it2) = station;
                    break;
                }
            } else if ((TunerStationTypes::TunerStationTypes::DeviceType)changes.deviceType ==
                TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                if (station.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] ==
                    (*it2).sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY]) {
                    found++;

                    // replace it
                    //printf("Replacing existing station:\n");
                    //tio->printStation(station);
                    (*it2) = station;
                    break;
                }
            }
        }
        if (!found) {
            //printf("Adding new station\n");
            //tio->printStation(station);
            currentList->stations.push_back(station);
        }
    }
}


void
startTune(std::shared_ptr<TunerStation::TunerStationProxy<> >& proxy)
{
    // in parameter
    TunerStationTypes::TunerStationTypes::StationSelector station;
    TunerStationTypes::TunerStationTypes::SelectionMode selectionMode;
    uint32_t handle;
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    //
    // out parameter
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
    uint32_t handle_out = 0;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;

    try {
        tio->enterStartTuneParameters(station, selectionMode, stationListAMFM, stationListDAB, stationListUndef, handle);
    } catch(exception &e) {
        printf("Sorry, selection from an empty station list is not possible.\n");
        printf("To fetch correct list, execute 'seek' for autostore scan, then\n");
        printf("retrieve the list using 'controlUpdate'.\n");
        fflush(stdout);
        return;
    }
    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerStation.startTune( ) ...\n";
    tio->printStationSelector(station);
    printf("SelectionMode: %s\n", tio->getSelectionMode(selectionMode).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->startTune(station, selectionMode, handle, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerStation.startTune( ) ...\n";
    printf("CallStatus %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback %s\n", tio->getFeedback(feedback).c_str());
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}


void
abortTune(std::shared_ptr<TunerStation::TunerStationProxy<> >& proxy)
{
    TunerStationTypes::TunerStationTypes::DeviceType device;
    uint32_t handle = 0;
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
    uint32_t handle_out = 0;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    device = tio->enterDeviceType();
    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerStation.abortTune( ) ...\n";
    printf("DeviceType: %s\n", tio->getDeviceType((TunerStationTypes::TunerStationTypes::DeviceType)device).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->abortTune(device, handle, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerStation.abortTune( ) ...\n";
    printf("CallStatus: %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback: %s\n", tio->getFeedback(feedback).c_str());
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}


void
seek(std::shared_ptr<TunerStation::TunerStationProxy<> >& proxy)
{
    TunerStationTypes::TunerStationTypes::DeviceType device =
        TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE;
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    TunerStationTypes::TunerStationTypes::SeekMode seekMode;
    uint8_t genre;
    TunerTypes::TunerTypes::UInt32s flags;
    uint32_t handle;
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
    uint32_t handle_out = 0;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;

    tio->enterSeekParameters(device, seekMode, genre, flags, handle);

    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));

    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerStation.seek( ) ...\n";
    printf("DeviceType: %s\n", tio->getDeviceType((TunerStationTypes::TunerStationTypes::DeviceType)device).c_str());
    printf("SeekMode: %s\n", tio->getSeekMode((TunerStationTypes::TunerStationTypes::SeekMode)seekMode).c_str());
    printf("Genre: %u\n", genre);
    //printf("Flags: %u\n", flags);
    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->seek(device, seekMode, genre, flags, handle, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerStation.seek( ) ...\n";
    printf("CallStatus: %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback: %s\n", tio->getFeedback(feedback).c_str());
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}

void
makePermanent(std::shared_ptr<TunerStation::TunerStationProxy<> >& proxy)
{
    TunerStationTypes::TunerStationTypes::StationSelector station;
    bool permanent;
    uint32_t handle;
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
    uint32_t handle_out = 0;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    try {
        tio->enterMakePermanentParameters(station, permanent, stationListAMFM, stationListDAB, stationListUndef, handle);
    } catch(exception &e) {
        printf("Sorry, selection from an empty station list is not possible.\n");
        printf("To fetch correct list, execute 'seek' for autostore scan, then\n");
        printf("retrieve the list using 'controlUpdate'.\n");
        fflush(stdout);
        return;
    }

    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerStation.makePermanent( ) ...\n";
    tio->printStationSelector(station);
    printf("Permanent: %s\n", tio->getPermanent(permanent).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->makePermanent(station, permanent, handle, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerStation.makePermanent( ) ...\n";
    printf("CallStatus: %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback: %s\n", tio->getFeedback(feedback).c_str());
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}

void
controlUpdate(std::shared_ptr<TunerStation::TunerStationProxy<> >& proxy)
{
    TunerStationTypes::TunerStationTypes::UpdateElement updateElement;
    TunerStationTypes::TunerStationTypes::UpdateType updateType =
        TunerStationTypes::TunerStationTypes::UpdateType::UT_NONE;
    uint32_t sourceType = 0;
    uint32_t stationType = 0;
    uint32_t handle = 0;
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
    uint32_t handle_out = 0;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    tio->enterControlUpdateParameters(updateElement, updateType, sourceType, stationType, handle);

    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));

    if (stationType == (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF) {
        lastHandleForUndefSeek = handle;
        printf("Storing SM_AUTOSTORE handle %d, 0x%08x\n", lastHandleForUndefSeek, lastHandleForUndefSeek);
    }

    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerStation.controlUpdate( ) ...\n";
    printf("UpdateElement: %s\n", tio->getUpdateElement(updateElement).c_str());
    printf("UpdateType: %s\n", tio->getUpdateType(updateType).c_str());
    printf("SourceType: %s\n", tio->getSourceType((TunerStationTypes::TunerStationTypes::SourceType)sourceType).c_str());
    printf("StationType: %s\n", tio->getStationType((TunerStationTypes::TunerStationTypes::StationType)stationType).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->controlUpdate(updateElement, updateType, sourceType, stationType, handle, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerStation.controlUpdate( ) ...\n";
    printf("CallStatus: %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback: %s\n", tio->getFeedback(feedback).c_str());
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}

CommonAPI::SubscriptionStatus seekCallback(TunerStationTypes::TunerStationTypes::SeekData seekData, uint32_t handle)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Received seekCallback( ) ...\n";
    printf("Handle: %u, 0x%08x\n", handle, handle);
    if (((handle & 0xff000000) >> 24) != hmiId) {
        printf("Ignored since it is not for us.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }
    printf("SeekMode: %s\n", tio->getSeekMode(seekData.mode).c_str());
    printf("ReturnValue: %s\n", tio->getSeekReturnValue(seekData.returnValue).c_str());
    printf("Data: %u\n", seekData.data);
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
    return CommonAPI::SubscriptionStatus::RETAIN;
}

CommonAPI::SubscriptionStatus currentStationCallback(TunerStationTypes::TunerStationTypes::Station current, uint32_t handle)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Received currentStationCallback( ) ...\n";
    printf("Handle: %u, 0x%08x\n", handle, handle);
    if (((handle & 0xff000000) >> 24) != hmiId) {
        printf("Ignored since it is not for us.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }

    tio->printStation(current);

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
    return CommonAPI::SubscriptionStatus::RETAIN;
}

CommonAPI::SubscriptionStatus stationListCallback(TunerStationTypes::TunerStationTypes::StationList list, uint32_t handle)
{
    int j = 0;
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Received stationListCallback( ) ...\n";
    printf("Handle: %u, 0x%08x\n", handle, handle);
    if (((handle & 0xff000000) >> 24) != hmiId) {
        printf("Ignored since it is not for us.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }

    // in StationList:
    // deviceType, stationType, stations
    printf("DeviceType: %s\n", tio->getDeviceType((TunerStationTypes::TunerStationTypes::DeviceType)list.deviceType).c_str());
    printf("StationType: %s\n", tio->getStationType((TunerStationTypes::TunerStationTypes::StationType)list.stationType).c_str());

    printf("--------------------------------------------------------------------------------\n");
    for (auto st = list.stations.cbegin(); st != list.stations.cend(); ++st, j++) {
        printf("Station %d:\n", j);
        tio->printStation(*st);
        printf("--------------------------------------------------------------------------------\n");
    }

    if ((TunerStationTypes::TunerStationTypes::DeviceType)list.deviceType ==
        TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE) {
        printf("No. Stationname\n");
    } else {
        printf("No. [RPAC] Frequency  Stationname\n");
    }
    tio->printStationListShort(list);
    printf("--------------------------------------------------------------------------------\n");

    //
    // store the list for later use
    // problem: we don't know whether this is an update list other than by handle
    //
    if (handle == lastHandleForUndefSeek) {
        cout << "Storing list" << endl;
        switch((TunerStationTypes::TunerStationTypes::DeviceType)list.deviceType) {
            case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
                stationListAMFM = list;
                break;
            case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
                stationListDAB = list;
                break;
            case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
                stationListUndef = list;
                break;
            default:
                // error
                break;
        }
    } else {
        // attempt to merge list, if it is not a list with changes, it will be ignored
        mergeLists(list);
    }

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
    return CommonAPI::SubscriptionStatus::RETAIN;
}

// end of station management
//
// begin of additional service

void
changeComponentTypeConfiguration(std::shared_ptr<TunerAdditionalService::TunerAdditionalServiceProxy<> >& proxy)
{
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType compType;
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions options;
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions options2;
//    TunerTypes::TunerTypes::UInt32 handle;
    uint32_t handle;
    // out parameter
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
//    TunerTypes::TunerTypes::UInt32 handle_out = 0;
    uint32_t handle_out = 0;;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    compType = tio->enterComponentType();
    options = tio->enterComponentTypeOptions();

    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));

    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerAdditionalServices.changeComponentTypeConfiguration( ) ...\n";
    printf("ComponentType: %s\n", tio->getComponentType(compType).c_str());

    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->changeComponentTypeConfiguration(compType, options, handle, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerAdditionalService.changeComponentTypeConfiguration( ) ...\n";
    printf("CallStatus %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback %s\n", tio->getFeedback(feedback).c_str());
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}

void
requestComponentOptions(std::shared_ptr<TunerAdditionalService::TunerAdditionalServiceProxy<> >& proxy)
{
//    TunerTypes::TunerTypes::UInt32 componentID;
//    TunerTypes::TunerTypes::UInt32 handle;
    uint32_t componentID;
    uint32_t handle;
    // out parameter
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
    //TunerTypes::TunerTypes::UInt32 handle_out = 0;
    uint32_t handle_out = 0;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    componentID = tio->enterComponentID();
    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerAdditionalServices.requestComponentOptions( ) ...\n";
    printf("Component ID: %u\n", componentID);
    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->requestComponentOptions(componentID, handle, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerAdditionalService.requestComponentOptions( ) ...\n";
    printf("CallStatus %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback %s\n", tio->getFeedback(feedback).c_str());
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}

void
requestComponentTypeConfiguration(std::shared_ptr<TunerAdditionalService::TunerAdditionalServiceProxy<> >& proxy)
{
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType componentType;
    //TunerTypes::TunerTypes::UInt32 handle;
    uint32_t handle;
    // out parameter
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
    uint32_t handle_out = 0;
//    TunerTypes::TunerTypes::UInt32 handle_out = 0;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
    MyTerminalIO *tio = MyTerminalIO::getInstance();

    componentType = tio->enterComponentType();
    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerAdditionalServices.requestComponentTypeConfiguration( ) ...\n";
    printf("ComponentType: %s\n", tio->getComponentType(componentType).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->requestComponentTypeConfiguration(componentType, handle, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerAdditionlService.requestComponentTypeConfiguration( ) ...\n";
    printf("CallStatus %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback %s\n", tio->getFeedback(feedback).c_str());
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}

void
selectComponent(std::shared_ptr<TunerAdditionalService::TunerAdditionalServiceProxy<> >& proxy)
{
    uint32_t componentID;
//TunerTypes::TunerTypes::UInt32 componentID;
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter componentParameter;
    uint32_t handle;
//TunerTypes::TunerTypes::UInt32 handle;
    // out parameter
    CommonAPI::CallStatus callStatus =
        CommonAPI::CallStatus::NOT_AVAILABLE;
    uint32_t handle_out = 0;
//    TunerTypes::TunerTypes::UInt32 handle_out = 0;
    TunerTypes::TunerTypes::Feedback feedback =
        TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    vector<uint32_t> list;

    for (auto it = activeAnnouncements.cbegin(); it != activeAnnouncements.cend(); it++) {
        list.push_back((*it).first);
    }
    if (list.size() == 0) {
        printf("There are currently no active announcements that could be cancelled.\n");
        return;
    }
    componentID = tio->enterComponentIDFromList(list);
    //componentID = tio->enterComponentID();

    // variant componentParameter; need dummy with exact one subtype of the variant
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_Parameter dummy;
    dummy.abort = tio->enterComponentParameter();
    componentParameter = dummy;
    printf("ComponentParameter.getValueType: %d\n", (int)componentParameter.getValueType());
    printf("ComponentParameter.isType Announcement_Parameter: %d\n", componentParameter.isType<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_Parameter>());
    printf("ComponentParameter.isType TeleText_Parameter: %d\n", componentParameter.isType<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::TeleText_Parameter>());

    handle = (((hmiId & 0xff) << 24) | (currentJobId++ & 0x00ffffff));
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Calling TunerAdditionalServices.selectComponent( ) ...\n";
    printf("Component ID: %d\n", componentID);
    printf("Handle: %u, 0x%08x\n", handle, handle);
    proxy->selectComponent(componentID, handle, componentParameter, callStatus, handle_out, feedback);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Returned from TunerAdditionlService.selectComponent( ) ...\n";
    printf("CallStatus %s\n", tio->getCallStatus(callStatus).c_str());
    printf("Handle_out: %u, 0x%08x\n", handle_out, handle_out);
    printf("Feedback %s\n", tio->getFeedback(feedback).c_str());

    if (feedback == TunerTypes::TunerTypes::Feedback::DONE) {
        if (componentParameter.isType<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_Parameter>()) {
            printf("Successfully cancelled announcement\n");

            try {
                activeAnnouncements.erase(componentID);
                printf("announcement componentID %d removed from list of active announcements.\n", componentID);
            } catch(exception& e) {
                printf("announcementFinished was attempted for unknown announcement componentID.\n");
            }
        }
    }

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
}


CommonAPI::SubscriptionStatus
announcementEventCallback(
    const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement,
    //const TunerTypes::TunerTypes::UInt32& handle
    const uint32_t handle
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Received announcementEventCallback( ) ...\n";
    printf("Handle: %u, 0x%08x\n", handle, handle);
    if (((handle & 0xff000000) >> 24) != hmiId) {
        printf("Ignored since it is not for us.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }

    printf("ComponentID: %d\n", announcement.componentID);
    printf("AnnouncementType: %s\n", tio->getAnnouncementType(announcement.type).c_str());

    try {
        activeAnnouncements[announcement.componentID] = announcement.type;
        printf("announcement with componentID %d added to list of active announcements.\n", announcement.componentID);
    } catch(exception& e) {
        printf("HMI has already received that kind of announcement earlier.\n");
    }

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
    return CommonAPI::SubscriptionStatus::RETAIN;
}

CommonAPI::SubscriptionStatus
announcementFinishedEventCallback(
    const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement,
    //const TunerTypes::TunerTypes::UInt32& handle
    const uint32_t &handle
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Received announcementFinishedEventCallback( ) ...\n";
    printf("Handle: %u, 0x%08x\n", handle, handle);
    if (((handle & 0xff000000) >> 24) != hmiId) {
        printf("Ignored since it is not for us.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }

    printf("ComponentID: %d\n", announcement.componentID);
    printf("AnnouncementType: %s\n", tio->getAnnouncementType(announcement.type).c_str());

    try {
        auto it = activeAnnouncements.find(announcement.componentID);
        if (it == activeAnnouncements.end()) {
            printf("announcementFinished was attempted for unknown announcement.\n");
        } else {
            activeAnnouncements.erase(announcement.componentID);
            printf("announcement removed from list of active announcements.\n");
        }
    } catch(exception& e) {
        printf("announcementFinished was attempted for unknown announcement.\n");
    }

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
    return CommonAPI::SubscriptionStatus::RETAIN;
}


CommonAPI::SubscriptionStatus
componentOptionsEventCallback(
//    const TunerTypes::TunerTypes::UInt32& componentID,
    const uint32_t& componentID,
    const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions& componentOptions,
//    const TunerTypes::TunerTypes::UInt32& handle
    const uint32_t& handle
)
{
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Received componentOptionsEventCallback( ) ...\n";
    printf("Handle: %u, 0x%08x\n", handle, handle);
    if (((handle & 0xff000000) >> 24) != hmiId) {
        printf("Ignored since it is not for us.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }

    printf("This functionality is not yet implemented.\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
    return CommonAPI::SubscriptionStatus::RETAIN;
}

CommonAPI::SubscriptionStatus
componentTypeConfigurationEventCallback(
    const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType,
    const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions,
//    const TunerTypes::TunerTypes::UInt32& handle
    const uint32_t& handle
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Received componentTypeConfigurationEventCallback( ) ...\n";
    printf("Handle: %u, 0x%08x\n", handle, handle);
    if (((handle & 0xff000000) >> 24) != hmiId) {
        printf("Ignored since it is not for us.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }

    if (componentType != TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType::CT_ANNOUNCEMENT) {
        printf("This functionality is not yet implemented.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }

    // CT_Announcement
    tio->printComponentTypeOptions(componentTypeOptions);

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
    return CommonAPI::SubscriptionStatus::RETAIN;
}


CommonAPI::SubscriptionStatus
getDataEventCallback(
//    const TunerTypes::TunerTypes::UInt32& componentID,
    const uint32_t& componentID,
    const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& selectParameter,
//    const TunerTypes::TunerTypes::UInt32& data,
//    const TunerTypes::TunerTypes::UInt32& handle
    const uint32_t& data,
    const uint32_t& handle

)
{
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	std::cout << "Received getDataEventCallback( ) ...\n";
    printf("Handle: %u, 0x%08x\n", handle, handle);
    if (((handle & 0xff000000) >> 24) != hmiId) {
        printf("Ignored since it is not for us.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        fflush(stdout);
        return CommonAPI::SubscriptionStatus::RETAIN;
    }

    printf("This functionality is not yet implemented.\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    fflush(stdout);
    return CommonAPI::SubscriptionStatus::RETAIN;
}

void
printActiveAnnouncements()
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    if (activeAnnouncements.size() == 0) {
        printf("\nThere are currently no active announcements.\n");
        return;
    }

    printf("\n");
    for (auto it = activeAnnouncements.cbegin(); it != activeAnnouncements.cend(); it++) {
        printf("ComponentID %d, type %s\n", (*it).first, tio->getAnnouncementType((*it).second).c_str());
    }
}

int
main(int argc, char **argv)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
	std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::load();
	std::shared_ptr<CommonAPI::Factory> factory = runtime->createFactory();
    // format from example code: "local:packagename.interfacename:packagename.Instance1"
	auto proxy =
        factory->buildProxy<TunerStation::TunerStationProxy>("local:TunerStation.TunerStation:TunerStation.Instance1");
	//auto broadcastProxy =
    //   factory->buildProxy<TunerStation::TunerStationBroadcastProxy>("local:TunerStation.TunerStationBroadcast:TunerStation.Instance1");

	proxy->getSeekEvent().subscribe(&seekCallback);
	proxy->getCurrentStationEvent().subscribe(&currentStationCallback);
	proxy->getStationListEvent().subscribe(&stationListCallback);

    // stuff for AdditionalService
	auto proxyAdditionalService =
        factory->buildProxy<TunerAdditionalService::TunerAdditionalServiceProxy>("local:TunerAdditionalService.TunerAdditionalService:TunerAdditionalService.Instance2");
	proxyAdditionalService->getAnnouncementEvent().subscribe(announcementEventCallback);
	proxyAdditionalService->getAnnouncementFinishedEvent().subscribe(announcementFinishedEventCallback);
	proxyAdditionalService->getComponentOptionsEvent().subscribe(componentOptionsEventCallback);
	proxyAdditionalService->getComponentTypeConfigurationEvent().subscribe(componentTypeConfigurationEventCallback);
	proxyAdditionalService->getGetDataEvent().subscribe(getDataEventCallback);

    if (argc < 2) {
        cerr << "Usage: myClient hmiId" << endl;
        cerr << "hmiId in range [0-3]" << endl;
        exit(1);
    }

    hmiId = atoi(argv[1]);

    cout << "Welcome to Genivi Tuner API simulation (HMI part)" << endl;
    cout << "Client HMI number is " << hmiId << endl;

	while (true) {
        unsigned int choice = 99;
        string menu = "\n0 exit\n1 startTune\n2 abortTune\n3 seek\n4 makePermanent\n5 controlUpdate\n";
#ifdef WITH_ADDITIONAL_SERVICES
        menu += "6 changeComponentTypeConfiguration\n";
        menu += "7 requestComponentOptions\n";
        menu += "8 requestComponentTypeConfiguration\n";
        menu += "9 selectComponent\n";
        menu += "10 printActiveAnnouncements (no API!)\n";
        choice = tio->readNumber(0, 10, "Enter number", menu);
#else
        choice = tio->readNumber(0, 5, "Enter number", menu);
#endif

        switch(choice) {
            case 0:
                printf("Exiting ...\n");
                exit(0);
            case 1:
                startTune(proxy);
                break;
            case 2:
                abortTune(proxy);
                break;
            case 3:
                seek(proxy);
                break;
            case 4:
                makePermanent(proxy);
                break;
            case 5:
                controlUpdate(proxy);
                break;
#ifdef WITH_ADDITIONAL_SERVICES
            case 6:
                changeComponentTypeConfiguration(proxyAdditionalService);
                break;
            case 7:
                requestComponentOptions(proxyAdditionalService);
                break;
            case 8:
                requestComponentTypeConfiguration(proxyAdditionalService);
                break;
            case 9:
                selectComponent(proxyAdditionalService);
                break;
            case 10:
                printActiveAnnouncements();
                break;
#endif
            default:
                fprintf(stderr, "Error, got unexpected choice %u\n", choice);
                exit(1);
        }
	}
}
