/** \class Configuration
 * \brief module manages the possible functionality type configuration. note that only a couple of functionalities which are provided in
 * the tuner interface are implemented in the POC. \n
 * all functionality types which are implemented are managed in own classes that care about the properties of those functionality types.
 * basically it is only possible to set and get configurations of functionality types. \n
 * every instance of a HMI needs one object of the Configuration class to manage functionality type configurations.
 *
 * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2013/11/14 14:16:20
 *
 * Contact: bernhard.singer@partner.bmw.de
 *
 *  * Copyright
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
 */
#if !defined(EA_B7DFB1F1_7D87_4f02_B2E7_2E857953A2AB__INCLUDED_)
#define EA_B7DFB1F1_7D87_4f02_B2E7_2E857953A2AB__INCLUDED_

#include "IVIRadio/Configuration/ConfigurationOptions.h"
#include "IVIRadio/Configuration/ConfigurationOptionsGetter.h"
#include <vector>

#include "CoverageArea.h"
#include "CountryVariantConfiguration.h"
#include "FollowingConfiguration.h"
#include "AvailableBandConfiguration.h"

class Configuration
{

public:
	/**
	 * \brief default constructor
	 */
	Configuration();

	/**
	 * \brief defualt destructor
	 */
	virtual ~Configuration();

	/**
	 * \brief method returns the configuration of a functionality type
	 * \param [in] functionalityTypes of type FunctionalityTypes; carries functionalityTypes for which configuration is requested
	 * \param [out] funtionalityOptions of type ArrayFuntionalityOptions; is a reference that will be filled with the requested configurations
	 * \return
	 */
	bool getConfigurations( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes	  			functionalityTypes,
							IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet  	funtionalityOptions,
							IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions&  			outFuntionalityOptions);

	/**
	 * \brief method sets functionality options of a functionality type
	 * \param functionalityType a FunctionalityType the type that should be set
	 * \param functionalityOptions of type FunctionalityOptions options that should be set
	 */
	bool setConfigurations( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
						    IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions  	 funtionalityOptions );

private:
	IVIRadio::Configuration::ConfigurationOptions::HDOptions 					m_HDOptions;

	IVIRadio::Configuration::ConfigurationOptions::SmartFavoriteOptions 		m_smartFavoriteOptions;

	/*
	 * \brief instance of CountryVariantConfiguration manages the settings for country variants for the particular hmi
	 */
	CountryVariantConfiguration *m_CountryVariant;
	/*
	 * \brief instance of CoverageArea manages the settings for coverage area for the particular hmi
	 */
	CoverageArea 				*m_CoverageArea;
	/*
	 * \brief instance of FollowingConfiguration manages the settings for Following for the particular hmi
	 */
	FollowingConfiguration		*m_Following;
	/*
	 * \brief instance of AvailableBandConfiguration manages the settings for available band for the particular hmi
	 */
	AvailableBandConfiguration	*m_AvailableBand;

	IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions 		m_interfaceVersionOptions;
	IVIRadio::Configuration::ConfigurationOptions::AMModiOptions 				m_amModiOptions;
	IVIRadio::Configuration::ConfigurationOptions::RDSOptions	 				m_rdsoptions;
	IVIRadio::Configuration::ConfigurationOptions::RTOptions					m_RTOptions;
	IVIRadio::Configuration::ConfigurationOptions::DLSOptions					m_DLSOptions;

};

#endif // !defined(EA_B7DFB1F1_7D87_4f02_B2E7_2E857953A2AB__INCLUDED_)
