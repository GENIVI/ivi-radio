/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_STATION_Station_DBUS_PROXY_H_
#define IVIRADIO_STATION_Station_DBUS_PROXY_H_

#include <IVIRadio/Station/StationProxyBase.h>
#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>

#include <string>

namespace IVIRadio {
namespace Station {

class StationDBusProxy: virtual public StationProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    StationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~StationDBusProxy() { }


    virtual CurrentStationEvent& getCurrentStationEvent();
    virtual SeekEvent& getSeekEvent();
    virtual StationListEvent& getStationListEvent();


    virtual void abortTune(const Types::Types::DeviceType& deviceType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const Types::Types::DeviceType& deviceType, const uint32_t& handle, AbortTuneAsyncCallback callback);

    virtual void makePermanent(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback);

    virtual void controlUpdate(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback);

    virtual void seek(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> seekAsync(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback);

    virtual void startTune(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback);
    
    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusEvent<CurrentStationEvent> currentStation_;
    CommonAPI::DBus::DBusEvent<SeekEvent> seek_;
    CommonAPI::DBus::DBusEvent<StationListEvent> stationList_;
};

} // namespace Station
} // namespace IVIRadio

#endif // IVIRADIO_STATION_Station_DBUS_PROXY_H_
