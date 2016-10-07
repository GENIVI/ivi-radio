/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_DBUS_PROXY_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_DBUS_PROXY_H_

#include <IVIRadio/AdditionalService/AdditionalServiceProxyBase.h>
#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>

#include <string>

namespace IVIRadio {
namespace AdditionalService {

class AdditionalServiceDBusProxy: virtual public AdditionalServiceProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    AdditionalServiceDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~AdditionalServiceDBusProxy() { }


    virtual DataEvent& getDataEvent();
    virtual AnnouncementEvent& getAnnouncementEvent();
    virtual AnnouncementFinishedEvent& getAnnouncementFinishedEvent();
    virtual SubscribedServiceOptionsEvent& getSubscribedServiceOptionsEvent();


    virtual void requestDataService(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> requestDataServiceAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, RequestDataServiceAsyncCallback callback);

    virtual void requestSubscribedServiceOptions(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> requestSubscribedServiceOptionsAsync(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, RequestSubscribedServiceOptionsAsyncCallback callback);

    virtual void abort(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> abortAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, AbortAsyncCallback callback);
    
    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusEvent<DataEvent> data_;
    CommonAPI::DBus::DBusEvent<AnnouncementEvent> announcement_;
    CommonAPI::DBus::DBusEvent<AnnouncementFinishedEvent> announcementFinished_;
    CommonAPI::DBus::DBusEvent<SubscribedServiceOptionsEvent> subscribedServiceOptions_;
};

} // namespace AdditionalService
} // namespace IVIRadio

#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_DBUS_PROXY_H_
