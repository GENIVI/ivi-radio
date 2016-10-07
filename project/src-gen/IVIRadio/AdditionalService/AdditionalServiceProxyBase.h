/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_PROXY_BASE_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_PROXY_BASE_H_

#include "AdditionalService.h"
#include <CommonAPI/ByteBuffer.h>
#include <CommonAPI/SerializableVariant.h>
#include <cstdint>
#include <vector>
#include <CommonAPI/InputStream.h>
#include <string>
#include <CommonAPI/SerializableStruct.h>
#include <IVIRadio/AdditionalService/AdditionalServiceTypes.h>
#include <memory>
#include <IVIRadio/AdditionalService/AdditionalServiceTypesOptions.h>
#include <IVIRadio/Types/Types.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/Event.h>
#include <CommonAPI/Proxy.h>
#include <functional>
#include <future>

namespace IVIRadio {
namespace AdditionalService {

class AdditionalServiceProxyBase: virtual public CommonAPI::Proxy {
 public:
    typedef CommonAPI::Event<Types::Types::StationSelectors, AdditionalServiceTypes::DataService, AdditionalServiceTypesOptions::UnifiedServiceOption, AdditionalServiceTypesOptions::DataServiceOption, AdditionalServiceTypes::DataFormat, AdditionalServiceTypes::DataType, AdditionalServiceTypes::Data, uint32_t, Types::Types::ErrorCodes> DataEvent;
    typedef CommonAPI::Event<Types::Types::StationSelectors, AdditionalServiceTypes::AnnouncementConfigurations, AdditionalServiceTypes::arrayAnnouncementStates, uint32_t, Types::Types::ErrorCodes> AnnouncementEvent;
    typedef CommonAPI::Event<AdditionalServiceTypes::Announcement, uint32_t, Types::Types::ErrorCodes> AnnouncementFinishedEvent;
    typedef CommonAPI::Event<AdditionalServiceTypes::DataService, Types::Types::arrayStationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOptions, AdditionalServiceTypesOptions::DataServiceOptions, uint32_t, Types::Types::ErrorCodes> SubscribedServiceOptionsEvent;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> RequestDataServiceAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> RequestSubscribedServiceOptionsAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> AbortAsyncCallback;


    virtual DataEvent& getDataEvent() = 0;
    virtual AnnouncementEvent& getAnnouncementEvent() = 0;
    virtual AnnouncementFinishedEvent& getAnnouncementFinishedEvent() = 0;
    virtual SubscribedServiceOptionsEvent& getSubscribedServiceOptionsEvent() = 0;


    virtual void requestDataService(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> requestDataServiceAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, RequestDataServiceAsyncCallback callback) = 0;

    virtual void requestSubscribedServiceOptions(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> requestSubscribedServiceOptionsAsync(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, RequestSubscribedServiceOptionsAsyncCallback callback) = 0;

    virtual void abort(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> abortAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, AbortAsyncCallback callback) = 0;
};


} // namespace AdditionalService
} // namespace IVIRadio

#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_PROXY_BASE_H_
