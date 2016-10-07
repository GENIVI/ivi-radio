///////////////////////////////////////////////////////////
//  HMIList.h
//  Implementation of the Class HMIList
//  Created on:      16-Jul-2013 16:47:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_62FFCC00_FD8A_409e_9226_7DABC7546F85__INCLUDED_)
#define EA_62FFCC00_FD8A_409e_9226_7DABC7546F85__INCLUDED_

#include "HMI.h"

#include <set>

/**
* \class HMIList
* \brief class HMIList administrates all HMIs; systemwide are three hmis possible
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

class HMIList
{

public:
    /**
    * \brief default constructor
    */
	HMIList();

    /**
    * \brief default destructor
    */
	virtual ~HMIList();

	void addHMI(HMI *hmi);

    /**
    * \brief method returns hmi from set according to the id
    * \param [in] m_hni_number an int id of the hmi that is required
    * \return hmi according to id or NULL if no hmi to that id is available
    */
	HMI* getHMIbyNumber(int hmi_number);

    /**
    * \brief method returns whole set of all hmis
    * \return set of all hmis
    */
	std::set<HMI *> getHMIList() { return m_hmiList; }

    /**
    * \brief method deletes a hmi according to the id
    * \param [in] m_hmi_number an int id of the hmi to be deleted
    */
	void deleteHMIbyNumber(int m_hmi_number);

    /**
    * \brief method deletes the given hmi
    * \param [in] *hmi pointer to the hmi to be deleted
    */
	void deleteHMI(HMI *hmi);

private:

	/**
	 * \brief set of HMI's
	 */
	set<HMI *> 	m_hmiList;

};
#endif // !defined(EA_62FFCC00_FD8A_409e_9226_7DABC7546F85__INCLUDED_)
