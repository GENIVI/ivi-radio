/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_PROXY_H_
#define MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_PROXY_H_

#include "MGEGTunerAdditionalServiceProxyBase.h"

namespace MGEGTunerAdditionalService {

template <typename ... _AttributeExtensions>
class MGEGTunerAdditionalServiceProxy: virtual public MGEGTunerAdditionalService, virtual public MGEGTunerAdditionalServiceProxyBase, public _AttributeExtensions... {
 public:
    MGEGTunerAdditionalServiceProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~MGEGTunerAdditionalServiceProxy();


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
    virtual void selectComponent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> selectComponentAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, SelectComponentAsyncCallback callback);

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
    virtual void requestComponentOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> requestComponentOptionsAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, RequestComponentOptionsAsyncCallback callback);

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
    virtual void requestComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> requestComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback);

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
    virtual void changeComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback);
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
    virtual std::future<CommonAPI::CallStatus> changeComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ChangeComponentTypeConfigurationAsyncCallback callback);

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
    std::shared_ptr<MGEGTunerAdditionalServiceProxyBase> delegate_;
};


//
// MGEGTunerAdditionalServiceProxy Implementation
//
template <typename ... _AttributeExtensions>
MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::MGEGTunerAdditionalServiceProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        delegate_(std::dynamic_pointer_cast<MGEGTunerAdditionalServiceProxyBase>(delegate)),
        _AttributeExtensions(*(std::dynamic_pointer_cast<MGEGTunerAdditionalServiceProxyBase>(delegate)))... {
}

template <typename ... _AttributeExtensions>
MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::~MGEGTunerAdditionalServiceProxy() {
}


template <typename ... _AttributeExtensions>
typename MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::GetDataEvent& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getGetDataEvent() {
    return delegate_->getGetDataEvent();
}

template <typename ... _AttributeExtensions>
typename MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::ComponentOptionsEvent& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getComponentOptionsEvent() {
    return delegate_->getComponentOptionsEvent();
}

template <typename ... _AttributeExtensions>
typename MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::ComponentTypeConfigurationEvent& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getComponentTypeConfigurationEvent() {
    return delegate_->getComponentTypeConfigurationEvent();
}

template <typename ... _AttributeExtensions>
typename MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::AnnouncementEvent& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getAnnouncementEvent() {
    return delegate_->getAnnouncementEvent();
}

template <typename ... _AttributeExtensions>
typename MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::AnnouncementFinishedEvent& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getAnnouncementFinishedEvent() {
    return delegate_->getAnnouncementFinishedEvent();
}


template <typename ... _AttributeExtensions>
void MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::selectComponent(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->selectComponent(componentID, handle, componentParameter, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::selectComponentAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_SelectParameter& componentParameter, SelectComponentAsyncCallback callback) {
    return delegate_->selectComponentAsync(componentID, handle, componentParameter, callback);
}

template <typename ... _AttributeExtensions>
void MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::requestComponentOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->requestComponentOptions(componentID, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::requestComponentOptionsAsync(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, RequestComponentOptionsAsyncCallback callback) {
    return delegate_->requestComponentOptionsAsync(componentID, handle, callback);
}

template <typename ... _AttributeExtensions>
void MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::requestComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->requestComponentTypeConfiguration(compentType, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::requestComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& compentType, const uint32_t& handle, RequestComponentTypeConfigurationAsyncCallback callback) {
    return delegate_->requestComponentTypeConfigurationAsync(compentType, handle, callback);
}

template <typename ... _AttributeExtensions>
void MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::changeComponentTypeConfiguration(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, CommonAPI::CallStatus& callStatus, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handleOut, MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) {
    delegate_->changeComponentTypeConfiguration(componentType, options, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::changeComponentTypeConfigurationAsync(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& componentType, const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentTypeOptions& options, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle, ChangeComponentTypeConfigurationAsyncCallback callback) {
    return delegate_->changeComponentTypeConfigurationAsync(componentType, options, handle, callback);
}


template <typename ... _AttributeExtensions>
std::string MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
const std::string& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getDomain() const {
    return delegate_->getDomain();
}

template <typename ... _AttributeExtensions>
const std::string& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getServiceId() const {
    return delegate_->getServiceId();
}

template <typename ... _AttributeExtensions>
const std::string& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getInstanceId() const {
    return delegate_->getInstanceId();
}

template <typename ... _AttributeExtensions>
bool MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& MGEGTunerAdditionalServiceProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}

} // namespace MGEGTunerAdditionalService



#endif // MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_PROXY_H_
