/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERSTATION_Tuner_Station_PROXY_BASE_H_
#define TUNERSTATION_Tuner_Station_PROXY_BASE_H_

#include "TunerStation.h"
#include <TunerStationTypes/TunerStationTypes.h>
#include <cstdint>
#include <vector>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <TunerTypes/TunerTypes.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/Event.h>
#include <CommonAPI/Proxy.h>
#include <functional>
#include <future>

namespace TunerStation {

class TunerStationProxyBase: virtual public CommonAPI::Proxy {
 public:
    typedef CommonAPI::Event<TunerStationTypes::TunerStationTypes::SeekData, uint32_t> SeekEvent;
    typedef CommonAPI::Event<TunerStationTypes::TunerStationTypes::StationList, uint32_t> StationListEvent;
    typedef CommonAPI::Event<TunerStationTypes::TunerStationTypes::Station, uint32_t> CurrentStationEvent;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> StartTuneAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> AbortTuneAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> SeekAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> ControlUpdateAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const TunerTypes::TunerTypes::Feedback&)> MakePermanentAsyncCallback;


    virtual SeekEvent& getSeekEvent() = 0;
    virtual StationListEvent& getStationListEvent() = 0;
    virtual CurrentStationEvent& getCurrentStationEvent() = 0;


    virtual void startTune(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback) = 0;

    virtual void abortTune(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, AbortTuneAsyncCallback callback) = 0;

    virtual void seek(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> seekAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) = 0;

    virtual void controlUpdate(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback) = 0;

    virtual void makePermanent(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback) = 0;
};


} // namespace TunerStation

#endif // TUNERSTATION_Tuner_Station_PROXY_BASE_H_
