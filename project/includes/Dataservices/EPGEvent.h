///////////////////////////////////////////////////////////
//  EPGEvent.h
//  Implementation of the Class EPGEvent
//  Created on:      01-Aug-2013 14:41:27
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_20B85573_D46F_4496_9EE0_1E9D4C2E9222__INCLUDED_)
#define EA_20B85573_D46F_4496_9EE0_1E9D4C2E9222__INCLUDED_

#include <string>
#include <iostream>
#include "DataHelper.h"

using namespace std;


/*
 * \class EPGEvent
 *
* \author (last to touch it)  Bernhard Singer
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

class EPGEvent : public DataHelper
{

public:
	EPGEvent( string event, string serviceID );
	virtual ~EPGEvent();

	string returnEventAsXML( );

	string getEventID  ( ) { return m_ID;        }
	//string getServiceID ( ) { return m_serviceID; }

private:
	string m_ID  ;
	string m_ver ;
	string m_reco;
	string m_name;
	string m_time;
	string m_dur ;
	string m_fsc ;
	string m_desc;

	string m_event;

	//string m_serviceID;

};
#endif // !defined(EA_20B85573_D46F_4496_9EE0_1E9D4C2E9222__INCLUDED_)
