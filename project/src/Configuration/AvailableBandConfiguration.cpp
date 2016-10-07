/*
 * AvailableBandConfiguration.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: b
 */

#include "includes/Configuration/AvailableBandConfiguration.h"


AvailableBandConfiguration::AvailableBandConfiguration() {
	m_availableBandOptions.deviceTypes		.push_back( IVIRadio::Types::Types::DeviceType::AMFM		 );
	m_availableBandOptions.availableBands	.push_back( IVIRadio::Types::Types::SourceType::UNDEF_SOURCE );
	m_availableBandOptions.deviceTypes		.push_back( IVIRadio::Types::Types::DeviceType::DAB			 );
	m_availableBandOptions.availableBands	.push_back( IVIRadio::Types::Types::SourceType::UNDEF_SOURCE );
	m_availableBandOptions.deviceTypes		.push_back( IVIRadio::Types::Types::DeviceType::SDARS		 );
	m_availableBandOptions.availableBands	.push_back( IVIRadio::Types::Types::SourceType::UNDEF_SOURCE );
	m_availableBandOptions.deviceTypes		.push_back( IVIRadio::Types::Types::DeviceType::TV			 );
	m_availableBandOptions.availableBands	.push_back( IVIRadio::Types::Types::SourceType::UNDEF_SOURCE );
	m_availableBandOptions.deviceTypes		.push_back( IVIRadio::Types::Types::DeviceType::UNDEF_DEVICE );
	m_availableBandOptions.availableBands	.push_back( IVIRadio::Types::Types::SourceType::UNDEF_SOURCE );
}

AvailableBandConfiguration::~AvailableBandConfiguration() {
	// TODO Auto-generated destructor stub
}

bool AvailableBandConfiguration::getConfigurations(IVIRadio::Configuration::ConfigurationOptionsGetter::FunctionalityOptionGet cv_options_get,
						IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions&		cv_options_out){
	vector<IVIRadio::Types::Types::DeviceType> vec_ft = cv_options_get.get<IVIRadio::Configuration::ConfigurationOptionsGetter::AvailableBandoptionsGet>().deviceTypes;

	for ( auto it_dev = vec_ft.cbegin(); it_dev != vec_ft.cend(); it_dev++ ){
		auto it_cv_conf = m_availableBandOptions.availableBands.cbegin();
		for ( auto it_dev_conf = m_availableBandOptions.deviceTypes.cbegin(); it_dev_conf != m_availableBandOptions.deviceTypes.cend(); it_dev_conf++, it_cv_conf++ ){
			if ( (*it_dev) == (*it_dev_conf) ){
				cv_options_out.deviceTypes   .push_back((*it_dev_conf));
				cv_options_out.availableBands.push_back((*it_cv_conf ));
			}
		}
	}
	return true;
}

bool AvailableBandConfiguration::setConfigurations(IVIRadio::Configuration::ConfigurationOptions::FunctionalityOption funtionalityOptions ){

	vector <IVIRadio::Types::Types::SourceType> vec_st  = funtionalityOptions.get<IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions>().availableBands;
	vector <IVIRadio::Types::Types::DeviceType> vec_dev = funtionalityOptions.get<IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions>().deviceTypes;

	auto it_st_act = vec_st.cbegin();
	int cnt = 0;
	for ( auto it_dev = vec_dev.cbegin(); it_dev != vec_dev.cend(); it_dev++, it_st_act++ ){
		cnt = 0;
		auto it_ab_conf = m_availableBandOptions.availableBands.cbegin();
		for ( auto it_dev_conf = m_availableBandOptions.deviceTypes.cbegin(); it_dev_conf != m_availableBandOptions.deviceTypes.cend(); it_dev_conf++, it_ab_conf++ ){
			if ( (*it_dev_conf) == (*it_dev) ){
				m_availableBandOptions.availableBands[cnt] = (*it_st_act);
			}
			cnt++;
		}
	}

	return true;
}
