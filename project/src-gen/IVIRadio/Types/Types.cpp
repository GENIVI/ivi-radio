/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "Types.h"

namespace IVIRadio {
namespace Types {
namespace Types {

StationSelector::StationSelector(const uint32_t& deviceTypeValue, const UInt32s& idValue):
        deviceType(deviceTypeValue),
        id(idValue)
{
}

bool operator==(const StationSelector& lhs, const StationSelector& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceType == rhs.deviceType &&
        lhs.id == rhs.id
    ;
}

void StationSelector::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceType;
    inputStream >> id;
}

void StationSelector::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceType;
    outputStream << id;
}

} // namespace Types
} // namespace Types
} // namespace IVIRadio
