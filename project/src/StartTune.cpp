///////////////////////////////////////////////////////////
//  StartTune.cpp
//  Implementation of the Class StartTune
//  Created on:      16-Jul-2013 16:45:43
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/StartTune.h"

StartTune::StartTune( Tuner *tuner, HMI *hmi, struct timeval tv,
	    IVIRadio::Types::Types::StationSelector station,
	    IVIRadio::Station::StationTypes::SelectionMode selectionMode,
	    uint32_t handle)
{

	m_FileIO		= FileIO::getInstance();
	m_tuner 		= tuner;
	m_hmi			= hmi;
	m_station 		= station;
	m_selectionMode = selectionMode;
	m_handle 		= handle;

}

StartTune::~StartTune(){

}


bool StartTune::continueJob(){
	/*
	 * Must determine the frequency of the real station here.
	 * If selection is done by frequency, we are finished.
	 *
	 * If the selection was made in list mode for AMFM or DAB,
	 * then we can directly access the station vector with that id.
	 *
	 * If the list mode for UNDEF was used, we need to lookup
	 * by PiCode and/or DAB service id in order to find suitable
	 * station.
	 */

	m_tuner->setState(TunerState::TUNING);

	if ( m_selectionMode == IVIRadio::Station::StationTypes::SelectionMode::SM_DIRECT ) {
		switch( ( IVIRadio::Types::Types::DeviceType )m_station.deviceType ) {
			case IVIRadio::Types::Types::DeviceType::AMFM:
				m_tuner->setFrequency( m_station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] );
				break;
			case IVIRadio::Types::Types::DeviceType::DAB:
				m_tuner->setFrequency( m_station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] );
				break;
			case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
				// fallthrough
			default:
				// illegal
				break;
		}
	}
	else if ( m_selectionMode == IVIRadio::Station::StationTypes::SelectionMode::SM_LIST ) {
		uint32_t key;
		IVIRadio::Station::StationTypes::Station  x_station;
		IVIRadio::Station::StationTypes::Station *y_station;

		switch( (IVIRadio::Types::Types::DeviceType )m_station.deviceType ) {

			case IVIRadio::Types::Types::DeviceType::AMFM:
				key = m_station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY];
				x_station = m_FileIO->getReceivableAMFMStationByIndex( key );
				m_tuner->setFrequency( x_station.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
				break;

			case IVIRadio::Types::Types::DeviceType::DAB:
				key = m_station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY];
				x_station = m_FileIO->getReceivableDABStationByIndex(key);
				m_tuner->setFrequency(x_station.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY]);
				break;

			case IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE:
				key = m_station.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY];
				// the key is the PI code or Service id
				// try DAB first
				y_station = m_FileIO->getReceivableDABStationByServiceId( key );
				if (y_station == NULL) {
					y_station = m_FileIO->getReceivableAMFMStationByPICode( key );
					if (y_station == NULL) {
						// error
					} else {
						m_tuner->setFrequency(y_station->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
					}
				} else {
					m_tuner->setFrequency(y_station->sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY]);
				}

				break;
			default:
				// illegal
				break;
		}
	}

	m_tuner->setState(TunerState::TUNED);

	return true;

}
