///////////////////////////////////////////////////////////
//  FMTuner.h
//  Implementation of the Class FMTuner
//  Created on:      16-Jul-2013 16:47:50
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_F8F98893_E601_46f4_BB1B_A6A02A27826D__INCLUDED_)
#define EA_F8F98893_E601_46f4_BB1B_A6A02A27826D__INCLUDED_

#include "Tuner.h"

/**
 * \class FMTuner
 *
 * \brief FMTuner class represents a physical fm tuner.
 * The fm tuner class inherits most of its functionality from the tuner class.
 * It just adds few fm specific constants.
 *
 * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2013/11/14 14:16:20
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


class FMTuner : public Tuner
{

public:
    /**
     * \brief default constructor
     * \param [in] tunerId an int is the Identification of the tuner
     */
	FMTuner(int tunerId);
    /**
     * \brief default destructor
    */
	virtual ~FMTuner();

    /**
     * \brief method returns the station the tuner is currently tuned to
     * \returns currently tuned Station
    */

	IVIRadio::Station::StationTypes::Station getTunedStation();

private:
	/**
	 * \brief minimum frequency of the fm waveband
	*/
	static const int m_minFrequencyFM = 87500;

	/**
	 * \brief maximum frequency of the fm waveband
	*/
	static const int m_maxFrequencyFM = 108000;
};
#endif // !defined(EA_F8F98893_E601_46f4_BB1B_A6A02A27826D__INCLUDED_)
