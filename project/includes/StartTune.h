///////////////////////////////////////////////////////////
//  StartTune.h
//  Implementation of the Class StartTune
//  Created on:      16-Jul-2013 16:45:43
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_7003EB7D_A113_41a4_8702_3FB25384E7CE__INCLUDED_)
#define EA_7003EB7D_A113_41a4_8702_3FB25384E7CE__INCLUDED_

#include "HMI.h"
#include "FileIO.h"
#include "Tuner.h"

/**
* \class StartTune
* \brief class is instantiated every time a startTune get invoked;
* call the method continueJob() until the tune has finished
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

class StartTune
{

public:
	StartTune( Tuner *tuner, HMI *hmi, struct timeval tv,
		    IVIRadio::Types::Types::StationSelector station,
		    IVIRadio::Station::StationTypes::SelectionMode selectionMode,
		    uint32_t handle);

	virtual ~StartTune();

	bool continueJob();

private:
	IVIRadio::Types::Types::StationSelector 		m_station;
	IVIRadio::Station::StationTypes::SelectionMode 	m_selectionMode;
	uint32_t m_handle;

	FileIO *m_FileIO;
	Tuner  *m_tuner;
	HMI    *m_hmi;

};
#endif // !defined(EA_7003EB7D_A113_41a4_8702_3FB25384E7CE__INCLUDED_)
