/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_PROXY_H_
#define IVIRADIO_CONFIGURATION_Configuration_PROXY_H_

#include "ConfigurationProxyBase.h"

namespace IVIRadio {
namespace Configuration {

template <typename ... _AttributeExtensions>
class ConfigurationProxy: virtual public Configuration, virtual public ConfigurationProxyBase, public _AttributeExtensions... {
 public:
    ConfigurationProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~ConfigurationProxy();


    /// Returns the wrapper class that provides access to the broadcast functionalityConfiguration.
    virtual FunctionalityConfigurationEvent& getFunctionalityConfigurationEvent();


    /**
     * Calls changeFunctionalityConfiguration with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void changeFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback);
    /**
     * Calls changeFunctionalityConfiguration with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> changeFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, ChangeFunctionalityConfigurationAsyncCallback callback);

    /**
     * Calls requestFunctionalityConfiguration with synchronous semantics.
     * 
     * All const parameters are input parameters to this method.
     * All non-const parameters will be filled with the returned values.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     * Synchronous calls are not supported (will block indefinitely) when mainloop integration is used.
     */
    virtual void requestFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, Types::Types::Feedback& feedback);
    /**
     * Calls requestFunctionalityConfiguration with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> requestFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, RequestFunctionalityConfigurationAsyncCallback callback);

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
    std::shared_ptr<ConfigurationProxyBase> delegate_;
};


//
// ConfigurationProxy Implementation
//
template <typename ... _AttributeExtensions>
ConfigurationProxy<_AttributeExtensions...>::ConfigurationProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        delegate_(std::dynamic_pointer_cast<ConfigurationProxyBase>(delegate)),
        _AttributeExtensions(*(std::dynamic_pointer_cast<ConfigurationProxyBase>(delegate)))... {
}

template <typename ... _AttributeExtensions>
ConfigurationProxy<_AttributeExtensions...>::~ConfigurationProxy() {
}


template <typename ... _AttributeExtensions>
typename ConfigurationProxy<_AttributeExtensions...>::FunctionalityConfigurationEvent& ConfigurationProxy<_AttributeExtensions...>::getFunctionalityConfigurationEvent() {
    return delegate_->getFunctionalityConfigurationEvent();
}


template <typename ... _AttributeExtensions>
void ConfigurationProxy<_AttributeExtensions...>::changeFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    delegate_->changeFunctionalityConfiguration(functionalityTypes, functionalityOptionsSet, handle, callStatus, handleOut, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ConfigurationProxy<_AttributeExtensions...>::changeFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, ChangeFunctionalityConfigurationAsyncCallback callback) {
    return delegate_->changeFunctionalityConfigurationAsync(functionalityTypes, functionalityOptionsSet, handle, callback);
}

template <typename ... _AttributeExtensions>
void ConfigurationProxy<_AttributeExtensions...>::requestFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, Types::Types::Feedback& feedback) {
    delegate_->requestFunctionalityConfiguration(functionalityTypes, functionalityOptionsGet, handle, callStatus, handle_out, feedback);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ConfigurationProxy<_AttributeExtensions...>::requestFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, RequestFunctionalityConfigurationAsyncCallback callback) {
    return delegate_->requestFunctionalityConfigurationAsync(functionalityTypes, functionalityOptionsGet, handle, callback);
}


template <typename ... _AttributeExtensions>
std::string ConfigurationProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
const std::string& ConfigurationProxy<_AttributeExtensions...>::getDomain() const {
    return delegate_->getDomain();
}

template <typename ... _AttributeExtensions>
const std::string& ConfigurationProxy<_AttributeExtensions...>::getServiceId() const {
    return delegate_->getServiceId();
}

template <typename ... _AttributeExtensions>
const std::string& ConfigurationProxy<_AttributeExtensions...>::getInstanceId() const {
    return delegate_->getInstanceId();
}

template <typename ... _AttributeExtensions>
bool ConfigurationProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& ConfigurationProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& ConfigurationProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}

} // namespace Configuration
} // namespace IVIRadio



#endif // IVIRADIO_CONFIGURATION_Configuration_PROXY_H_
