/*
 * AvailableBandConfiguration.h
 *
 *  Created on: Nov 7, 2013
 *      Author: b
 */

#ifndef AVAILABLEBANDCONFIGURATION_H_
#define AVAILABLEBANDCONFIGURATION_H_

#include "IVIRadio/Configuration/ConfigurationOptions.h"
#include "IVIRadio/Configuration/ConfigurationOptionsGetter.h"
#include <vector>

using namespace std;

/*
 * \class AvailableBandConfiguration
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

class AvailableBandConfiguration {
public:
	AvailableBandConfiguration();
	virtual ~AvailableBandConfiguration();

	bool getConfigurations( IVIRadio::Configuration::ConfigurationOptionsGetter::FunctionalityOptionGet cv_options_get,
							IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions&		cv_options_out);

	bool setConfigurations( IVIRadio::Configuration::ConfigurationOptions::FunctionalityOption funtionalityOptions );


private:
	IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions	m_availableBandOptions;
};

#endif /* AVAILABLEBANDCONFIGURATION_H_ */
