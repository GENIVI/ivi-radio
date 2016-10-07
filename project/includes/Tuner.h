///////////////////////////////////////////////////////////
//  Tuner.h
//  Implementation of the Class Tuner
//  Created on:      16-Jul-2013 16:47:50
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_65C0E150_D9B3_42d8_9B5C_83F6D100F22F__INCLUDED_)
#define EA_65C0E150_D9B3_42d8_9B5C_83F6D100F22F__INCLUDED_

#include "TerminalIO.h"
#include "FileIO.h"
#include "HMI.h"

enum class TunerState {
    IDLE,      // IDLE -> TUNING, IDLE -> SCANNING
    TUNING,    // TUNING -> TUNED
    TUNED,     // TUNED -> IDLE
    SCANNING   // SCANNING -> IDLE
};

/**
 * \class Tuner
 *
 * \brief Tuner class represents a physical tuner.
 * The tuner class represents a physical tuner. A tuner has a state (whether
 * it is currently performing a scan, or is tuned to some frequency) and may
 * be assigned to a HMI. This is a simplification, since in reality it might
 * be assigned to several HMIs at the same time, when it is tuned to a
 * frequency of a station, which e.g. is being listened to on front and rear
 * seats.
 *
 *  * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2013/06/16 14:16:20
 *
 * Contact: bernhard.singer@partner.bmw.de
 *
  * Copyright
 * Copyright (C) 2013, GENIVI Alliance, Inc.
 * Copyright (C) 2013, BMW AG
 *
 * Contributions are licensed to the GENIVI Alliance under one or more
 * Contribution License Agreements or MPL 2.0 .
 *
 * (C) Copyright
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
 * this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

class Tuner
{

public:

	/**
	 * \brief default constructor
	 * \param [in] tunerId an int ID of the tuner for identification issues
	 * \param [in] *tunerList an pointer of TunerList points to the list of tuner the tuner itself is part of
	 * \param [in] minFrequency an int is the minimum frequency of the corresponding waveband
	 * \param [in] maxFrequency an int is the maximum frequency of the corresponding waveband
	 * \param [in] deviceType an DeviceType device type of the tuner (DAB, AMFM, ...)
	*/
	Tuner(int tunerId, int minFrequency, int maxFrequency, IVIRadio::Types::Types::DeviceType deviceType);

	/**
	 * \brief default destructor
    */
	virtual ~Tuner();

	/**
	 * \brief method returns the Tuner ID
	 * \return Tuner ID
	*/
	int getTunerId(){ return m_tunerId; }

    /**
	 * \brief method assigns a HMI to a Tuner if Tuner is not yet assigned
	 * \param [in] *m_hmi an HMI is the HMI the Tuner should be assigned to
    */
    void alloc(HMI *hmi);

    /**
	 * \brief method frees an assigned Tuner if Tuner is assigned to the given HMI
	 * \param [in] *m_hmi an HMI the HMI the Tuner is assigned to
    */
    void free (HMI *hmi);

    /**
	 * \brief method sets the state of the Tuner; possible state transitions are IDLE -> TUNING, IDLE -> SCANNING, TUNING -> TUNED, TUNED -> IDLE, SCANNING -> IDLE
	 * \param [in] m_state is a TunerState state the Tuner should be set to
    */
    void setState(TunerState state);

    /**
	 * \brief method sets the current frequency of the Tuner if the given frequency is in the range between minFrequency and maxFrequency
	 * \param [in] m_frequency an int the frequency the Tuner should be set to
    */
    void setFrequency(int frequency);

    /**
	 * \brief method returns the current TunerState
	 * \return current TunerState
    */
    TunerState getState();

    /**
	 * \brief method returns the current TunerState as string
	 * \return TunerState as string
    */
    std::string getStateString(TunerState state);

    /**
	 * \brief method returns the currently assigned HMI
	 * \return currently assigned HMI
    */
    HMI *getCurrentAssignment();

    /**
     * \brief method increases the current set frequency for 0.1 kHz if current frequency is not higher than maxFrequency
   */
   void incrFrequency();

   /**
    * \brief method decreases the current set frequency for 0.1 kHz if current frequency is not lower than minFrequency
   */
   void decrFrequency();

   /**
    * \brief method increases the current set frequency for 0.1 kHz if current frequency is not higher than maxFrequency and looks in the station landscape if there is a station available
	* \returns true if a station is available at the currently set frequency else false
   */
   bool scanUpFrequency();

   /**
	 * \brief method decreases the current set frequency for 0.1 kHz if current frequency is not lower than minFrequency and looks in the station landscape if there is a station available
 	 * \returns true if a station is available at the currently set frequency else false
   */
   bool scanDownFrequency();

   /**
    * \brief method decreases the current set frequency for 0.1 kHz if current frequency is not lower than minFrequency and looks in the station landscape if there is a station available
	* \returns true if a station is available at the currently set frequency else false
   */
    bool autoStore();

    /**
	 * \brief method looks in the station landscape if there is a station available
	 * \returns true if a station is available at the currently set frequency else false
	*/
	bool stationFound(int m_frequency);

	/**
	 * \brief method returns the maximal frequency the Tuner can be set to
	 * \return maximal frequency the Tuner can be set to
	*/
	int getMinFrequency();

	/**
	 * \brief method returns the minimal frequency the Tuner can be set to
	 * \return minimal frequency the Tuner can be set to
	*/
	int getMaxFrequency();

	/**
	 * \brief method returns the device type of Tuner
	 * \return device Type of the Tuner
	*/
	IVIRadio::Types::Types::DeviceType getDeviceType();

	/**
	 * \brief method returns the station the Tuner is currently tuned to
	 * \return currently tuned station
	*/
	IVIRadio::Station::StationTypes::Station getTunedStation();

	/**
	 * \brief method returns the used File IO instance
	 * \return FIle IO Instance that is used
	*/
    FileIO*      getFileIO    () { return m_FileIO; }

    /**
	 * \brief method returns the frequency the Tuner is currently set to
	 * \return currently set frequency
    */
    int getFrequency() { return m_frequency; }

private:
    /**
	* \brief deviceType device Type of the tuner (AMFM, DAB, ...)
    */
    IVIRadio::Types::Types::DeviceType m_deviceType;

    /**
	* \brief tunerId ID of the tuner
    */
    int 		m_tunerId;

    /**
	* \brief frequency current frequency
	*/
    int 		m_frequency;

    /**
	* \brief minFrequency minimal frequency the tuner can be set to (minimal frequency of the waveband of the device type)
    */
    int 		m_minFrequency;

    /**
	* \brief minFrequency maximal frequency the tuner can be set to (maximal frequency of the waveband of the device type)
    */
    int 		m_maxFrequency;

    /**
	* \brief state current state the Tuner is set to
    */
    TunerState 	m_state;

    /**
	* \brief *assignedToHmi pointer to the HMI the Tuner is currently assigned to
    */
	HMI 		*m_assignedToHmi;

    /**
	* \brief *m_FileIO File IO the Tuner uses
    */
	FileIO 		*m_FileIO;

};
#endif // !defined(EA_65C0E150_D9B3_42d8_9B5C_83F6D100F22F__INCLUDED_)



