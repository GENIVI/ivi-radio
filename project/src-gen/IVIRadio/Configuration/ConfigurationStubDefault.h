/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_STUB_DEFAULT_H_
#define IVIRADIO_CONFIGURATION_Configuration_STUB_DEFAULT_H_

#include <IVIRadio/Configuration/ConfigurationStub.h>

namespace IVIRadio {
namespace Configuration {

/**
 * Provides a default implementation for ConfigurationStubRemoteEvent and
 * ConfigurationStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 * 
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class ConfigurationStubDefault : public ConfigurationStub {
 public:
    ConfigurationStubDefault();

    ConfigurationStubRemoteEvent* initStubAdapter(const std::shared_ptr<ConfigurationStubAdapter>& stubAdapter);


    virtual void changeFunctionalityConfiguration(ConfigurationTypesEnum::FunctionalityTypes functionalityTypes, ConfigurationOptions::FuntionalityOptions functionalityOptionsSet, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback);

    virtual void requestFunctionalityConfiguration(ConfigurationTypesEnum::FunctionalityTypes functionalityTypes, ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityOptionsGet, uint32_t handle, uint32_t& handle_out, Types::Types::Feedback& feedback);

    
    virtual void fireFunctionalityConfigurationEvent(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptions, const uint32_t& handle_out, const Types::Types::ErrorCodes& errorCode);

 protected:
    
 private:
    class RemoteEventHandler: public ConfigurationStubRemoteEvent {
     public:
        RemoteEventHandler(ConfigurationStubDefault* defaultStub);


     private:
        ConfigurationStubDefault* defaultStub_;
    };

    RemoteEventHandler remoteEventHandler_;
    std::shared_ptr<ConfigurationStubAdapter> stubAdapter_;

};

} // namespace Configuration
} // namespace IVIRadio

#endif // IVIRADIO_CONFIGURATION_Configuration_STUB_DEFAULT_H_
