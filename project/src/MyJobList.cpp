/*
Copyright (C) 2013 BMW Group

Author: Guido Ostkamp     (guido.ostkamp@de.bertrandt.com)
Author: Bernhard Singer   (bernhard.singer@partner.bmw.de)
Author: Matthias Freundel (matthias.freundel@partner.bmw.de)

This Source Code Form is subject to the terms of the Mozilla Public

License, v. 2.0. If a copy of the MPL was not distributed with this file,

You can obtain one at http://mozilla.org/MPL/2.0/.
*/

/*
 * MyJobList -
 *
 * this module contains a number of classes, e.g.
 *   Tuner     - representing possible Tuners
 *   FMTuner   - child class of Tuner for FM
 *   DABTuner  - child class of Tuner for DAB
 *   TunerList - maintaining the list of configured tuners
 *   HMI       - representing HMI states (remote clients)
 *   HMIList   - maintaining the list of configured HMIs
 *   Job       - representing an asynchronous activity
 *               that has been triggered by the HMI client
 *               by calling a Franca method
 *   JobQueue  - maintaining the list of currently active jobs
 *               sorted within a time based priority queue
 *
 * Tuners have states (idle, tuning, tuned, scanning, etc.),
 * a current frequency and a frequency range (depending on standard FM/DAB)
 * and will be assigned to a specific HMI when not in state idle
 *
 * HMI know about the last lists which have been sent to them
 * in order to calculate update lists later
 *
 * TunerList provides a list of known tuners as well as methods
 * to allocate a free one, or return (free) it to the list
 *
 * HMIList provides a list of HMIs.
 *
 * A job is created once a HMI issues a request to tune to a station,
 * abort an existing tuning, or carry out a seek (full autostore,
 * scan to next/previous receivable station, manual tune up/down).
 * Jobs may be executed in steps (e.g. when walking within a frequency
 * range) until they are finished to simulate real world behaviour
 * (e.g. a full scan may take a while).
 *
 * The jobs are maintained in a JobQueue in a time based order.
 *
 * Since the enqueuing, dequeuing of jobs and the job execution is
 * done in the background in parallel, all methods are protected
 * by a recursive mutex to avoid inconsistency caused by parallelism.
 * E.g. while a job is being executed, the system might be managing
 * an incoming request that needs to enqueue a new job in another
 * thread running at the same time in parallel.
 */

#include "MyJobList.h"
#include "MyTerminalIO.h"
#include "MyFileIO.h"
#include <mutex>

using namespace std;

extern void finishAllAnnouncementsForComponentID(std::shared_ptr<TunerAdditionalServiceIndividualStub> stub, uint32_t componentID);
extern TunerStationTypes::TunerStationTypes::StationList getTunedStations();

std::recursive_mutex myJobListMutex;

HMI::HMI(int m_hmiId, HMIList *m_hmiList) {
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    hmiId = m_hmiId;
    hmiList = m_hmiList;
    updateSeekNotificationAMFM = false;
    updateSeekNotificationDAB = false;
    updateStationListNotificationAMFM = false;
    updateStationListNotificationDAB = false;
    updateStationListNotificationUndef = false;
    announcementEnabled = TunerTypes::TunerTypes::Activation::INACTIVE;
    MY_TRACE(cout << "Created HMI id " << hmiId << endl);
}

HMI::~HMI() {
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Destroyed HMI id " << hmiId << endl);
}

int
HMI::getHMIId()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return hmiId;
}

HMIList *
HMI::getHMIList()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return hmiList;
}


void
HMI::setCompleteListAMFM(const vector<TunerStationTypes::TunerStationTypes::Station>& vec)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    completeListAMFM = vec;
}

void
HMI::setCompleteListDAB(const vector<TunerStationTypes::TunerStationTypes::Station>& vec)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    completeListDAB = vec;
}

void
HMI::setCompleteListUndef(const vector<TunerStationTypes::TunerStationTypes::Station>& vec)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    completeListUndef = vec;
}

vector<TunerStationTypes::TunerStationTypes::Station>
HMI::getCompleteListAMFM()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return(completeListAMFM);
}

vector<TunerStationTypes::TunerStationTypes::Station>
HMI::getCompleteListDAB()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return(completeListDAB);
}

vector<TunerStationTypes::TunerStationTypes::Station>
HMI::getCompleteListUndef()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return(completeListUndef);
}

bool
HMI::getUpdateSeekNotificationAMFM()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return updateSeekNotificationAMFM;
}

bool
HMI::getUpdateSeekNotificationDAB()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return updateSeekNotificationDAB;
}

bool
HMI::getUpdateStationListNotificationAMFM()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return updateStationListNotificationAMFM;
}

bool
HMI::getUpdateStationListNotificationDAB()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return updateStationListNotificationDAB;
}

bool
HMI::getUpdateStationListNotificationUndef()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return updateStationListNotificationUndef;
}

void
HMI::setUpdateSeekNotificationAMFM(bool val)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    updateSeekNotificationAMFM = val;
    MY_TRACE(cout << "HMI id " << hmiId << " updateSeekNotificationAMFM set to " << val << endl);
}

void
HMI::setUpdateSeekNotificationDAB(bool val)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    updateSeekNotificationDAB = val;
    MY_TRACE(cout << "HMI id " << hmiId << " updateSeekNotificationDAB set to " << val << endl);
}

void
HMI::setUpdateStationListNotificationAMFM(bool val)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    updateStationListNotificationAMFM = val;
    MY_TRACE(cout << "HMI id " << hmiId << " updateStationListNotificationAMFM set to " << val << endl);
}

void
HMI::setUpdateStationListNotificationDAB(bool val)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    updateStationListNotificationDAB = val;
    MY_TRACE(cout << "HMI id " << hmiId << " updateStationListNotificationDAB set to " << val << endl);
}

void
HMI::setUpdateStationListNotificationUndef(bool val)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    updateStationListNotificationUndef = val;
    MY_TRACE(cout << "HMI id " << hmiId << " updateStationListNotificationUndef set to " << val << endl);
}

uint32_t
HMI::getLastSeekNotificationValueAMFM()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return lastSeekNotificationValueAMFM;
}

uint32_t
HMI::getLastSeekNotificationValueDAB()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return lastSeekNotificationValueDAB;
}

void
HMI::setLastSeekNotificationValueAMFM(uint32_t val)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    lastSeekNotificationValueAMFM = val;
}

void
HMI::setLastSeekNotificationValueDAB(uint32_t val)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    lastSeekNotificationValueDAB = val;
}

void
HMI::setAnnouncementHandling(TunerTypes::TunerTypes::Activation state)
{
    auto tio = MyTerminalIO::getInstance();
    announcementEnabled = state;
    if (state == TunerTypes::TunerTypes::Activation::INACTIVE) {
        announcementType.clear();
    }
    MY_TRACE(cout << "HMI id " << hmiId << " announcementEnabled set to " << tio->getActivation(state) << endl);
}

TunerTypes::TunerTypes::Activation
HMI::getAnnouncementHandling()
{
    return announcementEnabled;
}

void
HMI::setAnnouncementConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType type, TunerTypes::TunerTypes::Activation active, uint32_t priority)
{
    AnnouncementConfig x;
    auto tio = MyTerminalIO::getInstance();
    //x.active = enabled;
    x.active = active;
    x.priority = priority;
    announcementType[type] = x;
    MY_TRACE(cout << "HMI id " << hmiId << " announcementType " << tio->getAnnouncementType(type) << " enabled set to " << tio->getActivation(active) <<
            " priority to " << priority << endl);
}

TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions
HMI::getAnnouncementConfiguration()
{
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions out;
    //class AnnouncementConfig {
    //   public:
    //      bool active;
     //     uint32_t priority;
    //};
    //map <TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType, AnnouncementConfig> announcementType;

    /*
     * it is unclear, whether we should send back info about all possible announcement types,
     * even if they are currently not included in our map, or not. Consider that in the map there
     * may be entries that activate or deactivate entries. However for some other entries, there
     * may be no entry at all, we have to assume that this also means disabled.
     */

    //out.activity = announcementEnabled;
    out.active = announcementEnabled;
    int n = announcementType.size();
    out.typeConfiguration.resize(n);
    int i = 0;
    for (auto it = announcementType.cbegin(); it != announcementType.cend(); it++, i++) {
        TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType x = (*it).first;
        AnnouncementConfig y = (*it).second;
        out.typeConfiguration[i].type = x;
        out.typeConfiguration[i].priority = y.priority;
        out.typeConfiguration[i].active = y.active;
    }

    return out;
}


//bool
TunerTypes::TunerTypes::Activation
HMI::getAnnouncementConfigurationEnabled(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType type)
{
    try {
        return announcementType.at(type).active;
    } catch (exception e) {
        //return false;
	return TunerTypes::TunerTypes::Activation::INACTIVE;
    }
}

bool
HMI::getAnnouncementConfigurationPriority(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType type)
{
    try {
        return announcementType.at(type).priority;
    } catch (exception e) {
        return 0;
    }
}

bool
HMI::addActiveAnnouncement(uint32_t componentID,
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType announcementType)
{
    auto tio = MyTerminalIO::getInstance();
    auto it = activeAnnouncements.find(componentID);
    if (it != activeAnnouncements.end()) {
        // cannot insert same announcement twice
        return false;
    }
    activeAnnouncements[componentID] = announcementType;
    MY_TRACE(cout << "HMI " << hmiId << " added announcementType " << tio->getAnnouncementType(announcementType) <<
            " from componentID " << componentID << " to list of active announcements." << endl);
    return true;
}

bool
HMI::deleteActiveAnnouncement(uint32_t componentID)
{
    auto tio = MyTerminalIO::getInstance();
    auto it = activeAnnouncements.find(componentID);
    if (it == activeAnnouncements.end()) {
        return false;
    } else {
        MY_TRACE(cout << "HMI " << hmiId << " removing announcementType " <<
            tio->getAnnouncementType(activeAnnouncements[componentID]) <<
            " from componentID " << componentID << " from list of active announcements." << endl);
        activeAnnouncements.erase(componentID);
        return true;
    }
}

bool
HMI::isActiveAnnouncement(uint32_t componentID)
{
    auto it = activeAnnouncements.find(componentID);
    if (it == activeAnnouncements.end()) {
        return false;
    } else {
        return true;
    }
}

map<uint32_t,
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType>
HMI::getActiveAnnouncements()
{
    return activeAnnouncements;
}

Tuner::Tuner(int m_tunerId, TunerList *m_tunerList, int m_minFrequency, int m_maxFrequency, TunerStationTypes::TunerStationTypes::DeviceType m_deviceType)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    tunerId = m_tunerId;
    tunerList = m_tunerList;
    // frequency = 87500; // now done in child class constructor
    state = TunerState::IDLE;
    assignedToHmi = NULL;
    minFrequency = m_minFrequency;
    maxFrequency = m_maxFrequency;
    deviceType = m_deviceType;
    frequency = minFrequency;
    MY_TRACE(cout << "Created Tuner id " << tunerId << endl);
}

Tuner::~Tuner()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Destroyed Tuner id " << tunerId << endl);
}


void
Tuner::alloc(HMI *m_hmi)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    if (assignedToHmi != NULL) {
        throw invalid_argument("Tuner already assigned");
        //throw bad_alloc("Tuner already assigned");
    }
    assignedToHmi = m_hmi;
    MY_TRACE(cout << "Tuner id " << tunerId << " now assigned to HMI id " << m_hmi->getHMIId() << endl);
}

void
Tuner::free(HMI *m_hmi)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    if (assignedToHmi == NULL) {
        throw invalid_argument("Tuner not assigned");
        //throw bad_alloc("Tuner not assigned");
    }
    assignedToHmi = NULL;
    state = TunerState::IDLE;
    MY_TRACE(cout << "Tuner id " << tunerId << " no longer assigned to HMI id " << m_hmi->getHMIId() << endl);
}

bool
Tuner::stationFound(int m_frequency)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MyFileIO *fio = MyFileIO::getInstance();

    if (deviceType == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
        TunerStationTypes::TunerStationTypes::Station *x;

        x = fio->getReceivableAMFMStationByFrequency(m_frequency);
        if (x != NULL) {
            return true;
        }
    } else if (deviceType == TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
        TunerStationTypes::TunerStationTypes::Station *x;

        x = fio->getReceivableDABStationByFrequency(m_frequency);
        if (x != NULL) {
            return true;
        }
    }

    return false;
}

void
Tuner::setFrequency(int m_frequency)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    // FM case only
    int old_frequency = frequency;

    if (frequency < minFrequency || frequency > maxFrequency) {
        throw invalid_argument("invalid frequency");
    }
    frequency = m_frequency;
    MY_TRACE(cout << "Tuner id " << tunerId << " frequency changed from " << old_frequency << " to " << frequency << endl);
}

void
Tuner::incrFrequency()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    // FM case only
    int old_frequency = frequency;

    if (frequency < getMaxFrequency()) {
        frequency += 100;
        MY_TRACE(cout << "Tuner id " << tunerId << " frequency changed from " << old_frequency << " to " << frequency << endl);
    }
}

void
Tuner::decrFrequency()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    // FM case only
    int old_frequency = frequency;

    if (frequency > minFrequency) {
        frequency -= 100;
        MY_TRACE(cout << "Tuner id " << tunerId << " frequency changed from " << old_frequency << " to " << frequency << endl);
    }
}

bool
Tuner::scanUpFrequency()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);
    int old_frequency = frequency;

    if (frequency < getMaxFrequency()) {
        frequency += 100;
        MY_TRACE(cout << "Tuner id " << tunerId << " frequency changed from " << old_frequency << " to " << frequency << endl);
    } else {
        return true;
    }

    if (stationFound(frequency)) {
        return true;
    }

    return false;
}

bool
Tuner::scanDownFrequency()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);
    int old_frequency = frequency;

    if (frequency > minFrequency) {
        frequency -= 100;
        MY_TRACE(cout << "Tuner id " << tunerId << " frequency changed from " << old_frequency << " to " << frequency << endl);
    } else {
        return true;
    }

    if (stationFound(frequency)) {
        return true;
    }

    return false;
}

bool
Tuner::autoStore()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);
    int old_frequency = frequency;

    frequency += 100;
    MY_TRACE(cout << "Tuner id " << tunerId << " frequency changed from " << old_frequency << " to " << frequency << endl);
    if (frequency >= getMaxFrequency()) {
        MY_TRACE(cout << "Tuner id " << tunerId << " current frequency " << old_frequency << " maxFrequency " << getMaxFrequency() << endl);
        return true;
    }

    // store stations

    return false;
}

void
Tuner::setState(TunerState m_state)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);
    // check whether state transition is allowed
    TunerState oldState = state;

    switch(state) {
        case TunerState::IDLE:
            if (m_state == TunerState::TUNING || m_state == TunerState::SCANNING) {
                state = m_state;
                frequency = minFrequency;
                MY_TRACE(cout << "Tuner id " << tunerId << " state change from " << getStateString(oldState) << " to " << getStateString(state) << endl);
                return;
            }
            break;
        case TunerState::TUNING:
            if (m_state == TunerState::TUNED || m_state == TunerState::IDLE) {
                state = m_state;
                MY_TRACE(cout << "Tuner id " << tunerId << " state change from " << getStateString(oldState) << " to " << getStateString(state) << endl);
                return;
            }
            break;
        case TunerState::TUNED:
            if (m_state == TunerState::IDLE || m_state == TunerState::TUNING) {
                state = m_state;
                MY_TRACE(cout << "Tuner id " << tunerId << " state change from " << getStateString(oldState) << " to " << getStateString(state) << endl);
                return;
            }
            break;
        case TunerState::SCANNING:
            if (m_state == TunerState::IDLE) {
                state = m_state;
                MY_TRACE(cout << "Tuner id " << tunerId << " state change from " << getStateString(oldState) << " to " << getStateString(state) << endl);
                return;
            }
            break;
        default:
            throw invalid_argument("invalid tuner state");
    }
    MY_TRACE(cout << "Tuner id " << tunerId << " INVALID state change from " << getStateString(oldState) << " to " << getStateString(m_state) << endl);
    throw invalid_argument("invalid tuner state transition");
}

TunerState
Tuner::getState()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return state;
}

string
Tuner::getStateString(TunerState m_state)
{
    switch(m_state) {
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

HMI *
Tuner::getCurrentAssignment()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return assignedToHmi;
}

int
Tuner::getFrequency()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return frequency;
}

int
Tuner::getTunerId()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return tunerId;
}

int
Tuner::getMinFrequency()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return minFrequency;
}

int
Tuner::getMaxFrequency()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return maxFrequency;
}

TunerStationTypes::TunerStationTypes::DeviceType
Tuner::getDeviceType()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return deviceType;
}

TunerStationTypes::TunerStationTypes::Station
Tuner::getTunedStation()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    TunerStationTypes::TunerStationTypes::Station myStation;
    MyFileIO *fio = MyFileIO::getInstance();

    if (deviceType == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
        TunerStationTypes::TunerStationTypes::Station *x;

        x = fio->getReceivableAMFMStationByFrequency(frequency);
        if (x != NULL) {
            myStation = *x;
        } else {
            // setup some fake AMFM station record

            myStation.stationType = (int32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF;
            myStation.sel.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::AMFM;
            myStation.sel.id.resize(4);
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY] = 0;
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY] = frequency;
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI] = 0;
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_SERVICE] = 0;

            myStation.name.resize(3);
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_PS] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_HD] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexAmFm::AMFM_NAM_RT] = "Not applicable";

            myStation.meta.resize(1);
            myStation.meta[0].type = 0;
            myStation.meta[0].str = "Not applicable";

            myStation.genre.resize(1);
            myStation.genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexAmFm::AMFM_GEN_PTY] = 0;

            myStation.flags.resize(1);
            myStation.flags[0] = 0;

            myStation.quality.resize(3);
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_FIELDSTRENGTH] = 0;
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_MULTIPATH] = 0;
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexAmFm::AMFM_QAL_DIGITAL] = 0;
        }
    } else if (deviceType == TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
        TunerStationTypes::TunerStationTypes::Station *x;

        x = fio->getReceivableDABStationByFrequency(frequency);
        if (x != NULL) {
            myStation = *x;
        } else {
            // setup some fake DAB station record
            myStation.stationType = (int32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF;
            myStation.sel.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::DAB;
            myStation.sel.id.resize(5);
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY] = 0;
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY] = frequency;
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_ENSEMBLE] = 0;
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE] = 0;
            myStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_COMPONENT] = 0;

            myStation.name.resize(8);
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_CLONG] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_CSHORT] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_DYNAMIC] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SLONG] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_SSHORT] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_ELONG] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_ESHORT] = "Not applicable";
            myStation.name[(uint32_t)TunerStationTypes::TunerStationTypes::NameIndexDab::DAB_NAM_FREQUENCY] = "Not applicable";

            myStation.meta.resize(1);
            myStation.meta[0].type = 0;
            myStation.meta[0].str = "Not applicable";

            myStation.genre.resize(2);
            myStation.genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexDab::DAB_GEN_STATIC_PTY] = 0;
            myStation.genre[(uint32_t)TunerStationTypes::TunerStationTypes::GenreIndexDab::DAB_GEN_DYNAMIC_PTY] = 0;

            myStation.flags.resize(1);
            myStation.flags[0] = 0;

            myStation.quality.resize(3);
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_BER] = 0;
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_SERVICE] = 0;
            myStation.quality[(uint32_t)TunerStationTypes::TunerStationTypes::QualityIndexDab::DAB_QAL_AUDIO] = 0;
        }
    } else {
        // error
    }
    return myStation;
}


FMTuner::FMTuner(int m_tunerId, TunerList *m_tunerList) :
    Tuner::Tuner(m_tunerId, m_tunerList, minFrequencyFM, maxFrequencyFM, TunerStationTypes::TunerStationTypes::DeviceType::AMFM)
    // Tuner::Tuner(m_tunerId, m_tunerList, 87500, 108000)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Created FMTuner id " << tunerId << endl);
}

FMTuner::~FMTuner()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Destroyed FMTuner id " << tunerId << endl);
}

DABTuner::DABTuner(int m_tunerId, TunerList *m_tunerList) :
    Tuner::Tuner(m_tunerId, m_tunerList, minFrequencyDAB, maxFrequencyDAB, TunerStationTypes::TunerStationTypes::DeviceType::DAB)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Created DABTuner id " << tunerId << endl);
}

DABTuner::~DABTuner()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Destroyed DABTuner id " << tunerId << endl);
}

TunerList *
Tuner::getTunerList()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return tunerList;
}

TunerList::TunerList(int m_numberOfFMTuners, int m_numberOfDABTuners) {
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    for (int i = 0; i < m_numberOfFMTuners; i++) {
        tunerListFM.push_back(new FMTuner(i, this));
    }
    for (int i = 0; i < m_numberOfFMTuners; i++) {
        tunerListDAB.push_back(new DABTuner(i, this));
    }
    MY_TRACE(cout << "Created TunerList with " << m_numberOfFMTuners << " FM Tuners and " <<
        m_numberOfDABTuners << " DAB tuners." << endl);
};

TunerList::~TunerList() {
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    for (int i = 0; i < tunerListFM.size(); i++) {
        delete tunerListFM[i];
    }
    for (int i = 0; i < tunerListDAB.size(); i++) {
        delete tunerListDAB[i];
    }
    MY_TRACE(cout << "Deleted TunerList." << endl);
}

Tuner *
TunerList::allocTuner(HMI *m_hmi, TunerStationTypes::TunerStationTypes::DeviceType deviceType)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Searching free tuner for HMI id " << m_hmi->getHMIId() << endl);

    switch(deviceType) {
        case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
            // check whether there is some tuner assigned to HMI, possibly in
            // TUNED state
            for (auto it = tunerListFM.cbegin(); it != tunerListFM.cend(); ++it) {
                if ((*it)->getCurrentAssignment() == m_hmi) {
                    MY_TRACE(cout << "Found already assigned tuner id " << (*it)->getTunerId() << endl);
                    return *it;
                }
            }

            // search for free tuner in IDLE state
            for (auto it = tunerListFM.cbegin(); it != tunerListFM.cend(); ++it) {
                if ((*it)->getState() == TunerState::IDLE && (*it)->getCurrentAssignment() == NULL) {
                    (*it)->alloc(m_hmi);
                    MY_TRACE(cout << "Found free tuner id " << (*it)->getTunerId() << endl);
                    return *it;
                }
            }

            MY_TRACE(cout << "No free tuner available" << endl);
            // use NULL at the moment, might want to change to exception later
            return NULL;
        case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
            // check whether there is some tuner assigned to HMI, possibly in
            // TUNED state
            for (auto it = tunerListDAB.cbegin(); it != tunerListDAB.cend(); ++it) {
                if ((*it)->getCurrentAssignment() == m_hmi) {
                    MY_TRACE(cout << "Found already assigned tuner id " << (*it)->getTunerId() << endl);
                    return *it;
                }
            }

            // search for free tuner in IDLE state
            for (auto it = tunerListDAB.cbegin(); it != tunerListDAB.cend(); ++it) {
                if ((*it)->getState() == TunerState::IDLE && (*it)->getCurrentAssignment() == NULL) {
                    (*it)->alloc(m_hmi);
                    MY_TRACE(cout << "Found free tuner id " << (*it)->getTunerId() << endl);
                    return *it;
                }
            }

            MY_TRACE(cout << "No free tuner available" << endl);
            // use NULL at the moment, might want to change to exception later
            return NULL;
        default:
            MY_TRACE(cout << "Wrong deviceType" << endl);
            return NULL;
    }
}

void
TunerList::freeTuner(HMI *m_hmi, Tuner *m_tuner)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Free tuner id " << m_tuner->getTunerId() << endl);
    m_tuner->free(m_hmi);
}

set <Tuner *>
TunerList::getTunersForHMI(HMI *m_hmi)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);
    set <Tuner *> list;

    for (auto it = tunerListFM.cbegin(); it != tunerListFM.cend(); ++it) {
        if ((*it)->getCurrentAssignment() == m_hmi) {
            list.insert(*it);
        }
    }
    for (auto it = tunerListDAB.cbegin(); it != tunerListDAB.cend(); ++it) {
        if ((*it)->getCurrentAssignment() == m_hmi) {
            list.insert(*it);
        }
    }

    return list;
}

HMIList::HMIList(
    std::shared_ptr<TunerStationIndividualStub> m_stationStub,
    std::shared_ptr<TunerAdditionalServiceIndividualStub> m_additionalServiceStub
) : stationStub(m_stationStub), additionalServiceStub(m_additionalServiceStub)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    hmiList.clear();
    MY_TRACE(cout << "Created HMI list." << endl);
}

HMIList::~HMIList()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Destroyed HMI list." << endl);
}


std::shared_ptr<TunerAdditionalServiceIndividualStub>
HMIList::getAdditionalServiceStub()
{
    return additionalServiceStub;
}


HMI *
HMIList::createHMI(int m_hmiId)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    HMI *hmi = new HMI(m_hmiId, this);
    hmiList.insert(hmi);
    MY_TRACE(cout << "CreateHMI done. Now " << hmiList.size() << " entries." << endl);
    return hmi;
}

void
HMIList::deleteHMIbyNumber(int m_hmiId)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    HMI *hmiFound;
    bool found = false;
    for (auto it = hmiList.cbegin(); it != hmiList.cend(); ++it) {
        if ((*it)->getHMIId() == m_hmiId) {
            hmiFound = (*it);
            found = true;
            break;
        }
    }
    if (found) {
        hmiList.erase(hmiFound);
        delete hmiFound;
    }
}

HMI *
HMIList::getHMIbyNumber(int m_hmiId)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);
    HMI *hmiFound;
    bool found = false;

    for (auto it = hmiList.cbegin(); it != hmiList.cend(); ++it) {
        if ((*it)->getHMIId() == m_hmiId) {
            return (*it);
        }
    }
    return NULL;
}

void
HMIList::deleteHMI(HMI *hmi)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    hmiList.erase(hmi);
    delete hmi;
}

set<HMI *>
HMIList::getHMIList()
{
    return hmiList;
}

int Job::globalJobId = 0;

// base constructor, used by others
Job::Job(JobType m_jobType, Tuner *m_tuner, HMI *m_hmi, struct timeval m_tv, TunerStationIndividualStub *m_stub)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    jobType = m_jobType;
    tuner = m_tuner;
    hmi = m_hmi;
    tv = m_tv;
    stub = m_stub;
    jobId = globalJobId++;

    switch(jobType) {
        case JobType::TUNE_TO:
            tuner->setState(TunerState::TUNING);
            break;
        case JobType::ABORT_TUNE:
            // no action here, will be done after delay
            break;
        case JobType::MANUAL_DOWN:
            tuner->setState(TunerState::TUNING);
            break;
        case JobType::MANUAL_UP:
            tuner->setState(TunerState::TUNING);
            break;
        case JobType::AUTO_DOWN:
            tuner->setState(TunerState::TUNING);
            break;
        case JobType::AUTO_UP:
            tuner->setState(TunerState::TUNING);
            break;
        case JobType::AUTOSTORE:
            tuner->setState(TunerState::SCANNING);
            if (tuner->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                hmi->setLastSeekNotificationValueAMFM(0);
            } else {
                // DAB
                hmi->setLastSeekNotificationValueDAB(0);
            }
            break;
        case JobType::CURRENT_STATION:
            //tuner->setState(TunerState::SCANNING);
            break;
        case JobType::CANCEL:
            // do nothing
            break;
        default:
            throw invalid_argument("invalid jobType");
    }

    MY_TRACE(cout << "Created Job id " << jobId << " for Job Type " << (int)jobType << " with HMI id " << hmi->getHMIId() << " and Tuner id " << tuner->getTunerId() << endl);
}

// this one is to be removed later since new on is startTune one
Job::Job(JobType m_jobType, Tuner *m_tuner, HMI *m_hmi, struct timeval m_tv, TunerStationIndividualStub *stub, int m_frequency)
    : Job::Job(m_jobType, m_tuner, m_hmi, m_tv, stub)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    frequency = m_frequency;
}

// startTune
Job::Job(
    JobType m_jobType,
    Tuner *m_tuner,
    HMI *m_hmi,
    struct timeval m_tv,
    TunerStationIndividualStub *stub,
    TunerStationTypes::TunerStationTypes::StationSelector m_station,
    TunerStationTypes::TunerStationTypes::SelectionMode m_selectionMode,
    uint32_t m_handle
) : Job::Job(m_jobType, m_tuner, m_hmi, m_tv, stub)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    station = m_station;
    selectionMode = m_selectionMode;
    handle = m_handle;
}

// abortTune
Job::Job(
    JobType m_jobType,
    Tuner *m_tuner,
    HMI *m_hmi,
    struct timeval m_tv,
    TunerStationIndividualStub *stub,
    TunerStationTypes::TunerStationTypes::DeviceType m_device,
    uint32_t m_handle
) : Job::Job(m_jobType, m_tuner, m_hmi, m_tv, stub)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    device = m_device;
    handle = m_handle;
}

// seek
Job::Job(
    JobType m_jobType,
    Tuner *m_tuner,
    HMI *m_hmi,
    struct timeval m_tv,
    TunerStationIndividualStub *stub,
    TunerStationTypes::TunerStationTypes::DeviceType m_device,
    TunerStationTypes::TunerStationTypes::SeekMode m_seekMode,
    uint8_t m_genre,
    TunerTypes::TunerTypes::UInt32s m_flags,
    uint32_t m_handle
) : Job::Job(m_jobType, m_tuner, m_hmi, m_tv, stub)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    device = m_device;
    seekMode = m_seekMode;
    genre = m_genre;
    flags = m_flags;
    handle = m_handle;
}


// makePermanent
Job::Job(
    JobType m_jobType,
    Tuner *m_tuner,
    HMI *m_hmi,
    struct timeval m_tv,
    TunerStationIndividualStub *stub,
    TunerStationTypes::TunerStationTypes::StationSelector m_station,
    bool m_permanent,
    uint32_t m_handle
) : Job::Job(m_jobType, m_tuner, m_hmi, m_tv, stub)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    station = m_station;
    permanent = m_permanent;
    handle = m_handle;
}

// controlUpdate
Job::Job(
    JobType m_jobType,
    Tuner *m_tuner,
    HMI *m_hmi,
    struct timeval m_tv,
    TunerStationIndividualStub *stub,
    TunerStationTypes::TunerStationTypes::UpdateElement m_updateElement,
    TunerStationTypes::TunerStationTypes::UpdateType m_updateType,
    uint32_t m_sourceType,
    uint32_t m_stationType,
    uint32_t m_handle
) : Job::Job(m_jobType, m_tuner, m_hmi, m_tv, stub)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    updateElement = m_updateElement;
    updateType = m_updateType;
    sourceType = m_sourceType;
    handle = m_handle;
}


Job::~Job()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Destroyed Job id " << jobId << endl);
}

int
Job::getJobId()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return jobId;
}

HMI *
Job::getHMI()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return hmi;
}

Tuner *
Job::getTuner()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return tuner;
}

// following function returns value from parameter
// not from actual private value!
string
Job::getJobTypeString(JobType m_jobType)
{
    switch(m_jobType) {
        case JobType::TUNE_TO:
            return("TUNE_TO");
        case JobType::ABORT_TUNE:
            return("ABORT_TUNE");
        case JobType::MANUAL_DOWN:
            return("MANUAL_DOWN");
        case JobType::MANUAL_UP:
            return("MANUAL_UP");
        case JobType::AUTO_DOWN:
            return("AUTO_DOWN");
        case JobType::AUTO_UP:
            return("AUTO_UP");
        case JobType::AUTOSTORE:
            return("AUTOSTORE");
        case JobType::CURRENT_STATION:
            return("CURRENT_STATION");
        case JobType::CANCEL:
            return("CANCEL");
        default:
            throw invalid_argument("invalid jobType");
    }
}

JobType
Job::getJobType()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return jobType;
}

void
Job::sendStationEvent()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    TunerStationTypes::TunerStationTypes::Station broadcast_current;
    uint32_t broadcast_handle = handle;
    MyFileIO *fio = MyFileIO::getInstance();

    broadcast_current = tuner->getTunedStation();
    stub->fireCurrentStationEvent(broadcast_current, broadcast_handle);
}

bool
Job::continueJob(JobQueue *jobQueue)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    bool finished = false;
    TunerList *m_tunerList;
    MY_TRACE(cout << "Continuing Job id " << jobId << " jobType " << getJobTypeString(jobType) << endl);
    int delta = 32500;
    MyFileIO *fio = MyFileIO::getInstance();

    switch(jobType) {
        case JobType::TUNE_TO:
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

            if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_DIRECT) {
                switch((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType) {
                    case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
                        tuner->setFrequency(station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
                        break;
                    case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
                        tuner->setFrequency(station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY]);
                        break;
                    case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
                        // fallthrough
                    default:
                        // illegal
                        break;
                }
            } else if (selectionMode == TunerStationTypes::TunerStationTypes::SelectionMode::SM_LIST) {
                uint32_t key;
                MyFileIO *fio = MyFileIO::getInstance();
                TunerStationTypes::TunerStationTypes::Station x_station;
                TunerStationTypes::TunerStationTypes::Station *y_station;

                switch((TunerStationTypes::TunerStationTypes::DeviceType)station.deviceType) {
                    case TunerStationTypes::TunerStationTypes::DeviceType::AMFM:
                        key = station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_KEY];
                        x_station = fio->getReceivableAMFMStationByIndex(key);
                        tuner->setFrequency(x_station.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
                        break;
                    case TunerStationTypes::TunerStationTypes::DeviceType::DAB:
                        key = station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY];
                        x_station = fio->getReceivableDABStationByIndex(key);
                        tuner->setFrequency(x_station.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY]);
                        break;
                    case TunerStationTypes::TunerStationTypes::DeviceType::UNDEF_DEVICE:
                        key = station.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_KEY];
                        // the key is the PI code or Service id
                        // try DAB first
                        y_station = fio->getReceivableDABStationByServiceId(key);
                        if (y_station == NULL) {
                            y_station = fio->getReceivableAMFMStationByPICode(key);
                            if (y_station == NULL) {
                                // error
                            } else {
                                tuner->setFrequency(y_station->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_FREQUENCY]);
                            }
                        } else {
                            tuner->setFrequency(y_station->sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_FREQUENCY]);
                        }

                        break;
                    default:
                        // illegal
                        break;
                }
            }

            tuner->setState(TunerState::TUNED);
            sendStationEvent();
            finished = true;
            break;
        case JobType::ABORT_TUNE:
            {
#ifdef WITH_ADDITIONAL_SERVICES
                TunerStationTypes::TunerStationTypes::Station currentStation;

                currentStation = tuner->getTunedStation();
                if (currentStation.stationType != (int32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF) {
                    // station was receivable
                    uint32_t code = 0;
                    int found = 0;
                    uint32_t componentID;

                    if (currentStation.sel.deviceType == (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::AMFM) {
                        code = currentStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexAmFm::AMFM_ID_PI];
                    } else if (currentStation.sel.deviceType == (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::DAB) {
                        code = currentStation.sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexDab::DAB_ID_SERVICE];
                    } else {
                        // error
                    }

                    // must set state to IDLE here, so that getTunedStations() ignores our tuner
                    tuner->setState(TunerState::IDLE);

                    TunerStationTypes::TunerStationTypes::StationList stationList;
                    stationList = getTunedStations();

                    for (auto it = stationList.stations.cbegin(); it != stationList.stations.cend(); it++) {
                        if ((*it).sel.id[(uint32_t)TunerStationTypes::TunerStationTypes::IdIndexUndef::UNDEF_ID_KEY] == code) {
                            found++;
                            break;
                        }
                    }
                    if (!found) {
                        componentID = fio->assignComponentID(code);
                        finishAllAnnouncementsForComponentID(hmi->getHMIList()->getAdditionalServiceStub(), componentID);
                    }
                } else {
                    tuner->setState(TunerState::IDLE);
                }
#else
                tuner->setState(TunerState::IDLE);
#endif
                m_tunerList = tuner->getTunerList();
                m_tunerList->freeTuner(hmi, tuner);
                finished = true;
            }
            break;
        case JobType::MANUAL_DOWN:
            tuner->decrFrequency();
            tuner->setState(TunerState::TUNED);
            sendStationEvent();
            finished = true;
            break;
        case JobType::MANUAL_UP:
            tuner->incrFrequency();
            tuner->setState(TunerState::TUNED);
            sendStationEvent();
            finished = true;
            break;
        case JobType::AUTO_DOWN:
            finished = tuner->scanDownFrequency();
            if (finished) {
                TunerStationTypes::TunerStationTypes::SeekData broadcast_seekData;

                tuner->setState(TunerState::TUNED);
                sendStationEvent();

                // send SM_OFF broadcast
                broadcast_seekData.mode = TunerStationTypes::TunerStationTypes::SeekMode::SM_OFF;
                broadcast_seekData.returnValue = TunerStationTypes::TunerStationTypes::SeekReturnValue::SM_FREQUENCY;
                broadcast_seekData.data = tuner->getFrequency();
                stub->fireSeekEvent(broadcast_seekData, handle);
            } else {
                int freq;
                // check whether to send seek broadcast
                if ((freq = tuner->getFrequency()) % 100 == 0) {
                    if (((tuner->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) &&
                         hmi->getUpdateSeekNotificationAMFM() == true) ||
                        ((tuner->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::DAB) &&
                         hmi->getUpdateSeekNotificationDAB() == true)) {
                        TunerStationTypes::TunerStationTypes::SeekData broadcast_seekData;

                        broadcast_seekData.mode = TunerStationTypes::TunerStationTypes::SeekMode::SM_AUTO_DOWN;
                        broadcast_seekData.returnValue = TunerStationTypes::TunerStationTypes::SeekReturnValue::SM_FREQUENCY;
                        broadcast_seekData.data = freq;
                        uint32_t broadcast_handle = handle;

                        stub->fireSeekEvent(broadcast_seekData, broadcast_handle);
                    }
                }
            }
            break;
        case JobType::AUTO_UP:
            finished = tuner->scanUpFrequency();
            if (finished) {
                TunerStationTypes::TunerStationTypes::SeekData broadcast_seekData;

                tuner->setState(TunerState::TUNED);
                sendStationEvent();

                // send SM_OFF broadcast
                broadcast_seekData.mode = TunerStationTypes::TunerStationTypes::SeekMode::SM_OFF;
                broadcast_seekData.returnValue = TunerStationTypes::TunerStationTypes::SeekReturnValue::SM_FREQUENCY;
                broadcast_seekData.data = tuner->getFrequency();
                stub->fireSeekEvent(broadcast_seekData, handle);
            } else {
                int freq;
                // check whether to send seek broadcast
                if ((freq = tuner->getFrequency()) % 100 == 0) {
                    if (((tuner->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::AMFM) &&
                         hmi->getUpdateSeekNotificationAMFM() == true) ||
                        ((tuner->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::DAB) &&
                         hmi->getUpdateSeekNotificationDAB() == true)) {
                        TunerStationTypes::TunerStationTypes::SeekData broadcast_seekData;

                        broadcast_seekData.mode = TunerStationTypes::TunerStationTypes::SeekMode::SM_AUTO_UP;
                        broadcast_seekData.returnValue = TunerStationTypes::TunerStationTypes::SeekReturnValue::SM_FREQUENCY;
                        broadcast_seekData.data = freq;
                        uint32_t broadcast_handle = handle;

                        stub->fireSeekEvent(broadcast_seekData, broadcast_handle);
                    }
                }
            }
            break;
        case JobType::AUTOSTORE:
            {
                finished = tuner->autoStore();
                bool deviceTypeIsAMFM = (tuner->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::AMFM);
                bool deviceTypeIsDAB = (tuner->getDeviceType() == TunerStationTypes::TunerStationTypes::DeviceType::DAB);

                if (finished) {
                    MyFileIO *fio = MyFileIO::getInstance();
                    TunerStationTypes::TunerStationTypes::SeekData broadcast_seekData;
                    bool doSendBroadCast = false;

#if 0
                    if ((deviceTypeIsAMFM && hmi->getUpdateSeekNotificationAMFM() == true) ||
                        (deviceTypeIsDAB && hmi->getUpdateSeekNotificationDAB() == true)) {

                        // must prepare the broadcast contents before freeing the tuner, but send later
                        broadcast_seekData.mode = TunerStationTypes::TunerStationTypes::SeekMode::SM_AUTOSTORE;
                        broadcast_seekData.returnValue = TunerStationTypes::TunerStationTypes::SeekReturnValue::SM_PERCENTAGE;
                        broadcast_seekData.data = 100; // we are finished, so we have 100%
                        doSendBroadCast = true;
                    }
#endif
                    // send last broadcast unconditionally, no check for notification settings
                    // must prepare the broadcast contents before freeing the tuner, but send later
                    broadcast_seekData.mode = TunerStationTypes::TunerStationTypes::SeekMode::SM_OFF;
                    broadcast_seekData.returnValue = TunerStationTypes::TunerStationTypes::SeekReturnValue::SM_PERCENTAGE;
                    broadcast_seekData.data = 100; // we are finished, so we have 100%
                    doSendBroadCast = true;

                    tuner->setState(TunerState::IDLE);

                    fio->scanStations("config", tuner->getDeviceType());

                    // prepare broadcast here, where old complete list is still available in HMI
                    TunerStationTypes::TunerStationTypes::StationList broadcast_list;
                    if (deviceTypeIsAMFM && hmi->getUpdateStationListNotificationAMFM() == true) {
                        broadcast_list.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::AMFM;
                        broadcast_list.stationType = (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF;
                        broadcast_list.stations = fio->getUpdateStationList(hmi->getCompleteListAMFM(), fio->getCompleteAMFMStationList());
                    } else if (deviceTypeIsDAB && hmi->getUpdateStationListNotificationDAB() == true) {
                        broadcast_list.deviceType = (uint32_t)TunerStationTypes::TunerStationTypes::DeviceType::DAB;
                        broadcast_list.stationType = (uint32_t)TunerStationTypes::TunerStationTypes::StationType::ST_UNDEF;
                        broadcast_list.stations = fio->getUpdateStationList(hmi->getCompleteListDAB(), fio->getCompleteDABStationList());
                    }

                    // store current list in HMI
                    if (deviceTypeIsAMFM) {
                        hmi->setCompleteListAMFM(fio->getCompleteAMFMStationList());
                    } else if (deviceTypeIsDAB) {
                        hmi->setCompleteListDAB(fio->getCompleteDABStationList());
                    }

                    m_tunerList = tuner->getTunerList();
                    m_tunerList->freeTuner(hmi, tuner);

                    if (doSendBroadCast == true) {
                        stub->fireSeekEvent(broadcast_seekData, handle);
                    }

                    // send list of updated stations via broadcast, if requested and list is not empty
                    if ((deviceTypeIsAMFM && hmi->getUpdateStationListNotificationAMFM() == true) ||
                        (deviceTypeIsDAB && hmi->getUpdateStationListNotificationDAB() == true)) {
                        if (broadcast_list.stations.size() > 0) {
                            stub->fireStationListEvent(broadcast_list, handle);
                        }
                    }
                } else {
                    int freq;
                    int percentage;
                    // check whether to send seek broadcast
                    freq = tuner->getFrequency();
                    percentage = (freq - tuner->getMinFrequency()) * 100 / (tuner->getMaxFrequency() - tuner->getMinFrequency());

                    cout << "Freq is " << freq << " and percentage is " << percentage << endl;
                    if ((percentage % 10 == 0) &&
                        ((deviceTypeIsAMFM && (hmi->getLastSeekNotificationValueAMFM() != percentage)) ||
                        (deviceTypeIsDAB && (hmi->getLastSeekNotificationValueDAB() != percentage)))) {
                        if ((deviceTypeIsAMFM && hmi->getUpdateSeekNotificationAMFM() == true) ||
                            (deviceTypeIsDAB && hmi->getUpdateSeekNotificationDAB() == true)) {
                            TunerStationTypes::TunerStationTypes::SeekData broadcast_seekData;

                            broadcast_seekData.mode = TunerStationTypes::TunerStationTypes::SeekMode::SM_AUTOSTORE;
                            broadcast_seekData.returnValue = TunerStationTypes::TunerStationTypes::SeekReturnValue::SM_PERCENTAGE;
                            broadcast_seekData.data = percentage;
                            uint32_t broadcast_handle = handle;

                            if (deviceTypeIsAMFM) {
                                hmi->setLastSeekNotificationValueAMFM(percentage);
                            } else {
                                // DAB
                                hmi->setLastSeekNotificationValueDAB(percentage);
                            }

                            stub->fireSeekEvent(broadcast_seekData, broadcast_handle);
                        }
                    }

                    // simulate faster scan on DAB
                    if (deviceTypeIsDAB) {
                        delta = 12500;
                    }
                }
            }
            break;
        case JobType::CURRENT_STATION:
            sendStationEvent();
            finished = true;
            break;
        case JobType::CANCEL:
            // The following enqueues a cancellation.
            // Would be much better if we would remove the
            // job entirely from here, however it also needs
            // to be removed from priority queue which is a problem.
            // Single elements in the queue cannot be removed due
            // to missing methods. That might interfere with later
            // new jobs which may be enqueued before the cancellation
            // has taken place. The tuner will appear to be still blocked.
            {
                Job *job;
                job = jobQueue->findJob(hmi);
                jobQueue->cancelJob(job);
                finished = true;
            }
            break;
        default:
            throw invalid_argument("invalid jobType");
            break;
    }

    if (!finished) {
        // reschedule job
        gettimeofday(&tv, NULL);
        tv.tv_usec += delta;
        // sanity
        tv.tv_sec += tv.tv_usec / 1000000;
        tv.tv_usec = tv.tv_usec % 1000000;
        jobQueue->queueJob(this);
        return true;
    } else {
        MY_TRACE(cout << "Finished Job id " << jobId << " jobType " << getJobTypeString(jobType) << endl);
        return false;
    }
}

void
Job::cancel()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    TunerList *m_tunerList;

    tuner->setState(TunerState::IDLE);
    m_tunerList = tuner->getTunerList();
    m_tunerList->freeTuner(hmi, tuner);
    MY_TRACE(cout << "Cancelled Job id " << jobId << " jobType " << getJobTypeString(jobType) << endl);
}

struct timeval
Job::getTime() const
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return tv;
}

JobQueue::JobQueue()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Created JobQueue." << endl);
}

JobQueue::~JobQueue()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    MY_TRACE(cout << "Destroyed JobQueue." << endl);
}
void
JobQueue::queueJob(Job *job)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    jobList.push(job);
    jobSet.insert(job);
    MY_TRACE(cout << "Queued Job id " << job->getJobId() << endl);
}

Job *
JobQueue::getNextJob()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);
    Job *x;

    while (!jobList.empty()) {
        x = jobList.top();
        MY_TRACE(cout << "Next Job id " << x->getJobId() << endl);
        jobList.pop();
        jobSet.erase(x);

        if (jobCancelSet.count(x) > 0) {
            // job must be cancelled
            jobCancelSet.erase(x);
            x->cancel();
            // start all over
        } else {
            // got some job
            return x;
        }
    }
    return NULL;
}

void
JobQueue::cancelJob(Job *job)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    jobCancelSet.insert(job);
}

Job *
JobQueue::findJob(HMI *m_hmi)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    for (auto it = jobSet.cbegin(); it != jobSet.cend(); ++it) {
        if ((*it)->getHMI() == m_hmi && (*it)->getJobType() != JobType::CANCEL) {
            return (*it);
        }
    }
}

Job *
JobQueue::findJob(Tuner *m_tuner)
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    for (auto it = jobSet.cbegin(); it != jobSet.cend(); ++it) {
        if ((*it)->getTuner() == m_tuner && (*it)->getJobType() != JobType::CANCEL) {
            return (*it);
        }
    }
}

bool
JobQueue::isEmpty()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    // cout << "Job queue is empty." << endl;
    return jobList.empty();
}

struct timeval
JobQueue::getTimeOfNextJob()
{
    std::lock_guard<std::recursive_mutex> lg(myJobListMutex);

    return jobList.top()->getTime();
}
