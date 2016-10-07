/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <MGEGTunerStation/MGEGTunerStationStubDefault.h>

namespace MGEGTunerStation {

MGEGTunerStationStubDefault::MGEGTunerStationStubDefault():
        remoteEventHandler_(this) {
}

MGEGTunerStationStubRemoteEvent* MGEGTunerStationStubDefault::initStubAdapter(const std::shared_ptr<MGEGTunerStationStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void MGEGTunerStationStubDefault::startTune(MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector station, MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode selectionMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}

void MGEGTunerStationStubDefault::abortTune(MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType device, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}

void MGEGTunerStationStubDefault::seek(MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType device, MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode seekMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8 genre, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s flags, uint32_t handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}

void MGEGTunerStationStubDefault::controlUpdate(MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement updateElement, MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType updateType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 sourceType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 stationType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}

void MGEGTunerStationStubDefault::makePermanent(MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector station, MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean permanent, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    // No operation in default
}


void MGEGTunerStationStubDefault::fireSeekEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekData& seekData, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle) {
    stubAdapter_->fireSeekEvent(seekData, handle);
}
void MGEGTunerStationStubDefault::fireStationListEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationList& list, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out) {
    stubAdapter_->fireStationListEvent(list, handle_out);
}
void MGEGTunerStationStubDefault::fireCurrentStationEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::Station& current, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle) {
    stubAdapter_->fireCurrentStationEvent(current, handle);
}

MGEGTunerStationStubDefault::RemoteEventHandler::RemoteEventHandler(MGEGTunerStationStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace MGEGTunerStation
