/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "TunerStationDBusProxy.h"

namespace TunerStation {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createTunerStationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection) {
    return std::make_shared<TunerStationDBusProxy>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection);
}

__attribute__((constructor)) void registerTunerStationDBusProxy(void) {
    CommonAPI::DBus::DBusFactory::registerProxyFactoryMethod(TunerStation::getInterfaceId(),
       &createTunerStationDBusProxy);
}

TunerStationDBusProxy::TunerStationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection):
        CommonAPI::DBus::DBusProxy(commonApiAddress, interfaceName, busName, objectPath, dbusProxyconnection)
,        seek_(*this, "seek", "(uii)u"),
                        stationList_(*this, "stationList", "(ua(auaua(sy)asau(uau)u)u)u"),
                        currentStation_(*this, "currentStation", "(auaua(sy)asau(uau)u)u")
                 {
}


TunerStationDBusProxy::SeekEvent& TunerStationDBusProxy::getSeekEvent() {
    return seek_;
}
TunerStationDBusProxy::StationListEvent& TunerStationDBusProxy::getStationListEvent() {
    return stationList_;
}
TunerStationDBusProxy::CurrentStationEvent& TunerStationDBusProxy::getCurrentStationEvent() {
    return currentStation_;
}

void TunerStationDBusProxy::startTune(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::StationSelector, TunerStationTypes::TunerStationTypes::SelectionMode, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "startTune",
        "(uau)iu",
        station, selectionMode, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> TunerStationDBusProxy::startTuneAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::StationSelector, TunerStationTypes::TunerStationTypes::SelectionMode, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "startTune",
        "(uau)iu",
        station, selectionMode, handle, 
        std::move(callback));
}
void TunerStationDBusProxy::abortTune(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::DeviceType, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "abortTune",
        "iu",
        device, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> TunerStationDBusProxy::abortTuneAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, AbortTuneAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::DeviceType, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "abortTune",
        "iu",
        device, handle, 
        std::move(callback));
}
void TunerStationDBusProxy::seek(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::DeviceType, TunerStationTypes::TunerStationTypes::SeekMode, uint8_t, TunerTypes::TunerTypes::UInt32s, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "seek",
        "iiyauu",
        device, seekMode, genre, flags, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> TunerStationDBusProxy::seekAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::DeviceType, TunerStationTypes::TunerStationTypes::SeekMode, uint8_t, TunerTypes::TunerTypes::UInt32s, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "seek",
        "iiyauu",
        device, seekMode, genre, flags, handle, 
        std::move(callback));
}
void TunerStationDBusProxy::controlUpdate(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::UpdateElement, TunerStationTypes::TunerStationTypes::UpdateType, uint32_t, uint32_t, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "controlUpdate",
        "iiuuu",
        updateElement, updateType, sourceType, stationType, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> TunerStationDBusProxy::controlUpdateAsync(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::UpdateElement, TunerStationTypes::TunerStationTypes::UpdateType, uint32_t, uint32_t, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "controlUpdate",
        "iiuuu",
        updateElement, updateType, sourceType, stationType, handle, 
        std::move(callback));
}
void TunerStationDBusProxy::makePermanent(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::StationSelector, bool, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "makePermanent",
        "(uau)bu",
        station, permanent, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> TunerStationDBusProxy::makePermanentAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::StationSelector, bool, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "makePermanent",
        "(uau)bu",
        station, permanent, handle, 
        std::move(callback));
}

void TunerStationDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
}

} // namespace TunerStation
