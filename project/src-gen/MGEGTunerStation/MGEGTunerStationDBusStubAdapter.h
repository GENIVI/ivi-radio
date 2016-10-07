/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERSTATION_MGEG_Tuner_Station_DBUS_STUB_ADAPTER_H_
#define MGEGTUNERSTATION_MGEG_Tuner_Station_DBUS_STUB_ADAPTER_H_

#include <MGEGTunerStation/MGEGTunerStationStub.h>

#include <CommonAPI/DBus/DBusStubAdapterHelper.h>
#include <CommonAPI/DBus/DBusFactory.h>

namespace MGEGTunerStation {

typedef CommonAPI::DBus::DBusStubAdapterHelper<MGEGTunerStationStub> MGEGTunerStationDBusStubAdapterHelper;

class MGEGTunerStationDBusStubAdapter: public MGEGTunerStationStubAdapter, public MGEGTunerStationDBusStubAdapterHelper {
 public:
    MGEGTunerStationDBusStubAdapter(
            const std::string& commonApiAddress,
            const std::string& dbusInterfaceName,
            const std::string& dbusBusName,
            const std::string& dbusObjectPath,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
            const std::shared_ptr<CommonAPI::StubBase>& stub);
    

    void fireSeekEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekData& seekData, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle);
    void fireStationListEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationList& list, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out);
    void fireCurrentStationEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::Station& current, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle);

 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;
};

} // namespace MGEGTunerStation

#endif // MGEGTUNERSTATION_MGEG_Tuner_Station_DBUS_STUB_ADAPTER_H_
