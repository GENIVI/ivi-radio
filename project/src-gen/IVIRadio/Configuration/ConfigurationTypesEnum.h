/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_CONFIGURATION_Configuration_Types_Enum_H_
#define IVIRADIO_CONFIGURATION_Configuration_Types_Enum_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/types.h>
#include <cstdint>
#include <vector>

namespace IVIRadio {
namespace Configuration {

namespace ConfigurationTypesEnum {
    enum class CountryVariant: int32_t {
        CV_EUROPE,
        CV_AUSTRALIA,
        CV_HONGKONG,
        CV_KOREA,
        CV_CHINA,
        CV_USA,
        CV_OZEANIEN,
        CV_JAPAN,
        CV_EUROPE_ROW
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct CountryVariantComparator;
    
    typedef std::vector<CountryVariant> CountryVariants;
    
    enum class FollowingType: int32_t {
        FM_INTERNAL,
        FM_DAB,
        DAB_INTERNAL,
        DAB_FM,
        DVBT_INTERNAL,
        DVBT_DAB
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct FollowingTypeComparator;
    
    typedef std::vector<FollowingType> FollowingTypes;
    
    enum class FunctionalityType: int32_t {
        HD,
        Following,
        ParentalLock,
        SmartFavorite,
        CIModule,
        AvailableBand,
        CountryVariant,
        Coding,
        CoverageArea,
        InterfaceVersion,
        AMModi,
        Regionalisation,
        RT,
        DLS,
        RDS,
        EPG,
        TPEG
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct FunctionalityTypeComparator;
    
    typedef std::vector<FunctionalityType> FunctionalityTypes;
    
    enum class AMMode: int32_t {
        AM_ONLY_MW,
        AM_ONLY_LW,
        AM_MWLW
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct AMModeComparator;
    
    enum class TPEGRequestMode: int32_t {
        RM_CURRENT_STATION,
        RM_CURRENT_ENSEMBLE,
        RM_ANY_ENSEMBLE
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct TPEGRequestModeComparator;
    
    enum class EPGCollectionMode: int32_t {
        CM_NO_COLLECTION_MODE,
        CM_ONLY_CURRENT_STATION,
        CM_ALL_RECEIVABLE_STATIONS
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct EPGCollectionModeComparator;
    

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, FunctionalityType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const FunctionalityType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct FunctionalityTypeComparator {
    inline bool operator()(const FunctionalityType& lhs, const FunctionalityType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, AMMode& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const AMMode& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct AMModeComparator {
    inline bool operator()(const AMMode& lhs, const AMMode& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, FollowingType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const FollowingType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct FollowingTypeComparator {
    inline bool operator()(const FollowingType& lhs, const FollowingType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, CountryVariant& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const CountryVariant& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct CountryVariantComparator {
    inline bool operator()(const CountryVariant& lhs, const CountryVariant& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, TPEGRequestMode& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const TPEGRequestMode& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct TPEGRequestModeComparator {
    inline bool operator()(const TPEGRequestMode& lhs, const TPEGRequestMode& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, EPGCollectionMode& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const EPGCollectionMode& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct EPGCollectionModeComparator {
    inline bool operator()(const EPGCollectionMode& lhs, const EPGCollectionMode& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};



static inline const char* getTypeCollectionName() {
    return "IVIRadio.Configuration.ConfigurationTypesEnum";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(2, 0);
}

} // namespace ConfigurationTypesEnum

} // namespace Configuration
} // namespace IVIRadio

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Configuration::ConfigurationTypesEnum::AMMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::AMMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::AMMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::AMMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::AMMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Configuration::ConfigurationTypesEnum::TPEGRequestMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::TPEGRequestMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::TPEGRequestMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::TPEGRequestMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::TPEGRequestMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Configuration::ConfigurationTypesEnum::EPGCollectionMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::EPGCollectionMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::EPGCollectionMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Configuration::ConfigurationTypesEnum::EPGCollectionMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Configuration::ConfigurationTypesEnum::EPGCollectionMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType> {
        inline size_t operator()(const IVIRadio::Configuration::ConfigurationTypesEnum::FunctionalityType& functionalityType) const {
            return static_cast<int32_t>(functionalityType);
        }
    };
    template<>
    struct hash<IVIRadio::Configuration::ConfigurationTypesEnum::AMMode> {
        inline size_t operator()(const IVIRadio::Configuration::ConfigurationTypesEnum::AMMode& aMMode) const {
            return static_cast<int32_t>(aMMode);
        }
    };
    template<>
    struct hash<IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType> {
        inline size_t operator()(const IVIRadio::Configuration::ConfigurationTypesEnum::FollowingType& followingType) const {
            return static_cast<int32_t>(followingType);
        }
    };
    template<>
    struct hash<IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant> {
        inline size_t operator()(const IVIRadio::Configuration::ConfigurationTypesEnum::CountryVariant& countryVariant) const {
            return static_cast<int32_t>(countryVariant);
        }
    };
    template<>
    struct hash<IVIRadio::Configuration::ConfigurationTypesEnum::TPEGRequestMode> {
        inline size_t operator()(const IVIRadio::Configuration::ConfigurationTypesEnum::TPEGRequestMode& tPEGRequestMode) const {
            return static_cast<int32_t>(tPEGRequestMode);
        }
    };
    template<>
    struct hash<IVIRadio::Configuration::ConfigurationTypesEnum::EPGCollectionMode> {
        inline size_t operator()(const IVIRadio::Configuration::ConfigurationTypesEnum::EPGCollectionMode& ePGCollectionMode) const {
            return static_cast<int32_t>(ePGCollectionMode);
        }
    };
}

#endif // IVIRADIO_CONFIGURATION_Configuration_Types_Enum_H_
