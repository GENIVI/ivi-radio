/*
 * Dataservices.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: b
 */

#include "includes/Dataservices/Dataservices.h"

Dataservices::Dataservices( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService ) {

	m_compType = dataService;
	m_active = IVIRadio::Types::Types::Activation::INACTIVE;
	if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_EWS ){
		//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::BWS_TypeOptions temp;
		//m_TypeOptions = temp;
		//temp.active =  IVIRadio::Types::Types::Activation::INACTIVE;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_EPG ){
		//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::EPG_TypeOptions temp;
		//m_TypeOptions = temp;
		//temp.active =  IVIRadio::Types::Types::Activation::INACTIVE;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_JOURNALINE ){
		//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Journaline_TypeOptions temp;
		//m_TypeOptions = temp;
		//temp.active =  IVIRadio::Types::Types::Activation::INACTIVE;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_IMAGE ){
		//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Slideshow_TypeOptions temp;
		//m_TypeOptions = temp;
		//temp.active =  IVIRadio::Types::Types::Activation::INACTIVE;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_SUBTITLE ){
		//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Subtitle_TypeOptions temp;
		//m_TypeOptions = temp;
		//temp.active =  IVIRadio::Types::Types::Activation::INACTIVE;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_TELETEXT ){
		//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Teletext_TypeOptions temp;
		//m_TypeOptions = temp;
		//temp.active =  IVIRadio::Types::Types::Activation::INACTIVE;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_TMC ){
		//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TMC_TypeOptions temp;
		//m_TypeOptions = temp;
		//temp.active =  IVIRadio::Types::Types::Activation::INACTIVE;
	}
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_TPEG ){
		//IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TPEG_TypeOptions temp;
		//m_TypeOptions = temp;
		//temp.active =  IVIRadio::Types::Types::Activation::INACTIVE;
	}
}

Dataservices::~Dataservices() {
}

IVIRadio::Types::Types::Activation Dataservices::getActivation( ){
	return m_active;
	/*
	if ( m_compType == IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType::CT_BWS ){
		return m_TypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::BWS_TypeOptions>().active;
	}
	else if ( m_compType == IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType::CT_EPG ){
		return m_TypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::EPG_TypeOptions>().active;
	}
	else if ( m_compType == IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType::CT_JOURNALINE ){
		return m_TypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Journaline_TypeOptions>().active;
	}
	else if ( m_compType == IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType::CT_SLIDESHOW ){
		return m_TypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Slideshow_TypeOptions>().active;
	}
	else if ( m_compType == IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType::CT_SUBTITLE ){
		return m_TypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Subtitle_TypeOptions>().active;
	}
	else if ( m_compType == IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType::CT_TELETEXT ){
		return m_TypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::Teletext_TypeOptions>().active;
	}
	else if ( m_compType == IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType::CT_TMC ){
		return m_TypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TMC_TypeOptions>().active;
	}
	else if ( m_compType == IVIRadio::AdditionalService::AdditionalServiceTypes::ComponentType::CT_TPEG ){
		return m_TypeOptions.get<IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::TPEG_TypeOptions>().active;
	}*/
}

/*IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::ComponentTypeOptions Dataservices::getConfiguration() {
	return m_TypeOptions;
}*/

/*
void Dataservices::setTypeOptions( IVIRadio::AdditionalService::AdditionalServiceTypesTypeOptions::ComponentTypeOptions compTypeOptions ){
	m_TypeOptions = compTypeOptions;
}*/
