///////////////////////////////////////////////////////////
//  TunerStationIndividualStub.cpp
//  Implementation of the Class TunerStationIndividualStub
//  Created on:      17-Jul-2013 10:25:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Interfaces/TunerStationIndividualStub.h"



TunerStationIndividualStub::TunerStationIndividualStub(){
	m_TerminalIO 				= TerminalIO::getInstance();
	m_thread_JobSeek_completed 	= false;
	m_MW 						= NULL;
}

TunerStationIndividualStub::~TunerStationIndividualStub(){
}

void TunerStationIndividualStub::startTune(
		IVIRadio::Types::Types::StationSelector station,
			IVIRadio::Station::StationTypes::SelectionMode selectionMode,
			uint32_t 	handle,
			uint32_t& 	handle_out,
			IVIRadio::Types::Types::Feedback& feedback
	   )
{
	struct arg_ThreadDataStartTune *threadData 	= new arg_ThreadDataStartTune();
	threadData->handle 							= handle;
	threadData->handle_out 						= handle_out;
	threadData->pThis 							= this;
	threadData->selectionMode 					= selectionMode;
	threadData->station 						= station;
	//if device type is 3 or 4 (TV or SDARS) return immediately without doing anything
	//since only dab and fm is supported
	if ( station.deviceType == 3 || station.deviceType == 4 ){
		feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
		return;
	}
	feedback = IVIRadio::Types::Types::Feedback::DONE;
	//start thread for the tune command
	pthread_create( &m_thread_startTune , NULL, InternalThreadEntryFunc_JobStartTune, threadData );
}

void TunerStationIndividualStub::InternalThreadEntry_JobStartTune( void * threadData ){
	struct arg_ThreadDataStartTune *_args = ( arg_ThreadDataStartTune *)threadData;
	m_MW->startTune( _args->station, _args->selectionMode, _args->handle );
	IVIRadio::Station::StationTypes::Station current_station ;
	IVIRadio::Types::Types::ErrorCodes errorCode = m_MW->getCurrentStationOfHMI( _args->handle , current_station );
	fireCurrentStationEvent( current_station , _args->handle, errorCode);
}

void TunerStationIndividualStub::abortTune(
		IVIRadio::Types::Types::DeviceType device,
	       uint32_t handle,
	       uint32_t& handle_out,
	       IVIRadio::Types::Types::Feedback& feedback
	   )
{

}

void TunerStationIndividualStub::seek(
		IVIRadio::Types::Types::DeviceType 				device,
	       IVIRadio::Station::StationTypes::SeekMode 	seekMode,
	       uint8_t 										genre,
	       IVIRadio::Types::Types::UInt32s 				flags,
	       uint32_t 									handle,
	       uint32_t& 									handle_out,
	       IVIRadio::Types::Types::Feedback& 			feedback
	   )
{
	LOG( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"					, INFO );
	LOG( "Received call to seek( )"																			, INFO );
	LOG( "DeviceType: " + m_TerminalIO->getDeviceType((IVIRadio::Types::Types::DeviceType)device)			, INFO );
	LOG( "SeekMode  : " + m_TerminalIO->getSeekMode  ((IVIRadio::Station::StationTypes::SeekMode)seekMode)	, INFO );
	LOG( "Genre     : " + to_string( genre  ), INFO );
	LOG( "Handle    : " + to_string( handle ), INFO );
	struct arg_ThreadDataStartSeek *threadData = new arg_ThreadDataStartSeek();
	threadData->device 		= device;
	threadData->handle 		= handle;
	threadData->pThis  		= this;
	threadData->seekMode 	= seekMode;
	//catch not supported cases and return immeadeately without doing anything
	if (	seekMode   	== IVIRadio::Station::StationTypes::SeekMode::SM_SCAN_UP        ||
			seekMode   	== IVIRadio::Station::StationTypes::SeekMode::SM_SCAN_DOWN      ||
			seekMode   	== IVIRadio::Station::StationTypes::SeekMode::SM_SCAN_SKIP_UP   ||
			seekMode  	== IVIRadio::Station::StationTypes::SeekMode::SM_SCAN_SKIP_DOWN ||
			device 		== IVIRadio::Types::Types::DeviceType::SDARS           			||
			device 		== IVIRadio::Types::Types::DeviceType::TV              			||
			device 		== IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE    			)
	{
		// not yet implemented
		// Prepare regular result
		feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
		handle_out = handle;
		LOG( "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" , INFO );
		return;
	}
	//create a thread to execute to actual seek and one to poll for changes in the data to fire events with updated data
	pthread_create( &m_thread_JobSeek , NULL, InternalThreadEntryFunc_JobSeek  , threadData );
	m_thread_JobSeek_completed = false; //set true if the thread JobSeek is finished
	if (seekMode == IVIRadio::Station::StationTypes::SeekMode::SM_AUTOSTORE ||
		seekMode == IVIRadio::Station::StationTypes::SeekMode::SM_AUTO_DOWN ||
		seekMode == IVIRadio::Station::StationTypes::SeekMode::SM_AUTO_UP    )

		if ( m_MW->getSeekNotification( handle, device ) ) {//check if HMI is notified on SeekProgress and create thread only if
			LOG( "Start thread to send back seek progress information", INFO );
			arg_ThreadDataStartSeek *_argsStartSeek = new arg_ThreadDataStartSeek();
			_argsStartSeek->handle 		= handle;
			_argsStartSeek->pThis 		= this;
			_argsStartSeek->device 		= device;
			_argsStartSeek->seekMode 	= seekMode;
			pthread_create( &m_thread_SeekData, NULL, InternalThreadEntryFunc_SeekEvent, _argsStartSeek );
		}
	return;
}

void TunerStationIndividualStub::InternalThreadEntry_JobSeek( void *_args ){
	struct arg_ThreadDataStartSeek *_argsStartSeek = ( arg_ThreadDataStartSeek *)_args;
	IVIRadio::Station::StationTypes::StationList oStationList;
	IVIRadio::Types::Types::ErrorCodes errorCode = m_MW->seek( _argsStartSeek->device, _argsStartSeek->seekMode, _argsStartSeek->handle , oStationList);

	IVIRadio::Station::StationTypes::SeekData seekData;
	if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_NOERROR ){
		seekData.data		 = 100;
		seekData.mode 		 = IVIRadio::Station::StationTypes::SeekMode       ::SM_OFF;
		seekData.returnValue = IVIRadio::Station::StationTypes::SeekReturnValue::SM_PERCENTAGE;
	}
	m_thread_JobSeek_completed = true; //set variable true if job is completed
	fireSeekEvent( seekData, _argsStartSeek->handle , errorCode ); //fire end of seek event without condition
	if ( _argsStartSeek->seekMode != IVIRadio::Station::StationTypes::SeekMode::SM_AUTOSTORE ) {
		IVIRadio::Station::StationTypes::Station current_station;
		IVIRadio::Types::Types::ErrorCodes errorCode_currentStation = m_MW->getCurrentStationOfHMI( _argsStartSeek->handle , current_station );
		fireCurrentStationEvent( current_station, _argsStartSeek->handle, errorCode_currentStation ); //send always current station result if not autostore because every other mode will cause a change of the current station
	}
	else {
		if ( m_MW->getListNotification( _argsStartSeek->handle, _argsStartSeek->device ) ) //send result only if client is notified
			fireStationListEvent( oStationList, _argsStartSeek->handle, errorCode );
	}
}

void TunerStationIndividualStub::InternalThreadEntry_SeekEvent( void *_args ){
	struct arg_ThreadDataStartSeek *_argsStartSeek = ( arg_ThreadDataStartSeek *)_args;
	uint32_t oldSeekData = m_MW->getSeekData().data;
	//as long as the seek is not completed pull the seek progress data of the middleware and fire an event if changed
	while ( !m_thread_JobSeek_completed ) {
		IVIRadio::Types::Types::ErrorCodes errorCode = IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
		usleep(1000*25);
		IVIRadio::Station::StationTypes::SeekData seekData = m_MW->getSeekData();
		uint32_t perc = seekData.data;
		if ( oldSeekData != perc && (perc % 10) == 0 ) { //if data has changed fire an event
			fireSeekEvent( seekData, _argsStartSeek->handle, errorCode );
		}
		oldSeekData = perc;
	}
}

void TunerStationIndividualStub::makePermanent(
		IVIRadio::Types::Types::StationSelector station,
	       bool permanent,
	       uint32_t handle,
	       uint32_t& handle_out,
	       IVIRadio::Types::Types::Feedback& feedback
	   )
{
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "Received call to makePermanent( )" << endl;
	m_TerminalIO->printStationSelector(station);
	cout << "Permanent: " << m_TerminalIO->getPermanent(permanent).c_str() << endl;
	cout << "Handle   : " << handle << endl;
	// can only handle AMFM or DAB at the moment
	if (((IVIRadio::Types::Types::DeviceType)station.deviceType != IVIRadio::Types::Types::DeviceType::AMFM) &&
		((IVIRadio::Types::Types::DeviceType)station.deviceType != IVIRadio::Types::Types::DeviceType::DAB)
	) {
		cout << "Device type is neither AMFM nor DAB" << station.deviceType << endl;
		handle_out = handle;
		feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		return;
	}
	int index;
	m_MW->makePermanent(station, permanent, handle);
	handle_out = handle;
	feedback = IVIRadio::Types::Types::Feedback::DONE;
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

}

void TunerStationIndividualStub::controlUpdate(
	       IVIRadio::Station::StationTypes::UpdateElement updateElement,
	       IVIRadio::Types::Types::UpdateType    updateType,
	       uint32_t sourceType,
	       uint32_t stationType,
	       uint32_t handle,
	       uint32_t& handle_out,
	       IVIRadio::Types::Types::Feedback& feedback
	   )
{
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "Received call to controlUpdate( )" << endl ;
	cout << "UpdateElement: " << m_TerminalIO->getUpdateElement(updateElement).c_str() << endl;
	cout << "UpdateType   : " << m_TerminalIO->getUpdateType   (updateType   ).c_str() << endl;
	cout << "SourceType   : " << m_TerminalIO->getSourceType   ((IVIRadio::Types::Types::SourceType)sourceType  ).c_str() << endl;
	cout << "StationType  : " << m_TerminalIO->getStationType  ((IVIRadio::Station::StationTypes::StationType)stationType).c_str() << endl;
	cout << "Handle       : " << handle << "  " << (( handle & 0xff000000 ) >> 24 ) << endl;

	// Prepare regular result
	handle_out = handle;
	feedback = IVIRadio::Types::Types::Feedback::DONE;
	IVIRadio::Types::Types::ErrorCodes errorCode = IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
	if ( updateElement == IVIRadio::Station::StationTypes::UpdateElement::UE_SEEK ) {

		if ( ( ( sourceType  != (uint32_t)IVIRadio::Types::Types::SourceType ::AMFM_FM  )   &&
			   ( sourceType  != (uint32_t)IVIRadio::Types::Types::SourceType ::DAB_DAB  ) ) ||
			   ( stationType != (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF )   ||
			   ( updateType  == IVIRadio::Types::Types::UpdateType::UT_ONCE             ) )  {

			feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
			cout << "Sorry, only calls with sourceType AMFM or DAB and stationType ST_UNDEF and " << endl;
			cout << "updateType UT_NONE or UT_NOTIFICATION allowed!" << endl;
			cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
			return;
		}
		else{
			m_MW->NotifyOnSeek ( updateType, sourceType, handle );
			return;
		}
	}
	else if ( updateElement == IVIRadio::Station::StationTypes::UpdateElement::UE_CURRENT_STATION ) {
		IVIRadio::Station::StationTypes::Station broadcast_current;
		IVIRadio::Types::Types::ErrorCodes errorCode = m_MW->getCurrentStationOfHMI( handle,  broadcast_current);
		if ( updateType != IVIRadio::Types::Types::UpdateType::UT_ONCE ){
			// current station request makes only sense with UT_ONCE
			feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
			cout << "Sorry, only calls with updateType == UT_ONCE allowed!" << endl;
			cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
			return;
		}
		else if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_NOSTATIONACTIVE ){
			cout << "Currently is no station active ..." << endl;
		}
		fireCurrentStationEvent(broadcast_current, handle, errorCode);
		return;
	}
	else if ( updateElement == IVIRadio::Station::StationTypes::UpdateElement::UE_STATION_LIST ) {
		IVIRadio::Station::StationTypes::StationList broadcast_list;
		if ( ( sourceType != (uint32_t)IVIRadio::Types::Types::SourceType::UNDEF_SOURCE    &&
			   sourceType != (uint32_t)IVIRadio::Types::Types::SourceType::AMFM_FM         &&
			   sourceType != (uint32_t)IVIRadio::Types::Types::SourceType::DAB_DAB        )||

		   ( sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::UNDEF_SOURCE   &&
		     ( IVIRadio::Station::StationTypes::StationType)stationType != IVIRadio::Station::StationTypes::StationType::ST_UNDEF ) )  {

			feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
			cout << " only sourcetypes AMFM_FM, DAB_DAB and UNDEF_SOURCE are allowed and " 			<< endl;
			cout << " for UNDEF_SOURCE only station type UNDEF_DEVICE is allowed!" 					<< endl;
			cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
			return;
		}
		if ( updateType == IVIRadio::Types::Types::UpdateType::UT_ONCE ) {
			broadcast_list = m_MW->GetStationList( updateElement, updateType, sourceType, stationType, handle );
				fireStationListEvent( broadcast_list, handle, errorCode );
				return;
		}
		else {
			m_MW->setListNotification( updateType, sourceType, handle );
			return;
		}
	}
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
}

void TunerStationIndividualStub::InternalThreadEntry_SendCurrentStation  () {

	while ( 1 ) {
		vector <uint32_t> handles;
		vector <IVIRadio::Station::StationTypes::Station> currStations;
		if ( m_MW->getCurrStation( handles, currStations ) ) {
			cout << "send a current station event..." << endl;
			IVIRadio::Station::StationTypes::Station currStation;
			uint32_t handle;
			auto it_currStation = currStations.cbegin();
			for ( auto it_handle = handles.cbegin(); it_handle != handles.cend(); it_handle++, it_currStation++)
				fireCurrentStationEvent( (*it_currStation), (*it_handle), IVIRadio::Types::Types::ErrorCodes::EC_NOERROR);
		}
		usleep(1000*25);
	}
}

