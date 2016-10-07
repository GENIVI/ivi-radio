/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERSTATION_MGEG_Tuner_Station_STUB_H_
#define MGEGTUNERSTATION_MGEG_Tuner_Station_STUB_H_

#include <cstdint>
#include <vector>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <MGEGTunerTypes/MGEGTunerTypes.h>
#include <MGEGTunerStationTypes/MGEGTunerStationTypes.h>
#include <CommonAPI/OutputStream.h>
#include "MGEGTunerStation.h"
#include <CommonAPI/Stub.h>

namespace MGEGTunerStation {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service MGEGTunerStation. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class MGEGTunerStationStubAdapter: virtual public CommonAPI::StubAdapter, public MGEGTunerStation {
 public:

    /**
     * Sends a broadcast event for seek. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireSeekEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekData& seekData, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle) = 0;
    /**
     * Sends a broadcast event for stationList. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireStationListEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationList& list, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out) = 0;
    /**
     * Sends a broadcast event for currentStation. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireCurrentStationEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::Station& current, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle) = 0;
};


/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for MGEGTunerStation.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class MGEGTunerStationStubRemoteEvent {
 public:
    virtual ~MGEGTunerStationStubRemoteEvent() { }

};


/**
 * Defines the interface that must be implemented by any class that should provide
 * the service MGEGTunerStation to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class MGEGTunerStationStub : public CommonAPI::Stub<MGEGTunerStationStubAdapter , MGEGTunerStationStubRemoteEvent> {
 public:
    virtual ~MGEGTunerStationStub() { }


    /// This is the method that will be called on remote calls on the method startTune.
    virtual void startTune(MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector station, MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode selectionMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method abortTune.
    virtual void abortTune(MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType device, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method seek.
    virtual void seek(MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType device, MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode seekMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8 genre, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s flags, uint32_t handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method controlUpdate.
    virtual void controlUpdate(MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement updateElement, MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType updateType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 sourceType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 stationType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method makePermanent.
    virtual void makePermanent(MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector station, MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean permanent, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    
    /// Sends a broadcast event for seek.
    virtual void fireSeekEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekData& seekData, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle) = 0;
    /// Sends a broadcast event for stationList.
    virtual void fireStationListEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationList& list, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out) = 0;
    /// Sends a broadcast event for currentStation.
    virtual void fireCurrentStationEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::Station& current, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle) = 0;
};

} // namespace MGEGTunerStation

#endif // MGEGTUNERSTATION_MGEG_Tuner_Station_STUB_H_
