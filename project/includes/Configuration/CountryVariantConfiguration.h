/*
 * CountryVariantConfiguration.h
 *
 *  Created on: Nov 7, 2013
 *      Author: b
 */

#ifndef COUNTRYVARIANTCONFIGURATION_H_
#define COUNTRYVARIANTCONFIGURATION_H_

#include "IVIRadio/Configuration/ConfigurationOptions.h"
#include "IVIRadio/Configuration/ConfigurationOptionsGetter.h"
#include <vector>

using namespace std;

/*
 * \class CountryVariantConfiguration
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

class CountryVariantConfiguration {
public:
	CountryVariantConfiguration();
	virtual ~CountryVariantConfiguration();

	/**
	 * \brief method returns the configuration of a functionality type
	 * \param [in] functionalityTypes of type FunctionalityTypes; carries functionalityTypes for which configuration is requested
	 * \param [out] funtionalityOptions of type ArrayFuntionalityOptions; is a reference that will be filled with the requested configurations
	 * \return
	 */
	bool getConfigurations( IVIRadio::Configuration::ConfigurationOptionsGetter::FunctionalityOptionGet cv_options_get,
							IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions& cv_options_out);

	/**
	 * \brief method sets functionality options of a functionality type
	 * \param functionalityType a FunctionalityType the type that should be set
	 * \param functionalityOptions of type FunctionalityOptions options that should be set
	 */
	bool setConfigurations( IVIRadio::Configuration::ConfigurationOptions::FunctionalityOption funtionalityOptions );

private:
	IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions m_CountryVariant;
};

#endif /* COUNTRYVARIANTCONFIGURATION_H_ */
