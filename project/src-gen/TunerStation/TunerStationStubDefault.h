/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERSTATION_Tuner_Station_STUB_DEFAULT_H_
#define TUNERSTATION_Tuner_Station_STUB_DEFAULT_H_

#include <TunerStation/TunerStationStub.h>

namespace TunerStation {

/**
 * Provides a default implementation for TunerStationStubRemoteEvent and
 * TunerStationStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 * 
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class TunerStationStubDefault : public TunerStationStub {
 public:
    TunerStationStubDefault();

    TunerStationStubRemoteEvent* initStubAdapter(const std::shared_ptr<TunerStationStubAdapter>& stubAdapter);


    virtual void startTune(TunerStationTypes::TunerStationTypes::StationSelector station, TunerStationTypes::TunerStationTypes::SelectionMode selectionMode, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);

    virtual void abortTune(TunerStationTypes::TunerStationTypes::DeviceType device, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);

    virtual void seek(TunerStationTypes::TunerStationTypes::DeviceType device, TunerStationTypes::TunerStationTypes::SeekMode seekMode, uint8_t genre, TunerTypes::TunerTypes::UInt32s flags, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);

    virtual void controlUpdate(TunerStationTypes::TunerStationTypes::UpdateElement updateElement, TunerStationTypes::TunerStationTypes::UpdateType updateType, uint32_t sourceType, uint32_t stationType, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);

    virtual void makePermanent(TunerStationTypes::TunerStationTypes::StationSelector station, bool permanent, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);

    
    virtual void fireSeekEvent(const TunerStationTypes::TunerStationTypes::SeekData& seekData, const uint32_t& handle);
    virtual void fireStationListEvent(const TunerStationTypes::TunerStationTypes::StationList& list, const uint32_t& handle_out);
    virtual void fireCurrentStationEvent(const TunerStationTypes::TunerStationTypes::Station& current, const uint32_t& handle);

 protected:
    
 private:
    class RemoteEventHandler: public TunerStationStubRemoteEvent {
     public:
        RemoteEventHandler(TunerStationStubDefault* defaultStub);


     private:
        TunerStationStubDefault* defaultStub_;
    };

    RemoteEventHandler remoteEventHandler_;
    std::shared_ptr<TunerStationStubAdapter> stubAdapter_;

};

} // namespace TunerStation

#endif // TUNERSTATION_Tuner_Station_STUB_DEFAULT_H_
