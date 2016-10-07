///////////////////////////////////////////////////////////
//  TunerAdditionalServiceIndividualStub.cpp
//  Implementation of the Class TunerAdditionalServiceIndividualStub
//  Created on:      17-Jul-2013 10:21:28
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Interfaces/TunerAdditionalServiceIndividualStub.h"

#define LOG( a, b ) m_TerminalIO->Log( a, b )

TunerAdditionalServiceIndividualStub::TunerAdditionalServiceIndividualStub(){
	m_TerminalIO = TerminalIO::getInstance();
}

TunerAdditionalServiceIndividualStub::~TunerAdditionalServiceIndividualStub(){

}

void TunerAdditionalServiceIndividualStub::requestSubscribedServiceOptions(
				IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
				uint32_t handle,
				uint32_t& handleOut,
				IVIRadio::Types::Types::Feedback& feedback
			){

	LOG( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>", INFO );
	LOG( "Received call to requestComponentNotifications()"           					, INFO );
	LOG( "ComponentType		: " + m_TerminalIO->getComponentType( dataService )  		, INFO );
	LOG( "Handle     		: " + to_string( handle )  									, INFO );
	//set return parameter
	feedback  = IVIRadio::Types::Types::Feedback::DONE;
	handleOut = handle;
	struct arg_requestComponentConfigurationThreadData *args  = new arg_requestComponentConfigurationThreadData();
	args->pThis 					= this;
	args->dataService				= dataService;
	args->handle					= handle;
	//start the thread to get the requested data
	pthread_create( &m_thread_requestComponentNotifications, NULL, InternalThreadEntryFunc_JobRequestComponentNotifications, args );
}

void TunerAdditionalServiceIndividualStub::abort(
		IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
		IVIRadio::Types::Types::StationSelectors stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedOptions,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption dataServiceOption,
		uint32_t handle, uint32_t& handleOut,
		IVIRadio::Types::Types::Feedback& feedback
		){
	LOG( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>", INFO );
	LOG( "Received call to abort()"           											, INFO );
	LOG( "StationID         : " + to_string(stationSelectors[0].id[0])					, INFO );
	LOG( "ComponentType		: " + m_TerminalIO->getComponentType( dataService )  		, INFO );
	LOG( "Handle     		: " + to_string( handle )  									, INFO );
	feedback  = IVIRadio::Types::Types::Feedback::DONE;
	handleOut = handle;

	if (dataService != IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_ANNOUNCEMENT ) {
		feedback  = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
		return;
	}
	IVIRadio::AdditionalService::AdditionalServiceTypes::Announcement announcement;
	IVIRadio::Types::Types::ErrorCodes errorCode = m_MW->abort(dataService, stationSelectors, unifiedOptions, handle, dataServiceOption, announcement);
	fireAnnouncementFinishedEvent(announcement, handle, errorCode);
}

void TunerAdditionalServiceIndividualStub::InternalThreadEntry_RequestComponentNotifications ( void *args ) {
	//call middleware for requested data
	struct arg_requestComponentConfigurationThreadData *_args = ( arg_requestComponentConfigurationThreadData *)args;
	IVIRadio::Types::Types::ErrorCodes													 _errorCode;
	IVIRadio::AdditionalService::AdditionalServiceTypes::Data 							data;
	IVIRadio::Types::Types::arrayStationSelectors 										arrayStationSel;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOptions 		dataServiceOptions;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOptions 	unifiedServiceOptions;
	_errorCode = _args->pThis->m_MW->getComponentNotifications ( _args->dataService,  arrayStationSel, unifiedServiceOptions, dataServiceOptions, _args->handle );
	//send dbus message containing the requested data
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat dataFormat = IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat::DF_XML;
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataType   dataType   = IVIRadio::AdditionalService::AdditionalServiceTypes::DataType  ::DT_BYTEBUFFER;
	vector <uint32_t> tmp;
	tmp.push_back(1);
	fireSubscribedServiceOptionsEvent( _args->dataService,  arrayStationSel, unifiedServiceOptions, dataServiceOptions, _args->handle, _errorCode );
}


void TunerAdditionalServiceIndividualStub::requestDataService(
		IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
		IVIRadio::Types::Types::StationSelectors stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedServiceOption,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption componentParameter,
		uint32_t handle,
		uint32_t& handleOut,
		IVIRadio::Types::Types::Feedback& feedback )
{

	LOG( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"		, INFO );
	LOG( "Received call to requestDataService()"           										, INFO );
	for ( auto it = stationSelectors.cbegin(); it != stationSelectors.cend(); it++ ){
		cout << "StationSelector : " << endl;
		m_TerminalIO->printStationSelector( (*it) );
	}
	LOG( "Handle      : " + to_string( handle )													, INFO );
	LOG( "Update Type : " + m_TerminalIO->getUpdateType   ( unifiedServiceOption.requestType ) 	, INFO );
	LOG( "Data Service: " + m_TerminalIO->getComponentType( dataService ) 						, INFO );
	LOG( "ComponentParameter	-> "															, INFO );
	m_TerminalIO->printSelectParamter( dataService, componentParameter, unifiedServiceOption.objectID );
	//set return parameter
	feedback  = IVIRadio::Types::Types::Feedback::DONE;
	handleOut = handle;
	struct arg_getDataThread *args  = new arg_getDataThread();
	args->pThis 					= this;
	args->dataService				= dataService;
	args->stationSelectors 			= stationSelectors;
	args->handle					= handle;
	args->dataServiceOption 		= componentParameter;
	args->unifiedServiceOption		= unifiedServiceOption;
	//start the thread to get the requested data
	pthread_create( &m_thread_getData, NULL, InternalThreadEntryFunc_JobGetData, args );
}

//thread calls middleware for requested data and sends it via broadcast to the client
void TunerAdditionalServiceIndividualStub::InternalThreadEntry_GetData ( void *args ) {
	//call middleware for requested data
	struct arg_getDataThread *_args = ( arg_getDataThread *)args;
	IVIRadio::Types::Types::ErrorCodes _errorCode;
	IVIRadio::AdditionalService::AdditionalServiceTypes::Data data;
	_errorCode = _args->pThis->m_MW->getData( _args->dataService, _args->stationSelectors, _args->unifiedServiceOption, _args->handle, _args->dataServiceOption, data  );
	//send dbus message containing the requested data
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat dataFormat = IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat::DF_XML;
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataType   dataType   = IVIRadio::AdditionalService::AdditionalServiceTypes::DataType  ::DT_BYTEBUFFER;
	fireDataEvent( _args->stationSelectors, _args->dataService, _args->unifiedServiceOption, _args->dataServiceOption, dataFormat, dataType, data, _args->handle, _errorCode );
}

void TunerAdditionalServiceIndividualStub::InternalThreadEntry_SendAnnouncement  () {
	while ( 1 ) {
		if ( m_MW->getSendAnnouncement() ) {
			IVIRadio::AdditionalService::AdditionalServiceTypes::Announcement announcement;
			uint32_t handle;
			IVIRadio::Types::Types::StationSelectors 										stationSelectors;
			IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations annConfigs;
			IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates 	arrAnnStates;

			m_MW->getCurrentAnnouncementData( handle, stationSelectors, annConfigs, arrAnnStates );
			IVIRadio::Types::Types::ErrorCodes errorCode = IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
			//change here fireEvent to version 2.0.1

			fireAnnouncementEvent(stationSelectors, annConfigs, arrAnnStates, handle, errorCode);
			//fireAnnouncementEvent( announcement , handle, errorCode );
			m_MW->setSendAnnouncement( false );
		}
		usleep(1000*25);
	}
}

void TunerAdditionalServiceIndividualStub::InternalThreadEntry_FinishAnnouncement  () {
	while ( 1 ) {
		if ( m_MW->getFinishAnnouncement() ) {
			IVIRadio::AdditionalService::AdditionalServiceTypes::Announcement announcement;
			uint32_t handle;
			//Version 2.0.1
			//m_MW->getCurrentAnnouncementData(announcement, handle);
			IVIRadio::Types::Types::ErrorCodes errorCode = IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
			fireAnnouncementFinishedEvent( announcement, handle,errorCode );
			m_MW->setFinishAnnouncement( false );
		}
		usleep(1000*25);
	}
}
