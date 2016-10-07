/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_DBUS_STUB_ADAPTER_H_
#define MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_DBUS_STUB_ADAPTER_H_

#include <MGEGTunerAdditionalService/MGEGTunerAdditionalServiceStub.h>

#include <CommonAPI/DBus/DBusStubAdapterHelper.h>
#include <CommonAPI/DBus/DBusFactory.h>

namespace MGEGTunerAdditionalService {

typedef CommonAPI::DBus::DBusStubAdapterHelper<MGEGTunerAdditionalServiceStub> MGEGTunerAdditionalServiceDBusStubAdapterHelper;

class MGEGTunerAdditionalServiceDBusStubAdapter: public MGEGTunerAdditionalServiceStubAdapter, public MGEGTunerAdditionalServiceDBusStubAdapterHelper {
 public:
    MGEGTunerAdditionalServiceDBusStubAdapter(
            const std::string& commonApiAddress,
            const std::string& dbusInterfaceName,
            const std::string& dbusBusName,
            const std::string& dbusObjectPath,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
            const std::shared_ptr<CommonAPI::StubBase>& stub);
    

    void fireGetDataEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& selectParameter, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& data, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut);
    void fireComponentOptionsEvent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentOptions& componentOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut);
    void fireComponentTypeConfigurationEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& componentTypeOptions, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut);
    void fireAnnouncementEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut);
    void fireAnnouncementFinishedEvent(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_Announcement& announcement, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut_);

 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;
};

} // namespace MGEGTunerAdditionalService

#endif // MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_DBUS_STUB_ADAPTER_H_
