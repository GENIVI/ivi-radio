/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "MGEGTunerAdditionalServiceDBusStubAdapter.h"
#include <MGEGTunerAdditionalService/MGEGTunerAdditionalService.h>

namespace MGEGTunerAdditionalService {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createMGEGTunerAdditionalServiceDBusStubAdapter(
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<MGEGTunerAdditionalServiceDBusStubAdapter>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerMGEGTunerAdditionalServiceDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(MGEGTunerAdditionalService::getInterfaceId(),
                                                               &createMGEGTunerAdditionalServiceDBusStubAdapter);
}

MGEGTunerAdditionalServiceDBusStubAdapter::MGEGTunerAdditionalServiceDBusStubAdapter(
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        MGEGTunerAdditionalServiceDBusStubAdapterHelper(commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, dbusConnection, std::dynamic_pointer_cast<MGEGTunerAdditionalServiceStub>(stub)) {
}

const char* MGEGTunerAdditionalServiceDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
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
    MGEGTunerAdditionalServiceStub,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > selectComponentStubDispatcher(&MGEGTunerAdditionalServiceStub::selectComponent, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    MGEGTunerAdditionalServiceStub,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > requestComponentOptionsStubDispatcher(&MGEGTunerAdditionalServiceStub::requestComponentOptions, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    MGEGTunerAdditionalServiceStub,
    std::tuple<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType, uint32_t>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > requestComponentTypeConfigurationStubDispatcher(&MGEGTunerAdditionalServiceStub::requestComponentTypeConfiguration, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    MGEGTunerAdditionalServiceStub,
    std::tuple<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > changeComponentTypeConfigurationStubDispatcher(&MGEGTunerAdditionalServiceStub::changeComponentTypeConfiguration, "ui");


template<>
const MGEGTunerAdditionalServiceDBusStubAdapterHelper::StubDispatcherTable MGEGTunerAdditionalServiceDBusStubAdapterHelper::stubDispatcherTable_ = {
    { { "selectComponent", "uu(yv)" }, &MGEGTunerAdditionalService::selectComponentStubDispatcher },
    { { "requestComponentOptions", "uu" }, &MGEGTunerAdditionalService::requestComponentOptionsStubDispatcher },
    { { "requestComponentTypeConfiguration", "iu" }, &MGEGTunerAdditionalService::requestComponentTypeConfigurationStubDispatcher },
    { { "changeComponentTypeConfiguration", "i(yv)u" }, &MGEGTunerAdditionalService::changeComponentTypeConfigurationStubDispatcher }
};


void MGEGTunerAdditionalServiceDBusStubAdapter::fireGetDataEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& selectParameter, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& data, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>>
            ::sendSignal(
                *this,
                "getData",
                "u(yv)uu",
                componentID, selectParameter, data, handleOut
        );
}
void MGEGTunerAdditionalServiceDBusStubAdapter::fireComponentOptionsEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentOptions& componentOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentOptions, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>>
            ::sendSignal(
                *this,
                "componentOptions",
                "u(yv)u",
                componentID, componentOptions, handleOut
        );
}
void MGEGTunerAdditionalServiceDBusStubAdapter::fireComponentTypeConfigurationEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& componentTypeOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>>
            ::sendSignal(
                *this,
                "componentTypeConfiguration",
                "i(yv)u",
                componentType, componentTypeOptions, handleOut
        );
}
void MGEGTunerAdditionalServiceDBusStubAdapter::fireAnnouncementEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>>
            ::sendSignal(
                *this,
                "announcement",
                "(ui)u",
                announcement, handleOut
        );
}
void MGEGTunerAdditionalServiceDBusStubAdapter::fireAnnouncementFinishedEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut_) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>>
            ::sendSignal(
                *this,
                "announcementFinished",
                "(ui)u",
                announcement, handleOut_
        );
}

} // namespace MGEGTunerAdditionalService
