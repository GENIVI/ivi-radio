/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "TunerAdditionalServiceTypes.h"

namespace TunerAdditionalServiceTypes {
namespace TunerAdditionalServiceTypes {

AnnouncementTypeConfiguration::AnnouncementTypeConfiguration(const AnnouncementType& typeValue, const TunerTypes::TunerTypes::Activation& activeValue, const uint32_t& priorityValue):
        type(typeValue),
        active(activeValue),
        priority(priorityValue)
{
}

bool operator==(const AnnouncementTypeConfiguration& lhs, const AnnouncementTypeConfiguration& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.type == rhs.type &&
        lhs.active == rhs.active &&
        lhs.priority == rhs.priority
    ;
}

void AnnouncementTypeConfiguration::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> type;
    inputStream >> active;
    inputStream >> priority;
}

void AnnouncementTypeConfiguration::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << type;
    outputStream << active;
    outputStream << priority;
}
Announcement_TypeOptions::Announcement_TypeOptions(const TunerTypes::TunerTypes::Activation& activeValue, const AnnouncementTypeConfigurations& typeConfigurationValue):
        active(activeValue),
        typeConfiguration(typeConfigurationValue)
{
}

bool operator==(const Announcement_TypeOptions& lhs, const Announcement_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.active == rhs.active &&
        lhs.typeConfiguration == rhs.typeConfiguration
    ;
}

void Announcement_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> active;
    inputStream >> typeConfiguration;
}

void Announcement_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << active;
    outputStream << typeConfiguration;
}
Announcement_Options::Announcement_Options(const TunerTypes::TunerTypes::Activation& activityValue, const AnnouncementTypeConfiguration& typeConfigurationValue):
        activity(activityValue),
        typeConfiguration(typeConfigurationValue)
{
}

bool operator==(const Announcement_Options& lhs, const Announcement_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.activity == rhs.activity &&
        lhs.typeConfiguration == rhs.typeConfiguration
    ;
}

void Announcement_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> activity;
    inputStream >> typeConfiguration;
}

void Announcement_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << activity;
    outputStream << typeConfiguration;
}

bool operator==(const BWS_TypeOptions& lhs, const BWS_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void BWS_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void BWS_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const BWS_Options& lhs, const BWS_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void BWS_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void BWS_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Journaline_TypeOptions& lhs, const Journaline_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Journaline_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Journaline_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Journaline_Options& lhs, const Journaline_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Journaline_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Journaline_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const NoComponent_TypeOptions& lhs, const NoComponent_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void NoComponent_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void NoComponent_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const NoComponent__Options& lhs, const NoComponent__Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void NoComponent__Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void NoComponent__Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Slideshow_TypeOptions& lhs, const Slideshow_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Slideshow_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Slideshow_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Slideshow_Options& lhs, const Slideshow_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Slideshow_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Slideshow_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Subtitle_TypeOptions& lhs, const Subtitle_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Subtitle_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Subtitle_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Subtitle_Options& lhs, const Subtitle_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Subtitle_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Subtitle_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const TMC_TypeOptions& lhs, const TMC_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void TMC_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void TMC_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const TMC_Options& lhs, const TMC_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void TMC_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void TMC_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const TPEG_TypeOptions& lhs, const TPEG_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void TPEG_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void TPEG_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Teletext_TypeOptions& lhs, const Teletext_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Teletext_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Teletext_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const TPEG_Options& lhs, const TPEG_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void TPEG_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void TPEG_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
EPG_TypeOptions::EPG_TypeOptions(const TunerTypes::TunerTypes::Activation& activeValue):
        active(activeValue)
{
}

bool operator==(const EPG_TypeOptions& lhs, const EPG_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.active == rhs.active
    ;
}

void EPG_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> active;
}

void EPG_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << active;
}

bool operator==(const Teletext_Options& lhs, const Teletext_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Teletext_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Teletext_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
EPG_Options::EPG_Options(const TunerTypes::TunerTypes::Activation& activeValue):
        active(activeValue)
{
}

bool operator==(const EPG_Options& lhs, const EPG_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.active == rhs.active
    ;
}

void EPG_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> active;
}

void EPG_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << active;
}
Announcement_Parameter::Announcement_Parameter(const bool& abortValue):
        abort(abortValue)
{
}

bool operator==(const Announcement_Parameter& lhs, const Announcement_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.abort == rhs.abort
    ;
}

void Announcement_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> abort;
}

void Announcement_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << abort;
}

bool operator==(const BWS_Parameter& lhs, const BWS_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void BWS_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void BWS_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
EPG_Parameter::EPG_Parameter(const TunerTypes::TunerTypes::DateTime& startDateValue, const TunerTypes::TunerTypes::DateTime& endDateValue, const std::string& genreValue, const TunerStationTypes::TunerStationTypes::StationSelector& stationValue, const uint32_t& eventIDValue):
        startDate(startDateValue),
        endDate(endDateValue),
        genre(genreValue),
        station(stationValue),
        eventID(eventIDValue)
{
}

bool operator==(const EPG_Parameter& lhs, const EPG_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.startDate == rhs.startDate &&
        lhs.endDate == rhs.endDate &&
        lhs.genre == rhs.genre &&
        lhs.station == rhs.station &&
        lhs.eventID == rhs.eventID
    ;
}

void EPG_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> startDate;
    inputStream >> endDate;
    inputStream >> genre;
    inputStream >> station;
    inputStream >> eventID;
}

void EPG_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << startDate;
    outputStream << endDate;
    outputStream << genre;
    outputStream << station;
    outputStream << eventID;
}

bool operator==(const Journaline_Parameter& lhs, const Journaline_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Journaline_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Journaline_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const NoComponenttype_Parameter& lhs, const NoComponenttype_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void NoComponenttype_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void NoComponenttype_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Slideshow_Parameter& lhs, const Slideshow_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Slideshow_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Slideshow_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const Subtitle_Parameter& lhs, const Subtitle_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void Subtitle_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void Subtitle_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const TMC_Parameter& lhs, const TMC_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void TMC_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void TMC_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const TPEG_Parameter& lhs, const TPEG_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void TPEG_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void TPEG_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const TeleText_Parameter& lhs, const TeleText_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void TeleText_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void TeleText_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
Announcement::Announcement(const uint32_t& componentIDValue, const AnnouncementType& typeValue):
        componentID(componentIDValue),
        type(typeValue)
{
}

bool operator==(const Announcement& lhs, const Announcement& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.componentID == rhs.componentID &&
        lhs.type == rhs.type
    ;
}

void Announcement::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> componentID;
    inputStream >> type;
}

void Announcement::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << componentID;
    outputStream << type;
}

} // namespace TunerAdditionalServiceTypes
} // namespace TunerAdditionalServiceTypes
