///////////////////////////////////////////////////////////
//  Seek.h
//  Implementation of the Class Seek
//  Created on:      16-Jul-2013 16:47:54
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_123208D2_592D_4726_A0A4_626ACC262618__INCLUDED_)
#define EA_123208D2_592D_4726_A0A4_626ACC262618__INCLUDED_

#include "HMI.h"
#include "Tuner.h"
#include "FileIO.h"

/**
* \class Seek
* \brief class is instantiated every time a seek gets started;
* the user can call the function continueJob() until the seek process has finished
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

class Seek
{

public:
	Seek( Tuner *tuner, HMI *hmi, struct timeval tv,
		IVIRadio::Types::Types::DeviceType device,
		IVIRadio::Station::StationTypes::SeekMode   seekMode);

	virtual ~Seek();

	bool continueJob();

	IVIRadio::Station::StationTypes::SeekData    getSeekData();
	IVIRadio::Station::StationTypes::StationList getSeekList();

private:
	IVIRadio::Types::Types::DeviceType 			m_device;
	IVIRadio::Station::StationTypes::SeekMode   m_seekMode;

	bool m_finished;

	IVIRadio::Station::StationTypes::SeekData    m_broadcastSeekData;
	IVIRadio::Station::StationTypes::StationList m_broadcastList;

	HMI	 	*m_hmi;
	Tuner	*m_tuner;
	timeval m_tv;
	FileIO  *m_FileIO;

};
#endif // !defined(EA_123208D2_592D_4726_A0A4_626ACC262618__INCLUDED_)
