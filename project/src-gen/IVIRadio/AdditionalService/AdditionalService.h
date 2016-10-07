/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_H_

#include <CommonAPI/types.h>

namespace IVIRadio {
namespace AdditionalService {

class AdditionalService {
 public:
    virtual ~AdditionalService() { }

    static inline const char* getInterfaceId();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* AdditionalService::getInterfaceId() {
    return "IVIRadio.AdditionalService.AdditionalService";
}

CommonAPI::Version AdditionalService::getInterfaceVersion() {
    return CommonAPI::Version(2, 0);
}


} // namespace AdditionalService
} // namespace IVIRadio

namespace CommonAPI {

}


namespace std {
}

#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_H_
