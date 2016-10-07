///////////////////////////////////////////////////////////
//  SubtitleStream.h
//  Implementation of the Class SubtitleStream
//  Created on:      13-Aug-2013 11:08:27
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_051C4703_E76F_4cb7_A4C3_671C2E3FC606__INCLUDED_)
#define EA_051C4703_E76F_4cb7_A4C3_671C2E3FC606__INCLUDED_

#include "DataHelper.h"
#include <string>
#include <iostream>

using namespace std;

/*
 * \class SubtitleStream
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

class SubtitleStream : public DataHelper
{

public:
	SubtitleStream( string stream, string serviceID );
	virtual ~SubtitleStream(  );

	string returnEventAsXML( );

private:
	string m_stream;
	string m_disp  ;
	string m_disphh ;

	string m_lan;

	string m_text;
	string m_color;

};
#endif // !defined(EA_051C4703_E76F_4cb7_A4C3_671C2E3FC606__INCLUDED_)



