/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef IVIRADIO_ADDITIONALSERVICE_Additional_Service_Types_Options_H_
#define IVIRADIO_ADDITIONALSERVICE_Additional_Service_Types_Options_H_

#include <CommonAPI/InputStream.h>
#include <CommonAPI/OutputStream.h>
#include <CommonAPI/SerializableStruct.h>
#include <CommonAPI/SerializableVariant.h>
#include <CommonAPI/types.h>
#include <IVIRadio/AdditionalService/AdditionalServiceTypes.h>
#include <IVIRadio/Types/Types.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace IVIRadio {
namespace AdditionalService {

namespace AdditionalServiceTypesOptions {
    struct UnifiedServiceOption: CommonAPI::SerializableStruct {
        Types::Types::UpdateType requestType;
        uint32_t objectID;
    
        UnifiedServiceOption() = default;
        UnifiedServiceOption(const Types::Types::UpdateType& requestType, const uint32_t& objectID);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    typedef std::vector<UnifiedServiceOption> UnifiedServiceOptions;
    
    struct Image_Options: CommonAPI::SerializableStruct {
        AdditionalServiceTypes::ImageType imageType;
        AdditionalServiceTypes::ImageService imageService;
        uint32_t width;
        uint32_t heigth;
    
        Image_Options() = default;
        Image_Options(const AdditionalServiceTypes::ImageType& imageType, const AdditionalServiceTypes::ImageService& imageService, const uint32_t& width, const uint32_t& heigth);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeUInt32Type();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    struct No_Options: CommonAPI::SerializableStruct {
    
        No_Options() = default;
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
        }
    };
    
    struct Journaline_Options: CommonAPI::SerializableStruct {
        bool Entry_Object;
    
        Journaline_Options() = default;
        Journaline_Options(const bool& Entry_Object);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeBoolType();
        }
    };
    
    struct Subtitle_Options: CommonAPI::SerializableStruct {
        AdditionalServiceTypes::Languages Languages;
    
        Subtitle_Options() = default;
        Subtitle_Options(const AdditionalServiceTypes::Languages& Languages);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeStringType();
            typeOutputStream.endWriteStructType();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    struct Teletext_Options: CommonAPI::SerializableStruct {
        bool Entry_Page;
        uint32_t Sub_Page;
    
        Teletext_Options() = default;
        Teletext_Options(const bool& Entry_Page, const uint32_t& Sub_Page);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeBoolType();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    struct EWS_Options: CommonAPI::SerializableStruct {
        AdditionalServiceTypes::EWSType Type;
        AdditionalServiceTypes::EWSAffectedArea Affected_Area;
    
        EWS_Options() = default;
        EWS_Options(const AdditionalServiceTypes::EWSType& Type, const AdditionalServiceTypes::EWSAffectedArea& Affected_Area);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeInt32Type();
            typeOutputStream.writeInt32Type();
        }
    };
    
    struct EPG_Options: CommonAPI::SerializableStruct {
        Types::Types::DateTime Start_Date_Time;
        Types::Types::DateTime End_Date_Time;
        std::string Genre;
        uint32_t Count_Events;
    
        EPG_Options() = default;
        EPG_Options(const Types::Types::DateTime& Start_Date_Time, const Types::Types::DateTime& End_Date_Time, const std::string& Genre, const uint32_t& Count_Events);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.writeStringType();
            typeOutputStream.writeStringType();
            typeOutputStream.writeStringType();
            typeOutputStream.writeUInt32Type();
        }
    };
    
    struct Announcement_Options: CommonAPI::SerializableStruct {
        AdditionalServiceTypes::AnnouncementConfigurations Type_Configurations;
    
        Announcement_Options() = default;
        Announcement_Options(const AdditionalServiceTypes::AnnouncementConfigurations& Type_Configurations);
    
        virtual void readFromInputStream(CommonAPI::InputStream& inputStream);
        virtual void writeToOutputStream(CommonAPI::OutputStream& outputStream) const;
    
        static inline void writeToTypeOutputStream(CommonAPI::TypeOutputStream& typeOutputStream) {
            typeOutputStream.beginWriteVectorType();
            typeOutputStream.beginWriteStructType();
            typeOutputStream.writeInt32Type();typeOutputStream.writeInt32Type();typeOutputStream.writeUInt32Type();
            typeOutputStream.endWriteStructType();
            typeOutputStream.endWriteVectorType();
        }
    };
    
    typedef CommonAPI::Variant<No_Options, Subtitle_Options, Teletext_Options, EPG_Options, Journaline_Options, Announcement_Options, EWS_Options, Image_Options>  DataServiceOption;
    
    typedef std::vector<DataServiceOption> DataServiceOptions;
    

bool operator==(const UnifiedServiceOption& lhs, const UnifiedServiceOption& rhs);
inline bool operator!=(const UnifiedServiceOption& lhs, const UnifiedServiceOption& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Image_Options& lhs, const Image_Options& rhs);
inline bool operator!=(const Image_Options& lhs, const Image_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const No_Options& lhs, const No_Options& rhs);
inline bool operator!=(const No_Options& lhs, const No_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Journaline_Options& lhs, const Journaline_Options& rhs);
inline bool operator!=(const Journaline_Options& lhs, const Journaline_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Subtitle_Options& lhs, const Subtitle_Options& rhs);
inline bool operator!=(const Subtitle_Options& lhs, const Subtitle_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Teletext_Options& lhs, const Teletext_Options& rhs);
inline bool operator!=(const Teletext_Options& lhs, const Teletext_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const EWS_Options& lhs, const EWS_Options& rhs);
inline bool operator!=(const EWS_Options& lhs, const EWS_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const EPG_Options& lhs, const EPG_Options& rhs);
inline bool operator!=(const EPG_Options& lhs, const EPG_Options& rhs) {
    return !(lhs == rhs);
}
bool operator==(const Announcement_Options& lhs, const Announcement_Options& rhs);
inline bool operator!=(const Announcement_Options& lhs, const Announcement_Options& rhs) {
    return !(lhs == rhs);
}


static inline const char* getTypeCollectionName() {
    return "IVIRadio.AdditionalService.AdditionalServiceTypesOptions";
}

inline CommonAPI::Version getTypeCollectionVersion() {
    return CommonAPI::Version(2, 0);
}

} // namespace AdditionalServiceTypesOptions

} // namespace AdditionalService
} // namespace IVIRadio

namespace CommonAPI {
	
	
}


namespace std {
}

#endif // IVIRADIO_ADDITIONALSERVICE_Additional_Service_Types_Options_H_
