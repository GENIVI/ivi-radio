/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "ConfigurationDBusStubAdapter.h"
#include <IVIRadio/Configuration/Configuration.h>

namespace IVIRadio {
namespace Configuration {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createConfigurationDBusStubAdapter(
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<ConfigurationDBusStubAdapter>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerConfigurationDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(Configuration::getInterfaceId(),
                                                               &createConfigurationDBusStubAdapter);
}

ConfigurationDBusStubAdapter::ConfigurationDBusStubAdapter(
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        ConfigurationDBusStubAdapterHelper(commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, dbusConnection, std::dynamic_pointer_cast<ConfigurationStub>(stub)) {
}

const char* ConfigurationDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
    return
        "<signal name=\"functionalityConfiguration\">\n"
            "<arg name=\"functionalityTypes\" type=\"ai\" />\n"
            "<arg name=\"functionalityOptions\" type=\"a(yv)\" />\n"
            "<arg name=\"handle_out\" type=\"u\" />\n"
            "<arg name=\"errorCode\" type=\"i\" />\n"
        "</signal>\n"
        "<method name=\"changeFunctionalityConfiguration\">\n"
            "<arg name=\"functionalityTypes\" type=\"ai\" direction=\"in\" />\n"
            "<arg name=\"functionalityOptionsSet\" type=\"a(yv)\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"requestFunctionalityConfiguration\">\n"
            "<arg name=\"functionalityTypes\" type=\"ai\" direction=\"in\" />\n"
            "<arg name=\"functionalityOptionsGet\" type=\"a(yv)\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle_out\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
    ;
}



static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ConfigurationStub,
    std::tuple<ConfigurationTypesEnum::FunctionalityTypes, ConfigurationOptions::FuntionalityOptions, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > changeFunctionalityConfigurationStubDispatcher(&ConfigurationStub::changeFunctionalityConfiguration, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ConfigurationStub,
    std::tuple<ConfigurationTypesEnum::FunctionalityTypes, ConfigurationOptionsGetter::FuntionalityOptionsGet, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > requestFunctionalityConfigurationStubDispatcher(&ConfigurationStub::requestFunctionalityConfiguration, "ui");


template<>
const ConfigurationDBusStubAdapterHelper::StubDispatcherTable ConfigurationDBusStubAdapterHelper::stubDispatcherTable_ = {
    { { "changeFunctionalityConfiguration", "aia(yv)u" }, &IVIRadio::Configuration::changeFunctionalityConfigurationStubDispatcher },
    { { "requestFunctionalityConfiguration", "aia(yv)u" }, &IVIRadio::Configuration::requestFunctionalityConfigurationStubDispatcher }
};


void ConfigurationDBusStubAdapter::fireFunctionalityConfigurationEvent(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptions, const uint32_t& handle_out, const Types::Types::ErrorCodes& errorCode) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<ConfigurationTypesEnum::FunctionalityTypes, ConfigurationOptions::FuntionalityOptions, uint32_t, Types::Types::ErrorCodes>>
            ::sendSignal(
                *this,
                "functionalityConfiguration",
                "aia(yv)ui",
                functionalityTypes, functionalityOptions, handle_out, errorCode
        );
}

} // namespace Configuration
} // namespace IVIRadio
