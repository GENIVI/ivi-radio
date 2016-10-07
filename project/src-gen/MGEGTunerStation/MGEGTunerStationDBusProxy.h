/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERSTATION_MGEG_Tuner_Station_DBUS_PROXY_H_
#define MGEGTUNERSTATION_MGEG_Tuner_Station_DBUS_PROXY_H_

#include <MGEGTunerStation/MGEGTunerStationProxyBase.h>
#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>

#include <string>

namespace MGEGTunerStation {

class MGEGTunerStationDBusProxy: virtual public MGEGTunerStationProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    MGEGTunerStationDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~MGEGTunerStationDBusProxy() { }


    virtual SeekEvent& getSeekEvent();
    virtual StationListEvent& getStationListEvent();
    virtual CurrentStationEvent& getCurrentStationEvent();


    virtual void startTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, StartTuneAsyncCallback callback);

    virtual void abortTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, AbortTuneAsyncCallback callback);

    virtual void seek(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> seekAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback);

    virtual void controlUpdate(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ControlUpdateAsyncCallback callback);

    virtual void makePermanent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, MakePermanentAsyncCallback callback);
    
    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusEvent<SeekEvent> seek_;
    CommonAPI::DBus::DBusEvent<StationListEvent> stationList_;
    CommonAPI::DBus::DBusEvent<CurrentStationEvent> currentStation_;
};

} // namespace MGEGTunerStation

#endif // MGEGTUNERSTATION_MGEG_Tuner_Station_DBUS_PROXY_H_
