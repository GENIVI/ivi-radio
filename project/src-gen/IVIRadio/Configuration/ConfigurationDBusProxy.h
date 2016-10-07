/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_DBUS_PROXY_H_
#define IVIRADIO_CONFIGURATION_Configuration_DBUS_PROXY_H_

#include <IVIRadio/Configuration/ConfigurationProxyBase.h>
#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>

#include <string>

namespace IVIRadio {
namespace Configuration {

class ConfigurationDBusProxy: virtual public ConfigurationProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    ConfigurationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~ConfigurationDBusProxy() { }


    virtual FunctionalityConfigurationEvent& getFunctionalityConfigurationEvent();


    virtual void changeFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> changeFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, ChangeFunctionalityConfigurationAsyncCallback callback);

    virtual void requestFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> requestFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, RequestFunctionalityConfigurationAsyncCallback callback);
    
    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusEvent<FunctionalityConfigurationEvent> functionalityConfiguration_;
};

} // namespace Configuration
} // namespace IVIRadio

#endif // IVIRADIO_CONFIGURATION_Configuration_DBUS_PROXY_H_
