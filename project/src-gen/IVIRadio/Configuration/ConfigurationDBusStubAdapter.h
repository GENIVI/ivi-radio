/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_DBUS_STUB_ADAPTER_H_
#define IVIRADIO_CONFIGURATION_Configuration_DBUS_STUB_ADAPTER_H_

#include <IVIRadio/Configuration/ConfigurationStub.h>

#include <CommonAPI/DBus/DBusStubAdapterHelper.h>
#include <CommonAPI/DBus/DBusFactory.h>

namespace IVIRadio {
namespace Configuration {

typedef CommonAPI::DBus::DBusStubAdapterHelper<ConfigurationStub> ConfigurationDBusStubAdapterHelper;

class ConfigurationDBusStubAdapter: public ConfigurationStubAdapter, public ConfigurationDBusStubAdapterHelper {
 public:
    ConfigurationDBusStubAdapter(
            const std::string& commonApiAddress,
            const std::string& dbusInterfaceName,
            const std::string& dbusBusName,
            const std::string& dbusObjectPath,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
            const std::shared_ptr<CommonAPI::StubBase>& stub);
    

    void fireFunctionalityConfigurationEvent(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptions, const uint32_t& handle_out, const Types::Types::ErrorCodes& errorCode);

 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;
};

} // namespace Configuration
} // namespace IVIRadio

#endif // IVIRADIO_CONFIGURATION_Configuration_DBUS_STUB_ADAPTER_H_
