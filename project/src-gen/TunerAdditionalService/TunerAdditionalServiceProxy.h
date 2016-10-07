/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERADDITIONALSERVICE_Tuner_Additional_Service_PROXY_H_
#define TUNERADDITIONALSERVICE_Tuner_Additional_Service_PROXY_H_

#include "TunerAdditionalServiceProxyBase.h"

namespace TunerAdditionalService {

template <typename ... _AttributeExtensions>
class TunerAdditionalServiceProxy: virtual public TunerAdditionalService, virtual public TunerAdditionalServiceProxyBase, public _AttributeExtensions... {
 public:
    TunerAdditionalServiceProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~TunerAdditionalServiceProxy();


    /// Returns the wrapper class that provides access to the broadcast getData.
    virtual GetDataEvent& getGetDataEvent();
    /// Returns the wrapper class that provides access to the broadcast componentOptions.
    virtual ComponentOptionsEvent& getComponentOptionsEvent();
    /// Returns the wrapper class that provides access to the broadcast componentTypeConfiguration.
    virtual ComponentTypeConfigurationEvent& getComponentTypeConfigurationEvent();
    /// Returns the wrapper class that provides access to the broadcast announcement.
    virtual AnnouncementEvent& getAnnouncementEvent();
    /// Returns the wrapper class that provides access to the broadcast announcementFinished.
    virtual AnnouncementFinishedEvent& getAnnouncementFinishedEvent();


    /**
     * Calls selectComponent with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void selectComponent(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);
    /**
     * Calls selectComponent with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> selectComponentAsync(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, SelectComponentAsyncCallback callback);

    /**
     * Calls requestComponentOptions with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void requestComponentOptions(const uint32_t& componentID, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);
    /**
     * Calls requestComponentOptions with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> requestComponentOptionsAsync(const uint32_t& componentID, const uint32_t& handle, RequestComponentOptionsAsyncCallback callback);

    /**
     * Calls requestComponentTypeConfiguration with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void requestComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);
    /**
     * Calls requestComponentTypeConfiguration with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> requestComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback);

    /**
     * Calls changeComponentTypeConfiguration with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void changeComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback);
    /**
     * Calls changeComponentTypeConfiguration with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> changeComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, ChangeComponentTypeConfigurationAsyncCallback callback);

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
    std::shared_ptr<TunerAdditionalServiceProxyBase> delegate_;
};


//
// TunerAdditionalServiceProxy Implementation
//
template <typename ... _AttributeExtensions>
TunerAdditionalServiceProxy<_AttributeExtensions...>::TunerAdditionalServiceProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        delegate_(std::dynamic_pointer_cast<TunerAdditionalServiceProxyBase>(delegate)),
        _AttributeExtensions(*(std::dynamic_pointer_cast<TunerAdditionalServiceProxyBase>(delegate)))... {
}

template <typename ... _AttributeExtensions>
TunerAdditionalServiceProxy<_AttributeExtensions...>::~TunerAdditionalServiceProxy() {
}


template <typename ... _AttributeExtensions>
typename TunerAdditionalServiceProxy<_AttributeExtensions...>::GetDataEvent& TunerAdditionalServiceProxy<_AttributeExtensions...>::getGetDataEvent() {
    return delegate_->getGetDataEvent();
}

template <typename ... _AttributeExtensions>
typename TunerAdditionalServiceProxy<_AttributeExtensions...>::ComponentOptionsEvent& TunerAdditionalServiceProxy<_AttributeExtensions...>::getComponentOptionsEvent() {
    return delegate_->getComponentOptionsEvent();
}

template <typename ... _AttributeExtensions>
typename TunerAdditionalServiceProxy<_AttributeExtensions...>::ComponentTypeConfigurationEvent& TunerAdditionalServiceProxy<_AttributeExtensions...>::getComponentTypeConfigurationEvent() {
    return delegate_->getComponentTypeConfigurationEvent();
}

template <typename ... _AttributeExtensions>
typename TunerAdditionalServiceProxy<_AttributeExtensions...>::AnnouncementEvent& TunerAdditionalServiceProxy<_AttributeExtensions...>::getAnnouncementEvent() {
    return delegate_->getAnnouncementEvent();
}

template <typename ... _AttributeExtensions>
typename TunerAdditionalServiceProxy<_AttributeExtensions...>::AnnouncementFinishedEvent& TunerAdditionalServiceProxy<_AttributeExtensions...>::getAnnouncementFinishedEvent() {
    return delegate_->getAnnouncementFinishedEvent();
}


template <typename ... _AttributeExtensions>
void TunerAdditionalServiceProxy<_AttributeExtensions...>::selectComponent(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->selectComponent(componentID, handle, componentParameter, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerAdditionalServiceProxy<_AttributeExtensions...>::selectComponentAsync(const uint32_t& componentID, const uint32_t& handle, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter& componentParameter, SelectComponentAsyncCallback callback) {
    return delegate_->selectComponentAsync(componentID, handle, componentParameter, callback);
}

template <typename ... _AttributeExtensions>
void TunerAdditionalServiceProxy<_AttributeExtensions...>::requestComponentOptions(const uint32_t& componentID, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->requestComponentOptions(componentID, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerAdditionalServiceProxy<_AttributeExtensions...>::requestComponentOptionsAsync(const uint32_t& componentID, const uint32_t& handle, RequestComponentOptionsAsyncCallback callback) {
    return delegate_->requestComponentOptionsAsync(componentID, handle, callback);
}

template <typename ... _AttributeExtensions>
void TunerAdditionalServiceProxy<_AttributeExtensions...>::requestComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->requestComponentTypeConfiguration(compentType, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerAdditionalServiceProxy<_AttributeExtensions...>::requestComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback) {
    return delegate_->requestComponentTypeConfigurationAsync(compentType, handle, callback);
}

template <typename ... _AttributeExtensions>
void TunerAdditionalServiceProxy<_AttributeExtensions...>::changeComponentTypeConfiguration(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, TunerTypes::TunerTypes::Feedback& feedback) {
    delegate_->changeComponentTypeConfiguration(componentType, options, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> TunerAdditionalServiceProxy<_AttributeExtensions...>::changeComponentTypeConfigurationAsync(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType, const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& options, const uint32_t& handle, ChangeComponentTypeConfigurationAsyncCallback callback) {
    return delegate_->changeComponentTypeConfigurationAsync(componentType, options, handle, callback);
}


template <typename ... _AttributeExtensions>
std::string TunerAdditionalServiceProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
const std::string& TunerAdditionalServiceProxy<_AttributeExtensions...>::getDomain() const {
    return delegate_->getDomain();
}

template <typename ... _AttributeExtensions>
const std::string& TunerAdditionalServiceProxy<_AttributeExtensions...>::getServiceId() const {
    return delegate_->getServiceId();
}

template <typename ... _AttributeExtensions>
const std::string& TunerAdditionalServiceProxy<_AttributeExtensions...>::getInstanceId() const {
    return delegate_->getInstanceId();
}

template <typename ... _AttributeExtensions>
bool TunerAdditionalServiceProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& TunerAdditionalServiceProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& TunerAdditionalServiceProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}

} // namespace TunerAdditionalService



#endif // TUNERADDITIONALSERVICE_Tuner_Additional_Service_PROXY_H_
