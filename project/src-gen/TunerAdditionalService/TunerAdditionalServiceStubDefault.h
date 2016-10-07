/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERADDITIONALSERVICE_Tuner_Additional_Service_STUB_DEFAULT_H_
#define TUNERADDITIONALSERVICE_Tuner_Additional_Service_STUB_DEFAULT_H_

#include <TunerAdditionalService/TunerAdditionalServiceStub.h>

namespace TunerAdditionalService {

/**
 * Provides a default implementation for TunerAdditionalServiceStubRemoteEvent and
 * TunerAdditionalServiceStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 * 
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class TunerAdditionalServiceStubDefault : public TunerAdditionalServiceStub {
 public:
    TunerAdditionalServiceStubDefault();

    TunerAdditionalServiceStubRemoteEvent* initStubAdapter(const std::shared_ptr<TunerAdditionalServiceStubAdapter>& stubAdapter);


    virtual void selectComponent(uint32_t componentID, uint32_t handle, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter componentParameter, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);

    virtual void requestComponentOptions(uint32_t componentID, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);

    virtual void requestComponentTypeConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType compentType, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);

    virtual void changeComponentTypeConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType componentType, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions options, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);

    
    virtual void fireGetDataEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& selectParameter, const uint32_t& data, const uint32_t& handleOut);
    virtual void fireComponentOptionsEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions& componentOptions, const uint32_t& handleOut);
    virtual void fireComponentTypeConfigurationEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions, const uint32_t& handleOut);
    virtual void fireAnnouncementEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut);
    virtual void fireAnnouncementFinishedEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut_);

 protected:
    
 private:
    class RemoteEventHandler: public TunerAdditionalServiceStubRemoteEvent {
     public:
        RemoteEventHandler(TunerAdditionalServiceStubDefault* defaultStub);


     private:
        TunerAdditionalServiceStubDefault* defaultStub_;
    };

    RemoteEventHandler remoteEventHandler_;
    std::shared_ptr<TunerAdditionalServiceStubAdapter> stubAdapter_;

};

} // namespace TunerAdditionalService

#endif // TUNERADDITIONALSERVICE_Tuner_Additional_Service_STUB_DEFAULT_H_
