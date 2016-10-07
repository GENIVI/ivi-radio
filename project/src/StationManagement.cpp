/*
 * StationManagement.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: b
 */

#include "includes/StationManagement.h"

StationManagement::StationManagement() {
}

StationManagement::~StationManagement() {
}

bool StationManagement::ManualDown(Tuner *tuner){
	tuner->setState(TunerState::TUNING);
	tuner->decrFrequency();
    tuner->setState(TunerState::TUNED);
    return true;
}

bool StationManagement::ManualUp(Tuner* tuner){
	tuner->setState(TunerState::TUNING);
	tuner->incrFrequency();
	tuner->setState(TunerState::TUNED);
	return true;
}

bool StationManagement::AutoDown( Tuner* tuner, HMI *hmi ){
	bool finished = tuner->scanDownFrequency();
	if ( finished ) {
		IVIRadio::Station::StationTypes::SeekData broadcast_seekData;
		tuner->setState(TunerState::TUNED);
		//send SM_OFF broadcast
		m_SeekData.mode 		= IVIRadio::Station::StationTypes::SeekMode       ::SM_OFF;
		m_SeekData.returnValue 	= IVIRadio::Station::StationTypes::SeekReturnValue::SM_FREQUENCY;
		m_SeekData.data 		= tuner->getFrequency();
	} else {
		int freq;
		// check whether to send seek broadcast
		if ( (freq = tuner->getFrequency() ) % 100 == 0) {
			if (((tuner->getDeviceType() == IVIRadio::Types::Types::DeviceType::AMFM) &&
				 hmi->getUpdateSeekNotificationAMFM() == true) ||
				((tuner->getDeviceType() == IVIRadio::Types::Types::DeviceType::DAB) &&
				 hmi->getUpdateSeekNotificationDAB() == true)) {
				IVIRadio::Station::StationTypes::SeekData broadcast_seekData;
				m_SeekData.mode 		= IVIRadio::Station::StationTypes::SeekMode       ::SM_AUTO_DOWN;
				m_SeekData.returnValue	= IVIRadio::Station::StationTypes::SeekReturnValue::SM_FREQUENCY;
				m_SeekData.data 		= freq;
			}
		}
	}
	return finished;
}

bool StationManagement::AutoUp(Tuner *tuner, HMI *hmi){

	bool finished = tuner->scanUpFrequency();
	if (finished) {
		tuner->setState(TunerState::TUNED);
		// send SM_OFF broadcast
		m_SeekData.mode = IVIRadio::Station::StationTypes::SeekMode::SM_OFF;
		m_SeekData.returnValue = IVIRadio::Station::StationTypes::SeekReturnValue::SM_FREQUENCY;
		m_SeekData.data = tuner->getFrequency();
	} else {
		int freq;
		// check whether to send seek broadcast
		if ( ( freq = tuner->getFrequency() ) % 100 == 0 ) {
			if ( ( ( tuner->getDeviceType() == IVIRadio::Types::Types::DeviceType::AMFM ) &&
				 hmi->getUpdateSeekNotificationAMFM() == true ) ||
				( ( tuner->getDeviceType() == IVIRadio::Types::Types::DeviceType::DAB ) &&
				 hmi->getUpdateSeekNotificationDAB() == true ) ) {
				m_SeekData.mode 		= IVIRadio::Station::StationTypes::SeekMode		::SM_AUTO_UP;
				m_SeekData.returnValue 	= IVIRadio::Station::StationTypes::SeekReturnValue	::SM_FREQUENCY;
				m_SeekData.data 		= freq;
			}
		}
	}
	return finished;
}
