/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef TUNERTYPES_Tuner_Types_H_
#define TUNERTYPES_Tuner_Types_H_

#include <CommonAPI/ByteBuffer.h>
#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/types.h>
#include <cstdint>
#include <string>
#include <vector>

namespace TunerTypes {

namespace TunerTypes {
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
    
    enum class Activation: int32_t {
        ACTIVE,
        INACTIVE
    };
    
    // XXX Definition of a comparator still is necessary for GCC 4.4.1, topic is fixed since 4.5.1
    struct ActivationComparator;
    
    typedef CommonAPI::ByteBuffer Bitmap;
    
    typedef std::vector<bool> Booleans;
    
    typedef std::string DateTime;
    
    typedef std::vector<std::string> Strings;
    
    typedef std::vector<uint32_t> UInt32s;
    

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



static inline const char* getTypeCollectionName() {
    return "TunerTypes.TunerTypes";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(1, 0);
}

} // namespace TunerTypes

} // namespace TunerTypes

namespace CommonAPI {
	
	template<>
	struct BasicTypeWriter<TunerTypes::TunerTypes::Feedback> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerTypes::TunerTypes::Feedback> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerTypes::TunerTypes::Feedback>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerTypes::TunerTypes::Feedback> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerTypes::TunerTypes::Feedback>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	template<>
	struct BasicTypeWriter<TunerTypes::TunerTypes::Activation> {
	    inline static void writeType (CommonAPI::TypeOutputStream& typeStream) {
	        typeStream.writeInt32EnumType();
	    }
	};
	
	template<>
	struct InputStreamVectorHelper<TunerTypes::TunerTypes::Activation> {
	    static void beginReadVector(InputStream& inputStream, const std::vector<TunerTypes::TunerTypes::Activation>& vectorValue) {
	        inputStream.beginReadInt32EnumVector();
	    }
	};
	
	template <>
	struct OutputStreamVectorHelper<TunerTypes::TunerTypes::Activation> {
	    static void beginWriteVector(OutputStream& outputStream, const std::vector<TunerTypes::TunerTypes::Activation>& vectorValue) {
	        outputStream.beginWriteInt32EnumVector(vectorValue.size());
	    }
	};
	
}


namespace std {
    template<>
    struct hash<TunerTypes::TunerTypes::Feedback> {
        inline size_t operator()(const TunerTypes::TunerTypes::Feedback& feedback) const {
            return static_cast<int32_t>(feedback);
        }
    };
    template<>
    struct hash<TunerTypes::TunerTypes::Activation> {
        inline size_t operator()(const TunerTypes::TunerTypes::Activation& activation) const {
            return static_cast<int32_t>(activation);
        }
    };
}

#endif // TUNERTYPES_Tuner_Types_H_
