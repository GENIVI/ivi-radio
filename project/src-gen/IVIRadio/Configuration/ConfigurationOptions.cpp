/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "ConfigurationOptions.h"

namespace IVIRadio {
namespace Configuration {
namespace ConfigurationOptions {

RegionalisationOptions::RegionalisationOptions(const Types::Types::DeviceTypes& deviceTypesValue, const Types::Types::Activations& activationsValue):
        deviceTypes(deviceTypesValue),
        activations(activationsValue)
{
}

bool operator==(const RegionalisationOptions& lhs, const RegionalisationOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes &&
        lhs.activations == rhs.activations
    ;
}

void RegionalisationOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
    inputStream >> activations;
}

void RegionalisationOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
    outputStream << activations;
}
AvailableBandoptions::AvailableBandoptions(const Types::Types::SourceTypes& availableBandsValue, const Types::Types::DeviceTypes& deviceTypesValue):
        availableBands(availableBandsValue),
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const AvailableBandoptions& lhs, const AvailableBandoptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.availableBands == rhs.availableBands &&
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void AvailableBandoptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> availableBands;
    inputStream >> deviceTypes;
}

void AvailableBandoptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << availableBands;
    outputStream << deviceTypes;
}
CoverageAreaOptions::CoverageAreaOptions(const ConfigurationTypesEnum::CountryVariants& countryVariantsValue, const Types::Types::DeviceTypes& deviceTypesValue):
        countryVariants(countryVariantsValue),
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const CoverageAreaOptions& lhs, const CoverageAreaOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.countryVariants == rhs.countryVariants &&
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void CoverageAreaOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> countryVariants;
    inputStream >> deviceTypes;
}

void CoverageAreaOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << countryVariants;
    outputStream << deviceTypes;
}
DLSOptions::DLSOptions(const Types::Types::Activations& activationsValue, const Types::Types::DeviceTypes& deviceTypesValue):
        activations(activationsValue),
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const DLSOptions& lhs, const DLSOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.activations == rhs.activations &&
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void DLSOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> activations;
    inputStream >> deviceTypes;
}

void DLSOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << activations;
    outputStream << deviceTypes;
}
RDSOptions::RDSOptions(const Types::Types::Activations& activationsValue, const Types::Types::DeviceTypes& deviceTypesValue):
        activations(activationsValue),
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const RDSOptions& lhs, const RDSOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.activations == rhs.activations &&
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void RDSOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> activations;
    inputStream >> deviceTypes;
}

void RDSOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << activations;
    outputStream << deviceTypes;
}
RTOptions::RTOptions(const Types::Types::Activations& activationsValue, const Types::Types::DeviceTypes& deviceTypesValue):
        activations(activationsValue),
        deviceTypes(deviceTypesValue)
{
}

bool operator==(const RTOptions& lhs, const RTOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.activations == rhs.activations &&
        lhs.deviceTypes == rhs.deviceTypes
    ;
}

void RTOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> activations;
    inputStream >> deviceTypes;
}

void RTOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << activations;
    outputStream << deviceTypes;
}
AMModiOptions::AMModiOptions(const ConfigurationTypesEnum::AMMode& amModeValue, const Types::Types::DeviceType& deviceTypeValue):
        amMode(amModeValue),
        deviceType(deviceTypeValue)
{
}

bool operator==(const AMModiOptions& lhs, const AMModiOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.amMode == rhs.amMode &&
        lhs.deviceType == rhs.deviceType
    ;
}

void AMModiOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> amMode;
    inputStream >> deviceType;
}

void AMModiOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << amMode;
    outputStream << deviceType;
}
InterfaceVersionOptions::InterfaceVersionOptions(const uint32_t& minorVersionValue, const uint32_t& majorVersionValue):
        minorVersion(minorVersionValue),
        majorVersion(majorVersionValue)
{
}

bool operator==(const InterfaceVersionOptions& lhs, const InterfaceVersionOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.minorVersion == rhs.minorVersion &&
        lhs.majorVersion == rhs.majorVersion
    ;
}

void InterfaceVersionOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> minorVersion;
    inputStream >> majorVersion;
}

void InterfaceVersionOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << minorVersion;
    outputStream << majorVersion;
}
HDOptions::HDOptions(const Types::Types::Activation& activationValue):
        activation(activationValue)
{
}

bool operator==(const HDOptions& lhs, const HDOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.activation == rhs.activation
    ;
}

void HDOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> activation;
}

void HDOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << activation;
}
CountryVariantsOptions::CountryVariantsOptions(const Types::Types::DeviceTypes& deviceTypesValue, const ConfigurationTypesEnum::CountryVariants& countryVariantsValue):
        deviceTypes(deviceTypesValue),
        countryVariants(countryVariantsValue)
{
}

bool operator==(const CountryVariantsOptions& lhs, const CountryVariantsOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.deviceTypes == rhs.deviceTypes &&
        lhs.countryVariants == rhs.countryVariants
    ;
}

void CountryVariantsOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> deviceTypes;
    inputStream >> countryVariants;
}

void CountryVariantsOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << deviceTypes;
    outputStream << countryVariants;
}
FollowingOptions::FollowingOptions(const Types::Types::Activations& activationsValue, const ConfigurationTypesEnum::FollowingTypes& followingStatesValue):
        activations(activationsValue),
        followingStates(followingStatesValue)
{
}

bool operator==(const FollowingOptions& lhs, const FollowingOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.activations == rhs.activations &&
        lhs.followingStates == rhs.followingStates
    ;
}

void FollowingOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> activations;
    inputStream >> followingStates;
}

void FollowingOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << activations;
    outputStream << followingStates;
}
SmartFavoriteOptions::SmartFavoriteOptions(const Types::Types::Activation& activityValue):
        activity(activityValue)
{
}

bool operator==(const SmartFavoriteOptions& lhs, const SmartFavoriteOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.activity == rhs.activity
    ;
}

void SmartFavoriteOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> activity;
}

void SmartFavoriteOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << activity;
}
EPGOptions::EPGOptions(const ConfigurationTypesEnum::EPGCollectionMode& collectionModeValue):
        collectionMode(collectionModeValue)
{
}

bool operator==(const EPGOptions& lhs, const EPGOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.collectionMode == rhs.collectionMode
    ;
}

void EPGOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> collectionMode;
}

void EPGOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << collectionMode;
}
TPEGOptions::TPEGOptions(const ConfigurationTypesEnum::TPEGRequestMode& requestModeValue):
        requestMode(requestModeValue)
{
}

bool operator==(const TPEGOptions& lhs, const TPEGOptions& rhs) {
    if (&lhs == &rhs)
        return true;

    return
        lhs.requestMode == rhs.requestMode
    ;
}

void TPEGOptions::readFromInputStream(CommonAPI::InputStream& inputStream) {
    inputStream >> requestMode;
}

void TPEGOptions::writeToOutputStream(CommonAPI::OutputStream& outputStream) const {
    outputStream << requestMode;
}

} // namespace ConfigurationOptions
} // namespace Configuration
} // namespace IVIRadio
