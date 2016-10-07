/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_STATION_Station_Types_H_
#define IVIRADIO_STATION_Station_Types_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/types.h>
#include <IVIRadio/Types/Types.h>
#include <cstdint>
#include <string>
#include <vector>

namespace IVIRadio {
namespace Station {

namespace StationTypes {
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
    
    typedef std::vector<Metadata> Metadatas;
    
    struct Station: CommonAPI::SerializableStruct {
        uint32_t flags;
        Types::Types::UInt32s genre;
        Metadatas meta;
        Types::Types::Strings name;
        Types::Types::UInt32s quality;
        Types::Types::StationSelector sel;
        uint32_t stationType;
    
        Station() = default;
        Station(const uint32_t& flags, const Types::Types::UInt32s& genre, const Metadatas& meta, const Types::Types::Strings& name, const Types::Types::UInt32s& quality, const Types::Types::StationSelector& sel, const uint32_t& stationType);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeUInt32Type();
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
            typeOutputStream.writeUInt32Type();typeOutputStream.beginWriteVectorType();
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
    
    enum class SelectionMode: int32_t {
        SM_UNDEF,
        SM_DIRECT,
        SM_LIST,
        SM_PRESET
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct SelectionModeComparator;
    
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
    
    enum class FlagsDefAmFm: int32_t {
        AMFM_FLG_TP = 0x1,
        AMFM_FLG_ANN_TA = 0x2,
        AMFM_FLG_MS = 0x4,
        AMFM_FLG_TMC = 0x8,
        AMFM_FLG_HDDIGAUDIO = 0x10,
        AMFM_FLG_HDENCRYPTED = 0x20,
        AMFM_FLG_HDBALLGAME = 0x40,
        AMFM_FLG_IMG_STATIONLOGO = 0x80
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct FlagsDefAmFmComparator;
    
    enum class FlagsDefDab: int32_t {
        DAB_FLG_LOCKED = 0x1,
        DAB_FLG_VALID = 0x2,
        DAB_FLG_MUTED = 0x4,
        DAB_FLG_ENS_MUTED = 0x8,
        DAB_FLG_ANN_ALARM = 0x10,
        DAB_FLG_ANN_TRAFFIC = 0x20,
        DAB_FLG_ANN_TRANSPORT = 0x40,
        DAB_FLG_ANN_WARNING = 0x80,
        DAB_FLG_ANN_NEWS = 0x100,
        DAB_FLG_ANN_WEATHER = 0x200,
        DAB_FLG_ANN_EVENT = 0x400,
        DAB_FLG_ANN_SPECIAL_EVENT = 0x800,
        DAB_FLG_ANN_PROGRAMM_INFO = 0x1000,
        DAB_FLG_ANN_SPORT = 0x2000,
        DAB_FLG_ANN_FINANCES = 0x4000,
        DAB_FLG_EPG = 0x8000,
        DAB_FLG_JLN = 0x10000,
        DAB_FLG_IMG_SLS_NPAD = 0x20000,
        DAB_FLG_IMG_SLS_XPAD = 0x40000,
        DAB_FLG_TMC = 0x80000,
        DAB_FLG_TPEG = 0x100000,
        DAB_FLG_BWS = 0x200000,
        DAB_FLG_MPEG2 = 0x400000,
        DAB_FLG_AAC = 0x800000,
        DAB_FLG_IMG_CSLS = 0x1000000,
        DAB_FLG_IMG_ALBUMCOVER = 0x2000000,
        DAB_FLG_IMG_STATIONLOGO = 0x4000000
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct FlagsDefDabComparator;
    
    enum class FlagsDefUndef: int32_t {
        UNDEF_FLG_MUTED = 0x1,
        UNDEF_FLG_ANN_ALARM = 0x2,
        UNDEF_FLG_ANN_TRAFFIC = 0x4,
        UNDEF_FLG_ANN_TRANSPORT = 0x8,
        UNDEF_FLG_ANN_WARNING = 0x10,
        UNDEF_FLG_ANN_NEWS = 0x20,
        UNDEF_FLG_ANN_WEATHER = 0x40,
        UNDEF_FLG_ANN_EVENT = 0x80,
        UNDEF_FLG_ANN_SPECIAL_EVENT = 0x100,
        UNDEF_FLG_ANN_PROGRAMM_INFO = 0x200,
        UNDEF_FLG_ANN_SPORT = 0x400,
        UNDEF_FLG_ANN_FINANCES = 0x800,
        UNDEF_FLG_EPG = 0x1000,
        UNDEF_FLG_JLN = 0x2000,
        UNDEF_FLG_IMG_SLS_NPAD = 0x4000,
        UNDEF_FLG_IMG_SLS_XPAD = 0x8000,
        UNDEF_FLG_TMC = 0x10000,
        UNDEF_FLG_TPEG = 0x20000,
        UNDEF_FLG_BWS = 0x40000,
        UNDEF_FLG_MPEG2 = 0x80000,
        UNDEF_FLG_AAC = 0x100000,
        UNDEF_FLG_IMG_CSLS = 0x200000,
        UNDEF_FLG_IMG_ALBUMCOVER = 0x400000,
        UNDEF_FLG_IMG_STATIONLOGO = 0x800000,
        UNDEF_FLG_SUBTITLE = 0x1000000,
        UNDEF_FLG_TELETEXT = 0x2000000
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
    

bool operator==(const Metadata& lhs, const Metadata& rhs);
inline bool operator!=(const Metadata& lhs, const Metadata& rhs) {
    return !(lhs == rhs);
}
bool operator==(const SeekData& lhs, const SeekData& rhs);
inline bool operator!=(const SeekData& lhs, const SeekData& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Station& lhs, const Station& rhs);
inline bool operator!=(const Station& lhs, const Station& rhs) {
    return !(lhs == rhs);
}
bool operator==(const StationList& lhs, const StationList& rhs);
inline bool operator!=(const StationList& lhs, const StationList& rhs) {
    return !(lhs == rhs);
}
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



static inline const char* getTypeCollectionName() {
    return "IVIRadio.Station.StationTypes";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(2, 0);
}

} // namespace StationTypes

} // namespace Station
} // namespace IVIRadio

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::SelectionMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::SelectionMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::SelectionMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::SelectionMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::SelectionMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::SeekMode> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::SeekMode> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::SeekMode>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::SeekMode> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::SeekMode>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::SeekReturnValue> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::SeekReturnValue> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::SeekReturnValue>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::SeekReturnValue> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::SeekReturnValue>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::StationType> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::StationType> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::StationType>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::StationType> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::StationType>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::UpdateElement> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::UpdateElement> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::UpdateElement>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::UpdateElement> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::UpdateElement>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::FlagsDefAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::FlagsDefAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::FlagsDefAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::FlagsDefAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::FlagsDefAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::FlagsDefDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::FlagsDefDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::FlagsDefDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::FlagsDefDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::FlagsDefDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::FlagsDefUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::FlagsDefUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::FlagsDefUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::FlagsDefUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::FlagsDefUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::GenreIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::GenreIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::GenreIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::GenreIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::GenreIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::GenreIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::GenreIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::GenreIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::GenreIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::GenreIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::GenreIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::GenreIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::GenreIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::GenreIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::GenreIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::IdIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::IdIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::IdIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::IdIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::IdIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::IdIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::IdIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::IdIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::IdIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::IdIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::IdIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::IdIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::IdIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::IdIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::IdIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::MetaIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::MetaIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::MetaIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::MetaIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::MetaIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::MetaIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::MetaIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::MetaIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::MetaIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::MetaIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::MetaIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::MetaIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::MetaIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::MetaIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::MetaIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::NameIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::NameIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::NameIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::NameIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::NameIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::NameIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::NameIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::NameIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::NameIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::NameIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::NameIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::NameIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::NameIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::NameIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::NameIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::QualityIndexAmFm> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::QualityIndexAmFm> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::QualityIndexAmFm>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::QualityIndexAmFm> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::QualityIndexAmFm>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::QualityIndexDab> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::QualityIndexDab> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::QualityIndexDab>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::QualityIndexDab> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::QualityIndexDab>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<IVIRadio::Station::StationTypes::QualityIndexUndef> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<IVIRadio::Station::StationTypes::QualityIndexUndef> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<IVIRadio::Station::StationTypes::QualityIndexUndef>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<IVIRadio::Station::StationTypes::QualityIndexUndef> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<IVIRadio::Station::StationTypes::QualityIndexUndef>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<IVIRadio::Station::StationTypes::SelectionMode> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::SelectionMode& selectionMode) const {
            return static_cast<int32_t>(selectionMode);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::SeekMode> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::SeekMode& seekMode) const {
            return static_cast<int32_t>(seekMode);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::SeekReturnValue> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::SeekReturnValue& seekReturnValue) const {
            return static_cast<int32_t>(seekReturnValue);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::StationType> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::StationType& stationType) const {
            return static_cast<int32_t>(stationType);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::UpdateElement> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::UpdateElement& updateElement) const {
            return static_cast<int32_t>(updateElement);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::FlagsDefAmFm> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::FlagsDefAmFm& flagsDefAmFm) const {
            return static_cast<int32_t>(flagsDefAmFm);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::FlagsDefDab> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::FlagsDefDab& flagsDefDab) const {
            return static_cast<int32_t>(flagsDefDab);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::FlagsDefUndef> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::FlagsDefUndef& flagsDefUndef) const {
            return static_cast<int32_t>(flagsDefUndef);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::GenreIndexAmFm> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::GenreIndexAmFm& genreIndexAmFm) const {
            return static_cast<int32_t>(genreIndexAmFm);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::GenreIndexDab> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::GenreIndexDab& genreIndexDab) const {
            return static_cast<int32_t>(genreIndexDab);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::GenreIndexUndef> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::GenreIndexUndef& genreIndexUndef) const {
            return static_cast<int32_t>(genreIndexUndef);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::IdIndexAmFm> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::IdIndexAmFm& idIndexAmFm) const {
            return static_cast<int32_t>(idIndexAmFm);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::IdIndexDab> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::IdIndexDab& idIndexDab) const {
            return static_cast<int32_t>(idIndexDab);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::IdIndexUndef> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::IdIndexUndef& idIndexUndef) const {
            return static_cast<int32_t>(idIndexUndef);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::MetaIndexAmFm> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::MetaIndexAmFm& metaIndexAmFm) const {
            return static_cast<int32_t>(metaIndexAmFm);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::MetaIndexDab> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::MetaIndexDab& metaIndexDab) const {
            return static_cast<int32_t>(metaIndexDab);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::MetaIndexUndef> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::MetaIndexUndef& metaIndexUndef) const {
            return static_cast<int32_t>(metaIndexUndef);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::NameIndexAmFm> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::NameIndexAmFm& nameIndexAmFm) const {
            return static_cast<int32_t>(nameIndexAmFm);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::NameIndexDab> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::NameIndexDab& nameIndexDab) const {
            return static_cast<int32_t>(nameIndexDab);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::NameIndexUndef> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::NameIndexUndef& nameIndexUndef) const {
            return static_cast<int32_t>(nameIndexUndef);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::QualityIndexAmFm> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::QualityIndexAmFm& qualityIndexAmFm) const {
            return static_cast<int32_t>(qualityIndexAmFm);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::QualityIndexDab> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::QualityIndexDab& qualityIndexDab) const {
            return static_cast<int32_t>(qualityIndexDab);
        }
    };
    template<>
    struct hash<IVIRadio::Station::StationTypes::QualityIndexUndef> {
        inline size_t operator()(const IVIRadio::Station::StationTypes::QualityIndexUndef& qualityIndexUndef) const {
            return static_cast<int32_t>(qualityIndexUndef);
        }
    };
}

#endif // IVIRADIO_STATION_Station_Types_H_
