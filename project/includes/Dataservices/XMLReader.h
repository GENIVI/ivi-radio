///////////////////////////////////////////////////////////
//  XMLReader.h
//  Implementation of the Class XMLReader
//  Created on:      31-Jul-2013 13:34:51
//  Original author: QX92858
///////////////////////////////////////////////////////////

#if !defined(EA_7F990017_42C6_4afa_9B42_ABA51E7F421F__INCLUDED_)
#define EA_7F990017_42C6_4afa_9B42_ABA51E7F421F__INCLUDED_

#include <CommonAPI/ByteBuffer.h>

#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <dirent.h>
#include <errno.h>

#include "EPGEvent.h"
#include "JournalineObject.h"
#include "SubtitleStream.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypes.h"
#include "IVIRadio/AdditionalService/AdditionalServiceTypesOptions.h"

using namespace std;

/**
 * \brief class reads all the additional information from the filesystem for the diffent component types and holds them during runtime
 * the XML Reader reads all the additional data for the different component types and holds the information during runtime. \n
 * therefore the class has a for every component type a vector to save the objects that contain actually the data.\n
 * by calling getComponentData it is possible to get a set of data corresponding to the filter information.\n
 * the additional data is stored in the filesystem in the folder "AdditionalData". This folder simulates the datastorage of the realsystem.\n
 * In the real system the data stored there would be broadcasted over the air and received by the tuner controlled by the middleware. \n
 * After decoding and interpreting the broadcasted data those data would be saved in filesystem or database maybe similar to the one used for the PoC.\n
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

class XMLReader
{

public:
	/**
	* \brief default constructor initiates to load the data from the filesystem
	*/
	XMLReader();
	/**
	 * \brief default destructor
	 */
	virtual ~XMLReader();

	/**
	 * \brief function provides additional data according to the given set of parameters
	 * \param [in] componentID an uint32_t is the unique in the system available ID for one component type belonging to on station
	 * \param [in] stationIdentifier an uint32_t is the unique in the system available ID of an station
	 * \param [in] component_parameter an SelectParameter can be the select parameter of every component type since SelectParameter is an union\n
	 * 		  it describes the filter options for the different component types
	 * \param [out] oBuff an ByteBuffer is a reference to a ByteBuffer that will contain the requested information
	 */
	 bool getComponentData ( IVIRadio::Types::Types::StationSelectors stationSelectors, IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
	 //bool getComponentData ( uint32_t stationIdentifier, IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
			IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption dataServiceOption, uint32_t objectID, CommonAPI::ByteBuffer &oBuff );

	/**
	* \brief function loads all names of the files with the extension $dirname in the directory "AdditionalData/$dirname"
	* \param [in] dirname an string name of the directory that should be loaded
	* \return a vector containing all the filenames in the directory "AdditionalData/$dirname" with the extension $dirname
	*/
	vector < string > LoadDirectory(string dirname);

	/**
	* \brief function invokes to load the data of the different additional component types
	*/
	void LoadData          ();

	/**
	* \brief function loads EPG data and saves it to the vector m_vecEPGEvents
	*/
	void LoadEPGData       ();

	/**
	* \brief function loads Journaline data and saves it to the vector m_vecJournalineObjects
	*/
	void LoadJournalineData();

	/**
	* \brief function loads Subtitle data and saves it to the vector m_vecSubtitleStreams
	*/
	void LoadSubtitleData  ();

	/**
	* \brief function reads the content of the file $file_name and returns it as string
	* \param [in] file_name an string is the name of the that needs to be read
	* \param [in] type an string is the component type and is used for a check if the extension of the $file_name is correct
	* \return	function returns the uninterpreted content of the file $file_name as a string
	*/
	string readFile( string file_name, string type );

private:

	/**
	 * \brief m_vecEPGEvents vector holds all EPG events during runtime
	 */
	vector < EPGEvent* > m_vecEPGEvents;

	/**
	* \brief m_vecJournalineObjects vector holds all journaline objects during runtime
	*/
	vector < JournalineObject* > m_vecJournalineObjects;

	/**
	* \brief m_vecSubtitleStreams vector holds all subtitle streams during runtime
	*/
	vector < SubtitleStream* > m_vecSubtitleStreams;

};
#endif // !defined(EA_7F990017_42C6_4afa_9B42_ABA51E7F421F__INCLUDED_)
