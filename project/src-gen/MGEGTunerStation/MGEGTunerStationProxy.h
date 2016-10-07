/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERSTATION_MGEG_Tuner_Station_PROXY_H_
#define MGEGTUNERSTATION_MGEG_Tuner_Station_PROXY_H_

#include "MGEGTunerStationProxyBase.h"

namespace MGEGTunerStation {

template <typename ... _AttributeExtensions>
class MGEGTunerStationProxy: virtual public MGEGTunerStation, virtual public MGEGTunerStationProxyBase, public _AttributeExtensions... {
 public:
    MGEGTunerStationProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~MGEGTunerStationProxy();


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
    virtual void startTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> startTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, StartTuneAsyncCallback callback);

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
    virtual void abortTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> abortTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, AbortTuneAsyncCallback callback);

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
    virtual void seek(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> seekAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback);

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
    virtual void controlUpdate(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> controlUpdateAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ControlUpdateAsyncCallback callback);

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
    virtual void makePermanent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> makePermanentAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, MakePermanentAsyncCallback callback);

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
    std::shared_ptr<MGEGTunerStationProxyBase> delegate_;
};


//
// MGEGTunerStationProxy Implementation
//
template <typename ... _AttributeExtensions>
MGEGTunerStationProxy<_AttributeExtensions...>::MGEGTunerStationProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        delegate_(std::dynamic_pointer_cast<MGEGTunerStationProxyBase>(delegate)),
        _AttributeExtensions(*(std::dynamic_pointer_cast<MGEGTunerStationProxyBase>(delegate)))... {
}

template <typename ... _AttributeExtensions>
MGEGTunerStationProxy<_AttributeExtensions...>::~MGEGTunerStationProxy() {
}


template <typename ... _AttributeExtensions>
typename MGEGTunerStationProxy<_AttributeExtensions...>::SeekEvent& MGEGTunerStationProxy<_AttributeExtensions...>::getSeekEvent() {
    return delegate_->getSeekEvent();
}

template <typename ... _AttributeExtensions>
typename MGEGTunerStationProxy<_AttributeExtensions...>::StationListEvent& MGEGTunerStationProxy<_AttributeExtensions...>::getStationListEvent() {
    return delegate_->getStationListEvent();
}

template <typename ... _AttributeExtensions>
typename MGEGTunerStationProxy<_AttributeExtensions...>::CurrentStationEvent& MGEGTunerStationProxy<_AttributeExtensions...>::getCurrentStationEvent() {
    return delegate_->getCurrentStationEvent();
}


template <typename ... _AttributeExtensions>
void MGEGTunerStationProxy<_AttributeExtensions...>::startTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->startTune(station, selectionMode, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerStationProxy<_AttributeExtensions...>::startTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, StartTuneAsyncCallback callback) {
    return delegate_->startTuneAsync(station, selectionMode, handle, callback);
}

template <typename ... _AttributeExtensions>
void MGEGTunerStationProxy<_AttributeExtensions...>::abortTune(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->abortTune(device, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerStationProxy<_AttributeExtensions...>::abortTuneAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, AbortTuneAsyncCallback callback) {
    return delegate_->abortTuneAsync(device, handle, callback);
}

template <typename ... _AttributeExtensions>
void MGEGTunerStationProxy<_AttributeExtensions...>::seek(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->seek(device, seekMode, genre, flags, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerStationProxy<_AttributeExtensions...>::seekAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& device, const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& genre, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const uint32_t& handle, SeekAsyncCallback callback) {
    return delegate_->seekAsync(device, seekMode, genre, flags, handle, callback);
}

template <typename ... _AttributeExtensions>
void MGEGTunerStationProxy<_AttributeExtensions...>::controlUpdate(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->controlUpdate(updateElement, updateType, sourceType, stationType, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerStationProxy<_AttributeExtensions...>::controlUpdateAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement, const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& sourceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ControlUpdateAsyncCallback callback) {
    return delegate_->controlUpdateAsync(updateElement, updateType, sourceType, stationType, handle, callback);
}

template <typename ... _AttributeExtensions>
void MGEGTunerStationProxy<_AttributeExtensions...>::makePermanent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->makePermanent(station, permanent, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerStationProxy<_AttributeExtensions...>::makePermanentAsync(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& permanent, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, MakePermanentAsyncCallback callback) {
    return delegate_->makePermanentAsync(station, permanent, handle, callback);
}


template <typename ... _AttributeExtensions>
std::string MGEGTunerStationProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
const std::string& MGEGTunerStationProxy<_AttributeExtensions...>::getDomain() const {
    return delegate_->getDomain();
}

template <typename ... _AttributeExtensions>
const std::string& MGEGTunerStationProxy<_AttributeExtensions...>::getServiceId() const {
    return delegate_->getServiceId();
}

template <typename ... _AttributeExtensions>
const std::string& MGEGTunerStationProxy<_AttributeExtensions...>::getInstanceId() const {
    return delegate_->getInstanceId();
}

template <typename ... _AttributeExtensions>
bool MGEGTunerStationProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& MGEGTunerStationProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& MGEGTunerStationProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}

} // namespace MGEGTunerStation



#endif // MGEGTUNERSTATION_MGEG_Tuner_Station_PROXY_H_
