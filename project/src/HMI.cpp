///////////////////////////////////////////////////////////
//  HMI.cpp
//  Implementation of the Class HMI
//  Created on:      16-Jul-2013 16:47:52
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/HMI.h"


HMI::HMI( int hmiId ) {

	bHasCurrentStation 	= false;

	m_SendCurrStation 	= false;

	m_TerminalIO 		= TerminalIO::getInstance();

	m_EPG				= new Dataservices	( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_EPG		  );
	m_Journaline		= new Dataservices 	( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_JOURNALINE );
	m_Subtitle			= new Dataservices	( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_SUBTITLE	  );

    m_hmiId 	= hmiId;

    //those parameters shall indicate if the client has notified on results of seek and on progress information of seek
    //if true the client will be informed; normally default value is false and the client need to call controlUpdate method
    //to notify itself on various functionality
    m_updateSeekNotificationAMFM 			= false;
    m_updateSeekNotificationDAB 			= false;
    m_updateStationListNotificationAMFM 	= false;
    m_updateStationListNotificationDAB 		= false;
    m_updateStationListNotificationUndef 	= false;
}

HMI::~HMI() {
	cout << "Destroyed HMI id " << m_hmiId << endl;
}

void HMI::setUpdateSeekNotificationAMFM(bool val)
{
	m_updateSeekNotificationAMFM = val;
    cout << "HMI id " << m_hmiId << " updateSeekNotificationAMFM set to " << val << endl;
}

void HMI::setUpdateSeekNotificationDAB(bool val)
{
	m_updateSeekNotificationDAB = val;
    cout << "HMI id " << m_hmiId << " updateSeekNotificationDAB set to " << val << endl;
}

void HMI::setUpdateStationListNotificationAMFM(bool val)
{
	m_updateStationListNotificationAMFM = val;
    cout << "HMI id " << m_hmiId << " updateStationListNotificationAMFM set to " << val << endl;
}

void HMI::setUpdateStationListNotificationDAB(bool val)
{
	m_updateStationListNotificationDAB = val;
    cout << "HMI id " << m_hmiId << " updateStationListNotificationDAB set to " << val << endl;
}

void HMI::setUpdateStationListNotificationUndef(bool val)
{
	m_updateStationListNotificationUndef = val;
    cout << "HMI id " << m_hmiId << " updateStationListNotificationUndef set to " << val << endl;
}

bool HMI::getStationToServiceIdentifier( uint32_t serviceID, IVIRadio::Station::StationTypes::Station &oStation){
	for ( auto it = m_completeListAMFM.cbegin(); it != m_completeListAMFM.cend(); ++it ){
		if ( ( *it ).sel.id[2] == serviceID ){
			oStation = ( *it );
			return true;
		}
	}
	for ( auto it = m_completeListDAB.cbegin(); it != m_completeListDAB.cend(); ++it ){
		if ( ( *it ).sel.id[3] == serviceID ){
			oStation = ( *it );
			return true;
		}
	}
	return false;
}

void HMI::setCurrentTunedStation(IVIRadio::Station::StationTypes::Station currentStation) {
	m_currentStation 	= currentStation;
	bHasCurrentStation 	= true;
	return;
}

bool HMI::addDataRequest	 	( data_request_parameter request ) {
	uint32_t res = 0;

	//check if request is already in the request list
	for ( auto it = m_requests.cbegin(); it != m_requests.cend() ; it++ ) {
		res = 0;
		if ( (*it).dataFormat == request.dataFormat ) {
			res++;
		}
		if ( (*it).dataType == request.dataType ) {
			res++;
		}
		if ( (*it).serviceOptions == request.serviceOptions ) {
			res++;
		}
		if ( (*it).stationSelectors == request.stationSelectors ) {
			res++;
		}
		if ( (*it).componentType == request.componentType ){
			res++;
		}

	}
	if ( res != 5 ) {
		m_requests.push_back( request );
	}

	return res;
}

bool HMI::removeDataRequest 	( data_request_parameter request ) {

	uint32_t cnt = 0;
	vector <data_request_parameter> tmp;
	//check if request is already in the request list
	for ( auto it = m_requests.cbegin(); it != m_requests.cend() ; it++ ) {
		cnt = 0;
		if ( (*it).dataFormat 		== request.dataFormat 		) {
			cnt++;
		}
		if ( (*it).dataType 		== request.dataType 		) {
			cnt++;
		}
		if ( (*it).serviceOptions 	== request.serviceOptions 	) {
			cnt++;
		}
		if ( (*it).stationSelectors == request.stationSelectors ) {
			cnt++;
		}
		if ( (*it).componentType 	== request.componentType 	){
			cnt++;
		}
		if ( cnt != 5 ){
			tmp.push_back( ( *it ) );
		}
	}
	m_requests = tmp;
	return true;
}

vector < data_request_parameter > HMI::getRequests( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService ){
	vector < data_request_parameter > ret;
	for ( auto it = m_requests.cbegin(); it != m_requests.cend() ; it++ ) {
		if ( (*it).componentType == dataService ){
			ret.push_back((*it));
		}
	}
	return ret;
}
