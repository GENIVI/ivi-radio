///////////////////////////////////////////////////////////
//  DataHelper.h
//  Implementation of the Class DataHelper
//  Created on:      09-Aug-2013 13:29:27
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_11674755_90D5_441a_8B1F_E922F2360E6D__INCLUDED_)
#define EA_11674755_90D5_441a_8B1F_E922F2360E6D__INCLUDED_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
 * \class DataHelper
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

class DataHelper
{

public:
	DataHelper( string serviceID );
	virtual ~DataHelper();

	string findTag(string startTag, string endTag, string stream);

	vector< string > findTags(string startTag, string endTag, string stream);

	string getServiceID();

public:
	string m_serviceID;

};
#endif // !defined(EA_11674755_90D5_441a_8B1F_E922F2360E6D__INCLUDED_)
