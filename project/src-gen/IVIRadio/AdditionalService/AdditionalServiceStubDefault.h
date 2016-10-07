/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_STUB_DEFAULT_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_STUB_DEFAULT_H_

#include <IVIRadio/AdditionalService/AdditionalServiceStub.h>

namespace IVIRadio {
namespace AdditionalService {

/**
 * Provides a default implementation for AdditionalServiceStubRemoteEvent and
 * AdditionalServiceStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 * 
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class AdditionalServiceStubDefault : public AdditionalServiceStub {
 public:
    AdditionalServiceStubDefault();

    AdditionalServiceStubRemoteEvent* initStubAdapter(const std::shared_ptr<AdditionalServiceStubAdapter>& stubAdapter);


    virtual void requestDataService(AdditionalServiceTypes::DataService dataService, Types::Types::StationSelectors selectors, AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions, AdditionalServiceTypesOptions::DataServiceOption serviceOptions, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    virtual void requestSubscribedServiceOptions(AdditionalServiceTypes::DataService dataservice, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    virtual void abort(AdditionalServiceTypes::DataService dataService, Types::Types::StationSelectors stationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions, AdditionalServiceTypesOptions::DataServiceOption dataServiceOption, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    
    virtual void fireDataEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::DataService& dataService, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& selectOptions, const AdditionalServiceTypes::DataFormat& format, const AdditionalServiceTypes::DataType& type, const AdditionalServiceTypes::Data& data, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    virtual void fireAnnouncementEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::AnnouncementConfigurations& announcementConfigurations, const AdditionalServiceTypes::arrayAnnouncementStates& announcementStates, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    virtual void fireAnnouncementFinishedEvent(const AdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    virtual void fireSubscribedServiceOptionsEvent(const AdditionalServiceTypes::DataService& dataService, const Types::Types::arrayStationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOptions& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOptions& selectOptions, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);

 protected:
    
 private:
    class RemoteEventHandler: public AdditionalServiceStubRemoteEvent {
     public:
        RemoteEventHandler(AdditionalServiceStubDefault* defaultStub);


     private:
        AdditionalServiceStubDefault* defaultStub_;
    };

    RemoteEventHandler remoteEventHandler_;
    std::shared_ptr<AdditionalServiceStubAdapter> stubAdapter_;

};

} // namespace AdditionalService
} // namespace IVIRadio

#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_STUB_DEFAULT_H_
