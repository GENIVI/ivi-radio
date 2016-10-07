/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_Options_Getter_H_
#define IVIRADIO_CONFIGURATION_Configuration_Options_Getter_H_

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

namespace ConfigurationOptionsGetter {
    struct EPGOptionsGet: CommonAPI::SerializableStruct {
    
        EPGOptionsGet() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct TPEGOptionsGet: CommonAPI::SerializableStruct {
    
        TPEGOptionsGet() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct RegionalisationOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
    
        RegionalisationOptionsGet() = default;
        RegionalisationOptionsGet(const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct DLSOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
    
        DLSOptionsGet() = default;
        DLSOptionsGet(const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct AvailableBandoptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
    
        AvailableBandoptionsGet() = default;
        AvailableBandoptionsGet(const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct RTOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
    
        RTOptionsGet() = default;
        RTOptionsGet(const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct CoverageAreaOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
    
        CoverageAreaOptionsGet() = default;
        CoverageAreaOptionsGet(const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct AMModiOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceType deviceType;
    
        AMModiOptionsGet() = default;
        AMModiOptionsGet(const Types::Types::DeviceType& deviceType);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct RDSOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
    
        RDSOptionsGet() = default;
        RDSOptionsGet(const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct InterfaceVersionOptionsGet: CommonAPI::SerializableStruct {
    
        InterfaceVersionOptionsGet() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct HDOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceType deviceType;
    
        HDOptionsGet() = default;
        HDOptionsGet(const Types::Types::DeviceType& deviceType);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct CountryVariantsOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceTypes deviceTypes;
    
        CountryVariantsOptionsGet() = default;
        CountryVariantsOptionsGet(const Types::Types::DeviceTypes& deviceTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct FollowingOptionsGet: CommonAPI::SerializableStruct {
        ConfigurationTypesEnum::FollowingTypes followingTypes;
    
        FollowingOptionsGet() = default;
        FollowingOptionsGet(const ConfigurationTypesEnum::FollowingTypes& followingTypes);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct SmartFavoriteOptionsGet: CommonAPI::SerializableStruct {
        Types::Types::DeviceType deviceType;
    
        SmartFavoriteOptionsGet() = default;
        SmartFavoriteOptionsGet(const Types::Types::DeviceType& deviceType);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    typedef CommonAPI::Variant<HDOptionsGet, FollowingOptionsGet, SmartFavoriteOptionsGet, CountryVariantsOptionsGet, CoverageAreaOptionsGet, AvailableBandoptionsGet, InterfaceVersionOptionsGet, AMModiOptionsGet, RDSOptionsGet, RTOptionsGet, DLSOptionsGet, RegionalisationOptionsGet>  FunctionalityOptionGet;
    
    typedef std::vector<FunctionalityOptionGet> FuntionalityOptionsGet;
    

bool operator==(const EPGOptionsGet& lhs, const EPGOptionsGet& rhs);
inline bool operator!=(const EPGOptionsGet& lhs, const EPGOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TPEGOptionsGet& lhs, const TPEGOptionsGet& rhs);
inline bool operator!=(const TPEGOptionsGet& lhs, const TPEGOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const RegionalisationOptionsGet& lhs, const RegionalisationOptionsGet& rhs);
inline bool operator!=(const RegionalisationOptionsGet& lhs, const RegionalisationOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const DLSOptionsGet& lhs, const DLSOptionsGet& rhs);
inline bool operator!=(const DLSOptionsGet& lhs, const DLSOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const AvailableBandoptionsGet& lhs, const AvailableBandoptionsGet& rhs);
inline bool operator!=(const AvailableBandoptionsGet& lhs, const AvailableBandoptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const RTOptionsGet& lhs, const RTOptionsGet& rhs);
inline bool operator!=(const RTOptionsGet& lhs, const RTOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const CoverageAreaOptionsGet& lhs, const CoverageAreaOptionsGet& rhs);
inline bool operator!=(const CoverageAreaOptionsGet& lhs, const CoverageAreaOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const AMModiOptionsGet& lhs, const AMModiOptionsGet& rhs);
inline bool operator!=(const AMModiOptionsGet& lhs, const AMModiOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const RDSOptionsGet& lhs, const RDSOptionsGet& rhs);
inline bool operator!=(const RDSOptionsGet& lhs, const RDSOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const InterfaceVersionOptionsGet& lhs, const InterfaceVersionOptionsGet& rhs);
inline bool operator!=(const InterfaceVersionOptionsGet& lhs, const InterfaceVersionOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const HDOptionsGet& lhs, const HDOptionsGet& rhs);
inline bool operator!=(const HDOptionsGet& lhs, const HDOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const CountryVariantsOptionsGet& lhs, const CountryVariantsOptionsGet& rhs);
inline bool operator!=(const CountryVariantsOptionsGet& lhs, const CountryVariantsOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const FollowingOptionsGet& lhs, const FollowingOptionsGet& rhs);
inline bool operator!=(const FollowingOptionsGet& lhs, const FollowingOptionsGet& rhs) {
    return !(lhs == rhs);
}
bool operator==(const SmartFavoriteOptionsGet& lhs, const SmartFavoriteOptionsGet& rhs);
inline bool operator!=(const SmartFavoriteOptionsGet& lhs, const SmartFavoriteOptionsGet& rhs) {
    return !(lhs == rhs);
}


static inline const char* getTypeCollectionName() {
    return "IVIRadio.Configuration.ConfigurationOptionsGetter";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(2, 0);
}

} // namespace ConfigurationOptionsGetter

} // namespace Configuration
} // namespace IVIRadio

namespace CommonAPI {
	
	
}


namespace std {
}

#endif // IVIRADIO_CONFIGURATION_Configuration_Options_Getter_H_
