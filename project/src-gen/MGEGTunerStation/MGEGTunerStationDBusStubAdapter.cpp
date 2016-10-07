/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "MGEGTunerStationDBusStubAdapter.h"
#include <MGEGTunerStation/MGEGTunerStation.h>

namespace MGEGTunerStation {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createMGEGTunerStationDBusStubAdapter(
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<MGEGTunerStationDBusStubAdapter>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerMGEGTunerStationDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(MGEGTunerStation::getInterfaceId(),
                                                               &createMGEGTunerStationDBusStubAdapter);
}

MGEGTunerStationDBusStubAdapter::MGEGTunerStationDBusStubAdapter(
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        MGEGTunerStationDBusStubAdapterHelper(commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, dbusConnection, std::dynamic_pointer_cast<MGEGTunerStationStub>(stub)) {
}

const char* MGEGTunerStationDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
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
    MGEGTunerStationStub,
    std::tuple<MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector, MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > startTuneStubDispatcher(&MGEGTunerStationStub::startTune, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    MGEGTunerStationStub,
    std::tuple<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > abortTuneStubDispatcher(&MGEGTunerStationStub::abortTune, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    MGEGTunerStationStub,
    std::tuple<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType, MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s, uint32_t>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > seekStubDispatcher(&MGEGTunerStationStub::seek, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    MGEGTunerStationStub,
    std::tuple<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement, MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > controlUpdateStubDispatcher(&MGEGTunerStationStub::controlUpdate, "ui");

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    MGEGTunerStationStub,
    std::tuple<MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector, MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>,
    std::tuple<MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32, MGEGTunerTypes::MGEGTunerTypes::Feedback>
    > makePermanentStubDispatcher(&MGEGTunerStationStub::makePermanent, "ui");


template<>
const MGEGTunerStationDBusStubAdapterHelper::StubDispatcherTable MGEGTunerStationDBusStubAdapterHelper::stubDispatcherTable_ = {
    { { "startTune", "(uau)iu" }, &MGEGTunerStation::startTuneStubDispatcher },
    { { "abortTune", "iu" }, &MGEGTunerStation::abortTuneStubDispatcher },
    { { "seek", "iiyauu" }, &MGEGTunerStation::seekStubDispatcher },
    { { "controlUpdate", "iiuuu" }, &MGEGTunerStation::controlUpdateStubDispatcher },
    { { "makePermanent", "(uau)bu" }, &MGEGTunerStation::makePermanentStubDispatcher }
};


void MGEGTunerStationDBusStubAdapter::fireSeekEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekData& seekData, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekData, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>>
            ::sendSignal(
                *this,
                "seek",
                "(uii)u",
                seekData, handle
        );
}
void MGEGTunerStationDBusStubAdapter::fireStationListEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationList& list, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle_out) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::StationList, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>>
            ::sendSignal(
                *this,
                "stationList",
                "(ua(auaua(sy)asau(uau)u)u)u",
                list, handle_out
        );
}
void MGEGTunerStationDBusStubAdapter::fireCurrentStationEvent(const MGEGTunerStationTypes::MGEGTunerStationTypes::Station& current, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& handle) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<MGEGTunerStationTypes::MGEGTunerStationTypes::Station, MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32>>
            ::sendSignal(
                *this,
                "currentStation",
                "(auaua(sy)asau(uau)u)u",
                current, handle
        );
}

} // namespace MGEGTunerStation
