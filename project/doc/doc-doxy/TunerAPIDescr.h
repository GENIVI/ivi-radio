/*! \page IntroTunerAPIDescr Description of the IVI Radio API

Description of the Tuner API version 2.0 (GENIVI Compliance 5.0 -> GEMINI and GENIVI Compliance 6.0 -> HORIZON)\n

\n
\image html TunerMiddlewareComponent.jpg "Component Specification Tuner Middleware"
\n



\section sec_Types Types

\subsection ssec_Types «Types» Types

\subsubsection ssec_ArrayStationSelectors «array» arrayStationSelectors

<b>Note:</b>\n
array of Station Selector

\subsubsection ssec_DeviceType «enumeration» DeviceType

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|UInt32|UNDEF_DEVICE|No information available|
|UInt32|AMFM|AMFM device|
|UInt32|DAB|DAB device|
|UInt32|SDARS|SDARS device|
|UInt32|TV|TV device|
<b>Note:</b>\n
Tuner device type (one for each device which has its own DevCtrl)

\subsubsection ssec_Activation «enumeration» Activation

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||ACTIVE|type active|
||INACTIVE|type inactive|
<b>Note:</b>\n
enumeration for activation type

\subsubsection ssec_Feedback «enumeration» Feedback

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||DONE|Request was successful|
||INTERRUPTED|Request was interrupted by another request|
||NOT_APPLICABLE|Request not supported|
||ALREADY_SET|Request had no effect (not used consequently)|
||FAILURE|Request was not successful because of invalid parameters|
||DELAYED|but result will be delayed (e.g. device currently blocked)|
<b>Note:</b>\n
Client information about the result of a request; delivered with response method.

\subsubsection ssec_ErrorCodes «enumeration» ErrorCodes

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||EC_NOTACTIVATED | |
||EC_NOTRECEIVABLE| |
||EC_OUTOFRESSOURCES| |
||EC_NOERROR| |
||EC_NOSTATIONACTIVE| |
||EC_INVALIDCOMPONENTID| |
||EC_NODATAAVAILABLE| |
||EC_NOTACTIVE| |
||EC_COMPONENTNOTSUPPORTED| |
||EC_FUNCTIONALITYNOTSUPPORTED| |
<b>Note:</b>\n
Contains different Errorcodes that can be transmitted in the broadcasts to give a feedback if an error occurs.

\subsubsection ssec_StationSelector «struct» StationSelector

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceType "DeviceType"|deviceType|device the station is transmitted on|
|UInt32s|id|The ID vector (indices are device and project dependent, refer to specific hbtd file)|
<b>Note:</b>\n
Parameters in order to identify a frequency/station uniquely.

\subsubsection ssec_UpdateType «enumeration» UpdateType

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
| |UT_NONE|No more updates for this handle|
| |UT_ONCE|Trigger one update|
| |UT_NOTIFICATION|Keep me up to date and send notifications|
<b>Note:</b>\n
Update types

\subsubsection ssec_SourceType «struct» SourceType

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|String|UNDEF_SOURCE|No information available|
|String|AMFM_FM|FM frequency|
|String|AMFM_MW|MW frequency|
|String|AMFM_LW|LW frequency|
|String|AMFM_SW|SW fequency|
|String|AMFM_WB|WB frequency|
|String|AMFM_TF|TF frequency|
|String|AMFM_HD|HD station|
|String|AMFM_DRM|DRM station|
|String|DAB_L|L band frequency|
|String|DAB_III|Band III frequency|
|String|DAB_DAB|DAB service|
|String|DAB_DAB_PLUS|DAB+ service|
|String|DAB_DMBA|DMB audio service|
|String|DAB_DMBV|DMB video service|
|String|SDARS_SIRIUS|SIRIUS station|
|String|SDARS_XM|XM station|
<b>Note:</b>\n
Tuner Source type of frequency/station.

\subsubsection ssec_DateTime «typedef» DateTime
<b>Note:</b>\n
API unsigned date and time bit type.

\subsubsection ssec_Activations «array» Activations
<b>Note:</b>\n
array of activation types.

\subsubsection ssec_DeviceTypes «array» DeviceTypes
<b>Note:</b>\n
array of \ref ssec_DeviceType "Device Types".

\subsubsection ssec_StationSelectors «array» StationSelectors
<b>Note:</b>\n
array of \ref ssec_StationSelector "Station Selector".

\subsubsection ssec_SourceTypes «array» SourceTypes
<b>Note:</b>\n
array of \ref ssec_SourceType "Source Types".

\subsubsection ssec_Booleans «array» Booleans
<b>Note:</b>\n
array of Booleans.\n

\subsubsection ssec_String «array» Strings
<b>Note:</b>\n
array of Strings.\n

\subsubsection ssec_UInt32s «array» UInt32s
<b>Note:</b>\n
array of UInt32.\n

\section Station

\subsection ssec_StationTypes «Types» Station Types

\subsubsection ssec_FlagsDefAmFm «enumeration» FlagsDefAmFm

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||AMFM_FLG_TP|TP station|
||AMFM_FLG_TA|AM_FLG_TP true: Active TA, AMFM_FLG_TP false: EON|
||AMFM_FLG_TMC|TMC station|
||AMFM_FLG_HDDIGAUDIO|HD digital audio available|
||AMFM_FLG HDENCRYPTED|HD encrypted|
||AMFM_FLG_HDSUBSCRIBED|HD subscribed|
<b>Note:</b>\n
Station.flags definition for AM/FM/HD devices

\subsubsection ssec_FlagsDefDab «enumeration» FlagsDefDab

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||DAB_FLG_LOCKED|Reception: Frequency locked|
||DAB_FLG_VALID|Reception: Valid audio stream|
||DAB_FLG_MUTED|Reception: Service muted|
||DAB_FLG_ENS_MUTED|Reception: Ensemble muted|
||DAB_FLG_ALARM|Announcement: Information about a serious or even life-threatening situation such as: nuclear fallout or war|
||DAB_FLG_TRAFFIC|Announcement: Information about problems on the road|
||DAB_FLG_TRANSPORT|Announcement: Information concerning Public Transport, such as: schedules of buses, derries, plains or trains|
||DAB_FLG_WARNING|Announcement: Information about incidents of less importance than Alarm Announcements, such as: disruption of power or water supplies|
||DAB_FLG_NEWS|Announcement: News bulletin|
||DAB_FLG_WEATHER|Announcement: Weather bulletin|
||DAB_FLG_EVENT|Announcement: Information about commercial, cultural or public events|
||DAB_FLG_SPECIAL_EVENT|Announcement: Information on unscheduled or previously unforeseen events|
||DAB_FLG_PROGRAMM_INFO|Announcement: Information about current or future radio broadcasts or programmes|
||DAB_FLG_SPORT|Announcement: Bulletin of news about sport|
||DAB_FLG_FINANCES|Announcement: Bulletin of news about finance or business|
||DAB_FLG_EPG|Data service: Electronic program guide (EPG)|
||DAB_FLG_JLN|Data service: Journaline|
||DAB_FLG_SLS_NPAD|Data service: Slideshow (NPAD)|
||DAB_FLG_SLS_XPAD|Data service: Slideshow (XPAD)|
||DAB_FLG_TMC|Data service: TMC|
||DAB_FLG_TPEG|Data service: TPEG|
||DAB_FLG_MPEG2|Coding: MPEG2 coding|
||DAB_FLG_AAC|Coding: AAC coding|
<b>Note:</b>\n
Station.flags definition for DAB/DMB devices

\subsubsection ssec_FlagsDefUndef «enumeration» FlagsDefUndef

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||UNDEF_FLG_MUTED|Reception: Audio muted|
||UNDEF_FLG_ALARM|Announcement: Information about a serious or even life-threatening situation such as: nuclear fallout or war|
||UNDEF_FLG_TRAFFIC|Announcement: Information about problems on the road|
||UNDEF_FLG_TRANSPORT|Announcement: Information concerning Public Transport, such as: schedules of buses, derries, plains or trains|
||UNDEF_FLG_WARNING|Announcement: Information about incidents of less importance than Alarm Announcements, such as: disruption of power or water supplies|
||UNDEF_FLG_NEWS|Announcement: News bulletin|
||UNDEF_FLG_WEATHER|Announcement: Weather bulletin|
||UNDEF_FLG_EVENT|Announcement: Information about commercial, cultural or public events|
||UNDEF_FLG_SPECIAL_EVENT|Announcement: Information on unscheduled or previously unforeseen events|
||UNDEF_FLG_PROGRAMM_INFO|Announcement: Information about current or future radio broadcasts or programmes|
||UNDEF_FLG_SPORT|Announcement: Bulletin of news about sport|
||UNDEF_FLG_FINANCES|Announcement: Bulletin of news about finance or business|
||UNDEF_FLG_BWS|Data service: Broadcast websites|
||UNDEF_FLG_EPG|Data service: Electronic program guide (EPG)|
||UNDEF_FLG_JLN|Data service: Journaline|
||UNDEF_FLG_SLS_NPAD|Data service: Slideshow (NPAD)|
||UNDEF_FLG_SLS_XPAD|Data service: Slideshow (XPAD)|
||UNDEF_FLG_TMC|Data service: TMC|
||UNDEF_FLG_TPEG|Data service: TPEG|
||UNDEF_FLG_MPEG2|Coding: MPEG2 coding|
||UNDEF_FLG_AAC|Coding: AAC coding|
<b>Note:</b>\n
Station.flags definition for the "UNDEF" device

\subsubsection ssec_GenreIndexAmFm «enumeration» GenreIndexAmFm

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||AMFM_GEN_PTY|PTY code|
<b>Note:</b>\n
Station.genre vector indices for AM/FM/HD devices

\subsubsection ssec_GenreIndexDab «enumeration» GenreIndexDab

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||DAB_GEN_STATIC_PTY|Static PTY code|
||DAB_GEN_DYNAMIC_PTY|Dynamic PTY code|
<b>Note:</b>\n
Station.genre vector indices for DAB/DMB devices\n

\subsubsection ssec_GenreIndexUndef «enumeration» GenreIndexUndef

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||UNDEF_GEN_STATICStatic genre information|Static genre information|
||UNDEF_GEN_DYNAMIC|Dynamic genre information|
<b>Note:</b>\n
Station.genre vector indices for the "UNDEF" device

\subsubsection ssec_IdIndexAmFm «enumeration»  IdIndexAmFm

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||AMFM_ID_KEY|Unique key|
||AMFM_ID_FREQUENCY|Frequency [kHz]|
||AMFM_ID_PI|Program identifier|
||AMFM_ID_SERVICE|HD service (0: MPS, 1: SPS1, ..)|
<b>Note:</b>\n
StationSelector ID vector indices for AM/FM/HD devices

\subsubsection ssec_IdIndexDab «enumeration»  IdIndexDab

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||DAB_ID_KEY|Unique key|
||DAB_ID_FREQUENCY|Frequency [kHz]|
||DAB_ID_ENSEMBLE|Ensemble identifier|
||DAB_ID_SERVICE|Service identifier|
||DAB_ID_COMPONENT|Component identifier|
<b>Note:</b>\n
StationSelector ID vector indices for DAB/DMB devices

\subsubsection ssec_IdIndexUndef «enumeration»  IdIndexUndef

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||UNDEF_ID_KEY|Unique key|
||UNDEF_ID_PARENT|Optional: Unique key of the parent in case of subservices|
<b>Note:</b>\n
StationSelector ID vector indices for the "UNDEF" device

\subsubsection ssec_MetaIndexAmFm «enumeration»  MetaIndexAmFm

<b>Note:</b>\n
Station.meta vector indices for AM/FM/HD devices\n

\subsubsection ssec_MetaIndexDab «enumeration»  MetaIndexDab

<b>Note:</b>\n
Station.meta vector indices for DAB/DMB devices

\subsubsection ssec_MetaIndexUndef  «enumeration»  MetaIndexUndef

<b>Note:</b>\n
Station.meta vector indices for the "UNDEF" device\n

\subsubsection ssec_Metadata «struct»  Metadata

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|String|str|Type of meta data (device dependent, refer to specific hbtd file)|
|UInt8|type|Type of meta data (device dependent, refer to specific hbtd file)|
<b>Note:</b>\n
Meta data (e.g. RT+ or DL+)\n

\subsubsection ssec_NameIndexAmFm «enumeration»  NameIndexAmFm

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||AMFM_NAM_PS|PS code|
||AMFM_NAM_HD|HD label|
||AMFM_NAM_RT|RadioText|
<b>Note:</b>\n
Station.name vector indices for AM/FM/HD devices

\subsubsection ssec_NameIndexDab «enumeration»  NameIndexDab

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||DAB_NAM_CLONG|Subcomponent label|
||DAB_NAM_CSHORT|Subcomponent abbreviation|
||DAB_NAM_DYNAMIC|Dynamic label|
||DAB_NAM_SLONG|Service label|
||DAB_NAM_SSHORT|Service abbreviation|
||DAB_NAM_ELONG|Ensemble label|
||DAB_NAM_ESHORT|Ensemble abbreviation|
||DAB_NAM_FREQUENCY|Frequency label|
<b>Note:</b>\n
Station.name vector indices for DAB/DMB devices

\subsubsection ssec_NameIndexUndef «enumeration»  NameIndexUndef

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||UNDEF_NAM_LONG|Long name / label|
||UNDEF_NAM_SHORT|Abbreviation|
||UNDEF_NAM_DYNAMIC|Dynamic label / RadioText|
<b>Note:</b>\n
Station.name vector indices for the "UNDEF" device

\subsubsection ssec_QualityIndexAmFm «enumeration»  QualityIndexAmFm

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||AMFM_QAL_FIELDSTRENGTH|Fieldstrength [dbuV]|
||AMFM_QAL_MULTIPATH|Multipath|
||AMFM_QAL_DIGITAL|Digital quality|
<b>Note:</b>\n
Station.quality vector indices for AM/FM/HD devices

\subsubsection ssec_QualityIndexDab «enumeration» QualityIndexDab

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||DAB_QAL_BER|Bit error rate|
||DAB_QAL_SERVICE|Service quality|
||DAB_QAL_AUDIO|Audio qualtiy|
<b>Note:</b>\n
Station.quality vector indices for DAB/DMB devices\n

\subsubsection ssec_QualityIndexUndef «enumeration» QualityIndexUndef

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||UNDEF_QAL_AUDIO|Generic audio quality, comparable between devices|
<b>Note:</b>\n
Station.quality vector indices for the "UNDEF" device

\subsubsection ssec_SeekData «struct» SeekData

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|UInt32|data|Value in frequency or progress in percent|
|SeekMode|mode|The current seek mode|
|SeekReturnValue|returnValue|The current frequency (during seek mode)|
<b>Note:</b>\n
Seek mode relevant data

\subsubsection ssec_SeekMode «enumeration» SeekMode

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||SM_OFF|No seek off, stop possible running seek mode|
||SM_MAN_UP|Skip to next valid frequency|
||SM_MAN_DOWN|Skip to previous valid frequency|
||SM_AUTO_UP|Search next receivable station|
||SM_AUTO_DOWN|Search previous receivable station|
||SM_SCAN_UP|Scan the available stations (upwards)|
||SM_SCAN_DOWN|Scan the available stations (downwards)|
||SM_SCAN_SKIP_UP|While scan is active: Skip to next station|
||SM_SCAN_SKIP_DOWN|While scan is active: Skip to previous station|
||SM_AUTOSTORE|Autostore current waveband|
<b>Note:</b>\n
No seek off, stop possible running seek mode

\subsubsection ssec_SeekReturnValue «enumeration» SeekReturnValue

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|UInt32|SM_FREQUENCY|frequency value|
|UInt32|SM_PERCENTAGE|percentage value|
<b>Note:</b>\n
This enumeration contains the different possibilities of return values for the seek broadcast.

\subsubsection ssec_SelectionMode «enumeration» SelectionMode

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
||SM_UNDEF|Undefined selection mode|
||SM_DIRECT|Direct frequency input|
||SM_LIST|Station selected from background list|
||SM_PRESET|Preset selection|
<b>Note:</b>\n
Possible selection modes.

\subsubsection ssec_Station «struct» Station

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|UInt32s|flags|Additional flags (device and project specific, refer to specific hbtd file)|
|UInt32s|genre|Genres of station (indices are device and project dependent, refer to specific hbtd file)|
MGEG_Metadatas|meta|Vector of metadata (e.g. RT+ or DL+), only currently available types are part of this vector.|
|Strings|name|Name vector (indices are device and project dependent, refer to specific hbtd file)|
|UInt32s|quality|The quality vector (indices are device and project dependent, refer to specific hbtd file)|
|StationSelector|sel|Frequency and ID vector, can be directly passed into requestStartTune().|
|UInt32|stationType|Station type characterized by a bit field (available bits are defined in StationType enum)|
<b>Note:</b>\n
All important information about a station

\subsubsection ssec_StationListStruct «struct» StationList

Station list\n

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|UInt32|deviceType|Bit field characterizing the emitting tuner source (SourceType enum). That is the ORing of all possible deviceTypes in this list.|
|MGEG_Stations|stations|List of stations|
|UInt32|stationType|Containing station types characterized by a bit field (available bits are defined in StationType enum). That is the ORing of all possible stationTypes in this list.|
<b>Note:</b>\n
List of Station

\subsubsection ssec_StationType «enumeration» StationType

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|String|ST_UNDEF|No information|
|String|ST_RECEIVABLE|Station receivable|
|String|ST_PERMANENT|Station receivable|
|String|ST_AUTOSTORED|Station is part of autostore list|
|String|ST_ENSEMBLE|This entry is an ensemble (multiplex), information about the ensemble (e.g. id or name) is part of the station struct.|
|String|ST_SERVICE|This entry is a service, information about the service (e.g. id or name) is part of the station struct.|
|String|ST_PRIMARY|This entry is a primary component, information about the component (e.g. id or name) is part of the station struct.|
|String|ST_SECONDARY|This entry is a secondary component, information about the component (e.g. id or name) is part of the station struct.|
|String|ST_CHANGED|Data changed since last update|
<b>Note:</b>\n
Generic tuner station characteristics

\subsubsection ssec_UpdateElement «enumeration» UpdateElement

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
| |UE_SEEK|Seek data (seek)|
| |UE_CURRENT_STATION|Current station (currentStation)|
| |UE_STATION_LIST|Station list (stationList)|
<b>Note:</b>\n
Update elements that can be received (i.e. broadcasts/informations/attributes/signals)

\subsubsection ssec_Metadatas «array» Metadatas
<b>Note:</b>\n
Pairs of MetaData

\subsubsection ssec_ Stations «array» Stations
<b>Note:</b>\n
A vector of stations


\subsection ssec_StationInterface «Interface» Station

Tuner generic and project independent station interface. This interface provides information about the current station, the available station lists, and gives the possibilty to tune or select the current station.

\subsubsection ssec_abortTuner «method» abortTune
abortTune( \ref ssec_DeviceType "DeviceType" device, UInt32 handle, \ref ssec_Feedback "Feedback" feedback, UInt32 handle_out )\n

|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceType "DeviceType"|device|Device on which tune process shall be aborted.|
|UInt32|handle|An optional handle for identifying the request|
|\ref ssec_Feedback "Feedback"|feedback|The result of the request|
|UInt32|handle_out|The handle of the corresponding request|
<b>Function note</b>\n
Aborts a running tune or station selection process\n

\subsubsection ssec_controlUpdate «method» controlUpdate
controlUpdate( \ref ssec_UpdateElement "UpdateElement" updateElement, \ref ssec_UpdateType "UpdateType" updateType, UInt32 sourceType,
UInt32 stationType, UInt32 handle, UInt32 handle_out, \ref ssec_Feedback "Feedback" feedback )\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_UpdateElement "UpdateElement"|updateElement|Update element: seek data, current station, station list|
|\ref ssec_UpdateType "UpdateType"|updateType|Update type: One single update or continuously|
|UInt32|sourceType|The source type of interest (e. g. UNDEF, FM, AMFM)|
|UInt32|stationType|The station type of interest (e. g. RECEIVABLE, AUTOSTORE, PERMANENT)|
|UInt32|handle|An optional handle for identifying the request|
|UInt32|handle_out|The handle of the corresponding request|
|\ref ssec_Feedback "Feedback"|feedback|The result of the request|
<b>Function note</b>\n
Controls the update of currentStation or stationList information. It is possible to enable continuous updates or to request one single update e.g. necessary for synchronization after startup.

\subsubsection ssec_makePermanent «method» makePermanent
makePermanent( \ref ssec_StationSelector "StationSelector" station, Boolean permanent, UInt32 handle, UInt32 handle_out, \ref ssec_Feedback "Feedback" feedback )\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_StationSelector "StationSelector"|station|The requested frequency/station|
|Boolean|permanent|Enable / disable the permanent flag|
|UInt32|handle|An optional handle for identifying the request|
|UInt32|handle_out|The handle of the corresponding request|
|\ref ssec_Feedback "Feedback"|feedback|The result of that request|
<b>Function note</b>\n
Make station permanent (tuning information will not be removed from middleware even if station is not receivable any more)\n

\subsubsection ssec_seekmeth «method» seek
seek( \ref ssec_DeviceType "DeviceType" device, \ref ssec_SeekMode "SeekMode" seekMode, UInt8 genre, UInt32s flags, UInt32 handle, UInt32 handle_out, |\ref ssec_Feedback "Feedback" feedback )\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceType "DeviceType"|device|Device on which search shall run|
|\ref ssec_SeekMode "SeekMode"|seekMode|The requested seek mode and genre/PTY mask|
|UInt8|genre|Consider only stations of this genre|
|UInt32s|flags|Additional flags to be considered (device and project dependent)|
|UInt32|handle|An optional handle for identifying the request|
|UInt32|handle_out|The handle of the corresponding request|
|\ref ssec_Feedback "Feedback"|feedback|The result of the request|
<b>Function note</b>\n
Starts/Stops a seek process\n

\subsubsection ssec_startTune «method» startTune
startTune( \ref ssec_StationSelector "StationSelector" station, \ref ssec_SelectionMode "SelectionMode", UInt32 handle, UInt32 handle_out, \ref ssec_Feedback "Feedback" feedback )\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_StationSelector "StationSelector"|station|The requested frequency/station|
|\ref ssec_SelectionMode "SelectionMode"|selectionMode|The required selection mode|
|UInt32|handle|An optional handle for identifying the request|
|UInt32|handle_out|The handle of the corresponding request|
|\ref ssec_Feedback "Feedback"|feedback|The result of that request|
<b>Function note</b>\n
Starts tuning a frequency or selecting a station.\n\n


\subsection ssec_StationClient «Client Interface» StationClient

Tuner generic and project independent interface for station services. This interface provides broadcasts to get station lists, seek results and current station information.\n

\subsubsection ssec_seek «broadcast» seek

seek( \ref ssec_SeekData "SeekData" seekData, UInt32 handle )\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_SeekData "SeekData"|seekData|The current seek data.|
|UInt32|handle|The handle of the corresponding controlUpdate request|
<b>Function note</b>\n
Seek information sent during an active search.\n\n

\subsubsection ssec_stationList «broadcast» stationList

stationList( \ref ssec_StationList "StationList" list, UInt32 handle_out )\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_StationList "StationList"|list|The current station list update (different station types might exist in parallel).|
|UInt32|handle_out|The handle of the corresponding controlUpdate request|
<b>Function note</b>\n
Station list information\n\n

\subsubsection ssec_currentStation «broadcast» currentStation
currentStation( |UInt32 handle, \ref ssec_Station "Station" )\n
|Type|Name|Notes|
|----|----|-----|
|UInt32|handle|The handle of the corresponding controlUpdate request|
|\ref ssec_Station "Station"|current|Up-to-date information about the current station (optionally with additional metadata strings)|
<b>Function note</b>\n
Information about the currently active station.\n\n


\section sec_AddServices Additional Services

\subsection ssec_AdditionalServiceTypes «Types» AdditionalServiceTypes

\subsubsection ssec_UnionData «Union» Data

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
|String|stringData|Data is returned as string (link).|
|ByteBuffer|byteBufferData|Data is returned as bytebuffer.|
<b>Note</b>\n
Union for the return value of the data broadcast.

\subsubsection ssec_DataFormat «enumeration» DataFormat

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
||DF_XML|Format XML|
||DF_HTML|Format HTML|
||DF_PICTURE|Format Picture|
||DF_RAW|Format RAW|
<b>Note</b>\n
Enumeration for the data return formats.

\subsubsection ssec_DataType «enumeration» DataType

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
| |DT_STRING||Data type string.|
| |DT_STREAM|Data type stream|
| |DT_BYTEBUFFER|Data type bytebuffer|
<b>Note</b>\n
Enumeration for the data return types.

\subsubsection ssec_EWSAffectedArea «enumeration» EWSAffectedArea

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
||EAA_UNKNOWN| |
||EAA_NATIONALWIDE| |
||EAA_WIDEAREA| |
||EAA_REGION| |
||EAA_LOCAL| |
||EAA_POINT| |
<b>Note</b>\n
Affected area of the emergency warning. 

\subsubsection ssec_EWSType «enumeration» EWSType

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
||ET_UNKNOWN| |
||ET_EMERGENCY_WARNING| |
||ET_EARTHQUAKE_WARNING| |
||ET_TIDAL_WAVEWARNING| |
||ET_WEATHER_WARNING| |
||ET_ROAD_TRAFFIC| |
||ET_PERSONAL_CALL| |
||ET_EVENT_ANNOUNCEMENT| |
||ET_CAS_SERVICE_MESSAGE| |
||ET_TEST_SIGNAL| |
<b>Note</b>\n
Type of the emergency warning. 

\subsubsection ssec_ImageService «enumeration» ImageService

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
||IS_CATEGORIZED_SLIDESHOW|type signalizes a categorized slideshow image|
||IS_SLIDESHOW|type signalizes a slideshow image|
||IS_ALBUM_COVER|type signalizes an album cover image|
||IS_STATION_LOGO|type signalizes a station logo image|
<b>Note</b>\n
enumeration for different image service types

\subsubsection ssec_ImageType «enumeration» ImageType

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
||IT_BOOKLET_FRONT|image type indicates a front view of the booklet|
||IT_BOOKLET_BACK|image type indicates a back view of the booklet|
||IT_INTERPRET|image type indicates a view of the interpret |
<b>Note</b>\n
enumeration for different image types

\subsubsection ssec_Language «enumeration» Language

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
|String|Name|Abbreviation of language. for instance ger for german|
<b>Note</b>\n
Struct for languages

\subsubsection ssec_Languages «array» Languages
<b>Note</b>\n
Array of languages

\subsubsection ssec_DataService «enumeration» DataService

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
| |DS_NO_SERVICE|No specific type, should cause an error.|
| |DS_SUBTITLE|Subtitle service|
| |DS_TELETEXT|Teletext service|
| |DS_IMAGE|Image service|
| |DS_EPG|EPG service|
| |DS_TMC|TMC service|
| |DS_TPEG|TPEG service|
| |DS_JOURNALINE|Journaline service|
| |DS_ANNOUNCEMENT|Announcement service|
| |DS_EWS|EWS service|
<b>Note</b>\n
Enumeration for data services.

\subsubsection ssec_AnnouncementStates «array» AnnouncementStates
<b>Note</b>\n
array of annoucnementstates

\subsubsection ssec_arrayAnnouncementStates «array» arrayAnnouncementStates
<b>Note</b>\n
array of arrays of announcement states

\subsubsection ssec_AnnouncementState «enumeration» AnnouncementState

<b>Attribute</b> \n
|Type|Name|Notes|
|----|----|-----|
| |AS_NOT_AVAAILABLE|describes if the notified announcement is not available (e.g. because of bad reception)|
| |AS_AVAILABLE|describes if the notified announcement is available|
| |AS_ACTIVE|describes if the notified announcement is currently active|
<b>Note</b>\n
different states an announcement can have

\subsubsection ssec_AnnouncementType «enumeration» AnnouncementType

<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
||AT_Alarm| |
||AT_RoadTraffic| |
||AT_TransportFlash| |
||AT_WarningService| |
||AT_News| |
||AT_AreaWeather| |
||AT_Event| |
||AT_SpecialEvent| |
||AT_ProgramInformation| |
||AT_SportReport| |
||AT_FinancialReport| |
<b>Note</b>\n
Enumeration of announcement types.

\subsubsection ssec_Announcement «struct» Announcement

<b>Attribute:</b>\n
|Type|Name|Notes|
|----|----|-----|
|UInt32|componentID|Contains the component id that provides the announcement|
|\ref ssec_AnnouncementType "AnnouncementType"|type|Information about the announcement type.|
<b>Note</b>\n
Structure for the current announcement with information about channel and type.\n

\subsubsection ssec_AnnouncementTypeConfiguration «struct» AnnouncementTypeConfiguration
<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|AnnouncementType|type|Announcement types.|
|Boolean|active|Activation of announcement type|
|UInt32|priority|Priority for the type.|
<b>Note</b>\n
Structure for announcement types. For every type of announcement the availability is given. The user can activate or deactivate each type and he can change the priorities for every type

\subsubsection ssec_AnnouncementConfigurations «array» AnnouncementConfigurations
<b>Note</b>\n
Array type for announcement configuration\n

\subsection ssec_AdditionalServiceTypes «Types» AdditionalServiceTypes

\subsubsection ssec_AnnouncementTypeConfigurations «array» AnnouncementTypeConfigurations
<b>Note</b>\n
Array of announcement type configurations.

\subsection ssec_AdditionalServiceTypesOptions «Types» AdditionalServiceTypesOptions

\subsubsection ssec_UnifiedServiceOption «struct» UnifiedServiceOption

<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_UpdateType "UpdateType"|requestType|Request type |
|UInt32|objectID|ObjectID|
<b>Note</b>\n
Structure for options which are selectable for all data services

\subsubsection ssec_UnifiedServiceOptions «array» UnifiedServiceOptions

\subsubsection ssec_DataServiceOptions «array» DataServiceOptions
<b>Note</b>\n
Array for data service options

\subsubsection ssec_DataServiceOption «union» DataServiceOption
<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_No_Options "No_Options"|DSO_NO_OPTION|Parameter for default type if no specific options are available|
|\ref ssec_Subtitle_Options "Subtitle_Options"|DSO_SUBTITLE|Parameter for subtitle options.|
|\ref ssec_Teletext_Options "Teletext_Options"|DSO_TELETEXT|Parameter for teletext options.|
|\ref ssec_EPG_Options "EPG_Options"|DSO_EPG|Parameter for EPG options|
|\ref ssec_Journaline_Options "Journaline_Options"|DSO_JOURNALINE|Parameter for journaline options.|
|\ref ssec_Announcement_Options "Announcement_Options"|DSO_ANNOUNCEMENT|Parameter for Announcement options.|
|\ref ssec_EWS_Options "EWS_Options"|DSO_EWS|Parameter for EWS options.|
<b>Note</b>\n
Union for the selection of a data service. Depending on the data service another structure is used.

\subsubsection ssec_Announcement_Options «struct» Announcement_Options
<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_AnnouncementTypeConfiguration "AnnouncementTypeConfigurations"|type_Configuration|Announcement configuration |
<b>Note</b>\n
Options for announcements

\subsubsection ssec_Journaline_Options «struct» Journaline_Options

<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|Boolean|Entry_Object|Entry object is requested|
<b>Note</b>\n
Journaline options

\subsubsection ssec_No_Options «struct» No_Options

<b>Note</b>\n
Default options

\subsubsection ssec_Subtitle_Options «struct» Subtitle_Options

<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_Languages "Languages"|Languages|Possible/requested languages|
<b>Note</b>\n
Journaline options

\subsubsection ssec_Teletext_Options «struct» Teletext_Options

<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|Boolean|Entry_Object|Entry object is requested|
|UInt32|Subpage|Sub page with number x is requested|
<b>Note</b>\n
Teletext options

\subsubsection ssec_EPG_Options «struct» EPG_Options

<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DateTime "DateTime"|Start_Date_Time|Start time to filter the epg data packet that is requested|
|\ref ssec_DateTime "DateTime"|End_Date_Time|End time to filter the returned epg data|
|String|Genre|Genre to filter the returned epg data|
|UInt32|Count_Events|Count of events which are requested from a start time|
<b>Note</b>\n
Teletext options

\subsubsection ssec_EWS_Options «struct» EWS_Options

<b>Attribute</b>\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_EWSType "EWSType"|Type|Type of the emergency warning. |
|\ref ssec_EWSAffectedArea "EWSAffectedArea"|Affected_Area|Affected area of the emergency warning. |
<b>Note</b>\n
Teletext options

\subsection ssec_AdditionalService «Interface» AdditionalService
Tuner generic and project independent interface for additional services. This interface provides functions to request data services and to configure them. Other services like announcements can also be configured.\n

\subsubsection ssec_requestDataService «method» requestDataService

requestDataService( \ref ssec_DataService "DataService" dataService, \ref ssec_StationSelectors "StationSelectors" selectors, \ref ssec_DataServiceOptions "DataServiceOptions" serviceOptions, UInt32 handle, UInt32 handleOut, \ref ssec_Feedback "Feedback" feedback)
| Type| Name| Node|
|-----|-----|-----|
|\ref ssec_DataService "DataService"|dataService| |
|\ref ssec_StationSelectors "StationSelectors"|selectors| |
|\ref ssec_UnifiedServiceOptions "UnifiedServiceOptions"|unifiedOptions| |
|\ref ssec_DataServiceOptions "DataServiceOptions"|serviceOptions| |
|UInt32|handleOut|The handle of the corresponding request|
|\ref ssec_Feedback "Feedback"|feedback|The result of the request|
|UInt32|handle|An optional handle for identifying the request|
 <b>Function note: </b> \n
Function to request data from one or many stations for a specific data service. It is possible to configure the request by the DataServiceOption parameter.

\subsubsection ssec_requestSubscribedServiceOptions «method» requestSubscribedServiceOptions
requestComponentOptions( \ref ssec_DataService "DataService" dataService, UInt32 handle, UInt32 handleOut, \ref ssec_Feedback "Feedback" feedback )
|Type|Name|Node|
|----|----|----|
|\ref ssec_DataService "DataService" |dataService||
|UInt32|handle|An optional handle for identifying the request|
|UInt32|handleOut|The handle of the corresponding request|
|\ref ssec_Feedback "Feedback"|feedback|The result of the request|
<b>Function note: </b> \n

\subsection ssec_AdditionalServicesClient «ClientInterface» AdditionalServiceClient

Tuner generic and project independent interface for additional services. This interface provides functions to request data services and to configure them. Other services like announcements can also be configured.\n

\subsubsection ssec_Data «broadcast» Data
Data( \ref ssec_StationSelectors "StationSelectors"  stationSelectors, \ref ssec_DataService "DataService" dataService, \ref ssec_UnifiedServiceOption "UnifiedServiceOption" unifiedServiceOption, \ref ssec_DataServiceOption "DataServiceOption" selectOptions, \ref ssec_DataFormat "DataFormat" dataFormat, \ref ssec_DataType "DataType" dataType, \ref ssec_Data "Data" data, UInt32 handleOut, \ref ssec_ErrorCodes "ErrorCodes" errorCodes )\n
|Type|Name|Node|
|----|----|----|
| \ref ssec_StationSelectors "StationSelectors"|stationSelectors| |
|\ref ssec_DataService "DataService" 32|dataService| |
|\ref ssec_UnifiedServiceOption "UnifiedServiceOption" |unifiedServiceOption| |
|\ref ssec_DataServiceOption "DataServiceOption" |selectOptions| |
|\ref ssec_DataFormat "DataFormat" |dataFormat| |
|\ref ssec_DataType "DataType" |dataType| |
|\ref ssec_Data "Data" |data| |
|UInt32|handleOut|The handle of the corresponding selectComponent request|
|ref ssec_ErrorCodes "ErrorCodes" |errorCodes| |
<b>Function note: </b> \n
Function to return the requested data.

\subsubsection ssec_SubscribedServiceOptions «broadcast» SubscribedServiceOptions

SubscribedServiceOptions( \ref ssec_DataService "DataService" dataService, \ref ssec_ArrayStationSelectors "ArrayStationSelectors"  arrayStationSelectors, UInt32 handleOut , \ref ssec_ErrorCodes "ErrorCodes" errorCodes)\n
|Type|Name|Node|
|----|----|----|
|\ref ssec_DataService "DataService" |dataService| |
|\ref ssec_ArrayStationSelectors "ArrayStationSelectors"  |arrayStationSelectors| |
|UInt32|handleOut|The handle of the corresponding selectComponent request|
|ref ssec_ErrorCodes "ErrorCodes" |errorCodes| |
<b>Function note: </b> \n
Function to return the subscribed requests for a dataservice.

\subsubsection ssec_announcement «broadcast» Announcement

Announcement( \ref ssec_Announcement "Announcement" announcement, UInt32 handleOut, \ref ssec_ErrorCodes "ErrorCodes" errorCodes )\n
|Type|Name|Node|
|----|----|----|
|\ref ssec_Announcement "Announcement"|announcement|Structure that carries information to the incoming announcement|
|UInt32|handleOut|The handle to identify the annoucnement when for example abort it.|
|\ref ssec_ErrorCodes "ErrorCodes" |errorCodes| |
<b>Function note: </b> \n
Function to return information about the current announcement

\subsubsection  ssec_AnnouncementFinished «broadcast» AnnouncementFinished

AnnouncementFinished( \ref ssec_Announcement "Announcement" announcement, UInt32 handleOut )\n
|Type|Name|Node|
|----|----|----|
| \ref ssec_Announcement "Announcement"|announcement|Structure that carries information describing the announcement that need to finished|
|UInt32|handleOut|The handle to identify the announcement.|
<b>Function note: </b> \n
Function to signalize that the announcement is finished.\n

\section Configuration

\subsection ssec_ConfigurationOptions «Types» ConfigurationOptions

\subsubsection ssec_FuntionalityOptions «array» FuntionalityOptions
<b>Function note: </b> \n
FuntionalityOptions array of FunctionalityOption

\subsubsection ssec_FunctionalityOption «union» FunctionalityOption

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_HDOptions "HDOptions"|HDOptions| |
|\ref ssec_FollowingOptions "FollowingOptions"|followingOptions| |
|\ref ssec_CountryVariantsOptions "CountryVariantsOptions"|countryVariant| |
|\ref ssec_CoverageAreaOptions "CoverageAreaOptions"|coverageAreaOptions| |
|\ref ssec_AvailableBandoptions "AvailableBandoptions"|availableBandOptions| |
|\ref ssec_InterfaceVersionOptions "InterfaceVersionOptions"|interfaceVersionOptions| |
|\ref ssec_AMModiOptions "AMModiOptions"|amModiOptions| |
|\ref ssec_RDSOptions "RDSOptions"|rdsOptions| |
|\ref ssec_DLSOptions "DLSOptions"|dlsOptions| |
|\ref ssec_RTOptions "RTOptions"|smartFartOptionsvoriteOptions| |
<b>Function note: </b> \n

\subsubsection ssec_AvailableBandoptions «struct» AvailableBandoptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_SourceTypes "SourceTypes"|availableBands| |
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes| |
<b>Note: </b> \n

\subsubsection ssec_CoverageAreaOptions «struct» CoverageAreaOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_CountryVariants "CountryVariants"|countryVariants|possible current receiver areas|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|Device Types for  the country variants|
<b>Note: </b> \n

\subsubsection ssec_DLSOptions «struct» DLSOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_Activations "Activations"|activations| |
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for the coding options|
<b>Note: </b> \n

\subsubsection ssec_RDSOptions «struct» RDSOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_Activations "Activations"|activations ||
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for the coding options|
<b>Note: </b> \n

\subsubsection ssec_RTOptions «struct» RTOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_Activations "Activations"|activations| |
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for the coding options|
<b>Note: </b> \n

\subsubsection ssec_AMModiOptions «struct» AMModiOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_AMMode "AMMode"|amMode|possible  modi for amplitude modulation analog device|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for the coding options|
<b>Note: </b> \n

\subsubsection ssec_InterfaceVersionOptions «struct» InterfaceVersionOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|UInt32|minorVersion| |
|UInt32|majorVersion| |
<b>Note: </b> \n

\subsubsection ssec_HDOptions «struct» HDOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_Activation "Activation"|activation| |
<b>Note: </b> \n

\susubbsection ssec_CountryVariantsOptions «struct» CountryVariantsOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which the country variant are|
|\ref ssec_CountryVariants "CountryVariants"|countryVariants|country variants for the different device types
<b>Note: </b> \n

\subsubsection ssec_FollowingOptions «struct» FollowingOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_Activations "Activations"|activations|activations for the different following states|
|\ref ssec_FollowingTypes "FollowingTypes"|followingStates| |
<b>Note: </b> \n

\subsubsection ssec_SmartFavoriteOptions «struct» SmartFavoriteOptions

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_Activation "Activation"|activation|Activation for smart favorite. Here only for SDARS|
<b>Note: </b> \n

\subsection sec_ConfigurationOptionsGetter «Types» ConfigurationOptionsGetter

\subsubsection ssec_FuntionalityOptionsGet «array» FuntionalityOptionsGet 

<b>Note: </b> \n
FuntionalityOptionsGet array of FunctionalityOptionGet\n
Array of functionality options. This parameter is part of the request method. Using a array of union types enables to request  multiple configuration of different functionality types at once.

\subsubsection ssec_FunctionalityOptionGet «union» FunctionalityOptionGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_HDOptionsGet "HDOptionsGet "|HDOptions| |
|\ref ssec_FollowingOptionsGet "FollowingOptionsGet "|followingOptions| |
|\ref ssec_CountryVariantsOptionsGet "CountryVariantsOptionsGet "|countryVariant| |
|\ref ssec_CoverageAreaOptionsGet "CoverageAreaOptionsGet "|coverageAreaOptions| |
|\ref ssec_InterfaceVersionOptionsGet "InterfaceVersionOptionsGet "|interfaceVersionOptions| |
|\ref ssec_AvilableBandoptionsGet "AailableBandoptionsGet"|availableBandOptions| |
|\ref ssec_AMModiOptionsGet "AMModiOptionsGet "|amModiOptions| |
|\ref ssec_RDSOptionsGet "RDSOptionsGet "|rdsOptions| |
|\ref ssec_RTOptionsGet "RTOptionsGet "|rtOptions| |
|\ref ssec_DLSOptionsGet "DLSOptionsGet "|dlsOptions| |
<b>Note: </b> \n



\subsubsection ssec_DLSOptionsGet «struct» DLSOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested. here only AMFM makes sense|
<b>Note: </b> \n

\subsubsection ssec_AvailableBandoptionsGet «struct» AvailableBandoptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested. here only AMFM makes sense|
<b>Note: </b> \n

\subsubsection ssec_RTOptionsGet «struct» RTOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested. here only AMFM makes sense|
<b>Note: </b> \n

\subsubsection ssec_CoverageAreaOptionsGet «struct» CoverageAreaOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested. here only AMFM makes sense|
<b>Note: </b> \n

\subsubsection ssec_AMModiOptionsGet «struct» AMModiOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested. here only AMFM makes sense|
<b>Note: </b> \n

\subsubsection ssec_RDSOptionsGet «struct» RDSOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested. here only AMFM makes sense|
<b>Note: </b> \n

\subsubsection ssec_InterfaceVersionOptionsGet «struct» InterfaceVersionOptionsGet

<b>Note: </b> \n

\subsubsection ssec_HDOptionsGet «struct» HDOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested. here only AMFM makes sense|
<b>Note: </b> \n

\subsubsection ssec_CountryVariantsOptionsGet «struct» CountryVariantsOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested.|

\subsubsection ssec_FollowingOptionsGet «struct» FollowingOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_FollowingTypes "FollowingTypes"|followingTypes| |

\subsubsection ssec_SmartFavoriteOptionsGet «struct» SmartFavoriteOptionsGet

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_DeviceTypes "DeviceTypes"|deviceTypes|device types for which coding options are requested. here only AMFM makes sense|



\subsection ssec_ConfigurationTypesEnum «Types» ConfigurationTypesEnum

\subsubsection ssec_FunctionalityType «enumeration» FunctionalityType

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
||HD| |
||Following| |
||ParentalLock| |
||SmartFavorite| |
||CIModule| |
||AvailableBand| |
||CountryVariant| |
||Coding| |
||CoverageArea| |
||InterfaceVersion| |
||AMModi| |
||RDS| |
||RT| |
||DLS| |


\subsubsection ssec_AMMode «enumeration» AMMode

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
||AM_ONLY_MW|for AM is only medium wave available|
||AM_ONLY_LW|for AM is only long wave available|
||AM_MWLW|for AM is bot medium and long wave available|

\subsubsection ssec_FollowingType «enumeration» FollowingType

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
||FM_INTERNAL| |
||FM_DAB| |
||DAB_INTERNAL| |
||DAB_FM| |
||DVBT_INTERNAL| |
||DVBT_DAB| |

\subsubsection ssec_CountryVariant «enumeration» CountryVariant

<b>Attribute: </b> \n
|Type|Name|Notes|
|----|----|-----|
||CV_EUROPE| |
||CV_AUSTRALIA| |
||CV_HONGKONG| |
||CV_KOREA| |
||CV_CHINA| |
||CV_USA| |
||CV_OZEANIEN| |
||CV_JAPAN| |
||CV_EUROPE_ROW| |

\subsubsection ssec_CountryVariants «array» CountryVariants

<b>Attribute: </b> \n
CountryVariants array of CountryVariant

\subsubsection ssec_FollowingTypes «array» FollowingTypes

<b>Attribute: </b> \n
FollowingTypes array of FollowingType

\subsubsection ssec_FunctionalityTypes «array» FunctionalityTypes

<b>Attribute: </b> \n
FunctionalityTypes array of FunctionalityType

\subsection ssec_Configuration «Interface» Configuration

change configuration of a basic functionalites like following or smart favorite options. it is possible to set more then one configuration at a time by adding multiple functionality types and configuration to the arrays.\n

\subsubsection ssec_changeFunctionalityConfiguration «method» changeFunctionalityConfiguration

changeFunctionalityConfiguration( \ref ssec_functionalityTypes "functionalityTypes" functionalityTypes, \ref ssec_FuntionalityOptions "FuntionalityOptions" functionalityOptionsSet, UINt32 handle, \ref ssec_Feedback "Feedback" feedback, UInt32 handle_out )
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_FunctionalityTypes "FunctionalityTypes"|functionalityTypes|array of basic functionality types of which the configuration should be set|
|\ref sse_FuntionalityOptions "FuntionalityOptions"|functionalityOptionsSet|array of options that should be set according to the different functionality types|
|UInt32|handle|An optional handle for identifying the request|
|\ref ssec_Feedback "Feedback"|feedback|The result of the request|
|UInt32|handle_out|The handle of the corresponding request|
<b>Function note</b>\n
change configuration of a basic functionalites like following or smart favorite options. it is possible to set more then one configuration at a time by adding multiple functionality types and configuration to the arrays\n

\subsubsection ssec_requestFunctionalityConfiguration «method» requestFunctionalityConfiguration

requestFunctionalityConfiguration( \ref ssec_functionalityTypes "functionalityTypes" functionalityTypes, \ref ssec_FuntionalityOptionsGet "FuntionalityOptionsGet" functionalityOptionsGet, UInt32 handle, \ref ssec_Feedback "Feedback" feedback, UInt32 handle_out )
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_FunctionalityTypes "FunctionalityTypes"|functionalityTypes|array of basic functionality types of which the configuration should be set|
|\ref sse_FuntionalityOptionsGet "FuntionalityOptionsGet"|functionalityOptionsGet|spcify the request by giving  request configurations matching to the functionality types|
|UInt32|handle|An optional handle for identifying the request|
|\ref ssec_Feedback "Feedback"|feedback|The result of the request|
|UInt32|handle_out|The handle of the corresponding request|
<b>Function note</b>\n
request configuration of basic functionalities like following or conditional access. it is possible to request more than one configuration at a time by adding multiple functionality types and get options to the arrays\n

\subsection ssec_ConfigurationClient «Client Interface» ConfigurationClient

\subsubsection ssec_functionalityConfiguration «broadcast» functionalityConfiguration

functionalityConfiguration( \ref ssec_FunctionalityTypes "FunctionalityTypes" functionalityTypes, \ref ssec_FuntionalityOptions "FuntionalityOptions" functionalityOptions, UInt32 handle_out, \ref ssec_ErrorCodes "ErrorCodes" errorCode)\n
|Type|Name|Notes|
|----|----|-----|
|\ref ssec_FunctionalityTypes "FunctionalityTypes"|functionalityTypes|functionality types for the requested or set configuration|
|\ref ssec_FuntionalityOptions "FuntionalityOptions"|functionalityOptions|current configurations of the requested functionalities|
|UInt32|handle_out|handle to identify the correct destination of the following event|
|\ref ssec_ErrorCodes "ErrorCodes"|errorCode|execution state of the job. if successful finished EC_OK|
<b>Function note</b>\n
broadcast to return the requested functionality configuration\n

*/
