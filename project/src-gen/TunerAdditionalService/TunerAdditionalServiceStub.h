/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERADDITIONALSERVICE_Tuner_Additional_Service_STUB_H_
#define TUNERADDITIONALSERVICE_Tuner_Additional_Service_STUB_H_

#include <CommonAPI/SerializableVariant.h>
#include <cstdint>
#include <TunerAdditionalServiceTypes/TunerAdditionalServiceTypes.h>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <TunerTypes/TunerTypes.h>
#include <CommonAPI/OutputStream.h>
#include <memory>
#include "TunerAdditionalService.h"
#include <CommonAPI/Stub.h>

namespace TunerAdditionalService {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service TunerAdditionalService. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class TunerAdditionalServiceStubAdapter: virtual public CommonAPI::StubAdapter, public TunerAdditionalService {
 public:

    /**
     * Sends a broadcast event for getData. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireGetDataEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& selectParameter, const uint32_t& data, const uint32_t& handleOut) = 0;
    /**
     * Sends a broadcast event for componentOptions. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireComponentOptionsEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions& componentOptions, const uint32_t& handleOut) = 0;
    /**
     * Sends a broadcast event for componentTypeConfiguration. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireComponentTypeConfigurationEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions, const uint32_t& handleOut) = 0;
    /**
     * Sends a broadcast event for announcement. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireAnnouncementEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut) = 0;
    /**
     * Sends a broadcast event for announcementFinished. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireAnnouncementFinishedEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut_) = 0;
};


/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for TunerAdditionalService.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TunerAdditionalServiceStubRemoteEvent {
 public:
    virtual ~TunerAdditionalServiceStubRemoteEvent() { }

};


/**
 * Defines the interface that must be implemented by any class that should provide
 * the service TunerAdditionalService to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class TunerAdditionalServiceStub : public CommonAPI::Stub<TunerAdditionalServiceStubAdapter , TunerAdditionalServiceStubRemoteEvent> {
 public:
    virtual ~TunerAdditionalServiceStub() { }


    /// This is the method that will be called on remote calls on the method selectComponent.
    virtual void selectComponent(uint32_t componentID, uint32_t handle, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter componentParameter, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method requestComponentOptions.
    virtual void requestComponentOptions(uint32_t componentID, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method requestComponentTypeConfiguration.
    virtual void requestComponentTypeConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType compentType, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method changeComponentTypeConfiguration.
    virtual void changeComponentTypeConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType componentType, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions options, uint32_t handle, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    
    /// Sends a broadcast event for getData.
    virtual void fireGetDataEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& selectParameter, const uint32_t& data, const uint32_t& handleOut) = 0;
    /// Sends a broadcast event for componentOptions.
    virtual void fireComponentOptionsEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions& componentOptions, const uint32_t& handleOut) = 0;
    /// Sends a broadcast event for componentTypeConfiguration.
    virtual void fireComponentTypeConfigurationEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions, const uint32_t& handleOut) = 0;
    /// Sends a broadcast event for announcement.
    virtual void fireAnnouncementEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut) = 0;
    /// Sends a broadcast event for announcementFinished.
    virtual void fireAnnouncementFinishedEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut_) = 0;
};

} // namespace TunerAdditionalService

#endif // TUNERADDITIONALSERVICE_Tuner_Additional_Service_STUB_H_
