/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <IVIRadio/Configuration/ConfigurationStubDefault.h>

namespace IVIRadio {
namespace Configuration {

ConfigurationStubDefault::ConfigurationStubDefault():
        remoteEventHandler_(this) {
}

ConfigurationStubRemoteEvent* ConfigurationStubDefault::initStubAdapter(const std::shared_ptr<ConfigurationStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void ConfigurationStubDefault::changeFunctionalityConfiguration(ConfigurationTypesEnum::FunctionalityTypes functionalityTypes, ConfigurationOptions::FuntionalityOptions functionalityOptionsSet, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) {
    // No operation in default
}

void ConfigurationStubDefault::requestFunctionalityConfiguration(ConfigurationTypesEnum::FunctionalityTypes functionalityTypes, ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityOptionsGet, uint32_t handle, uint32_t& handle_out, Types::Types::Feedback& feedback) {
    // No operation in default
}


void ConfigurationStubDefault::fireFunctionalityConfigurationEvent(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptions, const uint32_t& handle_out, const Types::Types::ErrorCodes& errorCode) {
    stubAdapter_->fireFunctionalityConfigurationEvent(functionalityTypes, functionalityOptions, handle_out, errorCode);
}

ConfigurationStubDefault::RemoteEventHandler::RemoteEventHandler(ConfigurationStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace Configuration
} // namespace IVIRadio
