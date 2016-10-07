/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERSTATION_Tuner_Station_DBUS_PROXY_H_
#define TUNERSTATION_Tuner_Station_DBUS_PROXY_H_

#include <TunerStation/TunerStationProxyBase.h>
#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>

#include <string>

namespace TunerStation {

class TunerStationDBusProxy: virtual public TunerStationProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    TunerStationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~TunerStationDBusProxy() { }


    virtual SeekEvent& getSeekEvent();
    virtual StationListEvent& getStationListEvent();
    virtual CurrentStationEvent& getCurrentStationEvent();


    virtual void startTune(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback);

    virtual void abortTune(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, AbortTuneAsyncCallback callback);

    virtual void seek(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> seekAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback);

    virtual void controlUpdate(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback);

    virtual void makePermanent(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback);
    
    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusEvent<SeekEvent> seek_;
    CommonAPI::DBus::DBusEvent<StationListEvent> stationList_;
    CommonAPI::DBus::DBusEvent<CurrentStationEvent> currentStation_;
};

} // namespace TunerStation

#endif // TUNERSTATION_Tuner_Station_DBUS_PROXY_H_
