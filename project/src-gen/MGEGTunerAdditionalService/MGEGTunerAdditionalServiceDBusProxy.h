/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_DBUS_PROXY_H_
#define MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_DBUS_PROXY_H_

#include <MGEGTunerAdditionalService/MGEGTunerAdditionalServiceProxyBase.h>
#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>

#include <string>

namespace MGEGTunerAdditionalService {

class MGEGTunerAdditionalServiceDBusProxy: virtual public MGEGTunerAdditionalServiceProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    MGEGTunerAdditionalServiceDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~MGEGTunerAdditionalServiceDBusProxy() { }


    virtual GetDataEvent& getGetDataEvent();
    virtual ComponentOptionsEvent& getComponentOptionsEvent();
    virtual ComponentTypeConfigurationEvent& getComponentTypeConfigurationEvent();
    virtual AnnouncementEvent& getAnnouncementEvent();
    virtual AnnouncementFinishedEvent& getAnnouncementFinishedEvent();


    virtual void selectComponent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> selectComponentAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, SelectComponentAsyncCallback callback);

    virtual void requestComponentOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> requestComponentOptionsAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, RequestComponentOptionsAsyncCallback callback);

    virtual void requestComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> requestComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback);

    virtual void changeComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> changeComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ChangeComponentTypeConfigurationAsyncCallback callback);
    
    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusEvent<GetDataEvent> getData_;
    CommonAPI::DBus::DBusEvent<ComponentOptionsEvent> componentOptions_;
    CommonAPI::DBus::DBusEvent<ComponentTypeConfigurationEvent> componentTypeConfiguration_;
    CommonAPI::DBus::DBusEvent<AnnouncementEvent> announcement_;
    CommonAPI::DBus::DBusEvent<AnnouncementFinishedEvent> announcementFinished_;
};

} // namespace MGEGTunerAdditionalService

#endif // MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_DBUS_PROXY_H_
