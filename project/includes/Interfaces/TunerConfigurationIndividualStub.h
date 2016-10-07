///////////////////////////////////////////////////////////
//  TunerConfigurationIndividualStub.h
//  Implementation of the Class TunerConfigurationIndividualStub
//  Created on:      18-Sep-2013 08:25:38
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_8AFDB338_A774_4cb1_B5EC_259813A660E5__INCLUDED_)
#define EA_8AFDB338_A774_4cb1_B5EC_259813A660E5__INCLUDED_

#include "IVIRadio/Configuration/ConfigurationStubDefault.h"
#include <stdint.h>
#include <pthread.h>
#include "../TerminalIO.h"
#include "../Middleware.h"

class TunerConfigurationStubDefault;
class TunerConfigurationIndividualStub;

/**
 * \struct arg_ThreadParam
 * \brief struct contains parameter to start a thread to request functionality configuration or to set functionality configuration
 * \param *pThis is a pointer to TunerConfigurationIndividualStub and contains always a this pointer
 * \param functionalityOptions a vector of FuntionalityOptions parameter that contains desired functionality options to be set as current
 * \param functionalityOptionsGet a vector of FuntionalityOptionsGet to request the configurations matching to the functionality types
 * \param functionalityTypes a vector FunctionalityTypes containing the types the configuration is requested for or desired to changed
 */
struct arg_ThreadParam {
	TunerConfigurationIndividualStub *pThis;
	IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions	 			functionalityOptions;
	IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet	 	functionalityOptionsGet;
	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes 			functionalityTypes;
	uint32_t handle;
};

/**
 * \class TunerConfigurationIndividualStub
 * \brief the class TunerConfigurationIndividualStub overrides the methods from TunerConfigurationStubDefault;\n
 * 		  practically all the calls from the client for additional services are ending here; this is the first part
 * 		  where individual logic (independent from Common API logic) needs to be implemented. \n
 * 		  this methods all start threads to start a middleware functionality or they call directly middleware methods to required information\n
 *		  calls regarding configuration are ending up here.\n
 * 		  class inherits IVIRadio::Configuration::ConfigurationStubDefault\n
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

class TunerConfigurationIndividualStub : public IVIRadio::Configuration::ConfigurationStubDefault
{

public:
	/**
	* \brief default costructor
	*/
	TunerConfigurationIndividualStub();
	/**
	* \brief default costructor
	*/
	virtual ~TunerConfigurationIndividualStub();

	/**
	* \brief user changes configuration of multiple functionality types
	* \param [in] functionalityTypes an vector of FunctionalityTypes contains functionalityTypes for which the configuration is requested
	* \param [in] functionalityOptions an vector FuntionalityOptions contain to every functionalityType the matching configuration to be set
	* \param [in] handle an UIn32  an optional handle for identifying the request
	* \param [out] handle_out an UInt32  the handle of the corresponding request
	* \param [out] feedback a Feedback the result of the request
	*/
	virtual void changeFunctionalityConfiguration(
    		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
    		IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions functionalityOptions,
    		uint32_t handle, uint32_t& handle_out, IVIRadio::Types::Types::Feedback& feedback);

	/**
	* \brief user requests configuration of multiple functionality types
	* \param [in] functionalityTypes an vector of FunctionalityTypes contains functionalityTypes for which the configuration is requested
	* \param [in] functionalityOptionsGet an vector FuntionalityOptionsGet contains to every functionalityType the matching options to request the configuration
	* \param [in] handle an UIn32  an optional handle for identifying the request
	* \param [out] handle_out an UInt32  the handle of the corresponding request
	* \param [out] feedback a Feedback the result of the request
	*/
	virtual void requestFunctionalityConfiguration(
    		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
    		IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityOptionsGet,
    		uint32_t handle, uint32_t& handle_out, IVIRadio::Types::Types::Feedback& feedback);

	/**
	 * \brief assign middleware to the stub and start threads for announcements to be enabled to send and finish everytime announcements
	 * \para [in] middleware a Middleare Middleware the Stub should be call when methodcalls are arriving
	 */
	void setMiddleware(Middleware *middleware){
		m_MW = middleware;
	}

   static void * InternalThreadEntryFunc_JobChangeConfig(void * args){
	   ((arg_ThreadParam *)args)->pThis->InternalThreadEntry_ChangeConfig( args );
	   return NULL;
   }

   void InternalThreadEntry_ChangeConfig(void * This);

   static void * InternalThreadEntryFunc_JobRequestConfig(void * args){
	   ((arg_ThreadParam *)args)->pThis->InternalThreadEntry_RequestConfig( args );
	   return NULL;
   }

   void InternalThreadEntry_RequestConfig(void *This);

private:

    /**
    * \brief m_TerminalIO is an instance of a singleton class that cares about console in and output
    */
	TerminalIO 	*m_TerminalIO;

	/**
	* \brief m_MW is a pointer to the middleware which administrates all possible required information that can be called for
	*/
	Middleware 	*m_MW;

	pthread_t m_thread_changeConfig;
	pthread_t m_thread_requestConfig;

};
#endif // !defined(EA_8AFDB338_A774_4cb1_B5EC_259813A660E5__INCLUDED_)
