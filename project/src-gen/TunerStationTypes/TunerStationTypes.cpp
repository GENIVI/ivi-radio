/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "TunerStationTypes.h"

namespace TunerStationTypes {
namespace TunerStationTypes {

Metadata::Metadata(const std::string& strValue, const uint8_t& typeValue):
        str(strValue),
        type(typeValue)
{
}

bool operator==(const Metadata& lhs, const Metadata& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.str == rhs.str &&
        lhs.type == rhs.type
    ;
}

void Metadata::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> str;
    inputStream >> type;
}

void Metadata::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << str;
    outputStream << type;
}
SeekData::SeekData(const uint32_t& dataValue, const SeekMode& modeValue, const SeekReturnValue& returnValueValue):
        data(dataValue),
        mode(modeValue),
        returnValue(returnValueValue)
{
}

bool operator==(const SeekData& lhs, const SeekData& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.data == rhs.data &&
        lhs.mode == rhs.mode &&
        lhs.returnValue == rhs.returnValue
    ;
}

void SeekData::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> data;
    inputStream >> mode;
    inputStream >> returnValue;
}

void SeekData::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << data;
    outputStream << mode;
    outputStream << returnValue;
}
Station::Station(const TunerTypes::TunerTypes::UInt32s& flagsValue, const TunerTypes::TunerTypes::UInt32s& genreValue, const Metadatas& metaValue, const TunerTypes::TunerTypes::Strings& nameValue, const TunerTypes::TunerTypes::UInt32s& qualityValue, const StationSelector& selValue, const uint32_t& stationTypeValue):
        flags(flagsValue),
        genre(genreValue),
        meta(metaValue),
        name(nameValue),
        quality(qualityValue),
        sel(selValue),
        stationType(stationTypeValue)
{
}

bool operator==(const Station& lhs, const Station& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.flags == rhs.flags &&
        lhs.genre == rhs.genre &&
        lhs.meta == rhs.meta &&
        lhs.name == rhs.name &&
        lhs.quality == rhs.quality &&
        lhs.sel == rhs.sel &&
        lhs.stationType == rhs.stationType
    ;
}

void Station::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> flags;
    inputStream >> genre;
    inputStream >> meta;
    inputStream >> name;
    inputStream >> quality;
    inputStream >> sel;
    inputStream >> stationType;
}

void Station::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << flags;
    outputStream << genre;
    outputStream << meta;
    outputStream << name;
    outputStream << quality;
    outputStream << sel;
    outputStream << stationType;
}
StationList::StationList(const uint32_t& deviceTypeValue, const Stations& stationsValue, const uint32_t& stationTypeValue):
        deviceType(deviceTypeValue),
        stations(stationsValue),
        stationType(stationTypeValue)
{
}

bool operator==(const StationList& lhs, const StationList& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceType == rhs.deviceType &&
        lhs.stations == rhs.stations &&
        lhs.stationType == rhs.stationType
    ;
}

void StationList::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceType;
    inputStream >> stations;
    inputStream >> stationType;
}

void StationList::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceType;
    outputStream << stations;
    outputStream << stationType;
}
StationSelector::StationSelector(const uint32_t& deviceTypeValue, const TunerTypes::TunerTypes::UInt32s& idValue):
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

} // namespace TunerStationTypes
} // namespace TunerStationTypes
