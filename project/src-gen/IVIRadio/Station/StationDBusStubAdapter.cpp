/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "StationDBusStubAdapter.h"
#include <IVIRadio/Station/Station.h>

namespace IVIRadio {
namespace Station {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createStationDBusStubAdapter(
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<StationDBusStubAdapter>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerStationDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(Station::getInterfaceId(),
                                                               &createStationDBusStubAdapter);
}

StationDBusStubAdapter::StationDBusStubAdapter(
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        StationDBusStubAdapterHelper(commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, dbusConnection, std::dynamic_pointer_cast<StationStub>(stub)) {
}

const char* StationDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
    return
        "<signal name=\"currentStation\">\n"
            "<arg name=\"current\" type=\"(uaua(sy)asau(uau)u)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
            "<arg name=\"errorCode\" type=\"i\" />\n"
        "</signal>\n"
        "<signal name=\"seek\">\n"
            "<arg name=\"seekData\" type=\"(uii)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
            "<arg name=\"errorCode\" type=\"i\" />\n"
        "</signal>\n"
        "<signal name=\"stationList\">\n"
            "<arg name=\"list\" type=\"(ua(uaua(sy)asau(uau)u)u)\" />\n"
            "<arg name=\"handleOut\" type=\"u\" />\n"
            "<arg name=\"errorCode\" type=\"i\" />\n"
        "</signal>\n"
        "<method name=\"abortTune\">\n"
            "<arg name=\"deviceType\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"makePermanent\">\n"
            "<arg name=\"station\" type=\"(uau)\" direction=\"in\" />\n"
            "<arg name=\"permanent\" type=\"b\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"controlUpdate\">\n"
            "<arg name=\"updateElement\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"updateType\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"sourceType\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"stationType\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"seek\">\n"
            "<arg name=\"device\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"seekMode\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"genre\" type=\"y\" direction=\"in\" />\n"
            "<arg name=\"flags\" type=\"au\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"startTune\">\n"
            "<arg name=\"station\" type=\"(uau)\" direction=\"in\" />\n"
            "<arg name=\"selectionMode\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"handle\" type=\"u\" direction=\"in\" />\n"
            "<arg name=\"handleOut\" type=\"u\" direction=\"out\" />\n"
            "<arg name=\"feedback\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
    ;
}



static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    StationStub,
    std::tuple<Types::Types::DeviceType, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > abortTuneStubDispatcher(&StationStub::abortTune, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    StationStub,
    std::tuple<Types::Types::StationSelector, bool, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > makePermanentStubDispatcher(&StationStub::makePermanent, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    StationStub,
    std::tuple<StationTypes::UpdateElement, Types::Types::UpdateType, uint32_t, uint32_t, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > controlUpdateStubDispatcher(&StationStub::controlUpdate, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    StationStub,
    std::tuple<Types::Types::DeviceType, StationTypes::SeekMode, uint8_t, Types::Types::UInt32s, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > seekStubDispatcher(&StationStub::seek, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    StationStub,
    std::tuple<Types::Types::StationSelector, StationTypes::SelectionMode, uint32_t>,
    std::tuple<uint32_t, Types::Types::Feedback>
    > startTuneStubDispatcher(&StationStub::startTune, "ui");


template<>
const StationDBusStubAdapterHelper::StubDispatcherTable StationDBusStubAdapterHelper::stubDispatcherTable_ = {
    { { "abortTune", "iu" }, &IVIRadio::Station::abortTuneStubDispatcher },
    { { "makePermanent", "(uau)bu" }, &IVIRadio::Station::makePermanentStubDispatcher },
    { { "controlUpdate", "iiuuu" }, &IVIRadio::Station::controlUpdateStubDispatcher },
    { { "seek", "iiyauu" }, &IVIRadio::Station::seekStubDispatcher },
    { { "startTune", "(uau)iu" }, &IVIRadio::Station::startTuneStubDispatcher }
};


void StationDBusStubAdapter::fireCurrentStationEvent(const StationTypes::Station& current, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<StationTypes::Station, uint32_t, Types::Types::ErrorCodes>>
            ::sendSignal(
                *this,
                "currentStation",
                "(uaua(sy)asau(uau)u)ui",
                current, handleOut, errorCode
        );
}
void StationDBusStubAdapter::fireSeekEvent(const StationTypes::SeekData& seekData, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<StationTypes::SeekData, uint32_t, Types::Types::ErrorCodes>>
            ::sendSignal(
                *this,
                "seek",
                "(uii)ui",
                seekData, handleOut, errorCode
        );
}
void StationDBusStubAdapter::fireStationListEvent(const StationTypes::StationList& list, const uint32_t& handleOut, const Types::Types::ErrorCodes& errorCode) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<StationTypes::StationList, uint32_t, Types::Types::ErrorCodes>>
            ::sendSignal(
                *this,
                "stationList",
                "(ua(uaua(sy)asau(uau)u)u)ui",
                list, handleOut, errorCode
        );
}

} // namespace Station
} // namespace IVIRadio
