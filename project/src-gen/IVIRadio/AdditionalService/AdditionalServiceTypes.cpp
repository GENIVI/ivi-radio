/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "AdditionalServiceTypes.h"

namespace IVIRadio {
namespace AdditionalService {
namespace AdditionalServiceTypes {

Language::Language(const std::string& NameValue):
        Name(NameValue)
{
}

bool operator==(const Language& lhs, const Language& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.Name == rhs.Name
    ;
}

void Language::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> Name;
}

void Language::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << Name;
}
Announcement::Announcement(const Types::Types::StationSelector& stationSelectorValue, const AnnouncementType& typeValue):
        stationSelector(stationSelectorValue),
        type(typeValue)
{
}

bool operator==(const Announcement& lhs, const Announcement& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.stationSelector == rhs.stationSelector &&
        lhs.type == rhs.type
    ;
}

void Announcement::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> stationSelector;
    inputStream >> type;
}

void Announcement::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << stationSelector;
    outputStream << type;
}
AnnouncementConfiguration::AnnouncementConfiguration(const AnnouncementType& typeValue, const Types::Types::Activation& activeValue, const uint32_t& priorityValue):
        type(typeValue),
        active(activeValue),
        priority(priorityValue)
{
}

bool operator==(const AnnouncementConfiguration& lhs, const AnnouncementConfiguration& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.type == rhs.type &&
        lhs.active == rhs.active &&
        lhs.priority == rhs.priority
    ;
}

void AnnouncementConfiguration::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> type;
    inputStream >> active;
    inputStream >> priority;
}

void AnnouncementConfiguration::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << type;
    outputStream << active;
    outputStream << priority;
}

} // namespace AdditionalServiceTypes
} // namespace AdditionalService
} // namespace IVIRadio
