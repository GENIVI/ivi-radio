/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_STATION_Station_H_
#define IVIRADIO_STATION_Station_H_

#include <CommonAPI/types.h>

namespace IVIRadio {
namespace Station {

class Station {
 public:
    virtual ~Station() { }

    static inline const char* getInterfaceId();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* Station::getInterfaceId() {
    return "IVIRadio.Station.Station";
}

CommonAPI::Version Station::getInterfaceVersion() {
    return CommonAPI::Version(2, 0);
}


} // namespace Station
} // namespace IVIRadio

namespace CommonAPI {

}


namespace std {
}

#endif // IVIRADIO_STATION_Station_H_
