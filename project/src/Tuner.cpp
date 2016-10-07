///////////////////////////////////////////////////////////
//  Tuner.cpp
//  Implementation of the Class Tuner
//  Created on:      16-Jul-2013 16:47:50
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Tuner.h"


Tuner::Tuner(int tunerId, int minFrequency, int maxFrequency, IVIRadio::Types::Types::DeviceType deviceType){
	m_tunerId 		= tunerId;
    m_state 		= TunerState::IDLE;
    m_assignedToHmi = NULL;
    m_minFrequency 	= minFrequency;
    m_maxFrequency 	= maxFrequency;
    m_deviceType 	= deviceType;
    m_frequency     = minFrequency;
    m_FileIO 		= FileIO::getInstance();
}

Tuner::~Tuner(){
}

void Tuner::alloc(HMI *hmi)
{
    if (m_assignedToHmi != NULL) {
        throw invalid_argument("Tuner already assigned");
    }
    m_assignedToHmi = hmi;
    cout << "Tuner id " << m_tunerId << " now assigned to HMI id " << hmi->getHMIId() << endl;
}

void Tuner::free(HMI *hmi)
{
    if (m_assignedToHmi == NULL) {
        throw invalid_argument("Tuner not assigned");
        //throw bad_alloc("Tuner not assigned");
    }
    m_assignedToHmi = NULL;
    m_state = TunerState::IDLE;
    cout << "Tuner id " << m_tunerId << " no longer assigned to HMI id " << hmi->getHMIId() << endl;
}

bool Tuner::stationFound( int frequency )
{
    if ( m_deviceType == IVIRadio::Types::Types::DeviceType::AMFM ) {
        IVIRadio::Station::StationTypes::Station *x;

        x = m_FileIO->getReceivableAMFMStationByFrequency( frequency );
        if (x != NULL) {
            return true;
        }
    } else if ( m_deviceType == IVIRadio::Types::Types::DeviceType::DAB ) {
        IVIRadio::Station::StationTypes::Station *x;

        x = m_FileIO->getReceivableDABStationByFrequency( frequency );
        if (x != NULL) {
            return true;
        }
    }

    return false;
}

void Tuner::setFrequency( int frequency )
{
    int old_frequency = frequency;

    if ( frequency < m_minFrequency || frequency > m_maxFrequency ) {
        throw invalid_argument("invalid frequency");
    }
    m_frequency = frequency;

    //cout << "Tuner id " << m_tunerId << " frequency changed from " << old_frequency << " to " << frequency << endl;
}

void Tuner::incrFrequency( )
{
    //Mutex->lockMutex();

    // FM case only
    int old_frequency = m_frequency;

    if ( m_frequency < getMaxFrequency() ) {
    	m_frequency += 100;
    	if ( ( m_frequency % 10 ) == 0 )
    		cout << "Tuner id " << m_tunerId << " frequency changed from " << old_frequency << " to " << m_frequency << endl;
    }
}

void Tuner::decrFrequency()
{
    // FM case only
    int old_frequency = m_frequency;

    if ( m_frequency > m_minFrequency ) {
    	m_frequency -= 100;
        //cout << "Tuner id " << m_tunerId << " frequency changed from " << old_frequency << " to " << m_frequency << endl;
    }
}

bool Tuner::scanUpFrequency()
{
    int old_frequency = m_frequency;

    if (m_frequency < getMaxFrequency()) {
    	m_frequency += 100;
        //cout << "Tuner id " << m_tunerId << " frequency changed from " << old_frequency << " to " << m_frequency << endl;
    } else {
        return true;
    }

    if ( stationFound( m_frequency ) ) {
        return true;
    }

    return false;
}

bool Tuner::scanDownFrequency()
{
    int old_frequency = m_frequency;
    if ( m_frequency > m_minFrequency ) {
    	m_frequency -= 100;
        cout << "Tuner id " << m_tunerId << " frequency changed from " << old_frequency << " to " << m_frequency << endl;
    } else {
        return true;
    }
    if ( stationFound( m_frequency ) ) {
        return true;
    }
    return false;
}

bool Tuner::autoStore()
{
    int old_frequency = m_frequency;
    m_frequency += 100;
    //cout << "Tuner id " << m_tunerId << " frequency changed from " << old_frequency << " to " << m_frequency << endl;
    if ( m_frequency >= getMaxFrequency() ) {
        cout << "Tuner id " << m_tunerId << " current frequency " << old_frequency << " maxFrequency " << getMaxFrequency() << endl;
        return true;
    }
    return false;
}

void Tuner::setState(TunerState state)
{
    // check whether state transition is allowed
    TunerState oldState = m_state;
    switch( m_state ) {
        case TunerState::IDLE:
            if (state == TunerState::TUNING || state == TunerState::SCANNING) {
            	m_state = state;
            	m_frequency = m_minFrequency;
                cout << "Tuner id " << m_tunerId << " state change from " << getStateString( oldState ) << " to " << getStateString( state ) << endl;
                return;
            }
            break;
        case TunerState::TUNING:
            if (state == TunerState::TUNED || state == TunerState::IDLE) {
                m_state = state;
                cout << "Tuner id " << m_tunerId << " state change from " << getStateString( oldState ) << " to " << getStateString( state ) << endl;
                return;
            }
            break;
        case TunerState::TUNED:
            if (state == TunerState::IDLE || state == TunerState::TUNING) {
            	m_state = state;
                cout << "Tuner id " << m_tunerId << " state change from " << getStateString( oldState ) << " to " << getStateString( state ) << endl;
                return;
            }
            break;
        case TunerState::SCANNING:
            if (state == TunerState::IDLE) {
                m_state = state;
                cout << "Tuner id " << m_tunerId << " state change from " << getStateString( oldState ) << " to " << getStateString( state ) << endl;
                return;
            }
            break;
        default:
            throw invalid_argument("invalid tuner state");
    }
    cout << "Tuner id " << m_tunerId << " INVALID state change from " << getStateString( oldState ) << " to " << getStateString( state ) << endl;
    throw invalid_argument("invalid tuner state transition");
}

TunerState Tuner::getState()
{
    return m_state;
}

string Tuner::getStateString(TunerState state)
{
    switch(state) {
        case TunerState::IDLE:
            return("IDLE");
        case TunerState::TUNING:
            return("TUNING");
        case TunerState::TUNED:
            return("TUNED");
        case TunerState::SCANNING:
            return("SCANNING");
        default:
            throw invalid_argument("invalid tuner state");
    }
}

HMI *Tuner::getCurrentAssignment()
{
    return m_assignedToHmi;
}

int Tuner::getMinFrequency()
{

    return m_minFrequency;
}

int Tuner::getMaxFrequency()
{
    return m_maxFrequency;
}

IVIRadio::Types::Types::DeviceType Tuner::getDeviceType()
{
    return m_deviceType;
}

IVIRadio::Station::StationTypes::Station Tuner::getTunedStation()
{
    IVIRadio::Station::StationTypes::Station myStation;

    if ( m_deviceType == IVIRadio::Types::Types::DeviceType::AMFM ) {
        IVIRadio::Station::StationTypes::Station *x;

        x = m_FileIO->getReceivableAMFMStationByFrequency( m_frequency );
        if (x != NULL) {
            myStation = *x;
        } else {
            // setup some fake AMFM station record

            myStation.stationType = (int32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF;
            myStation.sel.deviceType = (uint32_t)IVIRadio::Types::Types::DeviceType::AMFM;
            cout << "AMFM" << endl;
            myStation.sel.id.resize(4);
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_KEY] 			= 0;
            cout << "0" << endl;
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] 	= m_frequency;
            cout << m_frequency << endl;
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_PI] 			= 0;
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexAmFm::AMFM_ID_SERVICE] 		= 0;

            myStation.name.resize(3);
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_PS] = "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_HD] = "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexAmFm::AMFM_NAM_RT] = "Not applicable";

            myStation.meta.resize(1);
            myStation.meta[0].type = 0;
            myStation.meta[0].str = "Not applicable";

            myStation.genre.resize(1);
            myStation.genre[(uint32_t)IVIRadio::Station::StationTypes::GenreIndexAmFm::AMFM_GEN_PTY] = 0;

            //myStation.flags.resize(1);
            //myStation.flags[0] = 0;
            myStation.flags = 0;

            myStation.quality.resize(3);
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_FIELDSTRENGTH] = 0;
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_MULTIPATH] 	= 0;
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexAmFm::AMFM_QAL_DIGITAL] 		= 0;
        }
    } else if (m_deviceType == IVIRadio::Types::Types::DeviceType::DAB) {
        IVIRadio::Station::StationTypes::Station *x;

        x = m_FileIO->getReceivableDABStationByFrequency( m_frequency );
        if (x != NULL) {
            myStation = *x;
        } else {
            // setup some fake DAB station record
            myStation.stationType = (int32_t)IVIRadio::Station::StationTypes::StationType::ST_UNDEF;
            myStation.sel.deviceType = (uint32_t)IVIRadio::Types::Types::DeviceType::DAB;
            myStation.sel.id.resize(5);
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_KEY] 		= 0;
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_FREQUENCY] 	= m_frequency;
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_ENSEMBLE] 	= 0;
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_SERVICE] 	= 0;
            myStation.sel.id[(uint32_t)IVIRadio::Station::StationTypes::IdIndexDab::DAB_ID_COMPONENT] 	= 0;

            myStation.name.resize(8);
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_CLONG] 	= "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_CSHORT] 	= "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_DYNAMIC] 	= "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SLONG] 	= "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_SSHORT] 	= "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_ELONG] 	= "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_ESHORT] 	= "Not applicable";
            myStation.name[(uint32_t)IVIRadio::Station::StationTypes::NameIndexDab::DAB_NAM_FREQUENCY] = "Not applicable";

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
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_BER]		= 0;
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_SERVICE] = 0;
            myStation.quality[(uint32_t)IVIRadio::Station::StationTypes::QualityIndexDab::DAB_QAL_AUDIO] 	= 0;
        }
    } else {
        // error
    }

    return myStation;
}
