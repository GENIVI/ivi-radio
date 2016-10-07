/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_STUB_H_
#define MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_STUB_H_

#include <CommonAPI/SerializableVariant.h>
#include <cstdint>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <MGEGTunerTypes/MGEGTunerTypes.h>
#include <MGEGTunerAdditionalServiceTypes/MGEGTunerAdditionalServiceTypes.h>
#include <CommonAPI/OutputStream.h>
#include <memory>
#include "MGEGTunerAdditionalService.h"
#include <CommonAPI/Stub.h>

namespace MGEGTunerAdditionalService {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service MGEGTunerAdditionalService. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class MGEGTunerAdditionalServiceStubAdapter: virtual public CommonAPI::StubAdapter, public MGEGTunerAdditionalService {
 public:

    /**
     * Sends a broadcast event for getData. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireGetDataEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& selectParameter, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& data, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) = 0;
    /**
     * Sends a broadcast event for componentOptions. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireComponentOptionsEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentOptions& componentOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) = 0;
    /**
     * Sends a broadcast event for componentTypeConfiguration. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireComponentTypeConfigurationEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& componentTypeOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) = 0;
    /**
     * Sends a broadcast event for announcement. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireAnnouncementEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) = 0;
    /**
     * Sends a broadcast event for announcementFinished. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireAnnouncementFinishedEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut_) = 0;
};


/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for MGEGTunerAdditionalService.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class MGEGTunerAdditionalServiceStubRemoteEvent {
 public:
    virtual ~MGEGTunerAdditionalServiceStubRemoteEvent() { }

};


/**
 * Defines the interface that must be implemented by any class that should provide
 * the service MGEGTunerAdditionalService to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class MGEGTunerAdditionalServiceStub : public CommonAPI::Stub<MGEGTunerAdditionalServiceStubAdapter , MGEGTunerAdditionalServiceStubRemoteEvent> {
 public:
    virtual ~MGEGTunerAdditionalServiceStub() { }


    /// This is the method that will be called on remote calls on the method selectComponent.
    virtual void selectComponent(MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 componentID, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter componentParameter, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method requestComponentOptions.
    virtual void requestComponentOptions(MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 componentID, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method requestComponentTypeConfiguration.
    virtual void requestComponentTypeConfiguration(MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType compentType, uint32_t handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method changeComponentTypeConfiguration.
    virtual void changeComponentTypeConfiguration(MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType componentType, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions options, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 handle, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    
    /// Sends a broadcast event for getData.
    virtual void fireGetDataEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& selectParameter, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& data, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) = 0;
    /// Sends a broadcast event for componentOptions.
    virtual void fireComponentOptionsEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentOptions& componentOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) = 0;
    /// Sends a broadcast event for componentTypeConfiguration.
    virtual void fireComponentTypeConfigurationEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& componentTypeOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) = 0;
    /// Sends a broadcast event for announcement.
    virtual void fireAnnouncementEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut) = 0;
    /// Sends a broadcast event for announcementFinished.
    virtual void fireAnnouncementFinishedEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut_) = 0;
};

} // namespace MGEGTunerAdditionalService

#endif // MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_STUB_H_
