///////////////////////////////////////////////////////////
//  Configuration.cpp
//  Implementation of the Class Configuration
//  Created on:      19-Sep-2013 12:43:34
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Configuration/Configuration.h"
using namespace std;

Configuration::Configuration(){
	//set default values for different configurations
	m_HDOptions.activation = IVIRadio::Types::Types::Activation::INACTIVE;

	m_smartFavoriteOptions.activity = IVIRadio::Types::Types::Activation::INACTIVE;

	m_CountryVariant = new CountryVariantConfiguration	();
	m_CoverageArea   = new CoverageArea					();
	m_Following		 = new FollowingConfiguration		();
	m_AvailableBand  = new AvailableBandConfiguration	();

	m_interfaceVersionOptions.majorVersion = 1;
	m_interfaceVersionOptions.minorVersion = 2;

	m_amModiOptions.amMode     = IVIRadio::Configuration::ConfigurationTypesEnum::AMMode::AM_MWLW;
	m_amModiOptions.deviceType = IVIRadio::Types::Types::DeviceType::AMFM;

	m_rdsoptions.deviceTypes.push_back(IVIRadio::Types::Types::DeviceType::AMFM);
	m_rdsoptions.activations.push_back(IVIRadio::Types::Types::Activation::ACTIVE);

	m_RTOptions.deviceTypes.push_back(IVIRadio::Types::Types::DeviceType::AMFM);
	m_RTOptions.activations.push_back(IVIRadio::Types::Types::Activation::ACTIVE);

	m_DLSOptions.deviceTypes.push_back(IVIRadio::Types::Types::DeviceType::AMFM);
	m_DLSOptions.activations.push_back(IVIRadio::Types::Types::Activation::ACTIVE);
}

Configuration::~Configuration(){
}

bool Configuration::getConfigurations( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes	  	functionalityTypes,
						IVIRadio::Configuration::ConfigurationOptionsGetter::FuntionalityOptionsGet  			funtionalityOptions,
						IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions&  					outFuntionalityOptions ){
	auto it_fo = funtionalityOptions.cbegin();
	for ( auto it = functionalityTypes.cbegin(); it != functionalityTypes.cend(); it++, it_fo++ ){
		if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::HD					)
			outFuntionalityOptions.push_back( m_HDOptions );
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::Following 		){
			IVIRadio::Configuration::ConfigurationOptions::FollowingOptions cv_options;
			m_Following->getConfigurations( (*it_fo), cv_options);
			outFuntionalityOptions.push_back ( cv_options );
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::SmartFavorite 	)
			outFuntionalityOptions.push_back( m_smartFavoriteOptions );

		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AvailableBand 	){
			IVIRadio::Configuration::ConfigurationOptions::AvailableBandoptions cv_options;
			m_AvailableBand->getConfigurations( (*it_fo), cv_options);
			outFuntionalityOptions.push_back ( cv_options );
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CoverageArea 	){
			IVIRadio::Configuration::ConfigurationOptions::CoverageAreaOptions cv_options;
			m_CoverageArea->getConfigurations( (*it_fo), cv_options);
			outFuntionalityOptions.push_back ( cv_options );
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::InterfaceVersion)
			outFuntionalityOptions.push_back( m_interfaceVersionOptions );

		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AMModi 			)
			outFuntionalityOptions.push_back( m_amModiOptions );

		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CountryVariant	){
			IVIRadio::Configuration::ConfigurationOptions::CountryVariantsOptions cv_options;
			m_CountryVariant->getConfigurations( (*it_fo), cv_options);
			outFuntionalityOptions.push_back   ( cv_options );
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::RDS	)
							outFuntionalityOptions.push_back( m_rdsoptions );

		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::RT )
							outFuntionalityOptions.push_back( m_DLSOptions );

		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::DLS )
							outFuntionalityOptions.push_back( m_RTOptions );

	}
	return true;
}

bool Configuration::setConfigurations( IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityTypes functionalityTypes,
						    IVIRadio::Configuration::ConfigurationOptions::FuntionalityOptions  	 funtionalityOptions ){

	auto itOptions = funtionalityOptions.cbegin();
	for (auto it = functionalityTypes.cbegin(); it != functionalityTypes.cend(); ++it, ++itOptions){
		if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::HD					){
			m_HDOptions.activation = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::HDOptions>().activation;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::Following 		){
			m_Following->setConfigurations( (*itOptions) );
			cout << "set following configuration" << endl;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::InterfaceVersion){
			m_interfaceVersionOptions.minorVersion = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions>().minorVersion;
			m_interfaceVersionOptions.majorVersion = (*itOptions).get<IVIRadio::Configuration::ConfigurationOptions::InterfaceVersionOptions>().majorVersion;
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::AvailableBand 	){
			m_AvailableBand->setConfigurations( (*itOptions ) );
		}
		else if ( (*it) == IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType::CountryVariant 	){
			m_CountryVariant->setConfigurations( ( *itOptions ) );
		}
	}
	return true;
}

