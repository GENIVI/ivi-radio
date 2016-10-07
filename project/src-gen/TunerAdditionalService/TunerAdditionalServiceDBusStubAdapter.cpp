/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "TunerAdditionalServiceDBusStubAdapter.h"
#include <TunerAdditionalService/TunerAdditionalService.h>

namespace TunerAdditionalService {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createTunerAdditionalServiceDBusStubAdapter(
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<TunerAdditionalServiceDBusStubAdapter>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerTunerAdditionalServiceDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(TunerAdditionalService::getInterfaceId(),
                                                               &createTunerAdditionalServiceDBusStubAdapter);
}

TunerAdditionalServiceDBusStubAdapter::TunerAdditionalServiceDBusStubAdapter(
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        TunerAdditionalServiceDBusStubAdapterHelper(commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, dbusConnection, std::dynamic_pointer_cast<TunerAdditionalServiceStub>(stub)) {
}

const char* TunerAdditionalServiceDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
    return
        "<signal name=\"getData\">\n"
            "<arg name=\"componentID\" type=\"u\" />\n"
            "<arg name=\"selectParameter\" type=\"(yv)\" />\n"
            "<arg name=\"data\" type=\"u\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
        "</signal>\n"
        "<signal name=\"componentOptions\">\n"
            "<arg name=\"componentID\" type=\"u\" />\n"
            "<arg name=\"componentOptions\" type=\"(yv)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
        "</signal>\n"
        "<signal name=\"componentTypeConfiguration\">\n"
            "<arg name=\"componentType\" type=\"i\" />\n"
            "<arg name=\"componentTypeOptions\" type=\"(yv)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
        "</signal>\n"
        "<signal name=\"announcement\">\n"
            "<arg name=\"announcement\" type=\"(ui)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
        "</signal>\n"
        "<signal name=\"announcementFinished\">\n"
            "<arg name=\"announcement\" type=\"(ui)\" />\n"
            "<arg name=\"handleOut_\" type=\"u\" />\n"
        "</signal>\n"
        "<method name=\"selectComponent\">\n"
            "<arg name=\"componentID\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"componentParameter\" type=\"(yv)\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"requestComponentOptions\">\n"
            "<arg name=\"componentID\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"requestComponentTypeConfiguration\">\n"
            "<arg name=\"compentType\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"changeComponentTypeConfiguration\">\n"
            "<arg name=\"componentType\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"options\" type=\"(yv)\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
    ;
}



static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerAdditionalServiceStub,
    std::tuple<uint32_t, uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > selectComponentStubDispatcher(&TunerAdditionalServiceStub::selectComponent, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerAdditionalServiceStub,
    std::tuple<uint32_t, uint32_t>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > requestComponentOptionsStubDispatcher(&TunerAdditionalServiceStub::requestComponentOptions, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerAdditionalServiceStub,
    std::tuple<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType, uint32_t>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > requestComponentTypeConfigurationStubDispatcher(&TunerAdditionalServiceStub::requestComponentTypeConfiguration, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerAdditionalServiceStub,
    std::tuple<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions, uint32_t>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > changeComponentTypeConfigurationStubDispatcher(&TunerAdditionalServiceStub::changeComponentTypeConfiguration, "ui");


template<>
const TunerAdditionalServiceDBusStubAdapterHelper::StubDispatcherTable TunerAdditionalServiceDBusStubAdapterHelper::stubDispatcherTable_ = {
    { { "selectComponent", "uu(yv)" }, &TunerAdditionalService::selectComponentStubDispatcher },
    { { "requestComponentOptions", "uu" }, &TunerAdditionalService::requestComponentOptionsStubDispatcher },
    { { "requestComponentTypeConfiguration", "iu" }, &TunerAdditionalService::requestComponentTypeConfigurationStubDispatcher },
    { { "changeComponentTypeConfiguration", "i(yv)u" }, &TunerAdditionalService::changeComponentTypeConfigurationStubDispatcher }
};


void TunerAdditionalServiceDBusStubAdapter::fireGetDataEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& selectParameter, const uint32_t& data, const uint32_t& handleOut) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter, uint32_t, uint32_t>>
            ::sendSignal(
                *this,
                "getData",
                "u(yv)uu",
                componentID, selectParameter, data, handleOut
        );
}
void TunerAdditionalServiceDBusStubAdapter::fireComponentOptionsEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions& componentOptions, const uint32_t& handleOut) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions, uint32_t>>
            ::sendSignal(
                *this,
                "componentOptions",
                "u(yv)u",
                componentID, componentOptions, handleOut
        );
}
void TunerAdditionalServiceDBusStubAdapter::fireComponentTypeConfigurationEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions, const uint32_t& handleOut) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions, uint32_t>>
            ::sendSignal(
                *this,
                "componentTypeConfiguration",
                "i(yv)u",
                componentType, componentTypeOptions, handleOut
        );
}
void TunerAdditionalServiceDBusStubAdapter::fireAnnouncementEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement, uint32_t>>
            ::sendSignal(
                *this,
                "announcement",
                "(ui)u",
                announcement, handleOut
        );
}
void TunerAdditionalServiceDBusStubAdapter::fireAnnouncementFinishedEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut_) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement, uint32_t>>
            ::sendSignal(
                *this,
                "announcementFinished",
                "(ui)u",
                announcement, handleOut_
        );
}

} // namespace TunerAdditionalService
