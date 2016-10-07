/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_PROXY_BASE_H_
#define MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_PROXY_BASE_H_

#include "MGEGTunerAdditionalService.h"
#include <CommonAPI/SerializableVariant.h>
#include <cstdint>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <MGEGTunerTypes/MGEGTunerTypes.h>
#include <MGEGTunerAdditionalServiceTypes/MGEGTunerAdditionalServiceTypes.h>
#include <CommonAPI/OutputStream.h>
#include <memory>
#include <CommonAPI/Event.h>
#include <CommonAPI/Proxy.h>
#include <functional>
#include <future>

namespace MGEGTunerAdditionalService {

class MGEGTunerAdditionalServiceProxyBase: virtual public CommonAPI::Proxy {
 public:
    typedef CommonAPI::Event<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32> GetDataEvent;
    typedef CommonAPI::Event<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentOptions, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32> ComponentOptionsEvent;
    typedef CommonAPI::Event<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType, MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32> ComponentTypeConfigurationEvent;
    typedef CommonAPI::Event<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32> AnnouncementEvent;
    typedef CommonAPI::Event<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32> AnnouncementFinishedEvent;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> SelectComponentAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> RequestComponentOptionsAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> RequestComponentTypeConfigurationAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> ChangeComponentTypeConfigurationAsyncCallback;


    virtual GetDataEvent& getGetDataEvent() = 0;
    virtual ComponentOptionsEvent& getComponentOptionsEvent() = 0;
    virtual ComponentTypeConfigurationEvent& getComponentTypeConfigurationEvent() = 0;
    virtual AnnouncementEvent& getAnnouncementEvent() = 0;
    virtual AnnouncementFinishedEvent& getAnnouncementFinishedEvent() = 0;


    virtual void selectComponent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> selectComponentAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, SelectComponentAsyncCallback callback) = 0;

    virtual void requestComponentOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> requestComponentOptionsAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, RequestComponentOptionsAsyncCallback callback) = 0;

    virtual void requestComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> requestComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback) = 0;

    virtual void changeComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> changeComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ChangeComponentTypeConfigurationAsyncCallback callback) = 0;
};


} // namespace MGEGTunerAdditionalService

#endif // MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_PROXY_BASE_H_
