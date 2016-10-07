///////////////////////////////////////////////////////////
//  Middleware.cpp
//  Implementation of the Class Middleware
//  Created on:      16-Jul-2013 16:47:49
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Middleware.h"

using namespace std;

#define LOG( a, b ) m_TerminalIO->Log( a, b )


int sigterminate = 0;

Middleware::Middleware(){

	m_bSendAnnouncement 	= false;
	m_bFinishAnnouncement 	= false;
	m_runPipe 				= false;

	m_currAnnData = new currAnnouncementData;

	struct timeval tv;
	m_StationManagement = new StationManagement();
	m_FileIO			= FileIO::getInstance();
	m_TerminalIO 		= TerminalIO::getInstance();
	m_HMIList 			= new HMIList();
	// in future, the HMIs should be allocated once we initially get a request
	// from them. At the moment, we assume 3 HMIs.
	HMI *hmi1 = new HMI(0);
	HMI *hmi2 = new HMI(1);
	HMI *hmi3 = new HMI(2);
	m_HMIList->addHMI(hmi1);
	m_HMIList->addHMI(hmi2);
	m_HMIList->addHMI(hmi3);
	m_XMLReader  		= new XMLReader();
	//create tuner list and fill up with some tuner
	m_TunerList 	=  new TunerList();
	for (int i = 0; i < 3; i++) {
		m_TunerList->addFMTuner(new FMTuner(i));
	}
	for (int i = 0; i < 3; i++) {
		m_TunerList->addDABTuner(new DABTuner(i));
	}
	setupSignalHandling();

}

Middleware::~Middleware( ){
}

void Middleware::makePermanent(IVIRadio::Types::Types::StationSelector station, bool permanent, uint32_t handle){
	HMI  *hmi 	 	= m_HMIList  ->getHMIbyNumber( handle );
	LOG("Try to make station permanent", DEBUG);
	int index = 0;
	if ( (IVIRadio::Types::Types::DeviceType)station.deviceType == IVIRadio::Types::Types::DeviceType::AMFM ){
		index = station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY];
	}
	else {
		index = station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY];
	}
	m_FileIO->setPermanentFlagAMFM(index, permanent);
}

IVIRadio::Types::Types::ErrorCodes Middleware::seek(IVIRadio::Types::Types::DeviceType device,
		IVIRadio::Station::StationTypes::SeekMode seekMode, uint32_t handle,
		IVIRadio::Station::StationTypes::StationList &oStationList){

	HMI  *hmi 	 	= m_HMIList  ->getHMIbyNumber( handle );
	//get the tuner that is assigned to the current HMI; if no Tuner is currently assigned a new one will be assigned and
	//the SCAN jobs is starting from the beginning of the frequency band
	Tuner *assignedTuner = NULL;
	vector<Tuner*> possible_tuner;
	IVIRadio::Types::Types::ErrorCodes errorCode = IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
	if( seekMode == IVIRadio::Station::StationTypes::SeekMode::SM_AUTOSTORE  ) {
		// check tuner state
		// get free tuner to do backgroundscan
		Tuner *tuner =  m_TunerList->getFreeTuner( device );
		if ( tuner == NULL ){
			LOG("Sorry, no free tuner available.", DEBUG);
			return IVIRadio::Types::Types::ErrorCodes::EC_OUTOFRESSOURCES;
		}
		struct timeval tv;
		gettimeofday(&tv, NULL);
		//set tuner to scanning to signalize that it is not available anymore
		tuner->setState( TunerState::SCANNING );
		Seek *seek = new Seek( tuner, hmi, tv, device, seekMode);
		//continue job until it is finished
		while ( seek->continueJob() == false ) {
			if ( device == IVIRadio::Types::Types::DeviceType::DAB ){
				usleep( 500*25 );
			}
			else
				usleep( 1000*25 );
			m_broadcastSeekData = seek->getSeekData(); //write current seek progress to member to provide it the Stub
		}
		tuner->setState(TunerState::IDLE); 		//when job finished release the tune for other jobs
		//read station list from HMI and write it to a member after the seek to provide it the Stub
		m_CompleteAMFMList			= hmi->getCompleteListAMFM();
		m_CompleteDABList			= hmi->getCompleteListDAB();
		if ( device == IVIRadio::Types::Types::DeviceType::AMFM && hmi->getUpdateStationListNotificationAMFM()  == true ) {
			oStationList.deviceType  = (uint32_t)IVIRadio::Types::Types::DeviceType ::AMFM;
			oStationList.stationType = (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF;
			oStationList.stations    = hmi->getCompleteListAMFM();
		}
		else if (device == IVIRadio::Types::Types::DeviceType::DAB && hmi->getUpdateStationListNotificationDAB() == true) {
			oStationList.deviceType  = (uint32_t)IVIRadio::Types::Types::DeviceType ::DAB;
			oStationList.stationType = (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF;
			oStationList.stations    = hmi->getCompleteListDAB();
		}
		LOG("Job Seek ended...", DEBUG);
		m_TerminalIO->printStationListShort( oStationList );
		}
	else {
		LOG("Search for assigned tuner", DEBUG);

		Tuner* assignedTuner = getTunerAssignedToHMI( handle );
		//if currently assigned tuner does not support requested standard then deallocate ressource
		if ( assignedTuner != NULL && assignedTuner->getDeviceType() != device ){
			assignedTuner->free( hmi );
			assignedTuner = NULL;
		}
		//if currently no tuner is assigned because of deallocating the assigned tuner that only supports
		//non required standards or because there was no tuner assigned a new tuner will be assigned of the pool of available tuner
		if ( assignedTuner == NULL ){
			LOG("No tuner assigned to the current HMI yet so a new one will be assigned and start the SCAN from the beginning of the frequencyband.", DEBUG);
			assignedTuner = m_TunerList->getFreeTuner( device ); //search for free tuner in the tuner list that supports required standard
			assignedTuner->alloc( hmi ); //assign HMI to that Tuner
		}
		//if assigned tuner is still NULL here than the midleware is out of ressources and returns with an error code

		if( seekMode == IVIRadio::Station::StationTypes::SeekMode::SM_OFF ){
			//need to interrupt an autostore
		}
		else if(seekMode == IVIRadio::Station::StationTypes::SeekMode::SM_MAN_UP) {
			m_StationManagement->ManualUp( assignedTuner );
			hmi->setCurrentTunedStation( assignedTuner->getTunedStation() );
			return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
		}
		else if(seekMode == IVIRadio::Station::StationTypes::SeekMode::SM_MAN_DOWN) {
			m_StationManagement->ManualDown(assignedTuner);
			hmi->setCurrentTunedStation( assignedTuner->getTunedStation() );
		}
		else if(seekMode ==  IVIRadio::Station::StationTypes::SeekMode::SM_AUTO_UP){
			assignedTuner->setState(TunerState::TUNING);
			while ( m_StationManagement->AutoUp( assignedTuner, hmi ) == false ){
				usleep(1000*25);
				m_broadcastSeekData = m_StationManagement->getSeekData(); //write current seek progress to member to provide it the Stub
			}
			hmi->setCurrentTunedStation( assignedTuner->getTunedStation() );
			m_TerminalIO->printStation(assignedTuner->getTunedStation() );
		}
		else if(seekMode == IVIRadio::Station::StationTypes::SeekMode::SM_AUTO_DOWN){
			assignedTuner->setState(TunerState::TUNING);
			while ( m_StationManagement->AutoUp(assignedTuner, hmi) == false ){
				usleep(1000*25);
				m_StationManagement->AutoDown(assignedTuner, hmi);
			}
			hmi->setCurrentTunedStation( assignedTuner->getTunedStation() );
		}
	}
	return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
}

IVIRadio::Types::Types::Feedback Middleware::startTune( IVIRadio::Types::Types::StationSelector station, IVIRadio::Station::StationTypes::SelectionMode selectionMode, uint32_t handle )
{
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	//get the tuner that is assigned to the hmi
	Tuner *tuner = getTunerAssignedToHMI( handle );
	//organize device type of required station ; if device type undef then need to check station IDs
	//if device type of currently assigned tuner does not match to the device type of the current tune command
	//release the wrong tuner and assign a new one
	LOG("Check device type of assigned tuner ", DEBUG);
	IVIRadio::Types::Types::DeviceType devType;
	if ( m_TerminalIO->deviceTypeToName.at((uint32_t) station.deviceType ) == "AMFM" ){
		devType = IVIRadio::Types::Types::DeviceType::AMFM;
		LOG("Device Type: AMFM", DEBUG);
	}
	else if ( m_TerminalIO->deviceTypeToName.at((uint32_t) station.deviceType ) == "DAB" ){
		devType = IVIRadio::Types::Types::DeviceType::DAB;
		LOG("Device Type: DAB", DEBUG);
	}
	else if ( m_TerminalIO->deviceTypeToName.at((uint32_t) station.deviceType ) == "UNDEF_DEVICE" ) { //need to find a station of a standard to perform tune
		uint32_t key = station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexUndef::UNDEF_ID_KEY];
		//search for a station that is in the station lists and corresponds to the PI/SI Code
		IVIRadio::Station::StationTypes::Station y_station;
		if ( hmi->getStationToServiceIdentifier( key, y_station ) ) {
			//if a receivable station was found the device type needs to be
			if ( y_station.sel.deviceType == 1 ){ //AMFM
				devType = IVIRadio::Types::Types::DeviceType::AMFM;
			}
			else if ( y_station.sel.deviceType == 2 ){ //DAB
				devType = IVIRadio::Types::Types::DeviceType::DAB;
			}
		}
		else {
			return IVIRadio::Types::Types::Feedback::FAILURE;
		}
		station = y_station.sel;
	}
	//if there is currently a tuner assigned to the requesting client and the tuner does not support the correct standard the tuner gets deallocated
	if ( tuner != NULL && tuner->getDeviceType() != devType ){
		LOG("Need to free tuner, because station from other device type requested...", DEBUG);
		tuner->free( hmi );
		tuner = NULL;
	}
	//if tuner == NULL because of deallocating before or there wasn't assigned one yet then a new tuner will be assigned
	if ( tuner == NULL ) {//if currently no tuner is assigned to the hmi get a free one and assign it to the HMI
		LOG("Try to get a new tuner from front end pool...", DEBUG);
		//tuner = m_TunerList->getFreeTuner( station.deviceType );
		tuner = m_TunerList->getFreeTuner( devType );
		if (tuner != NULL)
			tuner->alloc( hmi );
	}
	//if no free tuner is available resources are all consumed and no tune is possible
	if ( tuner == NULL ){
		LOG("No free tuner available!!", WARNING);
		return IVIRadio::Types::Types::Feedback::FAILURE;
	}
	struct timeval tv;
	//create a job that effectively executes the tune to command
	StartTune *startTune = new StartTune( tuner, hmi, tv, station, selectionMode, handle );
	startTune->continueJob( );
	//m_Player->Play( tuner->getTunedStation( ) );
	return IVIRadio::Types::Types::Feedback::DONE;
}

IVIRadio::Types::Types::ErrorCodes Middleware::getCurrentStationOfHMI( uint32_t handle, IVIRadio::Station::StationTypes::Station &oStation )
{
	Tuner *assignedTuner = getTunerAssignedToHMI( handle );
	if ( assignedTuner == NULL ) {
		return IVIRadio::Types::Types::ErrorCodes::EC_NOSTATIONACTIVE;
	}
	oStation = assignedTuner->getTunedStation( );
	return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
}

Tuner* Middleware::getTunerAssignedToHMI( uint32_t handle ){
	LOG("Get assigned tuner of hmi", DEBUG);
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	Tuner *assignedTuner = NULL;
	//search for a possible tuner at first in the AMFM tuner list
	vector <Tuner*> possible_tuner = m_TunerList->getAMFMTuner();
	for (auto it = possible_tuner.cbegin(); it != possible_tuner.cend(); it++){
		if ( (*it)->getCurrentAssignment() != NULL ){
			if ( (*it)->getCurrentAssignment()->getHMIId() == hmi->getHMIId() ){
				assignedTuner = (*it);
			}
		}
	}
	//if no assigned AMFM tuner was found continue search in the dab tuner list
	if ( assignedTuner == NULL ){
		possible_tuner = m_TunerList->getDABTuner();
		for (auto it = possible_tuner.cbegin(); it != possible_tuner.cend(); it++){
			if ( (*it)->getCurrentAssignment() != NULL ){
				if ( (*it)->getCurrentAssignment()->getHMIId() == hmi->getHMIId() ){
					assignedTuner = (*it);
				}
			}
		}
	}
	return assignedTuner;
}

void Middleware::NotifyOnSeek( IVIRadio::Types::Types::UpdateType updateType, uint32_t sourceType, uint32_t handle ){

	HMI *hmi = m_HMIList->getHMIbyNumber( handle );

	if (updateType == IVIRadio::Types::Types::UpdateType::UT_NOTIFICATION) {
		if ((sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::AMFM_FM)) {
			hmi->setUpdateSeekNotificationAMFM(true);
		}
		else if ((sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::DAB_DAB)) {
			hmi->setUpdateSeekNotificationDAB(true);
		}
	}
	else{
		if ((sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::AMFM_FM)) {
			hmi->setUpdateSeekNotificationAMFM(false);
		}
		else if ((sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::DAB_DAB)) {
			hmi->setUpdateSeekNotificationDAB(false);
		}
	}
}

IVIRadio::Station::StationTypes::StationList Middleware::GetStationList( IVIRadio::Station::StationTypes::UpdateElement updateElement,
	       IVIRadio::Types::Types::UpdateType updateType, uint32_t sourceType, uint32_t stationType, uint32_t handle){
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	IVIRadio::Station::StationTypes::StationList broadcast_list;
	if (updateType == IVIRadio::Types::Types::UpdateType::UT_ONCE) {
		if (sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::UNDEF_SOURCE) {
			broadcast_list.deviceType  = (uint32_t)IVIRadio::Types::Types::DeviceType ::UNDEF_DEVICE;
			broadcast_list.stationType = (int32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF;
			broadcast_list.stations = hmi->getCompleteListUndef();
		}
		else if (sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::AMFM_FM) {
			broadcast_list.deviceType = (uint32_t)IVIRadio::Types::Types::DeviceType::AMFM;
			broadcast_list.stationType = stationType;
			if ((IVIRadio::Station::StationTypes::StationType)stationType ==
				IVIRadio::Station::StationTypes::StationType::ST_UNDEF) {
				broadcast_list.stations = hmi->getCompleteListAMFM();
			} else {
				broadcast_list.stations = m_FileIO->getFilteredAMFMStations((uint32_t)stationType);
			}
		}
		else if (sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::DAB_DAB) {
			broadcast_list.deviceType = (uint32_t)IVIRadio::Types::Types::DeviceType::DAB;
			broadcast_list.stationType = stationType;
			if ((IVIRadio::Station::StationTypes::StationType)stationType ==
				IVIRadio::Station::StationTypes::StationType::ST_UNDEF) {
				broadcast_list.stations = hmi->getCompleteListDAB();
			}
			else {
				broadcast_list.stations = m_FileIO->getFilteredDABStations((uint32_t)stationType);
			}
		}
	}
	return broadcast_list;
}

void Middleware::setListNotification ( IVIRadio::Types::Types::UpdateType updateType, uint32_t sourceType, uint32_t handle) {
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	if ( updateType == IVIRadio::Types::Types::UpdateType::UT_NOTIFICATION ) {
		if ( sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::AMFM_FM ) {
			hmi->setUpdateStationListNotificationAMFM(true);
		}
		else if ( sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::DAB_DAB ) {
			hmi->setUpdateStationListNotificationDAB(true);
		}
	}
	else if ( updateType == IVIRadio::Types::Types::UpdateType::UT_NONE ) {
		if ( sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::AMFM_FM ) {
			hmi->setUpdateStationListNotificationAMFM(false);
		}
		else if ( sourceType == (uint32_t)IVIRadio::Types::Types::SourceType::DAB_DAB ) {
			hmi->setUpdateStationListNotificationDAB(false);
		}
	}
}

bool Middleware::getSeekNotification( uint32_t handle, IVIRadio::Types::Types::DeviceType deviceType ) {
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	if ( deviceType == IVIRadio::Types::Types::DeviceType::DAB ){
		return hmi->getUpdateSeekNotificationDAB();
	}
	else
		return hmi->getUpdateSeekNotificationAMFM();
}

bool Middleware::getListNotification( uint32_t handle, IVIRadio::Types::Types::DeviceType deviceType ) {
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	if ( deviceType == IVIRadio::Types::Types::DeviceType::DAB ){
		return hmi->getUpdateStationListNotificationDAB();
	}
	else
		return hmi->getUpdateStationListNotificationAMFM();
}

IVIRadio::Types::Types::ErrorCodes Middleware::getComponentNotifications ( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService componentType,
		IVIRadio::Types::Types::arrayStationSelectors 										&arrayStationSel,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOptions 	&unifiedServiceOptions,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOptions 		&componentOptions, uint32_t handle ){

	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	vector <data_request_parameter> tmp;
	tmp = hmi->getRequests( componentType );
	for ( auto it = tmp.cbegin(); it != tmp.cend(); it++ ) {
		arrayStationSel .push_back( (*it).stationSelectors );
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption tmpUnifiedServiceOption;
		tmpUnifiedServiceOption.objectID 	= (*it).objectID;
		tmpUnifiedServiceOption.requestType = (*it).updateType;
		unifiedServiceOptions.push_back( tmpUnifiedServiceOption);
		componentOptions.push_back( (*it).serviceOptions   );
		m_TerminalIO->printSelectParamter(componentType, (*it).serviceOptions, 0);
	}
	return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
}

IVIRadio::Types::Types::ErrorCodes  Middleware::getData(
		IVIRadio::AdditionalService::AdditionalServiceTypes::DataService componentType,
		IVIRadio::Types::Types::StationSelectors stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedServiceOption,
		uint32_t handle,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption component_parameter,
		IVIRadio::AdditionalService::AdditionalServiceTypes::Data &data)
{
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	uint32_t serviceID;
	//find now the correct station identifier corresponding to the component ID; since the component ID should be unique
	//a station identifier should be matchable one to one to a component ID
	IVIRadio::Station::StationTypes::Station station;
	//check if updateType is UT_NOTIFICATION and safe request if it is so or delete request if updateType is UT_NONE if request is existing
	data_request_parameter requestParam;
	requestParam.dataFormat 		= IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat::DF_XML;
	requestParam.dataType   		= IVIRadio::AdditionalService::AdditionalServiceTypes::DataType::DT_BYTEBUFFER;
	requestParam.serviceOptions 	= component_parameter;
	requestParam.updateType 		= unifiedServiceOption.requestType;
	requestParam.stationSelectors 	= stationSelectors;
	requestParam.objectID			= unifiedServiceOption.objectID;
	requestParam.componentType 		= componentType;

	if ( unifiedServiceOption.requestType == IVIRadio::Types::Types::UpdateType::UT_NOTIFICATION ) {
		LOG("updateType == IVIRadio::Types::Types::UpdateType::UT_NOTIFICATION", INFO);
		hmi->addDataRequest( requestParam );
	}
	else if ( unifiedServiceOption.requestType == IVIRadio::Types::Types::UpdateType::UT_NONE ) {
		hmi->removeDataRequest( requestParam );
		if ( componentType == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_ANNOUNCEMENT ){
			for ( auto it = stationSelectors.cbegin(); it != stationSelectors.cend(); it++ ){
				IVIRadio::AdditionalService::AdditionalServiceTypes::Announcement announcement;
				announcement.stationSelector = (*it);
				for ( auto it = component_parameter.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options>().Type_Configurations.cbegin(); it != component_parameter.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options>().Type_Configurations.cend(); it++ ){
					announcement.type = (*it).type;
					//setCurrentAnnouncementData( announcement, handle );
					//setFinishAnnouncement( true );
					hmi->deleteActiveAnnouncement( announcement.stationSelector );
				}
			}
		}
		return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
	}
	else{
	}

	if ( componentType == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_ANNOUNCEMENT ){
		if ( unifiedServiceOption.requestType == IVIRadio::Types::Types::UpdateType::UT_NOTIFICATION ) {
			for ( auto it = component_parameter.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options>().Type_Configurations.cbegin(); it != component_parameter.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options>().Type_Configurations.cend(); it++ ){
				for ( auto it_stationsel = stationSelectors.cbegin(); it_stationsel != stationSelectors.cend(); it_stationsel++ ){
					hmi->setAnnouncementConfiguration( (*it).type, (*it).active, (*it).priority, (*it_stationsel), IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState::Available );
				}
			}
		}
		if ( unifiedServiceOption.requestType == IVIRadio::Types::Types::UpdateType::UT_NONE ) {
			for ( auto it = stationSelectors.cbegin(); it != stationSelectors.cend(); it++ ){
				hmi->deleteActiveAnnouncement( (*it) );
			}
		}
	}
	else if ( componentType == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_NO_SERVICE){
		return IVIRadio::Types::Types::ErrorCodes::EC_COMPONENTNOTSUPPORTED;
	}
	else if ( componentType == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_SUBTITLE ){
		if ( unifiedServiceOption.requestType == IVIRadio::Types::Types::UpdateType::UT_NOTIFICATION ) {
			string data = "/tmp/fifo";
			m_runPipe = true;
			pthread_create( &pipeHandling, NULL, InternalThreadEntryFunc_HandlePipeCommunication, this );
			return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
		}
		else if ( unifiedServiceOption.requestType == IVIRadio::Types::Types::UpdateType::UT_NONE ){
			m_runPipe = false;
			return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
		}
	}
	else{
		bool erg;

		//get requested data; filtering and stuff is done by the XMLReader
		CommonAPI::ByteBuffer buff;

		erg = m_XMLReader->getComponentData( stationSelectors, componentType, component_parameter, unifiedServiceOption.objectID, buff );

		data = buff;
		if ( erg )
			return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
		else{
			LOG("--> Found no data for the requested component type parameter", DEBUG);
			return IVIRadio::Types::Types::ErrorCodes::EC_NODATAAVAILABLE;
		}
	}
	return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
}

IVIRadio::Types::Types::ErrorCodes Middleware::abort(
		IVIRadio::AdditionalService::AdditionalServiceTypes::DataService componentType,
		IVIRadio::Types::Types::StationSelectors stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption unifiedServiceOption,
		uint32_t handle,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption component_parameter,
		IVIRadio::AdditionalService::AdditionalServiceTypes::Announcement &announcement
		){

	return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
}

IVIRadio::Types::Types::ErrorCodes Middleware::changeFunctionalityConfiguration( uint32_t handle, IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
			IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions functionalityOptions)
{
	//check if there is a functionality that is not yet supported in the POC
	//in that case the function returns with an error code
	//supported functionality types: HD, Following, InterfaceVersion, AvailableBand CountryVariant
	cout << "------------------------changeFunctionalityConfiguration----------------"  << endl;
	for ( auto it = functionalityTypes.cbegin(); it != functionalityTypes.cend(); it++ ){
		if ( (*it) != IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::HD 				&&
			 (*it) != IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AvailableBand 	&&
			 (*it) != IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CountryVariant 	&&
			 (*it) != IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::InterfaceVersion  &&
			 (*it) != IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CountryVariant	&&
			 (*it) != IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::Following 		){
			return IVIRadio::Types::Types::ErrorCodes::EC_FUNCTIONALITYNOTSUPPORTED;
		}
	}
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );

	m_TerminalIO->printFunctionalityTypesOptions( functionalityTypes, functionalityOptions);
	hmi->setConfigurations( functionalityTypes, functionalityOptions );
	return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
}

IVIRadio::Types::Types::ErrorCodes Middleware::requestFunctionalityConfiguration( uint32_t handle, IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
		IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet functionalityOptions,
						IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions& outFunctionalityOptions ){
	HMI *hmi = m_HMIList->getHMIbyNumber( handle );
	m_TerminalIO->printFunctionalityTypesOptionsGet( functionalityTypes, functionalityOptions );
	hmi->getConfigurations( functionalityTypes, functionalityOptions, outFunctionalityOptions);
	return IVIRadio::Types::Types::ErrorCodes::EC_NOERROR;
}

void Middleware::printActiveAnnouncements( int signum ) {
    map< uint32_t, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType > x;
    set<HMI *> myHMIList;
    myHMIList = m_HMIList->getHMIList();
    for (auto it2 = myHMIList.cbegin(); it2 != myHMIList.cend(); it2++) {
        HMI *hmi = (*it2);
        x = hmi->getActiveAnnouncements();
        if (x.size() == 0) {
            LOG("HMI " + to_string( hmi->getHMIId() ) + ": currently no active announcements.", INFO);
        }
        else {
            LOG("HMI " +  to_string(hmi->getHMIId()) + ": ", INFO);
            for (auto it = x.cbegin(); it != x.cend(); it++) {
                LOG("Station IDentifier: " + to_string( ( *it ).first ) + " , type " + m_TerminalIO->getAnnouncementType((*it).second) , INFO);
            }
        }
    }
}


void Middleware::sendAnnouncement()
{
    uint32_t handle, code, serviceID;
    set<HMI *> myHMIList;
    myHMIList = m_HMIList->getHMIList();
    LOG("Sending announcement information ..." , INFO);
    //ask for the unique ID_KEY of the station that shall provide announcements (need to the currently tuned one to actually send an announcement)
    IVIRadio::Types::Types::StationSelector stationSel;
    serviceID = m_TerminalIO->readNumber( 0, 25, "Enter unique ID_KEY (one of the currently tuned stations ...)", "");
    //get the station selector belonging to that
	if ( !getStationSelectorFromID ( serviceID , handle, stationSel) ) {
		LOG("could not find a matching station to that ID", INFO);
		return;
	}
    IVIRadio::AdditionalService::AdditionalServiceTypes::DataService compType = IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_ANNOUNCEMENT;

    IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType type = m_TerminalIO->enterAnnouncementType();
    IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState annState = m_TerminalIO->enterAnnouncementState();
    for (auto it2 = myHMIList.cbegin(); it2 != myHMIList.cend(); it2++) {
    	//change announcenement type for chosen announcement
    	bool bHmiregisteredAnnouncementType = (*it2)->changeAnnouncementType( annState, stationSel, type );
    	if ( bHmiregisteredAnnouncementType ) {
			//get Announcement Request registered for that HMI
			vector < data_request_parameter > annRequests = (*it2)->getRequests( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_ANNOUNCEMENT );
			//look in list if stationSel and announcement type are registered
			for (auto it_requests = annRequests.cbegin(); it_requests != annRequests.cend(); it_requests++ ) {
				//check for station selector in list of registered station selectors
				for ( auto it_stationsel = (*it_requests).stationSelectors.cbegin(); it_stationsel != (*it_requests).stationSelectors.cend(); it_stationsel++) {
					if ( (*it_stationsel).id[0] == stationSel.id[0] ) {
						IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations annConf = (*it_requests).serviceOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options>().Type_Configurations;
						for ( auto it_dataOptions = annConf.cbegin(); it_dataOptions != annConf.cend(); it_dataOptions++) {
							if ( (*it_dataOptions).type == type ) {
								IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates 	arrAnnStates;
								(*it2)->getAnnouncementStates( (*it_requests).stationSelectors , annConf, arrAnnStates);
								setCurrentAnnouncementData( ( *it2 )->getHMIId ( ), (*it_requests).stationSelectors, annConf, arrAnnStates  );
								m_bSendAnnouncement = true;
							}
						}
					}
				}
			}
    	}
    }
    return;
}

bool Middleware::getStationSelectorFromID ( uint32_t stationID, uint32_t handle, IVIRadio::Types::Types::StationSelector &station ){
	bool res = false;
	for ( auto it = m_CompleteDABList.cbegin(); it != m_CompleteDABList.cend(); it++ ){
		if ( stationID == (*it).sel.id[0] ){
			station = (*it).sel;
			res = true;
		}

	}
	for ( auto it = m_CompleteAMFMList.cbegin() ; it != m_CompleteAMFMList.cend() ; it++ ){
		if ( stationID == (*it).sel.id[0] ){
			station = (*it).sel;
			res = true;
		}
	}
	return res;
}

void Middleware::setCurrentAnnouncementData(uint32_t handle ,
		IVIRadio::Types::Types::StationSelectors 										stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations annConfigs,
		IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates 	arrAnnStates) {
	m_currAnnData->annConfigs 		= annConfigs;
	m_currAnnData->arrAnnStates 	= arrAnnStates;
	m_currAnnData->handle			= handle;
	m_currAnnData->stationSelectors = stationSelectors;
}

void Middleware::getCurrentAnnouncementData(uint32_t &handle,
		IVIRadio::Types::Types::StationSelectors 										&stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations &annConfigs,
		IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates 	&arrAnnStates){
	handle 				= m_currAnnData->handle;
	stationSelectors 	= m_currAnnData->stationSelectors;
	annConfigs 			= m_currAnnData->annConfigs;
	arrAnnStates 		= m_currAnnData->arrAnnStates;
}

/*
 * method checks which hmi has a runnning announcement with the given component ID
 * and send a finish signal if necessary
 */
void Middleware::sendAnnouncementFinished()
{
    IVIRadio::AdditionalService::AdditionalServiceTypes::Announcement announcement;
    uint32_t handle, code;
    IVIRadio::Station::StationTypes::StationList tunedStations;
    set<HMI *> myHMIList;
    printActiveAnnouncements( 1 ); //console out of all currently running announcement
    //prepare out parameter for broadcast
    IVIRadio::Types::Types::StationSelector stationSel;

    getStationSelectorFromID ( m_TerminalIO->readNumber( 0, 25, "Enter Station unique ID_KEY (of a station currently providing an announcement)", ""), handle, stationSel);

    announcement.stationSelector = stationSel;
    announcement.type 			= m_TerminalIO->enterAnnouncementType();
    //check every HMI if fulfills the requirements to receive a finishAnnouncement broadcast
    myHMIList = m_HMIList->getHMIList();
    for ( auto it2 = myHMIList.cbegin(); it2 != myHMIList.cend(); it2++ ) {
        HMI *hmi = (*it2);
		//check if that special announcement type is basically active
		if ( hmi->getAnnouncementConfigurationEnabled( announcement.type ) == IVIRadio::Types::Types::Activation::ACTIVE ) {
			//check if that component ID is currently active for that hmi
			if ( hmi->isActiveAnnouncement( announcement.stationSelector ) ) {
				handle = hmi->getHMIId();
				//implement version 2.0.1
				//setCurrentAnnouncementData( announcement, handle );
				setFinishAnnouncement( true );
				hmi->deleteActiveAnnouncement( announcement.stationSelector );
			} else {
				LOG( "HMI " + to_string(hmi->getHMIId()) + " does currently not have this kind of announcement.", WARNING );
			}
		} else {
			LOG( "HMI " + to_string(hmi->getHMIId()) + " has disabled this kind of announcement.", WARNING );
		}
    }
    LOG( "Sending announcement finished done", INFO );
}

void sigTermHandler(int sig, siginfo_t *siginfo, void *x)
{
    sigterminate++;
    cout << "SIGTERM received." << endl;
}

void Middleware::InternalThreadEntry_Interactive()
{
	while (!sigterminate) {
        unsigned int choice = 99;
        string menu = "\n============================================================================\n";
        menu += "Background interaction (the server keeps on running while in input dialog!):\n";
        menu += "============================================================================\n";
        menu += "0 exit program\n";
        menu += "1 send Announcement\n";
        menu += "2 send Announcement finished\n";
        menu += "3 print active announcements (no API!)\n";
        menu += "4 send following event\n";
        choice = m_TerminalIO->readNumber(0, 4, "Enter number", menu);

        switch(choice) {
            case 0:
                sigterminate++;
                exit(0);
                break;
            case 1:
                sendAnnouncement();
                break;
            case 2:
                sendAnnouncementFinished();
                break;
            case 3:
                printActiveAnnouncements(1);
                break;
            case 4:
            	sendFollowingEvent();
            default:
                fprintf(stderr, "Error, got unexpected choice %u\n", choice);
                break;
        }
    }
}

int Middleware::setupSignalHandling()
{
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(sigact));
    sigact.sa_sigaction = sigTermHandler;
    sigemptyset (&sigact.sa_mask);
    sigact.sa_flags = SA_SIGINFO;
    sigaction(SIGTERM, &sigact, NULL);
    sigaction(SIGINT, &sigact, NULL);
}

void Middleware::runLoop(){
	//start main thread which is waiting for terminal input; while main thread is running request from the clients are catched in the
	//IndividualStub and processed in the Middleware class; main thread will finish when user sends "0" from terminal
	pthread_create(&interactive, NULL, InternalThreadEntryFunc_Interactive, this);
	pthread_join( interactive , NULL );
	LOG("Exiting ..." , INFO );
}

void Middleware::sendFollowingEvent(){
	IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType tmp_ft = m_TerminalIO->enterFollowingType();
	IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet funcOptionsGet;
	IVIRadio::Configuration::ConfigurationOptionsGetter::FollowingOptionsGet follwingOptionsGet;
	IVIRadio::Configuration::ConfigurationOptionsGetter::FunctionalityOptionGet funcOptionGet;
	follwingOptionsGet.followingTypes.push_back(tmp_ft);
	funcOptionGet = follwingOptionsGet;
	funcOptionsGet.push_back( funcOptionGet );
	if ( tmp_ft != IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::DAB_FM &&
		 tmp_ft != IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::FM_INTERNAL ) {
		LOG("Sorry, ... PoC supports only DAB_FM and FM_INTERNAL Following...", ERROR );
		return;
	}
	set<HMI *> myHMIList;
	//check every HMI if fulfills the requirements to receive a following event
	myHMIList = m_HMIList->getHMIList();
	vector <IVIRadio::Station::StationTypes::Station> AFStations;
	IVIRadio::Station::StationTypes::Station currStation;
	vector <uint32_t> HMIIds_getEvent;
	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes funTypes;
	funTypes.push_back( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::Following );
	for ( auto it_hmi = myHMIList.cbegin(); it_hmi != myHMIList.cend(); it_hmi++ ) {

		IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions funtionalityOptions;
		(*it_hmi)->getConfigurations( funTypes, funcOptionsGet, funtionalityOptions );
		if ( funtionalityOptions[0].get<IVIRadio::Configuration::ConfigurationOptions::FollowingOptions>().activations[0] == IVIRadio::Types::Types::Activation::ACTIVE ){
			LOG("Following type is active so let's send an following event...", INFO);

			Tuner *assignedTuner = getTunerAssignedToHMI( (*it_hmi)->getHMIId() );

			if ( assignedTuner == NULL ) {
				LOG( "No tuner assigned to HMI " + to_string((*it_hmi)->getHMIId()), WARNING );
			}
			else {
				//search for alternative stations
				currStation = assignedTuner->getTunedStation( );
				string strCurrStationDeviceType = m_TerminalIO->getDeviceType((IVIRadio::Types::Types::DeviceType)currStation.sel.deviceType).c_str();
				LOG("Currently Tuned Station: " , DEBUG );
				cout << "Device Type: " << strCurrStationDeviceType << endl;
				uint32_t PiCode = 0;
				if ( strCurrStationDeviceType == "AMFM" ) {
					PiCode = currStation.sel.id[2];
					LOG( "PiCode     : " + to_string( PiCode ) , INFO );
					LOG( "Key        : " + to_string( currStation.flags ) , INFO);
				}
				else if ( strCurrStationDeviceType == "DAB" ){
					PiCode = currStation.sel.id[3];
					LOG( "PiCode     : " + to_string( PiCode ) , INFO );
					LOG( "Key        : " + to_string( currStation.flags ), INFO);
				}
				else
					PiCode = 0;
				LOG("Search for AF station in the available station lists... ", INFO);
				for ( auto it_stations = m_CompleteAMFMList.cbegin(); it_stations != m_CompleteAMFMList.cend(); it_stations++ ){
					LOG("PICode: " + to_string((*it_stations).sel.id[2]), INFO);
					if ( (*it_stations).sel.id[2] == PiCode ){

						if ( ( *it_stations ).sel.id[1] != currStation.sel.id[1] ){
							LOG("Found AMFM Station with the same PI Code", INFO);
							AFStations.push_back( ( *it_stations ) );
						}
					}
				}
				for ( auto it_stations_dab = m_CompleteDABList.cbegin(); it_stations_dab != m_CompleteDABList.cend(); it_stations_dab++ ){
					if ( (*it_stations_dab).sel.id[3] == PiCode ){
						if ( ( *it_stations_dab ).sel.id[1] != currStation.sel.id[1] ){
							LOG("Found DAB Station with the same PI Code", INFO);
							AFStations.push_back( ( *it_stations_dab ) );
						}
					}
				}
				//check if any alternative station is available
				if ( !AFStations.empty() ){
					//check if alternative station and current station fullfill FollowingType constraints
					//FM INTERNAL: both station need to be AMFM
					if ( tmp_ft == IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::FM_INTERNAL ) {
						if ( (IVIRadio::Types::Types::DeviceType)currStation.sel.deviceType == IVIRadio::Types::Types::DeviceType::AMFM ) {
							for ( auto it = AFStations.cbegin(); it != AFStations.cend(); it++ ) {
								if ( (IVIRadio::Types::Types::DeviceType)( *it ).sel.deviceType == IVIRadio::Types::Types::DeviceType::AMFM ){
									LOG("Found correct alternative station for FM_INTERNAL following....", INFO);
									LOG("Change currently tuned station to AF station...", INFO);
									( *it_hmi ) -> setCurrentTunedStation( *it );
									getTunerAssignedToHMI( (*it_hmi)->getHMIId() );
									struct timeval tv;
									StartTune *startTune = new StartTune( assignedTuner, (*it_hmi), tv, (*it).sel, IVIRadio::Station::StationTypes::SelectionMode::SM_LIST, (*it_hmi)->getHMIId() );
									startTune->continueJob( );
									( *it_hmi ) -> setCurrStation( true );
									HMIIds_getEvent.push_back( ( *it_hmi )->getHMIId() );
								}
							}
						}
					}
					else if ( tmp_ft == IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::DAB_FM ) {
						if ( (IVIRadio::Types::Types::DeviceType)currStation.sel.deviceType == IVIRadio::Types::Types::DeviceType::DAB ) {
							for ( auto it = AFStations.cbegin(); it != AFStations.cend(); it++ ) {
								bool bChanged = false;
								if ( (IVIRadio::Types::Types::DeviceType)( *it ).sel.deviceType == IVIRadio::Types::Types::DeviceType::AMFM ){
									LOG("Found correct alternative station for DAB_FM following....", INFO);
									LOG("change currently tuned station to AF station...", INFO);
									Tuner* tuner = m_TunerList->getFreeTuner( IVIRadio::Types::Types::DeviceType::AMFM ); //search for new AMFM tuner
									if ( tuner != NULL && !bChanged) {
										getTunerAssignedToHMI( (*it_hmi)->getHMIId() )->free( (*it_hmi) ); //release currently assigned DAB tuner
										( *it_hmi ) -> setCurrentTunedStation( *it );
										tuner -> alloc( *it_hmi );
										struct timeval tv;
										StartTune *startTune = new StartTune( tuner, (*it_hmi), tv, (*it).sel, IVIRadio::Station::StationTypes::SelectionMode::SM_LIST, (*it_hmi)->getHMIId() );
										startTune->continueJob( );
										( *it_hmi ) -> setCurrStation( true );
										HMIIds_getEvent.push_back( ( *it_hmi )->getHMIId() );
										bChanged = true;
										//bSendEvent = true;
									}
									else if ( bChanged ){
										LOG("already changed station...", INFO);
									}
									else
										LOG("No AMFM tuner available -> cannot execute following DAB->AMFM", INFO);
								}
							}
						}
					}
				}
			}

		}
		else {
			LOG("Sorry desired Following type is NOT activated for HMI " + to_string((*it_hmi)->getHMIId()) , WARNING);
		}
	}
}

void Middleware::InternalThreadEntry_HandlePipeCommunication(){
	mkfifo("/tmp/fifo", S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

	int num, fifo;
	if ((fifo = open("/tmp/fifo", O_WRONLY)) < 0) {
		printf("%s\n", strerror(errno));
		return;
	}
	string phrase = "1860\n";
	int i = 0;

	while ( m_runPipe ) {
		sleep(1);
		phrase = phrase + " " + to_string(i);
		if ((num= write( fifo, phrase.c_str() , phrase.length() + 1 ) ) < 0) {
			printf("ERROR: %s\n", strerror(errno));
			m_runPipe = false;
		}
		i++;
	}
	close(fifo);
}

bool Middleware::getCurrStation( vector<uint32_t>& handle, vector<IVIRadio::Station::StationTypes::Station>& station ){
	bool bTmp = false;
	set<HMI *> myHMIList = m_HMIList->getHMIList();
	for ( auto it = myHMIList.cbegin(); it != myHMIList.cend(); it++ ){
		if ( ( *it ) -> getCurrStationChanged() ){
			uint32_t tmp_handle = ( *it ) -> getHMIId();
			handle .push_back (tmp_handle);
			station.push_back ( ( *it ) -> getCurrentTunedStation() );
			( *it ) -> setCurrStation( false );
			bTmp = true;
		}
	}
	if ( bTmp )
		return true;
	return false;
}
