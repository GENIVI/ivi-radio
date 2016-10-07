#include "includes/Client.h"

#define LOG(a, b) m_terminalIO->Log(a, b)

Client::Client( int id ){

	m_pipeActive 	= false;
	m_hmiId	 		= id;
	m_currentJobId 	= 0;
	m_terminalIO 	= TerminalIO::getInstance();

	//load Common API runtime and create a factory to build proxys later
	runtime = CommonAPI::Runtime::load();
	factory = runtime->createFactory();

	//build proxy for the station management interface
	proxy_TunerStation = factory->buildProxy< IVIRadio::Station::StationProxy >("local:TunerStation.TunerStation:TunerStation.Instance1");

	//subscribe the client on all the possible incoming events from the additional service interface
	//and delegate them to the appropriate method
	proxy_TunerStation->getSeekEvent().subscribe(&seekCallback);
	proxy_TunerStation->getCurrentStationEvent().subscribe(&currentStationCallback);
	proxy_TunerStation->getStationListEvent().subscribe(&stationListCallback);

	//build proxy for the additional service interface
	proxy_AdditionalService = factory->buildProxy< IVIRadio::AdditionalService::AdditionalServiceProxy >("local:TunerAdditionalService.TunerAdditionalService:TunerAdditionalService.Instance2");

	//subscribe the client on all the possible incoming events from the additional service interface
	//and delegate them to the appropriate method
	proxy_AdditionalService->getAnnouncementEvent().subscribe(announcementEventCallback);
	//proxy_AdditionalService->getAnnouncementFinishedEvent().subscribe(announcementFinishedEventCallback);
	proxy_AdditionalService->getDataEvent().subscribe(DataEventCallback);
	proxy_AdditionalService->getSubscribedServiceOptionsEvent().subscribe(SubscribedServiceOptionsEventCallback);

	//build proxy for the additional service interface
	proxy_Configuration = factory->buildProxy< IVIRadio::Configuration::ConfigurationProxy >("local:TunerConfiguration.TunerConfiguration:TunerConfiguration.Instance3");

	//subscribe the client on all the possible incoming events from the additional service interface
	//and delegate them to the appropriate method
	proxy_Configuration->getFunctionalityConfigurationEvent().subscribe(functionalityConfigurationEventCallback);
}

Client::~Client(){

}

Client *Client::_instance = NULL;

Client *Client::getInstance( int id )
{
    if (_instance == NULL) {
        _instance = new Client( id );
    }
    return _instance;
}

void Client::mergeLists(const IVIRadio::Station::StationTypes::StationList& changes)
{
	IVIRadio::Station::StationTypes::StationList *currentList;

    if (( IVIRadio::Types::Types::DeviceType )changes.deviceType == IVIRadio::Types::Types::DeviceType::AMFM)
    {
        currentList = &m_stationListAMFM;
    }
    else if ((IVIRadio::Types::Types::DeviceType)changes.deviceType == IVIRadio::Types::Types::DeviceType::DAB)
    {
        currentList = &m_stationListDAB;
    }
    else
    {
        return;
    }

    if (changes.stations.size() == 0) {
        return;
    }
    if (!(changes.stations[0].stationType & (uint32_t)IVIRadio::Station::StationTypes::StationType::ST_CHANGED)) {
        return;
    }

    for (auto it = changes.stations.cbegin(); it != changes.stations.cend(); it++) {
        IVIRadio::Station::StationTypes::Station station;
        station = (*it);
        station.stationType &= ~((uint32_t)IVIRadio::Station::StationTypes::StationType::ST_CHANGED);
        int found = 0;
        for (auto it2 = currentList->stations.begin(); it2 != currentList->stations.end(); it2++) {
            if ((IVIRadio::Types::Types::DeviceType)changes.deviceType ==
                IVIRadio::Types::Types::DeviceType::AMFM) {
                if (station.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] ==
                    (*it2).sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY]) {
                    found++;
                    (*it2) = station;
                    break;
                }
            } else if ((IVIRadio::Types::Types::DeviceType)changes.deviceType ==
                IVIRadio::Types::Types::DeviceType::DAB) {
                if (station.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] ==
                    (*it2).sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY]) {
                    found++;
                    (*it2) = station;
                    break;
                }
            }
        }
        if (!found) {
            currentList->stations.push_back(station);
        }
    }
}

void Client::ConOutReturnFromMiddleware(uint32_t handle_out, CommonAPI::CallStatus callStatus, IVIRadio::Types::Types::Feedback feedback, string method ) {
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"	, INFO);
	LOG("Returned from TunerStation." + method + "( ) ..."    						   	, INFO);
	LOG("CallStatus: " + m_terminalIO->getCallStatus(callStatus)					   	, INFO);
	LOG("Handle_out: " + to_string(handle_out)											, INFO);
	LOG("Feedback  : " + m_terminalIO->getFeedback(feedback)		 					, INFO);
	LOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" , INFO);
}

void Client::startTune(std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy)
{
    IVIRadio::Types::Types::StationSelector station;
    IVIRadio::Station::StationTypes::SelectionMode selectionMode;
    uint32_t handle, handle_out = 0;
    CommonAPI::CallStatus callStatus = CommonAPI::CallStatus::NOT_AVAILABLE;
    IVIRadio::Types::Types::Feedback feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
    try {
        m_terminalIO->enterStartTuneParameters(station, selectionMode, m_stationListAMFM, m_stationListDAB, m_stationListUndef, handle);
    } catch(exception &e) {
    	LOG( "Sorry, selection from an empty station list is not possible."		, WARNING );
    	LOG( "To fetch correct list, execute 'seek' for autostore scan, then"	, WARNING );
    	LOG( "retrieve the list using 'controlUpdate'." 						, WARNING );
        return;
    }
    LOG( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>", INFO );
    LOG( "Calling TunerStation.startTune( ) ...", INFO );
    m_terminalIO->printStationSelector(station);
    LOG( "SelectionMode: " + m_terminalIO->getSelectionMode( selectionMode ), INFO );
    LOG( "Handle	   : " + to_string( handle ), INFO );
    proxy->startTune( station, selectionMode, m_hmiId, callStatus, handle_out, feedback );
    ConOutReturnFromMiddleware( handle_out, callStatus , feedback , "startTune()" );
}

void Client::abortTune(std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy)
{
    IVIRadio::Types::Types::DeviceType device;
    uint32_t handle_out = 0;
    CommonAPI::CallStatus callStatus 		  	= CommonAPI ::CallStatus::NOT_AVAILABLE;
    IVIRadio::Types::Types::Feedback feedback 	= IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
    device = m_terminalIO->enterDeviceType();
    LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"	, INFO);
    LOG("Calling TunerStation.abortTune( ) ..."											, INFO);
    LOG("DeviceType: " + m_terminalIO->getDeviceType((IVIRadio::Types::Types::DeviceType)device), INFO);
    LOG("Handle: " + to_string(m_hmiId)	, INFO);
    proxy->abortTune(device, m_hmiId, callStatus, handle_out, feedback);
	ConOutReturnFromMiddleware( handle_out, callStatus , feedback , "abortTune");
}

void Client::seek(std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy)
{
	//create variables for the seek method call and initialize them with dummy values
    IVIRadio::Types::Types::DeviceType device = IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE;
    IVIRadio::Station::StationTypes::SeekMode seekMode = IVIRadio::Station::StationTypes::SeekMode  ::SM_AUTOSTORE;
    IVIRadio::Types::Types::Feedback feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;  //out parameter
    CommonAPI::CallStatus callStatus = CommonAPI::CallStatus::NOT_AVAILABLE;
    uint8_t  genre  	= 1;
    uint32_t handle_out = 0;  //out parameter
    IVIRadio::Types::Types::UInt32s flags;
    flags.push_back(1);
    //get user input for the parameters that are passed to the seek function
    m_terminalIO->enterSeekParameters(device, seekMode, genre, flags);
    LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>", INFO);
    LOG("Calling TunerStation.seek( ) ...", INFO);
    LOG("DeviceType: " + m_terminalIO->getDeviceType((IVIRadio::Types::Types::DeviceType)device  ), INFO);
    LOG("SeekMode  : " + m_terminalIO->getSeekMode  ((IVIRadio::Station::StationTypes::SeekMode  )seekMode), INFO);
    LOG("Genre     : " + genre, INFO);
    LOG("Handle    : " + to_string(m_hmiId), INFO);
    LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>", INFO);
    proxy_TunerStation->seek(device, seekMode, genre, flags, m_hmiId, callStatus, handle_out, feedback);
    ConOutReturnFromMiddleware( handle_out, callStatus , feedback , "seek");
}

void Client::makePermanent(std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy)
{
    IVIRadio::Types::Types::StationSelector station;
    bool permanent;
    CommonAPI::CallStatus callStatus = CommonAPI::CallStatus::NOT_AVAILABLE;
    uint32_t handle_out = 0;
    IVIRadio::Types::Types::Feedback feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
    try {
        m_terminalIO->enterMakePermanentParameters( station, permanent, m_stationListAMFM, m_stationListDAB, m_stationListUndef);//, m_hmiId );
    } catch(exception &e) {
    	LOG("Sorry, selection from an empty station list is not possible." 	, WARNING);
    	LOG("To fetch correct list, execute 'seek' for autostore scan, then", WARNING);
    	LOG("retrieve the list using 'controlUpdate'." 						, WARNING);
        return;
    }
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"	, INFO);
	LOG("Calling TunerStation.makePermanent( ) ..." 									, INFO);
    m_terminalIO->printStationSelector(station);
	LOG("Permanent: " + m_terminalIO->getPermanent(permanent)			 				, INFO);
	LOG("Handle   : " + to_string(m_hmiId)												, INFO);
    proxy->makePermanent(station, permanent, m_hmiId, callStatus, handle_out, feedback);
    ConOutReturnFromMiddleware( handle_out, callStatus , feedback , "makePermanent");
}

void Client::controlUpdate(std::shared_ptr<IVIRadio::Station::StationProxy<> >& proxy)
{
    IVIRadio::Station::StationTypes::UpdateElement updateElement;
    IVIRadio::Types::Types::UpdateType updateType = IVIRadio::Types::Types::UpdateType::UT_NONE;
    uint32_t stationType 	= 0, handle_out = 0, sourceType 	= 0;
    CommonAPI::CallStatus callStatus = CommonAPI::CallStatus::NOT_AVAILABLE;
    IVIRadio::Types::Types::Feedback feedback = IVIRadio::Types::Types::Feedback::NOT_APPLICABLE;
    m_terminalIO->enterControlUpdateParameters(updateElement, updateType, sourceType, stationType);//, m_hmiId);
    LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" 								, INFO);
    LOG("Calling TunerStation.controlUpdate( ) ..." 																	, INFO);
    LOG("UpdateElement: " + m_terminalIO->getUpdateElement(updateElement) 												, INFO);
	LOG("UpdateType   : " + m_terminalIO->getUpdateType(updateType) 													, INFO);
	LOG("SourceType   : " + m_terminalIO->getSourceType((IVIRadio::Types::Types::SourceType)sourceType) 				, INFO);
	LOG("StationType  : " + m_terminalIO->getStationType((IVIRadio::Station::StationTypes::StationType)stationType), INFO);
	LOG("Handle		  : " + to_string(m_hmiId) 																			, INFO);
	proxy->controlUpdate(updateElement, updateType, sourceType, stationType, m_hmiId, callStatus, handle_out, feedback);
    ConOutReturnFromMiddleware( handle_out, callStatus , feedback , "controlUpdate");
}

// end of station management
//
// begin of additional service

bool Client::getStationSelectorFromID ( uint32_t stationID, IVIRadio::Types::Types::StationSelector &station ){
	bool res = false;
	for ( auto it = m_stationListAMFM.stations.cbegin(); it != m_stationListAMFM.stations.cend(); it++ ){
		if ( stationID == (*it).sel.id[0] ){
			station = (*it).sel;
			res = true;
		}
	}
	for ( auto it = m_stationListDAB.stations.cbegin() ; it != m_stationListDAB.stations.cend() ; it++ ){
		if ( stationID == (*it).sel.id[0] ){
			station = (*it).sel;
			res = true;
		}
	}
	return res;
}

void Client::requestSubscribedServiceOptions(std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy){
    uint32_t handle_out = 0;
	CommonAPI ::CallStatus 				callStatus 	= CommonAPI::CallStatus::NOT_AVAILABLE;
    IVIRadio::Types::Types::Feedback 	feedback 	= IVIRadio ::Types     ::Types::Feedback::NOT_APPLICABLE;
    IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService = m_terminalIO->enterComponentType();
	proxy->requestSubscribedServiceOptions( dataService, m_hmiId, callStatus, handle_out, feedback );
}

void Client::requestDataService( std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy )
{
	LOG("Only EPG, Journaline, Announcement and Subtitle are implemented right now. All others will be refused...", INFO);
	IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService = m_terminalIO->enterComponentType();
	LOG("Choosen ComponentType: " + m_terminalIO->getComponentType( dataService ) , INFO);
	uint32_t handle_out = 0;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption 	unifiedServiceOption;
    IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption 		dataServiceOption;
    CommonAPI ::CallStatus 				callStatus 	= CommonAPI::CallStatus::NOT_AVAILABLE;
    IVIRadio::Types::Types::Feedback 	feedback 	= IVIRadio ::Types     ::Types::Feedback::NOT_APPLICABLE;
    vector<uint32_t> list;
    //for ( auto it = m_activeAnnouncements.cbegin(); it != m_activeAnnouncements.cend(); it++ ) {
    //    list.push_back((*it).first);
    //}
	m_terminalIO->printStationListShortSelective( m_stationListAMFM, dataService );  //print AMFM list to help to select componentIDs
	m_terminalIO->printStationListShortSelective( m_stationListDAB , dataService );  //print DAB  list to help to select componentIDs
	IVIRadio::Types::Types::StationSelectors stationSelectors;
	IVIRadio::Types::Types::StationSelector  station;
	uint32_t stationID = 0;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::No_Options no_options;
	while ( stationID != 100 ){ //read multiple component ID's until user enters 0
		stationID = m_terminalIO->readNumber(0, 100, "Enter Station ID, 100 = Exit", "");
		if ( getStationSelectorFromID ( stationID, station ) )
			stationSelectors.push_back( station );
	}
    unifiedServiceOption.requestType 	= m_terminalIO->enterUpdateType();
    unifiedServiceOption.objectID 		= 1;
	if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_EPG ){
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::EPG_Options EPGPar;
		EPGPar.Start_Date_Time  			= "dummy time";
		unifiedServiceOption.objectID 		= m_terminalIO->readNumber	( 0, 2 , "Enter number", "EPG Event ID ! Zero means don care ");
		EPGPar.Genre 						= m_terminalIO->getGenre	( m_terminalIO->enterGenre() );
		EPGPar.End_Date_Time 				= "dummy time";
		dataServiceOption 					= EPGPar;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_JOURNALINE){
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Journaline_Options JournalinePar;
		JournalinePar.Entry_Object 		= m_terminalIO->readBoolean("Is it the entry object?");
		unifiedServiceOption.objectID 	= m_terminalIO->readNumber( 0, 5 , "Enter number", "Enter ID of Journaline Object");
		dataServiceOption 		= JournalinePar;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_SUBTITLE ){
		unifiedServiceOption.objectID = m_terminalIO->readNumber(0, 2 , "Enter Subtitle ID", "won be considered");
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Subtitle_Options SubtitlePar;
		int tmp  = m_terminalIO->readNumber(0, 2 , "Enter number", "1 = ger ; others are not supported");
		IVIRadio::AdditionalService::AdditionalServiceTypes::Language language;
		language.Name = "ger";
		if ( tmp == 1 ){
			SubtitlePar.Languages.push_back( language );
		}
		else
			SubtitlePar.Languages.push_back( language );
		dataServiceOption 	= SubtitlePar;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_ANNOUNCEMENT ){
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options dummy;
		LOG("Enter Configuration for Announcements:", INFO);
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options annoucement_options;
		IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations annTypeConfigurations;
		if ( unifiedServiceOption.requestType == IVIRadio::Types::Types::UpdateType::UT_NOTIFICATION ){
			while ( m_terminalIO->readNumber(0, 1 ,"Another AnnouncementType? (Enter 0 for exit)") ){
				IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfiguration annTypeConfiguration;
				annTypeConfiguration.type 		= m_terminalIO->enterAnnouncementType( );
				annTypeConfiguration.active 	= m_terminalIO->enterActivation( );
				annTypeConfiguration.priority 	= m_terminalIO->readNumber( 0, 10, "Enter priority of AnnouncementType:" );
				annTypeConfigurations.push_back(annTypeConfiguration);
			}
		}
		else if ( unifiedServiceOption.requestType == IVIRadio::Types::Types::UpdateType::UT_NONE ){
			LOG( "Enter Announcement Types which should be finished", INFO);
			while ( m_terminalIO->readNumber(0, 1 ,"Another AnnouncementType? (Enter 0 for exit)") ){
				IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfiguration annTypeConfiguration;
				annTypeConfiguration.type 		= m_terminalIO->enterAnnouncementType( );
				annTypeConfiguration.active 	= IVIRadio::Types::Types::Activation::INACTIVE;
				annTypeConfiguration.priority 	= 0;
				annTypeConfigurations.push_back(annTypeConfiguration);
			}
		}
		dummy.Type_Configurations 	= annTypeConfigurations;
		dataServiceOption 			= dummy;
	}
	else {
		LOG("No other Component Types than Announcement, EPG, Journaline and Subtitle are currently supported", WARNING);
		return;
	}
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" , INFO);
	LOG("Calling TunerAdditionalServices.selectComponent( ) ..."  						, INFO);
	LOG("Handle      : " + to_string(m_hmiId)											, INFO);
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" , INFO);
	proxy->requestDataService( dataService, stationSelectors , unifiedServiceOption, dataServiceOption, m_hmiId  , callStatus, handle_out, feedback );
	ConOutReturnFromMiddleware	( handle_out , callStatus, feedback, "selectComponent");
}

void Client::abort( std::shared_ptr<IVIRadio::AdditionalService::AdditionalServiceProxy<> >& proxy ) {

	IVIRadio::AdditionalService::AdditionalServiceTypes::DataService 					dataService = m_terminalIO->enterComponentType();
	IVIRadio::Types::Types::StationSelectors 											stationSelectors;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption 	unifiedOptions;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption 		dataServiceOption;
	uint32_t handleOut = 0;
	CommonAPI ::CallStatus 				callStatus 	= CommonAPI::CallStatus::NOT_AVAILABLE;
	IVIRadio::Types::Types::Feedback 	feedback 	= IVIRadio ::Types     ::Types::Feedback::NOT_APPLICABLE;
	IVIRadio::Types::Types::StationSelector tmp;
	getStationSelectorFromID(m_terminalIO->readNumber(0,  25, "Enter Station  ID"), tmp);
	stationSelectors.push_back( tmp );
	unifiedOptions.objectID 	= 0;
	unifiedOptions.requestType 	= IVIRadio::Types::Types::UpdateType::UT_NONE;
	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfiguration annConf;
	IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options annOptions;
	annConf.type 		= m_terminalIO->enterAnnouncementType();
	annConf.active 		= IVIRadio::Types::Types::Activation::ACTIVE;
	annConf.priority 	= 1;
	annOptions.Type_Configurations.push_back(annConf);
	dataServiceOption = annOptions;
	proxy->abort( dataService, stationSelectors, unifiedOptions, dataServiceOption, m_hmiId, callStatus, handleOut, feedback );
}

//end of additional services
//
//begin of configuration

void Client::changeFunctionalityConfiguration ( std::shared_ptr<IVIRadio::Configuration::ConfigurationProxy<> >&proxy ){
	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes;
	IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions functionalityOptions;
	uint32_t handle_out = 0;
	IVIRadio::Types::Types::Feedback 	feedback;
	CommonAPI ::CallStatus 				callStatus = CommonAPI::CallStatus::NOT_AVAILABLE;
	functionalityOptions = m_terminalIO->enterFunctionalityOptions( functionalityTypes );
	m_terminalIO->printFunctionalityTypesOptions	( functionalityTypes, functionalityOptions );
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" , INFO);
	LOG("Calling TunerAdditionalServices.changeFunctionalityConfiguration( ) ..."  		, INFO);
	LOG("Handle      : " + to_string(m_hmiId)											, INFO);
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" , INFO);
	proxy->changeFunctionalityConfiguration	( functionalityTypes, functionalityOptions, m_hmiId  , callStatus, handle_out, feedback  );
	ConOutReturnFromMiddleware				( handle_out 		, callStatus 		  , feedback, "changeFunctionalityConfiguration");
}

void Client::requestFunctionalityConfiguration ( std::shared_ptr<IVIRadio::Configuration::ConfigurationProxy<> >&proxy ){
	IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes 		functionalityTypes;
	uint32_t handle_out = 0;
	IVIRadio::Types::Types::Feedback 	feedback;
	CommonAPI::CallStatus 				callStatus = CommonAPI::CallStatus::NOT_AVAILABLE;
	IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet requestOptions;
	requestOptions = m_terminalIO->enterFunctionalityOptionsGet ( functionalityTypes );
	m_terminalIO->printFunctionalityTypesOptionsGet				( functionalityTypes, requestOptions );
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" , INFO);
	LOG("Calling TunerAdditionalServices.requestFunctionalityConfiguration( ) ..." 		, INFO);
	LOG("Handle      : " + to_string(m_hmiId)											, INFO);
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" , INFO);
	//proxy->requestFunctionalityConfiguration( functionalityTypes, requestOptions, handle  , callStatus, handle_out, feedback  );
	proxy->requestFunctionalityConfiguration( functionalityTypes, requestOptions, m_hmiId  , callStatus, handle_out, feedback  );
	ConOutReturnFromMiddleware				( handle_out 		, callStatus    , feedback, "changeFunctionalityConfiguration");
}

void Client::loop(){

	while (true) {
		unsigned int choice = 99;
		string menu = "\n0 exit\n";
		menu += "1  startTune\n";
		menu += "2  abortTune\n";
		menu += "3  seek\n";
		menu += "4  makePermanent\n";
		menu += "5  controlUpdate\n";
		menu += "6  requestSubscribedServiceOptions\n";
		menu += "8  abort DataService\n";
		menu += "9  requestDataService\n";
		menu += "11 changeFunctionalityConfiguration\n";
		menu += "12 requestFunctionalityConfiguration\n";

		choice = m_terminalIO->readNumber(0, 12, "Enter number", menu);

		switch(choice) {
			case 0:
				LOG( "Exiting ...", INFO);
				exit(0);
			case 1:
				startTune( proxy_TunerStation );
				break;
			case 2:
				abortTune( proxy_TunerStation );
				break;
			case 3:
				seek( proxy_TunerStation );
				break;
			case 4:
				makePermanent( proxy_TunerStation );
				break;
			case 5:
				controlUpdate( proxy_TunerStation );
				break;
			case 6:
				requestSubscribedServiceOptions( proxy_AdditionalService );
				break;
			case 8:
				abort( proxy_AdditionalService );
				break;
			case 9:
				requestDataService( proxy_AdditionalService );
				break;
			case 11:
				changeFunctionalityConfiguration( proxy_Configuration );
				break;
			case 12:
				requestFunctionalityConfiguration( proxy_Configuration );
				break;
			default:
				LOG("Error, got unexpected choice " + to_string( choice ), ERROR);
				//fprintf(stderr, "Error, got unexpected choice %u\n", choice);
				exit(1);
		}
	}
}

bool Client::ReceivedCallback( string sCallbackName, uint32_t handle){
	LOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"	, INFO);
	LOG("Received " + sCallbackName + "( ) ..." 										, INFO);
	LOG("Handle:  " + to_string( handle ) 												, INFO);
	if ( handle != m_hmiId ) {
		LOG("Ignored since it is not for us." 											, INFO);
		LOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<", INFO);
		return false;
	}
	return true;
}

bool Client::SeekCallbackClient(IVIRadio::Station::StationTypes::SeekData seekData, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode){
	if (!ReceivedCallback( "seekCallback", handle) )
		return false;
	LOG("Data: " + to_string(seekData.data)												, INFO);
	LOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"	, INFO);
	return true;
}

bool Client::CurrentStationCallbackClient(IVIRadio::Station::StationTypes::Station current, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode){
	if (!ReceivedCallback( "currentStationCallback", handle) )
		return false;
	if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_NOERROR ) {
		m_terminalIO->printStation(current);
	}
	else if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_NOSTATIONACTIVE ) {
		LOG("currently is no station active ... ", INFO);
	}
	else {
		LOG("some other not expected error occurs ... ", INFO);
	}
	LOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<", INFO);
	return true;
}

bool Client::StationListCallbackClient( IVIRadio::Station::StationTypes::StationList list, uint32_t handle, IVIRadio::Types::Types::ErrorCodes errorCode ){
	int j = 0;
	if (!ReceivedCallback( "stationListCallback", handle) )
		return false;
	LOG("DeviceType : " +  m_terminalIO->getDeviceType ((IVIRadio::Types::Types::DeviceType )list.deviceType ), INFO);
	LOG("StationType: " +  m_terminalIO->getStationType((IVIRadio::Station::StationTypes::StationType)list.stationType), INFO);;
	LOG("--------------------------------------------------------------------------------", INFO);
    for (auto st = list.stations.cbegin(); st != list.stations.cend(); ++st, j++) {
    	LOG("Station :" + to_string(j), INFO);
    	m_terminalIO->printStation(*st);
        LOG("--------------------------------------------------------------------------------", INFO);
    }
    if ((IVIRadio::Types::Types::DeviceType)list.deviceType ==
        IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE) {
    	LOG("No. Stationname", INFO);
    } else {
    	LOG("No. [RPAC] Frequency  Stationname", INFO);
    }
    m_terminalIO->printStationListShort(list);
    LOG("--------------------------------------------------------------------------------", INFO);
    // store the list for later use
    // problem: we don't know whether this is an update list other than by handle
    // here the new incoming list always overwrites the old list without any restrictions
	LOG("Storing list", INFO);
	switch((IVIRadio::Types::Types::DeviceType)list.deviceType) {
		case IVIRadio::Types::Types::DeviceType::AMFM:
			m_stationListAMFM 	= list;
			break;
		case IVIRadio::Types::Types::DeviceType::DAB:
			m_stationListDAB 	= list;
			break;
		case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
			m_stationListUndef 	= list;
			break;
		default:
			LOG("Cannot handle deviceType", ERROR);
			break;
	}
    LOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<", INFO);
    return true;
}

bool Client::AnnouncementEventCallbackClient(
		IVIRadio::Types::Types::StationSelectors stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations announcementConfigurations,
		IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates 	announcementStates,
		const uint32_t& handle, IVIRadio::Types::Types::ErrorCodes errorCode  )
{
	if (!ReceivedCallback( "announcementEventCallback", handle) )
			return false;
	auto it_AnnStates = announcementStates.cbegin();
	for ( auto it_stSel = stationSelectors.cbegin(); it_stSel != stationSelectors.cend(); it_stSel++, it_AnnStates++ ){
		LOG("StationSelector     : " , INFO);
		m_terminalIO->printStationSelector( (*it_stSel) );
		auto it_AnnState = (*it_AnnStates).cbegin();
		for ( auto it_AnnConf = announcementConfigurations.cbegin(); it_AnnConf != announcementConfigurations.cend(); it_AnnConf++, it_AnnState++ ){
			LOG("AnnouncementType     : " + m_terminalIO->getAnnouncementType((*it_AnnConf).type), INFO);
			LOG("AnnouncementState    : " + m_terminalIO->getAnnouncementState((*it_AnnState)), INFO);
		}
	}
	LOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<", INFO);
	return true;
}

bool Client::SubscribedServiceOptionsCallbackClient(
		IVIRadio::AdditionalService::AdditionalServiceTypes::DataService 					dataService,
		IVIRadio::Types::Types::arrayStationSelectors 										stationSelections,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOptions 	unifiedOptions,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOptions 		serviceOptions,
		uint32_t 																			handleOut,
		IVIRadio::Types::Types::ErrorCodes 													errorCode
		){

	if ( !ReceivedCallback( "SubscribedServiceOptionsCallbackClient", handleOut) )
			return false;
	auto it_serviceOptions = serviceOptions.cbegin();
	auto it_unifiedOptions = unifiedOptions.cbegin();
	LOG( "DataService: " + m_terminalIO->getComponentType( dataService ), INFO );
	for ( auto it = stationSelections.cbegin(); it != stationSelections.cend() ; it++ , it_serviceOptions++, it_unifiedOptions++ ) {
		LOG("--------------------------------------------", INFO);
		for ( auto it2 = (*it).cbegin(); it2 != (*it).cend() ; it2++ ) {
			m_terminalIO->printStationSelector((*it2));
		}
		LOG( "RequestType: " + m_terminalIO->getUpdateType((*it_unifiedOptions).requestType) , INFO );
		m_terminalIO->printSelectParamter( dataService, (*it_serviceOptions), 0 );
	}
	LOG("--------------------------------------------", INFO);
	LOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<", INFO);
	return true;
}

bool Client::DataEventCallbackClient		(
		const IVIRadio::Types::Types::StationSelectors 											stationSelectors,
		const IVIRadio::AdditionalService::AdditionalServiceTypes::DataService					dataService,
		const IVIRadio::AdditionalService::AdditionalServiceTypesOptions::UnifiedServiceOption 	unifiedOptions,
		const IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption 	selectOptions,
		const IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat 					format,
		const IVIRadio::AdditionalService::AdditionalServiceTypes::DataType 					type,
		const IVIRadio::AdditionalService::AdditionalServiceTypes::Data 						data,
		const uint32_t& handleOut,
		const IVIRadio::Types::Types::ErrorCodes errorCode
)
{
	if ( !ReceivedCallback( "getDataEventCallback", handleOut) )
		return false;
	uint8_t compType;

	if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_NO_SERVICE ){
		if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_COMPONENTNOTSUPPORTED )
			LOG( "Component not supported", INFO );
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_SUBTITLE ) {

		if ( unifiedOptions.requestType == IVIRadio::Types::Types::UpdateType::UT_NONE ){
			m_pipeActive = false;
		}
		else {
			m_pipeActive = true;
			pthread_create( &thread_pipe, NULL, InternalThreadEntryFunc_DataPipe, this );
		}
	}
	else  {
		if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_NOERROR ){
    		string buf = "";
    		if ( data.isType<CommonAPI::ByteBuffer>() ){
				for (auto it = data.get<CommonAPI::ByteBuffer>().cbegin(); it != data.get<CommonAPI::ByteBuffer>().cend(); it++) {

					if (   buf.find( "</text>") 		!= string::npos
						|| buf.find( "</line>") 		!= string::npos
						 ) {
						LOG ("", INFO);
						cout << buf;
						buf = "";
					}
					else if (buf.find( "</ID>" ) 		 	!= string::npos
							|| buf.find( "</ver>" )  		!= string::npos
							|| buf.find( "</reco>" )  		!= string::npos
							|| buf.find( "</name>" )  		!= string::npos
							|| buf.find( "</time>" )  		!= string::npos
							|| buf.find( "</dur>" )  		!= string::npos
							|| buf.find( "</fsc>" )  		!= string::npos
							|| buf.find( "</desc>" )  		!= string::npos ) {
						LOG( buf, INFO );
						buf = "";
					}
					else if (buf.find( "<ID>" ) 		 	!= string::npos
							|| buf.find( "<ver>" )  		!= string::npos
							|| buf.find( "<reco>" )  		!= string::npos
							|| buf.find( "<name>" )  		!= string::npos
							|| buf.find( "<time>" )  		!= string::npos
							|| buf.find( "<dur>" )  		!= string::npos
							|| buf.find( "<fsc>" )  		!= string::npos
							|| buf.find( "<desc>" )  		!= string::npos ) {
						cout << "        " << buf;
						buf = "";
					}
					else if ( buf.find( "</EPGEvent>" )  	!= string::npos
							|| buf.find( "</EPGProgram>" )  != string::npos ) {
						LOG( "    " + buf, INFO );
						buf = "";
					}
					else if ( buf.find( "<EPGEvent>" )  	!= string::npos
							|| buf.find( "<EPGProgram>" )  != string::npos ) {
						LOG( "    " + buf, INFO );
						buf = "";
					}
					else if ( buf.find( "<xml>" )  	!= string::npos || buf.find( "</xml>" )	!= string::npos) {
						LOG ( buf, INFO );
						buf = "";
					}
					buf += *it;
				}
    		}
    		else {
    			LOG( data.get<string>() , INFO );
    		}
		}
    	else if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_NOTACTIVE ){
    		LOG("Application not yet activated...", WARNING);
		}
		else if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_INVALIDCOMPONENTID ){
			LOG("Invalid Component ID ... please retry using another one..", WARNING);
		}
		else if ( errorCode == IVIRadio::Types::Types::ErrorCodes::EC_NODATAAVAILABLE ){
			LOG("for that request is no data available ( maybe no test data available. Use that in the folders )...", WARNING);
		}
    }
    LOG("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<", INFO);
    return false;
}

void Client::InternalThreadEntry_DataPipe (void *_arg ){
    int fifo_pipe = mkfifo("/tmp/fifo", S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	int num, fifo;
    char temp[38];
    if ((fifo = open("/tmp/fifo", O_RDONLY)) < 0) {
        printf("%s\n", strerror(errno));
        return;
    }

    while ( m_pipeActive ) {
        if ((num = read(fifo, temp, sizeof(temp))) < 0) {
            printf("%s\n", strerror(errno));
            m_pipeActive = false;
        }
        printf("Pipe:  %s \n", temp);
    }
    close(fifo);
}

bool Client::FunctionalityConfigurationEventCallbackClient(
		const IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes 	functionaliyTypes,
		const IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions	functionalityOptions,
		const uint32_t handle_out,
		const IVIRadio::Types::Types::ErrorCodes errorCode )
{
	LOG("reached functionalityConfigurationEventCallback ", INFO);
	m_terminalIO->printFunctionalityTypesOptions( functionaliyTypes, functionalityOptions );
	return true;
}

int main(int argc, char **argv)
{
	TerminalIO *m_terminalIO = TerminalIO::getInstance();
    if (argc < 2) {
        LOG( "Usage: Client hmiId"	, ERROR );
        LOG( "hmiId in range [0-3]" , ERROR );
        exit(1);
    }
    int hmiId = atoi(argv[1]);
    Client *client = Client::getInstance( hmiId );
    LOG( "Welcome to Genivi Tuner API simulation (HMI part)" , INFO);
    LOG( "Client HMI number is " + to_string( hmiId ) , INFO );
    client->loop();
}
