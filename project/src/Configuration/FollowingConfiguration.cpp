/*
 * FollowingConfiguration.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: b
 */

#include "includes/Configuration/FollowingConfiguration.h"

FollowingConfiguration::FollowingConfiguration() {
	m_FollowingOptions.followingStates.push_back ( IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::DAB_FM		);
	m_FollowingOptions.followingStates.push_back ( IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::DAB_INTERNAL	);
	m_FollowingOptions.followingStates.push_back ( IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::DVBT_DAB		);
	m_FollowingOptions.followingStates.push_back ( IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::DVBT_INTERNAL);
	m_FollowingOptions.followingStates.push_back ( IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::FM_DAB		);
	m_FollowingOptions.followingStates.push_back ( IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType::FM_INTERNAL	);
	for (int i = 0; i < 6; i++) {
		m_FollowingOptions.activations.push_back ( IVIRadio::Types::Types::Activation::INACTIVE );
	}
}

FollowingConfiguration::~FollowingConfiguration() {
}

bool FollowingConfiguration::getConfigurations( IVIRadio::Configuration::ConfigurationOptionsGetter::FunctionalityOptionGet cv_options_get,
												IVIRadio::Configuration::ConfigurationOptions::FollowingOptions& 			cv_options_out){

	cout << "FollowingConfiguration::getConfigurations" << endl;
	vector<IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType> vec_ft = cv_options_get.get<IVIRadio::Configuration::ConfigurationOptionsGetter::FollowingOptionsGet>().followingTypes;
	for ( auto it_dev = vec_ft.cbegin(); it_dev != vec_ft.cend(); it_dev++ ){
		auto it_cv_conf = m_FollowingOptions.activations.cbegin();
		for ( auto it_dev_conf = m_FollowingOptions.followingStates.cbegin(); it_dev_conf != m_FollowingOptions.followingStates.cend(); it_dev_conf++, it_cv_conf++ ){
			if ( (*it_dev) == (*it_dev_conf) ){
				cout << "youll get something from me friendo..." << endl;
				cv_options_out.followingStates.push_back((*it_dev_conf));
				cv_options_out.activations    .push_back((*it_cv_conf ));
			}
		}
	}
	return true;
}

bool FollowingConfiguration::setConfigurations( IVIRadio::Configuration::ConfigurationOptions::FunctionalityOption funtionalityOptions ){
	vector <IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType> vec_ft = funtionalityOptions.get<IVIRadio::Configuration::ConfigurationOptions::FollowingOptions>().followingStates;
	vector <IVIRadio::Types::Types::Activation> vec_act = funtionalityOptions.get<IVIRadio::Configuration::ConfigurationOptions::FollowingOptions>().activations;
	auto it_ft_act = vec_act.cbegin();
	int cnt = 0;
	for ( auto it_ft = vec_ft.cbegin(); it_ft != vec_ft.cend(); it_ft++, it_ft_act++ ){
		cnt = 0;
		auto it_cv_conf = m_FollowingOptions.activations.cbegin();
		for ( auto it_dev_conf = m_FollowingOptions.followingStates.cbegin(); it_dev_conf != m_FollowingOptions.followingStates.cend(); it_dev_conf++, it_cv_conf++ ){
			if ( (*it_ft) == (*it_dev_conf) ){
				m_FollowingOptions.activations[cnt] = (*it_ft_act);
			}
			cnt++;
		}
	}
	return true;
}

