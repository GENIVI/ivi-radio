/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERADDITIONALSERVICE_Tuner_Additional_Service_H_
#define TUNERADDITIONALSERVICE_Tuner_Additional_Service_H_

#include <CommonAPI/types.h>

namespace TunerAdditionalService {

class TunerAdditionalService {
 public:
    virtual ~TunerAdditionalService() { }

    static inline const char* getInterfaceId();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* TunerAdditionalService::getInterfaceId() {
    return "TunerAdditionalService.TunerAdditionalService";
}

CommonAPI::Version TunerAdditionalService::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace TunerAdditionalService

namespace CommonAPI {

}


namespace std {
}

#endif // TUNERADDITIONALSERVICE_Tuner_Additional_Service_H_
