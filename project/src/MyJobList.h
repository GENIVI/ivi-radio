/*
Copyright (C) 2013 BMW Group

Author: Guido Ostkamp     (guido.ostkamp@de.bertrandt.com)
Author: Bernhard Singer   (bernhard.singer@partner.bmw.de)
Author: Matthias Freundel (matthias.freundel@partner.bmw.de)

This Source Code Form is subject to the terms of the Mozilla Public

License, v. 2.0. If a copy of the MPL was not distributed with this file,

You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef MY_JOBLIST_H
#define MY_JOBLIST_H

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <exception>
#include <stdexcept>
#include <sys/time.h>
#include <unistd.h>
#include <TunerStation/TunerStationStubDefault.h>
#include <CommonAPI/Runtime.h>
#include "myProvider.h"

using namespace std;

#define MY_TRACE(X) X;

class HMIList;

/*
 * HMI class
 *
 * This is just for management of connections between HMI and Tuners.
 * Each HMI is a frontend (invocation of "client").
 *
 */

class HMI
{
public:
    HMI(int hmiId, HMIList *m_hmiList);
    ~HMI();

    HMIList * getHMIList();

    int getHMIId();
    void setCompleteListAMFM(const vector<TunerStationTypes::TunerStationTypes::Station>& vec);
    void setCompleteListDAB(const vector<TunerStationTypes::TunerStationTypes::Station>& vec);
    void setCompleteListUndef(const vector<TunerStationTypes::TunerStationTypes::Station>& vec);

    bool getUpdateSeekNotificationAMFM();
    bool getUpdateSeekNotificationDAB();
    bool getUpdateStationListNotificationAMFM();
    bool getUpdateStationListNotificationDAB();
    bool getUpdateStationListNotificationUndef();

    void setUpdateSeekNotificationAMFM(bool val);
    void setUpdateSeekNotificationDAB(bool val);
    void setUpdateStationListNotificationAMFM(bool val);
    void setUpdateStationListNotificationDAB(bool val);
    void setUpdateStationListNotificationUndef(bool val);

    uint32_t getLastSeekNotificationValueAMFM();
    uint32_t getLastSeekNotificationValueDAB();
    void setLastSeekNotificationValueAMFM(uint32_t val);
    void setLastSeekNotificationValueDAB(uint32_t val);
    void setAnnouncementHandling(TunerTypes::TunerTypes::Activation state);
    TunerTypes::TunerTypes::Activation getAnnouncementHandling();
    
    //void setAnnouncementConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType, bool enabled, uint32_t priority);
    void setAnnouncementConfiguration(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType,      TunerTypes::TunerTypes::Activation active, uint32_t priority);
    
    //bool getAnnouncementConfigurationEnabled(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType);
    TunerTypes::TunerTypes::Activation getAnnouncementConfigurationEnabled  (TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType);
    bool getAnnouncementConfigurationPriority(TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType);
    
    //TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementConfiguration getAnnouncementConfiguration();
    TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::Announcement_TypeOptions getAnnouncementConfiguration();

    bool addActiveAnnouncement(uint32_t componentID,
        TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType announcementType);
    bool deleteActiveAnnouncement(uint32_t componentID);
    bool isActiveAnnouncement(uint32_t componentID);
    map<uint32_t,
        TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType>
    getActiveAnnouncements();

    vector<TunerStationTypes::TunerStationTypes::Station> getCompleteListAMFM();
    vector<TunerStationTypes::TunerStationTypes::Station> getCompleteListDAB();
    vector<TunerStationTypes::TunerStationTypes::Station> getCompleteListUndef();

private:
    int hmiId;
    bool updateSeekNotificationAMFM;
    bool updateSeekNotificationDAB;
    bool updateStationListNotificationAMFM;
    bool updateStationListNotificationDAB;
    bool updateStationListNotificationUndef;
    uint32_t lastSeekNotificationValueAMFM;
    uint32_t lastSeekNotificationValueDAB;
    HMIList *hmiList;
    vector<TunerStationTypes::TunerStationTypes::Station> completeListAMFM;
    vector<TunerStationTypes::TunerStationTypes::Station> completeListDAB;
    vector<TunerStationTypes::TunerStationTypes::Station> completeListUndef;
    TunerTypes::TunerTypes::Activation announcementEnabled;
    class AnnouncementConfig {
        public:
            //bool active;
	    TunerTypes::TunerTypes::Activation active;
            uint32_t priority;
    };

    map <TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType, AnnouncementConfig> announcementType;
    map<uint32_t, TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> activeAnnouncements;
};

/*
 * Tuner class
 *
 * The tuner class represents a physical tuner. A tuner has a state (whether
 * it is currently performing a scan, or is tuned to some frequency) and may
 * be assigned to a HMI. This is a simplification, since in reality it might
 * be assigned to several HMIs at the same time, when it is tuned to a
 * frequency of a station, which e.g. is being listened to on front and rear
 * seats.
 */

enum class TunerState {
    IDLE,      // IDLE -> TUNING, IDLE -> SCANNING
    TUNING,    // TUNING -> TUNED
    TUNED,     // TUNED -> IDLE
    SCANNING   // SCANNING -> IDLE
};

class TunerList;

class Tuner {
public:
    Tuner(int m_tunerId, TunerList *m_tunerList, int m_minFrequency, int m_maxFrequency, TunerStationTypes::TunerStationTypes::DeviceType m_deviceType);
    virtual ~Tuner();
    void alloc(HMI *m_hmi);
    void free(HMI *m_hmi);
    void setState(TunerState m_state);
    void setFrequency(int m_frequency);
    TunerState getState();
    string getStateString(TunerState m_state);
    HMI *getCurrentAssignment();
    int getTunerId();
    int getFrequency();
    bool getSeekDone();
    TunerList *getTunerList();
    void incrFrequency();
    void decrFrequency();
    bool scanUpFrequency();
    bool scanDownFrequency();
    bool autoStore();
    bool stationFound(int m_frequency);
    int getMinFrequency();
    int getMaxFrequency();
    TunerStationTypes::TunerStationTypes::DeviceType getDeviceType();
    TunerStationTypes::TunerStationTypes::Station getTunedStation();
protected:
    TunerStationTypes::TunerStationTypes::DeviceType deviceType;
    int tunerId;
    int frequency;
    int minFrequency;
    int maxFrequency;
    HMI *assignedToHmi;
    TunerState state;
    TunerList *tunerList;
};

class FMTuner : public Tuner {
public:
    FMTuner(int m_tunerId, TunerList *m_tunerList);
    ~FMTuner();
private:
    static const int minFrequencyFM = 87500;
    static const int maxFrequencyFM = 108000;
};

class DABTuner : public Tuner {
public:
    DABTuner(int m_tunerId, TunerList *m_tunerList);
    ~DABTuner();
private:
    static const int minFrequencyDAB = 172000;
    static const int maxFrequencyDAB = 230000;
};

class TunerList
{
public:
    TunerList(int m_numberOfFMTuners, int numberOfDABTuners);
    ~TunerList();
    Tuner *allocTuner(HMI *m_hmi, TunerStationTypes::TunerStationTypes::DeviceType deviceType);
    void freeTuner(HMI *m_hmi, Tuner *m_tuner);
    set<Tuner *> getTunersForHMI(HMI *m_hmi);
private:
    vector<Tuner *> tunerListFM;
    vector<Tuner *> tunerListDAB;
};

class HMIList
{
public:
    HMIList(std::shared_ptr<TunerStationIndividualStub> stationStub, std::shared_ptr<TunerAdditionalServiceIndividualStub> additionalServiceStub);
    ~HMIList();
    HMI *createHMI(int m_hmi_number);
    HMI *getHMIbyNumber(int m_hmi_number);
    set<HMI *> getHMIList();
    void deleteHMIbyNumber(int m_hmi_number);
    void deleteHMI(HMI *hmi);
    std::shared_ptr<TunerAdditionalServiceIndividualStub> getAdditionalServiceStub();
private:
    set<HMI *> hmiList;
    std::shared_ptr<TunerStationIndividualStub> stationStub;
    std::shared_ptr<TunerAdditionalServiceIndividualStub> additionalServiceStub;
};


enum class JobType {
    TUNE_TO,
    ABORT_TUNE,
    MANUAL_DOWN,
    MANUAL_UP,
    AUTO_DOWN,
    AUTO_UP,
    AUTOSTORE,
    CURRENT_STATION,
    CANCEL
};

class JobQueue;

class Job {
public:
    Job(JobType m_jobType, Tuner *m_tuner, HMI *m_hmi, struct timeval m_tv, TunerStationIndividualStub *stub);

    Job(JobType m_jobType, Tuner *m_tuner, HMI *m_hmi, struct timeval m_tv, TunerStationIndividualStub *stub, int frequency);

    // several constructors for different jobs
    //
    // startTune
    Job(
        JobType m_jobType,
        Tuner *m_tuner,
        HMI *m_hmi,
        struct timeval m_tv,
        TunerStationIndividualStub *stub,
        TunerStationTypes::TunerStationTypes::StationSelector m_station,
        TunerStationTypes::TunerStationTypes::SelectionMode m_selectionMode,
        uint32_t m_handle
    );

    // abortTune
    Job(
        JobType m_jobType,
        Tuner *m_tuner,
        HMI *m_hmi,
        struct timeval m_tv,
        TunerStationIndividualStub *stub,
        TunerStationTypes::TunerStationTypes::DeviceType m_device,
        uint32_t m_handle
    );

    // seek
    Job(
        JobType m_jobType,
        Tuner *m_tuner,
        HMI *m_hmi,
        struct timeval m_tv,
        TunerStationIndividualStub *stub,
        TunerStationTypes::TunerStationTypes::DeviceType m_device,
        TunerStationTypes::TunerStationTypes::SeekMode seekMode,
        uint8_t genre,
        TunerTypes::TunerTypes::UInt32s flags,
        uint32_t m_handle
    );

    // makePermanent
    Job(
        JobType m_jobType,
        Tuner *m_tuner,
        HMI *m_hmi,
        struct timeval m_tv,
        TunerStationIndividualStub *stub,
        TunerStationTypes::TunerStationTypes::StationSelector m_station,
        bool permanent,
        uint32_t m_handle
    );

    // controlUpdate
    Job(
        JobType m_jobType,
        Tuner *m_tuner,
        HMI *m_hmi,
        struct timeval m_tv,
        TunerStationIndividualStub *stub,
        TunerStationTypes::TunerStationTypes::UpdateElement updateElement,
        TunerStationTypes::TunerStationTypes::UpdateType updateType,
        uint32_t sourceType,
        uint32_t stationType,
        uint32_t m_handle
    );

    ~Job();
    bool continueJob(JobQueue *jobQueue);
    struct timeval getTime() const;
    int getJobId();
    void cancel();
    HMI *getHMI();
    Tuner *getTuner();
    string getJobTypeString(JobType m_jobType);
    JobType getJobType();
private:
    struct timeval tv;   // absolute time for next invocation
    Tuner *tuner;
    HMI *hmi;
    JobType jobType;
    int jobId;

    // should be removed as its now part of station.id[]
    int frequency;

    // generic data
    uint32_t handle;
    TunerStationIndividualStub *stub;

    // startTune + makePermanent data
    TunerStationTypes::TunerStationTypes::StationSelector station;

    // startTune
    TunerStationTypes::TunerStationTypes::SelectionMode selectionMode;

    // abortTune + seek data
    TunerStationTypes::TunerStationTypes::DeviceType device;

    // seek data
    TunerStationTypes::TunerStationTypes::SeekMode seekMode;
    uint8_t genre;
    TunerTypes::TunerTypes::UInt32s flags;

    // makePermanent
    bool permanent;

    // controlUpdate
    TunerStationTypes::TunerStationTypes::UpdateElement updateElement;
    TunerStationTypes::TunerStationTypes::UpdateType updateType;
    uint32_t sourceType;
    uint32_t stationType;


    static int globalJobId;

    void sendStationEvent();
};

struct JobComparator
{
    bool operator() (Job *a, Job *b)
    {
        struct timeval aa = a->getTime();
        struct timeval bb = b->getTime();
        return(aa.tv_sec > bb.tv_sec) || (aa.tv_sec == bb.tv_sec && aa.tv_usec > bb.tv_usec);
    }
};

class JobQueue {
public:
    JobQueue();
    ~JobQueue();
    void queueJob(Job *job);
    void cancelJob(Job *job);
    Job *findJob(HMI *hmi);
    Job *findJob(Tuner *tuner);
    Job *getNextJob();
    struct timeval getTimeOfNextJob();
    bool isEmpty();
private:
    priority_queue<Job *, vector<Job *>, JobComparator> jobList;
    set<Job *> jobSet;
    set<Job *> jobCancelSet;
};
#endif /* MY_JOBLIST_H */
