/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERSTATION_Tuner_Station_DBUS_STUB_ADAPTER_H_
#define TUNERSTATION_Tuner_Station_DBUS_STUB_ADAPTER_H_

#include <TunerStation/TunerStationStub.h>

#include <CommonAPI/DBus/DBusStubAdapterHelper.h>
#include <CommonAPI/DBus/DBusFactory.h>

namespace TunerStation {

typedef CommonAPI::DBus::DBusStubAdapterHelper<TunerStationStub> TunerStationDBusStubAdapterHelper;

class TunerStationDBusStubAdapter: public TunerStationStubAdapter, public TunerStationDBusStubAdapterHelper {
 public:
    TunerStationDBusStubAdapter(
            const std::string& commonApiAddress,
            const std::string& dbusInterfaceName,
            const std::string& dbusBusName,
            const std::string& dbusObjectPath,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
            const std::shared_ptr<CommonAPI::StubBase>& stub);
    

    void fireSeekEvent(const TunerStationTypes::TunerStationTypes::SeekData& seekData, const uint32_t& handle);
    void fireStationListEvent(const TunerStationTypes::TunerStationTypes::StationList& list, const uint32_t& handle_out);
    void fireCurrentStationEvent(const TunerStationTypes::TunerStationTypes::Station& current, const uint32_t& handle);

 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;
};

} // namespace TunerStation

#endif // TUNERSTATION_Tuner_Station_DBUS_STUB_ADAPTER_H_
