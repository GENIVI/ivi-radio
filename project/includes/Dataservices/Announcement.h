///////////////////////////////////////////////////////////
//  Announcement.h
//  Implementation of the Class Announcement
//  Created on:      30-Jul-2013 16:25:52
//  Original author: QX92858
///////////////////////////////////////////////////////////

#if !defined(EA_89BDFA4E_1E19_46d4_819F_BBE64D612DB2__INCLUDED_)
#define EA_89BDFA4E_1E19_46d4_819F_BBE64D612DB2__INCLUDED_

#include <map>
#include "../TerminalIO.h"
#include "IVIRadio/Types/Types.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypes.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypes.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypesOptions.h"

using namespace std;

/**
 * \class Announcement -
 *
 * \brief class cares about Announcement handling for a client
 *
 *	every from the Middleware administrated HMI needs an instance of the Announcement class for handling Announcements.\n
 *	the class stores the complete Announcement configuration and saves active Announcements in a dynamic vector\n
 *	using getter and setter it is possible for the HMI to change/request Annoucnement configuration and active Annoucnements
 *
 * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2013/11/14 14:16:20
 *
 * Contact: bernhard.singer@partner.bmw.de
 *
 *  * Copyright
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
 */
class Announcement
{

public:

	/**
	 * \brief default constructor
	 */
	Announcement();

	/**
	 * \brief default constructor
	 */
	virtual ~Announcement();

    /**
    * \brief set the announcement handling for the HMI
    * \param state an Activation type, decides if announcement are activated or deactivated
    */
	//void setAnnouncementHandling(TunerTypes::TunerTypes::Activation state);
	void setAnnouncementHandling( IVIRadio::Types::Types::Activation state );

    /**
    * \brief get the announcement handling for the HMI
    * \returns if announcement is activated or deactivated
    */
	IVIRadio::Types::Types::Activation getAnnouncementHandling();

    /**
    * \brief method sets the configuration of one announcement type
    * \param [in] announcementType announcement type that should be configured
    * \param [in] active an Activation decides if announcement type should be activated
    * \param [in] priority an uint32_t priority of the announcement type
    */
	void setAnnouncementConfiguration(IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType type, IVIRadio::Types::Types::Activation enabled, uint32_t priority,
			IVIRadio::Types::Types::StationSelector stationSelector, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState annState);

	/**
    * \brief returns if the given Announcement Type is enabled
    * \param [in] announcementType announcement type of that the activation is required
    * \return true if announcement type is enabled and false if not
    */
	IVIRadio::Types::Types::Activation getAnnouncementConfigurationEnabled( IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType );

	/**
    * \brief returns if the given Announcement Type is enabled
    * \param [in] announcementType announcement type of that the activation is required
    * \return true if announcement type is enabled and false if not
    */
	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations  getAnnouncementConfiguration();

	/**
	 * \brief method adds an active announcement to the list of active announcements
	 * \param componentID an uint32_t unique identifier of the component
	 * \param announcementType an AnnouncementType type of the announcement that should be added as active
	 * \return true if announcement was added successfully and false if already in list
	 */
	bool addActiveAnnouncement( IVIRadio::Types::Types::StationSelector stationSelector, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType announcementType);
	/**
	 * \brief method deletes an active announcement from the list of active announcements
	 * \param componentID an uint32_t unique identifier of the component
	 * \param announcementType an AnnouncementType type of the announcement that should be deleted from the list of active announcements
	 * \return true if active announcement with componentID has been deleted successfully from the list and false if announcement was not in the list
	 */
	bool deleteActiveAnnouncement( IVIRadio::Types::Types::StationSelector stationSelector );

	/**
	 * \brief method checks if announcement with componentID is in list of active announcements
	 * \param componenntID an uint32_t unique system wide identifier of the component
	 * \return true if announcement is in list of active announcements and false if not
	 */
	bool isActiveAnnouncement( IVIRadio::Types::Types::StationSelector stationSelector );

	/**
	 * \brief method returns map of active announcements
	 * \return map containing all active announcements
	 */
	map< uint32_t, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType > getActiveAnnouncements();

	bool getAnnouncementStates( IVIRadio::Types::Types::StationSelectors stationSelectors , IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options annConf,
			IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates &arrAnnStates);

	bool changeAnnouncementType(IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState annState, IVIRadio::Types::Types::StationSelector stationSelector, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType annType );

private:

	/**
	 * \class AnnouncementConfig
	 * \brief class administrates the configuration of one announcement type
	 */
	class AnnouncementConfig {
		public:
		 	 /**
		 	  * \brief describes if the announcement type is active or not
		 	  */
			IVIRadio::Types::Types::Activation active;
			/**
			 * \brief contains the priority of the announcement type
			 */
			uint32_t priority;

			IVIRadio::Types::Types::StationSelector stationSelector;

			IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType type;

			IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState annState;

	};

	TerminalIO *m_terminalIO;

	/**
	 * \brief information if announcement is basically activated or not
	 */
	IVIRadio::Types::Types::Activation m_announcementEnabled;

	/**
	 * \brief map contains key value pairs; every announcement type can be a key and the configuration the matching value
	 */
	map < IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType,  AnnouncementConfig> 	m_announcementType;

	/**
	 * \brief map contains key value pairs; a component ID can be matched to a announcement type
	 */
	map < uint32_t, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType> m_activeAnnouncements;

	vector <AnnouncementConfig> m_vAnnouncementConfig;

};
#endif // !defined(EA_89BDFA4E_1E19_46d4_819F_BBE64D612DB2__INCLUDED_)
