/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERSTATION_MGEG_Tuner_Station_PROXY_BASE_H_
#define MGEGTUNERSTATION_MGEG_Tuner_Station_PROXY_BASE_H_

#include "MGEGTunerStation.h"
#include <cstdint>
#include <vector>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <MGEGTunerTypes/MGEGTunerTypes.h>
#include <MGEGTunerStationTypes/MGEGTunerStationTypes.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/Event.h>
#include <CommonAPI/Proxy.h>
#include <functional>
#include <future>

namespace MGEGTunerStation {

class MGEGTunerStationProxyBase: virtual public CommonAPI::Proxy {
 public:
    typedef CommonAPI::Event<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekData, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32> SeekEvent;
    typedef CommonAPI::Event<MGEGTunerStationTypes::MGEGTunerStationTypes::StationList, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32> StationListEvent;
    typedef CommonAPI::Event<MGEGTunerStationTypes::MGEGTunerStationTypes::Station, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32> CurrentStationEvent;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> StartTuneAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> AbortTuneAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> SeekAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> ControlUpdateAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32&, const MGEGTunerTypes::MGEGTunerTypes::Feedback&)> MakePermanentAsyncCallback;


    virtual SeekEvent& getSeekEvent() = 0;
    virtual StationListEvent& getStationListEvent() = 0;
    virtual CurrentStationEvent& getCurrentStationEvent() = 0;


    virtual void startTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, StartTuneAsyncCallback callback) = 0;

    virtual void abortTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, AbortTuneAsyncCallback callback) = 0;

    virtual void seek(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> seekAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) = 0;

    virtual void controlUpdate(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ControlUpdateAsyncCallback callback) = 0;

    virtual void makePermanent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, MakePermanentAsyncCallback callback) = 0;
};


} // namespace MGEGTunerStation

#endif // MGEGTUNERSTATION_MGEG_Tuner_Station_PROXY_BASE_H_
