/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "MGEGTunerStationDBusProxy.h"

namespace MGEGTunerStation {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createMGEGTunerStationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection) {
    return std::make_shared<MGEGTunerStationDBusProxy>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection);
}

__attribute__((constructor)) void registerMGEGTunerStationDBusProxy(void) {
    CommonAPI::DBus::DBusFactory::registerProxyFactoryMethod(MGEGTunerStation::getInterfaceId(),
       &createMGEGTunerStationDBusProxy);
}

MGEGTunerStationDBusProxy::MGEGTunerStationDBusProxy(
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


MGEGTunerStationDBusProxy::SeekEvent& MGEGTunerStationDBusProxy::getSeekEvent() {
    return seek_;
}
MGEGTunerStationDBusProxy::StationListEvent& MGEGTunerStationDBusProxy::getStationListEvent() {
    return stationList_;
}
MGEGTunerStationDBusProxy::CurrentStationEvent& MGEGTunerStationDBusProxy::getCurrentStationEvent() {
    return currentStation_;
}

void MGEGTunerStationDBusProxy::startTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector, MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "startTune",
        "(uau)iu",
        station, selectionMode, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerStationDBusProxy::startTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, StartTuneAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector, MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "startTune",
        "(uau)iu",
        station, selectionMode, handle, 
        std::move(callback));
}
void MGEGTunerStationDBusProxy::abortTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "abortTune",
        "iu",
        device, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerStationDBusProxy::abortTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, AbortTuneAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "abortTune",
        "iu",
        device, handle, 
        std::move(callback));
}
void MGEGTunerStationDBusProxy::seek(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType, MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "seek",
        "iiyauu",
        device, seekMode, genre, flags, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerStationDBusProxy::seekAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType, MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "seek",
        "iiyauu",
        device, seekMode, genre, flags, handle, 
        std::move(callback));
}
void MGEGTunerStationDBusProxy::controlUpdate(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement, MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "controlUpdate",
        "iiuuu",
        updateElement, updateType, sourceType, stationType, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerStationDBusProxy::controlUpdateAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ControlUpdateAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement, MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "controlUpdate",
        "iiuuu",
        updateElement, updateType, sourceType, stationType, handle, 
        std::move(callback));
}
void MGEGTunerStationDBusProxy::makePermanent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector, MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "makePermanent",
        "(uau)bu",
        station, permanent, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerStationDBusProxy::makePermanentAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, MakePermanentAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector, MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "makePermanent",
        "(uau)bu",
        station, permanent, handle, 
        std::move(callback));
}

void MGEGTunerStationDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
}

} // namespace MGEGTunerStation
