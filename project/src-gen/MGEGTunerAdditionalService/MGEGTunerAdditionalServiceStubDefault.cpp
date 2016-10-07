/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <MGEGTunerAdditionalService/MGEGTunerAdditionalServiceStubDefault.h>

namespace MGEGTunerAdditionalService {

MGEGTunerAdditionalServiceStubDefault::MGEGTunerAdditionalServiceStubDefault():
        remoteEventHandler_(this) {
}

MGEGTunerAdditionalServiceStubRemoteEvent* MGEGTunerAdditionalServiceStubDefault::initStubAdapter(const std::shared_ptr<MGEGTunerAdditionalServiceStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void MGEGTunerAdditionalServiceStubDefault::selectComponent(MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 componentID, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter componentParameter, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}

void MGEGTunerAdditionalServiceStubDefault::requestComponentOptions(MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 componentID, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}

void MGEGTunerAdditionalServiceStubDefault::requestComponentTypeConfiguration(MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType compentType, uint32_t handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}

void MGEGTunerAdditionalServiceStubDefault::changeComponentTypeConfiguration(MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType componentType, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions options, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}


void MGEGTunerAdditionalServiceStubDefault::fireGetDataEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& selectParameter, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& data, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) {
    stubAdapter_->fireGetDataEvent(componentID, selectParameter, data, handleOut);
}
void MGEGTunerAdditionalServiceStubDefault::fireComponentOptionsEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentOptions& componentOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) {
    stubAdapter_->fireComponentOptionsEvent(componentID, componentOptions, handleOut);
}
void MGEGTunerAdditionalServiceStubDefault::fireComponentTypeConfigurationEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& componentTypeOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) {
    stubAdapter_->fireComponentTypeConfigurationEvent(componentType, componentTypeOptions, handleOut);
}
void MGEGTunerAdditionalServiceStubDefault::fireAnnouncementEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) {
    stubAdapter_->fireAnnouncementEvent(announcement, handleOut);
}
void MGEGTunerAdditionalServiceStubDefault::fireAnnouncementFinishedEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut_) {
    stubAdapter_->fireAnnouncementFinishedEvent(announcement, handleOut_);
}

MGEGTunerAdditionalServiceStubDefault::RemoteEventHandler::RemoteEventHandler(MGEGTunerAdditionalServiceStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace MGEGTunerAdditionalService
