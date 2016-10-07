/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "ConfigurationDBusProxy.h"

namespace IVIRadio {
namespace Configuration {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createConfigurationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection) {
    return std::make_shared<ConfigurationDBusProxy>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection);
}

__attribute__((constructor)) void registerConfigurationDBusProxy(void) {
    CommonAPI::DBus::DBusFactory::registerProxyFactoryMethod(Configuration::getInterfaceId(),
       &createConfigurationDBusProxy);
}

ConfigurationDBusProxy::ConfigurationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection):
        CommonAPI::DBus::DBusProxy(commonApiAddress, interfaceName, busName, objectPath, dbusProxyconnection)
,        functionalityConfiguration_(*this, "functionalityConfiguration", "aia(yv)ui")
                 {
}


ConfigurationDBusProxy::FunctionalityConfigurationEvent& ConfigurationDBusProxy::getFunctionalityConfigurationEvent() {
    return functionalityConfiguration_;
}

void ConfigurationDBusProxy::changeFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<ConfigurationTypesEnum::FunctionalityTypes, ConfigurationOptions::FuntionalityOptions, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "changeFunctionalityConfiguration",
        "aia(yv)u",
        functionalityTypes, functionalityOptionsSet, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> ConfigurationDBusProxy::changeFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, ChangeFunctionalityConfigurationAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<ConfigurationTypesEnum::FunctionalityTypes, ConfigurationOptions::FuntionalityOptions, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "changeFunctionalityConfiguration",
        "aia(yv)u",
        functionalityTypes, functionalityOptionsSet, handle, 
        std::move(callback));
}
void ConfigurationDBusProxy::requestFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<ConfigurationTypesEnum::FunctionalityTypes, ConfigurationOptionsGetter::FuntionalityOptionsGet, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "requestFunctionalityConfiguration",
        "aia(yv)u",
        functionalityTypes, functionalityOptionsGet, handle, 
        callStatus
        , handle_out, feedback);
}
std::future<CommonAPI::CallStatus> ConfigurationDBusProxy::requestFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, RequestFunctionalityConfigurationAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<ConfigurationTypesEnum::FunctionalityTypes, ConfigurationOptionsGetter::FuntionalityOptionsGet, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "requestFunctionalityConfiguration",
        "aia(yv)u",
        functionalityTypes, functionalityOptionsGet, handle, 
        std::move(callback));
}

void ConfigurationDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 2;
    ownVersionMinor = 0;
}

} // namespace Configuration
} // namespace IVIRadio
