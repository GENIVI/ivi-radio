/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERSTATION_MGEG_Tuner_Station_STUB_DEFAULT_H_
#define MGEGTUNERSTATION_MGEG_Tuner_Station_STUB_DEFAULT_H_

#include <MGEGTunerStation/MGEGTunerStationStub.h>

namespace MGEGTunerStation {

/**
 * Provides a default implementation for MGEGTunerStationStubRemoteEvent and
 * MGEGTunerStationStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 * 
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class MGEGTunerStationStubDefault : public MGEGTunerStationStub {
 public:
    MGEGTunerStationStubDefault();

    MGEGTunerStationStubRemoteEvent* initStubAdapter(const std::shared_ptr<MGEGTunerStationStubAdapter>& stubAdapter);


    virtual void startTune(MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector station, MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode selectionMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    virtual void abortTune(MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType device, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    virtual void seek(MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType device, MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode seekMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8 genre, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s flags, uint32_t handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    virtual void controlUpdate(MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement updateElement, MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType updateType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 sourceType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 stationType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    virtual void makePermanent(MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector station, MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean permanent, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    
    virtual void fireSeekEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekData& seekData, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle);
    virtual void fireStationListEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationList& list, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out);
    virtual void fireCurrentStationEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::Station& current, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle);

 protected:
    
 private:
    class RemoteEventHandler: public MGEGTunerStationStubRemoteEvent {
     public:
        RemoteEventHandler(MGEGTunerStationStubDefault* defaultStub);


     private:
        MGEGTunerStationStubDefault* defaultStub_;
    };

    RemoteEventHandler remoteEventHandler_;
    std::shared_ptr<MGEGTunerStationStubAdapter> stubAdapter_;

};

} // namespace MGEGTunerStation

#endif // MGEGTUNERSTATION_MGEG_Tuner_Station_STUB_DEFAULT_H_
