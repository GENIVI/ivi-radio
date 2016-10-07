/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERADDITIONALSERVICE_Tuner_Additional_Service_DBUS_STUB_ADAPTER_H_
#define TUNERADDITIONALSERVICE_Tuner_Additional_Service_DBUS_STUB_ADAPTER_H_

#include <TunerAdditionalService/TunerAdditionalServiceStub.h>

#include <CommonAPI/DBus/DBusStubAdapterHelper.h>
#include <CommonAPI/DBus/DBusFactory.h>

namespace TunerAdditionalService {

typedef CommonAPI::DBus::DBusStubAdapterHelper<TunerAdditionalServiceStub> TunerAdditionalServiceDBusStubAdapterHelper;

class TunerAdditionalServiceDBusStubAdapter: public TunerAdditionalServiceStubAdapter, public TunerAdditionalServiceDBusStubAdapterHelper {
 public:
    TunerAdditionalServiceDBusStubAdapter(
            const std::string& commonApiAddress,
            const std::string& dbusInterfaceName,
            const std::string& dbusBusName,
            const std::string& dbusObjectPath,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
            const std::shared_ptr<CommonAPI::StubBase>& stub);
    

    void fireGetDataEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& selectParameter, const uint32_t& data, const uint32_t& handleOut);
    void fireComponentOptionsEvent(const uint32_t& componentID, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentOptions& componentOptions, const uint32_t& handleOut);
    void fireComponentTypeConfigurationEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions, const uint32_t& handleOut);
    void fireAnnouncementEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut);
    void fireAnnouncementFinishedEvent(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement& announcement, const uint32_t& handleOut_);

 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;
};

} // namespace TunerAdditionalService

#endif // TUNERADDITIONALSERVICE_Tuner_Additional_Service_DBUS_STUB_ADAPTER_H_
