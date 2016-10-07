/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_PROXY_BASE_H_
#define IVIRADIO_CONFIGURATION_Configuration_PROXY_BASE_H_

#include "Configuration.h"
#include <IVIRadio/Configuration/ConfigurationOptions.h>
#include <cstdint>
#include <IVIRadio/Configuration/ConfigurationTypesEnum.h>
#include <CommonAPI/InputStream.h>
#include <vector>
#include <IVIRadio/Configuration/ConfigurationOptionsGetter.h>
#include <CommonAPI/OutputStream.h>
#include <IVIRadio/Types/Types.h>
#include <CommonAPI/Event.h>
#include <CommonAPI/Proxy.h>
#include <functional>
#include <future>

namespace IVIRadio {
namespace Configuration {

class ConfigurationProxyBase: virtual public CommonAPI::Proxy {
 public:
    typedef CommonAPI::Event<ConfigurationTypesEnum::FunctionalityTypes, ConfigurationOptions::FuntionalityOptions, uint32_t, Types::Types::ErrorCodes> FunctionalityConfigurationEvent;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> ChangeFunctionalityConfigurationAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const uint32_t&, const Types::Types::Feedback&)> RequestFunctionalityConfigurationAsyncCallback;


    virtual FunctionalityConfigurationEvent& getFunctionalityConfigurationEvent() = 0;


    virtual void changeFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> changeFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptionsSet, const uint32_t& handle, ChangeFunctionalityConfigurationAsyncCallback callback) = 0;

    virtual void requestFunctionalityConfiguration(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, CommonAPI::CallStatus& callStatus, uint32_t& handle_out, Types::Types::Feedback& feedback) = 0;
    virtual std::future<CommonAPI::CallStatus> requestFunctionalityConfigurationAsync(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptionsGetter::FuntionalityOptionsGet& functionalityOptionsGet, const uint32_t& handle, RequestFunctionalityConfigurationAsyncCallback callback) = 0;
};


} // namespace Configuration
} // namespace IVIRadio

#endif // IVIRADIO_CONFIGURATION_Configuration_PROXY_BASE_H_
