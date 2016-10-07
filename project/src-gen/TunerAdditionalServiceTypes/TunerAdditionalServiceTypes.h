/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERADDITIONALSERVICETYPES_Tuner_Additional_Service_Types_H_
#define TUNERADDITIONALSERVICETYPES_Tuner_Additional_Service_Types_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/SerializableVariant.h>
#include <CommonAPI/types.h>
#include <TunerStationTypes/TunerStationTypes.h>
#include <TunerTypes/TunerTypes.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace TunerAdditionalServiceTypes {

namespace TunerAdditionalServiceTypes {
    enum class AnnouncementType: int32_t {
        AT_Alarm,
        AT_RoadTraffic,
        AT_TransportFlash,
        AT_WarningService,
        AT_News,
        AT_AreaWeather,
        AT_Event,
        AT_SpecialEvent,
        AT_ProgramInformation,
        AT_SportReport,
        AT_FinancialReport
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct AnnouncementTypeComparator;
    
    struct AnnouncementTypeConfiguration: CommonAPI::SerializableStruct {
        AnnouncementType type;
        TunerTypes::TunerTypes::Activation active;
        uint32_t priority;
    
        AnnouncementTypeConfiguration() = default;
        AnnouncementTypeConfiguration(const AnnouncementType& type, const TunerTypes::TunerTypes::Activation& active, const uint32_t& priority);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    typedef std::vector<AnnouncementTypeConfiguration> AnnouncementTypeConfigurations;
    
    enum class ComponentType: int32_t {
        CT_NO_COMPONENT_TYPE,
        CT_EPG,
        CT_TELETEXT,
        CT_TMC,
        CT_BWS,
        CT_SUBTITLE,
        CT_SLIDESHOW,
        CT_JOURNALINE,
        CT_TPEG,
        CT_ANNOUNCEMENT
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct ComponentTypeComparator;
    
    struct Announcement_TypeOptions: CommonAPI::SerializableStruct {
        TunerTypes::TunerTypes::Activation active;
        AnnouncementTypeConfigurations typeConfiguration;
    
        Announcement_TypeOptions() = default;
        Announcement_TypeOptions(const TunerTypes::TunerTypes::Activation& active, const AnnouncementTypeConfigurations& typeConfiguration);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeInt32Type();typeOutputStream.writeInt32Type();typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteStructType();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct BWS_TypeOptions: CommonAPI::SerializableStruct {
    
        BWS_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Journaline_TypeOptions: CommonAPI::SerializableStruct {
    
        Journaline_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct NoComponent_TypeOptions: CommonAPI::SerializableStruct {
    
        NoComponent_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Slideshow_TypeOptions: CommonAPI::SerializableStruct {
    
        Slideshow_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Subtitle_TypeOptions: CommonAPI::SerializableStruct {
    
        Subtitle_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct TMC_TypeOptions: CommonAPI::SerializableStruct {
    
        TMC_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct TPEG_TypeOptions: CommonAPI::SerializableStruct {
    
        TPEG_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Teletext_TypeOptions: CommonAPI::SerializableStruct {
    
        Teletext_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct EPG_TypeOptions: CommonAPI::SerializableStruct {
        TunerTypes::TunerTypes::Activation active;
    
        EPG_TypeOptions() = default;
        EPG_TypeOptions(const TunerTypes::TunerTypes::Activation& active);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    typedef CommonAPI::Variant<Announcement_TypeOptions, EPG_TypeOptions, TPEG_TypeOptions, Teletext_TypeOptions, BWS_TypeOptions, Subtitle_TypeOptions, Journaline_TypeOptions, NoComponent_TypeOptions, Slideshow_TypeOptions, TMC_TypeOptions>  ComponentTypeOptions;
    
    typedef CommonAPI::Variant<>  ComponentOptions;
    
    struct Announcement_Options: CommonAPI::SerializableStruct {
        TunerTypes::TunerTypes::Activation activity;
        AnnouncementTypeConfiguration typeConfiguration;
    
        Announcement_Options() = default;
        Announcement_Options(const TunerTypes::TunerTypes::Activation& activity, const AnnouncementTypeConfiguration& typeConfiguration);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeInt32Type();typeOutputStream.writeInt32Type();typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteStructType();
        }
    };
    
    struct BWS_Options: CommonAPI::SerializableStruct {
    
        BWS_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Journaline_Options: CommonAPI::SerializableStruct {
    
        Journaline_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct NoComponent__Options: CommonAPI::SerializableStruct {
    
        NoComponent__Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Slideshow_Options: CommonAPI::SerializableStruct {
    
        Slideshow_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Subtitle_Options: CommonAPI::SerializableStruct {
    
        Subtitle_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct TMC_Options: CommonAPI::SerializableStruct {
    
        TMC_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct TPEG_Options: CommonAPI::SerializableStruct {
    
        TPEG_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Teletext_Options: CommonAPI::SerializableStruct {
    
        Teletext_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct EPG_Options: CommonAPI::SerializableStruct {
        TunerTypes::TunerTypes::Activation active;
    
        EPG_Options() = default;
        EPG_Options(const TunerTypes::TunerTypes::Activation& active);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct Announcement_Parameter: CommonAPI::SerializableStruct {
        bool abort;
    
        Announcement_Parameter() = default;
        Announcement_Parameter(const bool& abort);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeBoolType();
        }
    };
    
    struct BWS_Parameter: CommonAPI::SerializableStruct {
    
        BWS_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct EPG_Parameter: CommonAPI::SerializableStruct {
        TunerTypes::TunerTypes::DateTime startDate;
        TunerTypes::TunerTypes::DateTime endDate;
        std::string genre;
        TunerStationTypes::TunerStationTypes::StationSelector station;
        uint32_t eventID;
    
        EPG_Parameter() = default;
        EPG_Parameter(const TunerTypes::TunerTypes::DateTime& startDate, const TunerTypes::TunerTypes::DateTime& endDate, const std::string& genre, const TunerStationTypes::TunerStationTypes::StationSelector& station, const uint32_t& eventID);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeStringType();
            typeOutputStream.writeStringType();
            typeOutputStream.writeStringType();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeUInt32Type();typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.endWriteStructType();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    struct Journaline_Parameter: CommonAPI::SerializableStruct {
    
        Journaline_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct NoComponenttype_Parameter: CommonAPI::SerializableStruct {
    
        NoComponenttype_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Slideshow_Parameter: CommonAPI::SerializableStruct {
    
        Slideshow_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Subtitle_Parameter: CommonAPI::SerializableStruct {
    
        Subtitle_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct TMC_Parameter: CommonAPI::SerializableStruct {
    
        TMC_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct TPEG_Parameter: CommonAPI::SerializableStruct {
    
        TPEG_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct TeleText_Parameter: CommonAPI::SerializableStruct {
    
        TeleText_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    typedef CommonAPI::Variant<NoComponenttype_Parameter, Announcement_Parameter, BWS_Parameter, EPG_Parameter, Journaline_Parameter, Slideshow_Parameter, Subtitle_Parameter, TeleText_Parameter, TMC_Parameter, TPEG_Parameter>  SelectParameter;
    
    struct Announcement: CommonAPI::SerializableStruct {
        uint32_t componentID;
        AnnouncementType type;
    
        Announcement() = default;
        Announcement(const uint32_t& componentID, const AnnouncementType& type);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
            typeOutputStream.writeInt32Type();
        }
    };
    

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, ComponentType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const ComponentType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct ComponentTypeComparator {
    inline bool operator()(const ComponentType& lhs, const ComponentType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

bool operator==(const AnnouncementTypeConfiguration& lhs, const AnnouncementTypeConfiguration& rhs);
inline bool operator!=(const AnnouncementTypeConfiguration& lhs, const AnnouncementTypeConfiguration& rhs) {
    return !(lhs == rhs);
}
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

bool operator==(const Announcement_TypeOptions& lhs, const Announcement_TypeOptions& rhs);
inline bool operator!=(const Announcement_TypeOptions& lhs, const Announcement_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Announcement_Options& lhs, const Announcement_Options& rhs);
inline bool operator!=(const Announcement_Options& lhs, const Announcement_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const BWS_TypeOptions& lhs, const BWS_TypeOptions& rhs);
inline bool operator!=(const BWS_TypeOptions& lhs, const BWS_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const BWS_Options& lhs, const BWS_Options& rhs);
inline bool operator!=(const BWS_Options& lhs, const BWS_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Journaline_TypeOptions& lhs, const Journaline_TypeOptions& rhs);
inline bool operator!=(const Journaline_TypeOptions& lhs, const Journaline_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Journaline_Options& lhs, const Journaline_Options& rhs);
inline bool operator!=(const Journaline_Options& lhs, const Journaline_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const NoComponent_TypeOptions& lhs, const NoComponent_TypeOptions& rhs);
inline bool operator!=(const NoComponent_TypeOptions& lhs, const NoComponent_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const NoComponent__Options& lhs, const NoComponent__Options& rhs);
inline bool operator!=(const NoComponent__Options& lhs, const NoComponent__Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Slideshow_TypeOptions& lhs, const Slideshow_TypeOptions& rhs);
inline bool operator!=(const Slideshow_TypeOptions& lhs, const Slideshow_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Slideshow_Options& lhs, const Slideshow_Options& rhs);
inline bool operator!=(const Slideshow_Options& lhs, const Slideshow_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Subtitle_TypeOptions& lhs, const Subtitle_TypeOptions& rhs);
inline bool operator!=(const Subtitle_TypeOptions& lhs, const Subtitle_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Subtitle_Options& lhs, const Subtitle_Options& rhs);
inline bool operator!=(const Subtitle_Options& lhs, const Subtitle_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TMC_TypeOptions& lhs, const TMC_TypeOptions& rhs);
inline bool operator!=(const TMC_TypeOptions& lhs, const TMC_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TMC_Options& lhs, const TMC_Options& rhs);
inline bool operator!=(const TMC_Options& lhs, const TMC_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TPEG_TypeOptions& lhs, const TPEG_TypeOptions& rhs);
inline bool operator!=(const TPEG_TypeOptions& lhs, const TPEG_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Teletext_TypeOptions& lhs, const Teletext_TypeOptions& rhs);
inline bool operator!=(const Teletext_TypeOptions& lhs, const Teletext_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TPEG_Options& lhs, const TPEG_Options& rhs);
inline bool operator!=(const TPEG_Options& lhs, const TPEG_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const EPG_TypeOptions& lhs, const EPG_TypeOptions& rhs);
inline bool operator!=(const EPG_TypeOptions& lhs, const EPG_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Teletext_Options& lhs, const Teletext_Options& rhs);
inline bool operator!=(const Teletext_Options& lhs, const Teletext_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const EPG_Options& lhs, const EPG_Options& rhs);
inline bool operator!=(const EPG_Options& lhs, const EPG_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Announcement_Parameter& lhs, const Announcement_Parameter& rhs);
inline bool operator!=(const Announcement_Parameter& lhs, const Announcement_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const BWS_Parameter& lhs, const BWS_Parameter& rhs);
inline bool operator!=(const BWS_Parameter& lhs, const BWS_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const EPG_Parameter& lhs, const EPG_Parameter& rhs);
inline bool operator!=(const EPG_Parameter& lhs, const EPG_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Journaline_Parameter& lhs, const Journaline_Parameter& rhs);
inline bool operator!=(const Journaline_Parameter& lhs, const Journaline_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const NoComponenttype_Parameter& lhs, const NoComponenttype_Parameter& rhs);
inline bool operator!=(const NoComponenttype_Parameter& lhs, const NoComponenttype_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Slideshow_Parameter& lhs, const Slideshow_Parameter& rhs);
inline bool operator!=(const Slideshow_Parameter& lhs, const Slideshow_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Subtitle_Parameter& lhs, const Subtitle_Parameter& rhs);
inline bool operator!=(const Subtitle_Parameter& lhs, const Subtitle_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TMC_Parameter& lhs, const TMC_Parameter& rhs);
inline bool operator!=(const TMC_Parameter& lhs, const TMC_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TPEG_Parameter& lhs, const TPEG_Parameter& rhs);
inline bool operator!=(const TPEG_Parameter& lhs, const TPEG_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const TeleText_Parameter& lhs, const TeleText_Parameter& rhs);
inline bool operator!=(const TeleText_Parameter& lhs, const TeleText_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Announcement& lhs, const Announcement& rhs);
inline bool operator!=(const Announcement& lhs, const Announcement& rhs) {
    return !(lhs == rhs);
}


static inline const char* getTypeCollectionName() {
    return "TunerAdditionalServiceTypes.TunerAdditionalServiceTypes";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

} // namespace TunerAdditionalServiceTypes

} // namespace TunerAdditionalServiceTypes

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType> {
        inline size_t operator()(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::ComponentType& componentType) const {
            return static_cast<int32_t>(componentType);
        }
    };
    template<>
    struct hash<TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType> {
        inline size_t operator()(const TunerAdditionalServiceTypes::TunerAdditionalServiceTypes::AnnouncementType& announcementType) const {
            return static_cast<int32_t>(announcementType);
        }
    };
}

#endif // TUNERADDITIONALSERVICETYPES_Tuner_Additional_Service_Types_H_
