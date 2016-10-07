/*
 * StationManagement.h
 *
 *  Created on: Jul 23, 2013
 *      Author: b
 */

#ifndef STATIONMANAGEMENT_H_
#define STATIONMANAGEMENT_H_

#include "Tuner.h"
#include "HMI.h"

/**
* \class StationManagement
* \brief class cares about a couple of jobs for station management
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

class StationManagement {
public:
	StationManagement();
	virtual ~StationManagement();

	bool ManualDown (Tuner *tuner);
	bool ManualUp   (Tuner* tuner);
	bool AutoDown   (Tuner* tuner, HMI *hmi);
	bool AutoUp		(Tuner *tuner, HMI *hmi);

	inline IVIRadio::Station::StationTypes::SeekData getSeekData() { return m_SeekData; }

private:
	IVIRadio::Station::StationTypes::SeekData  m_SeekData;
};

#endif /* STATIONMANAGEMENT_H_ */
