/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_STATION_Station_PROXY_BASE_H_
#define IVIRADIO_STATION_Station_PROXY_BASE_H_

#include "Station.h"
#include <cstdint>
#include <vector>
#include <CommonAPI/InputStream.h>
#include <IVIRadio/Station/StationTypes.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/OutputStream.h>
#include <IVIRadio/Types/Types.h>
#include <CommonAPI/Event.h>
#include <CommonAPI/Proxy.h>
#include <functional>
#include <future>

namespace IVIRadio {
namespace Station {

class StationProxyBase: virtual public CommonAPI::Proxy {
 public:
    typedef CommonAPI::Event<StationTypes::Station, uint32_t, Types::Types::ErrorCodes> CurrentStationEvent;
    typedef CommonAPI::Event<StationTypes::SeekData, uint32_t, Types::Types::ErrorCodes> SeekEvent;
    typedef CommonAPI::Event<StationTypes::StationList, uint32_t, Types::Types::ErrorCodes> StationListEvent;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> AbortTuneAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> MakePermanentAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> ControlUpdateAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> SeekAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> StartTuneAsyncCallback;


    virtual CurrentStationEvent& getCurrentStationEvent() = 0;
    virtual SeekEvent& getSeekEvent() = 0;
    virtual StationListEvent& getStationListEvent() = 0;


    virtual void abortTune(const Types::Types::DeviceType& deviceType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const Types::Types::DeviceType& deviceType, const uint32_t& handle, AbortTuneAsyncCallback callback) = 0;

    virtual void makePermanent(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback) = 0;

    virtual void controlUpdate(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback) = 0;

    virtual void seek(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> seekAsync(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) = 0;

    virtual void startTune(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback) = 0;
};


} // namespace Station
} // namespace IVIRadio

#endif // IVIRADIO_STATION_Station_PROXY_BASE_H_
