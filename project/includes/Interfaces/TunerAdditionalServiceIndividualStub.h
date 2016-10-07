///////////////////////////////////////////////////////////
//  TunerAdditionalServiceIndividualStub.h
//  Implementation of the Class TunerAdditionalServiceIndividualStub
//  Created on:      17-Jul-2013 10:21:28
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_3A644812_8E67_44c9_9F10_EF4371541619__INCLUDED_)
#define EA_3A644812_8E67_44c9_9F10_EF4371541619__INCLUDED_

#include "IVIRadio/AdditionalService/AdditionalServiceStubDefault.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypes.h"

#include "../TerminalIO.h"
#include "../Middleware.h"
#include <pthread.h>
#include <stdint.h>

class TunerAdditionalServiceIndividualStub;

/**
 * \struct arg_getDataThread
 * \brief struct contains information to start the get data thread to call for data from the middleware
 * \param *pThis is a pointer to TunerAdditionalServiceIndividualStub and contains always a this pointer
 * \param componentID an UInt32 parameter choose the component for the request
 * \param handle an uint32 an optional handle for identifying the request
 * \param component_parameter an SelectParamater parameter to configure the requested component
 */
struct arg_getDataThread {
	TunerAdditionalServiceIndividualStub *pThis;
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService;
	IVIRadio::Types::Types::StationSelectors stationSelectors;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedServiceOption;
	uint32_t handle;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption dataServiceOption;
};

struct arg_requestComponentConfigurationThreadData {
	TunerAdditionalServiceIndividualStub *pThis;
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService;
	uint32_t handle;
};

/**
 * \class TunerAdditionalServiceIndividualStub
 * \brief the class TunerAdditionalServiceIndividualStub overrides the methods from TunerAdditionalServiceStubDefault;\n
 * 		  practically all the calls from the client for additional services are ending here; this is the first part
 * 		  where individual logic (independent from Common API) needs to be implemented. \n
 * 		  this methods all start threads to start a middleware functionality or they call directly middleware methods to required information\n
 * 		  class inherits TunerAdditionalService::TunerAdditionalServiceStubDefault\n
 *
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


class TunerAdditionalServiceIndividualStub : public IVIRadio::AdditionalService::AdditionalServiceStubDefault
{

public:
	/**
	 * \brief default costructor
	 */
	TunerAdditionalServiceIndividualStub();

	/**
	 * \brief default destructor
	 */
	virtual ~TunerAdditionalServiceIndividualStub();

	/**
	 * \brief the user can notify on specific datasets and cancel those notifications
	 * \para [in] dataService the DataService the user wants to receive data from
	 * \para [in] stationSelectors is an array of StationSelector indicating the Station which shall provide the data
	 * \para [in] unifiedOptions the UnifiedServiceOption contains the information if the user wants to notify or cancel a existing notification
	 * \para [in] componentParameter the DataServiceOption are the specific filter options for the given dataservice
	 * \param [in] handle an UIn32  an optional handle for identifying the request
	 * \param [out] handle_out an UInt32  the handle of the corresponding request
	 * \param [out] feedback a Feedback the result of the request
	 */
	virtual void requestDataService(
			IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
					IVIRadio::Types::Types::StationSelectors stationSelectors,
					IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions,
					IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption componentParameter,
					uint32_t handle,
					uint32_t& handleOut,
					IVIRadio::Types::Types::Feedback& feedback
				);

	/**
	 * \brief function returns the subscription settings for the given dataService
	 * \param [in] dataService the DataService the Client requests the settings for
	 * \param [in] handle an UIn32  an optional handle for identifying the request
	 * \param [out] handle_out an UInt32  the handle of the corresponding request
	 * \param [out] feedback a Feedback the result of the request
	 */
	virtual void requestSubscribedServiceOptions(
					IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
					uint32_t handle,
					uint32_t& handleOut,
					IVIRadio::Types::Types::Feedback& feedback
				);

	/**
	 * \brief abort a currently active transmission of data
	 * \param [in] data service a current transmission of data want to be stopeed for
	 * \param [in] stationSelectors array of station selectors which are providing the currently transmitted data
	 * \param [in] unifiedOptions unified options describing the request
	 * \param [in] dataServiceOption specific parameter describing the data request
	 * \param [in] handle an UIn32  an optional handle for identifying the request
	 * \param [out] handle_out an UInt32  the handle of the corresponding request
	 * \param [out] feedback a Feedback the result of the request
	 */
	virtual void abort(
			IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
			IVIRadio::Types::Types::StationSelectors stationSelectors,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption dataServiceOption,
			uint32_t handle, uint32_t& handleOut,
			IVIRadio::Types::Types::Feedback& feedback
			);

	/**
	 * \brief assign middleware to the stub and start threads for announcements to be enabled to send and finish everytime announcements
	 * \para [in] middleware a Middleare Middleware the Stub should be call when methodcalls are arriving
	 */
	void setMiddleware(Middleware *middleware){
		m_MW = middleware;
		pthread_create(&m_thread_SendAnnouncement  , NULL, InternalThreadEntryFunc_SendAnnouncement  , this);
		pthread_create(&m_thread_FinishAnnouncement, NULL, InternalThreadEntryFunc_FinishAnnouncement, this);
	}

	/**
	 * \brief class internal entry point for the thread GetData; the parameter is casted to arg_getDataThread and then passed to the actual thread
	 * \param [in] This is a void pointer should be of type arg_getDataThread and contains information to execute the GetData job
	 */
   static void * InternalThreadEntryFunc_JobGetData(void * This){
	   ((arg_getDataThread *)This)->pThis->InternalThreadEntry_GetData( This );
	   return NULL;
   }


   static void * InternalThreadEntryFunc_JobRequestComponentNotifications(void * This){
   	   ((arg_getDataThread *)This)->pThis->InternalThreadEntry_RequestComponentNotifications( This );
   	   return NULL;
      }

   void InternalThreadEntry_RequestComponentNotifications (void *args );

   /**
    * \brief method calls middleware for required data and sends a get data broadcast back to the client
    * \param [in] *args is a void * should be type arg_getDataThread and contains parameter of the selectComponent method
    */
   void InternalThreadEntry_GetData( void *args );

   /**
   	 * \brief class internal entry point for the thread SendAnnouncement; the parameter is casted to TunerAdditionalServiceIndividualStub* and the actual thread InternalThreadEntry_SendAnnouncement gets started
   	 * \param [in] This is a void pointer should be of type arg_getDataThread and contains information to execute the GetData job
   	 */
   static void * InternalThreadEntryFunc_SendAnnouncement(void * This) {
	   ((TunerAdditionalServiceIndividualStub *)This)->InternalThreadEntry_SendAnnouncement(); return NULL;
   }

   /**
    * \param thread runs during the whole runtime of the program and pulls the middleware if it has a announcement to be send
    */
   void InternalThreadEntry_SendAnnouncement   ();

   /**
   	 * \brief class internal entry point for the thread FinishAnnouncement; the parameter is casted to TunerAdditionalServiceIndividualStub* and the actual thread InternalThreadEntryFunc_FinishAnnouncement gets started
   	 * \param [in] This is a void pointer should be of type arg_getDataThread and contains information to execute the GetData job
   	 */
   static void * InternalThreadEntryFunc_FinishAnnouncement(void * This) {
	   ((TunerAdditionalServiceIndividualStub *)This)->InternalThreadEntry_FinishAnnouncement(); return NULL;
   }

   /**
   * \param thread runs during the whole runtime of the program and pulls the middleware if it has a announcement to be finished
   */
   void InternalThreadEntry_FinishAnnouncement ();


private:

    /**
    * \brief m_TerminalIO is an instance of a singleton class that cares about console in and output
    */
	TerminalIO 	*m_TerminalIO;

	/**
	* \brief m_MW is a pointer to the middleware which administrates all possible required information that can be called for
	*/
	Middleware 	*m_MW;

	/**
	* \brief m_thread_getData is the thread to be started to get data from the middleware
	*/
	pthread_t m_thread_getData ;

	/**
	* \brief m_thread_SendAnnouncement is the thread to be started to wait for an announcement to be send
	*/
	pthread_t m_thread_SendAnnouncement;

	/**
	* \brief m_thread_SendAnnouncement is the thread to be started to wait for an announcement to be send
	*/
	pthread_t m_thread_FinishAnnouncement;

	pthread_t m_thread_requestComponentNotifications;

};

#endif // !defined(EA_3A644812_8E67_44c9_9F10_EF4371541619__INCLUDED_)
