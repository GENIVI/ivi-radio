/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERADDITIONALSERVICETYPES_MGEG_Tuner_Additional_Service_Types_H_
#define MGEGTUNERADDITIONALSERVICETYPES_MGEG_Tuner_Additional_Service_Types_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/SerializableVariant.h>
#include <CommonAPI/types.h>
#include <MGEGTunerStationTypes/MGEGTunerStationTypes.h>
#include <MGEGTunerTypes/MGEGTunerTypes.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace MGEGTunerAdditionalServiceTypes {

namespace MGEGTunerAdditionalServiceTypes {
    enum class MGEG_AnnouncementType: int32_t {
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
    struct MGEG_AnnouncementTypeComparator;
    
    struct MGEG_AnnouncementTypeConfiguration: CommonAPI::SerializableStruct {
        MGEG_AnnouncementType type;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation active;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 priority;
    
        MGEG_AnnouncementTypeConfiguration() = default;
        MGEG_AnnouncementTypeConfiguration(const MGEG_AnnouncementType& type, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& active, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& priority);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    typedef std::vector<MGEG_AnnouncementTypeConfiguration> MGEG_AnnouncementTypeConfigurations;
    
    enum class MGEG_ComponentType: int32_t {
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
    struct MGEG_ComponentTypeComparator;
    
    struct MGEG_Announcement_TypeOptions: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation active;
        MGEG_AnnouncementTypeConfigurations typeConfiguration;
    
        MGEG_Announcement_TypeOptions() = default;
        MGEG_Announcement_TypeOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& active, const MGEG_AnnouncementTypeConfigurations& typeConfiguration);
    
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
    
    struct MGEG_BWS_TypeOptions: CommonAPI::SerializableStruct {
    
        MGEG_BWS_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Journaline_TypeOptions: CommonAPI::SerializableStruct {
    
        MGEG_Journaline_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_NoComponent_TypeOptions: CommonAPI::SerializableStruct {
    
        MGEG_NoComponent_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Slideshow_TypeOptions: CommonAPI::SerializableStruct {
    
        MGEG_Slideshow_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Subtitle_TypeOptions: CommonAPI::SerializableStruct {
    
        MGEG_Subtitle_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_TMC_TypeOptions: CommonAPI::SerializableStruct {
    
        MGEG_TMC_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_TPEG_TypeOptions: CommonAPI::SerializableStruct {
    
        MGEG_TPEG_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Teletext_TypeOptions: CommonAPI::SerializableStruct {
    
        MGEG_Teletext_TypeOptions() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_EPG_TypeOptions: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation active;
    
        MGEG_EPG_TypeOptions() = default;
        MGEG_EPG_TypeOptions(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& active);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    typedef CommonAPI::Variant<MGEG_Announcement_TypeOptions, MGEG_EPG_TypeOptions, MGEG_TPEG_TypeOptions, MGEG_Teletext_TypeOptions, MGEG_BWS_TypeOptions, MGEG_Subtitle_TypeOptions, MGEG_Journaline_TypeOptions, MGEG_NoComponent_TypeOptions, MGEG_Slideshow_TypeOptions, MGEG_TMC_TypeOptions>  MGEG_ComponentTypeOptions;
    
    typedef CommonAPI::Variant<>  MGEG_ComponentOptions;
    
    struct MGEG_Announcement_Options: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation activity;
        MGEG_AnnouncementTypeConfiguration typeConfiguration;
    
        MGEG_Announcement_Options() = default;
        MGEG_Announcement_Options(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& activity, const MGEG_AnnouncementTypeConfiguration& typeConfiguration);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeInt32Type();typeOutputStream.writeInt32Type();typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteStructType();
        }
    };
    
    struct MGEG_BWS_Options: CommonAPI::SerializableStruct {
    
        MGEG_BWS_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Journaline_Options: CommonAPI::SerializableStruct {
    
        MGEG_Journaline_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_NoComponent__Options: CommonAPI::SerializableStruct {
    
        MGEG_NoComponent__Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Slideshow_Options: CommonAPI::SerializableStruct {
    
        MGEG_Slideshow_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Subtitle_Options: CommonAPI::SerializableStruct {
    
        MGEG_Subtitle_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_TMC_Options: CommonAPI::SerializableStruct {
    
        MGEG_TMC_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_TPEG_Options: CommonAPI::SerializableStruct {
    
        MGEG_TPEG_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Teletext_Options: CommonAPI::SerializableStruct {
    
        MGEG_Teletext_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_EPG_Options: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation active;
    
        MGEG_EPG_Options() = default;
        MGEG_EPG_Options(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& active);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct MGEG_Announcement_Parameter: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean abort;
    
        MGEG_Announcement_Parameter() = default;
        MGEG_Announcement_Parameter(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Boolean& abort);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeBoolType();
        }
    };
    
    struct MGEG_BWS_Parameter: CommonAPI::SerializableStruct {
    
        MGEG_BWS_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_EPG_Parameter: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_DateTime startDate;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_DateTime endDate;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_String genre;
        MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector station;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 eventID;
    
        MGEG_EPG_Parameter() = default;
        MGEG_EPG_Parameter(const MGEGTunerTypes::MGEGTunerTypes::MGEG_DateTime& startDate, const MGEGTunerTypes::MGEGTunerTypes::MGEG_DateTime& endDate, const MGEGTunerTypes::MGEGTunerTypes::MGEG_String& genre, const MGEGTunerStationTypes::MGEGTunerStationTypes::StationSelector& station, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& eventID);
    
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
    
    struct MGEG_Journaline_Parameter: CommonAPI::SerializableStruct {
    
        MGEG_Journaline_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_NoComponenttype_Parameter: CommonAPI::SerializableStruct {
    
        MGEG_NoComponenttype_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Slideshow_Parameter: CommonAPI::SerializableStruct {
    
        MGEG_Slideshow_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_Subtitle_Parameter: CommonAPI::SerializableStruct {
    
        MGEG_Subtitle_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_TMC_Parameter: CommonAPI::SerializableStruct {
    
        MGEG_TMC_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_TPEG_Parameter: CommonAPI::SerializableStruct {
    
        MGEG_TPEG_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct MGEG_TeleText_Parameter: CommonAPI::SerializableStruct {
    
        MGEG_TeleText_Parameter() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    typedef CommonAPI::Variant<MGEG_NoComponenttype_Parameter, MGEG_Announcement_Parameter, MGEG_BWS_Parameter, MGEG_EPG_Parameter, MGEG_Journaline_Parameter, MGEG_Slideshow_Parameter, MGEG_Subtitle_Parameter, MGEG_TeleText_Parameter, MGEG_TMC_Parameter, MGEG_TPEG_Parameter>  MGEG_SelectParameter;
    
    struct MGEG_Announcement: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 componentID;
        MGEG_AnnouncementType type;
    
        MGEG_Announcement() = default;
        MGEG_Announcement(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& componentID, const MGEG_AnnouncementType& type);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
            typeOutputStream.writeInt32Type();
        }
    };
    

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, MGEG_ComponentType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const MGEG_ComponentType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct MGEG_ComponentTypeComparator {
    inline bool operator()(const MGEG_ComponentType& lhs, const MGEG_ComponentType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

bool operator==(const MGEG_AnnouncementTypeConfiguration& lhs, const MGEG_AnnouncementTypeConfiguration& rhs);
inline bool operator!=(const MGEG_AnnouncementTypeConfiguration& lhs, const MGEG_AnnouncementTypeConfiguration& rhs) {
    return !(lhs == rhs);
}
inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, MGEG_AnnouncementType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const MGEG_AnnouncementType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct MGEG_AnnouncementTypeComparator {
    inline bool operator()(const MGEG_AnnouncementType& lhs, const MGEG_AnnouncementType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

bool operator==(const MGEG_Announcement_TypeOptions& lhs, const MGEG_Announcement_TypeOptions& rhs);
inline bool operator!=(const MGEG_Announcement_TypeOptions& lhs, const MGEG_Announcement_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Announcement_Options& lhs, const MGEG_Announcement_Options& rhs);
inline bool operator!=(const MGEG_Announcement_Options& lhs, const MGEG_Announcement_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_BWS_TypeOptions& lhs, const MGEG_BWS_TypeOptions& rhs);
inline bool operator!=(const MGEG_BWS_TypeOptions& lhs, const MGEG_BWS_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_BWS_Options& lhs, const MGEG_BWS_Options& rhs);
inline bool operator!=(const MGEG_BWS_Options& lhs, const MGEG_BWS_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Journaline_TypeOptions& lhs, const MGEG_Journaline_TypeOptions& rhs);
inline bool operator!=(const MGEG_Journaline_TypeOptions& lhs, const MGEG_Journaline_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Journaline_Options& lhs, const MGEG_Journaline_Options& rhs);
inline bool operator!=(const MGEG_Journaline_Options& lhs, const MGEG_Journaline_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_NoComponent_TypeOptions& lhs, const MGEG_NoComponent_TypeOptions& rhs);
inline bool operator!=(const MGEG_NoComponent_TypeOptions& lhs, const MGEG_NoComponent_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_NoComponent__Options& lhs, const MGEG_NoComponent__Options& rhs);
inline bool operator!=(const MGEG_NoComponent__Options& lhs, const MGEG_NoComponent__Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Slideshow_TypeOptions& lhs, const MGEG_Slideshow_TypeOptions& rhs);
inline bool operator!=(const MGEG_Slideshow_TypeOptions& lhs, const MGEG_Slideshow_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Slideshow_Options& lhs, const MGEG_Slideshow_Options& rhs);
inline bool operator!=(const MGEG_Slideshow_Options& lhs, const MGEG_Slideshow_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Subtitle_TypeOptions& lhs, const MGEG_Subtitle_TypeOptions& rhs);
inline bool operator!=(const MGEG_Subtitle_TypeOptions& lhs, const MGEG_Subtitle_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Subtitle_Options& lhs, const MGEG_Subtitle_Options& rhs);
inline bool operator!=(const MGEG_Subtitle_Options& lhs, const MGEG_Subtitle_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_TMC_TypeOptions& lhs, const MGEG_TMC_TypeOptions& rhs);
inline bool operator!=(const MGEG_TMC_TypeOptions& lhs, const MGEG_TMC_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_TMC_Options& lhs, const MGEG_TMC_Options& rhs);
inline bool operator!=(const MGEG_TMC_Options& lhs, const MGEG_TMC_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_TPEG_TypeOptions& lhs, const MGEG_TPEG_TypeOptions& rhs);
inline bool operator!=(const MGEG_TPEG_TypeOptions& lhs, const MGEG_TPEG_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Teletext_TypeOptions& lhs, const MGEG_Teletext_TypeOptions& rhs);
inline bool operator!=(const MGEG_Teletext_TypeOptions& lhs, const MGEG_Teletext_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_TPEG_Options& lhs, const MGEG_TPEG_Options& rhs);
inline bool operator!=(const MGEG_TPEG_Options& lhs, const MGEG_TPEG_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_EPG_TypeOptions& lhs, const MGEG_EPG_TypeOptions& rhs);
inline bool operator!=(const MGEG_EPG_TypeOptions& lhs, const MGEG_EPG_TypeOptions& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Teletext_Options& lhs, const MGEG_Teletext_Options& rhs);
inline bool operator!=(const MGEG_Teletext_Options& lhs, const MGEG_Teletext_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_EPG_Options& lhs, const MGEG_EPG_Options& rhs);
inline bool operator!=(const MGEG_EPG_Options& lhs, const MGEG_EPG_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Announcement_Parameter& lhs, const MGEG_Announcement_Parameter& rhs);
inline bool operator!=(const MGEG_Announcement_Parameter& lhs, const MGEG_Announcement_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_BWS_Parameter& lhs, const MGEG_BWS_Parameter& rhs);
inline bool operator!=(const MGEG_BWS_Parameter& lhs, const MGEG_BWS_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_EPG_Parameter& lhs, const MGEG_EPG_Parameter& rhs);
inline bool operator!=(const MGEG_EPG_Parameter& lhs, const MGEG_EPG_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Journaline_Parameter& lhs, const MGEG_Journaline_Parameter& rhs);
inline bool operator!=(const MGEG_Journaline_Parameter& lhs, const MGEG_Journaline_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_NoComponenttype_Parameter& lhs, const MGEG_NoComponenttype_Parameter& rhs);
inline bool operator!=(const MGEG_NoComponenttype_Parameter& lhs, const MGEG_NoComponenttype_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Slideshow_Parameter& lhs, const MGEG_Slideshow_Parameter& rhs);
inline bool operator!=(const MGEG_Slideshow_Parameter& lhs, const MGEG_Slideshow_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Subtitle_Parameter& lhs, const MGEG_Subtitle_Parameter& rhs);
inline bool operator!=(const MGEG_Subtitle_Parameter& lhs, const MGEG_Subtitle_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_TMC_Parameter& lhs, const MGEG_TMC_Parameter& rhs);
inline bool operator!=(const MGEG_TMC_Parameter& lhs, const MGEG_TMC_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_TPEG_Parameter& lhs, const MGEG_TPEG_Parameter& rhs);
inline bool operator!=(const MGEG_TPEG_Parameter& lhs, const MGEG_TPEG_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_TeleText_Parameter& lhs, const MGEG_TeleText_Parameter& rhs);
inline bool operator!=(const MGEG_TeleText_Parameter& lhs, const MGEG_TeleText_Parameter& rhs) {
    return !(lhs == rhs);
}
bool operator==(const MGEG_Announcement& lhs, const MGEG_Announcement& rhs);
inline bool operator!=(const MGEG_Announcement& lhs, const MGEG_Announcement& rhs) {
    return !(lhs == rhs);
}


static inline const char* getTypeCollectionName() {
    return "MGEGTunerAdditionalServiceTypes.MGEGTunerAdditionalServiceTypes";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

} // namespace MGEGTunerAdditionalServiceTypes

} // namespace MGEGTunerAdditionalServiceTypes

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_AnnouncementType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_AnnouncementType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_AnnouncementType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_AnnouncementType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_AnnouncementType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType> {
        inline size_t operator()(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_ComponentType& mGEG_ComponentType) const {
            return static_cast<int32_t>(mGEG_ComponentType);
        }
    };
    template<>
    struct hash<MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_AnnouncementType> {
        inline size_t operator()(const MGEGTunerAdditionalServiceTypes::MGEGTunerAdditionalServiceTypes::MGEG_AnnouncementType& mGEG_AnnouncementType) const {
            return static_cast<int32_t>(mGEG_AnnouncementType);
        }
    };
}

#endif // MGEGTUNERADDITIONALSERVICETYPES_MGEG_Tuner_Additional_Service_Types_H_
