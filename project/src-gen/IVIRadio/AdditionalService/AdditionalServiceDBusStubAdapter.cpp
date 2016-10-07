/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "AdditionalServiceDBusStubAdapter.h"
#include <IVIRadio/AdditionalService/AdditionalService.h>

namespace IVIRadio {
namespace AdditionalService {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createAdditionalServiceDBusStubAdapter(
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<AdditionalServiceDBusStubAdapter>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerAdditionalServiceDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(AdditionalService::getInterfaceId(),
                                                               &createAdditionalServiceDBusStubAdapter);
}

AdditionalServiceDBusStubAdapter::AdditionalServiceDBusStubAdapter(
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        AdditionalServiceDBusStubAdapterHelper(commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, dbusConnection, std::dynamic_pointer_cast<AdditionalServiceStub>(stub)) {
}

const char* AdditionalServiceDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
    return
        "<signal name=\"Data\">\n"
            "<arg name=\"stationSelectors\" type=\"a(uau)\" />\n"
            "<arg name=\"dataService\" type=\"i\" />\n"
            "<arg name=\"unifiedOptions\" type=\"(iu)\" />\n"
            "<arg name=\"selectOptions\" type=\"(yv)\" />\n"
            "<arg name=\"format\" type=\"i\" />\n"
            "<arg name=\"type\" type=\"i\" />\n"
            "<arg name=\"data\" type=\"(yv)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
            "<arg name=\"errorCode\" type=\"i\" />\n"
        "</signal>\n"
        "<signal name=\"Announcement\">\n"
            "<arg name=\"stationSelectors\" type=\"a(uau)\" />\n"
            "<arg name=\"announcementConfigurations\" type=\"a(iiu)\" />\n"
            "<arg name=\"announcementStates\" type=\"aai\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
            "<arg name=\"errorCode\" type=\"i\" />\n"
        "</signal>\n"
        "<signal name=\"AnnouncementFinished\">\n"
            "<arg name=\"announcement\" type=\"((uau)i)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
            "<arg name=\"errorCode\" type=\"i\" />\n"
        "</signal>\n"
        "<signal name=\"SubscribedServiceOptions\">\n"
            "<arg name=\"dataService\" type=\"i\" />\n"
            "<arg name=\"stationSelectors\" type=\"aa(uau)\" />\n"
            "<arg name=\"unifiedOptions\" type=\"a(iu)\" />\n"
            "<arg name=\"selectOptions\" type=\"a(yv)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
            "<arg name=\"errorCode\" type=\"i\" />\n"
        "</signal>\n"
        "<method name=\"requestDataService\">\n"
            "<arg name=\"dataService\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"selectors\" type=\"a(uau)\" direction=\"in\" />\n"
            "<arg name=\"unifiedOptions\" type=\"(iu)\" direction=\"in\" />\n"
            "<arg name=\"serviceOptions\" type=\"(yv)\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"requestSubscribedServiceOptions\">\n"
            "<arg name=\"dataservice\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"abort\">\n"
            "<arg name=\"dataService\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"stationSelectors\" type=\"a(uau)\" direction=\"in\" />\n"
            "<arg name=\"unifiedOptions\" type=\"(iu)\" direction=\"in\" />\n"
            "<arg name=\"dataServiceOption\" type=\"(yv)\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
    ;
}



static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    AdditionalServiceStub,
    std::tuple<AdditionalServiceTypes::DataService, Types::Types::StationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption, AdditionalServiceTypesOptions::DataServiceOption, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > requestDataServiceStubDispatcher(&AdditionalServiceStub::requestDataService, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    AdditionalServiceStub,
    std::tuple<AdditionalServiceTypes::DataService, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > requestSubscribedServiceOptionsStubDispatcher(&AdditionalServiceStub::requestSubscribedServiceOptions, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    AdditionalServiceStub,
    std::tuple<AdditionalServiceTypes::DataService, Types::Types::StationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption, AdditionalServiceTypesOptions::DataServiceOption, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > abortStubDispatcher(&AdditionalServiceStub::abort, "ui");


template<>
const AdditionalServiceDBusStubAdapterHelper::StubDispatcherTable AdditionalServiceDBusStubAdapterHelper::stubDispatcherTable_ = {
    { { "requestDataService", "ia(uau)(iu)(yv)u" }, &IVIRadio::AdditionalService::requestDataServiceStubDispatcher },
    { { "requestSubscribedServiceOptions", "iu" }, &IVIRadio::AdditionalService::requestSubscribedServiceOptionsStubDispatcher },
    { { "abort", "ia(uau)(iu)(yv)u" }, &IVIRadio::AdditionalService::abortStubDispatcher }
};


void AdditionalServiceDBusStubAdapter::fireDataEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::DataService& dataService, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& selectOptions, const AdditionalServiceTypes::DataFormat& format, const AdditionalServiceTypes::DataType& type, const AdditionalServiceTypes::Data& data, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::StationSelectors, AdditionalServiceTypes::DataService, AdditionalServiceTypesOptions::UnifiedServiceOption, AdditionalServiceTypesOptions::DataServiceOption, AdditionalServiceTypes::DataFormat, AdditionalServiceTypes::DataType, AdditionalServiceTypes::Data, uint32_t, Types::Types::ErrorCodes>>
            ::sendSignal(
                *this,
                "Data",
                "a(uau)i(iu)(yv)ii(yv)ui",
                stationSelectors, dataService, unifiedOptions, selectOptions, format, type, data, handleOut, errorCode
        );
}
void AdditionalServiceDBusStubAdapter::fireAnnouncementEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::AnnouncementConfigurations& announcementConfigurations, const AdditionalServiceTypes::arrayAnnouncementStates& announcementStates, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<Types::Types::StationSelectors, AdditionalServiceTypes::AnnouncementConfigurations, AdditionalServiceTypes::arrayAnnouncementStates, uint32_t, Types::Types::ErrorCodes>>
            ::sendSignal(
                *this,
                "Announcement",
                "a(uau)a(iiu)aaiui",
                stationSelectors, announcementConfigurations, announcementStates, handleOut, errorCode
        );
}
void AdditionalServiceDBusStubAdapter::fireAnnouncementFinishedEvent(const AdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<AdditionalServiceTypes::Announcement, uint32_t, Types::Types::ErrorCodes>>
            ::sendSignal(
                *this,
                "AnnouncementFinished",
                "((uau)i)ui",
                announcement, handleOut, errorCode
        );
}
void AdditionalServiceDBusStubAdapter::fireSubscribedServiceOptionsEvent(const AdditionalServiceTypes::DataService& dataService, const Types::Types::arrayStationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOptions& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOptions& selectOptions, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<AdditionalServiceTypes::DataService, Types::Types::arrayStationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOptions, AdditionalServiceTypesOptions::DataServiceOptions, uint32_t, Types::Types::ErrorCodes>>
            ::sendSignal(
                *this,
                "SubscribedServiceOptions",
                "iaa(uau)a(iu)a(yv)ui",
                dataService, stationSelectors, unifiedOptions, selectOptions, handleOut, errorCode
        );
}

} // namespace AdditionalService
} // namespace IVIRadio
