/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_STATION_Station_PROXY_H_
#define IVIRADIO_STATION_Station_PROXY_H_

#include "StationProxyBase.h"

namespace IVIRadio {
namespace Station {

template <typename ... _AttributeExtensions>
class StationProxy: virtual public Station, virtual public StationProxyBase, public _AttributeExtensions... {
 public:
    StationProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~StationProxy();


    /// Returns the wrapper class that provides access to the broadcast currentStation.
    virtual CurrentStationEvent& getCurrentStationEvent();
    /// Returns the wrapper class that provides access to the broadcast seek.
    virtual SeekEvent& getSeekEvent();
    /// Returns the wrapper class that provides access to the broadcast stationList.
    virtual StationListEvent& getStationListEvent();


    /**
     * Calls abortTune with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void abortTune(const Types::Types::DeviceType& deviceType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls abortTune with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const Types::Types::DeviceType& deviceType, const uint32_t& handle, AbortTuneAsyncCallback callback);

    /**
     * Calls makePermanent with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void makePermanent(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls makePermanent with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback);

    /**
     * Calls controlUpdate with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void controlUpdate(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls controlUpdate with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback);

    /**
     * Calls seek with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void seek(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls seek with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> seekAsync(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback);

    /**
     * Calls startTune with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void startTune(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls startTune with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback);

    /// Returns the CommonAPI address of the remote partner this proxy communicates with.
    virtual std::string getAddress() const;

    /// Returns the domain of the remote partner this proxy communicates with.
    virtual const std::string& getDomain() const;

    /// Returns the service ID of the remote partner this proxy communicates with.
    virtual const std::string& getServiceId() const;

    /// Returns the instance ID of the remote partner this proxy communicates with.
    virtual const std::string& getInstanceId() const;

    /// Returns true if the remote partner for this proxy is available.
    virtual bool isAvailable() const;

    /**
     * Returns the wrapper class that is used to (de-)register for notifications about
     * the availability of the remote partner of this proxy.
     */
    virtual CommonAPI::ProxyStatusEvent& getProxyStatusEvent();

    /**
     * Returns the wrapper class that is used to access version information of the remote
     * partner of this proxy.
     */
    virtual CommonAPI::InterfaceVersionAttribute& getInterfaceVersionAttribute();

 private:
    std::shared_ptr<StationProxyBase> delegate_;
};


//
// StationProxy Implementation
//
template <typename ... _AttributeExtensions>
StationProxy<_AttributeExtensions...>::StationProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        delegate_(std::dynamic_pointer_cast<StationProxyBase>(delegate)),
        _AttributeExtensions(*(std::dynamic_pointer_cast<StationProxyBase>(delegate)))... {
}

template <typename ... _AttributeExtensions>
StationProxy<_AttributeExtensions...>::~StationProxy() {
}


template <typename ... _AttributeExtensions>
typename StationProxy<_AttributeExtensions...>::CurrentStationEvent& StationProxy<_AttributeExtensions...>::getCurrentStationEvent() {
    return delegate_->getCurrentStationEvent();
}

template <typename ... _AttributeExtensions>
typename StationProxy<_AttributeExtensions...>::SeekEvent& StationProxy<_AttributeExtensions...>::getSeekEvent() {
    return delegate_->getSeekEvent();
}

template <typename ... _AttributeExtensions>
typename StationProxy<_AttributeExtensions...>::StationListEvent& StationProxy<_AttributeExtensions...>::getStationListEvent() {
    return delegate_->getStationListEvent();
}


template <typename ... _AttributeExtensions>
void StationProxy<_AttributeExtensions...>::abortTune(const Types::Types::DeviceType& deviceType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->abortTune(deviceType, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> StationProxy<_AttributeExtensions...>::abortTuneAsync(const Types::Types::DeviceType& deviceType, const uint32_t& handle, AbortTuneAsyncCallback callback) {
    return delegate_->abortTuneAsync(deviceType, handle, callback);
}

template <typename ... _AttributeExtensions>
void StationProxy<_AttributeExtensions...>::makePermanent(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->makePermanent(station, permanent, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> StationProxy<_AttributeExtensions...>::makePermanentAsync(const Types::Types::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback) {
    return delegate_->makePermanentAsync(station, permanent, handle, callback);
}

template <typename ... _AttributeExtensions>
void StationProxy<_AttributeExtensions...>::controlUpdate(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->controlUpdate(updateElement, updateType, sourceType, stationType, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> StationProxy<_AttributeExtensions...>::controlUpdateAsync(const StationTypes::UpdateElement& updateElement, const Types::Types::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback) {
    return delegate_->controlUpdateAsync(updateElement, updateType, sourceType, stationType, handle, callback);
}

template <typename ... _AttributeExtensions>
void StationProxy<_AttributeExtensions...>::seek(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->seek(device, seekMode, genre, flags, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> StationProxy<_AttributeExtensions...>::seekAsync(const Types::Types::DeviceType& device, const StationTypes::SeekMode& seekMode, const uint8_t& genre, const Types::Types::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) {
    return delegate_->seekAsync(device, seekMode, genre, flags, handle, callback);
}

template <typename ... _AttributeExtensions>
void StationProxy<_AttributeExtensions...>::startTune(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->startTune(station, selectionMode, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> StationProxy<_AttributeExtensions...>::startTuneAsync(const Types::Types::StationSelector& station, const StationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback) {
    return delegate_->startTuneAsync(station, selectionMode, handle, callback);
}


template <typename ... _AttributeExtensions>
std::string StationProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
const std::string& StationProxy<_AttributeExtensions...>::getDomain() const {
    return delegate_->getDomain();
}

template <typename ... _AttributeExtensions>
const std::string& StationProxy<_AttributeExtensions...>::getServiceId() const {
    return delegate_->getServiceId();
}

template <typename ... _AttributeExtensions>
const std::string& StationProxy<_AttributeExtensions...>::getInstanceId() const {
    return delegate_->getInstanceId();
}

template <typename ... _AttributeExtensions>
bool StationProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& StationProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& StationProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}

} // namespace Station
} // namespace IVIRadio



#endif // IVIRADIO_STATION_Station_PROXY_H_
