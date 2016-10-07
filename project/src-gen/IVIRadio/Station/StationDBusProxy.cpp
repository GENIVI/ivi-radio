/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "StationDBusProxy.h"

namespace IVIRadio {
namespace Station {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createStationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection) {
    return std::make_shared<StationDBusProxy>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection);
}

__attribute__((constructor)) void registerStationDBusProxy(void) {
    CommonAPI::DBus::DBusFactory::registerProxyFactoryMethod(Station::getInterfaceId(),
       &createStationDBusProxy);
}

StationDBusProxy::StationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection):
        CommonAPI::DBus::DBusProxy(commonApiAddress, interfaceName, busName, objectPath, dbusProxyconnection)
,        currentStation_(*this, "currentStation", "(uaua(sy)asau(uau)u)ui"),
                        seek_(*this, "seek", "(uii)ui"),
                        stationList_(*this, "stationList", "(ua(uaua(sy)asau(uau)u)u)ui")
                 {
}


StationDBusProxy::CurrentStationEvent& StationDBusProxy::getCurrentStationEvent() {
    return currentStation_;
}
StationDBusProxy::SeekEvent& StationDBusProxy::getSeekEvent() {
    return seek_;
}
StationDBusProxy::StationListEvent& StationDBusProxy::getStationListEvent() {
    return stationList_;
}

void StationDBusProxy::abortTune(const Types::Types::DeviceType& deviceType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::DeviceType, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "abortTune",
        "iu",
        deviceType, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> StationDBusProxy::abortTuneAsync(const Types::Types::DeviceType& deviceType, const uint32_t& handle, AbortTuneAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::DeviceType, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "abortTune",
        "iu",
        deviceType, handle, 
        std::move(callback));
}
void StationDBusProxy::makePermanent(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::StationSelector, bool, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "makePermanent",
        "(uau)bu",
        station, permanent, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> StationDBusProxy::makePermanentAsync(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::StationSelector, bool, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "makePermanent",
        "(uau)bu",
        station, permanent, handle, 
        std::move(callback));
}
void StationDBusProxy::controlUpdate(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<StationTypes::UpdateElement, Types::Types::UpdateType, uint32_t, uint32_t, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "controlUpdate",
        "iiuuu",
        updateElement, updateType, sourceType, stationType, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> StationDBusProxy::controlUpdateAsync(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<StationTypes::UpdateElement, Types::Types::UpdateType, uint32_t, uint32_t, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "controlUpdate",
        "iiuuu",
        updateElement, updateType, sourceType, stationType, handle, 
        std::move(callback));
}
void StationDBusProxy::seek(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::DeviceType, StationTypes::SeekMode, uint8_t, Types::Types::UInt32s, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "seek",
        "iiyauu",
        device, seekMode, genre, flags, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> StationDBusProxy::seekAsync(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::DeviceType, StationTypes::SeekMode, uint8_t, Types::Types::UInt32s, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "seek",
        "iiyauu",
        device, seekMode, genre, flags, handle, 
        std::move(callback));
}
void StationDBusProxy::startTune(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::StationSelector, StationTypes::SelectionMode, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "startTune",
        "(uau)iu",
        station, selectionMode, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> StationDBusProxy::startTuneAsync(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::StationSelector, StationTypes::SelectionMode, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "startTune",
        "(uau)iu",
        station, selectionMode, handle, 
        std::move(callback));
}

void StationDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 2;
    ownVersionMinor = 0;
}

} // namespace Station
} // namespace IVIRadio
