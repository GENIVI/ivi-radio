/*
Copyright (C) 2013 BMW Group

Author: Guido Ostkamp     (guido.ostkamp@de.bertrandt.com)
Author: Bernhard Singer   (bernhard.singer@partner.bmw.de)
Author: Matthias Freundel (matthias.freundel@partner.bmw.de)

This Source Code Form is subject to the terms of the Mozilla Public

License, v. 2.0. If a copy of the MPL was not distributed with this file,

You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef MY_PROVIDER_H
#define MY_PROVIDER_H
#include <memory>
#include <iostream>
#include <unistd.h>

#include <TunerStation/TunerStationStubDefault.h>
#include <TunerAdditionalService/TunerAdditionalServiceStubDefault.h>

#include <CommonAPI/Runtime.h>
#include <signal.h>
#include "MyTerminalIO.h"
#include "MyJobList.h"

class TunerStationIndividualStub : public TunerStation::TunerStationStubDefault {
 public:
	TunerStationIndividualStub();
	virtual ~TunerStationIndividualStub();

    virtual void startTune(
        TunerStationTypes::TunerStationTypes::StationSelector station,
        TunerStationTypes::TunerStationTypes::SelectionMode selectionMode,
        uint32_t handle,
        uint32_t& handle_out,
        TunerTypes::TunerTypes::Feedback& feedback
    );

    virtual void abortTune(
        TunerStationTypes::TunerStationTypes::DeviceType device,
        uint32_t handle,
        uint32_t& handle_out,
        TunerTypes::TunerTypes::Feedback& feedback
    );

    virtual void seek(
        TunerStationTypes::TunerStationTypes::DeviceType device,
        TunerStationTypes::TunerStationTypes::SeekMode seekMode,
        uint8_t genre,
        TunerTypes::TunerTypes::UInt32s flags,
        uint32_t handle,
        uint32_t& handle_out,
        TunerTypes::TunerTypes::Feedback& feedback
    );

    virtual void makePermanent(
        TunerStationTypes::TunerStationTypes::StationSelector station,
        bool permanent,
        uint32_t handle,
        uint32_t& handle_out,
        TunerTypes::TunerTypes::Feedback& feedback
    );

    virtual void controlUpdate(
        TunerStationTypes::TunerStationTypes::UpdateElement updateElement,
        TunerStationTypes::TunerStationTypes::UpdateType updateType,
        uint32_t sourceType,
        uint32_t stationType,
        uint32_t handle,
        uint32_t& handle_out,
        TunerTypes::TunerTypes::Feedback& feedback
    );
};

class TunerAdditionalServiceIndividualStub : public TunerAdditionalService::TunerAdditionalServiceStubDefault {
public:
    TunerAdditionalServiceIndividualStub();
    virtual ~TunerAdditionalServiceIndividualStub();

    virtual void changeComponentTypeConfiguration(
        TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType comptype,
        TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentTypeOptions options,
        uint32_t handle,
        uint32_t& handle_out,
        TunerTypes::TunerTypes::Feedback& feedback
    );

    virtual void requestComponentOptions(
        uint32_t componentID,
        uint32_t handle,
        TunerTypes::TunerTypes::Feedback& feedback,
        uint32_t& handle_out
    );

    virtual void requestComponentTypeConfiguration(
        TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType componentType,
        uint32_t handle,
        uint32_t& handle_out,
        TunerTypes::TunerTypes::Feedback& feedback
    );

    virtual void selectComponent(
        uint32_t componentID,
        uint32_t handle,
        TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::SelectParameter component_parameter,
        uint32_t& handle_out,
        TunerTypes::TunerTypes::Feedback& feedback
    );
};

#endif /* MY_PROVIDER_H */
