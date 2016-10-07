///////////////////////////////////////////////////////////
//  JournalineObject.h
//  Implementation of the Class JournalineObject
//  Created on:      09-Aug-2013 13:04:37
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_9BC87800_FC22_4728_A82D_0F25EBBACB8A__INCLUDED_)
#define EA_9BC87800_FC22_4728_A82D_0F25EBBACB8A__INCLUDED_

#include <string>
#include <iostream>
#include <vector>
#include "DataHelper.h"

using namespace std;

/*
 * \class JournalineObject
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

class JournalineObject : DataHelper
{

public:
	JournalineObject(string file, string serviceID);
	virtual ~JournalineObject( );

	string returnObjectAsXML( );

	uint32_t getObjectID( ) { return atoi( m_ID.c_str( ) ); }

private:
	string m_ID;
	string m_type;
	string m_jstatic;
	string m_title;
	string m_dlan;
	string m_jlink_descr;
	string m_jlink_id;
	vector<string> m_Text;
	vector<string> m_jlist;

};
#endif // !defined(EA_9BC87800_FC22_4728_A82D_0F25EBBACB8A__INCLUDED_)
