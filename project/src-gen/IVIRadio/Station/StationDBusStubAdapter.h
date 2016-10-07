/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_STATION_Station_DBUS_STUB_ADAPTER_H_
#define IVIRADIO_STATION_Station_DBUS_STUB_ADAPTER_H_

#include <IVIRadio/Station/StationStub.h>

#include <CommonAPI/DBus/DBusStubAdapterHelper.h>
#include <CommonAPI/DBus/DBusFactory.h>

namespace IVIRadio {
namespace Station {

typedef CommonAPI::DBus::DBusStubAdapterHelper<StationStub> StationDBusStubAdapterHelper;

class StationDBusStubAdapter: public StationStubAdapter, public StationDBusStubAdapterHelper {
 public:
    StationDBusStubAdapter(
            const std::string& commonApiAddress,
            const std::string& dbusInterfaceName,
            const std::string& dbusBusName,
            const std::string& dbusObjectPath,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
            const std::shared_ptr<CommonAPI::StubBase>& stub);
    

    void fireCurrentStationEvent(const StationTypes::Station& current, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    void fireSeekEvent(const StationTypes::SeekData& seekData, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);
    void fireStationListEvent(const StationTypes::StationList& list, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode);

 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;
};

} // namespace Station
} // namespace IVIRadio

#endif // IVIRADIO_STATION_Station_DBUS_STUB_ADAPTER_H_
