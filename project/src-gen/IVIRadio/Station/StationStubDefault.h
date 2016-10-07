/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_STATION_Station_STUB_DEFAULT_H_
#define IVIRADIO_STATION_Station_STUB_DEFAULT_H_

#include <IVIRadio/Station/StationStub.h>

namespace IVIRadio {
namespace Station {

/**
 * Provides a default implementation for StationStubRemoteEvent and
 * StationStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 * 
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class StationStubDefault : public StationStub {
 public:
    StationStubDefault();

    StationStubRemoteEvent* initStubAdapter(const std::shared_ptr<StationStubAdapter>& stubAdapter);


    virtual void abortTune(Types::Types::DeviceType deviceType, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    virtual void makePermanent(Types::Types::StationSelector station, bool permanent, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    virtual void controlUpdate(StationTypes::UpdateElement updateElement, Types::Types::UpdateType updateType, uint32_t sourceType, uint32_t stationType, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    virtual void seek(Types::Types::DeviceType device, StationTypes::SeekMode seekMode, uint8_t genre, Types::Types::UInt32s flags, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    virtual void startTune(Types::Types::StationSelector station, StationTypes::SelectionMode selectionMode, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    
    virtual void fireCurrentStationEvent(const StationTypes::Station& current, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    virtual void fireSeekEvent(const StationTypes::SeekData& seekData, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    virtual void fireStationListEvent(const StationTypes::StationList& list, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);

 protected:
    
 private:
    class RemoteEventHandler: public StationStubRemoteEvent {
     public:
        RemoteEventHandler(StationStubDefault* defaultStub);


     private:
        StationStubDefault* defaultStub_;
    };

    RemoteEventHandler remoteEventHandler_;
    std::shared_ptr<StationStubAdapter> stubAdapter_;

};

} // namespace Station
} // namespace IVIRadio

#endif // IVIRADIO_STATION_Station_STUB_DEFAULT_H_
