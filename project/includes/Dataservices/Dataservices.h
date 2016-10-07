/*
 * Dataservices.h
 *
 *  Created on: Sep 4, 2013
 *      Author: b
 */

#ifndef DATASERVICES_H_
#define DATASERVICES_H_

#include "IVIRadio/AdditionalService/AdditionalServiceTypes.h"


using namespace std;

/*
 * \class DataServices
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

class Dataservices {

public:

	Dataservices( IVIRadio::AdditionalService::AdditionalServiceTypes::DataService DataService );

	virtual ~Dataservices();

	IVIRadio::Types::Types::Activation getActivation( );

	//IVIRadio::AdditionalService::AdditionalServiceTypesOptions::ComponentTypeOptions getConfiguration();

	//void setTypeOptions( IVIRadio::AdditionalService::AdditionalServiceTypesOptions::ComponentTypeOptions compTypeOptions );

private:

	//IVIRadio::AdditionalService::AdditionalServiceTypesOptions::ComponentTypeOptions m_TypeOptions;

	IVIRadio::AdditionalService::AdditionalServiceTypes::DataService m_compType;

	IVIRadio::Types::Types::Activation m_active;

};

#endif /* DATASERVICES_H_ */
