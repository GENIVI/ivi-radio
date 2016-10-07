///////////////////////////////////////////////////////////
//  TunerConfigurationIndividualStub.cpp
//  Implementation of the Class TunerConfigurationIndividualStub
//  Created on:      18-Sep-2013 08:25:38
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Interfaces/TunerConfigurationIndividualStub.h"


TunerConfigurationIndividualStub::TunerConfigurationIndividualStub(){

}

TunerConfigurationIndividualStub::~TunerConfigurationIndividualStub(){

}

void TunerConfigurationIndividualStub::changeFunctionalityConfiguration(
		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
		IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions functionalityOptions,
		uint32_t handle, uint32_t& handle_out, IVIRadio::Types::Types::Feedback& feedback)
{
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "Received call to changeFunctionalityConfiguration()"							<< endl;
	cout << "Handle: " << handle << endl;
	//prepare out paramter
	handle_out 	= handle;
	feedback 	= IVIRadio::Types::Types::Feedback::DONE;
	//prepare parameter for thread
	struct arg_ThreadParam *args  	= new arg_ThreadParam();
	args->pThis 					= this;
	args->functionalityOptions		= functionalityOptions;
	args->functionalityTypes		= functionalityTypes;
	args->handle					= handle;
	pthread_create( &m_thread_changeConfig, NULL, InternalThreadEntryFunc_JobChangeConfig, args );
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
}

void TunerConfigurationIndividualStub::InternalThreadEntry_ChangeConfig(void * args){
	struct arg_ThreadParam *_args = ( arg_ThreadParam *)args;
	IVIRadio::Types::Types::ErrorCodes errorCode = IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
	errorCode = m_MW->changeFunctionalityConfiguration( _args->handle, _args->functionalityTypes, _args->functionalityOptions);
	fireFunctionalityConfigurationEvent(_args->functionalityTypes, _args->functionalityOptions, _args->handle, errorCode );
}

void TunerConfigurationIndividualStub::requestFunctionalityConfiguration(
		IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
		IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityOptionsGet,
		uint32_t handle, uint32_t& handle_out, IVIRadio::Types::Types::Feedback& feedback)
{
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "Received call to requestFunctionalityConfiguration()"							<< endl;
	handle_out = handle;
	feedback = IVIRadio::Types::Types::Feedback::DONE;
	IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityOptions;
	struct arg_ThreadParam *args  	= new arg_ThreadParam();
	args->pThis 					= this;
	args->functionalityOptionsGet	= functionalityOptionsGet;
	args->functionalityTypes		= functionalityTypes;
	args->handle					= handle;
	pthread_create( &m_thread_changeConfig, NULL, InternalThreadEntryFunc_JobRequestConfig, args );
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
}

void TunerConfigurationIndividualStub::InternalThreadEntry_RequestConfig(void *args){
	struct arg_ThreadParam *_args = ( arg_ThreadParam *)args;
	IVIRadio::Types::Types::ErrorCodes errorCode = IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
	errorCode = m_MW->requestFunctionalityConfiguration( _args->handle, _args->functionalityTypes, _args->functionalityOptionsGet, _args->functionalityOptions);
	fireFunctionalityConfigurationEvent(_args->functionalityTypes, _args->functionalityOptions, _args->handle, errorCode );
}
