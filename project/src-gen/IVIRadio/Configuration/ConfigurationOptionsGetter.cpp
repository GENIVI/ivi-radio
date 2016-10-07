/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "ConfigurationOptionsGetter.h"

namespace IVIRadio {
namespace Configuration {
namespace ConfigurationOptionsGetter {


bool operator==(const EPGOptionsGet& lhs, const EPGOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void EPGOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void EPGOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}

bool operator==(const TPEGOptionsGet& lhs, const TPEGOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void TPEGOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void TPEGOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
RegionalisationOptionsGet::RegionalisationOptionsGet(const Types::Types::DeviceTypes& deviceTypesValue):
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const RegionalisationOptionsGet& lhs, const RegionalisationOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void RegionalisationOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
}

void RegionalisationOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
}
DLSOptionsGet::DLSOptionsGet(const Types::Types::DeviceTypes& deviceTypesValue):
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const DLSOptionsGet& lhs, const DLSOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void DLSOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
}

void DLSOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
}
AvailableBandoptionsGet::AvailableBandoptionsGet(const Types::Types::DeviceTypes& deviceTypesValue):
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const AvailableBandoptionsGet& lhs, const AvailableBandoptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void AvailableBandoptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
}

void AvailableBandoptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
}
RTOptionsGet::RTOptionsGet(const Types::Types::DeviceTypes& deviceTypesValue):
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const RTOptionsGet& lhs, const RTOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void RTOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
}

void RTOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
}
CoverageAreaOptionsGet::CoverageAreaOptionsGet(const Types::Types::DeviceTypes& deviceTypesValue):
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const CoverageAreaOptionsGet& lhs, const CoverageAreaOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void CoverageAreaOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
}

void CoverageAreaOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
}
AMModiOptionsGet::AMModiOptionsGet(const Types::Types::DeviceType& deviceTypeValue):
        deviceType(deviceTypeValue)
{
}

bool operator==(const AMModiOptionsGet& lhs, const AMModiOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceType == rhs.deviceType
    ;
}

void AMModiOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceType;
}

void AMModiOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceType;
}
RDSOptionsGet::RDSOptionsGet(const Types::Types::DeviceTypes& deviceTypesValue):
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const RDSOptionsGet& lhs, const RDSOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void RDSOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
}

void RDSOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
}

bool operator==(const InterfaceVersionOptionsGet& lhs, const InterfaceVersionOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        true
    ;
}

void InterfaceVersionOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
}

void InterfaceVersionOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
}
HDOptionsGet::HDOptionsGet(const Types::Types::DeviceType& deviceTypeValue):
        deviceType(deviceTypeValue)
{
}

bool operator==(const HDOptionsGet& lhs, const HDOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceType == rhs.deviceType
    ;
}

void HDOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceType;
}

void HDOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceType;
}
CountryVariantsOptionsGet::CountryVariantsOptionsGet(const Types::Types::DeviceTypes& deviceTypesValue):
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const CountryVariantsOptionsGet& lhs, const CountryVariantsOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void CountryVariantsOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
}

void CountryVariantsOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
}
FollowingOptionsGet::FollowingOptionsGet(const ConfigurationTypesEnum::FollowingTypes& followingTypesValue):
        followingTypes(followingTypesValue)
{
}

bool operator==(const FollowingOptionsGet& lhs, const FollowingOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.followingTypes == rhs.followingTypes
    ;
}

void FollowingOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> followingTypes;
}

void FollowingOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << followingTypes;
}
SmartFavoriteOptionsGet::SmartFavoriteOptionsGet(const Types::Types::DeviceType& deviceTypeValue):
        deviceType(deviceTypeValue)
{
}

bool operator==(const SmartFavoriteOptionsGet& lhs, const SmartFavoriteOptionsGet& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceType == rhs.deviceType
    ;
}

void SmartFavoriteOptionsGet::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceType;
}

void SmartFavoriteOptionsGet::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceType;
}

} // namespace ConfigurationOptionsGetter
} // namespace Configuration
} // namespace IVIRadio
