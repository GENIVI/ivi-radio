/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_TYPES_Types_H_
#define IVIRADIO_TYPES_Types_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/types.h>
#include <cstdint>
#include <string>
#include <vector>

namespace IVIRadio {
namespace Types {

namespace Types {
    typedef std::vector<uint32_t> UInt32s;
    
    struct StationSelector: CommonAPI::SerializableStruct {
        uint32_t deviceType;
        UInt32s id;
    
        StationSelector() = default;
        StationSelector(const uint32_t& deviceType, const UInt32s& id);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    typedef std::vector<StationSelector> StationSelectors;
    
    typedef std::vector<StationSelectors> arrayStationSelectors;
    
    enum class Activation: int32_t {
        ACTIVE,
        INACTIVE
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct ActivationComparator;
    
    typedef std::vector<Activation> Activations;
    
    enum class DeviceType: int32_t {
        UNDEF_DEVICE = 0x0,
        AMFM = 0xff,
        DAB = 0x3f00,
        SDARS = 0xc000,
        TV = 0x30000
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct DeviceTypeComparator;
    
    typedef std::vector<DeviceType> DeviceTypes;
    
    enum class SourceType: int32_t {
        UNDEF_SOURCE = 0x0,
        AMFM_FM = 0x1,
        AMFM_MW = 0x2,
        AMFM_LW = 0x4,
        AMFM_SW = 0x8,
        AMFM_WB = 0x10,
        AMFM_TF = 0x20,
        AMFM_HD = 0x40,
        AMFM_DRM = 0x80,
        DAB_L = 0x100,
        DAB_III = 0x200,
        DAB_DAB = 0x400,
        DAB_DAB_PLUS = 0x800,
        DAB_DMBA = 0x1000,
        DAB_DMBV = 0x2000,
        SDARS_SIRIUS = 0x4000,
        SDARS_XM = 0x8000,
        TV_A = 0x10000,
        TV_AV = 0x20000
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct SourceTypeComparator;
    
    typedef std::vector<SourceType> SourceTypes;
    
    typedef std::vector<bool> Booleans;
    
    typedef std::vector<std::string> Strings;
    
    typedef std::string DateTime;
    
    enum class ErrorCodes: int32_t {
        EC_NOTACTIVATED,
        EC_NOTRECEIVABLE,
        EC_OUTOFRESSOURCES,
        EC_NOERROR,
        EC_NOSTATIONACTIVE,
        EC_INVALIDCOMPONENTID,
        EC_NODATAAVAILABLE,
        EC_NOTACTIVE,
        EC_COMPONENTNOTSUPPORTED,
        EC_FUNCTIONALITYNOTSUPPORTED
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct ErrorCodesComparator;
    
    enum class Feedback: int32_t {
        DONE,
        INTERRUPTED,
        NOT_APPLICABLE,
        ALREADY_SET,
        FAILURE,
        DELAYED
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct FeedbackComparator;
    
    enum class UpdateType: int32_t {
        UT_NONE,
        UT_ONCE,
        UT_NOTIFICATION
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct UpdateTypeComparator;
    

bool operator==(const StationSelector& lhs, const StationSelector& rhs);
inline bool operator!=(const StationSelector& lhs, const StationSelector& rhs) {
    return !(lhs == rhs);
}
inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, Activation& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const Activation& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct ActivationComparator {
    inline bool operator()(const Activation& lhs, const Activation& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, ErrorCodes& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const ErrorCodes& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct ErrorCodesComparator {
    inline bool operator()(const ErrorCodes& lhs, const ErrorCodes& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, Feedback& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const Feedback& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct FeedbackComparator {
    inline bool operator()(const Feedback& lhs, const Feedback& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, SourceType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const SourceType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct SourceTypeComparator {
    inline bool operator()(const SourceType& lhs, const SourceType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, DeviceType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const DeviceType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct DeviceTypeComparator {
    inline bool operator()(const DeviceType& lhs, const DeviceType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, UpdateType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const UpdateType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct UpdateTypeComparator {
    inline bool operator()(const UpdateType& lhs, const UpdateType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};



static inline const char* getTypeCollectionName() {
    return "IVIRadio.Types.Types";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(2, 0);
}

} // namespace Types

} // namespace Types
} // namespace IVIRadio

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<IVIRadio::Types::Types::Activation> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Types::Types::Activation> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Types::Types::Activation>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Types::Types::Activation> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Types::Types::Activation>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Types::Types::ErrorCodes> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Types::Types::ErrorCodes> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Types::Types::ErrorCodes>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Types::Types::ErrorCodes> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Types::Types::ErrorCodes>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Types::Types::Feedback> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Types::Types::Feedback> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Types::Types::Feedback>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Types::Types::Feedback> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Types::Types::Feedback>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Types::Types::SourceType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Types::Types::SourceType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Types::Types::SourceType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Types::Types::SourceType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Types::Types::SourceType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Types::Types::DeviceType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Types::Types::DeviceType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Types::Types::DeviceType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Types::Types::DeviceType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Types::Types::DeviceType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Types::Types::UpdateType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Types::Types::UpdateType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Types::Types::UpdateType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Types::Types::UpdateType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Types::Types::UpdateType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<IVIRadio::Types::Types::Activation> {
        inline size_t operator()(const IVIRadio::Types::Types::Activation& activation) const {
            return static_cast<int32_t>(activation);
        }
    };
    template<>
    struct hash<IVIRadio::Types::Types::ErrorCodes> {
        inline size_t operator()(const IVIRadio::Types::Types::ErrorCodes& errorCodes) const {
            return static_cast<int32_t>(errorCodes);
        }
    };
    template<>
    struct hash<IVIRadio::Types::Types::Feedback> {
        inline size_t operator()(const IVIRadio::Types::Types::Feedback& feedback) const {
            return static_cast<int32_t>(feedback);
        }
    };
    template<>
    struct hash<IVIRadio::Types::Types::SourceType> {
        inline size_t operator()(const IVIRadio::Types::Types::SourceType& sourceType) const {
            return static_cast<int32_t>(sourceType);
        }
    };
    template<>
    struct hash<IVIRadio::Types::Types::DeviceType> {
        inline size_t operator()(const IVIRadio::Types::Types::DeviceType& deviceType) const {
            return static_cast<int32_t>(deviceType);
        }
    };
    template<>
    struct hash<IVIRadio::Types::Types::UpdateType> {
        inline size_t operator()(const IVIRadio::Types::Types::UpdateType& updateType) const {
            return static_cast<int32_t>(updateType);
        }
    };
}

#endif // IVIRADIO_TYPES_Types_H_
