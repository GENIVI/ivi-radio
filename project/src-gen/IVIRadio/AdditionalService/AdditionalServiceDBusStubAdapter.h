/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_DBUS_STUB_ADAPTER_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_DBUS_STUB_ADAPTER_H_

#include <IVIRadio/AdditionalService/AdditionalServiceStub.h>

#include <CommonAPI/DBus/DBusStubAdapterHelper.h>
#include <CommonAPI/DBus/DBusFactory.h>

namespace IVIRadio {
namespace AdditionalService {

typedef CommonAPI::DBus::DBusStubAdapterHelper<AdditionalServiceStub> AdditionalServiceDBusStubAdapterHelper;

class AdditionalServiceDBusStubAdapter: public AdditionalServiceStubAdapter, public AdditionalServiceDBusStubAdapterHelper {
 public:
    AdditionalServiceDBusStubAdapter(
            const std::string& commonApiAddress,
            const std::string& dbusInterfaceName,
            const std::string& dbusBusName,
            const std::string& dbusObjectPath,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
            const std::shared_ptr<CommonAPI::StubBase>& stub);
    

    void fireDataEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::DataService& dataService, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& selectOptions, const AdditionalServiceTypes::DataFormat& format, const AdditionalServiceTypes::DataType& type, const AdditionalServiceTypes::Data& data, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    void fireAnnouncementEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::AnnouncementConfigurations& announcementConfigurations, const AdditionalServiceTypes::arrayAnnouncementStates& announcementStates, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    void fireAnnouncementFinishedEvent(const AdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    void fireSubscribedServiceOptionsEvent(const AdditionalServiceTypes::DataService& dataService, const Types::Types::arrayStationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOptions& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOptions& selectOptions, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);

 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;
};

} // namespace AdditionalService
} // namespace IVIRadio

#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_DBUS_STUB_ADAPTER_H_
