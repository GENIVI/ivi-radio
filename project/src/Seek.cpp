///////////////////////////////////////////////////////////
//  Seek.cpp
//  Implementation of the Class Seek
//  Created on:      16-Jul-2013 16:47:54
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Seek.h"


Seek::Seek( Tuner *tuner, HMI *hmi, struct timeval tv,
			IVIRadio::Types::Types::DeviceType device,
			IVIRadio::Station::StationTypes::SeekMode   seekMode) {

	m_hmi		 = hmi;
	m_tuner		 = tuner;
	m_tv		 = tv;
	m_device     = device  ;
	m_seekMode 	 = seekMode;
	m_FileIO 	 = FileIO::getInstance();
	m_finished 	 = false;
}

Seek::~Seek(){

}



bool Seek::continueJob(){

	m_finished = m_tuner->autoStore();
	bool deviceTypeIsAMFM = ( m_tuner->getDeviceType() == IVIRadio::Types::Types::DeviceType::AMFM);
	bool deviceTypeIsDAB  = ( m_tuner->getDeviceType() == IVIRadio::Types::Types::DeviceType::DAB );
	if ( m_finished ) {
		IVIRadio::Station::StationTypes::SeekData broadcast_seekData;
		bool doSendBroadCast = false;
		if ((deviceTypeIsAMFM && m_hmi->getUpdateSeekNotificationAMFM() == true) ||
			(deviceTypeIsDAB  && m_hmi->getUpdateSeekNotificationDAB()  == true)) {
			// must prepare the broadcast contents before freeing the tuner, but send later
			m_broadcastSeekData.mode 		= IVIRadio::Station::StationTypes::SeekMode       ::SM_AUTOSTORE;
			m_broadcastSeekData.returnValue = IVIRadio::Station::StationTypes::SeekReturnValue::SM_PERCENTAGE;
			m_broadcastSeekData.data 		= 100; // we are finished, so we have 100%
			doSendBroadCast = true;
		}
		// send last broadcast unconditionally, no check for notification settings
		// must prepare the broadcast contents before freeing the tuner, but send later
		m_broadcastSeekData.mode 		= IVIRadio::Station::StationTypes::SeekMode::SM_OFF;
		m_broadcastSeekData.returnValue = IVIRadio::Station::StationTypes::SeekReturnValue::SM_PERCENTAGE;
		m_broadcastSeekData.data 		= 100; // we are finished, so we have 100%
		doSendBroadCast = true;
		m_FileIO->scanStations("config", m_tuner->getDeviceType());
		// store current list in HMI
		if (deviceTypeIsAMFM) {
			m_hmi->setCompleteListAMFM( m_FileIO->getCompleteAMFMStationList() );
		}
		else if (deviceTypeIsDAB) {
			m_hmi->setCompleteListDAB ( m_FileIO->getCompleteDABStationList () );
		}
		m_hmi->setCompleteListUndef( m_FileIO->getCompleteUndefStationList() );
	}
	else {
		int freq;
		int percentage;
		// check whether to send seek broadcast
		freq = m_tuner->getFrequency();
		percentage = ( freq - m_tuner->getMinFrequency()) * 100 / ( m_tuner->getMaxFrequency() - m_tuner->getMinFrequency() );
		if ( m_broadcastSeekData.data != percentage && (percentage % 10) == 0 ){
			cout << "Freq is " << freq << " and percentage is " << percentage << endl;
		}
		m_broadcastSeekData.mode 		= IVIRadio::Station::StationTypes::SeekMode::SM_AUTOSTORE;
		m_broadcastSeekData.returnValue = IVIRadio::Station::StationTypes::SeekReturnValue::SM_PERCENTAGE;
		m_broadcastSeekData.data 		= percentage;
	}
	return m_finished;
}

IVIRadio::Station::StationTypes::SeekData Seek::getSeekData() {
	return m_broadcastSeekData;
}

IVIRadio::Station::StationTypes::StationList Seek::getSeekList() {
	return m_broadcastList;
}
