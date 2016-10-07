/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <IVIRadio/AdditionalService/AdditionalServiceStubDefault.h>

namespace IVIRadio {
namespace AdditionalService {

AdditionalServiceStubDefault::AdditionalServiceStubDefault():
        remoteEventHandler_(this) {
}

AdditionalServiceStubRemoteEvent* AdditionalServiceStubDefault::initStubAdapter(const std::shared_ptr<AdditionalServiceStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void AdditionalServiceStubDefault::requestDataService(AdditionalServiceTypes::DataService dataService, Types::Types::StationSelectors selectors, AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions, AdditionalServiceTypesOptions::DataServiceOption serviceOptions, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}

void AdditionalServiceStubDefault::requestSubscribedServiceOptions(AdditionalServiceTypes::DataService dataservice, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}

void AdditionalServiceStubDefault::abort(AdditionalServiceTypes::DataService dataService, Types::Types::StationSelectors stationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions, AdditionalServiceTypesOptions::DataServiceOption dataServiceOption, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}


void AdditionalServiceStubDefault::fireDataEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::DataService& dataService, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& selectOptions, const AdditionalServiceTypes::DataFormat& format, const AdditionalServiceTypes::DataType& type, const AdditionalServiceTypes::Data& data, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    stubAdapter_->fireDataEvent(stationSelectors, dataService, unifiedOptions, selectOptions, format, type, data, handleOut, errorCode);
}
void AdditionalServiceStubDefault::fireAnnouncementEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::AnnouncementConfigurations& announcementConfigurations, const AdditionalServiceTypes::arrayAnnouncementStates& announcementStates, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    stubAdapter_->fireAnnouncementEvent(stationSelectors, announcementConfigurations, announcementStates, handleOut, errorCode);
}
void AdditionalServiceStubDefault::fireAnnouncementFinishedEvent(const AdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    stubAdapter_->fireAnnouncementFinishedEvent(announcement, handleOut, errorCode);
}
void AdditionalServiceStubDefault::fireSubscribedServiceOptionsEvent(const AdditionalServiceTypes::DataService& dataService, const Types::Types::arrayStationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOptions& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOptions& selectOptions, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    stubAdapter_->fireSubscribedServiceOptionsEvent(dataService, stationSelectors, unifiedOptions, selectOptions, handleOut, errorCode);
}

AdditionalServiceStubDefault::RemoteEventHandler::RemoteEventHandler(AdditionalServiceStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace AdditionalService
} // namespace IVIRadio
