/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERSTATION_MGEG_Tuner_Station_H_
#define MGEGTUNERSTATION_MGEG_Tuner_Station_H_

#include <CommonAPI/types.h>

namespace MGEGTunerStation {

class MGEGTunerStation {
 public:
    virtual ~MGEGTunerStation() { }

    static inline const char* getInterfaceId();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* MGEGTunerStation::getInterfaceId() {
    return "MGEGTunerStation.MGEGTunerStation";
}

CommonAPI::Version MGEGTunerStation::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace MGEGTunerStation

namespace CommonAPI {

}


namespace std {
}

#endif // MGEGTUNERSTATION_MGEG_Tuner_Station_H_
