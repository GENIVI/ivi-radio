/*
 * CountryVariantConfiguration.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: b
 */

#include "includes/Configuration/CountryVariantConfiguration.h"

CountryVariantConfiguration::CountryVariantConfiguration() {
	m_CountryVariant.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::AMFM);
	m_CountryVariant.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
	m_CountryVariant.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE);
	m_CountryVariant.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_AUSTRALIA);
	m_CountryVariant.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::TV);
	m_CountryVariant.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
	m_CountryVariant.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::SDARS);
	m_CountryVariant.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
	m_CountryVariant.deviceTypes.push_back( IVIRadio::Types::Types::DeviceType::DAB);
	m_CountryVariant.countryVariants.push_back (IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant::CV_EUROPE);
}

CountryVariantConfiguration::~CountryVariantConfiguration() {
}

//bool CountryVariantConfiguration::getConfigurations( IVIRadio::Configuration::ConfigurationOptionsGetter::CountryVariantsOptionsGet cv_options_get,
//										IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions& cv_options_out){
bool CountryVariantConfiguration::getConfigurations( IVIRadio::Configuration::ConfigurationOptionsGetter::FunctionalityOptionGet cv_options_get,
										IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions& cv_options_out){

	vector<IVIRadio::Types::Types::DeviceType> vec_dev = cv_options_get.get<IVIRadio::Configuration::ConfigurationOptionsGetter::CountryVariantsOptionsGet>().deviceTypes;

	for ( auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it_dev++ ){
		auto it_cv_conf = m_CountryVariant.countryVariants.cbegin();
		for ( auto it_dev_conf = m_CountryVariant.deviceTypes.cbegin(); it_dev_conf != m_CountryVariant.deviceTypes.cend(); it_dev_conf++, it_cv_conf++ ){
			if ( (*it_dev) == (*it_dev_conf) ){
				cv_options_out.deviceTypes    .push_back((*it_dev_conf));
				cv_options_out.countryVariants.push_back((*it_cv_conf ));
			}
		}
	}
	return true;
}


bool CountryVariantConfiguration::setConfigurations( IVIRadio::Configuration::ConfigurationOptions::FunctionalityOption funtionalityOptions ){

	vector <IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant> vec_cv  = funtionalityOptions.get<IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions>().countryVariants;
	vector <IVIRadio::Types::Types::DeviceType> vec_dev = funtionalityOptions.get<IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions>().deviceTypes;

	auto it_cv_act = vec_cv.cbegin();
	int cnt = 0;
	for ( auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it_dev++, it_cv_act++ ){
		cnt = 0;
		auto it_cv_conf = m_CountryVariant.countryVariants.cbegin();
		for ( auto it_dev_conf = m_CountryVariant.deviceTypes.cbegin(); it_dev_conf != m_CountryVariant.deviceTypes.cend(); it_dev_conf++, it_cv_conf++ ){
			if ( (*it_dev_conf) == (*it_dev) ){
				m_CountryVariant.countryVariants[cnt] = (*it_cv_act);
			}
			cnt++;
		}
	}

	return true;
}

