/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "MGEGTunerAdditionalServiceTypes.h"

namespace MGEGTunerAdditionalServiceTypes {
namespace MGEGTunerAdditionalServiceTypes {

MGEG_AnnouncementTypeConfiguration::MGEG_AnnouncementTypeConfiguration(const MGEG_AnnouncementType& typeValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& activeValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& priorityValue):
        type(typeValue),
        active(activeValue),
        priority(priorityValue)
{
}

bool operator==(const MGEG_AnnouncementTypeConfiguration& lhs, const MGEG_AnnouncementTypeConfiguration& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.type == rhs.type &&
        lhs.active == rhs.active &&
        lhs.priority == rhs.priority
    ;
}

void MGEG_AnnouncementTypeConfiguration::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> type;
    inputStream >> active;
    inputStream >> priority;
}

void MGEG_AnnouncementTypeConfiguration::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << type;
    outputStream << active;
    outputStream << priority;
}
MGEG_Announcement_TypeOptions::MGEG_Announcement_TypeOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& activeValue, const MGEG_AnnouncementTypeConfigurations& typeConfigurationValue):
        active(activeValue),
        typeConfiguration(typeConfigurationValue)
{
}

bool operator==(const MGEG_Announcement_TypeOptions& lhs, const MGEG_Announcement_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.active == rhs.active &&
        lhs.typeConfiguration == rhs.typeConfiguration
    ;
}

void MGEG_Announcement_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> active;
    inputStream >> typeConfiguration;
}

void MGEG_Announcement_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << active;
    outputStream << typeConfiguration;
}
MGEG_Announcement_Options::MGEG_Announcement_Options(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& activityValue, const MGEG_AnnouncementTypeConfiguration& typeConfigurationValue):
        activity(activityValue),
        typeConfiguration(typeConfigurationValue)
{
}

bool operator==(const MGEG_Announcement_Options& lhs, const MGEG_Announcement_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.activity == rhs.activity &&
        lhs.typeConfiguration == rhs.typeConfiguration
    ;
}

void MGEG_Announcement_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> activity;
    inputStream >> typeConfiguration;
}

void MGEG_Announcement_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << activity;
    outputStream << typeConfiguration;
}

bool operator==(const MGEG_BWS_TypeOptions& lhs, const MGEG_BWS_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_BWS_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_BWS_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_BWS_Options& lhs, const MGEG_BWS_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_BWS_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_BWS_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Journaline_TypeOptions& lhs, const MGEG_Journaline_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Journaline_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Journaline_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Journaline_Options& lhs, const MGEG_Journaline_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Journaline_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Journaline_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_NoComponent_TypeOptions& lhs, const MGEG_NoComponent_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_NoComponent_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_NoComponent_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_NoComponent__Options& lhs, const MGEG_NoComponent__Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_NoComponent__Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_NoComponent__Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Slideshow_TypeOptions& lhs, const MGEG_Slideshow_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Slideshow_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Slideshow_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Slideshow_Options& lhs, const MGEG_Slideshow_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Slideshow_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Slideshow_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Subtitle_TypeOptions& lhs, const MGEG_Subtitle_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Subtitle_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Subtitle_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Subtitle_Options& lhs, const MGEG_Subtitle_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Subtitle_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Subtitle_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_TMC_TypeOptions& lhs, const MGEG_TMC_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_TMC_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_TMC_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_TMC_Options& lhs, const MGEG_TMC_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_TMC_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_TMC_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_TPEG_TypeOptions& lhs, const MGEG_TPEG_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_TPEG_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_TPEG_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Teletext_TypeOptions& lhs, const MGEG_Teletext_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Teletext_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Teletext_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_TPEG_Options& lhs, const MGEG_TPEG_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_TPEG_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_TPEG_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
MGEG_EPG_TypeOptions::MGEG_EPG_TypeOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& activeValue):
        active(activeValue)
{
}

bool operator==(const MGEG_EPG_TypeOptions& lhs, const MGEG_EPG_TypeOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.active == rhs.active
    ;
}

void MGEG_EPG_TypeOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> active;
}

void MGEG_EPG_TypeOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << active;
}

bool operator==(const MGEG_Teletext_Options& lhs, const MGEG_Teletext_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Teletext_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Teletext_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
MGEG_EPG_Options::MGEG_EPG_Options(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& activeValue):
        active(activeValue)
{
}

bool operator==(const MGEG_EPG_Options& lhs, const MGEG_EPG_Options& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.active == rhs.active
    ;
}

void MGEG_EPG_Options::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> active;
}

void MGEG_EPG_Options::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << active;
}
MGEG_Announcement_Parameter::MGEG_Announcement_Parameter(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& abortValue):
        abort(abortValue)
{
}

bool operator==(const MGEG_Announcement_Parameter& lhs, const MGEG_Announcement_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.abort == rhs.abort
    ;
}

void MGEG_Announcement_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> abort;
}

void MGEG_Announcement_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << abort;
}

bool operator==(const MGEG_BWS_Parameter& lhs, const MGEG_BWS_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_BWS_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_BWS_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
MGEG_EPG_Parameter::MGEG_EPG_Parameter(const MGEGTunerTypes::MGEGTunerTypes::MGEG_DateTime& startDateValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_DateTime& endDateValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_String& genreValue, const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& stationValue, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& eventIDValue):
        startDate(startDateValue),
        endDate(endDateValue),
        genre(genreValue),
        station(stationValue),
        eventID(eventIDValue)
{
}

bool operator==(const MGEG_EPG_Parameter& lhs, const MGEG_EPG_Parameter& rhs) {
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

void MGEG_EPG_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> startDate;
    inputStream >> endDate;
    inputStream >> genre;
    inputStream >> station;
    inputStream >> eventID;
}

void MGEG_EPG_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << startDate;
    outputStream << endDate;
    outputStream << genre;
    outputStream << station;
    outputStream << eventID;
}

bool operator==(const MGEG_Journaline_Parameter& lhs, const MGEG_Journaline_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Journaline_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Journaline_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_NoComponenttype_Parameter& lhs, const MGEG_NoComponenttype_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_NoComponenttype_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_NoComponenttype_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Slideshow_Parameter& lhs, const MGEG_Slideshow_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Slideshow_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Slideshow_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_Subtitle_Parameter& lhs, const MGEG_Subtitle_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_Subtitle_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_Subtitle_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_TMC_Parameter& lhs, const MGEG_TMC_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_TMC_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_TMC_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_TPEG_Parameter& lhs, const MGEG_TPEG_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_TPEG_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_TPEG_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const MGEG_TeleText_Parameter& lhs, const MGEG_TeleText_Parameter& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void MGEG_TeleText_Parameter::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void MGEG_TeleText_Parameter::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
MGEG_Announcement::MGEG_Announcement(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentIDValue, const MGEG_AnnouncementType& typeValue):
        componentID(componentIDValue),
        type(typeValue)
{
}

bool operator==(const MGEG_Announcement& lhs, const MGEG_Announcement& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.componentID == rhs.componentID &&
        lhs.type == rhs.type
    ;
}

void MGEG_Announcement::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> componentID;
    inputStream >> type;
}

void MGEG_Announcement::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << componentID;
    outputStream << type;
}

} // namespace MGEGTunerAdditionalServiceTypes
} // namespace MGEGTunerAdditionalServiceTypes
