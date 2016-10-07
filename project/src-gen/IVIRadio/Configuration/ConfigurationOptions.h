/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_Options_H_
#define IVIRADIO_CONFIGURATION_Configuration_Options_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/SerializableVariant.h>
#include <CommonAPI/types.h>
#include <IVIRadio/Configuration/ConfigurationTypesEnum.h>
#include <IVIRadio/Types/Types.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace IVIRadio {
namespace Configuration {

namespace ConfigurationOptions {
    struct AvailableBandoptions: CommonAPI::SerializableStruct {
        Types::Types::SourceTypes availableBands;
        Types::Types::DeviceTypes deviceTypes;
    
        AvailableBandoptions() = default;
        AvailableBandoptions(const Types::Types::SourceTypes& availableBands, const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct CoverageAreaOptions: CommonAPI::SerializableStruct {
        ConfigurationTypesEnum::CountryVariants countryVariants;
        Types::Types::DeviceTypes deviceTypes;
    
        CoverageAreaOptions() = default;
        CoverageAreaOptions(const ConfigurationTypesEnum::CountryVariants& countryVariants, const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct DLSOptions: CommonAPI::SerializableStruct {
        Types::Types::Activations activations;
        Types::Types::DeviceTypes deviceTypes;
    
        DLSOptions() = default;
        DLSOptions(const Types::Types::Activations& activations, const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct RDSOptions: CommonAPI::SerializableStruct {
        Types::Types::Activations activations;
        Types::Types::DeviceTypes deviceTypes;
    
        RDSOptions() = default;
        RDSOptions(const Types::Types::Activations& activations, const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct RTOptions: CommonAPI::SerializableStruct {
        Types::Types::Activations activations;
        Types::Types::DeviceTypes deviceTypes;
    
        RTOptions() = default;
        RTOptions(const Types::Types::Activations& activations, const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct AMModiOptions: CommonAPI::SerializableStruct {
        ConfigurationTypesEnum::AMMode amMode;
        Types::Types::DeviceType deviceType;
    
        AMModiOptions() = default;
        AMModiOptions(const ConfigurationTypesEnum::AMMode& amMode, const Types::Types::DeviceType& deviceType);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct InterfaceVersionOptions: CommonAPI::SerializableStruct {
        uint32_t minorVersion;
        uint32_t majorVersion;
    
        InterfaceVersionOptions() = default;
        InterfaceVersionOptions(const uint32_t& minorVersion, const uint32_t& majorVersion);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    struct HDOptions: CommonAPI::SerializableStruct {
        Types::Types::Activation activation;
    
        HDOptions() = default;
        HDOptions(const Types::Types::Activation& activation);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct CountryVariantsOptions: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
        ConfigurationTypesEnum::CountryVariants countryVariants;
    
        CountryVariantsOptions() = default;
        CountryVariantsOptions(const Types::Types::DeviceTypes& deviceTypes, const ConfigurationTypesEnum::CountryVariants& countryVariants);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct FollowingOptions: CommonAPI::SerializableStruct {
        Types::Types::Activations activations;
        ConfigurationTypesEnum::FollowingTypes followingStates;
    
        FollowingOptions() = default;
        FollowingOptions(const Types::Types::Activations& activations, const ConfigurationTypesEnum::FollowingTypes& followingStates);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct SmartFavoriteOptions: CommonAPI::SerializableStruct {
        Types::Types::Activation activity;
    
        SmartFavoriteOptions() = default;
        SmartFavoriteOptions(const Types::Types::Activation& activity);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    typedef CommonAPI::Variant<HDOptions, FollowingOptions, SmartFavoriteOptions, CountryVariantsOptions, CoverageAreaOptions, AvailableBandoptions, InterfaceVersionOptions, AMModiOptions, RDSOptions, DLSOptions, RTOptions>  FunctionalityOption;
    
    typedef std::vector<FunctionalityOption> FuntionalityOptions;
    
    struct RegionalisationOptions: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
        Types::Types::Activations activations;
    
        RegionalisationOptions() = default;
        RegionalisationOptions(const Types::Types::DeviceTypes& deviceTypes, const Types::Types::Activations& activations);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct EPGOptions: CommonAPI::SerializableStruct {
        ConfigurationTypesEnum::EPGCollectionMode collectionMode;
    
        EPGOptions() = default;
        EPGOptions(const ConfigurationTypesEnum::EPGCollectionMode& collectionMode);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct TPEGOptions: CommonAPI::SerializableStruct {
        ConfigurationTypesEnum::TPEGRequestMode requestMode;
    
        TPEGOptions() = default;
        TPEGOptions(const ConfigurationTypesEnum::TPEGRequestMode& requestMode);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    

bool operator==(const RegionalisationOptions& lhs, const RegionalisationOptions& rhs);
inline bool operator!=(const RegionalisationOptions& lhs, const RegionalisationOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const AvailableBandoptions& lhs, const AvailableBandoptions& rhs);
inline bool operator!=(const AvailableBandoptions& lhs, const AvailableBandoptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const CoverageAreaOptions& lhs, const CoverageAreaOptions& rhs);
inline bool operator!=(const CoverageAreaOptions& lhs, const CoverageAreaOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const DLSOptions& lhs, const DLSOptions& rhs);
inline bool operator!=(const DLSOptions& lhs, const DLSOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const RDSOptions& lhs, const RDSOptions& rhs);
inline bool operator!=(const RDSOptions& lhs, const RDSOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const RTOptions& lhs, const RTOptions& rhs);
inline bool operator!=(const RTOptions& lhs, const RTOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const AMModiOptions& lhs, const AMModiOptions& rhs);
inline bool operator!=(const AMModiOptions& lhs, const AMModiOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const InterfaceVersionOptions& lhs, const InterfaceVersionOptions& rhs);
inline bool operator!=(const InterfaceVersionOptions& lhs, const InterfaceVersionOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const HDOptions& lhs, const HDOptions& rhs);
inline bool operator!=(const HDOptions& lhs, const HDOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const CountryVariantsOptions& lhs, const CountryVariantsOptions& rhs);
inline bool operator!=(const CountryVariantsOptions& lhs, const CountryVariantsOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const FollowingOptions& lhs, const FollowingOptions& rhs);
inline bool operator!=(const FollowingOptions& lhs, const FollowingOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const SmartFavoriteOptions& lhs, const SmartFavoriteOptions& rhs);
inline bool operator!=(const SmartFavoriteOptions& lhs, const SmartFavoriteOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const EPGOptions& lhs, const EPGOptions& rhs);
inline bool operator!=(const EPGOptions& lhs, const EPGOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TPEGOptions& lhs, const TPEGOptions& rhs);
inline bool operator!=(const TPEGOptions& lhs, const TPEGOptions& rhs) {
    return !(lhs == rhs);
}


static inline const char* getTypeCollectionName() {
    return "IVIRadio.Configuration.ConfigurationOptions";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(2, 0);
}

} // namespace ConfigurationOptions

} // namespace Configuration
} // namespace IVIRadio

namespace CommonAPI {
	
	
}


namespace std {
}

#endif // IVIRADIO_CONFIGURATION_Configuration_Options_H_
