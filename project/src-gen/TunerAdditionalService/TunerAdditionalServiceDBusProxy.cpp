/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "TunerAdditionalServiceDBusProxy.h"

namespace TunerAdditionalService {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createTunerAdditionalServiceDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection) {
    return std::make_shared<TunerAdditionalServiceDBusProxy>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection);
}

__attribute__((constructor)) void registerTunerAdditionalServiceDBusProxy(void) {
    CommonAPI::DBus::DBusFactory::registerProxyFactoryMethod(TunerAdditionalService::getInterfaceId(),
       &createTunerAdditionalServiceDBusProxy);
}

TunerAdditionalServiceDBusProxy::TunerAdditionalServiceDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection):
        CommonAPI::DBus::DBusProxy(commonApiAddress, interfaceName, busName, objectPath, dbusProxyconnection)
,        getData_(*this, "getData", "u(yv)uu"),
                        componentOptions_(*this, "componentOptions", "u(yv)u"),
                        componentTypeConfiguration_(*this, "componentTypeConfiguration", "i(yv)u"),
                        announcement_(*this, "announcement", "(ui)u"),
                        announcementFinished_(*this, "announcementFinished", "(ui)u")
                 {
}


TunerAdditionalServiceDBusProxy::GetDataEvent& TunerAdditionalServiceDBusProxy::getGetDataEvent() {
    return getData_;
}
TunerAdditionalServiceDBusProxy::ComponentOptionsEvent& TunerAdditionalServiceDBusProxy::getComponentOptionsEvent() {
    return componentOptions_;
}
TunerAdditionalServiceDBusProxy::ComponentTypeConfigurationEvent& TunerAdditionalServiceDBusProxy::getComponentTypeConfigurationEvent() {
    return componentTypeConfiguration_;
}
TunerAdditionalServiceDBusProxy::AnnouncementEvent& TunerAdditionalServiceDBusProxy::getAnnouncementEvent() {
    return announcement_;
}
TunerAdditionalServiceDBusProxy::AnnouncementFinishedEvent& TunerAdditionalServiceDBusProxy::getAnnouncementFinishedEvent() {
    return announcementFinished_;
}

void TunerAdditionalServiceDBusProxy::selectComponent(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t, uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "selectComponent",
        "uu(yv)",
        componentID, handle, componentParameter, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> TunerAdditionalServiceDBusProxy::selectComponentAsync(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, SelectComponentAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t, uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "selectComponent",
        "uu(yv)",
        componentID, handle, componentParameter, 
        std::move(callback));
}
void TunerAdditionalServiceDBusProxy::requestComponentOptions(const uint32_t& componentID, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "requestComponentOptions",
        "uu",
        componentID, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> TunerAdditionalServiceDBusProxy::requestComponentOptionsAsync(const uint32_t& componentID, const uint32_t& handle, RequestComponentOptionsAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "requestComponentOptions",
        "uu",
        componentID, handle, 
        std::move(callback));
}
void TunerAdditionalServiceDBusProxy::requestComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "requestComponentTypeConfiguration",
        "iu",
        compentType, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> TunerAdditionalServiceDBusProxy::requestComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "requestComponentTypeConfiguration",
        "iu",
        compentType, handle, 
        std::move(callback));
}
void TunerAdditionalServiceDBusProxy::changeComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "changeComponentTypeConfiguration",
        "i(yv)u",
        componentType, options, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> TunerAdditionalServiceDBusProxy::changeComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, ChangeComponentTypeConfigurationAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerTypes::TunerTypes::Feedback> >::callMethodAsync(
        *this,
        "changeComponentTypeConfiguration",
        "i(yv)u",
        componentType, options, handle, 
        std::move(callback));
}

void TunerAdditionalServiceDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
}

} // namespace TunerAdditionalService
