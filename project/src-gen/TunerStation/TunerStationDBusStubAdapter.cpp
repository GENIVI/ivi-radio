/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "TunerStationDBusStubAdapter.h"
#include <TunerStation/TunerStation.h>

namespace TunerStation {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createTunerStationDBusStubAdapter(
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<TunerStationDBusStubAdapter>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerTunerStationDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(TunerStation::getInterfaceId(),
                                                               &createTunerStationDBusStubAdapter);
}

TunerStationDBusStubAdapter::TunerStationDBusStubAdapter(
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        TunerStationDBusStubAdapterHelper(commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, dbusConnection, std::dynamic_pointer_cast<TunerStationStub>(stub)) {
}

const char* TunerStationDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
    return
        "<signal name=\"seek\">\n"
            "<arg name=\"seekData\" type=\"(uii)\" />\n"
            "<arg name=\"handle\" type=\"u\" />\n"
        "</signal>\n"
        "<signal name=\"stationList\">\n"
            "<arg name=\"list\" type=\"(ua(auaua(sy)asau(uau)u)u)\" />\n"
            "<arg name=\"handle_out\" type=\"u\" />\n"
        "</signal>\n"
        "<signal name=\"currentStation\">\n"
            "<arg name=\"current\" type=\"(auaua(sy)asau(uau)u)\" />\n"
            "<arg name=\"handle\" type=\"u\" />\n"
        "</signal>\n"
        "<method name=\"startTune\">\n"
            "<arg name=\"station\" type=\"(uau)\" direction=\"in\" />\n"
            "<arg name=\"selectionMode\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle_out\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"abortTune\">\n"
            "<arg name=\"device\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle_out\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"seek\">\n"
            "<arg name=\"device\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"seekMode\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"genre\" type=\"y\" direction=\"in\" />\n"
            "<arg name=\"flags\" type=\"au\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle_out\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"controlUpdate\">\n"
            "<arg name=\"updateElement\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"updateType\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"sourceType\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"stationType\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle_out\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"makePermanent\">\n"
            "<arg name=\"station\" type=\"(uau)\" direction=\"in\" />\n"
            "<arg name=\"permanent\" type=\"b\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle_out\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
    ;
}



static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerStationStub,
    std::tuple<TunerStationTypes::TunerStationTypes::StationSelector, TunerStationTypes::TunerStationTypes::SelectionMode, uint32_t>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > startTuneStubDispatcher(&TunerStationStub::startTune, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerStationStub,
    std::tuple<TunerStationTypes::TunerStationTypes::DeviceType, uint32_t>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > abortTuneStubDispatcher(&TunerStationStub::abortTune, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerStationStub,
    std::tuple<TunerStationTypes::TunerStationTypes::DeviceType, TunerStationTypes::TunerStationTypes::SeekMode, uint8_t, TunerTypes::TunerTypes::UInt32s, uint32_t>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > seekStubDispatcher(&TunerStationStub::seek, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerStationStub,
    std::tuple<TunerStationTypes::TunerStationTypes::UpdateElement, TunerStationTypes::TunerStationTypes::UpdateType, uint32_t, uint32_t, uint32_t>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > controlUpdateStubDispatcher(&TunerStationStub::controlUpdate, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    TunerStationStub,
    std::tuple<TunerStationTypes::TunerStationTypes::StationSelector, bool, uint32_t>,
    std::tuple<uint32_t, TunerTypes::TunerTypes::Feedback>
    > makePermanentStubDispatcher(&TunerStationStub::makePermanent, "ui");


template<>
const TunerStationDBusStubAdapterHelper::StubDispatcherTable TunerStationDBusStubAdapterHelper::stubDispatcherTable_ = {
    { { "startTune", "(uau)iu" }, &TunerStation::startTuneStubDispatcher },
    { { "abortTune", "iu" }, &TunerStation::abortTuneStubDispatcher },
    { { "seek", "iiyauu" }, &TunerStation::seekStubDispatcher },
    { { "controlUpdate", "iiuuu" }, &TunerStation::controlUpdateStubDispatcher },
    { { "makePermanent", "(uau)bu" }, &TunerStation::makePermanentStubDispatcher }
};


void TunerStationDBusStubAdapter::fireSeekEvent(const TunerStationTypes::TunerStationTypes::SeekData& seekData, const uint32_t& handle) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::SeekData, uint32_t>>
            ::sendSignal(
                *this,
                "seek",
                "(uii)u",
                seekData, handle
        );
}
void TunerStationDBusStubAdapter::fireStationListEvent(const TunerStationTypes::TunerStationTypes::StationList& list, const uint32_t& handle_out) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::StationList, uint32_t>>
            ::sendSignal(
                *this,
                "stationList",
                "(ua(auaua(sy)asau(uau)u)u)u",
                list, handle_out
        );
}
void TunerStationDBusStubAdapter::fireCurrentStationEvent(const TunerStationTypes::TunerStationTypes::Station& current, const uint32_t& handle) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<TunerStationTypes::TunerStationTypes::Station, uint32_t>>
            ::sendSignal(
                *this,
                "currentStation",
                "(auaua(sy)asau(uau)u)u",
                current, handle
        );
}

} // namespace TunerStation
