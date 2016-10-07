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
 * myProvider -
 *
 * this module represents the simulated Tuner Middleware (TunerMW).
 *
 * It accepts calls from clients (the simulated HMIs). Each Franca method of
 * an interface is represented by its own function of the same name. Each
 * Franca interface is represented by its own class, which is a stub that
 * inherits from auto-generated class code in src-gen directory structure.
 * This auto-generated class already contains virtual declarations of the
 * required methods.
 *
 * From the instance context, so called 'fire...' methods can be executed
 * which represent the Franca broadcasts of the same interface.
 *
 * In this simulation, where it is not applicable to return a broadcast
 * immediately, the 'this' instance pointer is stored within an instance
 * of the class job, which represents an asynchronous job to be executed
 * later (in several steps, if required). The jobs are enqueued and
 * managed by the JobQueue class.
 *
 * Each method will also return a standard 'handle_out' and 'feedback' as
 * defined in Franca interface specifications, that is returned immediately
 * as opposed to the broadcasts done asynchronously at a later time. If
 * there is an error in parameters or the system cannot execute the request
 * due to missing prerequisites, the feedback contains NOT APPLICABLE or
 * FAILURE, otherwise if the job could be executed or at least queue, it
 * will contain DONE.
 *
 * The main function, after setting up server handling, will go into an
 * endless loop where it periodically checks the job queue for asynchronous
 * activities to perform next.
 *
 * On receiption of a SIGTERM or SIGINT the program will gracefully exit.
 */

#include <memory>
#include <iostream>
#include <unistd.h>

#include <TunerStation/TunerStationStubDefault.h>
#include <TunerAdditionalService/TunerAdditionalServiceStubDefault.h>

#include <CommonAPI/Runtime.h>
#include <signal.h>
#include "MyTerminalIO.h"
#include "MyJobList.h"
#include "myProvider.h"
#include "MyFileIO.h"

JobQueue *jobQueue = NULL;
HMIList *hmiList = NULL;
TunerList *tunerList = NULL;

TunerStationIndividualStub::TunerStationIndividualStub()
{
}

TunerStationIndividualStub::~TunerStationIndividualStub()
{
}

void
TunerStationIndividualStub::startTune(
    TunerStationTypes::TunerStationTypes::StationSelector station,
    TunerStationTypes::TunerStationTypes::SelectionMode selectionMode,
    uint32_t handle,
    uint32_t& handle_out,
    TunerTypes::TunerTypes::Feedback& feedback
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to startTune( )\n";

    // debug output
    tio->printStationSelector(station);
    printf("SelectionMode: %s\n", tio->getSelectionMode(selectionMode).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);

    // can only handle SM_DIRECT and SM_LIST
    if (selectionMode != TunerStationTypes::TunerStationTypes::SelectionMode::SM_DIRECT &&
        selectionMode != TunerStationTypes::TunerStationTypes::SelectionMode::SM_LIST) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("Only selectionModes SM_DIRECT and SM_LIST are supported.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // can only handle AMFM, DAB or UNDEF_DEVICE at the moment
    if (((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType != TunerStationTypes::TunerStationTypes::DeviceType::AMFM) &&
        ((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType != TunerStationTypes::TunerStationTypes::DeviceType::DAB) &&
        ((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType != TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE)
    ) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("Only deviceType AMFM, DAB and UNDEF_DEVICE are supported.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // UNDEF_DEVICE is only allowed with SM_LIST
    if ((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType ==
        TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE &&
        selectionMode != TunerStationTypes::TunerStationTypes::SelectionMode::SM_LIST) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("DeviceType UNDEF_DEVICE can only be combined with selectionMode SM_LIST.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // ignore values for PIcode, Service etc. for FM

    // Prepare regular result
    handle_out = handle;
    feedback = TunerTypes::TunerTypes::Feedback::DONE;

    // start after five seconds
    struct timeval tv;
    gettimeofday(&tv, NULL);
    tv.tv_sec += 5;

    int hmi_number = ((handle & 0xff000000) >> 24);
    HMI *hmi = hmiList->getHMIbyNumber(hmi_number);
    if (hmi == NULL) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // unclear for deviceType UNDEF!
    TunerStationTypes::TunerStationTypes::DeviceType tunerDeviceType = (TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType;

    if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_LIST) {
        uint32_t key;
        MyFileIO *fio = MyFileIO::getInstance();
        TunerStationTypes::TunerStationTypes::Station x_station;
        TunerStationTypes::TunerStationTypes::Station *y_station;

        switch((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType) {
            case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
                tunerDeviceType = TunerStationTypes::TunerStationTypes::DeviceType::AMFM;
                break;
            case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
                tunerDeviceType = TunerStationTypes::TunerStationTypes::DeviceType::DAB;
                break;
            case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
                key = station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY];
                // the key is the PI code or Service id
                // try DAB first
                y_station = fio->getReceivableDABStationByServiceId(key);
                if (y_station == NULL) {
                    y_station = fio->getReceivableAMFMStationByPICode(key);
                    if (y_station == NULL) {
                        // error
                        handle_out = handle;
                        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
                        printf("Could not find station with PIcode / Service ID %d\n", key);
                        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                        fflush(stdout);
                        return;
                    } else {
                        tunerDeviceType = TunerStationTypes::TunerStationTypes::DeviceType::AMFM;
                    }
                } else {
                    tunerDeviceType = TunerStationTypes::TunerStationTypes::DeviceType::DAB;
                }
                break;
            default:
                // illegal, already checked earlier
                break;
        }
    }

    Tuner *tuner = tunerList->allocTuner(hmi, tunerDeviceType);

    if (tuner->getState() != TunerState::IDLE) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("Sorry, tuner is not in state IDLE. If tuned, you must call abortTune first.\n");
        printf("Otherwise you will have to wait until current action is finished.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    Job *job = new Job(
        JobType::TUNE_TO,
        tuner,
        hmi,
        tv,
        this,
        station,
        selectionMode,
        handle
    );
    jobQueue->queueJob(job);

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    fflush(stdout);
}

void
TunerStationIndividualStub::abortTune(
    TunerStationTypes::TunerStationTypes::DeviceType device,
    uint32_t handle,
    uint32_t& handle_out,
    TunerTypes::TunerTypes::Feedback& feedback
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to abortTune( )\n";
    printf("DeviceType: %s\n", tio->getDeviceType((TunerStationTypes::TunerStationTypes::DeviceType)device).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);

    // can only handle AMFM at the moment
    if (device != TunerStationTypes::TunerStationTypes::DeviceType::AMFM &&
        device != TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // start after five seconds
    struct timeval tv;
    gettimeofday(&tv, NULL);
    tv.tv_sec += 5;

    int hmi_number = ((handle & 0xff000000) >> 24);
    HMI *hmi = hmiList->getHMIbyNumber(hmi_number);
    if (hmi == NULL) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }
    Tuner *tuner = tunerList->allocTuner(hmi, (TunerStationTypes::TunerStationTypes::DeviceType)device);

    if (tuner->getState() != TunerState::TUNED) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // Prepare regular result
    handle_out = handle;
    feedback = TunerTypes::TunerTypes::Feedback::DONE;

    Job *job = new Job(
        JobType::ABORT_TUNE,
        tuner,
        hmi,
        tv,
        this,
        device,
        handle
    );
    jobQueue->queueJob(job);

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    fflush(stdout);
}

void
TunerStationIndividualStub::seek(
    TunerStationTypes::TunerStationTypes::DeviceType device,
    TunerStationTypes::TunerStationTypes::SeekMode seekMode,
    uint8_t genre,
    TunerTypes::TunerTypes::UInt32s flags,
    uint32_t handle,
    uint32_t& handle_out,
    TunerTypes::TunerTypes::Feedback& feedback
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to seek( )\n";
    printf("DeviceType: %s\n", tio->getDeviceType((TunerStationTypes::TunerStationTypes::DeviceType)device).c_str());
    printf("SeekMode: %s\n", tio->getSeekMode((TunerStationTypes::TunerStationTypes::SeekMode)seekMode).c_str());
    printf("Genre: %u\n", genre);
    //printf("Flags: %u\n", flags);
    printf("Handle: %u, 0x%08x\n", handle, handle);

    // can only handle AMFM and DAB at the moment
    if (device != TunerStationTypes::TunerStationTypes::DeviceType::AMFM &&
       (device != TunerStationTypes::TunerStationTypes::DeviceType::DAB)) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // Prepare regular result
    handle_out = handle;
    feedback = TunerTypes::TunerTypes::Feedback::DONE;
    //
    // start after five seconds
    struct timeval tv;
    gettimeofday(&tv, NULL);
    tv.tv_sec += 5;

    int hmi_number = ((handle & 0xff000000) >> 24);
    HMI *hmi = hmiList->getHMIbyNumber(hmi_number);
    if (hmi == NULL) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // can it be deviceType UNDEF here?
    // in this case we would need two jobs, one for AMFM and one for DAB tuner!
    Tuner *tuner = tunerList->allocTuner(hmi, device);


    JobType jobType;

    switch(seekMode) {
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_OFF:
            jobType = JobType::CANCEL;
            break;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_MAN_UP:
            jobType = JobType::MANUAL_UP;
            break;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_MAN_DOWN:
            jobType = JobType::MANUAL_DOWN;
            break;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_AUTO_UP:
            jobType = JobType::AUTO_UP;
            break;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_AUTO_DOWN:
            jobType = JobType::AUTO_DOWN;
            break;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_SCAN_UP:
            // not yet implemented
            // Prepare regular result
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_SCAN_DOWN:
            // not yet implemented
            // Prepare regular result
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_SCAN_SKIP_UP:
            // not yet implemented
            // Prepare regular result
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_SCAN_SKIP_DOWN:
            // not yet implemented
            // Prepare regular result
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        case TunerStationTypes::TunerStationTypes::SeekMode::SM_AUTOSTORE:
            // check tuner state
            if (tuner->getState() != TunerState::IDLE) {
                handle_out = handle;
                feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
                printf("Sorry, tunerstate is not IDLE. If you are tuned, use aborttune first.\n");
                printf("Otherwise you will have to wait until current operation is completed.\n");
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                fflush(stdout);
                return;
            }

            jobType = JobType::AUTOSTORE;
            break;
    }

    Job *job = new Job(
        jobType,
        tuner,
        hmi,
        tv,
        this,
        device,
        seekMode,
        genre,
        flags,
        handle
    );
    jobQueue->queueJob(job);

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    fflush(stdout);
    return;
}

void
TunerStationIndividualStub::makePermanent(
    TunerStationTypes::TunerStationTypes::StationSelector station,
    bool permanent,
    uint32_t handle,
    uint32_t& handle_out,
    TunerTypes::TunerTypes::Feedback& feedback
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    MyFileIO *fio = MyFileIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to makePermanent( )\n";

    tio->printStationSelector(station);
    printf("Permanent: %s\n", tio->getPermanent(permanent).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);

    // can only handle AMFM or DAB at the moment
    if (((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType != TunerStationTypes::TunerStationTypes::DeviceType::AMFM) &&
        ((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType != TunerStationTypes::TunerStationTypes::DeviceType::DAB)
    ) {
        cout << "Device type is neither AMFM nor DAB" << station.deviceType << endl;
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    int index;

    switch ((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType ) {
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            index = station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY];
            fio->setPermanentFlagAMFM(index, permanent);
            break;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            index = station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY];
            fio->setPermanentFlagDAB(index, permanent);
            break;
        default:
            // cannot happen; see above
            break;
    }

    // debug
    fio->dumpStations();

    // Prepare result
    handle_out = handle;
    feedback = TunerTypes::TunerTypes::Feedback::DONE;
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    fflush(stdout);
}

void
TunerStationIndividualStub::controlUpdate(
    TunerStationTypes::TunerStationTypes::UpdateElement updateElement,
    TunerStationTypes::TunerStationTypes::UpdateType updateType,
    uint32_t sourceType,
    uint32_t stationType,
    uint32_t handle,
    uint32_t& handle_out,
    TunerTypes::TunerTypes::Feedback& feedback
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to controlUpdate( )\n";

    printf("UpdateElement: %s\n", tio->getUpdateElement(updateElement).c_str());
    printf("UpdateType: %s\n", tio->getUpdateType(updateType).c_str());
    printf("SourceType: %s\n", tio->getSourceType((TunerStationTypes::TunerStationTypes::SourceType)sourceType).c_str());
    printf("StationType: %s\n", tio->getStationType((TunerStationTypes::TunerStationTypes::StationType)stationType).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);

    // Prepare regular result
    handle_out = handle;
    feedback = TunerTypes::TunerTypes::Feedback::DONE;

    int hmi_number = ((handle & 0xff000000) >> 24);
    HMI *hmi = hmiList->getHMIbyNumber(hmi_number);
    if (hmi == NULL) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }
    // fake for now
    JobType jobType;

    if (updateElement == TunerStationTypes::TunerStationTypes::UpdateElement::UE_SEEK) {
        if ((sourceType != (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::AMFM_FM) &&
            (sourceType != (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::DAB_DAB)) {
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            cout << "Sorry, only calls with sourceType AMFM or DAB allowed!" << endl;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        }

        if (stationType != (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF) {
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            cout << "Sorry, only calls with stationType ST_UNDEF allowed!" << endl;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        }

        switch(updateType) {
            case TunerStationTypes::TunerStationTypes::UpdateType::UT_NOTIFICATION:
                if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::AMFM_FM)) {
                    hmi->setUpdateSeekNotificationAMFM(true);
                } else if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::DAB_DAB)) {
                    hmi->setUpdateSeekNotificationDAB(true);
                }
                break;
            case TunerStationTypes::TunerStationTypes::UpdateType::UT_NONE:
                if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::AMFM_FM)) {
                    hmi->setUpdateSeekNotificationAMFM(false);
                } else if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::DAB_DAB)) {
                    hmi->setUpdateSeekNotificationDAB(false);
                }

                break;
            case TunerStationTypes::TunerStationTypes::UpdateType::UT_ONCE:
                // fallthrough
            default:
                feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
                cout << "Sorry, only calls with updateType UT_NONE or UT_NOTIFICATION allowed!" << endl;
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                fflush(stdout);
                return;
        }
    } else if (updateElement ==
        TunerStationTypes::TunerStationTypes::UpdateElement::UE_CURRENT_STATION) {

        if (updateType != TunerStationTypes::TunerStationTypes::UpdateType::UT_ONCE) {
            // current station request makes only sense with UT_ONCE
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            cout << "Sorry, only calls with updateType == UT_ONCE allowed!" << endl;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        }

        // any tuner assigned?
        set <Tuner *> myTuner;
        int found = 0;

        myTuner = tunerList->getTunersForHMI(hmi);
        if (myTuner.size() == 0) {
            // no tuner assigned, so no station
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            cout << "Sorry, no tuner assigned yet!" << endl;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        }

        // start after five seconds
        struct timeval tv;
        gettimeofday(&tv, NULL);
        tv.tv_sec += 5;

        for (auto it = myTuner.cbegin(); it != myTuner.cend(); it++) {
            if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::AMFM_FM &&
                (*it)->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) ||
                (sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::DAB_DAB &&
                (*it)->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::DAB)) {
                Job *job = new Job(
                    JobType::CURRENT_STATION,
                    *it,
                    hmi,
                    tv,
                    this,
                    updateElement,
                    updateType,
                    sourceType,
                    stationType,
                    handle
                );
                jobQueue->queueJob(job);
                found++;
            }
        }
        if (!found) {
            // no tuner for this sourceType found
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            cout << "Sorry, no tuner found that fits to sourceType!" << endl;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        }
    } else if (updateElement ==
        TunerStationTypes::TunerStationTypes::UpdateElement::UE_STATION_LIST) {
        TunerStationTypes::TunerStationTypes::StationList broadcast_list;
        MyFileIO *fio = MyFileIO::getInstance();

        if (updateType == TunerStationTypes::TunerStationTypes::UpdateType::UT_ONCE) {

            if (sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::UNDEF_SOURCE) {
                hmi->setCompleteListUndef(fio->getCompleteUndefStationList());

                broadcast_list.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE;
                broadcast_list.stationType = (int32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF;

                // stations array
                switch((TunerStationTypes::TunerStationTypes::StationType)stationType) {
                    case TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF:
                        broadcast_list.stations = hmi->getCompleteListUndef();
                        break;
                    default:
                        handle_out = handle;
                        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
                        cout << "Sorry, this stationType is not supported for UNDEF_DEVICE!" << endl;
                        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                        fflush(stdout);
                        return;
                }
            } else if (sourceType & (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::AMFM_FM) {
                broadcast_list.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::AMFM;
                broadcast_list.stationType = stationType;

                // stations array
                if ((TunerStationTypes::TunerStationTypes::StationType)stationType ==
                    TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF) {
                    // full selection
                    hmi->setCompleteListAMFM(fio->getCompleteAMFMStationList());
                    broadcast_list.stations = hmi->getCompleteListAMFM();
                } else {
                    broadcast_list.stations = fio->getFilteredAMFMStations((uint32_t)stationType);
                }
            } else if (sourceType & (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::DAB_DAB) {
                broadcast_list.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::DAB;
                broadcast_list.stationType = stationType;

                // stations array
                if ((TunerStationTypes::TunerStationTypes::StationType)stationType ==
                    TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF) {
                    // full selection
                    hmi->setCompleteListDAB(fio->getCompleteDABStationList());
                    broadcast_list.stations = hmi->getCompleteListDAB();
                } else {
                    broadcast_list.stations = fio->getFilteredDABStations((uint32_t)stationType);
                }
            } else {
                // other stuff not yet implemented
                handle_out = handle;
                feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
                cout << "Sorry, no support for this SourceType implemented yet!" << endl;
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                fflush(stdout);
                return;
            }

            uint32_t broadcast_handle = handle;

            fireStationListEvent(broadcast_list, broadcast_handle);
        } else if (updateType == TunerStationTypes::TunerStationTypes::UpdateType::UT_NOTIFICATION) {
            if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::AMFM_FM)) {
                hmi->setUpdateStationListNotificationAMFM(true);
            } else if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::DAB_DAB)) {
                hmi->setUpdateStationListNotificationDAB(true);
            } else {
                handle_out = handle;
                feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
                cout << "Sorry, no support for this SourceType implemented yet!" << endl;
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                fflush(stdout);
                return;
            }
        } else if (updateType == TunerStationTypes::TunerStationTypes::UpdateType::UT_NONE) {
            if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::AMFM_FM)) {
                hmi->setUpdateStationListNotificationAMFM(false);
            } else if ((sourceType == (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::DAB_DAB)) {
                hmi->setUpdateStationListNotificationDAB(false);
            } else {
                handle_out = handle;
                feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
                cout << "Sorry, no support for this SourceType implemented yet!" << endl;
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                fflush(stdout);
                return;
            }
        } else {
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
            cout << "Sorry, no support for this UpdateType implemented yet!" << endl;
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        }
    }
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    fflush(stdout);
}

// end of station management
//
// begin of additional services

TunerAdditionalServiceIndividualStub::TunerAdditionalServiceIndividualStub()
{
}

TunerAdditionalServiceIndividualStub::~TunerAdditionalServiceIndividualStub()
{
}


void
TunerAdditionalServiceIndividualStub::changeComponentTypeConfiguration(
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType compType,
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions options,
    uint32_t handle,
    uint32_t& handle_out,
    TunerTypes::TunerTypes::Feedback& feedback)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions componentTypeOptions;

    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to changeComponentTypeConfiguration()\n";
    printf("compType: %s\n", tio->getComponentType(compType).c_str());

    // anything but announcements is unsupported
    if (compType != TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType::CT_ANNOUNCEMENT) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        cout << "Sorry, only support for CT_ANNOUNCEMENT implemented!" << endl;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    tio->printComponentTypeOptions(options);

    // store it

    int hmi_number = ((handle & 0xff000000) >> 24);
    HMI *hmi = hmiList->getHMIbyNumber(hmi_number);
    if (hmi == NULL) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
        printf("HMI not found.\n");
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    //TunerTypes::TunerTypes::Activation state =
    //    options.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementConfiguration>().activity;

    TunerTypes::TunerTypes::Activation state =
        options.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().active;

    // the following also clears all detailed announcement handling, if set to false
    hmi->setAnnouncementHandling(state);

    if (state == TunerTypes::TunerTypes::Activation::INACTIVE) {
        if (options.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().typeConfiguration.size() > 0) {
            handle_out = handle;
            feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
            printf("When general activate flag is false, list should be empty.\n");
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            fflush(stdout);
            return;
        }
    } else {
        for (int i = 0; i < options.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().typeConfiguration.size(); i++) {
            hmi->setAnnouncementConfiguration(
                options.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().typeConfiguration[i].type,
                options.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().typeConfiguration[i].active,
                options.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions>().typeConfiguration[i].priority
            );
        }
    }

    printf("Handle: %u, 0x%08x\n", handle, handle);
    handle_out = handle;

    // setup broadcast; currently this sent directly without delay
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions dummy;
    dummy = hmi->getAnnouncementConfiguration();
    componentTypeOptions = dummy;
    tio->printComponentTypeOptions(componentTypeOptions);
    fireComponentTypeConfigurationEvent(compType, componentTypeOptions, handle_out);

    feedback = TunerTypes::TunerTypes::Feedback::DONE;
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    fflush(stdout);
}

void
TunerAdditionalServiceIndividualStub::requestComponentOptions(
    uint32_t componentID,
    uint32_t handle,
    TunerTypes::TunerTypes::Feedback& feedback,
    uint32_t& handle_out
)
{
    // dummy
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions componentOptions;

    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to requestComponentOptions()\n";
    printf("ComponentID: %u\n", componentID);
    printf("Handle: %u, 0x%08x\n", handle, handle);

    handle_out = handle;
    // componentOptions cannot be initialized, since the struct has no members
    //fireComponentOptionsEvent(componentID, componentOptions, handle_out);

    feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    fflush(stdout);
}

void
TunerAdditionalServiceIndividualStub::requestComponentTypeConfiguration(
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType componentType,
    uint32_t handle,
    uint32_t& handle_out,
    TunerTypes::TunerTypes::Feedback& feedback
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions componentTypeOptions;

    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to requestComponentTypeConfiguration()\n";
    printf("CompType: %s\n", tio->getComponentType(componentType).c_str());
    printf("Handle: %u, 0x%08x\n", handle, handle);

    handle_out = handle;

    // handle only CT_ANNOUNCEMENT
    if (componentType != TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType::CT_ANNOUNCEMENT) {
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    int hmi_number = ((handle & 0xff000000) >> 24);
    HMI *hmi = hmiList->getHMIbyNumber(hmi_number);
    if (hmi == NULL) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    // setup broadcast; currently this sent directly without delay
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions dummy;
    dummy = hmi->getAnnouncementConfiguration();
    componentTypeOptions = dummy;
    tio->printComponentTypeOptions(componentTypeOptions);
    fireComponentTypeConfigurationEvent(componentType, componentTypeOptions, handle_out);

    feedback = TunerTypes::TunerTypes::Feedback::DONE;
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    fflush(stdout);
}

void
TunerAdditionalServiceIndividualStub::selectComponent(
    uint32_t componentID,
    uint32_t handle,
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter component_parameter,
    uint32_t& handle_out,
    TunerTypes::TunerTypes::Feedback& feedback
)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    std::cout << "Received call to selectComponent()\n";
    printf("ComponentID: %u\n", componentID);
    printf("Handle: %u, 0x%08x\n", handle, handle);
    printf("ComponentParameter.getValueType: %d\n", component_parameter.getValueType());

    int hmi_number = ((handle & 0xff000000) >> 24);
    HMI *hmi = hmiList->getHMIbyNumber(hmi_number);
    if (hmi == NULL) {
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
        return;
    }

    if (component_parameter.isType<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_Parameter>()) {
        // Announcement_Parameter
        printf("announcement.abort: %s\n", (component_parameter.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_Parameter>().abort == true) ? "TRUE" : "FALSE");
        handle_out = handle;

        // if user wishes to abort announcement, try it
        if (component_parameter.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_Parameter>().abort == true) {
            if (hmi->deleteActiveAnnouncement(componentID) == false) {
                // there is no such active announcement
                feedback = TunerTypes::TunerTypes::Feedback::FAILURE;
            } else {
                feedback = TunerTypes::TunerTypes::Feedback::DONE;
            }
        } else {
            // abort was false, it is unclear what this case is good for
            feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        }
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
    } else if (component_parameter.isType<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::EPG_Parameter>()) {
        // EPG_Parameter
        printf("announcement.epg.startDate: %s\n", component_parameter.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::EPG_Parameter>().startDate.c_str());
        printf("announcement.epg.endDate: %s\n", component_parameter.get<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::EPG_Parameter>().endDate.c_str());
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
    } else {
        printf("subtype parameter not yet implemented.\n");
        handle_out = handle;
        feedback = TunerTypes::TunerTypes::Feedback::NOT_APPLICABLE;
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fflush(stdout);
    }
}

void
printActiveAnnouncements()
{
    map<uint32_t,
        TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> x;
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    set<HMI *> myHMIList;

    myHMIList = hmiList->getHMIList();
    for (auto it2 = myHMIList.cbegin(); it2 != myHMIList.cend(); it2++) {
        HMI *hmi = (*it2);
        x = hmi->getActiveAnnouncements();
        if (x.size() == 0) {
            printf("HMI %d: currently no active announcements.\n", hmi->getHMIId());
        } else {
            printf("HMI %d:\n", hmi->getHMIId());
            for (auto it = x.cbegin(); it != x.cend(); it++) {
                printf("ComponentID %d, type %s\n", (*it).first, tio->getAnnouncementType((*it).second).c_str());
            }
        }
    }
}


TunerStationTypes::TunerStationTypes::StationList
getTunedStations()
{
    TunerStationTypes::TunerStationTypes::StationList resultingStations;
    set<uint32_t> codes;
    MyFileIO *fio = MyFileIO::getInstance();
    set<HMI *> myHMIList;

    resultingStations.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE;
    resultingStations.stationType = (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_RECEIVABLE;

    // for all HMIs
    myHMIList = hmiList->getHMIList();
    for (auto it2 = myHMIList.cbegin(); it2 != myHMIList.cend(); it2++) {
        HMI *hmi = (*it2);

        // get tuners assigned to this HMI
        set<Tuner *> myTuner;
        myTuner = tunerList->getTunersForHMI(hmi);
        if (myTuner.size() == 0) {
            // empty list
            continue;
        }

        // for each tuner, check it is in state TUNED and get PICode or ServiceID 
        // for tuned station
        for (auto it = myTuner.cbegin(); it != myTuner.cend(); it++) {
            TunerStationTypes::TunerStationTypes::Station *x;

            if ((*it)->getState() != TunerState::TUNED) {
                continue;
            }
            if ((*it)->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                // get the frequency and from frequency determine the station
                x = fio->getReceivableAMFMStationByFrequency((*it)->getFrequency());
                if (x != NULL) {
                    codes.insert(x->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI]);
                }
            } else if ((*it)->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                x = fio->getReceivableDABStationByFrequency((*it)->getFrequency());
                if (x != NULL) {
                    codes.insert(x->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE]);
                }
            }
        }
    }

    // here we should have a set of PIcode or ServiceIDs
    // now get the stations
    TunerStationTypes::TunerStationTypes::Station *x;

    for (auto it = codes.cbegin(); it != codes.cend(); it++) {
        x = fio->getReceivableUndefStationById((*it));
        if (x) {
            resultingStations.stations.push_back(*x);
            continue;
        }
    }

    return resultingStations;
}


void
sendAnnouncement(std::shared_ptr<TunerAdditionalServiceIndividualStub> stub)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement announcement;
    uint32_t handle;
    MyFileIO *fio = MyFileIO::getInstance();
    uint32_t code;
    TunerStationTypes::TunerStationTypes::StationList tunedStations;
    set<HMI *> myHMIList;

    cout << "\nSending announcement ..." << endl;

    tunedStations = getTunedStations();
    if (tunedStations.stations.size() == 0) {
        // no stations
        cout << "Sorry, no stations tuned, hence no announcements can be send." << endl;
        return;
    }
    printf("Select originating station for announcement:\n");
    code = tio->enterFromStationList(tunedStations);
    printf("PIcode/ServiceID %d 0x%08x\n", code, code);
    announcement.componentID = fio->assignComponentID(code);
    printf("ComponentID %d\n", announcement.componentID, announcement.componentID);

    // announcement.componentID = tio->enterComponentID();
    announcement.type = tio->enterAnnouncementType();

    // for all HMIs
    myHMIList = hmiList->getHMIList();
    for (auto it2 = myHMIList.cbegin(); it2 != myHMIList.cend(); it2++) {
        HMI *hmi = (*it2);

        if (hmi->getAnnouncementHandling() == TunerTypes::TunerTypes::Activation::ACTIVE) {
//            if (hmi->getAnnouncementConfigurationEnabled(announcement.type) == true) {
	    if (hmi->getAnnouncementConfigurationEnabled(announcement.type) == TunerTypes::TunerTypes::Activation::ACTIVE) {
                handle = (((hmi->getHMIId() & 0xff) << 24) | 0);

                if (hmi->isActiveAnnouncement(announcement.componentID)) {
                    printf("HMI %d already has this kind of announcement\n", hmi->getHMIId());
                } else {
                    printf("HMI %d appears to be interested in this kind of announcement -> sending\n", hmi->getHMIId());
                    stub->fireAnnouncementEvent(announcement, handle);
                    hmi->addActiveAnnouncement(announcement.componentID, announcement.type);
                }
            } else {
                printf("HMI %d has disabled this kind of announcement.\n", hmi->getHMIId());
            }
        } else {
            printf("HMI %d is not interested in announcements at all.\n", hmi->getHMIId());
        }
    }
    cout << "Sending announcements done" << endl;
}

void
finishAllAnnouncementsForComponentID(std::shared_ptr<TunerAdditionalServiceIndividualStub> stub, uint32_t componentID)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement announcement;
    uint32_t handle;
    set<HMI *> myHMIList;
    
    // for all HMIs
    myHMIList = hmiList->getHMIList();
    for (auto it2 = myHMIList.cbegin(); it2 != myHMIList.cend(); it2++) {
        HMI *hmi = (*it2);

        if (hmi->getAnnouncementHandling() != TunerTypes::TunerTypes::Activation::ACTIVE) {
            printf("HMI %d is not interested in announcements at all.\n", hmi->getHMIId());
            continue;
        }

        map<uint32_t,
            TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> x;
        int found = 0;

        // assume that per componentID there is maximum one announcment at a time
        x = hmi->getActiveAnnouncements();
        for (auto it = x.cbegin(); it != x.cend(); it++) {
            printf("Checking ComponentID %d, type %s\n", (*it).first, tio->getAnnouncementType((*it).second).c_str());
            if ((*it).first == componentID) {
                announcement.componentID = componentID;
                announcement.type = (*it).second;
                found++;
                break;
            }
        }

        if (!found) {
            printf("HMI %d has no outstanding announcements for componentID %d at all.\n", hmi->getHMIId(), componentID);
            continue;
        }

        handle = (((hmi->getHMIId() & 0xff) << 24) | 0);
        printf("HMI %d appears to be interested in announcement type %d -> sending\n", hmi->getHMIId(), announcement.type);
        stub->fireAnnouncementFinishedEvent(announcement, handle);
        hmi->deleteActiveAnnouncement(announcement.componentID);
    }
    cout << "finishAllAnnouncement done" << endl;
}


void
sendAnnouncementFinished(std::shared_ptr<TunerAdditionalServiceIndividualStub> stub)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement announcement;
    uint32_t handle;
    MyFileIO *fio = MyFileIO::getInstance();
    uint32_t code;
    TunerStationTypes::TunerStationTypes::StationList tunedStations;
    set<HMI *> myHMIList;

    cout << "\nSending announcement finished ..." << endl;
    tunedStations = getTunedStations();
    if (tunedStations.stations.size() == 0) {
        // no stations
        cout << "Sorry, no stations tuned, hence no announcments can be send." << endl;
        return;
    }
    printf("Select originating station for ending of announcement:\n");
    code = tio->enterFromStationList(tunedStations);
    printf("PIcode/ServiceID %d 0x%08x\n", code, code);
    announcement.componentID = fio->assignComponentID(code);
    printf("ComponentID %d\n", announcement.componentID, announcement.componentID);

    //announcement.componentID = tio->enterComponentID();
    announcement.type = tio->enterAnnouncementType();

    // for all HMIs
    myHMIList = hmiList->getHMIList();
    for (auto it2 = myHMIList.cbegin(); it2 != myHMIList.cend(); it2++) {
        HMI *hmi = (*it2);

        if (hmi->getAnnouncementHandling() == TunerTypes::TunerTypes::Activation::ACTIVE) {
            //if (hmi->getAnnouncementConfigurationEnabled(announcement.type) == true) {
	    if (hmi->getAnnouncementConfigurationEnabled(announcement.type) == TunerTypes::TunerTypes::Activation::ACTIVE) {
                if (hmi->isActiveAnnouncement(announcement.componentID)) {
                    handle = (((hmi->getHMIId() & 0xff) << 24) | 0);
                    printf("HMI %d appears to be interested in this kind of announcement -> sending\n", hmi->getHMIId());
                    stub->fireAnnouncementFinishedEvent(announcement, handle);
                    hmi->deleteActiveAnnouncement(announcement.componentID);
                } else {
                    printf("HMI %d does currently not have this kind of announcement.\n", hmi->getHMIId());
                }
            } else {
                printf("HMI %d has disabled this kind of announcement.\n", hmi->getHMIId());
            }
        } else {
            printf("HMI %d is not interested in announcements at all.\n", hmi->getHMIId());
        }
    }
    cout << "Sending announcement finished done" << endl;
}


int sigterminate = 0;

void
sigTermHandler(int sig, siginfo_t *siginfo, void *x)
{
    sigterminate++;
    cout << "SIGTERM received." << endl;
}


void
interactive(std::shared_ptr<TunerAdditionalServiceIndividualStub> myTunerAdditionalServiceStub)
{
    MyTerminalIO *tio = MyTerminalIO::getInstance();

	while (!sigterminate) {
        unsigned int choice = 99;
        string menu = "\n============================================================================\n";
        menu += "Background interaction (the server keeps on running while in input dialog!):\n";
        menu += "============================================================================\n";
        menu += "0 exit program\n";
        menu += "1 send Announcement\n";
        menu += "2 send Announcement finished\n";
        menu += "3 print active announcements (no API!)\n";
        choice = tio->readNumber(0, 3, "Enter number", menu);

        switch(choice) {
            case 0:
                sigterminate++;
                break;
            case 1:
                sendAnnouncement(myTunerAdditionalServiceStub);
                break;
            case 2:
                sendAnnouncementFinished(myTunerAdditionalServiceStub);
                break;
            case 3:
                printActiveAnnouncements();
                break;
            default:
                fprintf(stderr, "Error, got unexpected choice %u\n", choice);
                break;
        }
    }
}

int
setupSignalHandling()
{
    struct sigaction sigact;

    memset(&sigact, 0, sizeof(sigact));
    sigact.sa_sigaction = sigTermHandler;
    sigemptyset (&sigact.sa_mask);
    sigact.sa_flags = SA_SIGINFO;

    sigaction(SIGTERM, &sigact, NULL);
    sigaction(SIGINT, &sigact, NULL);
}


int
main(void)
{
	std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::load();
	std::shared_ptr<CommonAPI::Factory> factory = runtime->createFactory();
    bool registerResult;

    printf("Welcome to Genivi Tuner API simulation (Tuner Middleware part)\n\n");

    /*
     * Setup job queue and stuff
     */
    jobQueue = new JobQueue;
    tunerList = new TunerList(3, 4);
    Job *current_job;
    struct timeval tv;

    auto myStub = std::make_shared<TunerStationIndividualStub>();
    registerResult = factory->registerService(myStub, "local:TunerStation.TunerStation:TunerStation.Instance1");
    if (registerResult != true) {
        cerr << "Registering of TunerStation stub failed." << endl;
        return 1;
    }
    cout << "Successfully registered TunerStation stub." << endl;

#if 0
    /*
     * the following second registration does not work
     * for an unknown reason. Without this registration we are not able to support the
     * interface for AdditionalService.
     */
    auto myTunerAdditionalServiceStub = std::make_shared<TunerAdditionalServiceIndividualStub>();
    registerResult = factory->registerService(myTunerAdditionalServiceStub, "local:TunerAdditionalService.TunerAdditionalService:TunerAdditionalService.Instance2");
    if (registerResult != true) {
        cerr << "Registering of TunerAdditionalService stub failed." << endl;
        return 1;
    }
    cout << "Successfully registered TunerAdditionalService stub." << endl;
#endif
#ifdef WITH_ADDITIONAL_SERVICES
	std::shared_ptr<CommonAPI::Factory> factory2 = runtime->createFactory();
    /*
     * the following second registration does not work
     * for an unknown reason. Without this registration we are not able to support the
     * interface for AdditionalService.
     */
    auto myTunerAdditionalServiceStub = std::make_shared<TunerAdditionalServiceIndividualStub>();
    registerResult = factory2->registerService(myTunerAdditionalServiceStub, "local:TunerAdditionalService.TunerAdditionalService:TunerAdditionalService.Instance2");
    if (registerResult != true) {
        cerr << "Registering of TunerAdditionalService stub failed." << endl;
        return 1;
    }
    cout << "Successfully registered TunerAdditionalService stub." << endl;
#endif

#ifdef WITH_ADDITIONAL_SERVICES
    hmiList = new HMIList(myStub, myTunerAdditionalServiceStub);
#else
    hmiList = new HMIList(myStub, NULL);
#endif

    // in future, the HMIs should be allocated once we initially get a request
    // from them. At the moment, we assume 2 HMIs.
    HMI *hmi1 = hmiList->createHMI(0);
    HMI *hmi2 = hmiList->createHMI(1);
    HMI *hmi3 = hmiList->createHMI(2);


    setupSignalHandling();

#ifdef WITH_ADDITIONAL_SERVICES
    std::thread t1(interactive, myTunerAdditionalServiceStub);
#endif

    while(!sigterminate) {
        bool continueJob;
        int currentJobId;

        if (jobQueue->isEmpty()) {
            usleep(1000);
            continue;
        }

        struct timeval next = jobQueue->getTimeOfNextJob();
        gettimeofday(&tv, NULL);

        if (next.tv_sec > tv.tv_sec ||
            (next.tv_sec == tv.tv_sec && next.tv_usec > tv.tv_usec)) {
            usleep(1000);
            continue;
        }

        // time expired, some work to do here
        if ((current_job = jobQueue->getNextJob()) == NULL) {
            // this might happen, in case job is suddenly cancelled
            continue;
        }
        continueJob = current_job->continueJob(jobQueue);
        currentJobId = current_job->getJobId();
        if (!continueJob) {
            delete current_job;
        }
    }
#ifdef WITH_ADDITIONAL_SERVICES
    t1.join();
#endif
    cout << "Exiting ..." << endl;
    factory->unregisterService("local:TunerStation.TunerStation:TunerStation.Instance1");
}
