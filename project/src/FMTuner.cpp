///////////////////////////////////////////////////////////
//  FMTuner.cpp
//  Implementation of the Class FMTuner
//  Created on:      16-Jul-2013 16:47:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/FMTuner.h"


FMTuner::FMTuner(int tunerId) : Tuner( tunerId, m_minFrequencyFM, m_maxFrequencyFM, IVIRadio::Types::Types::DeviceType::AMFM ){
}

FMTuner::~FMTuner(){
}


IVIRadio::Station::StationTypes::Station FMTuner::getTunedStation() {

	IVIRadio::Station::StationTypes::Station myStation;

	IVIRadio::Station::StationTypes::Station *x;

	x = getFileIO()->getReceivableAMFMStationByFrequency( getFrequency() );
	if (x != NULL) {
		myStation = *x;
	} else {
		// setup some fake AMFM station record

		myStation.stationType 		= (int32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF;
		myStation.sel.deviceType 	= (uint32_t)IVIRadio::Types::Types::DeviceType::AMFM;
		myStation.sel.id.resize(4);
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] 			= 0;
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] 	= getFrequency();
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI] 			= 0;
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE] 		= 0;

		myStation.name.resize(3);
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_PS] = "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_HD] = "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_RT] = "Not applicable";

		myStation.meta.resize(1);
		myStation.meta[0].type 	= 0;
		myStation.meta[0].str 	= "Not applicable";

		myStation.genre.resize(1);
		myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexAmFm::AMFM_GEN_PTY] = 0;

		//myStation.flags.resize(1);
		//myStation.flags[0] = 0;
		myStation.flags = 0;

		myStation.quality.resize(3);
		myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_FIELDSTRENGTH] 	= 0;
		myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_MULTIPATH] 		= 0;
		myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_DIGITAL] 		= 0;
	}

	return myStation;
}
