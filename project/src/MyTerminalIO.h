/*
Copyright (C) 2013 BMW Group

Author: Guido Ostkamp     (guido.ostkamp@de.bertrandt.com)
Author: Bernhard Singer   (bernhard.singer@partner.bmw.de)
Author: Matthias Freundel (matthias.freundel@partner.bmw.de)

This Source Code Form is subject to the terms of the Mozilla Public

License, v. 2.0. If a copy of the MPL was not distributed with this file,

You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef MY_TERMINALIO_H
#define MY_TERMINALIO_H
#include <memory>
#include <iostream>
#include <unistd.h>
#include <map>

#include <TunerStation/TunerStationStubDefault.h>
#include <TunerTypes/TunerTypes.h>
#include <TunerStationTypes/TunerStationTypes.h>

#include <TunerAdditionalService/TunerAdditionalServiceStubDefault.h>
#include <TunerAdditionalServiceTypes/TunerAdditionalServiceTypes.h>

#include <CommonAPI/Runtime.h>

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

using namespace std;

class MyTerminalIO
{
public:
    static MyTerminalIO *getInstance();

    // utility functions

    void printMaps();

    unsigned int
    readNumber(unsigned int minval, unsigned int maxval, string question, string menu = "");

    bool
    readBoolean(string question);

    // functions reading input from console via menu

    TunerStationTypes::TunerStationTypes::StationType
    enterStationType();

    TunerStationTypes::TunerStationTypes::SeekMode
    enterSeekMode();

    TunerStationTypes::TunerStationTypes::SelectionMode
    enterSelectionMode();

    TunerStationTypes::TunerStationTypes::UpdateElement
    enterUpdateElement();

    TunerStationTypes::TunerStationTypes::SourceType
    enterSourceType();

    TunerStationTypes::TunerStationTypes::DeviceType
    enterDeviceType();

    TunerTypes::TunerTypes::Feedback
    enterFeedback();

    TunerStationTypes::TunerStationTypes::UpdateType
    enterUpdateType();

    TunerStationTypes::TunerStationTypes::FlagsDefUndef
    enterFlagsDefUndef();

    TunerStationTypes::TunerStationTypes::FlagsDefAmFm
    enterFlagsDefAmFm();

    TunerStationTypes::TunerStationTypes::FlagsDefDab
    enterFlagsDefDab();

    TunerStationTypes::TunerStationTypes::QualityIndexUndef
    enterQualityIndexUndef();

    TunerStationTypes::TunerStationTypes::QualityIndexAmFm
    enterQualityIndexAmFm();

    TunerStationTypes::TunerStationTypes::QualityIndexDab
    enterQualityIndexDab();

    TunerStationTypes::TunerStationTypes::NameIndexDab
    enterNameIndexDab();

    TunerStationTypes::TunerStationTypes::NameIndexAmFm
    enterNameIndexAmFm();

    TunerStationTypes::TunerStationTypes::NameIndexUndef
    enterNameIndexUndef();

    TunerStationTypes::TunerStationTypes::IdIndexDab
    enterIdIndexDab();

    TunerStationTypes::TunerStationTypes::IdIndexAmFm
    enterIdIndexAmFm();

    TunerStationTypes::TunerStationTypes::IdIndexUndef
    enterIdIndexUndef();

    uint32_t
    enterHandle();

    uint32_t
    enterFrequencyFM();

    uint32_t
    enterPi();

    uint32_t
    enterFrequencyDAB();

    uint32_t
    enterUniqueKey();

    uint32_t
    enterParent();

    uint32_t
    enterService();

    uint32_t
    enterEnsemble();

    uint32_t
    enterComponent();

    uint8_t
    enterGenre();

    TunerTypes::TunerTypes::UInt32s
    enterFlags();

    bool
    enterPermanent();

    // following function is overloaded

    TunerStationTypes::TunerStationTypes::StationSelector
    enterStationSelector();

    TunerStationTypes::TunerStationTypes::StationSelector
    enterStationSelector(
        TunerStationTypes::TunerStationTypes::SelectionMode selectionMode,
        const TunerStationTypes::TunerStationTypes::StationList& stationsAMFM,
        const TunerStationTypes::TunerStationTypes::StationList& stationsDAB,
        const TunerStationTypes::TunerStationTypes::StationList& stationsUndef
    );

    void
    enterStartTuneParameters(
        TunerStationTypes::TunerStationTypes::StationSelector &station,
        TunerStationTypes::TunerStationTypes::SelectionMode &selectionMode,
        const TunerStationTypes::TunerStationTypes::StationList& stationsAMFM,
        const TunerStationTypes::TunerStationTypes::StationList& stationsDAB,
        const TunerStationTypes::TunerStationTypes::StationList& stationsUndef,
        uint32_t &handle
    );

    void
    enterAbortTuneParameters(
        TunerStationTypes::TunerStationTypes::DeviceType &deviceType,
        uint32_t &handle
    );

    // no return here, just use by reference parameters
    void
    enterSeekParameters(
        TunerStationTypes::TunerStationTypes::DeviceType &deviceType,
        TunerStationTypes::TunerStationTypes::SeekMode &seekMode,
        uint8_t &genre,
        TunerTypes::TunerTypes::UInt32s &flags,
        uint32_t &handle
    );

    // no return here, just use by reference parameters
    void
    enterMakePermanentParameters(
        TunerStationTypes::TunerStationTypes::StationSelector &stationSelector,
        bool &permanent,
        const TunerStationTypes::TunerStationTypes::StationList& stationsAMFM,
        const TunerStationTypes::TunerStationTypes::StationList& stationsDAB,
        const TunerStationTypes::TunerStationTypes::StationList& stationsUndef,
        uint32_t &handle
    );

    // no return here, just use by reference parameters
    void
    enterControlUpdateParameters(
        TunerStationTypes::TunerStationTypes::UpdateElement &updateElement,
        TunerStationTypes::TunerStationTypes::UpdateType &updateType,
        uint32_t &sourceType,
        uint32_t &stationType,
        uint32_t &handle
    );

    int
    enterFromStationList(const TunerStationTypes::TunerStationTypes::StationList& stations);

    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType
    enterComponentType();

    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType
    enterAnnouncementType();

    uint32_t
    enterComponentID();

    uint32_t
    enterComponentIDFromList(vector<uint32_t>& list);

    bool
    enterComponentParameter();

    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions
    enterComponentTypeOptions();

    TunerTypes::TunerTypes::Activation
    enterActivation();

    // functions returning string from enumeration value

    string
    getStationType(TunerStationTypes::TunerStationTypes::StationType x);

    string
    getStationTypeShort(uint32_t x);

    string
    getSeekMode(TunerStationTypes::TunerStationTypes::SeekMode x);

    string
    getSeekReturnValue(TunerStationTypes::TunerStationTypes::SeekReturnValue x);

    string
    getSelectionMode(TunerStationTypes::TunerStationTypes::SelectionMode x);

    string
    getUpdateElement(TunerStationTypes::TunerStationTypes::UpdateElement x);

    string
    getSourceType(TunerStationTypes::TunerStationTypes::SourceType x);

    string
    getDeviceType(TunerStationTypes::TunerStationTypes::DeviceType x);

    string
    getFeedback(TunerTypes::TunerTypes::Feedback x);

    string
    getUpdateType(TunerStationTypes::TunerStationTypes::UpdateType x);

    string
    getFlagsDefUndef(TunerStationTypes::TunerStationTypes::FlagsDefUndef x);

    string
    getFlagsDefAmFm(TunerStationTypes::TunerStationTypes::FlagsDefAmFm x);

    string
    getFlagsDefDab(TunerStationTypes::TunerStationTypes::FlagsDefDab x);

    string
    getQualityIndexUndef(TunerStationTypes::TunerStationTypes::QualityIndexUndef x);

    string
    getQualityIndexAmFm(TunerStationTypes::TunerStationTypes::QualityIndexAmFm x);

    string
    getQualityIndexDab(TunerStationTypes::TunerStationTypes::QualityIndexDab x);

    string
    getNameIndexDab(TunerStationTypes::TunerStationTypes::NameIndexDab x);

    string
    getNameIndexAmFm(TunerStationTypes::TunerStationTypes::NameIndexAmFm x);

    string
    getNameIndexUndef(TunerStationTypes::TunerStationTypes::NameIndexUndef x);

    string
    getIdIndexUndef(TunerStationTypes::TunerStationTypes::IdIndexUndef x);

    string
    getIdIndexAmFm(TunerStationTypes::TunerStationTypes::IdIndexAmFm x);

    string
    getIdIndexDab(TunerStationTypes::TunerStationTypes::IdIndexDab x);

    string
    getPermanent(bool x);

    string
    getFrequency(bool x);

    string
    getGenre(uint8_t x);

    string
    getFlags(uint32_t x);

    string
    getCallStatus(CommonAPI::CallStatus x);

    string
    getAnnouncementType(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType);

    string
    getComponentType(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType);

    string
    getActivation(TunerTypes::TunerTypes::Activation);

    // setter turning string into value

    TunerStationTypes::TunerStationTypes::StationType
    setStationType(string x);

    TunerStationTypes::TunerStationTypes::SeekMode
    setSeekMode(string x);

    TunerStationTypes::TunerStationTypes::SelectionMode
    setSelectionMode(string x);

    TunerStationTypes::TunerStationTypes::UpdateElement
    setUpdateElement(string x);

    TunerStationTypes::TunerStationTypes::SourceType
    setSourceType(string x);

    TunerStationTypes::TunerStationTypes::DeviceType
    setDeviceType(string x);

    TunerTypes::TunerTypes::Feedback
    setFeedback(string x);

    TunerStationTypes::TunerStationTypes::UpdateType
    setUpdateType(string x);

    TunerStationTypes::TunerStationTypes::FlagsDefUndef
    setFlagsDefUndef(string x);

    TunerStationTypes::TunerStationTypes::FlagsDefAmFm
    setFlagsDefAmFm(string x);

    TunerStationTypes::TunerStationTypes::FlagsDefDab
    setFlagsDefDab(string x);

    TunerStationTypes::TunerStationTypes::QualityIndexUndef
    setQualityIndexUndef(string x);

    TunerStationTypes::TunerStationTypes::QualityIndexAmFm
    setQualityIndexAmFm(string x);

    TunerStationTypes::TunerStationTypes::QualityIndexDab
    setQualityIndexDab(string x);

    TunerStationTypes::TunerStationTypes::NameIndexDab
    setNameIndexDab(string x);

    TunerStationTypes::TunerStationTypes::NameIndexAmFm
    setNameIndexAmFm(string x);

    TunerStationTypes::TunerStationTypes::NameIndexUndef
    setNameIndexUndef(string x);

    TunerStationTypes::TunerStationTypes::IdIndexUndef
    setIdIndexUndef(string x);

    TunerStationTypes::TunerStationTypes::IdIndexAmFm
    setIdIndexAmFm(string x);

    TunerStationTypes::TunerStationTypes::IdIndexDab
    setIdIndexDab(string x);

    bool
    setPermanent(string x);

    bool
    setFrequency(string x);

    uint32_t
    setGenre(string x);

    uint32_t
    setFlags(string x);

    CommonAPI::CallStatus
    setCallStatus(string x);

    // debug print methods

    void printStation(const TunerStationTypes::TunerStationTypes::Station& myStation);
    void printStationSelector(const TunerStationTypes::TunerStationTypes::StationSelector& station);
    void printStationListShort(const TunerStationTypes::TunerStationTypes::StationList& stations);
    void printComponentTypeOptions(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions& componentTypeOptions);

private:
    static MyTerminalIO *instance;
    MyTerminalIO();
    MyTerminalIO(const MyTerminalIO&);
    ~MyTerminalIO();

    class Guard {
        public:
            ~Guard();
    };
    friend class Guard;
#define STATION_TYPE(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::StationType::A }
    map<string, uint32_t> nameToStationType = {
        STATION_TYPE(ST_UNDEF),
        STATION_TYPE(ST_RECEIVABLE),
        STATION_TYPE(ST_PERMANENT),
        STATION_TYPE(ST_AUTOSTORED),
        STATION_TYPE(ST_ENSEMBLE),
        STATION_TYPE(ST_SERVICE),
        STATION_TYPE(ST_PRIMARY),
        STATION_TYPE(ST_SECONDARY),
        STATION_TYPE(ST_CHANGED)
    };
    map<uint32_t, string> stationTypeToName;

#define SEEK_MODE(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::SeekMode::A }
    map<string, uint32_t> nameToSeekMode = {
        SEEK_MODE(SM_OFF),
        SEEK_MODE(SM_MAN_UP),
        SEEK_MODE(SM_MAN_DOWN),
        SEEK_MODE(SM_AUTO_UP),
        SEEK_MODE(SM_AUTO_DOWN),
        SEEK_MODE(SM_SCAN_UP),
        SEEK_MODE(SM_SCAN_DOWN),
        SEEK_MODE(SM_SCAN_SKIP_UP),
        SEEK_MODE(SM_SCAN_SKIP_DOWN),
        SEEK_MODE(SM_AUTOSTORE)
    };
    map<uint32_t, string> seekModeToName;

#define SELECTION_MODE(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::SelectionMode::A }
    map<string, uint32_t> nameToSelectionMode = {
        SELECTION_MODE(SM_UNDEF),
        SELECTION_MODE(SM_DIRECT),
        SELECTION_MODE(SM_LIST),
        SELECTION_MODE(SM_PRESET)
    };
    map<uint32_t, string> selectionModeToName;

#define UPDATE_ELEMENT(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::UpdateElement::A }
    map<string, uint32_t> nameToUpdateElement = {
        UPDATE_ELEMENT(UE_SEEK),
        UPDATE_ELEMENT(UE_CURRENT_STATION),
        UPDATE_ELEMENT(UE_STATION_LIST)
    };
    map<uint32_t, string> updateElementToName;

#define SOURCE_TYPE(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::SourceType::A }
    map<string, uint32_t> nameToSourceType = {
        SOURCE_TYPE(UNDEF_SOURCE),
        SOURCE_TYPE(AMFM_FM),
        SOURCE_TYPE(AMFM_MW),
        SOURCE_TYPE(AMFM_LW),
        SOURCE_TYPE(AMFM_SW),
        SOURCE_TYPE(AMFM_WB),
        SOURCE_TYPE(AMFM_TF),
        SOURCE_TYPE(AMFM_HD),
        SOURCE_TYPE(AMFM_DRM),
        SOURCE_TYPE(DAB_L),
        SOURCE_TYPE(DAB_III),
        SOURCE_TYPE(DAB_DAB),
        SOURCE_TYPE(DAB_DAB_PLUS),
        SOURCE_TYPE(DAB_DMBA),
        SOURCE_TYPE(DAB_DMBV),
        SOURCE_TYPE(SDARS_SIRIUS),
        SOURCE_TYPE(SDARS_XM)
    };
    map<uint32_t, string> sourceTypeToName;

#define DEVICE_TYPE(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::A }
    map<string, uint32_t> nameToDeviceType = {
        DEVICE_TYPE(UNDEF_DEVICE),
        DEVICE_TYPE(AMFM),
        DEVICE_TYPE(DAB),
        DEVICE_TYPE(SDARS),
        DEVICE_TYPE(TV)
    };
    map<uint32_t, string> deviceTypeToName;

#define FEEDBACK(A) { #A, (uint32_t)TunerTypes::TunerTypes::Feedback::A }
    map<string, uint32_t> nameToFeedback = {
        FEEDBACK(DONE),
        FEEDBACK(INTERRUPTED),
        FEEDBACK(NOT_APPLICABLE),
        FEEDBACK(ALREADY_SET),
        FEEDBACK(FAILURE),
        FEEDBACK(DELAYED)
    };
    map<uint32_t, string> feedbackToName;

#define UPDATE_TYPE(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::UpdateType::A }
    map<string, uint32_t> nameToUpdateType = {
        UPDATE_TYPE(UT_NONE),
        UPDATE_TYPE(UT_ONCE),
        UPDATE_TYPE(UT_NOTIFICATION)
    };
    map<uint32_t, string> updateTypeToName;

#define FLAGS_DEF_UNDEF(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::FlagsDefUndef::A }
    map<string, uint32_t> nameToFlagsDefUndef = {
        FLAGS_DEF_UNDEF(UNDEF_FLG_MUTED),
        FLAGS_DEF_UNDEF(UNDEF_FLG_ALARM),
        FLAGS_DEF_UNDEF(UNDEF_FLG_TRAFFIC),
        FLAGS_DEF_UNDEF(UNDEF_FLG_TRANSPORT),
        FLAGS_DEF_UNDEF(UNDEF_FLG_WARNING),
        FLAGS_DEF_UNDEF(UNDEF_FLG_NEWS),
        FLAGS_DEF_UNDEF(UNDEF_FLG_WEATHER),
        FLAGS_DEF_UNDEF(UNDEF_FLG_EVENT),
        FLAGS_DEF_UNDEF(UNDEF_FLG_SPECIAL_EVENT),
        FLAGS_DEF_UNDEF(UNDEF_FLG_PROGRAMM_INFO),
        FLAGS_DEF_UNDEF(UNDEF_FLG_SPORT),
        FLAGS_DEF_UNDEF(UNDEF_FLG_FINANCES),
        FLAGS_DEF_UNDEF(UNDEF_FLG_BWS),
        FLAGS_DEF_UNDEF(UNDEF_FLG_EPG),
        FLAGS_DEF_UNDEF(UNDEF_FLG_JLN),
        FLAGS_DEF_UNDEF(UNDEF_FLG_SLS_NPAD),
        FLAGS_DEF_UNDEF(UNDEF_FLG_SLS_XPAD),
        FLAGS_DEF_UNDEF(UNDEF_FLG_TMC),
        FLAGS_DEF_UNDEF(UNDEF_FLG_TPEG),
        FLAGS_DEF_UNDEF(UNDEF_FLG_MPEG2),
        FLAGS_DEF_UNDEF(UNDEF_FLG_AAC)
    };
    map<uint32_t, string> flagsDefUndefToName;

#define FLAGS_DEF_AM_FM(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::FlagsDefAmFm::A }
    map<string, uint32_t> nameToFlagsDefAmFm = {
        FLAGS_DEF_AM_FM(AMFM_FLG_TP),
        FLAGS_DEF_AM_FM(AMFM_FLG_TA),
        FLAGS_DEF_AM_FM(AMFM_FLG_TMC),
        FLAGS_DEF_AM_FM(AMFM_FLG_HDDIGAUDIO),
        FLAGS_DEF_AM_FM(AMFM_FLG_HDENCRYPTED),
        FLAGS_DEF_AM_FM(AMFM_FLG_HDSUBSCRIBED)
    };
    map<uint32_t, string> flagsDefAmFmToName;

#define FLAGS_DEF_DAB(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::FlagsDefDab::A }
    map<string, uint32_t> nameToFlagsDefDab = {
        FLAGS_DEF_DAB(DAB_FLG_LOCKED),
        FLAGS_DEF_DAB(DAB_FLG_VALID),
        FLAGS_DEF_DAB(DAB_FLG_MUTED),
        FLAGS_DEF_DAB(DAB_FLG_ENS_MUTED),
        FLAGS_DEF_DAB(DAB_FLG_ALARM),
        FLAGS_DEF_DAB(DAB_FLG_TRAFFIC),
        FLAGS_DEF_DAB(DAB_FLG_TRANSPORT),
        FLAGS_DEF_DAB(DAB_FLG_WARNING),
        FLAGS_DEF_DAB(DAB_FLG_NEWS),
        FLAGS_DEF_DAB(DAB_FLG_WEATHER),
        FLAGS_DEF_DAB(DAB_FLG_EVENT),
        FLAGS_DEF_DAB(DAB_FLG_SPECIAL_EVENT),
        FLAGS_DEF_DAB(DAB_FLG_PROGRAMM_INFO),
        FLAGS_DEF_DAB(DAB_FLG_SPORT),
        FLAGS_DEF_DAB(DAB_FLG_FINANCES),
        // FLAGS_DEF_DAB(DAB_FLG_BWS), unclear whether this entry should be around
        FLAGS_DEF_DAB(DAB_FLG_EPG),
        FLAGS_DEF_DAB(DAB_FLG_JLN),
        FLAGS_DEF_DAB(DAB_FLG_SLS_NPAD),
        FLAGS_DEF_DAB(DAB_FLG_SLS_XPAD),
        FLAGS_DEF_DAB(DAB_FLG_TMC),
        FLAGS_DEF_DAB(DAB_FLG_TPEG),
        FLAGS_DEF_DAB(DAB_FLG_MPEG2),
        FLAGS_DEF_DAB(DAB_FLG_AAC)
    };
    map<uint32_t, string> flagsDefDabToName;

#define QUALITY_INDEX_UNDEF(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexUndef::A }
    map<string, uint32_t> nameToQualityIndexUndef = {
        QUALITY_INDEX_UNDEF(UNDEF_QAL_AUDIO)
    };
    map<uint32_t, string> qualityIndexUndefToName;

#define QUALITY_INDEX_AMFM(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::A }
    map<string, uint32_t> nameToQualityIndexAmFm = {
        QUALITY_INDEX_AMFM(AMFM_QAL_FIELDSTRENGTH),
        QUALITY_INDEX_AMFM(AMFM_QAL_MULTIPATH),
        QUALITY_INDEX_AMFM(AMFM_QAL_DIGITAL)
    };
    map<uint32_t, string> qualityIndexAmFmToName;

#define QUALITY_INDEX_DAB(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::A }
    map<string, uint32_t> nameToQualityIndexDab = {
        QUALITY_INDEX_DAB(DAB_QAL_BER)
    };
    map<uint32_t, string> qualityIndexDabToName;

#define NAME_INDEX_DAB(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::A }
    map<string, uint32_t> nameToNameIndexDab = {
        NAME_INDEX_DAB(DAB_NAM_CLONG),
        NAME_INDEX_DAB(DAB_NAM_CSHORT),
        NAME_INDEX_DAB(DAB_NAM_DYNAMIC),
        NAME_INDEX_DAB(DAB_NAM_SLONG),
        NAME_INDEX_DAB(DAB_NAM_SSHORT),
        NAME_INDEX_DAB(DAB_NAM_ELONG),
        NAME_INDEX_DAB(DAB_NAM_ESHORT),
        NAME_INDEX_DAB(DAB_NAM_FREQUENCY)
    };
    map<uint32_t, string> nameIndexDabToName;

#define NAME_INDEX_AMFM(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::A }
    map<string, uint32_t> nameToNameIndexAmFm = {
        NAME_INDEX_AMFM(AMFM_NAM_PS),
        NAME_INDEX_AMFM(AMFM_NAM_HD),
        NAME_INDEX_AMFM(AMFM_NAM_RT)
    };
    map<uint32_t, string> nameIndexAmFmToName;

#define NAME_INDEX_UNDEF(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::NameIndexUndef::A }
    map<string, uint32_t> nameToNameIndexUndef = {
        NAME_INDEX_UNDEF(UNDEF_NAM_LONG),
        NAME_INDEX_UNDEF(UNDEF_NAM_SHORT),
        NAME_INDEX_UNDEF(UNDEF_NAM_DYNAMIC)
    };
    map<uint32_t, string> nameIndexUndefToName;

#define ID_INDEX_DAB(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::A }
    map<string, uint32_t> nameToIdIndexDab = {
        ID_INDEX_DAB(DAB_ID_KEY),
        ID_INDEX_DAB(DAB_ID_FREQUENCY),
        ID_INDEX_DAB(DAB_ID_ENSEMBLE),
        ID_INDEX_DAB(DAB_ID_SERVICE),
        ID_INDEX_DAB(DAB_ID_COMPONENT)
    };
    map<uint32_t, string> idIndexDabToName;

#define ID_INDEX_AMFM(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::A }
    map<string, uint32_t> nameToIdIndexAmFm = {
        ID_INDEX_AMFM(AMFM_ID_KEY),
        ID_INDEX_AMFM(AMFM_ID_FREQUENCY),
        ID_INDEX_AMFM(AMFM_ID_PI),
        ID_INDEX_AMFM(AMFM_ID_SERVICE)
    };
    map<uint32_t, string> idIndexAmFmToName;

#define ID_INDEX_UNDEF(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::A }
    map<string, uint32_t> nameToIdIndexUndef = {
        ID_INDEX_UNDEF(UNDEF_ID_KEY),
        ID_INDEX_UNDEF(UNDEF_ID_PARENT)
    };
    map<uint32_t, string> idIndexUndefToName;

#define CALL_STATUS(A) { #A, (uint32_t)CommonAPI::CallStatus::A }
    map<string, uint32_t> nameToCallStatus = {
        CALL_STATUS(SUCCESS),
        CALL_STATUS(OUT_OF_MEMORY),
        CALL_STATUS(NOT_AVAILABLE),
        CALL_STATUS(CONNECTION_FAILED),
        CALL_STATUS(REMOTE_ERROR)
    };
    map<uint32_t, string> callStatusToName;

#define SEEK_RETURN_VALUE(A) { #A, (uint32_t)TunerStationTypes::TunerStationTypes::SeekReturnValue::A }
    map<string, uint32_t> nameToSeekReturnValue = {
        SEEK_RETURN_VALUE(SM_FREQUENCY),
        SEEK_RETURN_VALUE(SM_PERCENTAGE)
    };
    map<uint32_t, string> seekReturnValueToName;

#define ANNOUNCEMENT_TYPE(A) { #A, (uint32_t)TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType::A }
    map<string, uint32_t> nameToAnnouncementType = {
        ANNOUNCEMENT_TYPE(AT_Alarm),
        ANNOUNCEMENT_TYPE(AT_RoadTraffic),
        ANNOUNCEMENT_TYPE(AT_TransportFlash),
        ANNOUNCEMENT_TYPE(AT_WarningService),
        ANNOUNCEMENT_TYPE(AT_News),
        ANNOUNCEMENT_TYPE(AT_AreaWeather),
        ANNOUNCEMENT_TYPE(AT_Event),
        ANNOUNCEMENT_TYPE(AT_SpecialEvent),
        ANNOUNCEMENT_TYPE(AT_ProgramInformation),
        ANNOUNCEMENT_TYPE(AT_SportReport),
        ANNOUNCEMENT_TYPE(AT_FinancialReport)
    };
    map<uint32_t, string> AnnouncementTypeToName;

#define COMPONENT_TYPE(A) { #A, (uint32_t)TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType::A }
    map<string, uint32_t> nameToComponentType = {
        COMPONENT_TYPE(CT_NO_COMPONENT_TYPE),
        COMPONENT_TYPE(CT_EPG),
        COMPONENT_TYPE(CT_TELETEXT),
        COMPONENT_TYPE(CT_TMC),
        COMPONENT_TYPE(CT_BWS),
        COMPONENT_TYPE(CT_SUBTITLE),
        COMPONENT_TYPE(CT_SLIDESHOW),
        COMPONENT_TYPE(CT_JOURNALINE),
        COMPONENT_TYPE(CT_TPEG),
        COMPONENT_TYPE(CT_ANNOUNCEMENT)
    };
    map<uint32_t, string> ComponentTypeToName;

#define ACTIVATION(A) { #A, (uint32_t)TunerTypes::TunerTypes::Activation::A }
    map<string, uint32_t> nameToActivation = {
        ACTIVATION(ACTIVE),
        ACTIVATION(INACTIVE)
    };
    map<uint32_t, string> ActivationToName;

};
#endif /* MY_TERMINALIO_H */
