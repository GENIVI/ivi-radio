/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERADDITIONALSERVICE_Tuner_Additional_Service_PROXY_BASE_H_
#define TUNERADDITIONALSERVICE_Tuner_Additional_Service_PROXY_BASE_H_

#include "TunerAdditionalService.h"
#include <CommonAPI/SerializableVariant.h>
#include <cstdint>
#include <TunerAdditionalServiceTypes/TunerAdditionalServiceTypes.h>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <TunerTypes/TunerTypes.h>
#include <CommonAPI/OutputStream.h>
#include <memory>
#include <CommonAPI/Event.h>
#include <CommonAPI/Proxy.h>
#include <functional>
#include <future>

namespace TunerAdditionalService {

class TunerAdditionalServiceProxyBase: virtual public CommonAPI::Proxy {
 public:
    typedef CommonAPI::Event<uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter, uint32_t, uint32_t> GetDataEvent;
    typedef CommonAPI::Event<uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions, uint32_t> ComponentOptionsEvent;
    typedef CommonAPI::Event<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions, uint32_t> ComponentTypeConfigurationEvent;
    typedef CommonAPI::Event<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement, uint32_t> AnnouncementEvent;
    typedef CommonAPI::Event<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement, uint32_t> AnnouncementFinishedEvent;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> SelectComponentAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> RequestComponentOptionsAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> RequestComponentTypeConfigurationAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> ChangeComponentTypeConfigurationAsyncCallback;


    virtual GetDataEvent& getGetDataEvent() = 0;
    virtual ComponentOptionsEvent& getComponentOptionsEvent() = 0;
    virtual ComponentTypeConfigurationEvent& getComponentTypeConfigurationEvent() = 0;
    virtual AnnouncementEvent& getAnnouncementEvent() = 0;
    virtual AnnouncementFinishedEvent& getAnnouncementFinishedEvent() = 0;


    virtual void selectComponent(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> selectComponentAsync(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, SelectComponentAsyncCallback callback) = 0;

    virtual void requestComponentOptions(const uint32_t& componentID, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> requestComponentOptionsAsync(const uint32_t& componentID, const uint32_t& handle, RequestComponentOptionsAsyncCallback callback) = 0;

    virtual void requestComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> requestComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback) = 0;

    virtual void changeComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> changeComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, ChangeComponentTypeConfigurationAsyncCallback callback) = 0;
};


} // namespace TunerAdditionalService

#endif // TUNERADDITIONALSERVICE_Tuner_Additional_Service_PROXY_BASE_H_
