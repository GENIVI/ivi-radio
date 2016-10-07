///////////////////////////////////////////////////////////
//  TunerList.h
//  Implementation of the Class TunerList
//  Created on:      16-Jul-2013 16:47:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_23006F5D_BCE2_4a33_A257_FF33A94AF54F__INCLUDED_)
#define EA_23006F5D_BCE2_4a33_A257_FF33A94AF54F__INCLUDED_

#include "DABTuner.h"
#include "FMTuner.h"
#include "TerminalIO.h"
#include "FileIO.h"

#include <vector>

/**
* \class TunerList
* \brief class TunerList administrates the generated Tuner
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

class TunerList
{

public:
	/**
	 * \brief default constructor
	 */
	TunerList();

	/**
	 * \brief default constructor
	 */
	virtual ~TunerList();

	/**
	* \brief returns a free tuner to the given device type
	* \param [in] device an DeviceType the device type (FM or DAB) the free tuner is required for
	* \return free tuner according to the device type
	*/
	Tuner* getFreeTuner( IVIRadio::Types::Types::DeviceType device );

	/**
	* \brief returns a free tuner to the given device type
	* \param [in] device an int  the device type ( 1 == FM or 2 == DAB) the free tuner is required for
	* \return free tuner according to the device type
	*/
	Tuner* getFreeTuner( uint32_t device );

	/**
	* \brief method returns list of all FM tuner
	* \return vector containing all FM tuner
	*/
    inline std::vector<Tuner *> getAMFMTuner() { return m_tunerListFM ; }

    /**
	* \brief method returns list of all DAB tuner
	* \return vector containing all DAB tuner
	*/
    inline std::vector<Tuner *> getDABTuner () { return m_tunerListDAB; }

    /**
	* \brief method adds a DAB tuner to the dab list
	* \param *dabTuner pointer to a DABTuner that should be added to the list
	*/
	void addDABTuner(DABTuner *dabTuner);

	/**
	* \brief method adds a FM tuner to the fm list
	* \param *FMTuner pointer to a FMTuner that should be added to the list
	*/
	void addFMTuner (FMTuner  *fmTuner );


private:

	/**
	* \brief list of all available fm tuner
	*/
	std::vector<Tuner *> m_tunerListFM;

	/**
    * \brief list of all available dab tuner
    */
	std::vector<Tuner *> m_tunerListDAB;

};
#endif // !defined(EA_23006F5D_BCE2_4a33_A257_FF33A94AF54F__INCLUDED_)
