/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_STUB_H_
#define IVIRADIO_CONFIGURATION_Configuration_STUB_H_

#include <IVIRadio/Configuration/ConfigurationOptions.h>
#include <cstdint>
#include <IVIRadio/Configuration/ConfigurationTypesEnum.h>
#include <CommonAPI/InputStream.h>
#include <vector>
#include <IVIRadio/Configuration/ConfigurationOptionsGetter.h>
#include <CommonAPI/OutputStream.h>
#include <IVIRadio/Types/Types.h>
#include "Configuration.h"
#include <CommonAPI/Stub.h>

namespace IVIRadio {
namespace Configuration {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service Configuration. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class ConfigurationStubAdapter: virtual public CommonAPI::StubAdapter, public Configuration {
 public:

    /**
     * Sends a broadcast event for functionalityConfiguration. Should not be called directly.
     * Instead, the "fire<broadcastName>Event" methods of the stub should be used.
     */
    virtual void fireFunctionalityConfigurationEvent(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptions, const uint32_t& handle_out, const Types::Types::ErrorCodes& errorCode) = 0;
};


/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for Configuration.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class ConfigurationStubRemoteEvent {
 public:
    virtual ~ConfigurationStubRemoteEvent() { }

};


/**
 * Defines the interface that must be implemented by any class that should provide
 * the service Configuration to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class ConfigurationStub : public CommonAPI::Stub<ConfigurationStubAdapter , ConfigurationStubRemoteEvent> {
 public:
    virtual ~ConfigurationStub() { }


    /// This is the method that will be called on remote calls on the method changeFunctionalityConfiguration.
    virtual void changeFunctionalityConfiguration(ConfigurationTypesEnum::FunctionalityTypes functionalityTypes, ConfigurationOptions::FuntionalityOptions functionalityOptionsSet, uint32_t handle, uint32_t& handleOut, Types::Types::Feedback& feedback) = 0;
    /// This is the method that will be called on remote calls on the method requestFunctionalityConfiguration.
    virtual void requestFunctionalityConfiguration(ConfigurationTypesEnum::FunctionalityTypes functionalityTypes, ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityOptionsGet, uint32_t handle, uint32_t& handle_out, Types::Types::Feedback& feedback) = 0;
    
    /// Sends a broadcast event for functionalityConfiguration.
    virtual void fireFunctionalityConfigurationEvent(const ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes, const ConfigurationOptions::FuntionalityOptions& functionalityOptions, const uint32_t& handle_out, const Types::Types::ErrorCodes& errorCode) = 0;
};

} // namespace Configuration
} // namespace IVIRadio

#endif // IVIRADIO_CONFIGURATION_Configuration_STUB_H_
