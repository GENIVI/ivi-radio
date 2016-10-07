/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERSTATIONTYPES_Tuner_Station_Types_H_
#define TUNERSTATIONTYPES_Tuner_Station_Types_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/types.h>
#include <TunerTypes/TunerTypes.h>
#include <cstdint>
#include <string>
#include <vector>

namespace TunerStationTypes {

namespace TunerStationTypes {
    enum class DeviceType: int32_t {
        UNDEF_DEVICE = 0,
        AMFM = 1,
        DAB = 2,
        SDARS = 3,
        TV = 4
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct DeviceTypeComparator;
    
    enum class FlagsDefAmFm: int32_t {
        AMFM_FLG_TP,
        AMFM_FLG_TA,
        AMFM_FLG_TMC,
        AMFM_FLG_HDDIGAUDIO,
        AMFM_FLG_HDENCRYPTED,
        AMFM_FLG_HDSUBSCRIBED
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct FlagsDefAmFmComparator;
    
    enum class FlagsDefDab: int32_t {
        DAB_FLG_LOCKED,
        DAB_FLG_VALID,
        DAB_FLG_MUTED,
        DAB_FLG_ENS_MUTED,
        DAB_FLG_ALARM,
        DAB_FLG_TRAFFIC,
        DAB_FLG_TRANSPORT,
        DAB_FLG_WARNING,
        DAB_FLG_NEWS,
        DAB_FLG_WEATHER,
        DAB_FLG_EVENT,
        DAB_FLG_SPECIAL_EVENT,
        DAB_FLG_PROGRAMM_INFO,
        DAB_FLG_SPORT,
        DAB_FLG_FINANCES,
        DAB_FLG_EPG,
        DAB_FLG_JLN,
        DAB_FLG_SLS_NPAD,
        DAB_FLG_SLS_XPAD,
        DAB_FLG_TMC,
        DAB_FLG_TPEG,
        DAB_FLG_MPEG2,
        DAB_FLG_AAC,
        DAB_FLG_BWS
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct FlagsDefDabComparator;
    
    enum class FlagsDefUndef: int32_t {
        UNDEF_FLG_MUTED,
        UNDEF_FLG_ALARM,
        UNDEF_FLG_TRAFFIC,
        UNDEF_FLG_TRANSPORT,
        UNDEF_FLG_WARNING,
        UNDEF_FLG_NEWS,
        UNDEF_FLG_WEATHER,
        UNDEF_FLG_EVENT,
        UNDEF_FLG_SPECIAL_EVENT,
        UNDEF_FLG_PROGRAMM_INFO,
        UNDEF_FLG_SPORT,
        UNDEF_FLG_FINANCES,
        UNDEF_FLG_BWS,
        UNDEF_FLG_EPG,
        UNDEF_FLG_JLN,
        UNDEF_FLG_SLS_NPAD,
        UNDEF_FLG_SLS_XPAD,
        UNDEF_FLG_TMC,
        UNDEF_FLG_TPEG,
        UNDEF_FLG_MPEG2,
        UNDEF_FLG_AAC
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct FlagsDefUndefComparator;
    
    enum class GenreIndexAmFm: int32_t {
        AMFM_GEN_PTY
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct GenreIndexAmFmComparator;
    
    enum class GenreIndexDab: int32_t {
        DAB_GEN_STATIC_PTY,
        DAB_GEN_DYNAMIC_PTY
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct GenreIndexDabComparator;
    
    enum class GenreIndexUndef: int32_t {
        UNDEF_GEN_STATIC,
        UNDEF_GEN_DYNAMIC
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct GenreIndexUndefComparator;
    
    enum class IdIndexAmFm: int32_t {
        AMFM_ID_KEY,
        AMFM_ID_FREQUENCY,
        AMFM_ID_PI,
        AMFM_ID_SERVICE
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct IdIndexAmFmComparator;
    
    enum class IdIndexDab: int32_t {
        DAB_ID_KEY,
        DAB_ID_FREQUENCY,
        DAB_ID_ENSEMBLE,
        DAB_ID_SERVICE,
        DAB_ID_COMPONENT
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct IdIndexDabComparator;
    
    enum class IdIndexUndef: int32_t {
        UNDEF_ID_KEY,
        UNDEF_ID_PARENT
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct IdIndexUndefComparator;
    
    struct Metadata: CommonAPI::SerializableStruct {
        std::string str;
        uint8_t type;
    
        Metadata() = default;
        Metadata(const std::string& str, const uint8_t& type);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeStringType();
            typeOutputStream.writeUInt8Type();
        }
    };
    
    enum class MetaIndexAmFm: int32_t {
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct MetaIndexAmFmComparator;
    
    enum class MetaIndexDab: int32_t {
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct MetaIndexDabComparator;
    
    enum class MetaIndexUndef: int32_t {
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct MetaIndexUndefComparator;
    
    enum class NameIndexAmFm: int32_t {
        AMFM_NAM_PS,
        AMFM_NAM_HD,
        AMFM_NAM_RT
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct NameIndexAmFmComparator;
    
    enum class NameIndexDab: int32_t {
        DAB_NAM_CLONG,
        DAB_NAM_CSHORT,
        DAB_NAM_DYNAMIC,
        DAB_NAM_SLONG,
        DAB_NAM_SSHORT,
        DAB_NAM_ELONG,
        DAB_NAM_ESHORT,
        DAB_NAM_FREQUENCY
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct NameIndexDabComparator;
    
    enum class NameIndexUndef: int32_t {
        UNDEF_NAM_LONG,
        UNDEF_NAM_SHORT,
        UNDEF_NAM_DYNAMIC
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct NameIndexUndefComparator;
    
    enum class QualityIndexAmFm: int32_t {
        AMFM_QAL_FIELDSTRENGTH,
        AMFM_QAL_MULTIPATH,
        AMFM_QAL_DIGITAL
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct QualityIndexAmFmComparator;
    
    enum class QualityIndexDab: int32_t {
        DAB_QAL_BER,
        DAB_QAL_SERVICE,
        DAB_QAL_AUDIO
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct QualityIndexDabComparator;
    
    enum class QualityIndexUndef: int32_t {
        UNDEF_QAL_AUDIO
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct QualityIndexUndefComparator;
    
    enum class SeekMode: int32_t {
        SM_OFF,
        SM_MAN_UP,
        SM_MAN_DOWN,
        SM_AUTO_UP,
        SM_AUTO_DOWN,
        SM_SCAN_UP,
        SM_SCAN_DOWN,
        SM_SCAN_SKIP_UP,
        SM_SCAN_SKIP_DOWN,
        SM_AUTOSTORE
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct SeekModeComparator;
    
    enum class SeekReturnValue: int32_t {
        SM_FREQUENCY,
        SM_PERCENTAGE
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct SeekReturnValueComparator;
    
    struct SeekData: CommonAPI::SerializableStruct {
        uint32_t data;
        SeekMode mode;
        SeekReturnValue returnValue;
    
        SeekData() = default;
        SeekData(const uint32_t& data, const SeekMode& mode, const SeekReturnValue& returnValue);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeInt32Type();
        }
    };
    
    enum class SelectionMode: int32_t {
        SM_UNDEF,
        SM_DIRECT,
        SM_LIST,
        SM_PRESET
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct SelectionModeComparator;
    
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
        SDARS_XM = 0x8000
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct SourceTypeComparator;
    
    struct StationSelector: CommonAPI::SerializableStruct {
        uint32_t deviceType;
        TunerTypes::TunerTypes::UInt32s id;
    
        StationSelector() = default;
        StationSelector(const uint32_t& deviceType, const TunerTypes::TunerTypes::UInt32s& id);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    typedef std::vector<Metadata> Metadatas;
    
    struct Station: CommonAPI::SerializableStruct {
        TunerTypes::TunerTypes::UInt32s flags;
        TunerTypes::TunerTypes::UInt32s genre;
        Metadatas meta;
        TunerTypes::TunerTypes::Strings name;
        TunerTypes::TunerTypes::UInt32s quality;
        StationSelector sel;
        uint32_t stationType;
    
        Station() = default;
        Station(const TunerTypes::TunerTypes::UInt32s& flags, const TunerTypes::TunerTypes::UInt32s& genre, const Metadatas& meta, const TunerTypes::TunerTypes::Strings& name, const TunerTypes::TunerTypes::UInt32s& quality, const StationSelector& sel, const uint32_t& stationType);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeStringType();typeOutputStream.writeUInt8Type();
            typeOutputStream.endWriteStructType();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeStringType();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeUInt32Type();typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.endWriteStructType();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    typedef std::vector<Station> Stations;
    
    struct StationList: CommonAPI::SerializableStruct {
        uint32_t deviceType;
        Stations stations;
        uint32_t stationType;
    
        StationList() = default;
        StationList(const uint32_t& deviceType, const Stations& stations, const uint32_t& stationType);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();typeOutputStream.beginWriteVectorType();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeStringType();typeOutputStream.writeUInt8Type();
            typeOutputStream.endWriteStructType();
            typeOutputStream.endWriteVectorType();typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeStringType();
            typeOutputStream.endWriteVectorType();typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();typeOutputStream.beginWriteStructType();
            typeOutputStream.writeUInt32Type();typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.endWriteStructType();typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteStructType();
            typeOutputStream.endWriteVectorType();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    enum class StationType: int32_t {
        ST_UNDEF = 0x0,
        ST_RECEIVABLE = 0x1,
        ST_PERMANENT = 0x2,
        ST_AUTOSTORED = 0x4,
        ST_ENSEMBLE = 0x8,
        ST_SERVICE = 0x10,
        ST_PRIMARY = 0x20,
        ST_SECONDARY = 0x40,
        ST_CHANGED = 0x8000
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct StationTypeComparator;
    
    enum class UpdateElement: int32_t {
        UE_SEEK,
        UE_CURRENT_STATION,
        UE_STATION_LIST
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct UpdateElementComparator;
    
    enum class UpdateType: int32_t {
        UT_NONE,
        UT_ONCE,
        UT_NOTIFICATION
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct UpdateTypeComparator;
    

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

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, FlagsDefAmFm& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const FlagsDefAmFm& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct FlagsDefAmFmComparator {
    inline bool operator()(const FlagsDefAmFm& lhs, const FlagsDefAmFm& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, FlagsDefDab& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const FlagsDefDab& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct FlagsDefDabComparator {
    inline bool operator()(const FlagsDefDab& lhs, const FlagsDefDab& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, FlagsDefUndef& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const FlagsDefUndef& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct FlagsDefUndefComparator {
    inline bool operator()(const FlagsDefUndef& lhs, const FlagsDefUndef& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, GenreIndexAmFm& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const GenreIndexAmFm& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct GenreIndexAmFmComparator {
    inline bool operator()(const GenreIndexAmFm& lhs, const GenreIndexAmFm& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, GenreIndexDab& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const GenreIndexDab& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct GenreIndexDabComparator {
    inline bool operator()(const GenreIndexDab& lhs, const GenreIndexDab& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, GenreIndexUndef& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const GenreIndexUndef& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct GenreIndexUndefComparator {
    inline bool operator()(const GenreIndexUndef& lhs, const GenreIndexUndef& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, IdIndexAmFm& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const IdIndexAmFm& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct IdIndexAmFmComparator {
    inline bool operator()(const IdIndexAmFm& lhs, const IdIndexAmFm& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, IdIndexDab& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const IdIndexDab& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct IdIndexDabComparator {
    inline bool operator()(const IdIndexDab& lhs, const IdIndexDab& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, IdIndexUndef& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const IdIndexUndef& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct IdIndexUndefComparator {
    inline bool operator()(const IdIndexUndef& lhs, const IdIndexUndef& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

bool operator==(const Metadata& lhs, const Metadata& rhs);
inline bool operator!=(const Metadata& lhs, const Metadata& rhs) {
    return !(lhs == rhs);
}
inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, MetaIndexAmFm& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const MetaIndexAmFm& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct MetaIndexAmFmComparator {
    inline bool operator()(const MetaIndexAmFm& lhs, const MetaIndexAmFm& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, MetaIndexDab& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const MetaIndexDab& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct MetaIndexDabComparator {
    inline bool operator()(const MetaIndexDab& lhs, const MetaIndexDab& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, MetaIndexUndef& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const MetaIndexUndef& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct MetaIndexUndefComparator {
    inline bool operator()(const MetaIndexUndef& lhs, const MetaIndexUndef& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, NameIndexAmFm& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const NameIndexAmFm& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct NameIndexAmFmComparator {
    inline bool operator()(const NameIndexAmFm& lhs, const NameIndexAmFm& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, NameIndexDab& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const NameIndexDab& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct NameIndexDabComparator {
    inline bool operator()(const NameIndexDab& lhs, const NameIndexDab& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, NameIndexUndef& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const NameIndexUndef& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct NameIndexUndefComparator {
    inline bool operator()(const NameIndexUndef& lhs, const NameIndexUndef& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, QualityIndexAmFm& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const QualityIndexAmFm& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct QualityIndexAmFmComparator {
    inline bool operator()(const QualityIndexAmFm& lhs, const QualityIndexAmFm& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, QualityIndexDab& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const QualityIndexDab& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct QualityIndexDabComparator {
    inline bool operator()(const QualityIndexDab& lhs, const QualityIndexDab& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, QualityIndexUndef& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const QualityIndexUndef& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct QualityIndexUndefComparator {
    inline bool operator()(const QualityIndexUndef& lhs, const QualityIndexUndef& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

bool operator==(const SeekData& lhs, const SeekData& rhs);
inline bool operator!=(const SeekData& lhs, const SeekData& rhs) {
    return !(lhs == rhs);
}
inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, SeekMode& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const SeekMode& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct SeekModeComparator {
    inline bool operator()(const SeekMode& lhs, const SeekMode& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, SeekReturnValue& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const SeekReturnValue& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct SeekReturnValueComparator {
    inline bool operator()(const SeekReturnValue& lhs, const SeekReturnValue& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, SelectionMode& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const SelectionMode& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct SelectionModeComparator {
    inline bool operator()(const SelectionMode& lhs, const SelectionMode& rhs) const {
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

bool operator==(const Station& lhs, const Station& rhs);
inline bool operator!=(const Station& lhs, const Station& rhs) {
    return !(lhs == rhs);
}
bool operator==(const StationList& lhs, const StationList& rhs);
inline bool operator!=(const StationList& lhs, const StationList& rhs) {
    return !(lhs == rhs);
}
bool operator==(const StationSelector& lhs, const StationSelector& rhs);
inline bool operator!=(const StationSelector& lhs, const StationSelector& rhs) {
    return !(lhs == rhs);
}
inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, StationType& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const StationType& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct StationTypeComparator {
    inline bool operator()(const StationType& lhs, const StationType& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, UpdateElement& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const UpdateElement& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct UpdateElementComparator {
    inline bool operator()(const UpdateElement& lhs, const UpdateElement& rhs) const {
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
    return "TunerStationTypes.TunerStationTypes";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

} // namespace TunerStationTypes

} // namespace TunerStationTypes

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::DeviceType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::DeviceType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::DeviceType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::DeviceType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::DeviceType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::FlagsDefAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::FlagsDefAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::FlagsDefAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::FlagsDefAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::FlagsDefAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::FlagsDefDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::FlagsDefDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::FlagsDefDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::FlagsDefDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::FlagsDefDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::FlagsDefUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::FlagsDefUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::FlagsDefUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::FlagsDefUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::FlagsDefUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::GenreIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::GenreIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::GenreIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::GenreIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::GenreIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::GenreIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::GenreIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::GenreIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::GenreIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::GenreIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::GenreIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::GenreIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::GenreIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::GenreIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::GenreIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::IdIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::IdIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::IdIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::IdIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::IdIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::IdIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::IdIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::IdIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::IdIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::IdIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::IdIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::IdIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::IdIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::IdIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::IdIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::MetaIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::MetaIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::MetaIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::MetaIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::MetaIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::MetaIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::MetaIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::MetaIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::MetaIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::MetaIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::MetaIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::MetaIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::MetaIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::MetaIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::MetaIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::NameIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::NameIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::NameIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::NameIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::NameIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::NameIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::NameIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::NameIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::NameIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::NameIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::NameIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::NameIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::NameIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::NameIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::NameIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::QualityIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::QualityIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::QualityIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::QualityIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::QualityIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::QualityIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::QualityIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::QualityIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::QualityIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::QualityIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::QualityIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::QualityIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::QualityIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::QualityIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::QualityIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::SeekMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::SeekMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::SeekMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::SeekMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::SeekMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::SeekReturnValue> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::SeekReturnValue> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::SeekReturnValue>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::SeekReturnValue> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::SeekReturnValue>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::SelectionMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::SelectionMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::SelectionMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::SelectionMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::SelectionMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::SourceType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::SourceType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::SourceType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::SourceType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::SourceType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::StationType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::StationType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::StationType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::StationType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::StationType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::UpdateElement> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::UpdateElement> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::UpdateElement>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::UpdateElement> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::UpdateElement>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerStationTypes::TunerStationTypes::UpdateType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerStationTypes::TunerStationTypes::UpdateType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerStationTypes::TunerStationTypes::UpdateType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerStationTypes::TunerStationTypes::UpdateType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerStationTypes::TunerStationTypes::UpdateType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::DeviceType> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::DeviceType& deviceType) const {
            return static_cast<int32_t>(deviceType);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::FlagsDefAmFm> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::FlagsDefAmFm& flagsDefAmFm) const {
            return static_cast<int32_t>(flagsDefAmFm);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::FlagsDefDab> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::FlagsDefDab& flagsDefDab) const {
            return static_cast<int32_t>(flagsDefDab);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::FlagsDefUndef> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::FlagsDefUndef& flagsDefUndef) const {
            return static_cast<int32_t>(flagsDefUndef);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::GenreIndexAmFm> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::GenreIndexAmFm& genreIndexAmFm) const {
            return static_cast<int32_t>(genreIndexAmFm);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::GenreIndexDab> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::GenreIndexDab& genreIndexDab) const {
            return static_cast<int32_t>(genreIndexDab);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::GenreIndexUndef> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::GenreIndexUndef& genreIndexUndef) const {
            return static_cast<int32_t>(genreIndexUndef);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::IdIndexAmFm> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::IdIndexAmFm& idIndexAmFm) const {
            return static_cast<int32_t>(idIndexAmFm);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::IdIndexDab> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::IdIndexDab& idIndexDab) const {
            return static_cast<int32_t>(idIndexDab);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::IdIndexUndef> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::IdIndexUndef& idIndexUndef) const {
            return static_cast<int32_t>(idIndexUndef);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::MetaIndexAmFm> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::MetaIndexAmFm& metaIndexAmFm) const {
            return static_cast<int32_t>(metaIndexAmFm);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::MetaIndexDab> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::MetaIndexDab& metaIndexDab) const {
            return static_cast<int32_t>(metaIndexDab);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::MetaIndexUndef> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::MetaIndexUndef& metaIndexUndef) const {
            return static_cast<int32_t>(metaIndexUndef);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::NameIndexAmFm> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::NameIndexAmFm& nameIndexAmFm) const {
            return static_cast<int32_t>(nameIndexAmFm);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::NameIndexDab> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::NameIndexDab& nameIndexDab) const {
            return static_cast<int32_t>(nameIndexDab);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::NameIndexUndef> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::NameIndexUndef& nameIndexUndef) const {
            return static_cast<int32_t>(nameIndexUndef);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::QualityIndexAmFm> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::QualityIndexAmFm& qualityIndexAmFm) const {
            return static_cast<int32_t>(qualityIndexAmFm);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::QualityIndexDab> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::QualityIndexDab& qualityIndexDab) const {
            return static_cast<int32_t>(qualityIndexDab);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::QualityIndexUndef> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::QualityIndexUndef& qualityIndexUndef) const {
            return static_cast<int32_t>(qualityIndexUndef);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::SeekMode> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::SeekMode& seekMode) const {
            return static_cast<int32_t>(seekMode);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::SeekReturnValue> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::SeekReturnValue& seekReturnValue) const {
            return static_cast<int32_t>(seekReturnValue);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::SelectionMode> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::SelectionMode& selectionMode) const {
            return static_cast<int32_t>(selectionMode);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::SourceType> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::SourceType& sourceType) const {
            return static_cast<int32_t>(sourceType);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::StationType> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::StationType& stationType) const {
            return static_cast<int32_t>(stationType);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::UpdateElement> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::UpdateElement& updateElement) const {
            return static_cast<int32_t>(updateElement);
        }
    };
    template<>
    struct hash<TunerStationTypes::TunerStationTypes::UpdateType> {
        inline size_t operator()(const TunerStationTypes::TunerStationTypes::UpdateType& updateType) const {
            return static_cast<int32_t>(updateType);
        }
    };
}

#endif // TUNERSTATIONTYPES_Tuner_Station_Types_H_
