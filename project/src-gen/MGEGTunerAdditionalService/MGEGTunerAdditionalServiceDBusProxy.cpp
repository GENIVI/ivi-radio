/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "MGEGTunerAdditionalServiceDBusProxy.h"

namespace MGEGTunerAdditionalService {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createMGEGTunerAdditionalServiceDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection) {
    return std::make_shared<MGEGTunerAdditionalServiceDBusProxy>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection);
}

__attribute__((constructor)) void registerMGEGTunerAdditionalServiceDBusProxy(void) {
    CommonAPI::DBus::DBusFactory::registerProxyFactoryMethod(MGEGTunerAdditionalService::getInterfaceId(),
       &createMGEGTunerAdditionalServiceDBusProxy);
}

MGEGTunerAdditionalServiceDBusProxy::MGEGTunerAdditionalServiceDBusProxy(
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


MGEGTunerAdditionalServiceDBusProxy::GetDataEvent& MGEGTunerAdditionalServiceDBusProxy::getGetDataEvent() {
    return getData_;
}
MGEGTunerAdditionalServiceDBusProxy::ComponentOptionsEvent& MGEGTunerAdditionalServiceDBusProxy::getComponentOptionsEvent() {
    return componentOptions_;
}
MGEGTunerAdditionalServiceDBusProxy::ComponentTypeConfigurationEvent& MGEGTunerAdditionalServiceDBusProxy::getComponentTypeConfigurationEvent() {
    return componentTypeConfiguration_;
}
MGEGTunerAdditionalServiceDBusProxy::AnnouncementEvent& MGEGTunerAdditionalServiceDBusProxy::getAnnouncementEvent() {
    return announcement_;
}
MGEGTunerAdditionalServiceDBusProxy::AnnouncementFinishedEvent& MGEGTunerAdditionalServiceDBusProxy::getAnnouncementFinishedEvent() {
    return announcementFinished_;
}

void MGEGTunerAdditionalServiceDBusProxy::selectComponent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "selectComponent",
        "uu(yv)",
        componentID, handle, componentParameter, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerAdditionalServiceDBusProxy::selectComponentAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, SelectComponentAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "selectComponent",
        "uu(yv)",
        componentID, handle, componentParameter, 
        std::move(callback));
}
void MGEGTunerAdditionalServiceDBusProxy::requestComponentOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "requestComponentOptions",
        "uu",
        componentID, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerAdditionalServiceDBusProxy::requestComponentOptionsAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, RequestComponentOptionsAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "requestComponentOptions",
        "uu",
        componentID, handle, 
        std::move(callback));
}
void MGEGTunerAdditionalServiceDBusProxy::requestComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "requestComponentTypeConfiguration",
        "iu",
        compentType, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerAdditionalServiceDBusProxy::requestComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "requestComponentTypeConfiguration",
        "iu",
        compentType, handle, 
        std::move(callback));
}
void MGEGTunerAdditionalServiceDBusProxy::changeComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodWithReply(
        *this,
        "changeComponentTypeConfiguration",
        "i(yv)u",
        componentType, options, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> MGEGTunerAdditionalServiceDBusProxy::changeComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ChangeComponentTypeConfigurationAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
                                     CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback> >::callMethodAsync(
        *this,
        "changeComponentTypeConfiguration",
        "i(yv)u",
        componentType, options, handle, 
        std::move(callback));
}

void MGEGTunerAdditionalServiceDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
}

} // namespace MGEGTunerAdditionalService
