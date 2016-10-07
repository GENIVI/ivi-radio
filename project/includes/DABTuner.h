///////////////////////////////////////////////////////////
//  DABTuner.h
//  Implementation of the Class DABTuner
//  Created on:      16-Jul-2013 16:47:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_51E7E1EE_C987_4a78_A054_0448A2564E58__INCLUDED_)
#define EA_51E7E1EE_C987_4a78_A054_0448A2564E58__INCLUDED_

#include "Tuner.h"

/**
 * \class DABTuner
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
 *  * Copyright
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
 */
class DABTuner : public Tuner
{

public:
	/**
	 * \brief default constructor
	 * \param [in] m_tunerId an int Identification of the dab tuner
	 */
	DABTuner(int m_tunerId);

	/**
	 * \brief default destructor
	*/
	virtual ~DABTuner();

    /**
     * \brief method returns the station the tuner is currently tuned to
     * \returns currently tuned Station
    */
	IVIRadio::Station::StationTypes::Station getDABTunedStation();

private:
    /**
     * \brief minimum frequency of the dab waveband
    */
    static const int m_minFrequencyDAB = 172000;

    /**
     * \brief maximum frequency of the dab waveband
    */
    static const int m_maxFrequencyDAB = 230000;

};
#endif // !defined(EA_51E7E1EE_C987_4a78_A054_0448A2564E58__INCLUDED_)





