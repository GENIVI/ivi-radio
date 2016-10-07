/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_H_
#define MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_H_

#include <CommonAPI/types.h>

namespace MGEGTunerAdditionalService {

class MGEGTunerAdditionalService {
 public:
    virtual ~MGEGTunerAdditionalService() { }

    static inline const char* getInterfaceId();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* MGEGTunerAdditionalService::getInterfaceId() {
    return "MGEGTunerAdditionalService.MGEGTunerAdditionalService";
}

CommonAPI::Version MGEGTunerAdditionalService::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace MGEGTunerAdditionalService

namespace CommonAPI {

}


namespace std {
}

#endif // MGEGTUNERADDITIONALSERVICE_MGEG_Tuner_Additional_Service_H_
