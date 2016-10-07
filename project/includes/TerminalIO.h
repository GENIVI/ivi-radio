///////////////////////////////////////////////////////////
//  TerminalIO.h
//  Implementation of the Class TerminalIO
//  Created on:      16-Jul-2013 16:47:52
//  Original author: qx92858
///////////////////////////////////////////////////////////


#if !defined(EA_839E62CA_EE73_4dae_B295_1A13DF9512E2__INCLUDED_)
#define EA_839E62CA_EE73_4dae_B295_1A13DF9512E2__INCLUDED_

#include <stddef.h>
#include <string>
#include <stdio.h>
#include <map>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <err.h>
#include <string.h>
#include <memory>
#include <iostream>
#include <unistd.h>
#include <exception>
#include <iomanip>
#include <set>
#include <sstream>
#include </usr/include/asm-generic/errno-base.h>


#include "IVIRadio/Station/StationStubDefault.h"
#include "IVIRadio/Types/Types.h"
#include "IVIRadio/Station/StationTypes.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypes.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypesOptions.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypes.h"
#include "IVIRadio/Configuration/ConfigurationOptions.h"
#include "IVIRadio/Configuration/ConfigurationOptionsGetter.h"
#include "IVIRadio/Configuration/ConfigurationTypesEnum.h"

#include <CommonAPI/Runtime.h>

using namespace std;

/**
 * \class TerminalIO -
 *
 * \brief class cares about input from and output to the console
 *
 * class cares about input from and output to the console\n
 * this class deals with everything required to read input from console\n
 * terminal for the parameters required by the different methods, as well\n
 * as for printing parameters or general special and enumeration types\n
 * to console.\n
 *\n
 * The method prefixes used for this purpose are\n
 *    'enter...' (for input)\n
 *    'get...'   (for translation from value to string for use in print)\n
 *    'print...' (for actually performing print to console)\n
 *\n
 * Internally, the class contains mapping table (in both direction) from\n
 * enumeration values to strings and vice versa. If values are not existing\n
 * within an enumeration, the 'get...' method returns the string\n
 * 'undefined value' to avoid a crash on lookup.\n
 *\n
 * \author Guido Ostkamp
 * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2013/06/16 14:16:20
 *
 * Contact: bernhard.singer@partner.bmw.de
 *
  * Copyright
 * Copyright (C) 2013, GENIVI Alliance, Inc.
 * Copyright (C) 2013, BMW AG
 *
 * Contributions are licensed to the GENIVI Alliance under one or more
 * Contribution License Agreements or MPL 2.0 .
 *
 * (C) Copyright
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
 * this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#define DEBUG 1
#define VERBOSE 2
#define ERROR 3
#define WARNING 4
#define INFO 5


class TerminalIO
{

public:
	virtual ~TerminalIO();

	static TerminalIO* getInstance();

	// functions reading input from console via menu
	/**
	 * \brief read a number inside given interval (minval-maxval) with prompt
	 * \param minval an unsigned int minimal value of possible range for input
	 * \param maxval an unsigned int maximal value of possible range for input
	 * \param menu an string optional with default value is an empty string
	 * \return unsigned int the number from the input
	 */
	unsigned int readNumber(unsigned int minval, unsigned int maxval, string question, string menu = "");

	/**
	 * \brief read a number inside given interval (minval-maxval) with prompt
	 * \param question an string question the user is confronted with
	 * \return boolean from the input
	 */
	bool readBoolean(string question);

	void Log( string log, int level );

	IVIRadio::Types::Types::Feedback						enterFeedback();


	IVIRadio::Types::Types::SourceType 						enterSourceType			();
	IVIRadio::Types::Types::DeviceType 						enterDeviceType			();

	IVIRadio::Station::StationTypes::StationType	 		enterStationType		();
	IVIRadio::Station::StationTypes::SeekMode 				enterSeekMode			();
	IVIRadio::Station::StationTypes::SelectionMode 			enterSelectionMode		();
	IVIRadio::Station::StationTypes::UpdateElement 			enterUpdateElement		();
	IVIRadio::Types::Types::UpdateType 						enterUpdateType			();
	IVIRadio::Station::StationTypes::FlagsDefUndef 			enterFlagsDefUndef		();
	IVIRadio::Station::StationTypes::FlagsDefAmFm 			enterFlagsDefAmFm		();
	IVIRadio::Station::StationTypes::FlagsDefDab 			enterFlagsDefDab		();
	IVIRadio::Station::StationTypes::QualityIndexUndef 		enterQualityIndexUndef	();
	IVIRadio::Station::StationTypes::QualityIndexAmFm 		enterQualityIndexAmFm	();
	IVIRadio::Station::StationTypes::QualityIndexDab 		enterQualityIndexDab	();
	IVIRadio::Station::StationTypes::NameIndexDab 			enterNameIndexDab		();
	IVIRadio::Station::StationTypes::NameIndexAmFm 			enterNameIndexAmFm		();
	IVIRadio::Station::StationTypes::NameIndexUndef 		enterNameIndexUndef		();
	IVIRadio::Station::StationTypes::IdIndexDab 			enterIdIndexDab			();
	IVIRadio::Station::StationTypes::IdIndexAmFm 			enterIdIndexAmFm		();
	IVIRadio::Station::StationTypes::IdIndexUndef 			enterIdIndexUndef		();


	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType		enterFunctionalityType	();
	IVIRadio::Configuration::ConfigurationTypesEnum::AMMode					enterAMModi				();
	IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType			enterFollowingType		();
	IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant			enterCountryVariants	();

	IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions 	enterAvailableBandOptions 	();
	IVIRadio::Configuration::ConfigurationOptions::HDOptions 				enterHDOptions 				();
	IVIRadio::Configuration::ConfigurationOptions::FollowingOptions 		enterFollowingOptions		();
	IVIRadio::Configuration::ConfigurationOptions::SmartFavoriteOptions 	enterSmartFavoriteOptions	();
	IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions 	enterCountryVariantOptions	();
	IVIRadio::Configuration::ConfigurationOptions::CoverageAreaOptions		enterCoverageAreaOptions	();
	IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions	enterInterfaceVersionOptions();
	IVIRadio::Configuration::ConfigurationOptions::AMModiOptions			enterAMModiOptions			();
	IVIRadio::Configuration::ConfigurationOptions::RDSOptions				enterRDSOptions				();
	IVIRadio::Configuration::ConfigurationOptions::DLSOptions				enterDLSOptions				();
	IVIRadio::Configuration::ConfigurationOptions::RTOptions				enterRTOptions				();

	IVIRadio::Configuration::ConfigurationOptionsGetter::AvailableBandoptionsGet	enterAvailableBandOptionsGet	();
	IVIRadio::Configuration::ConfigurationOptionsGetter::HDOptionsGet				enterHDOptionsGet				();
	IVIRadio::Configuration::ConfigurationOptionsGetter::FollowingOptionsGet		enterFollowingOptionsGet		();
	IVIRadio::Configuration::ConfigurationOptionsGetter::SmartFavoriteOptionsGet	enterSmartFavoriteOptionsGet	();
	IVIRadio::Configuration::ConfigurationOptionsGetter::CountryVariantsOptionsGet	enterCountryVariantOptionsGet	();
	IVIRadio::Configuration::ConfigurationOptionsGetter::CoverageAreaOptionsGet		enterCoverageAreaOptionsGet		();
	IVIRadio::Configuration::ConfigurationOptionsGetter::InterfaceVersionOptionsGet	enterInterfaceVersionOptionsGet	();
	IVIRadio::Configuration::ConfigurationOptionsGetter::AMModiOptionsGet			enterAMModiIOptionsGet			();
	IVIRadio::Configuration::ConfigurationOptionsGetter::RDSOptionsGet				enterRDSOptionsGet				();
	IVIRadio::Configuration::ConfigurationOptionsGetter::DLSOptionsGet				enterDLSOptionsGet				();
	IVIRadio::Configuration::ConfigurationOptionsGetter::RTOptionsGet				enterRTOptionsGet				();

	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes				enterFunctionalityTypes   		();
	IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions				enterFunctionalityOptions		( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes&  functionalityTypes );
	IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet		enterFunctionalityOptionsGet  	( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes& functionalityTypes );

	IVIRadio::Types::Types::UInt32s enterFlags();

	uint32_t enterHandle		();
	uint32_t enterFrequencyFM	();
	uint32_t enterPi			();
	uint32_t enterFrequencyDAB	();
	uint32_t enterUniqueKey		();
	uint32_t enterParent		();
	uint32_t enterService		();
	uint32_t enterEnsemble		();
	uint32_t enterComponent		();
	uint8_t  enterGenre			();

	bool enterPermanent();

	// following function is overloaded
	IVIRadio::Types::Types::StationSelector enterStationSelector();

	IVIRadio::Types::Types::StationSelector enterStationSelector(
		IVIRadio::Station::StationTypes::SelectionMode selectionMode,
		const IVIRadio::Station::StationTypes::StationList& stationsAMFM,
		const IVIRadio::Station::StationTypes::StationList& stationsDAB,
		const IVIRadio::Station::StationTypes::StationList& stationsUndef
	);

	void enterStartTuneParameters(
		IVIRadio::Types::Types::StationSelector &station,
		IVIRadio::Station::StationTypes::SelectionMode &selectionMode,
		const IVIRadio::Station::StationTypes::StationList& stationsAMFM,
		const IVIRadio::Station::StationTypes::StationList& stationsDAB,
		const IVIRadio::Station::StationTypes::StationList& stationsUndef,
		uint32_t &handle
	);

	// no return here, just use by reference parameters
	void enterSeekParameters(
		IVIRadio::Types::Types::DeviceType &deviceType,
		IVIRadio::Station::StationTypes::SeekMode &seekMode,
		uint8_t &genre,
		IVIRadio::Types::Types::UInt32s &flags
	);

	// no return here, just use by reference parameters
	void enterMakePermanentParameters(
		IVIRadio::Types::Types::StationSelector &stationSelector,
		bool &permanent,
		const IVIRadio::Station::StationTypes::StationList& stationsAMFM,
		const IVIRadio::Station::StationTypes::StationList& stationsDAB,
		const IVIRadio::Station::StationTypes::StationList& stationsUndef
	);

	// no return here, just use by reference parameters
	void enterControlUpdateParameters(
		IVIRadio::Station::StationTypes::UpdateElement &updateElement,
		IVIRadio::Types::Types::UpdateType &updateType,
		uint32_t &sourceType,
		uint32_t &stationType
	);

	int enterFromStationList(const IVIRadio::Station::StationTypes::StationList& stations);

	IVIRadio::AdditionalService::AdditionalServiceTypes::DataService enterComponentType();

	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType enterAnnouncementType();

	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState enterAnnouncementState();

	uint32_t enterComponentID();

	uint32_t enterComponentIDFromList(vector<uint32_t>& list);

	bool enterComponentParameter();

	//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::ComponentTypeOptions enterComponentTypeOptions( IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType compType );

	IVIRadio::Types::Types::Activation enterActivation();

	// functions returning string from enumeration value
	string getFeedback			( IVIRadio::Types::Types::Feedback  						x );
	string getActivation		( IVIRadio::Types::Types::Activation 					 	  );
	string getStationType		( IVIRadio::Station::StationTypes::StationType 		x );
	string getSeekMode			( IVIRadio::Station::StationTypes::SeekMode 			x );
	string getSeekReturnValue	( IVIRadio::Station::StationTypes::SeekReturnValue 	x );
	string getSelectionMode		( IVIRadio::Station::StationTypes::SelectionMode 		x );
	string getUpdateElement		( IVIRadio::Station::StationTypes::UpdateElement   	x );
	string getSourceType		( IVIRadio::Types::Types::SourceType 		 				x );
	string getDeviceType		( IVIRadio::Types::Types::DeviceType 		 				x );
	string getUpdateType		( IVIRadio::Types::Types::UpdateType 			x );
	string getFlagsDefUndef		( IVIRadio::Station::StationTypes::FlagsDefUndef 		x );
	string getFlagsDefAmFm		( IVIRadio::Station::StationTypes::FlagsDefAmFm  		x );
	string getFlagsDefDab		( IVIRadio::Station::StationTypes::FlagsDefDab 		x );
	string getQualityIndexUndef	( IVIRadio::Station::StationTypes::QualityIndexUndef 	x );
	string getQualityIndexAmFm	( IVIRadio::Station::StationTypes::QualityIndexAmFm  	x );
	string getQualityIndexDab	( IVIRadio::Station::StationTypes::QualityIndexDab   	x );
	string getNameIndexDab		( IVIRadio::Station::StationTypes::NameIndexDab 	 	x );
	string getNameIndexAmFm		( IVIRadio::Station::StationTypes::NameIndexAmFm 	 	x );
	string getNameIndexUndef	( IVIRadio::Station::StationTypes::NameIndexUndef 	 	x );
	string getIdIndexUndef		( IVIRadio::Station::StationTypes::IdIndexUndef 	 	x );
	string getIdIndexAmFm		( IVIRadio::Station::StationTypes::IdIndexAmFm 		x );
	string getIdIndexDab		( IVIRadio::Station::StationTypes::IdIndexDab 		 	x );
	string getPermanent			( bool 		x );
	string getFrequency			( bool 		x );
	string getGenre				( uint8_t  	x );
	string getFlags				( uint32_t 	x );
	string getStationTypeShort	( uint32_t 	x );
	string getCallStatus		( CommonAPI::CallStatus x);
	string getAnnouncementType	( IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType );
	string getComponentType		( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService	  );
	string getComponentType		( int );
	string getAnnouncementState	(IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState x);
	string getFlagDefAmFm       ( int x );
	string getFlagDefDab		( int x );
	string getFlagDefUndef 		( int x );

	string getFollowingType 	( IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType	 	x );
	string getCountryVariant 	( IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant   	x );
	string getAMModi			( IVIRadio::Configuration::ConfigurationTypesEnum::AMMode    			x );

	string getDataFormat		( IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat 		x );
	string getDataType			( IVIRadio::AdditionalService::AdditionalServiceTypes::DataType	 		x );

	// setter turning string into value
	IVIRadio::Types::Types::Feedback setFeedback(string x);
	IVIRadio::Types::Types::SourceType 							setSourceType		(string x);
	IVIRadio::Types::Types::DeviceType 							setDeviceType		(string x);

	IVIRadio::Station::StationTypes::StationType 			setStationType		(string x);
	IVIRadio::Station::StationTypes::SeekMode 				setSeekMode			(string x);
	IVIRadio::Station::StationTypes::SelectionMode 			setSelectionMode	(string x);
	IVIRadio::Station::StationTypes::UpdateElement 			setUpdateElement	(string x);
	IVIRadio::Types::Types::UpdateType 						setUpdateType		(string x);
	IVIRadio::Station::StationTypes::FlagsDefUndef 			setFlagsDefUndef	(string x);
	IVIRadio::Station::StationTypes::FlagsDefAmFm 			setFlagsDefAmFm		(string x);
	IVIRadio::Station::StationTypes::FlagsDefDab 			setFlagsDefDab		(string x);
	IVIRadio::Station::StationTypes::QualityIndexUndef 		setQualityIndexUndef(string x);
	IVIRadio::Station::StationTypes::QualityIndexAmFm 		setQualityIndexAmFm	(string x);
	IVIRadio::Station::StationTypes::QualityIndexDab 		setQualityIndexDab	(string x);
	IVIRadio::Station::StationTypes::NameIndexDab 			setNameIndexDab		(string x);
	IVIRadio::Station::StationTypes::NameIndexAmFm 			setNameIndexAmFm	(string x);
	IVIRadio::Station::StationTypes::NameIndexUndef 		setNameIndexUndef	(string x);
	IVIRadio::Station::StationTypes::IdIndexUndef 			setIdIndexUndef		(string x);
	IVIRadio::Station::StationTypes::IdIndexAmFm 			setIdIndexAmFm		(string x);
	IVIRadio::Station::StationTypes::IdIndexDab 			setIdIndexDab		(string x);

	bool setPermanent(string x);
	bool setFrequency(string x);
	uint32_t setGenre(string x);
	uint32_t setFlags(string x);
	CommonAPI::CallStatus setCallStatus(string x);

	// debug print methods
	void printStation					( const IVIRadio::Station::StationTypes::Station& myStation);
	void printStationSelector			( const IVIRadio::Types::Types::StationSelector& station);
	void printStationListShort			( const IVIRadio::Station::StationTypes::StationList& stations);
	void printStationListShortSelective	( IVIRadio::Station::StationTypes::StationList list,
			IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService);

	void printSelectParamter			( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption dataServiceOption, uint32_t objectID );


	void printFunctionalityTypesOptionsGet ( 	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
												IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityoptions );

	void printFunctionalityTypesOptions    ( 	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes 	functionalityTypes,
												IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions 			functionalityoptions );

	void flagsAMFMHelp ( uint32_t flags );
	void flagsDABHelp  ( uint32_t flags );
	void flagsUNDEFHelp( uint32_t flags );

//private:
public:

#define STATION_TYPE(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::StationType::A }
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

#define SEEK_MODE(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::SeekMode::A }
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

#define SELECTION_MODE(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::SelectionMode::A }
	map<string, uint32_t> nameToSelectionMode = {
		SELECTION_MODE(SM_UNDEF),
		SELECTION_MODE(SM_DIRECT),
		SELECTION_MODE(SM_LIST),
		SELECTION_MODE(SM_PRESET)
	};
	map<uint32_t, string> selectionModeToName;

#define UPDATE_ELEMENT(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::UpdateElement::A }
	map<string, uint32_t> nameToUpdateElement = {
		UPDATE_ELEMENT(UE_SEEK),
		UPDATE_ELEMENT(UE_CURRENT_STATION),
		UPDATE_ELEMENT(UE_STATION_LIST)
	};
	map<uint32_t, string> updateElementToName;

#define SOURCE_TYPE(A) { #A, (uint32_t)IVIRadio::Types::Types::SourceType::A }
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

#define DEVICE_TYPE(A) { #A, (uint32_t)IVIRadio::Types::Types::DeviceType::A }
	map<string, uint32_t> nameToDeviceType = {
		DEVICE_TYPE(UNDEF_DEVICE),
		DEVICE_TYPE(AMFM),
		DEVICE_TYPE(DAB),
		DEVICE_TYPE(SDARS),
		DEVICE_TYPE(TV)
	};
	map<uint32_t, string> deviceTypeToName;

#define FEEDBACK(A) { #A, (uint32_t)IVIRadio::Types::Types::Feedback::A }
	map<string, uint32_t> nameToFeedback = {
		FEEDBACK(DONE),
		FEEDBACK(INTERRUPTED),
		FEEDBACK(NOT_APPLICABLE),
		FEEDBACK(ALREADY_SET),
		FEEDBACK(FAILURE),
		FEEDBACK(DELAYED)
	};
	map<uint32_t, string> feedbackToName;

#define UPDATE_TYPE(A) { #A, (uint32_t)IVIRadio::Types::Types::UpdateType::A }
	map<string, uint32_t> nameToUpdateType = {
		UPDATE_TYPE(UT_NONE),
		UPDATE_TYPE(UT_ONCE),
		UPDATE_TYPE(UT_NOTIFICATION)
	};
	map<uint32_t, string> updateTypeToName;

#define FLAGS_DEF_UNDEF(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::FlagsDefUndef::A }
	map<string, uint32_t> nameToFlagsDefUndef = {
		FLAGS_DEF_UNDEF(UNDEF_FLG_MUTED),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_ALARM),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_TRAFFIC),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_TRANSPORT),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_WARNING),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_NEWS),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_WEATHER),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_EVENT),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_SPECIAL_EVENT),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_PROGRAMM_INFO),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_SPORT),
		FLAGS_DEF_UNDEF(UNDEF_FLG_ANN_FINANCES),
		FLAGS_DEF_UNDEF(UNDEF_FLG_EPG),
		FLAGS_DEF_UNDEF(UNDEF_FLG_JLN),
		FLAGS_DEF_UNDEF(UNDEF_FLG_IMG_SLS_NPAD),
		FLAGS_DEF_UNDEF(UNDEF_FLG_IMG_SLS_XPAD),
		FLAGS_DEF_UNDEF(UNDEF_FLG_TMC),
		FLAGS_DEF_UNDEF(UNDEF_FLG_TPEG),
		FLAGS_DEF_UNDEF(UNDEF_FLG_BWS),
		FLAGS_DEF_UNDEF(UNDEF_FLG_MPEG2),
		FLAGS_DEF_UNDEF(UNDEF_FLG_AAC),
		FLAGS_DEF_UNDEF(UNDEF_FLG_IMG_CSLS),
		FLAGS_DEF_UNDEF(UNDEF_FLG_IMG_ALBUMCOVER),
		FLAGS_DEF_UNDEF(UNDEF_FLG_IMG_STATIONLOGO),
		FLAGS_DEF_UNDEF(UNDEF_FLG_SUBTITLE),
		FLAGS_DEF_UNDEF(UNDEF_FLG_TELETEXT)
	};
	map<uint32_t, string> flagsDefUndefToName;

#define FLAGS_DEF_AM_FM(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::FlagsDefAmFm::A }
	map<string, uint32_t> nameToFlagsDefAmFm = {
		FLAGS_DEF_AM_FM(AMFM_FLG_TP),
		FLAGS_DEF_AM_FM(AMFM_FLG_ANN_TA),
		FLAGS_DEF_AM_FM(AMFM_FLG_MS),
		FLAGS_DEF_AM_FM(AMFM_FLG_TMC),
		FLAGS_DEF_AM_FM(AMFM_FLG_HDDIGAUDIO),
		FLAGS_DEF_AM_FM(AMFM_FLG_HDENCRYPTED),
		FLAGS_DEF_AM_FM(AMFM_FLG_HDBALLGAME),
		FLAGS_DEF_AM_FM(AMFM_FLG_IMG_STATIONLOGO)

	};
	map<uint32_t, string> flagsDefAmFmToName;

#define FLAGS_DEF_DAB(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::FlagsDefDab::A }
	map<string, uint32_t> nameToFlagsDefDab = {
		FLAGS_DEF_DAB(DAB_FLG_LOCKED),
		FLAGS_DEF_DAB(DAB_FLG_VALID),
		FLAGS_DEF_DAB(DAB_FLG_MUTED),
		FLAGS_DEF_DAB(DAB_FLG_ENS_MUTED),
		FLAGS_DEF_DAB(DAB_FLG_ANN_ALARM),
		FLAGS_DEF_DAB(DAB_FLG_ANN_TRAFFIC),
		FLAGS_DEF_DAB(DAB_FLG_ANN_TRANSPORT),
		FLAGS_DEF_DAB(DAB_FLG_ANN_WARNING),
		FLAGS_DEF_DAB(DAB_FLG_ANN_NEWS),
		FLAGS_DEF_DAB(DAB_FLG_ANN_WEATHER),
		FLAGS_DEF_DAB(DAB_FLG_ANN_EVENT),
		FLAGS_DEF_DAB(DAB_FLG_ANN_SPECIAL_EVENT),
		FLAGS_DEF_DAB(DAB_FLG_ANN_PROGRAMM_INFO),
		FLAGS_DEF_DAB(DAB_FLG_ANN_SPORT),
		FLAGS_DEF_DAB(DAB_FLG_ANN_FINANCES),
		FLAGS_DEF_DAB(DAB_FLG_EPG),
		FLAGS_DEF_DAB(DAB_FLG_JLN),
		FLAGS_DEF_DAB(DAB_FLG_IMG_SLS_NPAD),
		FLAGS_DEF_DAB(DAB_FLG_IMG_SLS_XPAD),
		FLAGS_DEF_DAB(DAB_FLG_TMC),
		FLAGS_DEF_DAB(DAB_FLG_TPEG),
		FLAGS_DEF_DAB(DAB_FLG_BWS),
		FLAGS_DEF_DAB(DAB_FLG_MPEG2),
		FLAGS_DEF_DAB(DAB_FLG_AAC),
		FLAGS_DEF_DAB(DAB_FLG_IMG_CSLS),
		FLAGS_DEF_DAB(DAB_FLG_IMG_ALBUMCOVER),
		FLAGS_DEF_DAB(DAB_FLG_IMG_STATIONLOGO)
	};
	map<uint32_t, string> flagsDefDabToName;

#define QUALITY_INDEX_UNDEF(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::QualityIndexUndef::A }
	map<string, uint32_t> nameToQualityIndexUndef = {
		QUALITY_INDEX_UNDEF(UNDEF_QAL_AUDIO)
	};
	map<uint32_t, string> qualityIndexUndefToName;

#define QUALITY_INDEX_AMFM(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::A }
	map<string, uint32_t> nameToQualityIndexAmFm = {
		QUALITY_INDEX_AMFM(AMFM_QAL_FIELDSTRENGTH),
		QUALITY_INDEX_AMFM(AMFM_QAL_MULTIPATH),
		QUALITY_INDEX_AMFM(AMFM_QAL_DIGITAL)
	};
	map<uint32_t, string> qualityIndexAmFmToName;

#define QUALITY_INDEX_DAB(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::A }
	map<string, uint32_t> nameToQualityIndexDab = {
		QUALITY_INDEX_DAB(DAB_QAL_BER)
	};
	map<uint32_t, string> qualityIndexDabToName;

#define NAME_INDEX_DAB(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::A }
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

#define NAME_INDEX_AMFM(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::A }
	map<string, uint32_t> nameToNameIndexAmFm = {
		NAME_INDEX_AMFM(AMFM_NAM_PS),
		NAME_INDEX_AMFM(AMFM_NAM_HD),
		NAME_INDEX_AMFM(AMFM_NAM_RT)
	};
	map<uint32_t, string> nameIndexAmFmToName;

#define NAME_INDEX_UNDEF(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::NameIndexUndef::A }
	map<string, uint32_t> nameToNameIndexUndef = {
		NAME_INDEX_UNDEF(UNDEF_NAM_LONG),
		NAME_INDEX_UNDEF(UNDEF_NAM_SHORT),
		NAME_INDEX_UNDEF(UNDEF_NAM_DYNAMIC)
	};
	map<uint32_t, string> nameIndexUndefToName;

#define ID_INDEX_DAB(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::A }
	map<string, uint32_t> nameToIdIndexDab = {
		ID_INDEX_DAB(DAB_ID_KEY),
		ID_INDEX_DAB(DAB_ID_FREQUENCY),
		ID_INDEX_DAB(DAB_ID_ENSEMBLE),
		ID_INDEX_DAB(DAB_ID_SERVICE),
		ID_INDEX_DAB(DAB_ID_COMPONENT)
	};
	map<uint32_t, string> idIndexDabToName;

#define ID_INDEX_AMFM(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::A }
	map<string, uint32_t> nameToIdIndexAmFm = {
		ID_INDEX_AMFM(AMFM_ID_KEY),
		ID_INDEX_AMFM(AMFM_ID_FREQUENCY),
		ID_INDEX_AMFM(AMFM_ID_PI),
		ID_INDEX_AMFM(AMFM_ID_SERVICE)
	};
	map<uint32_t, string> idIndexAmFmToName;

#define ID_INDEX_UNDEF(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::A }
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

#define SEEK_RETURN_VALUE(A) { #A, (uint32_t)IVIRadio::Station::StationTypes::SeekReturnValue::A }
	map<string, uint32_t> nameToSeekReturnValue = {
		SEEK_RETURN_VALUE(SM_FREQUENCY),
		SEEK_RETURN_VALUE(SM_PERCENTAGE)
	};
	map<uint32_t, string> seekReturnValueToName;

#define ANNOUNCEMENT_TYPE(A) { #A, (uint32_t)IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType::A }
	map<string, uint32_t> nameToAnnouncementType = {
		ANNOUNCEMENT_TYPE(AT_ALARM),
		ANNOUNCEMENT_TYPE(AT_ROAD_TRAFFIC),
		ANNOUNCEMENT_TYPE(AT_TRANSPORT_FLASH),
		ANNOUNCEMENT_TYPE(AT_WARNING_SERVICE),
		ANNOUNCEMENT_TYPE(AT_NEWS),
		ANNOUNCEMENT_TYPE(AT_AREA_WEATHER),
		ANNOUNCEMENT_TYPE(AT_EVENT),
		ANNOUNCEMENT_TYPE(AT_SEPECIAL_EVENT),
		ANNOUNCEMENT_TYPE(AT_PROGRAM_INFORMATION),
		ANNOUNCEMENT_TYPE(AT_SPORT_REPORT),
		ANNOUNCEMENT_TYPE(AT_FINANCIAL_REPORT)
	};
	map<uint32_t, string> AnnouncementTypeToName;


#define ANNOUNCEMENT_STATE(A) { #A, (uint32_t)IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState::A }
	map<string, uint32_t> nameToAnnouncementState = {
		ANNOUNCEMENT_STATE(NotAvailable),
		ANNOUNCEMENT_STATE(Available),
		ANNOUNCEMENT_STATE(Active)
	};
	map<uint32_t, string> AnnouncementStateToName;


#define DATA_SERVICE(A) { #A, (uint32_t)IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::A }
	map<string, uint32_t> nameToComponentType = {
			DATA_SERVICE(DS_NO_SERVICE),
			DATA_SERVICE(DS_SUBTITLE),
			DATA_SERVICE(DS_TELETEXT),
			DATA_SERVICE(DS_IMAGE),
			DATA_SERVICE(DS_EPG),
			DATA_SERVICE(DS_TMC),
			DATA_SERVICE(DS_TPEG),
			DATA_SERVICE(DS_JOURNALINE),
			DATA_SERVICE(DS_ANNOUNCEMENT),
			DATA_SERVICE(DS_EWS)
	};
	map<uint32_t, string> ComponentTypeToName;


#define ACTIVATION(A) { #A, (uint32_t)IVIRadio::Types::Types::Activation::A }
	map<string, uint32_t> nameToActivation = {
		ACTIVATION(ACTIVE),
		ACTIVATION(INACTIVE)
	};
	map<uint32_t, string> ActivationToName;

//
//start with TunerConfigurationTypesEnum
//
#define AMMode(A) { #A, (uint32_t)IVIRadio::Configuration::ConfigurationTypesEnum::AMMode::A }
	map<string, uint32_t> nameToAMModi = {
		AMMode(AM_ONLY_MW),
		AMMode(AM_ONLY_LW),
		AMMode(AM_MWLW)
	};
	map<uint32_t, string> AMModiToName;

#define FollowingType(A) { #A, (uint32_t)IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::A }
	map<string, uint32_t> nameToFollowingModi = {
			FollowingType(FM_INTERNAL),
			FollowingType(FM_DAB),
			FollowingType(DAB_INTERNAL),
			FollowingType(DAB_FM),
			FollowingType(DVBT_INTERNAL),
			FollowingType(DVBT_DAB)
	};
	map<uint32_t, string> FollowingModiToName;

#define CountryVariant(A) { #A, (uint32_t)IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::A }
	map<string, uint32_t> nameToCountryVariants = {
			CountryVariant(CV_EUROPE),
			CountryVariant(CV_HONGKONG),
			CountryVariant(CV_KOREA),
			CountryVariant(CV_CHINA),
			CountryVariant(CV_USA),
			CountryVariant(CV_OZEANIEN),
			CountryVariant(CV_JAPAN),
			CountryVariant(CV_EUROPE_ROW),
			CountryVariant(CV_AUSTRALIA)
	};
	map<uint32_t, string> CountryVariantsToName;

#define FUNCTIONALITY_TYPE(A) { #A, (uint32_t)IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::A }
	map<string, uint32_t> nameToFunctionalityType = {
			FUNCTIONALITY_TYPE(HD),
			FUNCTIONALITY_TYPE(Following),
			FUNCTIONALITY_TYPE(ParentalLock),
			FUNCTIONALITY_TYPE(SmartFavorite),
			FUNCTIONALITY_TYPE(CIModule),
			FUNCTIONALITY_TYPE(AvailableBand),
			FUNCTIONALITY_TYPE(CountryVariant),
			FUNCTIONALITY_TYPE(CoverageArea),
			FUNCTIONALITY_TYPE(InterfaceVersion),
			FUNCTIONALITY_TYPE(AMModi),
			FUNCTIONALITY_TYPE(Regionalisation),
			FUNCTIONALITY_TYPE(RDS),
			FUNCTIONALITY_TYPE(RT),
			FUNCTIONALITY_TYPE(DLS)
	};
	map<uint32_t, string> FunctionalityTypeToName;

#define DATA_FORMAT(A) { #A, (uint32_t)IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat::A }
	map<string, uint32_t> nameToDataFormat = {
			DATA_FORMAT(DF_XML),
			DATA_FORMAT(DF_HTML),
			DATA_FORMAT(DF_PICTURE),
			DATA_FORMAT(DF_RAW)
	};
	map<uint32_t, string> DataFormatToName;

#define DATA_TYPE(A) { #A, (uint32_t)IVIRadio::AdditionalService::AdditionalServiceTypes::DataType::A }
	map<string, uint32_t> nameToDataType = {
			DATA_TYPE(DT_STRING),
			DATA_TYPE(DT_STREAM),
			DATA_TYPE(DT_BYTEBUFFER)
	};
	map<uint32_t, string> DataTypeToName;



protected:
	static TerminalIO* _instance;

	TerminalIO();

};
#endif // !defined(EA_839E62CA_EE73_4dae_B295_1A13DF9512E2__INCLUDED_)


