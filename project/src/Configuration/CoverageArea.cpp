/*
 * CoverageArea.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: b
 */

#include "includes/Configuration/CoverageArea.h"

CoverageArea::CoverageArea() {
	m_coverageAreaOptions.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE);
	m_coverageAreaOptions.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
	m_coverageAreaOptions.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::AMFM);
	m_coverageAreaOptions.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
	m_coverageAreaOptions.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::TV);
	m_coverageAreaOptions.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
	m_coverageAreaOptions.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::SDARS);
	m_coverageAreaOptions.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
	m_coverageAreaOptions.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::DAB);
	m_coverageAreaOptions.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
}

CoverageArea::~CoverageArea() {
	// TODO Auto-generated destructor stub
}

bool CoverageArea::getConfigurations( IVIRadio::Configuration::ConfigurationOptionsGetter::FunctionalityOptionGet cv_options_get,
										IVIRadio::Configuration::ConfigurationOptions::CoverageAreaOptions& cv_options_out){

	vector<IVIRadio::Types::Types::DeviceType> vec_dev = cv_options_get.get<IVIRadio::Configuration::ConfigurationOptionsGetter::CoverageAreaOptionsGet>().deviceTypes;

	for ( auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it_dev++ ){
		auto it_cv_conf = m_coverageAreaOptions.countryVariants.cbegin();
		for ( auto it_dev_conf = m_coverageAreaOptions.deviceTypes.cbegin(); it_dev_conf != m_coverageAreaOptions.deviceTypes.cend(); it_dev_conf++, it_cv_conf++ ){
			if ( (*it_dev) == (*it_dev_conf) ){
				cv_options_out.deviceTypes    .push_back((*it_dev_conf));
				cv_options_out.countryVariants.push_back((*it_cv_conf ));
			}
		}
	}
	return true;
}


bool CoverageArea::setConfigurations( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
							IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions  	 funtionalityOptions ){
	return true;
}
