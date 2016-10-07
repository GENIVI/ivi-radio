/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERSTATION_Tuner_Station_PROXY_H_
#define TUNERSTATION_Tuner_Station_PROXY_H_

#include "TunerStationProxyBase.h"

namespace TunerStation {

template <typename ... _AttributeExtensions>
class TunerStationProxy: virtual public TunerStation, virtual public TunerStationProxyBase, public _AttributeExtensions... {
 public:
    TunerStationProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~TunerStationProxy();


    /// Returns the wrapper class that provides access to the broadcast seek.
    virtual SeekEvent& getSeekEvent();
    /// Returns the wrapper class that provides access to the broadcast stationList.
    virtual StationListEvent& getStationListEvent();
    /// Returns the wrapper class that provides access to the broadcast currentStation.
    virtual CurrentStationEvent& getCurrentStationEvent();


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
    virtual void startTune(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback);

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
    virtual void abortTune(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, AbortTuneAsyncCallback callback);

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
    virtual void seek(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> seekAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback);

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
    virtual void controlUpdate(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback);

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
    virtual void makePermanent(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback);

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
    std::shared_ptr<TunerStationProxyBase> delegate_;
};


//
// TunerStationProxy Implementation
//
template <typename ... _AttributeExtensions>
TunerStationProxy<_AttributeExtensions...>::TunerStationProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        delegate_(std::dynamic_pointer_cast<TunerStationProxyBase>(delegate)),
        _AttributeExtensions(*(std::dynamic_pointer_cast<TunerStationProxyBase>(delegate)))... {
}

template <typename ... _AttributeExtensions>
TunerStationProxy<_AttributeExtensions...>::~TunerStationProxy() {
}


template <typename ... _AttributeExtensions>
typename TunerStationProxy<_AttributeExtensions...>::SeekEvent& TunerStationProxy<_AttributeExtensions...>::getSeekEvent() {
    return delegate_->getSeekEvent();
}

template <typename ... _AttributeExtensions>
typename TunerStationProxy<_AttributeExtensions...>::StationListEvent& TunerStationProxy<_AttributeExtensions...>::getStationListEvent() {
    return delegate_->getStationListEvent();
}

template <typename ... _AttributeExtensions>
typename TunerStationProxy<_AttributeExtensions...>::CurrentStationEvent& TunerStationProxy<_AttributeExtensions...>::getCurrentStationEvent() {
    return delegate_->getCurrentStationEvent();
}


template <typename ... _AttributeExtensions>
void TunerStationProxy<_AttributeExtensions...>::startTune(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->startTune(station, selectionMode, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerStationProxy<_AttributeExtensions...>::startTuneAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode, const uint32_t& handle, StartTuneAsyncCallback callback) {
    return delegate_->startTuneAsync(station, selectionMode, handle, callback);
}

template <typename ... _AttributeExtensions>
void TunerStationProxy<_AttributeExtensions...>::abortTune(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->abortTune(device, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerStationProxy<_AttributeExtensions...>::abortTuneAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const uint32_t& handle, AbortTuneAsyncCallback callback) {
    return delegate_->abortTuneAsync(device, handle, callback);
}

template <typename ... _AttributeExtensions>
void TunerStationProxy<_AttributeExtensions...>::seek(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->seek(device, seekMode, genre, flags, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerStationProxy<_AttributeExtensions...>::seekAsync(const TunerStationTypes::TunerStationTypes::DeviceType& device, const TunerStationTypes::TunerStationTypes::SeekMode& seekMode, const uint8_t& genre, const TunerTypes::TunerTypes::UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) {
    return delegate_->seekAsync(device, seekMode, genre, flags, handle, callback);
}

template <typename ... _AttributeExtensions>
void TunerStationProxy<_AttributeExtensions...>::controlUpdate(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->controlUpdate(updateElement, updateType, sourceType, stationType, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerStationProxy<_AttributeExtensions...>::controlUpdateAsync(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement, const TunerStationTypes::TunerStationTypes::UpdateType& updateType, const uint32_t& sourceType, const uint32_t& stationType, const uint32_t& handle, ControlUpdateAsyncCallback callback) {
    return delegate_->controlUpdateAsync(updateElement, updateType, sourceType, stationType, handle, callback);
}

template <typename ... _AttributeExtensions>
void TunerStationProxy<_AttributeExtensions...>::makePermanent(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->makePermanent(station, permanent, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerStationProxy<_AttributeExtensions...>::makePermanentAsync(const TunerStationTypes::TunerStationTypes::StationSelector& station, const bool& permanent, const uint32_t& handle, MakePermanentAsyncCallback callback) {
    return delegate_->makePermanentAsync(station, permanent, handle, callback);
}


template <typename ... _AttributeExtensions>
std::string TunerStationProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
const std::string& TunerStationProxy<_AttributeExtensions...>::getDomain() const {
    return delegate_->getDomain();
}

template <typename ... _AttributeExtensions>
const std::string& TunerStationProxy<_AttributeExtensions...>::getServiceId() const {
    return delegate_->getServiceId();
}

template <typename ... _AttributeExtensions>
const std::string& TunerStationProxy<_AttributeExtensions...>::getInstanceId() const {
    return delegate_->getInstanceId();
}

template <typename ... _AttributeExtensions>
bool TunerStationProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& TunerStationProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& TunerStationProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}

} // namespace TunerStation



#endif // TUNERSTATION_Tuner_Station_PROXY_H_
