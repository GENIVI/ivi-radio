/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "MGEGTunerStationTypes.h"

namespace MGEGTunerStationTypes {
namespace MGEGTunerStationTypes {

Metadata::Metadata(const MGEGTunerTypes::MGEGTunerTypes::MGEG_String& strValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& typeValue):
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
SeekData::SeekData(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& dataValue, const SeekMode& modeValue, const SeekReturnValue& returnValueValue):
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
Station::Station(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flagsValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& genreValue, const MGEG_Metadatas& metaValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Strings& nameValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& qualityValue, const StationSelector& selValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationTypeValue):
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
StationList::StationList(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& deviceTypeValue, const MGEG_Stations& stationsValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationTypeValue):
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
StationSelector::StationSelector(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& deviceTypeValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& idValue):
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

} // namespace MGEGTunerStationTypes
} // namespace MGEGTunerStationTypes
