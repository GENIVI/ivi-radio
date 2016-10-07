/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERADDITIONALSERVICE_Tuner_Additional_Service_DBUS_PROXY_H_
#define TUNERADDITIONALSERVICE_Tuner_Additional_Service_DBUS_PROXY_H_

#include <TunerAdditionalService/TunerAdditionalServiceProxyBase.h>
#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>

#include <string>

namespace TunerAdditionalService {

class TunerAdditionalServiceDBusProxy: virtual public TunerAdditionalServiceProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    TunerAdditionalServiceDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~TunerAdditionalServiceDBusProxy() { }


    virtual GetDataEvent& getGetDataEvent();
    virtual ComponentOptionsEvent& getComponentOptionsEvent();
    virtual ComponentTypeConfigurationEvent& getComponentTypeConfigurationEvent();
    virtual AnnouncementEvent& getAnnouncementEvent();
    virtual AnnouncementFinishedEvent& getAnnouncementFinishedEvent();


    virtual void selectComponent(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> selectComponentAsync(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, SelectComponentAsyncCallback callback);

    virtual void requestComponentOptions(const uint32_t& componentID, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> requestComponentOptionsAsync(const uint32_t& componentID, const uint32_t& handle, RequestComponentOptionsAsyncCallback callback);

    virtual void requestComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> requestComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback);

    virtual void changeComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> changeComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, ChangeComponentTypeConfigurationAsyncCallback callback);
    
    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusEvent<GetDataEvent> getData_;
    CommonAPI::DBus::DBusEvent<ComponentOptionsEvent> componentOptions_;
    CommonAPI::DBus::DBusEvent<ComponentTypeConfigurationEvent> componentTypeConfiguration_;
    CommonAPI::DBus::DBusEvent<AnnouncementEvent> announcement_;
    CommonAPI::DBus::DBusEvent<AnnouncementFinishedEvent> announcementFinished_;
};

} // namespace TunerAdditionalService

#endif // TUNERADDITIONALSERVICE_Tuner_Additional_Service_DBUS_PROXY_H_
