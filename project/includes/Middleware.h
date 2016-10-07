///////////////////////////////////////////////////////////
//  Middleware.h
//  Implementation of the Class Middleware
//  Created on:      16-Jul-2013 16:47:49
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_1684FDE8_EDD0_46a8_B6BA_EF4FA7026778__INCLUDED_)
#define EA_1684FDE8_EDD0_46a8_B6BA_EF4FA7026778__INCLUDED_

#include <stdio.h>
#include <memory>
#include <iostream>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <CommonAPI/Runtime.h>

#include "TunerList.h"
#include "HMIList.h"
#include "TerminalIO.h"
#include "FileIO.h"
#include "Seek.h"
#include "StartTune.h"
#include "StationManagement.h"
#include "Dataservices/XMLReader.h"
//#include "Player.h"
#include <csignal>

/**
* \class Middleware
 *
 * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2013/11/14 14:16:20
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
 *
 *
 */

struct currAnnouncementData {
	uint32_t handle;
	IVIRadio::Types::Types::StationSelectors 										stationSelectors;
	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations annConfigs;
	IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates 	arrAnnStates;
};

class Middleware
{

public:
	/**
	 * \brief default constructor
	 * creation of necessary instances and all tuner and hmis
	 */
	Middleware();
	/**
	 * \brief default destructor
	 */
	virtual ~Middleware();

	/**
	 * \brief enable the application to receive user input from terminal
	 */
	int setupSignalHandling();

	/**
	 * \brief starts a thread that runs a endless loop that waits for user input from console
	 */
	void runLoop();

	/**
	 * \brief prints a list o all currently active announcements of all hmis
	 */
	void printActiveAnnouncements( int signum );

	/**
	 * \brief sends an announcement broadcast
	 * method send an announcement broadcast containing the state of an announcement when the state has changed\n
	 * constraint is that the client has registered to the announcement of which the state has changed
	 */
	void sendAnnouncement();

	/**
	 * \brief method sends an announcementFinished broadcast if given componentID is valid and if desired announcement is currently active
	 */
	void sendAnnouncementFinished();

	/*
	 * \brief the middleware is called to execute a seek when the interface function Seek was called.
	 * therefore the middleware catches an idle tuner from the tuner list and a hmi (right now I have not
	 * thought about using more than one HMIs so the hmi id is always zero)
	 * to execute the seek an instance of the class Seek is created which cares about simulating a background seek
	 * the middleware class writes data from the seek progress and station information to members that could be polled
	 * from the Stub to send events to the clients
	 */
	IVIRadio::Types::Types::ErrorCodes seek(IVIRadio::Types::Types::DeviceType device,
			IVIRadio::Station::StationTypes::SeekMode seekMode, uint32_t handle,
			IVIRadio::Station::StationTypes::StationList &oStationList);

	IVIRadio::Types::Types::Feedback startTune(IVIRadio::Types::Types::StationSelector station,
			IVIRadio::Station::StationTypes::SelectionMode selectionMode, uint32_t handle);

	/*
	 * \brief hmi can notify on seek results and denotify on them; for that only a variable in the HMI instance is set
	 * \param updateType can be UT_NOTIFY to notify on a special value or UT_NONE to denotify
	 * \param sourceType is an uitn32_t source type of the information which want to be notified on
	 * \param handle is an uint32_t, is the handle of the hmi for which a notification should be set or cancelled
	 */
	void NotifyOnSeek( IVIRadio::Types::Types::UpdateType updateType, uint32_t sourceType, uint32_t handle );

	IVIRadio::Station::StationTypes::StationList GetStationList( IVIRadio::Station::StationTypes::UpdateElement updateElement,
		       IVIRadio::Types::Types::UpdateType    updateType, uint32_t sourceType, uint32_t stationType, uint32_t handle);

	void setListNotification ( IVIRadio::Types::Types::UpdateType updateType, uint32_t sourceType, uint32_t handle);

	IVIRadio::Types::Types::ErrorCodes getCurrentStationOfHMI( uint32_t handle, IVIRadio::Station::StationTypes::Station &oStation );

	IVIRadio::Station::StationTypes::SeekData getSeekData () { return m_broadcastSeekData; }

	/*
	 * \brief search in the Tuner Lists to get the tuner that is assigned to the HMI.
	 * Only one tuner can be assigned to a HMI at one time
	 * returns the assigned tuner; if no tuner is assigned returns NULL
	 * \param handle is an uint32_t handle of the hmi
	 * \return returns the tuner which is currently assigned to the hmi or NULL if no tuner is assigned
	 */
	Tuner* getTunerAssignedToHMI( uint32_t handle );

	bool getSeekNotification( uint32_t handle, IVIRadio::Types::Types::DeviceType deviceType );
	bool getListNotification( uint32_t handle, IVIRadio::Types::Types::DeviceType deviceType );

	/*
	 * methods for additional services
	 */
	bool getStationSelectorFromID ( uint32_t stationID, uint32_t handle, IVIRadio::Types::Types::StationSelector &station );

	IVIRadio::Types::Types::ErrorCodes getData(
			IVIRadio::AdditionalService::AdditionalServiceTypes::DataService componentType,
			IVIRadio::Types::Types::StationSelectors stationSelectors,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedServiceOption,
			uint32_t handle,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption component_parameter,
			IVIRadio::AdditionalService::AdditionalServiceTypes::Data &data);

	IVIRadio::Types::Types::ErrorCodes abort(
			IVIRadio::AdditionalService::AdditionalServiceTypes::DataService componentType,
			IVIRadio::Types::Types::StationSelectors stationSelectors,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedServiceOption,
			uint32_t handle,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption component_parameter,
			IVIRadio::AdditionalService::AdditionalServiceTypes::Announcement &announcement
			);



	/*
	 *  methods for configuration
	 */
	IVIRadio::Types::Types::ErrorCodes changeFunctionalityConfiguration( uint32_t handle, IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
				IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions functionalityOptions);

	IVIRadio::Types::Types::ErrorCodes requestFunctionalityConfiguration( uint32_t handle, IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
				IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityOptions,
				IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions& outFunctionalityOptions);
	/*
	 * methods to send announcement over the Individual Stub
	 */
	inline void setSendAnnouncement( bool val) { m_bSendAnnouncement = val ; }
	inline bool getSendAnnouncement()          { return m_bSendAnnouncement; }

	inline void setFinishAnnouncement( bool val) { m_bFinishAnnouncement = val ; }
	inline bool getFinishAnnouncement()          { return m_bFinishAnnouncement; }

	void getCurrentAnnouncementData(uint32_t &handle,
			IVIRadio::Types::Types::StationSelectors 										&stationSelectors,
			IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations &annConfigs,
			IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates 	&arrAnnStates);

	void setCurrentAnnouncementData(uint32_t handle,
			IVIRadio::Types::Types::StationSelectors 										stationSelectors,
			IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations annConfigs,
			IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates 	arrAnnStates);

	//thread keeps whole middleware alive until sigterm received
	//thread provides terminal input from user
	static void * InternalThreadEntryFunc_Interactive(void * This) {
		((Middleware *)This)->InternalThreadEntry_Interactive(); return NULL;
	}
	void InternalThreadEntry_Interactive  ();

	static void * InternalThreadEntryFunc_HandlePipeCommunication(void * This) {
			((Middleware *)This)->InternalThreadEntry_HandlePipeCommunication(); return NULL;
	}

	void InternalThreadEntry_HandlePipeCommunication  ();

	void makePermanent(IVIRadio::Types::Types::StationSelector station, bool permanent, uint32_t handle);

	IVIRadio::Types::Types::ErrorCodes getComponentNotifications ( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService componentType,
			IVIRadio::Types::Types::arrayStationSelectors 										&arrayStationSel,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOptions 	&unifiedServiceOptions,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOptions 		&componentOptions, uint32_t handle );

	/**
	 * @brief function sends a following event to the client.
	 * constraints for sending the event:
	 * - client must have tuned to a station from a list
	 * - there need to be a alternative station available in the station list
	 * - current station and alternative station needs to fit to the following type (e.g. following type FM_INTERNAL: current station and alternative station are FM stations)
	 * action if all constraints are fullfilled
	 * - middleware tunes to alternative station
	 * - if alternative station has different device type type middleware releases current assigned tuner and assignes new tuner of required device type
	 * - sending following event to any client which is qualified to receive one
	 * - sending currentStation event to the client that received a following event
	 *
	 */
	void sendFollowingEvent();

	bool getCurrStation( vector<uint32_t>& handle, vector<IVIRadio::Station::StationTypes::Station>& station);
private:
	TunerList 			*m_TunerList;
	HMIList 			*m_HMIList;
	TerminalIO 			*m_TerminalIO;
	FileIO 				*m_FileIO;
	StationManagement 	*m_StationManagement;
	XMLReader			*m_XMLReader;
	//Player				*m_Player;

	currAnnouncementData *m_currAnnData;

	IVIRadio::Station::StationTypes::SeekData    						m_broadcastSeekData;

	bool m_bSendAnnouncement;
	bool m_bFinishAnnouncement;
	bool m_runPipe;

	IVIRadio::Station::StationTypes::Stations m_CompleteAMFMList;
	IVIRadio::Station::StationTypes::Stations m_CompleteDABList;

	pthread_t interactive;
	pthread_t pipeHandling;

};
#endif // !defined(EA_1684FDE8_EDD0_46a8_B6BA_EF4FA7026778__INCLUDED_)
