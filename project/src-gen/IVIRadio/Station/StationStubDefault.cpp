/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <IVIRadio/Station/StationStubDefault.h>

namespace IVIRadio {
namespace Station {

StationStubDefault::StationStubDefault():
        remoteEventHandler_(this) {
}

StationStubRemoteEvent* StationStubDefault::initStubAdapter(const std::shared_ptr<StationStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void StationStubDefault::abortTune(Types::Types::DeviceType deviceType, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}

void StationStubDefault::makePermanent(Types::Types::StationSelector station, bool permanent, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}

void StationStubDefault::controlUpdate(StationTypes::UpdateElement updateElement, Types::Types::UpdateType updateType, uint32_t sourceType, uint32_t stationType, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}

void StationStubDefault::seek(Types::Types::DeviceType device, StationTypes::SeekMode seekMode, uint8_t genre, Types::Types::UInt32s flags, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}

void StationStubDefault::startTune(Types::Types::StationSelector station, StationTypes::SelectionMode selectionMode, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}


void StationStubDefault::fireCurrentStationEvent(const StationTypes::Station& current, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    stubAdapter_->fireCurrentStationEvent(current, handleOut, errorCode);
}
void StationStubDefault::fireSeekEvent(const StationTypes::SeekData& seekData, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    stubAdapter_->fireSeekEvent(seekData, handleOut, errorCode);
}
void StationStubDefault::fireStationListEvent(const StationTypes::StationList& list, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    stubAdapter_->fireStationListEvent(list, handleOut, errorCode);
}

StationStubDefault::RemoteEventHandler::RemoteEventHandler(StationStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace Station
} // namespace IVIRadio
