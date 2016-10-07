/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <TunerAdditionalService/TunerAdditionalServiceStubDefault.h>

namespace TunerAdditionalService {

TunerAdditionalServiceStubDefault::TunerAdditionalServiceStubDefault():
        remoteEventHandler_(this) {
}

TunerAdditionalServiceStubRemoteEvent* TunerAdditionalServiceStubDefault::initStubAdapter(const std::shared_ptr<TunerAdditionalServiceStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void TunerAdditionalServiceStubDefault::selectComponent(uint32_t componentID, uint32_t handle, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter componentParameter, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}

void TunerAdditionalServiceStubDefault::requestComponentOptions(uint32_t componentID, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}

void TunerAdditionalServiceStubDefault::requestComponentTypeConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType compentType, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}

void TunerAdditionalServiceStubDefault::changeComponentTypeConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType componentType, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions options, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}


void TunerAdditionalServiceStubDefault::fireGetDataEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& selectParameter, const uint32_t& data, const uint32_t& handleOut) {
    stubAdapter_->fireGetDataEvent(componentID, selectParameter, data, handleOut);
}
void TunerAdditionalServiceStubDefault::fireComponentOptionsEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions& componentOptions, const uint32_t& handleOut) {
    stubAdapter_->fireComponentOptionsEvent(componentID, componentOptions, handleOut);
}
void TunerAdditionalServiceStubDefault::fireComponentTypeConfigurationEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions, const uint32_t& handleOut) {
    stubAdapter_->fireComponentTypeConfigurationEvent(componentType, componentTypeOptions, handleOut);
}
void TunerAdditionalServiceStubDefault::fireAnnouncementEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut) {
    stubAdapter_->fireAnnouncementEvent(announcement, handleOut);
}
void TunerAdditionalServiceStubDefault::fireAnnouncementFinishedEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut_) {
    stubAdapter_->fireAnnouncementFinishedEvent(announcement, handleOut_);
}

TunerAdditionalServiceStubDefault::RemoteEventHandler::RemoteEventHandler(TunerAdditionalServiceStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace TunerAdditionalService
