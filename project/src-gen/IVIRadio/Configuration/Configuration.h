/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_H_
#define IVIRADIO_CONFIGURATION_Configuration_H_

#include <CommonAPI/types.h>

namespace IVIRadio {
namespace Configuration {

class Configuration {
 public:
    virtual ~Configuration() { }

    static inline const char* getInterfaceId();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* Configuration::getInterfaceId() {
    return "IVIRadio.Configuration.Configuration";
}

CommonAPI::Version Configuration::getInterfaceVersion() {
    return CommonAPI::Version(2, 0);
}


} // namespace Configuration
} // namespace IVIRadio

namespace CommonAPI {

}


namespace std {
}

#endif // IVIRADIO_CONFIGURATION_Configuration_H_
