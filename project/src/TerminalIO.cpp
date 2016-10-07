///////////////////////////////////////////////////////////
//  TerminalIO.cpp
//  Implementation of the Class TerminalIO
//  Created on:      16-Jul-2013 16:47:53
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/TerminalIO.h"

using namespace std;

TerminalIO::TerminalIO()
{
    // populate maps for reverse lookup
    for (auto it = nameToStationType.cbegin(); it != nameToStationType.cend(); ++it) {
        stationTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToSeekMode.cbegin(); it != nameToSeekMode.cend(); ++it) {
        seekModeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToSelectionMode.cbegin(); it != nameToSelectionMode.cend(); ++it) {
        selectionModeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToUpdateElement.cbegin(); it != nameToUpdateElement.cend(); ++it) {
        updateElementToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToSourceType.cbegin(); it != nameToSourceType.cend(); ++it) {
        sourceTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToDeviceType.cbegin(); it != nameToDeviceType.cend(); ++it) {
        deviceTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToFeedback.cbegin(); it != nameToFeedback.cend(); ++it) {
        feedbackToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToUpdateType.cbegin(); it != nameToUpdateType.cend(); ++it) {
        updateTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToFlagsDefUndef.cbegin(); it != nameToFlagsDefUndef.cend(); ++it) {
        flagsDefUndefToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToFlagsDefAmFm.cbegin(); it != nameToFlagsDefAmFm.cend(); ++it) {
        flagsDefAmFmToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToFlagsDefDab.cbegin(); it != nameToFlagsDefDab.cend(); ++it) {
        flagsDefDabToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToQualityIndexUndef.cbegin(); it != nameToQualityIndexUndef.cend(); ++it) {
        qualityIndexUndefToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToQualityIndexAmFm.cbegin(); it != nameToQualityIndexAmFm.cend(); ++it) {
        qualityIndexAmFmToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToQualityIndexDab.cbegin(); it != nameToQualityIndexDab.cend(); ++it) {
        qualityIndexDabToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToNameIndexDab.cbegin(); it != nameToNameIndexDab.cend(); ++it) {
        nameIndexDabToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToNameIndexAmFm.cbegin(); it != nameToNameIndexAmFm.cend(); ++it) {
        nameIndexAmFmToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToNameIndexUndef.cbegin(); it != nameToNameIndexUndef.cend(); ++it) {
        nameIndexUndefToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToIdIndexDab.cbegin(); it != nameToIdIndexDab.cend(); ++it) {
        idIndexDabToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToIdIndexAmFm.cbegin(); it != nameToIdIndexAmFm.cend(); ++it) {
        idIndexAmFmToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToIdIndexUndef.cbegin(); it != nameToIdIndexUndef.cend(); ++it) {
        idIndexUndefToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToCallStatus.cbegin(); it != nameToCallStatus.cend(); ++it) {
        callStatusToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToSeekReturnValue.cbegin(); it != nameToSeekReturnValue.cend(); ++it) {
        seekReturnValueToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToAnnouncementType.cbegin(); it != nameToAnnouncementType.cend(); ++it) {
        AnnouncementTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToComponentType.cbegin(); it != nameToComponentType.cend(); ++it) {
        ComponentTypeToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToActivation.cbegin(); it != nameToActivation.cend(); ++it) {
        ActivationToName[(*it).second] = (*it).first;
    }
    for (auto it = nameToAMModi.cbegin(); it != nameToAMModi.cend(); ++it) {
    	AMModiToName[(*it).second] = (*it).first;
	}
    for (auto it = nameToFollowingModi.cbegin(); it != nameToFollowingModi.cend(); ++it) {
    	FollowingModiToName[(*it).second] = (*it).first;
	}
    for (auto it = nameToCountryVariants.cbegin(); it != nameToCountryVariants.cend(); ++it) {
    	CountryVariantsToName[(*it).second] = (*it).first;
	}
    for (auto it = nameToFunctionalityType.cbegin(); it != nameToFunctionalityType.cend(); ++it) {
    	FunctionalityTypeToName[(*it).second] = (*it).first;
	}
    for (auto it = nameToDataFormat.cbegin(); it != nameToDataFormat.cend(); ++it) {
    	DataFormatToName[(*it).second] = (*it).first;
	}
    for (auto it = nameToDataType.cbegin(); it != nameToDataType.cend(); ++it) {
    	DataTypeToName[(*it).second] = (*it).first;
	}
    for (auto it = nameToAnnouncementState.cbegin(); it != nameToAnnouncementState.cend(); ++it) {
    	AnnouncementStateToName[(*it).second] = (*it).first;
	}
}

TerminalIO *TerminalIO::_instance = NULL;

TerminalIO::~TerminalIO()
{
}

TerminalIO *TerminalIO::getInstance()
{
    if (_instance == NULL) {
        _instance = new TerminalIO();
    }
    return _instance;
}

void TerminalIO::Log( string log, int level ){
	if ( level == ERROR ) {
		cerr << log << endl;
	}
	else {
		cout << log << endl;
	}
}

unsigned int TerminalIO::readNumber(unsigned int minval, unsigned int maxval, string question, string menu)
{
    int base;
    char *endptr, *str;
    unsigned long val;
    char buf[24];

    while(1) {
        if (menu != "") {
            printf("%s", menu.c_str());
        }
        printf("\n%s [%u-%u]: ", question.c_str(), minval, maxval);
        fflush(stdout);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            continue;
        }
        buf[strlen(buf)-1] = '\0';
        if (buf[0] == '\0') {
            continue;
        }
        base = 0;
        errno = 0;    /* To distinguish success/failure after call */
        val = strtoul(buf, &endptr, base);
        if ((errno == ERANGE && (val == ULONG_MAX || val == 0))
            || (errno != 0 && val == 0)) {
            Log( "Invalid value. Please try again!", ERROR );
            continue;
        }
        if (endptr == str) {
        	Log( "Invalid value. Please try again!", ERROR );
            continue;
        }
        if (*endptr != '\0') {
        	Log( "Invalid value. Please try again!", ERROR );
            continue;
        }
        if (val >= minval && val <= maxval) {
            return(val);
        }
        Log("Value out of range [" + to_string(minval) + "-" + to_string(maxval) + "]. Please try again!", ERROR);
    }
    // NOTREACHED
}

bool TerminalIO::readBoolean(string question)
{
    uint32_t result;
    Log("0 FALSE", INFO);
    Log("1 TRUE", INFO);
    result = readNumber(0, 1, question);
    printf("Selected value: %s\n", result ? "TRUE" : "FALSE");
    return result ? true : false;
}

IVIRadio::Station::StationTypes::StationType TerminalIO::enterStationType()
{
    vector<IVIRadio::Station::StationTypes::StationType> x;
    uint32_t current = (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF;
    int result;
    int i;
    cout << endl;
    do {
        x.clear();
        i = 0;
        for (auto it = nameToStationType.cbegin(); it != nameToStationType.cend(); ++it, i++) {
            x.push_back((IVIRadio::Station::StationTypes::StationType)(*it).second);
            printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
        }
        cout << endl;
        cout << "Already selected: " << getStationType((IVIRadio::Station::StationTypes::StationType)current).c_str() << endl;
        cout << "Select ST_UNDEF from menu to end selection." << endl;
        result = readNumber(0, x.size()-1, "Enter StationType");
        cout << "Selected value: "<< result << ", meaning " << stationTypeToName[(uint32_t)x[result]].c_str() << endl;
        current |= (uint32_t)x[result];
    } while(x[result] != IVIRadio::Station::StationTypes::StationType::ST_UNDEF);

    return (IVIRadio::Station::StationTypes::StationType)current;
}

IVIRadio::Station::StationTypes::SeekMode TerminalIO::enterSeekMode()
{
    vector<IVIRadio::Station::StationTypes::SeekMode> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToSeekMode.cbegin(); it != nameToSeekMode.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::SeekMode)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter SeekMode");
    printf("Selected value: %d, meaning %s\n", result,
        seekModeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::SelectionMode TerminalIO::enterSelectionMode()
{
    vector<IVIRadio::Station::StationTypes::SelectionMode> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToSelectionMode.cbegin(); it != nameToSelectionMode.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::SelectionMode)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter SelectionMode");
    printf("Selected value: %d, meaning %s\n", result,
        selectionModeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


IVIRadio::Station::StationTypes::UpdateElement TerminalIO::enterUpdateElement()
{
    vector<IVIRadio::Station::StationTypes::UpdateElement> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToUpdateElement.cbegin(); it != nameToUpdateElement.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::UpdateElement)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter UpdateElement");
    printf("Selected value: %d, meaning %s\n", result,
        updateElementToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


IVIRadio::Types::Types::SourceType TerminalIO::enterSourceType()
{
    vector<IVIRadio::Types::Types::SourceType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToSourceType.cbegin(); it != nameToSourceType.cend(); ++it, i++) {
        x.push_back((IVIRadio::Types::Types::SourceType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter SourceType");
    printf("Selected value: %d, meaning %s\n", result,
        sourceTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


IVIRadio::Types::Types::DeviceType TerminalIO::enterDeviceType()
{
    vector<IVIRadio::Types::Types::DeviceType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToDeviceType.cbegin(); it != nameToDeviceType.cend(); ++it, i++) {
        x.push_back((IVIRadio::Types::Types::DeviceType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter DeviceType");
    printf("Selected value: %d, meaning %s\n", result,
        deviceTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


IVIRadio::Types::Types::Feedback TerminalIO::enterFeedback()
{
    vector<IVIRadio::Types::Types::Feedback> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFeedback.cbegin(); it != nameToFeedback.cend(); ++it, i++) {
        x.push_back((IVIRadio::Types::Types::Feedback)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter Feedback");
    printf("Selected value: %d, meaning %s\n", result,
        feedbackToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Types::Types::UpdateType TerminalIO::enterUpdateType()
{
    vector<IVIRadio::Types::Types::UpdateType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToUpdateType.cbegin(); it != nameToUpdateType.cend(); ++it, i++) {
        x.push_back((IVIRadio::Types::Types::UpdateType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter UpdateType");
    printf("Selected value: %d, meaning %s\n", result,
        updateTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


IVIRadio::Station::StationTypes::FlagsDefUndef TerminalIO::enterFlagsDefUndef()
{
    vector<IVIRadio::Station::StationTypes::FlagsDefUndef> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFlagsDefUndef.cbegin(); it != nameToFlagsDefUndef.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::FlagsDefUndef)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter FlagsDefUndef");
    printf("Selected value: %d, meaning %s\n", result,
        flagsDefUndefToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::FlagsDefAmFm TerminalIO::enterFlagsDefAmFm()
{
    vector<IVIRadio::Station::StationTypes::FlagsDefAmFm> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFlagsDefAmFm.cbegin(); it != nameToFlagsDefAmFm.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::FlagsDefAmFm)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter FlagsDefAmFm");
    printf("Selected value: %d, meaning %s\n", result,
        flagsDefAmFmToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::FlagsDefDab TerminalIO::enterFlagsDefDab()
{
    vector<IVIRadio::Station::StationTypes::FlagsDefDab> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFlagsDefDab.cbegin(); it != nameToFlagsDefDab.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::FlagsDefDab)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter FlagsDefDab");
    printf("Selected value: %d, meaning %s\n", result,
        flagsDefDabToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


IVIRadio::Station::StationTypes::QualityIndexUndef TerminalIO::enterQualityIndexUndef()
{
    vector<IVIRadio::Station::StationTypes::QualityIndexUndef> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToQualityIndexUndef.cbegin(); it != nameToQualityIndexUndef.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::QualityIndexUndef)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter QualityIndexUndef");
    printf("Selected value: %d, meaning %s\n", result,
        qualityIndexUndefToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::QualityIndexAmFm TerminalIO::enterQualityIndexAmFm()
{
    vector<IVIRadio::Station::StationTypes::QualityIndexAmFm> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToQualityIndexAmFm.cbegin(); it != nameToQualityIndexAmFm.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::QualityIndexAmFm)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter QualityIndexAmFm");
    printf("Selected value: %d, meaning %s\n", result,
        qualityIndexAmFmToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::QualityIndexDab TerminalIO::enterQualityIndexDab()
{
    vector<IVIRadio::Station::StationTypes::QualityIndexDab> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToQualityIndexDab.cbegin(); it != nameToQualityIndexDab.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::QualityIndexDab)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter QualityIndexDab");
    printf("Selected value: %d, meaning %s\n", result,
        qualityIndexDabToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}


IVIRadio::Station::StationTypes::NameIndexDab TerminalIO::enterNameIndexDab()
{
    vector<IVIRadio::Station::StationTypes::NameIndexDab> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToNameIndexDab.cbegin(); it != nameToNameIndexDab.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::NameIndexDab)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter NameIndexDab");
    printf("Selected value: %d, meaning %s\n", result,
        nameIndexDabToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::NameIndexAmFm TerminalIO::enterNameIndexAmFm()
{
    vector<IVIRadio::Station::StationTypes::NameIndexAmFm> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToNameIndexAmFm.cbegin(); it != nameToNameIndexAmFm.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::NameIndexAmFm)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter NameIndexAmFm");
    printf("Selected value: %d, meaning %s\n", result,
        nameIndexAmFmToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::NameIndexUndef TerminalIO::enterNameIndexUndef()
{
    vector<IVIRadio::Station::StationTypes::NameIndexUndef> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToNameIndexUndef.cbegin(); it != nameToNameIndexUndef.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::NameIndexUndef)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter NameIndexUndef");
    printf("Selected value: %d, meaning %s\n", result,
        nameIndexUndefToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::IdIndexDab TerminalIO::enterIdIndexDab()
{
    vector<IVIRadio::Station::StationTypes::IdIndexDab> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToIdIndexDab.cbegin(); it != nameToIdIndexDab.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::IdIndexDab)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter IdIndexDab");
    printf("Selected value: %d, meaning %s\n", result,
        idIndexDabToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::IdIndexAmFm TerminalIO::enterIdIndexAmFm()
{
    vector<IVIRadio::Station::StationTypes::IdIndexAmFm> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToIdIndexAmFm.cbegin(); it != nameToIdIndexAmFm.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::IdIndexAmFm)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter IdIndexAmFm");
    printf("Selected value: %d, meaning %s\n", result,
        idIndexAmFmToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Station::StationTypes::IdIndexUndef TerminalIO::enterIdIndexUndef()
{
    vector<IVIRadio::Station::StationTypes::IdIndexUndef> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToIdIndexUndef.cbegin(); it != nameToIdIndexUndef.cend(); ++it, i++) {
        x.push_back((IVIRadio::Station::StationTypes::IdIndexUndef)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter IdIndexUndef");
    printf("Selected value: %d, meaning %s\n", result,
        idIndexUndefToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType		TerminalIO::enterFunctionalityType		(){
    vector<IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToFunctionalityType.cbegin(); it != nameToFunctionalityType.cend(); ++it, i++) {
        x.push_back( ( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType )( *it ).second );
        printf("%2d %-30s [%10d/0x%08x]\n", i, ( *it ).first.c_str(), ( *it ).second, ( *it ).second );
    }
    result = readNumber(0, x.size()-1, "Enter FunctionalityType");
    printf("Selected value: %d, meaning %s\n", result, FunctionalityTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::Configuration::ConfigurationTypesEnum::AMMode				TerminalIO::enterAMModi					(){
	vector<IVIRadio::Configuration::ConfigurationTypesEnum::AMMode> x;
	int result;
	int i = 0;
	printf("\n");
	for (auto it = nameToAMModi.cbegin(); it != nameToAMModi.cend(); ++it, i++) {
		x.push_back( ( IVIRadio::Configuration::ConfigurationTypesEnum::AMMode )( *it ).second );
		printf("%2d %-30s [%10d/0x%08x]\n", i, ( *it ).first.c_str(), ( *it ).second, ( *it ).second );
	}
	result = readNumber(0, x.size()-1, "Enter AMModiToName");
	printf("Selected value: %d, meaning %s\n", result, AMModiToName[(uint32_t)x[result]].c_str());
	return(x[result]);
}

IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType			TerminalIO::enterFollowingType		(){
	vector<IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType> x;
	int result;
	int i = 0;
	printf("\n");
	for (auto it = nameToFollowingModi.cbegin(); it != nameToFollowingModi.cend(); ++it, i++) {
		x.push_back( ( IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType )( *it ).second );
		printf("%2d %-30s [%10d/0x%08x]\n", i, ( *it ).first.c_str(), ( *it ).second, ( *it ).second );
	}
	result = readNumber(0, x.size()-1, "Enter FollowingType");
	printf("Selected value: %d, meaning %s\n", result, FollowingModiToName[(uint32_t)x[result]].c_str());
	return(x[result]);
}

IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant		TerminalIO::enterCountryVariants	(){
	vector<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant> x;
	int result;
	int i = 0;
	printf("\n");
	for (auto it = nameToCountryVariants.cbegin(); it != nameToCountryVariants.cend(); ++it, i++) {
		x.push_back( ( IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant )( *it ).second );
		printf("%2d %-30s [%10d/0x%08x]\n", i, ( *it ).first.c_str(), ( *it ).second, ( *it ).second );
	}
	result = readNumber(0, x.size()-1, "Enter CountryVariants");
	printf("Selected value: %d, meaning %s\n", result, CountryVariantsToName[(uint32_t)x[result]].c_str());
	return(x[result]);
}

IVIRadio::Configuration::ConfigurationOptions::HDOptions TerminalIO::enterHDOptions(){
	IVIRadio::Configuration::ConfigurationOptions::HDOptions hdOptions;
	hdOptions.activation = enterActivation();
	return hdOptions;
}

IVIRadio::Configuration::ConfigurationOptionsGetter::HDOptionsGet TerminalIO::enterHDOptionsGet(){
	IVIRadio::Configuration::ConfigurationOptionsGetter::HDOptionsGet hdOptions;
	hdOptions.deviceType = enterDeviceType();
	return hdOptions;
}

IVIRadio::Configuration::ConfigurationOptions::FollowingOptions TerminalIO::enterFollowingOptions()
{
	IVIRadio::Configuration::ConfigurationOptions::FollowingOptions followingOptions;
	int cnt = readNumber(0, 10, "How many Followings Types to be configured?");
	for (int i = 0; i < cnt; i++) {
		followingOptions.followingStates.push_back(enterFollowingType());
		followingOptions.activations.push_back(enterActivation());
	}
	return followingOptions;
}

IVIRadio::Configuration::ConfigurationOptionsGetter::FollowingOptionsGet TerminalIO::enterFollowingOptionsGet()
{
	IVIRadio::Configuration::ConfigurationOptionsGetter::FollowingOptionsGet followingOptions;
	int cnt = readNumber(0, 10, "How many following types are requested?");
	for (int i = 0; i < cnt; i++) {
		followingOptions.followingTypes.push_back(enterFollowingType());
	}
	return followingOptions;
}

IVIRadio::Configuration::ConfigurationOptions::SmartFavoriteOptions 		TerminalIO::enterSmartFavoriteOptions()
{
	IVIRadio::Configuration::ConfigurationOptions::SmartFavoriteOptions smartFavoriteOptions;
	smartFavoriteOptions.activity		= enterActivation();
	return smartFavoriteOptions;
}

IVIRadio::Configuration::ConfigurationOptionsGetter::SmartFavoriteOptionsGet 		TerminalIO::enterSmartFavoriteOptionsGet()
{
	IVIRadio::Configuration::ConfigurationOptionsGetter::SmartFavoriteOptionsGet smartFavoriteOptions;
	smartFavoriteOptions.deviceType		= enterDeviceType();
	return smartFavoriteOptions;
}

IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions TerminalIO::enterAvailableBandOptions 	()
{
	IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions availableBand;
	int acnt = readNumber(0, 10, "How many device types need to be configured?");
	for ( int j = 0; j < acnt; j++) {
		availableBand.deviceTypes.push_back( enterDeviceType() );
		//int cnt = readNumber(0, 10, "How many bands are available?");
		//for (int i = 0; i < cnt; i++) {
		availableBand.availableBands.push_back( enterSourceType() );
		//}
	}
	return availableBand;
}

IVIRadio::Configuration::ConfigurationOptionsGetter::AvailableBandoptionsGet TerminalIO::enterAvailableBandOptionsGet()
{
	IVIRadio::Configuration::ConfigurationOptionsGetter::AvailableBandoptionsGet availableBand;
	int acnt = readNumber(0, 10, "For how many device types is the available band configuration required?");
	for ( int j = 0; j < acnt; j++) {
		availableBand.deviceTypes.push_back( enterDeviceType() );
	}
	return availableBand;
}

IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions TerminalIO::enterCountryVariantOptions	()
{
	IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions countryVariant_Options;
	int cnt = readNumber(0, 10, "How many device types are to be configured?");
	for (int i = 0; i < cnt; i++) {
		countryVariant_Options.deviceTypes.push_back( enterDeviceType() );
		countryVariant_Options.countryVariants.push_back( enterCountryVariants() );
	}
	return countryVariant_Options;
}

IVIRadio::Configuration::ConfigurationOptionsGetter::CountryVariantsOptionsGet TerminalIO::enterCountryVariantOptionsGet()
{
	IVIRadio::Configuration::ConfigurationOptionsGetter::CountryVariantsOptionsGet countryVariant_Options;
	int cnt = readNumber(0, 10, "For how many device types is the country variant configuration required?");
	for (int i = 0; i < cnt; i++) {
		countryVariant_Options.deviceTypes.push_back( enterDeviceType() );
	}
	return countryVariant_Options;
}

IVIRadio::Configuration::ConfigurationOptions::CoverageAreaOptions TerminalIO::enterCoverageAreaOptions		()
{
	IVIRadio::Configuration::ConfigurationOptions::CoverageAreaOptions coverageAreaOptions;
	int cnt = readNumber(0, 10, "How many device types are to be configured?");
	for (int i = 0; i < cnt; i++) {
		coverageAreaOptions.deviceTypes.push_back( enterDeviceType() );
		coverageAreaOptions.countryVariants.push_back( enterCountryVariants() );
	}
	return coverageAreaOptions;
}

IVIRadio::Configuration::ConfigurationOptionsGetter::CoverageAreaOptionsGet TerminalIO::enterCoverageAreaOptionsGet()
{
	IVIRadio::Configuration::ConfigurationOptionsGetter::CoverageAreaOptionsGet coverageAreaOptions;
	int cnt = readNumber(0, 10, "For how many device types is the coverage area configuration required?");
	for (int i = 0; i < cnt; i++) {
		coverageAreaOptions.deviceTypes.push_back( enterDeviceType() );
	}
	return coverageAreaOptions;
}

IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions		TerminalIO::enterInterfaceVersionOptions(){
	IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions interfaceVersionOptions;
	interfaceVersionOptions.minorVersion 		= readNumber(0,10, "minor Interface Version");
	interfaceVersionOptions.majorVersion 		= readNumber(0,10, "major Interface Version");
	return interfaceVersionOptions;
}

IVIRadio::Configuration::ConfigurationOptions::AMModiOptions TerminalIO::enterAMModiOptions(){
	IVIRadio::Configuration::ConfigurationOptions::AMModiOptions amModiOptions;
	amModiOptions.amMode 		= enterAMModi();
	return amModiOptions;
}

IVIRadio::Configuration::ConfigurationOptionsGetter::AMModiOptionsGet TerminalIO::enterAMModiIOptionsGet(){
	IVIRadio::Configuration::ConfigurationOptionsGetter::AMModiOptionsGet amModiOptions;
	amModiOptions.deviceType = enterDeviceType();
	return amModiOptions;
}

IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes TerminalIO::enterFunctionalityTypes   (){
	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes x;
	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType result;
	int i;
	x.clear();
	cout << endl;
	do {
		i = 0;
		cout << endl;
		cout << "Enter 0 to end selection." << endl;
		result = enterFunctionalityType();
		x.push_back( result );
		cout << "Added " << FunctionalityTypeToName.at((uint32_t)result)  << "  " << (uint32_t)result <<  " to vector..."<< endl;
	} while( result != IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AMModi );

	return x;
}

IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions	TerminalIO::enterFunctionalityOptions(
		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes )
{
	IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions x;
	IVIRadio::Configuration::ConfigurationOptions::FunctionalityOption result;
	int i;
	x.clear();
	cout << endl;
	while ( readNumber(0,1,"Enter 1 to continue typeing configuration for functionality Type; enter 0 to exit") == 1 ){
	//for (auto it = functionalityTypes.cbegin(); it != functionalityTypes.cend(); it++ ){
		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType tempFT = enterFunctionalityType();
		functionalityTypes.push_back( tempFT );
		cout << "Enter Options for " << FunctionalityTypeToName.at((uint32_t)tempFT) << endl;
		if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::HD 						){
			result = enterHDOptions();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::Following 	){
			result = enterFollowingOptions();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::SmartFavorite 		){
			result = enterSmartFavoriteOptions();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AvailableBand 		){
			result = enterAvailableBandOptions();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CountryVariant 		){
			result = enterCountryVariantOptions();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CoverageArea 	){
			result = enterCoverageAreaOptions();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::InterfaceVersion 	){
			result = enterInterfaceVersionOptions();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AMModi 				){
			result = enterAMModiOptions();
		}
		x.push_back( result );
	}
	//cout << "Added " << FunctionalityTypeToName.at((uint32_t)result)  << " to vector..."<< endl;
	return x;
}

IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet	TerminalIO::enterFunctionalityOptionsGet (
		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes )
{
	IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet x;
	IVIRadio::Configuration::ConfigurationOptionsGetter::FunctionalityOptionGet result;

	int i;
	x.clear();
	cout << endl;
	while ( readNumber(0,1,"Enter 1 to continue typeing configuration for functionality Type; enter 0 to exit") == 1 ){

		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType tempFT = enterFunctionalityType();
		functionalityTypes.push_back( tempFT );
		cout << "Enter Options for " << FunctionalityTypeToName.at((uint32_t)(tempFT)) << endl;
		if 		( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::HD 				){
			result = enterHDOptionsGet();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::Following 			){
			result = enterFollowingOptionsGet();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::SmartFavorite 		){
			result = enterSmartFavoriteOptionsGet();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AvailableBand 		){
			result = enterAvailableBandOptionsGet();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CountryVariant 	){
			result = enterCountryVariantOptionsGet();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CoverageArea 		){
			result = enterCoverageAreaOptionsGet();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::InterfaceVersion 	){
			//result = enterInterfaceVersionOptions();
		}
		else if ( tempFT == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AMModi 			){
			result = enterAMModiIOptionsGet();
		}
		x.push_back( result );
	}
	return x;
}


IVIRadio::Types::Types::Activation TerminalIO::enterActivation()
{
    vector<IVIRadio::Types::Types::Activation> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToActivation.cbegin(); it != nameToActivation.cend(); ++it, i++) {
        x.push_back((IVIRadio::Types::Types::Activation)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter Activation");
    printf("Selected value: %d, meaning %s\n", result,
        ActivationToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

uint32_t TerminalIO::enterHandle()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter handle");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterFrequencyFM()
{
    uint32_t result;
    result = readNumber(87500, 108000, "Enter AM/FM frequency (khz)");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterPi()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter PI");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterFrequencyDAB()
{
    uint32_t result;
    result = readNumber(172000, 230000, "Enter DAB frequency (khz)");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterUniqueKey()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Unique Key");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterParent()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Parent");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterService()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Service");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterEnsemble()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Ensemble");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterComponent()
{
    uint32_t result;
    result = readNumber(0, UINT_MAX, "Enter Component");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint8_t TerminalIO::enterGenre()
{
    uint8_t result;
    result = (uint8_t)readNumber(0, 255, "Enter Genre");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

IVIRadio::Types::Types::UInt32s TerminalIO::enterFlags()
{
    IVIRadio::Types::Types::UInt32s result;
    result.clear();
    result.resize(1);
    result[0] = readNumber(0, UINT_MAX, "Enter Flag 0");
    return result;
}

bool TerminalIO::enterPermanent()
{
    return readBoolean("Enter Permanent");
}

IVIRadio::Types::Types::StationSelector TerminalIO::enterStationSelector(
    IVIRadio::Station::StationTypes::SelectionMode selectionMode,
    const IVIRadio::Station::StationTypes::StationList& stationsAMFM,
    const IVIRadio::Station::StationTypes::StationList& stationsDAB,
    const IVIRadio::Station::StationTypes::StationList& stationsUndef
)
{
    IVIRadio::Types::Types::StationSelector x;
    IVIRadio::Types::Types::DeviceType deviceType;

    deviceType = enterDeviceType();
    x.deviceType = (uint32_t)deviceType;
    switch(deviceType) {
        case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            // sanity cleanup
            x.id.resize(2, 0);
            if (selectionMode == IVIRadio::Station::StationTypes::SelectionMode::SM_DIRECT) {
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_PARENT] = enterParent();
            } else if (selectionMode == IVIRadio::Station::StationTypes::SelectionMode::SM_LIST) {
                if (stationsUndef.stations.size() == 0) {
                    throw invalid_argument("Undef station list is empty.");
                }
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] = enterFromStationList(stationsUndef);
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_PARENT] = enterParent();
            } else {
                // anything else is unsupported
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_PARENT] = enterParent();
            }
            break;
        case IVIRadio::Types::Types::DeviceType::AMFM:
            // sanity cleanup
            x.id.resize(4, 0);
            if (selectionMode == IVIRadio::Station::StationTypes::SelectionMode::SM_DIRECT) {
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = enterFrequencyFM();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = 0;
            } else if (selectionMode == IVIRadio::Station::StationTypes::SelectionMode::SM_LIST) {
                if (stationsAMFM.stations.size() == 0) {
                    throw invalid_argument("AMFM station list is empty.");
                }
                //x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] = enterFromStationList(stationsAMFM);
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = 0;
            } else {
                // unknown
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = enterFrequencyFM();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI] = enterPi();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = enterService();
            }
            break;
        case IVIRadio::Types::Types::DeviceType::DAB:
            // sanity cleanup
            x.id.resize(5, 0);
            if (selectionMode == IVIRadio::Station::StationTypes::SelectionMode::SM_DIRECT) {
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] = enterFrequencyDAB();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT] = 0;
            } else if (selectionMode == IVIRadio::Station::StationTypes::SelectionMode::SM_LIST) {
                if (stationsDAB.stations.size() == 0) {
                    throw invalid_argument("DAB station list is empty.");
                }
                //x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] = enterUniqueKey();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] = enterFromStationList(stationsDAB);
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE] = 0;
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT] = 0;
            } else {
                // unknown
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] 		= enterUniqueKey();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] 	= enterFrequencyDAB();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE] 	= enterEnsemble();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE] 	= enterService();
                x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT] 	= enterComponent();
            }
            break;
        case IVIRadio::Types::Types::DeviceType::SDARS:
            break;
        //case IVIRadio::Types::Types::DeviceType::TV:
          //  break;
        default:
            // error
            fprintf(stderr, "Illegal device Type %d", (uint32_t)x.deviceType);
            exit(1);
    }

    return x;
}

IVIRadio::Types::Types::StationSelector TerminalIO::enterStationSelector()
{
    IVIRadio::Types::Types::StationSelector x;
    IVIRadio::Types::Types::DeviceType deviceType;

    deviceType = enterDeviceType();
    x.deviceType = (uint32_t)deviceType;
    switch(deviceType) {
        case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            // sanity cleanup
            x.id.resize(2, 0);
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY] = enterUniqueKey();
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_PARENT] = enterParent();
            break;
        case IVIRadio::Types::Types::DeviceType::AMFM:
            // sanity cleanup
            x.id.resize(4, 0);
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] = enterUniqueKey();
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = enterFrequencyFM();
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI] = enterPi();
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = enterService();
            break;
        case IVIRadio::Types::Types::DeviceType::DAB:
            // sanity cleanup
            x.id.resize(5, 0);
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] = enterUniqueKey();
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] = enterFrequencyDAB();
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = enterEnsemble();
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE] = enterService();
            x.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT] = enterComponent();
            break;
        case IVIRadio::Types::Types::DeviceType::SDARS:
            break;
        //case IVIRadio::Types::Types::DeviceType::TV:
          //  break;
        default:
            // error
            fprintf(stderr, "Illegal device Type %d", (uint32_t)x.deviceType);
            exit(1);
    }

    return x;
}




// no return here, just use by reference parameters
void TerminalIO::enterStartTuneParameters(
    IVIRadio::Types::Types::StationSelector &station,
    IVIRadio::Station::StationTypes::SelectionMode &selectionMode,
    const IVIRadio::Station::StationTypes::StationList& stationsAMFM,
    const IVIRadio::Station::StationTypes::StationList& stationsDAB,
    const IVIRadio::Station::StationTypes::StationList& stationsUndef,
    uint32_t &handle
)
{
    printf("\nEntering StartTuneParameters:\n");
    selectionMode = enterSelectionMode();
    station = enterStationSelector(selectionMode, stationsAMFM, stationsDAB, stationsUndef);
    //handle = enterHandle();
}

// no return here, just use by reference parameters
void TerminalIO::enterSeekParameters(
    IVIRadio::Types::Types::DeviceType &deviceType,
    IVIRadio::Station::StationTypes::SeekMode &seekMode,
    uint8_t &genre,
    IVIRadio::Types::Types::UInt32s &flags
)
{
    printf("\nEntering SeekParameters:\n");
    deviceType = enterDeviceType();
    seekMode = enterSeekMode();
    genre = enterGenre();
    flags = enterFlags();
}

// no return here, just use by reference parameters
void TerminalIO::enterMakePermanentParameters(
    IVIRadio::Types::Types::StationSelector &stationSelector,
    bool &permanent,
    const IVIRadio::Station::StationTypes::StationList& stationsAMFM,
    const IVIRadio::Station::StationTypes::StationList& stationsDAB,
    const IVIRadio::Station::StationTypes::StationList& stationsUndef
)
{
    IVIRadio::Station::StationTypes::SelectionMode selectionMode = IVIRadio::Station::StationTypes::SelectionMode::SM_LIST;
    printf("\nEntering MakePermanentParameters:\n");
    stationSelector = enterStationSelector(selectionMode, stationsAMFM, stationsDAB, stationsUndef);
    permanent = enterPermanent();
}

// no return here, just use by reference parameters
void TerminalIO::enterControlUpdateParameters(
    IVIRadio::Station::StationTypes::UpdateElement &updateElement,
    IVIRadio::Types::Types::UpdateType 	&updateType	  ,
    uint32_t &sourceType ,
    uint32_t &stationType
)
{
    cout << endl << "Entering ControlUpdateParameters: " << endl;
    updateElement 	= enterUpdateElement		();
    updateType 		= enterUpdateType			();
    sourceType 		= (uint32_t)enterSourceType	();
    stationType 	= (uint32_t)enterStationType();
}

IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType TerminalIO::enterAnnouncementType()
{
    vector<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToAnnouncementType.cbegin(); it != nameToAnnouncementType.cend(); ++it, i++) {
        x.push_back((IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter AnnouncementType");
    printf("Selected value: %d, meaning %s\n", result,
        AnnouncementTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState TerminalIO::enterAnnouncementState(){
    vector<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToAnnouncementState.cbegin(); it != nameToAnnouncementState.cend(); ++it, i++) {
        x.push_back((IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter AnnouncementState");
    printf("Selected value: %d, meaning %s\n", result,
        AnnouncementStateToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

IVIRadio::AdditionalService::AdditionalServiceTypes::DataService TerminalIO::enterComponentType()
{
    vector<IVIRadio::AdditionalService::AdditionalServiceTypes::DataService> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = nameToComponentType.cbegin(); it != nameToComponentType.cend(); ++it, i++) {
        x.push_back((IVIRadio::AdditionalService::AdditionalServiceTypes::DataService)(*it).second);
        printf("%2d %-30s [%10d/0x%08x]\n", i, (*it).first.c_str(), (*it).second, (*it).second);
    }
    result = readNumber(0, x.size()-1, "Enter Componenttype");

    printf("Selected value: %d, meaning %s\n", result,
        ComponentTypeToName[(uint32_t)x[result]].c_str());
    return(x[result]);
}

uint32_t TerminalIO::enterComponentID()
{
    uint32_t result;
    //result = readNumber(0, UINT_MAX, "Enter Component ID");
    result = readNumber(0, 30, "Enter Component ID");
    printf("Selected value: %d, 0x%08x\n", result, result);
    return result;
}

uint32_t TerminalIO::enterComponentIDFromList(vector<uint32_t>& list)
{
    vector<uint32_t> x;
    int result;
    int i = 0;
    printf("\n");
    for (auto it = list.cbegin(); it != list.cend(); ++it, i++) {
        x.push_back(*it);
        printf("%2d %d\n", i, *it);
    }
    result = readNumber(0, x.size()-1, "Enter ComponentID");
    printf("Selected value: %d, meaning %d\n", result, x[result]);
    return(x[result]);
}

bool TerminalIO::enterComponentParameter()
{
    return readBoolean("Enter ComponentParameter.announcement.abort");
}

/*IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::ComponentTypeOptions TerminalIO::enterComponentTypeOptions( IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType compType )
{
    IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::ComponentTypeOptions options;

    if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_ANNOUNCEMENT ){
    	IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Announcement_TypeOptions dummy;
    	options = dummy;
		bool r;

		dummy.active = enterActivation();
		if (dummy.active == IVIRadio::Types::Types::Activation::ACTIVE) {
			uint32_t n = readNumber(0, 11, "How many announcementtypes", "");
			set<IVIRadio::AdditionalService::AdditionalServicesEnums::AnnouncementType> annTypesSeen;
			dummy.typeConfiguration.resize(n);

			for (int i = 0; i < n; i++) {
				int done = 0;
				do {
					printf("Entry %d\n", i);
					dummy.typeConfiguration[i].type = enterAnnouncementType();
					try {
						annTypesSeen.insert(dummy.typeConfiguration[i].type);
						done++;
					} catch (exception e) {
						printf("Sorry, this announcement type is already included.\n");
					}
					dummy.typeConfiguration[i].active = enterActivation();
					dummy.typeConfiguration[i].priority = readNumber(0, 15, "Enter priority", "");
				} while(!done);
			}
		} else {
			dummy.typeConfiguration.resize(0);
		}
		options = dummy;
    }
    else if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_EPG ) {
        IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::EPG_TypeOptions dummy;
        dummy.active = enterActivation();
        options = dummy;
    }
    else if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_JOURNALINE ){
        IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Journaline_TypeOptions dummy;
        dummy.active = enterActivation();
        options = dummy;
    }
    else if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_SLIDESHOW ){
	   IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Slideshow_TypeOptions dummy;
	   dummy.active = enterActivation();
	   options = dummy;
   }
    else if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_TELETEXT ){
		   IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Teletext_TypeOptions dummy;
		   dummy.active = enterActivation();
		   options = dummy;
    }
    else if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_BWS ){
		   IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::BWS_TypeOptions dummy;
		   dummy.active = enterActivation();
		   options = dummy;
    }
    else if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_SUBTITLE ){
		   IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Subtitle_TypeOptions dummy;
		   dummy.active = enterActivation();
		   options = dummy;
	   }
    else if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_TMC ){
		   IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TMC_TypeOptions dummy;
		   dummy.active = enterActivation();
		   options = dummy;
    	   }
    else if ( compType == IVIRadio::AdditionalService::AdditionalServicesEnums::ComponentType::CT_TPEG ){
		   IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TPEG_TypeOptions dummy;
		   dummy.active = enterActivation();
		   options = dummy;
    	   }
    else {
    	IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::EPG_TypeOptions dummy;
    	options = dummy;
    }
  //  options = dummy;
    return options;
}*/

string TerminalIO::getStationType(IVIRadio::Station::StationTypes::StationType x)
{
    string out;

    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_AUTOSTORED) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_AUTOSTORED);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_ENSEMBLE) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_ENSEMBLE);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_SERVICE) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_SERVICE);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PRIMARY) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PRIMARY);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_SECONDARY) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_SECONDARY);
        out += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_CHANGED) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_CHANGED);
        out += " ";
    }

    // special case for ST_UNDEF which is 0, where & does not work
    if (x == IVIRadio::Station::StationTypes::StationType::ST_UNDEF) {
        out += stationTypeToName.at((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF);
    }

    return out;
}

string TerminalIO::getSeekMode(IVIRadio::Station::StationTypes::SeekMode x)
{
    try {
        return seekModeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getSeekReturnValue(IVIRadio::Station::StationTypes::SeekReturnValue x)
{
    try {
        return seekReturnValueToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getSelectionMode(IVIRadio::Station::StationTypes::SelectionMode x)
{
    try {
        return selectionModeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getUpdateElement(IVIRadio::Station::StationTypes::UpdateElement x)
{
    try {
        return updateElementToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getSourceType(IVIRadio::Types::Types::SourceType x)
{
    try {
        return sourceTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getDeviceType(IVIRadio::Types::Types::DeviceType x)
{
	//cout << "Device Type: " << x << endl;
    try {
        return deviceTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getFeedback(IVIRadio::Types::Types::Feedback x)
{
    try {
        return feedbackToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getUpdateType(IVIRadio::Types::Types::UpdateType x)
{
    try {
        return updateTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getFlagsDefUndef(IVIRadio::Station::StationTypes::FlagsDefUndef x)
{
    try {
        return flagsDefUndefToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getFlagsDefAmFm(IVIRadio::Station::StationTypes::FlagsDefAmFm x)
{
    try {
        return flagsDefAmFmToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getFlagsDefDab(IVIRadio::Station::StationTypes::FlagsDefDab x)
{
    try {
        return flagsDefDabToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getQualityIndexUndef(IVIRadio::Station::StationTypes::QualityIndexUndef x)
{
    try {
        return qualityIndexUndefToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getQualityIndexAmFm(IVIRadio::Station::StationTypes::QualityIndexAmFm x)
{
    try {
        return qualityIndexAmFmToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getQualityIndexDab(IVIRadio::Station::StationTypes::QualityIndexDab x)
{
    try {
        return qualityIndexDabToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getNameIndexDab(IVIRadio::Station::StationTypes::NameIndexDab x)
{
    try {
        return nameIndexDabToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getNameIndexAmFm(IVIRadio::Station::StationTypes::NameIndexAmFm x)
{
    try {
        return nameIndexAmFmToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getNameIndexUndef(IVIRadio::Station::StationTypes::NameIndexUndef x)
{
    try {
        return nameIndexUndefToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getIdIndexUndef(IVIRadio::Station::StationTypes::IdIndexUndef x)
{
    try {
        return idIndexUndefToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getIdIndexAmFm(IVIRadio::Station::StationTypes::IdIndexAmFm x)
{
    try {
        return idIndexAmFmToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getIdIndexDab(IVIRadio::Station::StationTypes::IdIndexDab x)
{
    try {
        return idIndexDabToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getPermanent(bool x)
{
    return (x == true) ? "TRUE" : "FALSE";
}

string TerminalIO::getFrequency(bool x)
{
    return (x == true) ? "TRUE" : "FALSE";
}

string TerminalIO::getGenre(uint8_t x)
{
    char buffer[24];

    sprintf(buffer, "%d", x);
    string result(buffer);

    return result;
}

string TerminalIO::getFlags(uint32_t x)
{
    char buffer[24];

    sprintf(buffer, "%u", x);
    string result(buffer);

    return result;
}

string TerminalIO::getCallStatus(CommonAPI::CallStatus x)
{
    try {
        return callStatusToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}


string TerminalIO::getAnnouncementType(IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType x)
{
    try {
        return AnnouncementTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}


string TerminalIO::getAnnouncementState(IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState x)
{
    try {
        return AnnouncementStateToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}


string TerminalIO::getComponentType(IVIRadio::AdditionalService::AdditionalServiceTypes::DataService x)
{
    try {
        return ComponentTypeToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getComponentType(int x)
{
    try {
        return ComponentTypeToName.at( (uint32_t)x );
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getFlagDefAmFm(int x)
{
    try {
        return flagsDefAmFmToName.at( (uint32_t)x );
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getFlagDefDab(int x)
{
    try {
        return flagsDefDabToName.at( (uint32_t)x );
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getFlagDefUndef(int x)
{
    try {
        return flagsDefUndefToName.at( (uint32_t)x );
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getActivation(IVIRadio::Types::Types::Activation x)
{
    try {
        return ActivationToName.at((uint32_t)x);
    }
    catch (int e) {
        return "Undefined value";
    }
}

string TerminalIO::getFollowingType (IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType x){
	try {
		return FollowingModiToName.at((uint32_t)x);
	}
	/*catch (int e) {
		return "Undefined value";
	}*/
	/*catch (const std::exception& e){
		cout << e.what() << endl;
		return "real undef value";
	}*/
	catch (...){
		return "real undef value";
	}
}

string TerminalIO::getCountryVariant (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant x) {
	try {
		return CountryVariantsToName.at((uint32_t)x);
	}
	catch (int e) {
		return "Undefined value";
	}
}

string TerminalIO::getAMModi(IVIRadio::Configuration::ConfigurationTypesEnum::AMMode x){
	try {
		return AMModiToName.at((uint32_t)x);
	}
	catch (int e) {
		return "Undefined value";
	}

}

string TerminalIO::getDataFormat		( IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat 		x ){
	try {
		return DataFormatToName.at((uint32_t)x);
	}
	catch (int e) {
		return "Undefined value";
	}
}

string TerminalIO::getDataType			( IVIRadio::AdditionalService::AdditionalServiceTypes::DataType	 		x ){
	try {
		return DataTypeToName.at((uint32_t)x);
	}
	catch (int e) {
		return "Undefined value";
	}
}

// setter
//

IVIRadio::Station::StationTypes::StationType TerminalIO::setStationType(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::StationType)nameToStationType.at(x);
    }
    catch (int e) {
        throw invalid_argument("StationType value out or range");
    }
}

IVIRadio::Station::StationTypes::SeekMode TerminalIO::setSeekMode(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::SeekMode)nameToSeekMode.at(x);
    }
    catch (int e) {
        throw invalid_argument("SeekMode value out or range");
    }
}

IVIRadio::Station::StationTypes::SelectionMode TerminalIO::setSelectionMode(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::SelectionMode)nameToSelectionMode.at(x);
    }
    catch (int e) {
        throw invalid_argument("SelectionMode value out or range");
    }
}

IVIRadio::Station::StationTypes::UpdateElement TerminalIO::setUpdateElement(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::UpdateElement)nameToUpdateElement.at(x);
    }
    catch (int e) {
        throw invalid_argument("UpdateElement value out or range");
    }
}

IVIRadio::Types::Types::SourceType
TerminalIO::setSourceType(string x)
{
    try {
        return (IVIRadio::Types::Types::SourceType)nameToSourceType.at(x);
    }
    catch (int e) {
        throw invalid_argument("SourceType value out or range");
    }
}

IVIRadio::Types::Types::DeviceType
TerminalIO::setDeviceType(string x)
{
    try {
        return (IVIRadio::Types::Types::DeviceType)nameToDeviceType.at(x);
    }
    catch (int e) {
        throw invalid_argument("DeviceType value out or range");
    }
}

IVIRadio::Types::Types::Feedback
TerminalIO::setFeedback(string x)
{
    try {
        return (IVIRadio::Types::Types::Feedback)nameToFeedback.at(x);
    }
    catch (int e) {
        throw invalid_argument("Feedback value out or range");
    }
}

IVIRadio::Types::Types::UpdateType
TerminalIO::setUpdateType(string x)
{
    try {
        return (IVIRadio::Types::Types::UpdateType)nameToUpdateType.at(x);
    }
    catch (int e) {
        throw invalid_argument("UpdateType value out or range");
    }
}

IVIRadio::Station::StationTypes::FlagsDefUndef
TerminalIO::setFlagsDefUndef(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::FlagsDefUndef)nameToFlagsDefUndef.at(x);
    }
    catch (int e) {
        throw invalid_argument("FlagsDefUndef value out or range");
    }
}

IVIRadio::Station::StationTypes::FlagsDefAmFm
TerminalIO::setFlagsDefAmFm(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::FlagsDefAmFm)nameToFlagsDefAmFm.at(x);
    }
    catch (int e) {
        throw invalid_argument("FlagsDefAmFm value out or range");
    }
}

IVIRadio::Station::StationTypes::FlagsDefDab
TerminalIO::setFlagsDefDab(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::FlagsDefDab)nameToFlagsDefDab.at(x);
    }
    catch (int e) {
        throw invalid_argument("FlagsDefDab value out or range");
    }
}

IVIRadio::Station::StationTypes::QualityIndexUndef
TerminalIO::setQualityIndexUndef(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::QualityIndexUndef)nameToQualityIndexUndef.at(x);
    }
    catch (int e) {
        throw invalid_argument("QualityIndexUndef value out or range");
    }
}

IVIRadio::Station::StationTypes::QualityIndexAmFm
TerminalIO::setQualityIndexAmFm(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::QualityIndexAmFm)nameToQualityIndexAmFm.at(x);
    }
    catch (int e) {
        throw invalid_argument("QualityIndexAmFm value out or range");
    }
}

IVIRadio::Station::StationTypes::QualityIndexDab
TerminalIO::setQualityIndexDab(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::QualityIndexDab)nameToQualityIndexDab.at(x);
    }
    catch (int e) {
        throw invalid_argument("QualityIndexDab value out or range");
    }
}

IVIRadio::Station::StationTypes::NameIndexDab
TerminalIO::setNameIndexDab(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::NameIndexDab)nameToNameIndexDab.at(x);
    }
    catch (int e) {
        throw invalid_argument("NameIndexDab value out or range");
    }
}

IVIRadio::Station::StationTypes::NameIndexAmFm
TerminalIO::setNameIndexAmFm(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::NameIndexAmFm)nameToNameIndexAmFm.at(x);
    }
    catch (int e) {
        throw invalid_argument("NameIndexAmFm value out or range");
    }
}

IVIRadio::Station::StationTypes::NameIndexUndef
TerminalIO::setNameIndexUndef(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::NameIndexUndef)nameToNameIndexUndef.at(x);
    }
    catch (int e) {
        throw invalid_argument("NameIndexUndef value out or range");
    }
}

IVIRadio::Station::StationTypes::IdIndexUndef
TerminalIO::setIdIndexUndef(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::IdIndexUndef)nameToIdIndexUndef.at(x);
    }
    catch (int e) {
        throw invalid_argument("IdIndexUndef value out or range");
    }
}

IVIRadio::Station::StationTypes::IdIndexAmFm
TerminalIO::setIdIndexAmFm(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::IdIndexAmFm)nameToIdIndexAmFm.at(x);
    }
    catch (int e) {
        throw invalid_argument("IdIndexAmFm value out or range");
    }
}

IVIRadio::Station::StationTypes::IdIndexDab
TerminalIO::setIdIndexDab(string x)
{
    try {
        return (IVIRadio::Station::StationTypes::IdIndexDab)nameToIdIndexDab.at(x);
    }
    catch (int e) {
        throw invalid_argument("IdIndexDab value out or range");
    }
}

bool
TerminalIO::setPermanent(string x)
{
    if (x == "TRUE") {
        return true;
    } else if (x == "FALSE") {
        return false;
    } else {
        throw invalid_argument("setPermanent value out or range");
    }
}

bool
TerminalIO::setFrequency(string x)
{
    if (x == "TRUE") {
        return true;
    } else if (x == "FALSE") {
        return false;
    } else {
        throw invalid_argument("setFrequency value out or range");
    }
}

uint32_t
TerminalIO::setGenre(string x)
{
    uint32_t result;

    try {
        result = stoul (x, nullptr, 0);
        return result;
    } catch (int e) {
        throw invalid_argument("setGenre value out or range");
    }
}

uint32_t
TerminalIO::setFlags(string x)
{
    uint32_t result;

    try {
        result = stoul (x, nullptr, 0);
        return result;
    } catch (int e) {
        throw invalid_argument("setFlags value out or range");
    }
}

CommonAPI::CallStatus
TerminalIO::setCallStatus(string x)
{
    try {
        return (CommonAPI::CallStatus)nameToCallStatus.at(x);
    }
    catch (int e) {
        throw invalid_argument("CallStatus value out or range");
    }
}

void
TerminalIO::printStation(const IVIRadio::Station::StationTypes::Station& myStation)
{
    TerminalIO *tio = new TerminalIO();

    // debug
    printf("StationSelector:\n");
    printf("DeviceType: %s\n", tio->getDeviceType((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType).c_str());
    printf("Id:\n");
    switch((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType) {
        case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            printf("\tUNDEF_ID_KEY: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY]);
            if (myStation.sel.id.size() < 2) {
                printf("\tUNDEF_ID_PARENT: - not provided -\n");
            } else {
                printf("\tUNDEF_ID_PARENT: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_PARENT]);
            }
            break;
        case IVIRadio::Types::Types::DeviceType::AMFM:
            printf("\tAMFM_ID_KEY: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY]);
            printf("\tAMFM_ID_FREQUENCY: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
            printf("\tAMFM_ID_PI: %u, 0x%08x\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI], myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI]);
            printf("\tAMFM_ID_SERVICE %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE]);
            break;
        case IVIRadio::Types::Types::DeviceType::DAB:
            printf("\tDAB_ID_KEY: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY]);
            printf("\tDAB_ID_FREQUENCY: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY]);
            printf("\tDAB_ID_ENSEMBLE: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE]);
            printf("\tDAB_ID_SERVICE: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE]);
            printf("\tDAB_ID_COMPONENT: %u\n", myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT]);
            break;
        case IVIRadio::Types::Types::DeviceType::SDARS:
            fprintf(stderr, "SDARS not handled - sorry\n");
            exit(1);
        //case IVIRadio::Types::Types::DeviceType::TV:
          //  fprintf(stderr, "TV not handled - sorry\n");
            exit(1);
        default:
            // error
            fprintf(stderr, "Illegal device Type %d", (uint32_t)myStation.sel.deviceType);
            exit(1);
    }

    printf("StationType: %s\n", tio->getStationType((IVIRadio::Station::StationTypes::StationType)myStation.stationType).c_str());

    printf("Name:\n");
    switch((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType) {
        case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            printf("\tUNDEF_NAM_LONG: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_LONG].c_str());
            printf("\tUNDEF_NAM_SHORT: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_SHORT].c_str());
            printf("\tUNDEF_NAM_DYNAMIC: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_DYNAMIC].c_str());
            break;
        case IVIRadio::Types::Types::DeviceType::AMFM:
            printf("\tAMFM_NAM_PS: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_PS].c_str());
            printf("\tAMFM_NAM_HD: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_HD].c_str());
            printf("\tAMFM_NAM_RT: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_RT].c_str());
            break;
        case IVIRadio::Types::Types::DeviceType::DAB:
            printf("\tDAB_NAM_CLONG: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_CLONG].c_str());
            printf("\tDAB_NAM_CSHORT: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_CSHORT].c_str());
            printf("\tDAB_NAM_DYNAMIC: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_DYNAMIC].c_str());
            printf("\tDAB_NAM_SLONG: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SLONG].c_str());
            printf("\tDAB_NAM_SSHORT: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SSHORT].c_str());
            printf("\tDAB_NAM_ELONG: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_ELONG].c_str());
            printf("\tDAB_NAM_ESHORT: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_ESHORT].c_str());
            printf("\tDAB_NAM_FREQUENCY: %s\n", myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_FREQUENCY].c_str());
            break;
        // need no default since this has been checked before
    }

    // there are currently no specific enums for meta stuff, so we just output
    // the complete vector here
    cout << "Meta: " << endl;
    int k = 0;
    for (auto meta = myStation.meta.cbegin(); meta != myStation.meta.cend(); ++meta, k++) {
        printf("\tMeta[%d].type: %u\n", k, (*meta).type);
        printf("\tMeta[%d].name: %s\n", k, (*meta).str.c_str());
    }

    printf("Genre:\n");
    switch((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType) {
        case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            printf("\tUNDEF_GEN_STATIC: %u\n", myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexUndef::UNDEF_GEN_STATIC]);
            printf("\tUNDEF_GEN_DYNAMIC: %u\n", myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexUndef::UNDEF_GEN_DYNAMIC]);
            break;
        case IVIRadio::Types::Types::DeviceType::AMFM:
            printf("\tAMFM_GEN_PTY: %u\n", myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexAmFm::AMFM_GEN_PTY]);
            break;
        case IVIRadio::Types::Types::DeviceType::DAB:
            printf("\tDAB_GEN_STATIC_PTY: %u\n", myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexDab::DAB_GEN_STATIC_PTY]);
            printf("\tDAB_GEN_DYNAMIC_PTY: %u\n", myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexDab::DAB_GEN_DYNAMIC_PTY]);
            break;
        // need no default since this has been checked before
    }

    //k = 0;
    //for (auto flag = myStation.flags.cbegin(); flag != myStation.flags.cend(); ++flag, k++) {
        printf("Flags: %u\n, 0x%08x", myStation.flags, myStation.flags);
   // }

    printf("Quality:\n");
    switch((IVIRadio::Types::Types::DeviceType)myStation.sel.deviceType) {
        case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            printf("\tUNDEF_QAL_AUDIO: %u\n", myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexUndef::UNDEF_QAL_AUDIO]);
            break;
        case IVIRadio::Types::Types::DeviceType::AMFM:
            printf("\tAMFM_QAL_FIELDSTRENGTH: %u\n", myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_FIELDSTRENGTH]);
            printf("\tAMFM_QAL_MULTIPATH: %u\n", myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_MULTIPATH]);
            printf("\tAMFM_QAL_DIGITAL: %u\n", myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_DIGITAL]);
            break;
        case IVIRadio::Types::Types::DeviceType::DAB:
            printf("\tDAB_QAL_BER: %u\n", myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_BER]);
            printf("\tDAB_QAL_SERVICE: %u\n", myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_SERVICE]);
            printf("\tDAB_QAL_AUDIO: %u\n", myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_AUDIO]);
            break;
        // need no default since this has been checked before
    }
}

void
TerminalIO::printStationSelector(const IVIRadio::Types::Types::StationSelector& station)
{
    // print id's here depending on value
    switch((IVIRadio::Types::Types::DeviceType)station.deviceType) {
        case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            printf("UNDEF_ID_KEY: %u\n", station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY]);
            if (station.id.size() < 2) {
                printf("UNDEF_ID_PARENT: - not provided -\n");
            } else {
                printf("UNDEF_ID_PARENT: %u\n", station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_PARENT]);
            }
            break;
        case IVIRadio::Types::Types::DeviceType::AMFM:
        	cout << setw( 18 ) << "AMFM_ID_KEY:" 		<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY]		<< endl;;
        	cout << setw( 18 ) << "AMFM_ID_FREQUENCY:" 	<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]<< endl;;
        	cout << setw( 18 ) << "AMFM_ID_PI:" 		<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI] 		<< endl;;
        	cout << setw( 18 ) << "AMFM_ID_SERVICE" 	<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE] 	<< endl;
            break;
        case IVIRadio::Types::Types::DeviceType::DAB:
            cout << setw( 18 ) << "DAB_ID_KEY: " 		<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] 		<< endl;
            cout << setw( 18 ) << "DAB_ID_FREQUENCY:" 	<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] 	<< endl;
            cout << setw( 18 ) << "DAB_ID_ENSEMBLE:"	<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE] 	<< endl;
            cout << setw( 18 ) << "DAB_ID_SERVICE:" 	<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE] 	<< endl;
            cout << setw( 18 ) << "DAB_ID_COMPONENT" 	<< station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT] 	<< endl;
            break;
        case IVIRadio::Types::Types::DeviceType::SDARS:
            fprintf(stderr, "TV currently not handled - sorry\n");
            break;
       // case IVIRadio::Types::Types::DeviceType::TV:
         //   fprintf(stderr, "TV currently not handled - sorry\n");
            break;
        default:
            // error
            fprintf(stderr, "Illegal device Type %d", (uint32_t)station.deviceType);
            exit(1);
    }
}

string
TerminalIO::getStationTypeShort(uint32_t x)
{
    string result;

    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_RECEIVABLE) {
        result += "R";
    } else {
        result += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_PERMANENT) {
        result += "P";
    } else {
        result += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_AUTOSTORED) {
        result += "A";
    } else {
        result += " ";
    }
    if ((uint32_t)x & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_CHANGED) {
        result += "C";
    } else {
        result += " ";
    }
    return result;
}

void TerminalIO::printSelectParamter( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption dataServiceOption,
		uint32_t objectID) {

	if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_EPG ){
		cout << setw( 12 ) << "Start Date: " << dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::EPG_Options>().Start_Date_Time << endl;
		cout << setw( 12 ) << "End   Date: " << dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::EPG_Options>().End_Date_Time   << endl;
		cout << setw( 12 ) << "Genre     : " << dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::EPG_Options>().Genre     		<< endl;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_TELETEXT ){
		cout << "Entry    Number	: " << dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Teletext_Options>().Entry_Page   << endl;
		cout << "Subpage number		: " << dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Teletext_Options>().Sub_Page << endl;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_SUBTITLE ){
		for ( auto it = dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Subtitle_Options>().Languages.cbegin(); it != dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Subtitle_Options>().Languages.cend(); it++ ) {
			cout << "Language			: " << (*it).Name << endl;
		}
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_IMAGE ){
		cout << "Picture ID			: " << objectID << endl;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_JOURNALINE ){
		cout << setw(14) << "Object ID: " << objectID << endl;
		cout << setw(14) << "Entry object: " << dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Journaline_Options>().Entry_Object << endl;
	}
	else if ( dataServiceOption.isType<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options>() ){
		IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations annConf = dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options>().Type_Configurations;
		for (auto it = annConf.cbegin(); it != annConf.cend(); it++ ) {
			Log( "AnnouncementType	: " + getAnnouncementType( (*it).type )		, INFO);
			Log( "Active			: " + getActivation		 ( (*it).active )	, INFO);
			Log( "Priority			: " + to_string			 ( (*it).priority )	, INFO);
		}
	}
}

void TerminalIO::printStationListShort(const IVIRadio::Station::StationTypes::StationList& list)
{
    int i = 0;

    for ( auto it = list.stations.cbegin(); it != list.stations.cend(); it++, i++ ) {
        switch((IVIRadio::Types::Types::DeviceType)(*it).sel.deviceType) {

        	case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            	cout << setw( 3 ) << i << setw( 21 ) << (*it).name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_LONG].c_str()
            	<< " PICode:" << setw( 5 ) << (*it).sel.id[2] << " ID_KEY:" << setw(5) << (*it).sel.id[0];
            	cout << "Dataservices: "; flagsUNDEFHelp( (*it).flags );
            	cout << endl;
                break;

        	case IVIRadio::Types::Types::DeviceType::AMFM:
            	cout << setw(3) << i << " [" << getStationTypeShort((*it).stationType).c_str() << "] " << setw(6) <<  ( *it ).sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] << " kHz ";
            	cout.width(20);
            	cout << std::left << ( *it ).name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_HD].c_str()
            	<< " PICode: "<< setw( 5 ) << (*it).sel.id[2] << " ID_KEY: " << setw(5) << (*it).sel.id[0] ;
            		cout << "Dataservices: "; flagsAMFMHelp( (*it).flags );
                	cout << endl;
                break;

        	case IVIRadio::Types::Types::DeviceType::DAB:
            	cout << setw(3) << i << " [" << getStationTypeShort((*it).stationType).c_str() << "] " << setw(6) <<  ( *it ).sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] << " kHz ";
							cout.width(20); cout << std::left << ( *it ).name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SLONG].c_str() << " SICode: "<< setw( 5 ) << (*it).sel.id[2]<< " ID_KEY: " << setw(5) << (*it).sel.id[0] ;
			            	cout << "Dataservices: "; flagsDABHelp( (*it).flags );
			            	cout << endl;
				cout << endl;
                break;

        	default:
                break;
        }
    }
}

void TerminalIO::flagsAMFMHelp( uint32_t flags ){
	uint32_t tmp = 1;
	while ( tmp <= flags ){
		tmp = tmp * 2;
	}
	tmp = tmp / 2;
	while ( flags != 0 ) {
		cout << setw(26) << getFlagDefAmFm( tmp );
		flags = flags % tmp;
		while ( tmp > flags)
			tmp = tmp / 2;
	}
}
void TerminalIO::flagsDABHelp  ( uint32_t flags ){
	uint32_t tmp = 1;
	while ( tmp <= flags ){
		tmp = tmp * 2;
	}
	tmp = tmp / 2;
	while ( flags != 0 ) {
		cout << setw(26) << getFlagDefDab( tmp );
		flags = flags % tmp;
		while ( tmp > flags )
			tmp = tmp / 2;
	}
}

void TerminalIO::flagsUNDEFHelp( uint32_t flags ){
	uint32_t tmp = 1;
	while ( tmp <= flags ){
		tmp = tmp * 2;
	}
	tmp = tmp / 2;
	while ( flags != 0 ) {
		cout << setw(26) << getFlagDefUndef(tmp);
		flags = flags % tmp;
		while ( tmp > flags)
			tmp = tmp / 2;
	}
}


void TerminalIO::printStationListShortSelective(IVIRadio::Station::StationTypes::StationList list, IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService )
{
	int i = 0;
    int printStation = 0;
    for ( auto it = list.stations.cbegin(); it != list.stations.cend(); it++, i++ ) {
        switch((IVIRadio::Types::Types::DeviceType)(*it).sel.deviceType) {
            case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
                printf("%3d %s\n", i,
                    (*it).name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::UNDEF_NAM_LONG].c_str());
                break;

            case IVIRadio::Types::Types::DeviceType::AMFM:
            	printStation = 0;
            	for (auto meta = (*it).meta.cbegin(); meta !=  (*it).meta.cend(); ++meta) {
					uint32_t itype = ( *meta ).type;
					if ( ((uint32_t)dataService == itype) )
						printStation++;
				}
            	if ( printStation == 0 ){
            		break;
            	}
            	cout << setw(3) << i << " [" << getStationTypeShort((*it).stationType).c_str() << "] " << setw(6) <<  ( *it ).sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] << " kHz ";
            	cout.width(20); cout << std::left << ( *it ).name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_HD].c_str();

                	for (auto meta = (*it).meta.cbegin(); meta !=  (*it).meta.cend(); ++meta) {
                		int itype = ( *meta ).type;
                		string tmp = "  DS: " + getComponentType( itype ) + "  ID: " + (*meta).str.c_str() ;
                		cout << setw( 30 ) << tmp;
                	}
                	cout << endl;
                break;
            case IVIRadio::Types::Types::DeviceType::DAB:

            	printStation = 0;
				for (auto meta = (*it).meta.cbegin(); meta !=  (*it).meta.cend(); ++meta) {
					uint32_t itype = ( *meta ).type;
					if ( ((uint32_t)dataService == itype) )
						printStation++;
				}
				if ( printStation == 0 ){
					break;
				}
            	cout << setw(3) << i << " [" << getStationTypeShort((*it).stationType).c_str() << "] " << setw(6) <<  ( *it ).sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] << " kHz ";
							cout.width(20); cout << std::left << ( *it ).name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SLONG].c_str();
				for (auto meta = (*it).meta.cbegin(); meta !=  (*it).meta.cend(); ++meta) {
					int itype = ( *meta ).type;
					string tmp = "  DS: " + getComponentType( itype ) + "  ID: " + (*meta).str.c_str() ;
					cout << setw( 30 ) << tmp;
				}
				cout << endl;
                break;
            default:
                break;
        }
    }
}


/*void TerminalIO::printComponentTypeOptions(const IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::ComponentTypeOptions& componentTypeOptions)
{

	if (componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::EPG_TypeOptions>()) {
		cout << "componentType is EPG ..." << endl;
		if ( componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::EPG_TypeOptions>().active == IVIRadio::Types::Types::Activation::INACTIVE ){
			cout << "EPG is now inactive" << endl;
		}
		else {
			cout << "EPG is now active" << endl;
		}
	}
	else if (componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Journaline_TypeOptions>()) {
		cout << "componentType is Journaline ..." << endl;
		if ( componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Journaline_TypeOptions>().active == IVIRadio::Types::Types::Activation::INACTIVE ){
			cout << "Journaline is now inactive" << endl;
		}
		else {
			cout << "Journaline is now active" << endl;
		}
	}
	else if (componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Slideshow_TypeOptions>()) {
		cout << "componentType is Slideshow ..." << endl;
		if ( componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Slideshow_TypeOptions>().active == IVIRadio::Types::Types::Activation::INACTIVE ){
			cout << "Slideshow is now inactive" << endl;
		}
		else {
			cout << "Slideshow is now active" << endl;
		}
	}
	else if (componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Subtitle_TypeOptions>()) {
		cout << "componentType is Subtitle ..." << endl;
		if ( componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Subtitle_TypeOptions>().active == IVIRadio::Types::Types::Activation::INACTIVE ){
			cout << "Subtitle is now inactive" << endl;
		}
		else {
			cout << "Subtitle is now active" << endl;
		}
	}
	else if (componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TPEG_TypeOptions>()) {
		cout << "componentType is TPEG ..." << endl;
		if ( componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TPEG_TypeOptions>().active == IVIRadio::Types::Types::Activation::INACTIVE ){
			cout << "TPEG is now inactive" << endl;
		}
		else {
			cout << "TPEG is now active" << endl;
		}
	}
	else if (componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TMC_TypeOptions>()) {
		cout << "componentType is TMC ..." << endl;
		if ( componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TMC_TypeOptions>().active == IVIRadio::Types::Types::Activation::INACTIVE ){
			cout << "TMC is now inactive" << endl;
		}
		else {
			cout << "TMC is now active" << endl;
		}
	}
	else if (componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Teletext_TypeOptions>()) {
		cout << "componentType is Teletext ..." << endl;
		if ( componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Teletext_TypeOptions>().active == IVIRadio::Types::Types::Activation::INACTIVE ){
			cout << "Teletext is now inactive" << endl;
		}
		else {
			cout << "Teletext is now active" << endl;
		}
	}
	else if (componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::BWS_TypeOptions>()) {
		cout << "componentType is BWS ..." << endl;
		if ( componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::BWS_TypeOptions>().active == IVIRadio::Types::Types::Activation::INACTIVE ){
			cout << "BWS is now inactive" << endl;
		}
		else {
			cout << "BWS is now active" << endl;
		}
	}
	else if ( componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Announcement_TypeOptions>() ){

		printf("componentTypeOptions.announcement_configuration.activity: %s\n", getActivation(componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Announcement_TypeOptions>().active).c_str());

	    int k = 0;
	    for (auto it = componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Announcement_TypeOptions>().typeConfiguration.cbegin();
	        it != componentTypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Announcement_TypeOptions>().typeConfiguration.cend(); it++, k++) {
	        //printf("componentTypeOptions.announcement_configuration.typeConfiguration[%d].active: %s\n", k, ((*it).active == true) ? "TRUE" : "FALSE");
	        printf("componentTypeOptions.announcement_configuration.typeConfiguration[%d].priority: %u\n", k, (*it).priority);
	        printf("componentTypeOptions.announcement_configuration.typeConfiguration[%d].type: %s\n", k, getAnnouncementType((*it).type).c_str());
	    }
	}

	else if (!componentTypeOptions.isType<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Announcement_TypeOptions>()) {
        printf("componenTypeOptions not of type AnnouncementConfiguration\n");
        printf("not implemented\n");
        return;
    }


}*/

void TerminalIO::printFunctionalityTypesOptionsGet ( 	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
												IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityoptions ) {
	auto itOptions = functionalityoptions.cbegin();
	for (auto it = functionalityTypes.cbegin(); it != functionalityTypes.cend(); it++, itOptions++ ){
		cout << endl << "Functionality Type: " << FunctionalityTypeToName.at((uint32_t)(*it)) << endl << endl;
		if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::HD ){
			cout << "Device Type: " <<
			getDeviceType((*itOptions).get<IVIRadio::Configuration::ConfigurationOptionsGetter::HDOptionsGet>().deviceType).c_str() << endl;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::Following 	){
			vector <IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType> vec = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptionsGetter::FollowingOptionsGet>().followingTypes;
			for ( auto it_follTypes = vec.cbegin() ; it_follTypes != vec.cend(); it_follTypes++ ) {
				cout << "Following Type: " << getFollowingType ( (*it_follTypes) ).c_str() << endl;
			}
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::SmartFavorite ){
			cout << "Device Type: " <<
			getDeviceType((*itOptions).get<IVIRadio::Configuration::ConfigurationOptionsGetter::SmartFavoriteOptionsGet>().deviceType).c_str() << endl;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AvailableBand 		){

			vector <IVIRadio::Types::Types::DeviceType> vec_dev = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptionsGetter::AvailableBandoptionsGet>().deviceTypes;
			for ( auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it_dev++ ){
				cout << "DeviceType    : " << getDeviceType( (*it_dev)).c_str() << endl;
			}
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CountryVariant 		){
			vector <IVIRadio::Types::Types::DeviceType> vec_dev = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptionsGetter::CountryVariantsOptionsGet>().deviceTypes;
			for ( auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it_dev++ ){
				cout << "DeviceType    : " << getDeviceType( (*it_dev)).c_str() << endl;
			}
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CoverageArea 		){
			vector <IVIRadio::Types::Types::DeviceType> vec_dev = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptionsGetter::CoverageAreaOptionsGet>().deviceTypes;
			for ( auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it_dev++ ){
				cout << "DeviceType    : " << getDeviceType( (*it_dev)).c_str() << endl;
			}
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::InterfaceVersion 	){
			//cout << "Interface Version: major: " << (*itOptions).get<IVIRadio::Configuration::ConfigurationOptionsGetter::InterfaceVersionOptions>().majorVersion
				// << " minor: " << (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions>().minorVersion << endl;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AMModi 				){
			cout << "Device Type: " << getDeviceType( (*itOptions).get<IVIRadio::Configuration::ConfigurationOptionsGetter::AMModiOptionsGet>().deviceType).c_str() << endl;
		}
	}

}


void TerminalIO::printFunctionalityTypesOptions (
		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes 	functionalityTypes,
		IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions 			functionalityoptions  )
{
	auto itOptions = functionalityoptions.cbegin();
	cout << "printFunctionalityTypesOptions...." << endl;
	for (auto it = functionalityTypes.cbegin(); it != functionalityTypes.cend(); it++, itOptions++ ){
		if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::HD ){
			cout << "Activity: " <<
			getActivation((*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::HDOptions>().activation).c_str() << endl;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::Following 	){
			cout << "FunctionalityType::Following" << endl;
			vector< IVIRadio::Types::Types::Activation > 									vec_activations = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::FollowingOptions>().activations;
			vector< IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType >   vec_follStates  = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::FollowingOptions>().followingStates;
			auto it_follStates = vec_follStates.cbegin();
			for (auto it = vec_activations.cbegin() ; it != vec_activations.cend(); it++, it_follStates++) {
				cout << "Following Type: " << getFollowingType ( (*it_follStates) ).c_str() << endl;
				cout << "Activity      : " << getActivation    ( (*it) ).c_str() 			<< endl;
			}
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::SmartFavorite 		){
			cout << "Activity: " <<
			getActivation    ((*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::SmartFavoriteOptions>().activity     ).c_str() << endl;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AvailableBand 		){

			vector <IVIRadio::Types::Types::DeviceType> vec_dev = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions>().deviceTypes;
			vector <IVIRadio::Types::Types::SourceType> vec     = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions>().availableBands;

			auto it = vec.cbegin();
			for (  auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it++, it_dev++ ){
				cout << "DeviceType    : " << getDeviceType( (*it_dev)).c_str() << endl;
				cout << "Available Band: " << getSourceType( (*it    )).c_str() << endl;
			}
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CountryVariant 		){
			vector<IVIRadio::Types::Types::DeviceType> vec_dev = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions>().deviceTypes;
			vector<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant> vec_cv = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions>().countryVariants;
 			auto it_cv = vec_cv.cbegin();
			for (auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it_dev++, it_cv++){
 				cout << "Device Type	: " << getDeviceType    ((*it_dev)).c_str() << endl;
 				cout << "Country Variant: " << getCountryVariant((*it_cv )).c_str() << endl;
 			}
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CoverageArea 		){
			cout << "Functionality Type: Coverage Area " << endl;
			vector<IVIRadio::Types::Types::DeviceType> vec_dev = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::CoverageAreaOptions>().deviceTypes;
			vector<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant> vec_cv = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::CoverageAreaOptions>().countryVariants;
			cout << "vectors correct " << endl;
			auto it_cv = vec_cv.cbegin();
			cout << "it correct " << endl;
			for (auto it = vec_dev.cbegin(); it != vec_dev.cend(); it++, it_cv++){
				cout << "Device Type	: " << getDeviceType    ((*it   )).c_str() << endl;
				cout << "Country Variant: " << getCountryVariant((*it_cv)).c_str() << endl;
			}
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::InterfaceVersion 	){
			cout << "Interface Version: major: " << (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions>().majorVersion
				 << " minor: " << (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions>().minorVersion << endl;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AMModi 				){
			cout << "Device Type: " << getDeviceType( (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::AMModiOptions>().deviceType).c_str() << endl;
			cout << "AM Mode    : " << getAMModi	( (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::AMModiOptions>().amMode    ).c_str() << endl;
		}
	}
}

int
TerminalIO::enterFromStationList(const IVIRadio::Station::StationTypes::StationList& list)
{
    int ret;
    int index;
    int sz;
    printStationListShort(list);
    // count elements
    sz = 0;
    for (auto it = list.stations.cbegin(); it != list.stations.cend(); it++, sz++);
    index = readNumber(0, sz-1, "Enter station number");
    // check entry and return correct id
    switch((IVIRadio::Types::Types::DeviceType)list.stations[index].sel.deviceType) {
        case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
            ret = list.stations[index].sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY];
            break;
        case IVIRadio::Types::Types::DeviceType::AMFM:
            ret = list.stations[index].sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY];
            break;
        case IVIRadio::Types::Types::DeviceType::DAB:
            ret = list.stations[index].sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY];
            break;
        default:
            // error
            break;
    }

    return ret;
}
