/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_Types_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_Types_H_

#include <CommonAPI/ByteBuffer.h>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/SerializableVariant.h>
#include <CommonAPI/types.h>
#include <IVIRadio/Types/Types.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace IVIRadio {
namespace AdditionalService {

namespace AdditionalServiceTypes {
    enum class AnnouncementState: int32_t {
        NotAvailable,
        Available,
        Active
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct AnnouncementStateComparator;
    
    typedef std::vector<AnnouncementState> AnnouncementStates;
    
    typedef std::vector<AnnouncementStates> arrayAnnouncementStates;
    
    typedef CommonAPI::Variant<std::string, CommonAPI::ByteBuffer>  Data;
    
    enum class DataFormat: int32_t {
        DF_XML,
        DF_HTML,
        DF_PICTURE,
        DF_RAW
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct DataFormatComparator;
    
    enum class DataType: int32_t {
        DT_STRING,
        DT_STREAM,
        DT_BYTEBUFFER
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct DataTypeComparator;
    
    enum class EWSAffectedArea: int32_t {
        EAA_UNKNOWN,
        EAA_NATIONALWIDE,
        EAA_WIDEAREA,
        EAA_REGION,
        EAA_LOCAL,
        EAA_POINT
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct EWSAffectedAreaComparator;
    
    enum class EWSType: int32_t {
        ET_UNKNOWN,
        ET_EMERGENCY_WARNING,
        ET_EARTHQUAKE_WARNING,
        ET_TIDAL_WAVE_WARNING,
        ET_WEATHER_WARNING,
        ET_ROAD_TRAFFIC,
        ET_PERSONAL_CALL,
        ET_EVENT_ANNOUNCEMENT,
        ET_CAS_SERVICE_MESSAGE,
        ET_TEST_SIGNAL
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct EWSTypeComparator;
    
    enum class ImageService: int32_t {
        IS_CATEGORIZED_SLIDESHOW,
        IS_SLIDESHOW,
        IS_ALBUM_COVER,
        IS_STATION_LOGO
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct ImageServiceComparator;
    
    enum class ImageType: int32_t {
        IT_BOOKLET_FRONT,
        IT_BOOKLET_BACK,
        IT_INTERPRET
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct ImageTypeComparator;
    
    struct Language: CommonAPI::SerializableStruct {
        std::string Name;
    
        Language() = default;
        Language(const std::string& Name);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeStringType();
        }
    };
    
    typedef std::vector<Language> Languages;
    
    enum class DataService: int32_t {
        DS_NO_SERVICE,
        DS_SUBTITLE,
        DS_TELETEXT,
        DS_EPG,
        DS_IMAGE,
        DS_TMC,
        DS_TPEG,
        DS_JOURNALINE,
        DS_ANNOUNCEMENT,
        DS_EWS
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct DataServiceComparator;
    
    enum class AnnouncementType: int32_t {
        AT_ALARM,
        AT_ROAD_TRAFFIC,
        AT_TRANSPORT_FLASH,
        AT_WARNING_SERVICE,
        AT_NEWS,
        AT_AREA_WEATHER,
        AT_EVENT,
        AT_SEPECIAL_EVENT,
        AT_PROGRAM_INFORMATION,
        AT_SPORT_REPORT,
        AT_FINANCIAL_REPORT
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct AnnouncementTypeComparator;
    
    struct Announcement: CommonAPI::SerializableStruct {
        Types::Types::StationSelector stationSelector;
        AnnouncementType type;
    
        Announcement() = default;
        Announcement(const Types::Types::StationSelector& stationSelector, const AnnouncementType& type);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeUInt32Type();typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.endWriteStructType();
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct AnnouncementConfiguration: CommonAPI::SerializableStruct {
        AnnouncementType type;
        Types::Types::Activation active;
        uint32_t priority;
    
        AnnouncementConfiguration() = default;
        AnnouncementConfiguration(const AnnouncementType& type, const Types::Types::Activation& active, const uint32_t& priority);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    typedef std::vector<AnnouncementConfiguration> AnnouncementConfigurations;
    

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, AnnouncementState& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const AnnouncementState& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct AnnouncementStateComparator {
    inline bool operator()(const AnnouncementState& lhs, const AnnouncementState& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, DataFormat& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const DataFormat& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct DataFormatComparator {
    inline bool operator()(const DataFormat& lhs, const DataFormat& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, DataType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const DataType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct DataTypeComparator {
    inline bool operator()(const DataType& lhs, const DataType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, EWSAffectedArea& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const EWSAffectedArea& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct EWSAffectedAreaComparator {
    inline bool operator()(const EWSAffectedArea& lhs, const EWSAffectedArea& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, EWSType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const EWSType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct EWSTypeComparator {
    inline bool operator()(const EWSType& lhs, const EWSType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, ImageService& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const ImageService& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct ImageServiceComparator {
    inline bool operator()(const ImageService& lhs, const ImageService& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, ImageType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const ImageType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct ImageTypeComparator {
    inline bool operator()(const ImageType& lhs, const ImageType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

bool operator==(const Language& lhs, const Language& rhs);
inline bool operator!=(const Language& lhs, const Language& rhs) {
    return !(lhs == rhs);
}
inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, DataService& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const DataService& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct DataServiceComparator {
    inline bool operator()(const DataService& lhs, const DataService& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, AnnouncementType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const AnnouncementType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct AnnouncementTypeComparator {
    inline bool operator()(const AnnouncementType& lhs, const AnnouncementType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

bool operator==(const Announcement& lhs, const Announcement& rhs);
inline bool operator!=(const Announcement& lhs, const Announcement& rhs) {
    return !(lhs == rhs);
}
bool operator==(const AnnouncementConfiguration& lhs, const AnnouncementConfiguration& rhs);
inline bool operator!=(const AnnouncementConfiguration& lhs, const AnnouncementConfiguration& rhs) {
    return !(lhs == rhs);
}


static inline const char* getTypeCollectionName() {
    return "IVIRadio.AdditionalService.AdditionalServiceTypes";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(2, 0);
}

} // namespace AdditionalServiceTypes

} // namespace AdditionalService
} // namespace IVIRadio

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::DataType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::DataType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::DataType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::DataType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::DataType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSAffectedArea> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSAffectedArea> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSAffectedArea>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSAffectedArea> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSAffectedArea>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageService> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageService> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageService>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageService> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageService>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::DataService> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::DataService> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::DataService>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::DataService> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::DataService>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState& announcementState) const {
            return static_cast<int32_t>(announcementState);
        }
    };
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::DataFormat& dataFormat) const {
            return static_cast<int32_t>(dataFormat);
        }
    };
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::DataType> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::DataType& dataType) const {
            return static_cast<int32_t>(dataType);
        }
    };
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSAffectedArea> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::EWSAffectedArea& eWSAffectedArea) const {
            return static_cast<int32_t>(eWSAffectedArea);
        }
    };
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::EWSType> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::EWSType& eWSType) const {
            return static_cast<int32_t>(eWSType);
        }
    };
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageService> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::ImageService& imageService) const {
            return static_cast<int32_t>(imageService);
        }
    };
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::ImageType> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::ImageType& imageType) const {
            return static_cast<int32_t>(imageType);
        }
    };
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::DataService> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::DataService& dataService) const {
            return static_cast<int32_t>(dataService);
        }
    };
    template<>
    struct hash<IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType> {
        inline size_t operator()(const IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType& announcementType) const {
            return static_cast<int32_t>(announcementType);
        }
    };
}

#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_Types_H_
