/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERSTATIONTYPES_MGEG_Tuner_Station_Types_H_
#define MGEGTUNERSTATIONTYPES_MGEG_Tuner_Station_Types_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/types.h>
#include <MGEGTunerTypes/MGEGTunerTypes.h>
#include <cstdint>
#include <vector>

namespace MGEGTunerStationTypes {

namespace MGEGTunerStationTypes {
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
        MGEGTunerTypes::MGEGTunerTypes::MGEG_String str;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8 type;
    
        Metadata() = default;
        Metadata(const MGEGTunerTypes::MGEGTunerTypes::MGEG_String& str, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt8& type);
    
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
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 data;
        SeekMode mode;
        SeekReturnValue returnValue;
    
        SeekData() = default;
        SeekData(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& data, const SeekMode& mode, const SeekReturnValue& returnValue);
    
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
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 deviceType;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s id;
    
        StationSelector() = default;
        StationSelector(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& deviceType, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& id);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    typedef std::vector<Metadata> MGEG_Metadatas;
    
    struct Station: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s flags;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s genre;
        MGEG_Metadatas meta;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_Strings name;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s quality;
        StationSelector sel;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 stationType;
    
        Station() = default;
        Station(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& flags, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& genre, const MGEG_Metadatas& meta, const MGEGTunerTypes::MGEGTunerTypes::MGEG_Strings& name, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32s& quality, const StationSelector& sel, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType);
    
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
    
    typedef std::vector<Station> MGEG_Stations;
    
    struct StationList: CommonAPI::SerializableStruct {
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 deviceType;
        MGEG_Stations stations;
        MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32 stationType;
    
        StationList() = default;
        StationList(const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& deviceType, const MGEG_Stations& stations, const MGEGTunerTypes::MGEGTunerTypes::MGEG_UInt32& stationType);
    
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
    return "MGEGTunerStationTypes.MGEGTunerStationTypes";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

} // namespace MGEGTunerStationTypes

} // namespace MGEGTunerStationTypes

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekReturnValue> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekReturnValue> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekReturnValue>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekReturnValue> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekReturnValue>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::SourceType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::SourceType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::SourceType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::SourceType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::SourceType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::StationType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::StationType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::StationType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::StationType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::StationType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::DeviceType& deviceType) const {
            return static_cast<int32_t>(deviceType);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefAmFm> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefAmFm& flagsDefAmFm) const {
            return static_cast<int32_t>(flagsDefAmFm);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefDab> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefDab& flagsDefDab) const {
            return static_cast<int32_t>(flagsDefDab);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefUndef> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::FlagsDefUndef& flagsDefUndef) const {
            return static_cast<int32_t>(flagsDefUndef);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexAmFm> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexAmFm& genreIndexAmFm) const {
            return static_cast<int32_t>(genreIndexAmFm);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexDab> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexDab& genreIndexDab) const {
            return static_cast<int32_t>(genreIndexDab);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexUndef> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::GenreIndexUndef& genreIndexUndef) const {
            return static_cast<int32_t>(genreIndexUndef);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexAmFm> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexAmFm& idIndexAmFm) const {
            return static_cast<int32_t>(idIndexAmFm);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexDab> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexDab& idIndexDab) const {
            return static_cast<int32_t>(idIndexDab);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexUndef> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::IdIndexUndef& idIndexUndef) const {
            return static_cast<int32_t>(idIndexUndef);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexAmFm> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexAmFm& metaIndexAmFm) const {
            return static_cast<int32_t>(metaIndexAmFm);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexDab> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexDab& metaIndexDab) const {
            return static_cast<int32_t>(metaIndexDab);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexUndef> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::MetaIndexUndef& metaIndexUndef) const {
            return static_cast<int32_t>(metaIndexUndef);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexAmFm> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexAmFm& nameIndexAmFm) const {
            return static_cast<int32_t>(nameIndexAmFm);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexDab> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexDab& nameIndexDab) const {
            return static_cast<int32_t>(nameIndexDab);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexUndef> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::NameIndexUndef& nameIndexUndef) const {
            return static_cast<int32_t>(nameIndexUndef);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexAmFm> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexAmFm& qualityIndexAmFm) const {
            return static_cast<int32_t>(qualityIndexAmFm);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexDab> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexDab& qualityIndexDab) const {
            return static_cast<int32_t>(qualityIndexDab);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexUndef> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::QualityIndexUndef& qualityIndexUndef) const {
            return static_cast<int32_t>(qualityIndexUndef);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekMode& seekMode) const {
            return static_cast<int32_t>(seekMode);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::SeekReturnValue> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::SeekReturnValue& seekReturnValue) const {
            return static_cast<int32_t>(seekReturnValue);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::SelectionMode& selectionMode) const {
            return static_cast<int32_t>(selectionMode);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::SourceType> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::SourceType& sourceType) const {
            return static_cast<int32_t>(sourceType);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::StationType> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::StationType& stationType) const {
            return static_cast<int32_t>(stationType);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateElement& updateElement) const {
            return static_cast<int32_t>(updateElement);
        }
    };
    template<>
    struct hash<MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType> {
        inline size_t operator()(const MGEGTunerStationTypes::MGEGTunerStationTypes::UpdateType& updateType) const {
            return static_cast<int32_t>(updateType);
        }
    };
}

#endif // MGEGTUNERSTATIONTYPES_MGEG_Tuner_Station_Types_H_
