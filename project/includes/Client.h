///////////////////////////////////////////////////////////
//  Client.h
//  Implementation of the Class Client
//  Created on:      17-Jul-2013 10:08:33
//  Original author: qx92858
///////////////////////////////////////////////////////////


#if !defined(EA_6DC8A062_292B_4a30_91A1_B934F82EBE47__INCLUDED_)
#define EA_6DC8A062_292B_4a30_91A1_B934F82EBE47__INCLUDED_

#include <iostream>
#include <map>
#include <pthread.h>
#include <sys/stat.h> //need that lib for fifo pipe
#include <fcntl.h> //need that lib to open a file

#include "IVIRadio/Station/StationProxy.h"
#include "IVIRadio/Types/Types.h"
#include "IVIRadio/AdditionalService/AdditionalServiceProxy.h"
#include "IVIRadio/Configuration/ConfigurationProxy.h"
#include <CommonAPI/Runtime.h>
#include "TerminalIO.h"

/** \class Client
 * \brief This module represents a simulated HMI client
 * This module represents a simulated HMI client and can be invoked
 * multiple times in parallel with different id number starting from 0.
 * The maximum number of supported clients depends on the Tuner middleware.
 *
 * After setting up the environment it will present a menu to the user
 * to choose from the methods of the interface defined in Franca or to
 * exit the program gracefully.
 *
 * If an interface method has been chosen, its parameter are queried
 * from the user interactively by selecting possible values from a list.
 * It is thus not possible to enter values out of range for a parameter,
 * however it is still possible to enter combinations that make no sense
 * and will thus be refused by the Tuner middleware (Middleware).
 *
 * In some situations the selection of parameters will be aborted when
 * certain conditions are not met, e.g. user selects to choose from a
 * list of known stations, but this list is empty.
 *
 * The aforementioned station lists are the only data which is stored
 * as a kind of state info within the client. They must be retrieved
 * using controlUpdate in stationlist mode before startTune can use
 * them.
 *
 * Each method of the Franca interface is represented by its own function
 * of the same name, additionally for all broadcasts of the interface,
 * a callback function is registered with the underlying CommonAPI
 * framework on startup.
 *
 * All API parameters used for calling an interface, or those which
 * are received within an asynchonous broadcast or as result of an interface
 * call are printed on the console immediately before performing the call
 * or after reception, respectively.
 *
 * \author Guido Ostkamp
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

class Client
{

public:

	/**
	* \brief default destructor
	*/
	virtual ~Client();

	/**
	* \brief returns an instance of the object which is only once available in the system (singleton pattern)
	*/
	static Client* getInstance( int id );

	/**
	 * \brief methdo generates a loop that waits for user input from console
	 */
	void loop();

	/**
	* \brief method prepares necessary parameters for a selectComponent and starts the selectComponent call using the interface proxy
	* \param [in] proxy a TunerAdditionalServiceProxy; this proxy provides the interface functions of the Additional Services component
	*/
	void requestDataService(std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy);

	/**
	* \brief method prepares necessary parameters for a requestComponentOptions and starts the requestComponentOptions call using the interface proxy
	* \param [in] proxy a TunerAdditionalServiceProxy; this proxy provides the interface functions of the Additional Services component
	*/
	void requestComponentOptions(std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy);

	/**
	* \brief user can request the notifications for a specific dataservice
	* \param [in] proxy a TunerAdditionalServiceProxy; this proxy provides the interface functions of the Additional Services component
	*/
	void requestSubscribedServiceOptions(std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy);

	/**
	* \brief user can abort the transmission of data for a specific dataservice (intended specially for announcement)
	* \param [in] proxy a TunerAdditionalServiceProxy; this proxy provides the interface functions of the Additional Services component
	*/
	void abort(std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy);

	/**
	* \brief method prepares necessary parameters for a requestComponentTypeConfiguration and starts the requestComponentTypeConfiguration call using the interface proxy
	* \param [in] proxy a TunerAdditionalServiceProxy; this proxy provides the interface functions of the Additional Services component
	*/
	void requestComponentTypeConfiguration(std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy);

	/**
	* \brief method prepares necessary parameters for a changeComponentTypeConfiguration and starts the changeComponentTypeConfiguration call using the interface proxy
	* \param [in] proxy a TunerAdditionalServiceProxy; this proxy provides the interface functions of the Additional Services component
	*/
	void changeComponentTypeConfiguration(std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy);

	/**
	* \brief the merge a new DAB list to an existing one
	* double entries are ignored. double entries can be found by comparing the SID / PI Information provided by every station
	* only DAB and AMFM lists are handled
	* \param [in] changes a reference to a station list that should be merged to an existing one
	*/
	void mergeLists( const IVIRadio::Station::StationTypes::StationList& changes );

	/**
	* \brief method prepares necessary parameters for a abortTune and starts the abortTune call using the interface proxy
	* \param [in] proxy a TunerStationProxy; this proxy provides the interface functions of the Tuner Management component
	*/
	void abortTune( std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy );

	/**
	* \brief method prepares necessary parameters for a startTuner and starts the startTune call using the interface proxy
	* \param [in] proxy a TunerStationProxy; this proxy provides the interface functions of the Tuner Management component
	*/
	void startTune( std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy );

	/**
	* \brief method prepares necessary parameters for a seek and starts the seek call using the interface proxy
	* \param [in] proxy a TunerStationProxy; this proxy provides the interface functions of the Tuner Management component
	*/
	void seek( std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy );

	/**
	* \brief method prepares necessary parameters for a makePermanent and starts the makePermanent call using the interface proxy
	* \param [in] proxy a TunerStationProxy; this proxy provides the interface functions of the Tuner Management component
	*/
	void makePermanent( std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy );

	/**
	* \brief method prepares necessary parameters for a controlUpdate and starts the controlUpdate call using the interface proxy
	* \param [in] proxy a TunerStationProxy; this proxy provides the interface functions of the Tuner Management component
	*/
	void controlUpdate( std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy );

	/**
	 * \brief change configuration of a basic functionality like following or conditional access
	 * \param [in] proxy a ConfigurationProxy; this proxy provides the interface functions set and get configurations
	 */
	void changeFunctionalityConfiguration ( std::shared_ptr<IVIRadio::Configuration::ConfigurationProxy<> >&proxy );

	/**
	 * \brief request configuration of a basic functionality like following or conditional access
	 * \param [in] proxy a ConfigurationProxy; this proxy provides the interface functions set and get configurations
	 */
	void requestFunctionalityConfiguration ( std::shared_ptr<IVIRadio::Configuration::ConfigurationProxy<> >&proxy );

	/**
	 * \brief method prints the feedback information of the current methodcall to the console
	 *  \param [in] handle_out an uint32_t handle to identify the origin of the callback
	 *  \param [in] callStatus a CallStatus; information if there was a bus error
	 *  \param [in] feedback a Feedback; information if the call was accepted or if it produced an error
	 *  \param [in] method a string information which functio was called
	 *  \return returns true if a matching station was found and false if not
	 */
	void ConOutReturnFromMiddleware(uint32_t handle_out, CommonAPI::CallStatus callStatus, IVIRadio::Types::Types::Feedback feedback, string method);

	/**
	 * \brief method is the callback of a seek
	 *  \param [in] seekData is a SeekData; contains the progress information of a ssek progress (data is dependent on middleware implementation)
	 *  \param [in] handle a uint32_t; handle to identify the callback
	 *  \param [in] errorCode a ErrorCode; process execution state
	 *  \return returns true (do not care)
	 */
	bool SeekCallbackClient				( IVIRadio::Station::StationTypes::SeekData	seekData, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode );

	/**
	 *  \brief method is the callback of a controlUpdate call with UpdateElement == UE_LIST
	 *  \param [in] list is a StationList; contains the requested list
	 *  \param [in] handle a uint32_t; handle to identify the callback
	 *  \param [in] errorCode a ErrorCode; process execution state
	 *  \return returns true (do not care)
	 */
	bool StationListCallbackClient		( IVIRadio::Station::StationTypes::StationList list	, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode );

	/**
	 *  \brief method is the callback of a controlUpdate call with UpdateElement == UE_CURRENTSTATION
	 *  \param [in] current is a Station; contains the current station if a station is active
	 *  \param [in] handle a uint32_t; handle to identify the callback
	 *  \param [in] errorCode a ErrorCode; process execution state
	 *  \return returns true (do not care)
	 */
	bool CurrentStationCallbackClient	( IVIRadio::Station::StationTypes::Station current	, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode );

	/**
	 *  \brief method is a callback which is invoked when an announcement gets active and the client has set the nesserary configuratuions
	 	\param [in] stationSelectors an array of StationSelector; configuratios of the announcement configured in the request
	 *  \param [in] announcementConfigurations is an array of AnnouncementConfiguration; configuratios of the announcement configured in the request
	 *  \param [in] announcementStates an array of arrayAnnouncementState; states of the announcement configured in that request
	 *  \param [out] handleOut an uint32_t; handle to identify the correct destination of a announcement broadcast
	 *  \param [out] errorCode an ErrorCodes; execution state of the job. if successful finished EC_OK
	 *  \return returns true (do not care)
	 */
	bool AnnouncementEventCallbackClient( 		IVIRadio::Types::Types::StationSelectors stationSelectors,
			IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations announcementConfigurations,
			IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates announcementStates,
			const uint32_t& handle, IVIRadio::Types::Types::ErrorCodes errorCode  );

	/**
	 * \brief method is the callback of the selectComponent call; if middleware executed the call correct and preconditions were  followed the callback carries the requested data
	 *  \param [in] componentID a uint32_t; ID of the requested component
	 *  \param [in] selectParameter a SelectParameter; contains the filter information of the data requesting call
	 *  \param [in] data a Bytebuffer; carries the requested data in the project specific format
	 *  \param [in] handle a uint32_t; handle to identify the callback
	 *  \param [in] errorCode a ErrorCode; process execution state
	 *  \return returns true (do not care)
	 */
	bool DataEventCallbackClient		(
			const IVIRadio::Types::Types::StationSelectors stationSelectors,
			const IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
			const IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions,
			const IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption selectOptions,
			const IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat format,
			const IVIRadio::AdditionalService::AdditionalServiceTypes::DataType type,
			const IVIRadio::AdditionalService::AdditionalServiceTypes::Data data,
			const uint32_t& handleOut,
			const IVIRadio::Types::Types::ErrorCodes errorCode
		);

	static void * InternalThreadEntryFunc_DataPipe(void * _arg){
		((Client*)_arg)->InternalThreadEntry_DataPipe( _arg );
	   	return NULL;
	}

	void InternalThreadEntry_DataPipe (void *_arg );


	bool SubscribedServiceOptionsCallbackClient
			(
			IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
			IVIRadio::Types::Types::arrayStationSelectors stationSelections,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOptions unifiedOptions,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOptions serviceOptions,
			uint32_t handleOut,
			IVIRadio::Types::Types::ErrorCodes errorCode
			);

	/**
	 * \brief method is the callback of the method call changeFunctionalityConfiguration or requestFunctionalityConfiguration
	 *  \param [in] functionaliyTypes a vector of FunctionaliyTypes; vector contains functionality types for which the configuration was requested or changed
	 *  \param [in] FuntionalityOptions a vector of functionalityOptions; vector contains the current configuration of the functionality types matching to the first parameter
	 *  \param [in] handle a uint32_t; handle to identify the callback
	 *  \param [in] errorCode a ErrorCode; process execution state
	 *  \return returns true (do not care)
	 */
	bool FunctionalityConfigurationEventCallbackClient( const IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionaliyTypes,
			const IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions functionalityOptions,
			const uint32_t handle_out, const IVIRadio::Types::Types::ErrorCodes errorCode );

	/**
	 * \brief method evaluates the handle and checks if the callback handle is same like the client handle
	 *  \param [in] sCallbackName is a string; contains the callback name; is just for logging purpose
	 *  \param [in] handle is an uint32_t; handle from the callback that needs to be evaluated
	 *  \param [in] handle a uint32_t; handle to identify the callback
	 *  \return returns true is callback handle matches to client handle
	 */
	bool ReceivedCallback( string sCallbackName, uint32_t handle);

	bool getStationSelectorFromID ( uint32_t stationID, IVIRadio::Types::Types::StationSelector &station );

private:

	bool m_pipeActive;
	int m_hmiId;
	int m_currentJobId;
	IVIRadio::Station::StationTypes::StationList m_stationListAMFM;
	IVIRadio::Station::StationTypes::StationList m_stationListDAB;
	IVIRadio::Station::StationTypes::StationList m_stationListUndef;

	map<uint32_t, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType> m_activeAnnouncements;

	/**
	 * \brief instance of terminalIO controls in and output from and to the console
	 */
	TerminalIO *m_terminalIO;

	std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::load();
	std::shared_ptr<CommonAPI::Factory> factory = runtime->createFactory();

	/**
	 * \brief proxy provides the methods for the Tuner station Management component
	 */
	std::shared_ptr<IVIRadio::Station::StationProxy<> > proxy_TunerStation;

	/**
	 * \brief proxy provides the methods for the Tuner Additional Services component
	 */
	std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> > proxy_AdditionalService;

	/**
	 * \brief proxy provides the methods for the Configuration Options
	 */
	std::shared_ptr<IVIRadio::Configuration::ConfigurationProxy<> > proxy_Configuration;

	pthread_t thread_pipe;

protected:
	/**
	* \brief default constructor; constructor creates the proxys for the communication with the middleware and creates a loop that waits for console input from the user
	*/
	Client( int id );
	static Client* _instance;

};

/**
* \brief method provides a sink where a seek callback (answer to a seek interface method call from the middleware) ends; method simply forwards the callback to the client
* \param [in] seekData a SeekData struct contains the seek mode relevant data; progress information, seek mode and type of value of progress information
* \param [in] handle an uint32_t to identifiy the request
*/
CommonAPI::SubscriptionStatus seekCallback          (IVIRadio::Station::StationTypes::SeekData seekData, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode){
	Client::getInstance(handle)->SeekCallbackClient(seekData, handle, errorCode);
    return CommonAPI::SubscriptionStatus::RETAIN;
}

/**
* \brief method provides a sink where a currentStation callback (answer to a controlUpdate interface method call from the middleware) ends
* \param [in] current a Station contains the information of the currently tuned station
* \param [in] uint32_t handle an uint32_t to identifiy the request
*/
CommonAPI::SubscriptionStatus currentStationCallback(IVIRadio::Station::StationTypes::Station current, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode)
{
	Client::getInstance(handle)->CurrentStationCallbackClient(current, handle,  errorCode);
	return CommonAPI::SubscriptionStatus::RETAIN;
}


/**
* \brief method provides a sink where a stationList callback (answer to a controlUpdate interface method call from the middleware) ends
* \param [in] list a StationList contains the information of the most recent background scan for the requested waveband
* \param [in] uint32_t handle an uint32_t to identifiy the request
*/

CommonAPI::SubscriptionStatus stationListCallback(IVIRadio::Station::StationTypes::StationList list, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode)
{
	Client::getInstance(handle)->StationListCallbackClient(list, handle, errorCode);
	return CommonAPI::SubscriptionStatus::RETAIN;
}

/**
* \brief method provides a sink where a stationList callback ends
* \param [in] announcement an Announcement; Structure that carries information to the incoming announcement
* \param [in] uint32_t handle an uint32_t to identifiy the request
*/

CommonAPI::SubscriptionStatus announcementEventCallback(
		IVIRadio::Types::Types::StationSelectors stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations announcementConfigurations,
		IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates announcementStates,
		const uint32_t& handle, IVIRadio::Types::Types::ErrorCodes errorCode )
{
	Client::getInstance(handle)->AnnouncementEventCallbackClient(stationSelectors, announcementConfigurations, announcementStates, handle, errorCode);
	return CommonAPI::SubscriptionStatus::RETAIN;
}

/**
* \brief method provides a sink where a announcementFinished callback (answer to a getData interface method call from the middleware) ends
* \param [in] announcement an Announcement; Structure that carries information to the incoming announcement
* \param [in] uint32_t handle an uint32_t to identifiy the request
*/
/*CommonAPI::SubscriptionStatus announcementFinishedEventCallback( const IVIRadio::AdditionalService::AdditionalServiceTypes::Announcement& announcement,
		const uint32_t& handle, IVIRadio::Types::Types::ErrorCodes errorCode )
{
	Client::getInstance(handle)->AnnouncementFinishedEventCallbackClient(announcement, handle, errorCode);
	return CommonAPI::SubscriptionStatus::RETAIN;
}*/

/**
* \brief method provides a sink where a componentOptionsEventCallback callback (answer to a componentOptionsEventCallback interface method call from the middleware) ends
* \param [in] componentID an uint32_t; systemwide unique id to identify a additional component
* \param [in] selectParameter an SelectParameter; Union for the selection of a component. Depending on the component type the used structure is different.
* \param [in] data a uint32_t; containing the data in a format depending on the component type
* \param [in] uint32_t handle an uint32_t to identifiy the request
*/
CommonAPI::SubscriptionStatus DataEventCallback
		(
				const IVIRadio::Types::Types::StationSelectors stationSelectors,
				const IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
				const IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions,
				const IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption selectOptions,
				const IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat format,
				const IVIRadio::AdditionalService::AdditionalServiceTypes::DataType type,
				const IVIRadio::AdditionalService::AdditionalServiceTypes::Data data,
				const uint32_t& handleOut,
				const IVIRadio::Types::Types::ErrorCodes errorCode
		)
{
	Client::getInstance(handleOut)->DataEventCallbackClient( stationSelectors, dataService, unifiedOptions, selectOptions, format, type, data, handleOut, errorCode);
	return CommonAPI::SubscriptionStatus::RETAIN;
}

CommonAPI::SubscriptionStatus SubscribedServiceOptionsEventCallback(
		IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
		IVIRadio::Types::Types::arrayStationSelectors stationSelections,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOptions unifiedOptions,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOptions serviceOptions,
		uint32_t handleOut,
		IVIRadio::Types::Types::ErrorCodes errorCode
		){
	Client::getInstance(0)->SubscribedServiceOptionsCallbackClient(dataService, stationSelections, unifiedOptions, serviceOptions, handleOut, errorCode);
	return CommonAPI::SubscriptionStatus::RETAIN;
}

/**
 * \brief broadcast to return the requested functionality configuration
 * \param functionaliytyTypes of type FunctionalityTypes; functionality types the configuration should be set of
 * \param functionalityOptions of type ArrayFuntionalityOptions; current configuration of a functionality
 * \param handle_out an uint32_t handle to identify the correct destination of the following event
 * \param errorCode of type ErrorCodes; execution state of the job. if successful finished EC_OK
 */
CommonAPI::SubscriptionStatus functionalityConfigurationEventCallback(
		const IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes 			functionaliyTypes,
		const IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions		 		functionalityOptions,
		const uint32_t handle_out,
		const IVIRadio::Types::Types::ErrorCodes errorCode )
{
	Client::getInstance(0)->FunctionalityConfigurationEventCallbackClient(functionaliyTypes, functionalityOptions, handle_out, errorCode);
	return CommonAPI::SubscriptionStatus::RETAIN;
}

#endif // !defined(EA_6DC8A062_292B_4a30_91A1_B934F82EBE47__INCLUDED_)
