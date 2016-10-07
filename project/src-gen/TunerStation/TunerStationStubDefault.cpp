/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <TunerStation/TunerStationStubDefault.h>

namespace TunerStation {

TunerStationStubDefault::TunerStationStubDefault():
        remoteEventHandler_(this) {
}

TunerStationStubRemoteEvent* TunerStationStubDefault::initStubAdapter(const std::shared_ptr<TunerStationStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void TunerStationStubDefault::startTune(TunerStationTypes::TunerStationTypes::StationSelector station, TunerStationTypes::TunerStationTypes::SelectionMode selectionMode, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}

void TunerStationStubDefault::abortTune(TunerStationTypes::TunerStationTypes::DeviceType device, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}

void TunerStationStubDefault::seek(TunerStationTypes::TunerStationTypes::DeviceType device, TunerStationTypes::TunerStationTypes::SeekMode seekMode, uint8_t genre, TunerTypes::TunerTypes::UInt32s flags, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}

void TunerStationStubDefault::controlUpdate(TunerStationTypes::TunerStationTypes::UpdateElement updateElement, TunerStationTypes::TunerStationTypes::UpdateType updateType, uint32_t sourceType, uint32_t stationType, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}

void TunerStationStubDefault::makePermanent(TunerStationTypes::TunerStationTypes::StationSelector station, bool permanent, uint32_t handle, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    // No operation in default
}


void TunerStationStubDefault::fireSeekEvent(const TunerStationTypes::TunerStationTypes::SeekData& seekData, const uint32_t& handle) {
    stubAdapter_->fireSeekEvent(seekData, handle);
}
void TunerStationStubDefault::fireStationListEvent(const TunerStationTypes::TunerStationTypes::StationList& list, const uint32_t& handle_out) {
    stubAdapter_->fireStationListEvent(list, handle_out);
}
void TunerStationStubDefault::fireCurrentStationEvent(const TunerStationTypes::TunerStationTypes::Station& current, const uint32_t& handle) {
    stubAdapter_->fireCurrentStationEvent(current, handle);
}

TunerStationStubDefault::RemoteEventHandler::RemoteEventHandler(TunerStationStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace TunerStation
