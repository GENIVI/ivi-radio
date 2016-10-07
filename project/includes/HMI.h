///////////////////////////////////////////////////////////
//  HMI.h
//  Implementation of the Class HMI
//  Created on:      16-Jul-2013 16:47:52
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_BFD75FEB_0A4B_4619_9FB5_D29330139FAE__INCLUDED_)
#define EA_BFD75FEB_0A4B_4619_9FB5_D29330139FAE__INCLUDED_

#include "TerminalIO.h"
#include "Dataservices/Announcement.h"
#include "Dataservices/Dataservices.h"
#include "IVIRadio/Configuration/ConfigurationTypesEnum.h"
#include "IVIRadio/Configuration/ConfigurationOptions.h"
#include "IVIRadio/Configuration/ConfigurationOptionsGetter.h"
#include "Configuration/Configuration.h"

/*
 * \struct data_request_parameter
 * \brief structure holds the information of one data request the client has notified on
 * \param serviceOptions DataServiceOption this parameter is an union an can hold the options belonging to a data service
 * \param updateType describes the UpdateType the for the request; UT_NOTIFICATION means subscription on changes in the dataset;
 * 			UT_NONE means cancel an existing subscription; UT_ONCE means the dataset is request just one time
 * \param objectID is an uint32_t and describes an ID that can be interpreted different for each dataservice (Journaline: ID = ObjectID of Journaline Obejct;
 * 	Teletext: ID = Page Number of Teletext page; ...)
 * \param dataFormat describes if the data is transmitted  XML, HTML, PICTURE or RAW
 * \param dataType describes the type of transmitted data (STRING, BYTEBUFFER, PIPE)
 * \param stationSelectors is a vector of StationSelectors to that the request belongs
 * \param componentType is the type of data service the request belongs to
 */
struct data_request_parameter {
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption serviceOptions;
	IVIRadio::Types::Types::UpdateType 	updateType;
	uint32_t 							objectID;
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat 	dataFormat;
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataType   	dataType;
	IVIRadio::Types::Types::StationSelectors 							stationSelectors;
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataService 	componentType;
};

/** \class HMI
 * \brief the HMI class administrates all parameter that could be set using the tuner api. since the system shall be multiuser able
 * the middleware creates for client which registers one hmi which administrates the parameter independent from other clients
 * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2014/01/10 14:16:20
 *
 * Contact: bernhard.singer@partner.bmw.de
 *
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

class HMI : public Announcement, public Configuration
{

public:
	/**
	 * \brief default constructor; creates all objects of all dataservices and configuration options
	 * \param [in] hmiId an int is the identificator of an HMI object
	 */
	HMI(int hmiId);

	/**
	 * \brief default destructor
	 */
	virtual ~HMI();

	/**
	 * \brief returns identificator of the HMI
	 * \return returns HMI Id
	 */
    int getHMIId() { return m_hmiId; }

    //method for station handling
    /**
    * \brief method sets the AMFM station list the Middleware has found during the last background scan for this HMI
    * \param vec an vector<Station> List of AMFM station to be set for the HMI
    */
    void setCompleteListAMFM (const vector<IVIRadio::Station::StationTypes::Station>& vec) { m_completeListAMFM = vec; }

    /**
    * \brief method sets the AMFM station list the Middleware has found during the last background scan
    * \param vec an vector<Station> List of DAB station to be set for the HMI
    */
    void setCompleteListDAB  (const vector<IVIRadio::Station::StationTypes::Station>& vec) { m_completeListDAB = vec; }

    /**
    * \brief method sets the undef station list the Middleware combined from the AMFM and DAB list
    * \param vec an vector<Station> List of undef stations to be set for the HMI
    */
    void setCompleteListUndef(const vector<IVIRadio::Station::StationTypes::Station>& vec) { m_completeListUndef = vec; }

   /**
   * \brief returns the AMFM seek notification status (can be set by calling the API method: controlUpdate (UE_SEEK, UT_NOTIFICATION, AMFM_FM, ST_UNDEF) )
   * \return true if AMFM Seek notification is true else returns false
   */
   bool getUpdateSeekNotificationAMFM() { return m_updateSeekNotificationAMFM; }

    /**
    * \brief returns the DAB seek notification status (can be set by calling the API method: controlUpdate (UE_SEEK, UT_NOTIFICATION, DAB_DAB, ST_UNDEF) )
    * \return true if AMFM Seek notification is true else returns false
    */
    bool getUpdateSeekNotificationDAB() { return m_updateSeekNotificationDAB; }

    /**
    * \brief returns the AMFM stationlist notification status (can be set by calling the API method: controlUpdate (UE_STATIONLIST, UT_NOTIFICATION, AMFM_FM, ST_UNDEF) )
    * \return true if AMFM station list notification is true else returns false
    */
    bool getUpdateStationListNotificationAMFM() { return m_updateStationListNotificationAMFM; }

    /**
    * \brief returns the DAB stationlist notification status (can be set by calling the API method: controlUpdate (UE_STATIONLIST, UT_NOTIFICATION, DAB_DAB, ST_UNDEF) )
    * \return true if DAB station list notification is true else returns false
    */
    bool getUpdateStationListNotificationDAB() {     return m_updateStationListNotificationDAB; }

    /**
    * \brief returns the undef stationlist notification status (can be set by calling the API method: controlUpdate (UE_STATIONLIST, UT_NOTIFICATION, UNDEF, ST_UNDEF) )
    * \return true if AMFM station list notification is true else returns false
    */
    bool getUpdateStationListNotificationUndef() {     return m_updateStationListNotificationUndef; }

    /**
    * \brief set AMFM seek notification status
    * \param val a bool value the seek AMFM notification status is set to
    */
    void setUpdateSeekNotificationAMFM( bool val );

    /**
    * \brief set DAB seek notification status
    * \param val a bool value the DAB seek notification status is set to
    */
    void setUpdateSeekNotificationDAB( bool val );

    /**
    * \brief set AMFM station list notification status
    * \param val a bool value the AMFM station list notification status is set to
    */
    void setUpdateStationListNotificationAMFM( bool val );

    /**
    * \brief set DAB station list notification status
    * \param val a bool value the DAB station list notification status is set to
    */
    void setUpdateStationListNotificationDAB( bool val );

    /**
    * \brief set UNDEF station list notification status
    * \param val a bool value the UNDEF station list notification status is set to
    */
    void setUpdateStationListNotificationUndef( bool val );

    /**
     * \brief method set the currently tuned station of the hmi
     * \param currentStation a Station the station the currently tuned station should be set to
     */
    void setCurrentTunedStation( IVIRadio::Station::StationTypes::Station currentStation );

    /**
     * \brief method returns the currently tuned station
     * \return Station that is currently tuned
     */
    IVIRadio::Station::StationTypes::Station getCurrentTunedStation() { return m_currentStation; }

    /**
     * \brief returns if the hmi has currently tuned to a station
     * \return true if hmi has currently to a station and false if not
     */
    bool hasCurrentStation () { return bHasCurrentStation; }

    /**
     * \brief returns the AMFM station list that was ultimately assigned to the hmi
     * \return AMFM station list
     */
    vector<IVIRadio::Station::StationTypes::Station> getCompleteListAMFM() 	{ return m_completeListAMFM;  }

    /**
     * \brief returns the DAB station list that was ultimately assigned to the hmi
     * \return DAB station list
     */
    vector<IVIRadio::Station::StationTypes::Station> getCompleteListDAB() 	{ return m_completeListDAB;   }

    /**
     * \brief returns the undef station list that was ultimately assigned to the hmi
     * \return undef station list
     */
    vector<IVIRadio::Station::StationTypes::Station> getCompleteListUndef() { return m_completeListUndef; }

	/**
	 * \brief method searches for station matching the service Identifier (SID / PI)
	 * method searches for the station the given service ID belongs to; there is no logic if more than one stations
	 * with the same service ID of maybe different standards are found. the method returns the first one it finds and it starts
	 * with searching in the amfm station list. the method return true if one station is found. the station itself will be returned
	 * in the reference parameter oStation. if no station is found the method returns false and the reference oStation will not be filled
	 * \param [in] serviceID an uint32_t is the Service ID (DAB) or program Identifier (AMFM) the station is searched for
	 * \param [out] oStation a reference to a Station ; if a matching station is found the parameter contains that station
	 * \return returns true if a station was found and false if not
	 */
	bool getStationToServiceIdentifier( uint32_t serviceID, IVIRadio::Station::StationTypes::Station &oStation);

	bool getCurrStationChanged(){ return m_SendCurrStation; }

	void setCurrStation (bool val){ m_SendCurrStation = val; }

	bool addDataRequest	 	( data_request_parameter request );

	bool removeDataRequest 	( data_request_parameter request );

	vector < data_request_parameter > getRequests( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService componentType );

private:

	vector < data_request_parameter > m_requests;

	TerminalIO 	*m_TerminalIO;

	/**
	* \brief instance of Dataservices to administrate EPG settings, configuration
	*/
	Dataservices	*m_EPG;

	/**
	* \brief instance of Dataservices to administrate Journaline settings, configuration
	*/
	Dataservices	*m_Journaline;

	/**
	* \brief instance of Dataservices to administrate Subtitle settings, configuration
	*/
	Dataservices	*m_Subtitle;

	/**
	* \brief identification number of a HMI
	*/
    int  m_hmiId;

	/**
	* \brief indicates if seek notification amfm is activated or not
	*/
    bool m_updateSeekNotificationAMFM;

	/**
	* \brief indicates if seek notification dab is activated or not
	*/
    bool m_updateSeekNotificationDAB;

	/**
	* \brief indicates if station list notification amfm is activated or not
	*/
    bool m_updateStationListNotificationAMFM;

	/**
	* \brief indicates if station list notification dab is activated or not
	*/
    bool m_updateStationListNotificationDAB;

	/**
	* \brief indicates if station list notification undef is activated or not
	*/
    bool m_updateStationListNotificationUndef;

    /*
	* \brief vector carries the amfm station list from the very last controlUpdate call
	*/
	vector<IVIRadio::Station::StationTypes::Station> m_completeListAMFM;

	/**
	* \brief vector carries the dab station list from the very last controlUpdate call
	*/
	vector<IVIRadio::Station::StationTypes::Station> m_completeListDAB;

	/**
	* \brief vector carries the undef station list from the very last controlUpdate call
	*/
	vector<IVIRadio::Station::StationTypes::Station> m_completeListUndef;


    bool m_SendCurrStation;

	/**
	* \brief parameter stores the currently tuned station
	*/
    IVIRadio::Station::StationTypes::Station m_currentStation;

	/**
	* \brief parameter indicates that the hmi has a currently active station
	*/
    bool bHasCurrentStation;

};
#endif // !defined(EA_BFD75FEB_0A4B_4619_9FB5_D29330139FAE__INCLUDED_)















