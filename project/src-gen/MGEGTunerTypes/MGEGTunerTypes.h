/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef MGEGTUNERTYPES_MGEG_Tuner_Types_H_
#define MGEGTUNERTYPES_MGEG_Tuner_Types_H_

#include <CommonAPI/ByteBuffer.h>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/types.h>
#include <cstdint>
#include <string>
#include <vector>

namespace MGEGTunerTypes {

namespace MGEGTunerTypes {
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
    
    enum class MGEG_Activation: int32_t {
        ACTIVE,
        INACTIVE
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct MGEG_ActivationComparator;
    
    typedef CommonAPI::ByteBuffer MGEG_Bitmap;
    
    typedef bool MGEG_Boolean;
    
    typedef std::vector<MGEG_Boolean> MGEG_Booleans;
    
    typedef std::string MGEG_DateTime;
    
    typedef std::string MGEG_String;
    
    typedef std::vector<MGEG_String> MGEG_Strings;
    
    typedef uint32_t MGEG_UInt32;
    
    typedef std::vector<MGEG_UInt32> MGEG_UInt32s;
    
    typedef uint8_t MGEG_UInt8;
    

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

inline CommonAPI::InputStream& operator>>(CommonAPI::InputStream& inputStream, MGEG_Activation& enumValue) {
    return inputStream.readEnumValue<int32_t>(enumValue);
}

inline CommonAPI::OutputStream& operator<<(CommonAPI::OutputStream& outputStream, const MGEG_Activation& enumValue) {
    return outputStream.writeEnumValue(static_cast<int32_t>(enumValue));
}

struct MGEG_ActivationComparator {
    inline bool operator()(const MGEG_Activation& lhs, const MGEG_Activation& rhs) const {
        return static_cast<int32_t>(lhs) < static_cast<int32_t>(rhs);
    }
};



static inline const char* getTypeCollectionName() {
    return "MGEGTunerTypes.MGEGTunerTypes";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

} // namespace MGEGTunerTypes

} // namespace MGEGTunerTypes

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<MGEGTunerTypes::MGEGTunerTypes::Feedback> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerTypes::MGEGTunerTypes::Feedback> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerTypes::MGEGTunerTypes::Feedback>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerTypes::MGEGTunerTypes::Feedback> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerTypes::MGEGTunerTypes::Feedback>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<MGEGTunerTypes::MGEGTunerTypes::Feedback> {
        inline size_t operator()(const MGEGTunerTypes::MGEGTunerTypes::Feedback& feedback) const {
            return static_cast<int32_t>(feedback);
        }
    };
    template<>
    struct hash<MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation> {
        inline size_t operator()(const MGEGTunerTypes::MGEGTunerTypes::MGEG_Activation& mGEG_Activation) const {
            return static_cast<int32_t>(mGEG_Activation);
        }
    };
}

#endif // MGEGTUNERTYPES_MGEG_Tuner_Types_H_
