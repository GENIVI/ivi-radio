/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERSTATION_Tuner_Station_STUB_H_
#define TUNERSTATION_Tuner_Station_STUB_H_

#include <TunerStationTypes/TunerStationTypes.h>
#include <cstdint>
#include <vector>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <TunerTypes/TunerTypes.h>
#include <CommonAPI/OutputStream.h>
#include "TunerStation.h"
#include <CommonAPI/Stub.h>

namespace TunerStation {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service TunerStation. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class TunerStationStubAdapter: virtual public CommonAPI::StubAdapter, public TunerStation {
 public:

    /**
     * Sends a broadcast event for seek. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireSeekEvent(const TunerStationTypes::TunerStationTypes::SeekData& seekData, const uint32_t& handle) = 0;
    /**
     * Sends a broadcast event for stationList. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireStationListEvent(const TunerStationTypes::TunerStationTypes::StationList& list, const uint32_t& handle_out) = 0;
    /**
     * Sends a broadcast event for currentStation. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireCurrentStationEvent(const TunerStationTypes::TunerStationTypes::Station& current, const uint32_t& handle) = 0;
};


/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for TunerStation.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TunerStationStubRemoteEvent {
 public:
    virtual ~TunerStationStubRemoteEvent() { }

};


/**
 * Defines the interface that must be implemented by any class that should provide
 * the service TunerStation to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TunerStationStub : public CommonAPI::Stub<TunerStationStubAdapter , TunerStationStubRemoteEvent> {
 public:
    virtual ~TunerStationStub() { }


    /// This is the method that will be called on remote calls on the method startTune.
    virtual void startTune(TunerStationTypes::TunerStationTypes::StationSelector station, TunerStationTypes::TunerStationTypes::SelectionMode selectionMode, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method abortTune.
    virtual void abortTune(TunerStationTypes::TunerStationTypes::DeviceType device, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method seek.
    virtual void seek(TunerStationTypes::TunerStationTypes::DeviceType device, TunerStationTypes::TunerStationTypes::SeekMode seekMode, uint8_t genre, TunerTypes::TunerTypes::UInt32s flags, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method controlUpdate.
    virtual void controlUpdate(TunerStationTypes::TunerStationTypes::UpdateElement updateElement, TunerStationTypes::TunerStationTypes::UpdateType updateType, uint32_t sourceType, uint32_t stationType, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method makePermanent.
    virtual void makePermanent(TunerStationTypes::TunerStationTypes::StationSelector station, bool permanent, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    
    /// Sends a broadcast event for seek.
    virtual void fireSeekEvent(const TunerStationTypes::TunerStationTypes::SeekData& seekData, const uint32_t& handle) = 0;
    /// Sends a broadcast event for stationList.
    virtual void fireStationListEvent(const TunerStationTypes::TunerStationTypes::StationList& list, const uint32_t& handle_out) = 0;
    /// Sends a broadcast event for currentStation.
    virtual void fireCurrentStationEvent(const TunerStationTypes::TunerStationTypes::Station& current, const uint32_t& handle) = 0;
};

} // namespace TunerStation

#endif // TUNERSTATION_Tuner_Station_STUB_H_
