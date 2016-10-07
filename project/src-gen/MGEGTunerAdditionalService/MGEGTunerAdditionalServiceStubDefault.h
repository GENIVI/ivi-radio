/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_STUB_DEFAULT_H_
#define MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_STUB_DEFAULT_H_

#include <MGEGTunerAdditionalService/MGEGTunerAdditionalServiceStub.h>

namespace MGEGTunerAdditionalService {

/**
 * Provides a default implementation for MGEGTunerAdditionalServiceStubRemoteEvent and
 * MGEGTunerAdditionalServiceStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 * 
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class MGEGTunerAdditionalServiceStubDefault : public MGEGTunerAdditionalServiceStub {
 public:
    MGEGTunerAdditionalServiceStubDefault();

    MGEGTunerAdditionalServiceStubRemoteEvent* initStubAdapter(const std::shared_ptr<MGEGTunerAdditionalServiceStubAdapter>& stubAdapter);


    virtual void selectComponent(MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 componentID, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter componentParameter, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    virtual void requestComponentOptions(MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 componentID, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    virtual void requestComponentTypeConfiguration(MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType compentType, uint32_t handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    virtual void changeComponentTypeConfiguration(MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType componentType, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions options, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);

    
    virtual void fireGetDataEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& selectParameter, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& data, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut);
    virtual void fireComponentOptionsEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentOptions& componentOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut);
    virtual void fireComponentTypeConfigurationEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& componentTypeOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut);
    virtual void fireAnnouncementEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut);
    virtual void fireAnnouncementFinishedEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut_);

 protected:
    
 private:
    class RemoteEventHandler: public MGEGTunerAdditionalServiceStubRemoteEvent {
     public:
        RemoteEventHandler(MGEGTunerAdditionalServiceStubDefault* defaultStub);


     private:
        MGEGTunerAdditionalServiceStubDefault* defaultStub_;
    };

    RemoteEventHandler remoteEventHandler_;
    std::shared_ptr<MGEGTunerAdditionalServiceStubAdapter> stubAdapter_;

};

} // namespace MGEGTunerAdditionalService

#endif // MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_STUB_DEFAULT_H_
