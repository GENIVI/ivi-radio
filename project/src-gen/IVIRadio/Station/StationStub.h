/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_STATION_Station_STUB_H_
#define IVIRADIO_STATION_Station_STUB_H_

#include <cstdint>
#include <vector>
#include <CommonAPI/InputStream.h>
#include <IVIRadio/Station/StationTypes.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/OutputStream.h>
#include <IVIRadio/Types/Types.h>
#include "Station.h"
#include <CommonAPI/Stub.h>

namespace IVIRadio {
namespace Station {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service Station. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class StationStubAdapter: virtual public CommonAPI::StubAdapter, public Station {
 public:

    /**
     * Sends a broadcast event for currentStation. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireCurrentStationEvent(const StationTypes::Station& current, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /**
     * Sends a broadcast event for seek. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireSeekEvent(const StationTypes::SeekData& seekData, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /**
     * Sends a broadcast event for stationList. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireStationListEvent(const StationTypes::StationList& list, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
};


/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for Station.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class StationStubRemoteEvent {
 public:
    virtual ~StationStubRemoteEvent() { }

};


/**
 * Defines the interface that must be implemented by any class that should provide
 * the service Station to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class StationStub : public CommonAPI::Stub<StationStubAdapter , StationStubRemoteEvent> {
 public:
    virtual ~StationStub() { }


    /// This is the method that will be called on remote calls on the method abortTune.
    virtual void abortTune(Types::Types::DeviceType deviceType, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method makePermanent.
    virtual void makePermanent(Types::Types::StationSelector station, bool permanent, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method controlUpdate.
    virtual void controlUpdate(StationTypes::UpdateElement updateElement, Types::Types::UpdateType updateType, uint32_t sourceType, uint32_t stationType, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method seek.
    virtual void seek(Types::Types::DeviceType device, StationTypes::SeekMode seekMode, uint8_t genre, Types::Types::UInt32s flags, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method startTune.
    virtual void startTune(Types::Types::StationSelector station, StationTypes::SelectionMode selectionMode, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    
    /// Sends a broadcast event for currentStation.
    virtual void fireCurrentStationEvent(const StationTypes::Station& current, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /// Sends a broadcast event for seek.
    virtual void fireSeekEvent(const StationTypes::SeekData& seekData, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /// Sends a broadcast event for stationList.
    virtual void fireStationListEvent(const StationTypes::StationList& list, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
};

} // namespace Station
} // namespace IVIRadio

#endif // IVIRADIO_STATION_Station_STUB_H_
