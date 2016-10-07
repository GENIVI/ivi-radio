/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_STUB_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_STUB_H_

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
#include "AdditionalService.h"
#include <CommonAPI/Stub.h>

namespace IVIRadio {
namespace AdditionalService {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service AdditionalService. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class AdditionalServiceStubAdapter: virtual public CommonAPI::StubAdapter, public AdditionalService {
 public:

    /**
     * Sends a broadcast event for Data. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireDataEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::DataService& dataService, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& selectOptions, const AdditionalServiceTypes::DataFormat& format, const AdditionalServiceTypes::DataType& type, const AdditionalServiceTypes::Data& data, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /**
     * Sends a broadcast event for Announcement. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireAnnouncementEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::AnnouncementConfigurations& announcementConfigurations, const AdditionalServiceTypes::arrayAnnouncementStates& announcementStates, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /**
     * Sends a broadcast event for AnnouncementFinished. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireAnnouncementFinishedEvent(const AdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /**
     * Sends a broadcast event for SubscribedServiceOptions. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireSubscribedServiceOptionsEvent(const AdditionalServiceTypes::DataService& dataService, const Types::Types::arrayStationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOptions& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOptions& selectOptions, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
};


/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for AdditionalService.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class AdditionalServiceStubRemoteEvent {
 public:
    virtual ~AdditionalServiceStubRemoteEvent() { }

};


/**
 * Defines the interface that must be implemented by any class that should provide
 * the service AdditionalService to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class AdditionalServiceStub : public CommonAPI::Stub<AdditionalServiceStubAdapter , AdditionalServiceStubRemoteEvent> {
 public:
    virtual ~AdditionalServiceStub() { }


    /// This is the method that will be called on remote calls on the method requestDataService.
    virtual void requestDataService(AdditionalServiceTypes::DataService dataService, Types::Types::StationSelectors selectors, AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions, AdditionalServiceTypesOptions::DataServiceOption serviceOptions, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method requestSubscribedServiceOptions.
    virtual void requestSubscribedServiceOptions(AdditionalServiceTypes::DataService dataservice, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method abort.
    virtual void abort(AdditionalServiceTypes::DataService dataService, Types::Types::StationSelectors stationSelectors, AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions, AdditionalServiceTypesOptions::DataServiceOption dataServiceOption, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    
    /// Sends a broadcast event for Data.
    virtual void fireDataEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::DataService& dataService, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& selectOptions, const AdditionalServiceTypes::DataFormat& format, const AdditionalServiceTypes::DataType& type, const AdditionalServiceTypes::Data& data, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /// Sends a broadcast event for Announcement.
    virtual void fireAnnouncementEvent(const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypes::AnnouncementConfigurations& announcementConfigurations, const AdditionalServiceTypes::arrayAnnouncementStates& announcementStates, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /// Sends a broadcast event for AnnouncementFinished.
    virtual void fireAnnouncementFinishedEvent(const AdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
    /// Sends a broadcast event for SubscribedServiceOptions.
    virtual void fireSubscribedServiceOptionsEvent(const AdditionalServiceTypes::DataService& dataService, const Types::Types::arrayStationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOptions& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOptions& selectOptions, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) = 0;
};

} // namespace AdditionalService
} // namespace IVIRadio

#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_STUB_H_
