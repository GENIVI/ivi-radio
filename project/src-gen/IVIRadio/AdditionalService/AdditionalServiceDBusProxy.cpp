/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "AdditionalServiceDBusProxy.h"

namespace IVIRadio {
namespace AdditionalService {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createAdditionalServiceDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection) {
    return std::make_shared<AdditionalServiceDBusProxy>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection);
}

__attribute__((constructor)) void registerAdditionalServiceDBusProxy(void) {
    CommonAPI::DBus::DBusFactory::registerProxyFactoryMethod(AdditionalService::getInterfaceId(),
       &createAdditionalServiceDBusProxy);
}

AdditionalServiceDBusProxy::AdditionalServiceDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection):
        CommonAPI::DBus::DBusProxy(commonApiAddress, interfaceName, busName, objectPath, dbusProxyconnection)
,        data_(*this, "Data", "a(uau)i(iu)(yv)ii(yv)ui"),
                        announcement_(*this, "Announcement", "a(uau)a(iiu)aaiui"),
                        announcementFinished_(*this, "AnnouncementFinished", "((uau)i)ui"),
                        subscribedServiceOptions_(*this, "SubscribedServiceOptions", "iaa(uau)a(iu)a(yv)ui")
                 {
}


AdditionalServiceDBusProxy::DataEvent& AdditionalServiceDBusProxy::getDataEvent() {
    return data_;
}
AdditionalServiceDBusProxy::AnnouncementEvent& AdditionalServiceDBusProxy::getAnnouncementEvent() {
    return announcement_;
}
AdditionalServiceDBusProxy::AnnouncementFinishedEvent& AdditionalServiceDBusProxy::getAnnouncementFinishedEvent() {
    return announcementFinished_;
}
AdditionalServiceDBusProxy::SubscribedServiceOptionsEvent& AdditionalServiceDBusProxy::getSubscribedServiceOptionsEvent() {
    return subscribedServiceOptions_;
}

void AdditionalServiceDBusProxy::requestDataService(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<AdditionalServiceTypes::DataService, Types::Types::StationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption, AdditionalServiceTypesOptions::DataServiceOption, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "requestDataService",
        "ia(uau)(iu)(yv)u",
        dataService, selectors, unifiedOptions, serviceOptions, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> AdditionalServiceDBusProxy::requestDataServiceAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, RequestDataServiceAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<AdditionalServiceTypes::DataService, Types::Types::StationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption, AdditionalServiceTypesOptions::DataServiceOption, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "requestDataService",
        "ia(uau)(iu)(yv)u",
        dataService, selectors, unifiedOptions, serviceOptions, handle, 
        std::move(callback));
}
void AdditionalServiceDBusProxy::requestSubscribedServiceOptions(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<AdditionalServiceTypes::DataService, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "requestSubscribedServiceOptions",
        "iu",
        dataservice, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> AdditionalServiceDBusProxy::requestSubscribedServiceOptionsAsync(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, RequestSubscribedServiceOptionsAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<AdditionalServiceTypes::DataService, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "requestSubscribedServiceOptions",
        "iu",
        dataservice, handle, 
        std::move(callback));
}
void AdditionalServiceDBusProxy::abort(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<AdditionalServiceTypes::DataService, Types::Types::StationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption, AdditionalServiceTypesOptions::DataServiceOption, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodWithReply(
        *this,
        "abort",
        "ia(uau)(iu)(yv)u",
        dataService, stationSelectors, unifiedOptions, dataServiceOption, handle, 
        callStatus
        , handleOut, feedback);
}
std::future<CommonAPI::CallStatus> AdditionalServiceDBusProxy::abortAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, AbortAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<AdditionalServiceTypes::DataService, Types::Types::StationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption, AdditionalServiceTypesOptions::DataServiceOption, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<uint32_t, Types::Types::Feedback> >::callMethodAsync(
        *this,
        "abort",
        "ia(uau)(iu)(yv)u",
        dataService, stationSelectors, unifiedOptions, dataServiceOption, handle, 
        std::move(callback));
}

void AdditionalServiceDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 2;
    ownVersionMinor = 0;
}

} // namespace AdditionalService
} // namespace IVIRadio
