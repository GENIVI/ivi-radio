/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_PROXY_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_PROXY_H_

#include "AdditionalServiceProxyBase.h"

namespace IVIRadio {
namespace AdditionalService {

template <typename ... _AttributeExtensions>
class AdditionalServiceProxy: virtual public AdditionalService, virtual public AdditionalServiceProxyBase, public _AttributeExtensions... {
 public:
    AdditionalServiceProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~AdditionalServiceProxy();


    /// Returns the wrapper class that provides access to the broadcast Data.
    virtual DataEvent& getDataEvent();
    /// Returns the wrapper class that provides access to the broadcast Announcement.
    virtual AnnouncementEvent& getAnnouncementEvent();
    /// Returns the wrapper class that provides access to the broadcast AnnouncementFinished.
    virtual AnnouncementFinishedEvent& getAnnouncementFinishedEvent();
    /// Returns the wrapper class that provides access to the broadcast SubscribedServiceOptions.
    virtual SubscribedServiceOptionsEvent& getSubscribedServiceOptionsEvent();


    /**
     * Calls requestDataService with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void requestDataService(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls requestDataService with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> requestDataServiceAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, RequestDataServiceAsyncCallback callback);

    /**
     * Calls requestSubscribedServiceOptions with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void requestSubscribedServiceOptions(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls requestSubscribedServiceOptions with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> requestSubscribedServiceOptionsAsync(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, RequestSubscribedServiceOptionsAsyncCallback callback);

    /**
     * Calls abort with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void abort(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls abort with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> abortAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, AbortAsyncCallback callback);

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
    std::shared_ptr<AdditionalServiceProxyBase> delegate_;
};


//
// AdditionalServiceProxy Implementation
//
template <typename ... _AttributeExtensions>
AdditionalServiceProxy<_AttributeExtensions...>::AdditionalServiceProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        delegate_(std::dynamic_pointer_cast<AdditionalServiceProxyBase>(delegate)),
        _AttributeExtensions(*(std::dynamic_pointer_cast<AdditionalServiceProxyBase>(delegate)))... {
}

template <typename ... _AttributeExtensions>
AdditionalServiceProxy<_AttributeExtensions...>::~AdditionalServiceProxy() {
}


template <typename ... _AttributeExtensions>
typename AdditionalServiceProxy<_AttributeExtensions...>::DataEvent& AdditionalServiceProxy<_AttributeExtensions...>::getDataEvent() {
    return delegate_->getDataEvent();
}

template <typename ... _AttributeExtensions>
typename AdditionalServiceProxy<_AttributeExtensions...>::AnnouncementEvent& AdditionalServiceProxy<_AttributeExtensions...>::getAnnouncementEvent() {
    return delegate_->getAnnouncementEvent();
}

template <typename ... _AttributeExtensions>
typename AdditionalServiceProxy<_AttributeExtensions...>::AnnouncementFinishedEvent& AdditionalServiceProxy<_AttributeExtensions...>::getAnnouncementFinishedEvent() {
    return delegate_->getAnnouncementFinishedEvent();
}

template <typename ... _AttributeExtensions>
typename AdditionalServiceProxy<_AttributeExtensions...>::SubscribedServiceOptionsEvent& AdditionalServiceProxy<_AttributeExtensions...>::getSubscribedServiceOptionsEvent() {
    return delegate_->getSubscribedServiceOptionsEvent();
}


template <typename ... _AttributeExtensions>
void AdditionalServiceProxy<_AttributeExtensions...>::requestDataService(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->requestDataService(dataService, selectors, unifiedOptions, serviceOptions, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> AdditionalServiceProxy<_AttributeExtensions...>::requestDataServiceAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& selectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& serviceOptions, const uint32_t& handle, RequestDataServiceAsyncCallback callback) {
    return delegate_->requestDataServiceAsync(dataService, selectors, unifiedOptions, serviceOptions, handle, callback);
}

template <typename ... _AttributeExtensions>
void AdditionalServiceProxy<_AttributeExtensions...>::requestSubscribedServiceOptions(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->requestSubscribedServiceOptions(dataservice, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> AdditionalServiceProxy<_AttributeExtensions...>::requestSubscribedServiceOptionsAsync(const AdditionalServiceTypes::DataService& dataservice, const uint32_t& handle, RequestSubscribedServiceOptionsAsyncCallback callback) {
    return delegate_->requestSubscribedServiceOptionsAsync(dataservice, handle, callback);
}

template <typename ... _AttributeExtensions>
void AdditionalServiceProxy<_AttributeExtensions...>::abort(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->abort(dataService, stationSelectors, unifiedOptions, dataServiceOption, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> AdditionalServiceProxy<_AttributeExtensions...>::abortAsync(const AdditionalServiceTypes::DataService& dataService, const Types::Types::StationSelectors& stationSelectors, const AdditionalServiceTypesOptions::UnifiedServiceOption& unifiedOptions, const AdditionalServiceTypesOptions::DataServiceOption& dataServiceOption, const uint32_t& handle, AbortAsyncCallback callback) {
    return delegate_->abortAsync(dataService, stationSelectors, unifiedOptions, dataServiceOption, handle, callback);
}


template <typename ... _AttributeExtensions>
std::string AdditionalServiceProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
const std::string& AdditionalServiceProxy<_AttributeExtensions...>::getDomain() const {
    return delegate_->getDomain();
}

template <typename ... _AttributeExtensions>
const std::string& AdditionalServiceProxy<_AttributeExtensions...>::getServiceId() const {
    return delegate_->getServiceId();
}

template <typename ... _AttributeExtensions>
const std::string& AdditionalServiceProxy<_AttributeExtensions...>::getInstanceId() const {
    return delegate_->getInstanceId();
}

template <typename ... _AttributeExtensions>
bool AdditionalServiceProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& AdditionalServiceProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& AdditionalServiceProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}

} // namespace AdditionalService
} // namespace IVIRadio



#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_PROXY_H_
