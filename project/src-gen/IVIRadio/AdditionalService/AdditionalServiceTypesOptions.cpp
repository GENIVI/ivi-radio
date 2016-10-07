/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "AdditionalServiceTypesOptions.h"

namespace IVIRadio {
namespace AdditionalService {
namespace AdditionalServiceTypesOptions {

UnifiedServiceOption::UnifiedServiceOption(const Types::Types::UpdateType& requestTypeValue, const uint32_t& objectIDValue):
        requestType(requestTypeValue),
        objectID(objectIDValue)
{
}

bool operator==(const UnifiedServiceOption& lhs, const UnifiedServiceOption& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.requestType == rhs.requestType &&
        lhs.objectID == rhs.objectID
    ;
}

void UnifiedServiceOption::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> requestType;
    inputStream >> objectID;
}

void UnifiedServiceOption::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << requestType;
    outputStream << objectID;
}
Image_Options::Image_Options(const AdditionalServiceTypes::ImageType& imageTypeValue, const AdditionalServiceTypes::ImageService& imageServiceValue, const uint32_t& widthValue, const uint32_t& heigthValue):
        imageType(imageTypeValue),
        imageService(imageServiceValue),
        width(widthValue),
        heigth(heigthValue)
{
}

bool operator==(const Image_Options& lhs, const Image_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.imageType == rhs.imageType &&
        lhs.imageService == rhs.imageService &&
        lhs.width == rhs.width &&
        lhs.heigth == rhs.heigth
    ;
}

void Image_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> imageType;
    inputStream >> imageService;
    inputStream >> width;
    inputStream >> heigth;
}

void Image_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << imageType;
    outputStream << imageService;
    outputStream << width;
    outputStream << heigth;
}

bool operator==(const No_Options& lhs, const No_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void No_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void No_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
Journaline_Options::Journaline_Options(const bool& Entry_ObjectValue):
        Entry_Object(Entry_ObjectValue)
{
}

bool operator==(const Journaline_Options& lhs, const Journaline_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.Entry_Object == rhs.Entry_Object
    ;
}

void Journaline_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> Entry_Object;
}

void Journaline_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << Entry_Object;
}
Subtitle_Options::Subtitle_Options(const AdditionalServiceTypes::Languages& LanguagesValue):
        Languages(LanguagesValue)
{
}

bool operator==(const Subtitle_Options& lhs, const Subtitle_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.Languages == rhs.Languages
    ;
}

void Subtitle_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> Languages;
}

void Subtitle_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << Languages;
}
Teletext_Options::Teletext_Options(const bool& Entry_PageValue, const uint32_t& Sub_PageValue):
        Entry_Page(Entry_PageValue),
        Sub_Page(Sub_PageValue)
{
}

bool operator==(const Teletext_Options& lhs, const Teletext_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.Entry_Page == rhs.Entry_Page &&
        lhs.Sub_Page == rhs.Sub_Page
    ;
}

void Teletext_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> Entry_Page;
    inputStream >> Sub_Page;
}

void Teletext_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << Entry_Page;
    outputStream << Sub_Page;
}
EWS_Options::EWS_Options(const AdditionalServiceTypes::EWSType& TypeValue, const AdditionalServiceTypes::EWSAffectedArea& Affected_AreaValue):
        Type(TypeValue),
        Affected_Area(Affected_AreaValue)
{
}

bool operator==(const EWS_Options& lhs, const EWS_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.Type == rhs.Type &&
        lhs.Affected_Area == rhs.Affected_Area
    ;
}

void EWS_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> Type;
    inputStream >> Affected_Area;
}

void EWS_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << Type;
    outputStream << Affected_Area;
}
EPG_Options::EPG_Options(const Types::Types::DateTime& Start_Date_TimeValue, const Types::Types::DateTime& End_Date_TimeValue, const std::string& GenreValue, const uint32_t& Count_EventsValue):
        Start_Date_Time(Start_Date_TimeValue),
        End_Date_Time(End_Date_TimeValue),
        Genre(GenreValue),
        Count_Events(Count_EventsValue)
{
}

bool operator==(const EPG_Options& lhs, const EPG_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.Start_Date_Time == rhs.Start_Date_Time &&
        lhs.End_Date_Time == rhs.End_Date_Time &&
        lhs.Genre == rhs.Genre &&
        lhs.Count_Events == rhs.Count_Events
    ;
}

void EPG_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> Start_Date_Time;
    inputStream >> End_Date_Time;
    inputStream >> Genre;
    inputStream >> Count_Events;
}

void EPG_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << Start_Date_Time;
    outputStream << End_Date_Time;
    outputStream << Genre;
    outputStream << Count_Events;
}
Announcement_Options::Announcement_Options(const AdditionalServiceTypes::AnnouncementConfigurations& Type_ConfigurationsValue):
        Type_Configurations(Type_ConfigurationsValue)
{
}

bool operator==(const Announcement_Options& lhs, const Announcement_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.Type_Configurations == rhs.Type_Configurations
    ;
}

void Announcement_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> Type_Configurations;
}

void Announcement_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << Type_Configurations;
}

} // namespace AdditionalServiceTypesOptions
} // namespace AdditionalService
} // namespace IVIRadio
