///////////////////////////////////////////////////////////
//  DABTuner.cpp
//  Implementation of the Class DABTuner
//  Created on:      16-Jul-2013 16:47:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/DABTuner.h"


//DABTuner::DABTuner(int m_tunerId, TunerList *m_tunerList) : Tuner::Tuner(m_tunerId, m_tunerList, minFrequencyDAB, maxFrequencyDAB, IVIRadio::Types::Types::DeviceType::DAB)
DABTuner::DABTuner(int tunerId) : Tuner(tunerId, m_minFrequencyDAB, m_maxFrequencyDAB, IVIRadio::Types::Types::DeviceType::DAB) {
}

DABTuner::~DABTuner(){
}

IVIRadio::Station::StationTypes::Station DABTuner::getDABTunedStation() {

	IVIRadio::Station::StationTypes::Station myStation;

	IVIRadio::Station::StationTypes::Station *x;

	x = getFileIO()->getReceivableDABStationByFrequency( getFrequency() );
	if (x != NULL) {
		myStation = *x;
	} else {
		// setup some fake DAB station record
		myStation.stationType = (int32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF;
		myStation.sel.deviceType = (uint32_t)IVIRadio::Types::Types::DeviceType::DAB;
		myStation.sel.id.resize(5);
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY]			= 0;
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] 	= getFrequency();
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE] 	= 0;
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE] 	= 0;
		myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT] 	= 0;

		myStation.name.resize(8);
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_CLONG] 		= "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_CSHORT] 	= "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_DYNAMIC]	= "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SLONG] 		= "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SSHORT] 	= "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_ELONG] 		= "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_ESHORT] 	= "Not applicable";
		myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_FREQUENCY]	= "Not applicable";

		myStation.meta.resize(1);
		myStation.meta[0].type = 0;
		myStation.meta[0].str = "Not applicable";

		myStation.genre.resize(2);
		myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexDab::DAB_GEN_STATIC_PTY] 	= 0;
		myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexDab::DAB_GEN_DYNAMIC_PTY] = 0;

		//myStation.flags.resize(1);
		//myStation.flags[0] = 0;
		myStation.flags = 0;

		myStation.quality.resize(3);
		myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_BER] 	= 0;
		myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_SERVICE] = 0;
		myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_AUDIO] 	= 0;
	}

	return myStation;
}
