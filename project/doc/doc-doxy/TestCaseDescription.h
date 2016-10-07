/*! \page IntroTestcases Testcases 

Description of Test Cases realized in the PoC version 2.0\n

\n

Station Management Test Cases\n
\ref pageStartSeek\n
\ref pageRequestStationList\n
\ref pageTuneToFreq\n
\ref pageSelectStationFromList\n
\ref pageSaveInPresetList\n
\ref pageGetPresetList\n
\ref pageFollowing\n

\n

\ref pageDataServices "Data Services"\n
\ref pageConfigAdditionalServiceComponents\n
\ref pageIncomingAnnouncements\n
\ref pageAbortAnnouncement\n

\n
\ref pageConfiguration "Configuration"\n
\ref pageRequestFunctionalityConfig\n
\ref pageChangeFunctionalityConfig\n

\section pageStartSeek Start Seek 

\subsection sec_DesrStartSeek Test Case Description

The Test Case 'Start \ref ssec_seekmeth "Seek"' simulates a background scan that scans a desired waveband (e.g. FM or DAB) once from the lowest to the highest frequency and reads information from a simulated station landscape.

\subsection ssec_SequenceChartStartSeek SequenceChart

\image html SeqChartStartSeek.jpg
The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
In the \ref ssec_seekmeth "seek command" the Client specifies the \ref ssec_DeviceType "DeviceType" and the \ref ssec_SeekMode "SeekMode" seekMode. Possible \ref ssec_DeviceType "DeviceTypes" for the PoC are FM or DAB and to perform an autostore the user needs to pass the \ref ssec_SeekMode "SeekMode" SM_AUTOSTORE.\n
The call of the function returns immediately with a \ref ssec_Feedback "Feedback" if the call can be handled. \n
In the loop 'Autostore' the Middleware sends a \ref ssec_seek "seek broadcast" containing the progress of the process in percentage back to the Client. This broadcast is sent in 10 percent steps. (The interface would provide also to send the progress in frequency steps or in different step width depending on the specific implementation of the Middleware)

\subsection ssec_UsageStartSeek Simulate Testcase in the PoC

To get a list of stations firstly a \ref ssec_seekmeth "seek" command with parameter ‘autostore’ needs to be performed (not shown in the Sequence Chart). After passing this command to the Middleware it will parse the subdirectory ‘bin/config’
and will save all the information from the simulated station environment to an internal station list.\n
To get progress information of the performing seek the client needs to notify on this functionality by calling the \ref ssec_controlUpdate "controlUpdate" method.\n\n

Command to notify on progress information of a seek for FM stations:\n
Commands entered in the Client console: 5 1 1 1 8\n\n
Command that is passed to the Middleware:\n
\ref ssec_controlUpdate "controlUpdate" (UE_SEEK, UT_NOTIFICATION, AMFM_FM, ST_UNDEF)\n\n
Command to invoke a seek for FM stations:\n
Command entered in the Client console: 3 0 0 0 0\n\n
Command that is passed to the Middleware:\n
\ref ssec_seekmeth "seek"(AMFM, SM_AUTOSTORE, 0, 0)\n\n
The Middleware is configured to send a progress feedback to the Client in 10% steps. This information is provided in the \ref ssec_seek "seek" broadcast.\n When the Middleware has finished executing the seek process and the Client has notified on progress feedback, it sends an additional \ref ssec_seek "seek broadcast" with the parameter SEEK_OFF.\n
The Proof of Concept supports the two broadcast \ref ssec_DeviceType "standards" FM and DAB, so a seek can be executed for both FM and DAB. For this simply change the first parameter of the
\ref ssec_seekmeth "Seek" command from AMFM (0) to DAB (1). All other \ref ssec_DeviceType "DeviceTypes" will be refused from the Middleware.\n\n

\section pageRequestStationList Request Station List


\subsection sec_DesrStationList Testcase Description

The Test Case Start 'Request Station List' simulates the exchange of a station list between the Middleware and the Client.

\subsection ssec_SequenceChartRequestStationList SequenceChart

\image html SeqChartGetList.jpg
The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
In the \ref ssec_controlUpdate "controlUpdate" command the user specifies the \ref ssec_UpdateElement "updateElement", the \ref ssec_SourceType "sourceType", the \ref ssec_UpdateType "updateType" and the \ref ssec_StationType "station type". The user can request two different types of \ref ssec_StationListStruct "station lists" depending on the \ref ssec_DeviceType "device type". Either a tuner specific list or a combined list. For a standard specific list the parameter \ref ssec_SourceType "sourceType" need to be either AMFM or DAB (other standards are not yet supported and will be refused by the Middleware). To receive a combined station list the parameter need to be UNDEF_SOURCE. \n
Since it is possible to request different information by calling \ref ssec_controlUpdate "controlUpdate" the user must specify his call. To get a station list the parameter \ref ssec_UpdateElement "updateElement" has to be set to UE_STATION_LIST.
To get a list of receivable stations the \ref ssec_UpdateType "updateType" should be set to ST_RECEIVABLE.\n
Like every function call the function returns immediately with a feedback if the call can be handled. \n
After finishing the job the Middleware sends a \ref ssec_controlUpdate "controlUpdate" broadcast containing the requested information back to the Client.\n

\subsection ssec_UsageRequestStationList Simulate Testcase in the PoC

If Test Case Start Seek was successfully executed the Client can request a standard specific station list.\n
Command to get a standard specific station list:\n
Command entered in the Client console: 5 2 2 1 8\n\n
Command that is passed to the Middleware:\n
\ref ssec_controlUpdate "controlUpdate"(UE_STATION_LIST, UT_ONCE, AMFM_FM, ST_UNDEF)\n
The Middleware passes a list of FM station to the Client using the \ref ssec_stationList "stationList" broadcast.\n\n
After executing a seek for both supported standards FM and DAB the Client can request a combined station list. In that combined \ref ssec_StationListStruct "station list" no station will appear more than once. \ref ssec_Station "Stations" which are received on different frequencies are combined using program identifier (FM) or the service identifier (DAB).\n
Command to get a combined station list:\n
Command entered in the Client console:  2 2 16 8\n\n
Command that is passed to the Middleware:\n
\ref ssec_controlUpdate "controlUpdate"(UE_STATION_LIST, UT_ONCE, UNDEF_SOURCE, ST_UNDEF)\n\n


\section pageTuneToFreq Tune to frequency

\subsection sec_DesrTuneToFreq Description Tune to Frequency

The Test Case 'Tune to Frequency' simulates a direct tune to the desired frequency in the desired waveband.

\subsection ssec_SequenceChartRequestStationList SequenceChart

\image html SeqChartTuneToFreq.jpg
The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
In the \ref ssec_startTune "startTune" command the user can specify the \ref ssec_Station "Station" and the \ref ssec_SelectionMode "SelectionMode". If \ref ssec_SelectionMode "SelectionMode" is SM_DIRECT a direct tune to a desired frequency will be executed. The frequency and device type information must be send in the \ref ssec_StationSelector "StationSelector".

\subsection ssec_UsageRequestStationList Simulate Testcase in the PoC

The client has different options to tune to a station. One is to tune directly to the frequency.\n
Command to tune to a frequency:\n
Command entered in the Client console: 1 0 0 95500\n\n
Command that is passed to the Middleware:\n
startTune(SM_DIRECT, AMFM, 95500)\n\n
The Middleware performs a tune to frequency in the background and after finishing the action the Middleware will send a \refssec_currentStation "currentStation" broadcast to the Client. If a station was found at this specific frequency, the broadcast contains the information describing the station. If no station is available at the desired frequency (no description file for that frequency in the station environment) the Middleware will tune to the desired frequency and the Client receives a ‘not applicable’ message.


\section pageSelectStationFromList Select Station from station list

\subsection sec_DesrSelectStationFromList Description Select Station from station list

The Test Case "Select Station from station List" simulates a tune to a \ref ssec_Station "Station" that is available in a \ref ssec_StationListStruct "Station List" that was created by a background scan.

\subsection ssec_SequenceChartSelStationFromList SequenceChart

\image html SeqChartSelStationFromList.jpg
The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
The first command flow to provide a station List to the client is not a necessary part of this Test Case but for the understanding included.\n
In the startTune command the user specifies the \ref ssec_StationSelector "StationSelector" and the \ref ssec_SelectionMode "SelectionMode" for the request. \n
If the \ref ssec_SelectionMode "SelectionMode" is SM_LIST a tune to a station from a list will be executed. The \ref ssec_SelectionMode "SelectionMode" must now contain the unique station identifier, which is assigned to a station by the Middleware. The \ref ssec_DeviceType "Device Type" can be AMFM, DAB or UNDEF depending on the list the user chooses the station from.

\subsection ssec_UsageSelStationFromList Simulate Testcase in the PoC

The second option for the Client to tune to a station is from an available list. For that the Client needs to pass the ID identifying the Station uniquely in the system.\n
Command to select a station from an available list:\n
Command entered in the Client console: 1 1 0 10\n\n
Command that is passed to the Middleware:\n
\ref ssec_startTune "startTune"(SM_LIST, AMFM, 10)\n\n
The Provider sends a \ref ssec_currentStation "currentStation" broadcast back to the Client after successfully finished the command.\n


\section pageSaveInPresetList Make station permanent

\subsection sec_DesrSaveInPreset Description make station permanent

The Test Case 'Make station permanent' describes the process of making a \ref ssec_Station "Station" a station permanent. In fact every \ref ssec_Station "Station" has a flag that could be set true and false, which indicates if it is allowed to delete the \ref ssec_Station "Station" or not.

\subsection ssec_SequenceChartSaveInPreset SequenceChart

\image html SeqChartSaveInPreset.jpg "Interaction Diagram: Make station permanent"

The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
In the command \ref ssec_makePermanent "makePermanent" the user specifies the \ref ssec_Station "Station" of which the indicator flag "permanent" should be set or reset.

\subsection ssec_UsageSaveInPreset Simulate Testcase in the PoC

For managing a list of favorites the Client can set the attribute ‘permanent’ of a station.\n
Command to make a station permanent:\n
Command entered in the Client console: 0, 4, 1\n\n
Command that is passed to the Middleware:\n
\ref ssec_makePermanent "makePermanent"(AMFM, 4, TRUE)\n\n
If the second parameter is a valid \ref ssec_Station "Station" identifier from the \ref ssec_stationList "Station List", the attribute will be set. To reset the attribute the Client simply needs to send FALSE as third parameter.

\section pageGetPresetList Get List of permanent stations

\subsection sec_DesrGetPresetList Description 'Get List of permanent stations'

The Test Case describes how to request a list of permanent stations. The Middleware returns all stations marked with the flag permanent as true.

\subsection ssec_SequenceChartGetPresetList SequenceChart

\image html SeqChartGetPresetList.jpg

The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
In the \ref ssec_controlUpdate "controlUpdate" command the user specifies the \ref ssec_UpdateElement "updateElement", the \ref ssec_SourceTypes "sourceType", the \ref ssec_UpdateType "UpdateType" and the \ref ssec_StationType "StationType". To request the list of permanent stations the user needs to specify the \ref ssec_StationType "StationType" as ST_PERMANENT. The \ref ssec_DeviceType "deviceType" should be set to UNDEF_SOURCE.\n
Since it is possible to request different information by calling \ref ssec_controlUpdate "controlUpdate" the user must specify his call. To get a \ref ssec_stationList "Station List" the parameter \ref ssec_UpdateElement "updateElement" has to be set to UE_STATION_LIST and the \ref ssec_StationType "StationType" needs to be ST_PERMANENT.

\subsection ssec_UsageGetPresetList Simulate Testcase in the PoC

The Client can request the list with all \ref ssec_Station "Stations" having the ‘permanent’ attribute set TRUE.\n
Command to get list of all permanent stations:\n
Command entered in the Client console: 5 2 2 1 3 8\n\n
Command that is passed to the Middleware:\n
\ref ssec_ContolUpdate "controlUpdate"(UE_STATION_LIST, UT_ONCE, AMFM, ST_PERMANENT )\n\n
The Middleware will send back a list of all \ref ssec_Station "Station" with the attribute ‘permanent’ set in the \ref ssec_stationList "stationList" broadcast.\n


\section pageFollowing Following

\subsection sec_Following Description Following

The Test Case describes how the User can invoke a following event using the Middleware.\n

\subsection ssec_SequenceChartFollowing SequenceChart

\image html SeqChartFollowing.jpg "Interaction Diagram: Following"
\n
The Sequence Chart shows the interaction between the middleware and the client that are necessary to execute the following use case.\n
To show the dependencies the Sequence Chart contains additionally the tune process which is in fact part of another use case. \n
Firstly the user should request a station list (not shown in the sequence chart) to be able to tune to a station stored in that list.\n
After tuning to a station from a station list the user should have a currently active station. \n
Secondly the user needs to activate the desired following types by executing the changeFunctionalityConfiguration use case.\n
When a following is initiated in the middleware, it sends a currentStation broadcast to signalise the Client that a tune to another station (or following) has happened.

\subsection ssec_UsageFollowing Simulate Testcase in the PoC

The Proof of Concept supports sending following events from the Middleware to the Client. For that a station from a station list must be tuned (see the first sequence in the chart). Additionally an alternative station to the currently tuned one must be available in the station environment (means there must be at least two stations with the same PI/SI Code; if a FM_INTERNAL event should be send two FM stations with the same PI Code, if DAB_FM following one DAB and FM station with the same PI/SI Code must be available). \n
To request a station list and start a tune to a station refer to the particular testcase (\ref pageRequestStationList "Request Stationlist" \ref pageSelectStationFromList "Tune to Station"). \n
The first client action belonging actually to that use case is to activate the following functionality itself. For detailed description refer to test case \ref pageChangeFunctionalityConfig "Change Functionality Configuration".\n
To actually inform the Client that a following event has happened the Middleware sends a currentStation broadcast to the Client:
Command to invoke following:\n
Command entered in the Middleware console: 4 5\n
If all constraints are fulfilled, the client should get the following event and after the middleware has changed the current station, the client should receive a currentStation broadcast.



\section sec_DataServices Data Services

With the Data Services component of the IVI Radio API is it possible to to get diverse data from different \ref ssec_DataService "Data Services" provided by the broadcaster.\n 
When requesting a Station List the Middleware communicates the supported \ref ssec_DataService "Data Services" for each station to Client. \n
The Data Services Component basically provides to request data by subscribing on specific set of data or requesting that set of data once. The Client can as well cancel a subscription once there is no more need for updates of those data. (see Use Case \ref pageConfigAdditionalServiceComponents "Configure Additional Service Component")\n
It is also possible to request a set of currently active subscriptions for a \ref ssec_DataService "Data Services" (see Use Case \ref pageRequestFunctionalityConfig "Request Functionality Configuration")\n
Additionally this component cares about handling of \ref ssec_Announcement "Announcements". Therefore are two special broadcasts intended. One to signalise an incoming announcement and one to signalise the end of current announcement (see Use Cases \ref pageIncomingAnnouncements "Incoming Annoucements" and  \ref pageAbortAnnouncement "Abort Annoucement").\n

\section pageConfigAdditionalServiceComponents Configure Additional Service Component

\subsection sec_DesrConfAnn Description Configure Additional Service Component

The Test Case describes how to subscribe or cancel subscriptions on \ref ssec_DataService "Data Services" (Version 1.0 only supports the Data Service Announcement, in Version 2.0 other Data Services are also implemented and configurable with these sequence.) and how to request all active subscriptions. \n
The Sequence consists of requests of currently active subscriptions of the desired \ref ssec_DataService "Data Services" and then more subscriptions are added or subscriptions are cancelled.

\subsection ssec_SequenceChartGetPresetList SequenceChart

\image html SeqChartConfigAnnouncement.jpg "Interaction Diagram: Configure Additional Service Component"
\n
\image html RequestDataServiceSubscriptions.jpg "Interaction Occurance: RequestDataServiceSubscriptions"
\n
\image html SetCancelDataServiceSubscription.jpg "Interaction Occurance: Set/Cancel Data Service Subscription "

The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
In the \ref ssec_requestSubscribedServiceOptions "requestSubscribedServiceOptions" command the user specifies the \ref ssec_DataService "Data Service" for that the subscriptions are requested. \n
In the broadcast \ref ssec_SubscribedServiceOptions "SubscribedServiceOptions" the Middleware provides the requested subscriptions of the desired \ref ssec_DataService "Data Service". Such a subscription consists of a \ref ssec_DataService "DataService", an \ref ssec_ArrayStationSelectors "Array of StationSelectors" for which the subscription is valid and information describing the subscription (\ref ssec_UnifiedServiceOption "UnifiedServiceOptions", \ref ssec_DataServiceOptions "DataServiceOptions"). The Unified Options containing an ID and the \ref ssec_UpdateType "Update Type" (if subscriptions are requested the update type should be UT_NOTIFICATION). For all \ref sse_DataService "Data Services" the Unified Options are the same. The \ref ssec_DataServiceOptions "DataServiceOptions" Parameter however contains filter options specific to the desired \ref sse_DataService "Data Service".\n
In the \ref ssec_requestDataService "requestDataService" command the Client changes the settings of subscriptions for a \ref ssec_DataService "Data Service". To add a new subscription the Client needs to specify the subscription by passing the \ref ssec_DataService "Data Service" the subscription is for, a list of \ref ssec_StationSelectors "Station Selectors" to indicate from which station the data is required and the specific filter options for the desired \ref ssec_DataService "Data Service". To add a new subscription the value UnifiedOptions.requestType should be UT_NOTIFICATION. If the User passes the requestType UT_NONE an existing subscription can be cancelled. If passing requestType UT_ONCE no new subscription is added but the requested data is transmitted once.

\subsection ssec_UsageGetPresetList Simulate Testcase in the PoC

The Client requests the current settings of subscriptions of a specific \ref ssec_DataService "Data Service" \n
Command to request subscriptions:\n
Command entered in the Client console: 6 3\n
Command that is passed to the Middleware:\n
\ref ssec_requestDataService "requestDataService"(DS_EPG)\n
The command in the example above will request the currently active subscriptions\n
The Middleware answers that call with a \ref ssec_SubscribedServiceOptions "SubscribedServiceOptions" broadcast which contains the description of the subscription.\n
To add one more subscription for the desired \ref ssec_DataService "Data Service" the Client calls \ref ssec_requestDataService "requestDataService".\n
Command to specify subscriptions:\n
Commands entered in the console (example is to specify a new subscription for EPG): 9 3 18 100 1 0 0\n
Command that is passed to the Middleware:\n
requestDataService(DS_EPG, [{DAB, [18, 180000, 25, 4122, 21]}], {UT_NOTIFICATION, 0}, {"dummyTime", "dummyTime", 0, 0})\n
The Middleware answers with a \ssec_Data "Data broadcast" that contains all information to the subscription and the data as well as some information describing \ref ssec_DataFormat "format" and \ref ssec_DataType "type" of the transmitted data.

\section pageIncomingAnnouncements Incoming Annoucements

\subsection sec_DesrIncommingAnn Description 'Incomming Annoucements'

The Test Case describes how the Middleware communicates an incoming announcement to the Client.

\subsection ssec_SequenceChartIncomingAnnouncement SequenceChart

\image html SeqChartIncomingAnnouncement.jpg "Interaction Diagram: Incoming Announcement"
\n
The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
First to see in the sequence diagram is that the annoucement configuration is changed to enable the Client to receive announcements. (see \ref pageConfigAdditionalServiceComponents "Configure Additional Service Components")\n
The Middleware signalises an incoming announcement by sending an \ref ssec_Announcement "Announcement broadcast" containing an \ref ssec_Announcement "Announcement" struct that specifies the \ref ssec_AnnouncementType "AnnouncementType" and the ID_KEY of the belonging station of the Announcement. When the announcement is finished the Middleware sends an \ref ssec_AnnouncementFinished "AnnouncementFinished" broadcast containing an \ref ssec_Announcement "Announcement" struct that specifies the \ref ssec_AnnouncementType "AnnouncementType" and the ID_KEY of the belonging station of the Announcement.

\subsection ssec_UsageIncomingAnn Simulate Testcase in the PoC

The Proof of Concept supports sending announcements. For that a station needs to be currently tuned. To simulate an Announcement the Provider needs to send an \ref ssec_announcement "Announcement" broadcast to the Client. (Precondition: a station is currently tuned -> see \ref pageSelectStationFromList "Tune to Station from list" possible command 1 1 0 10 (tunes to station with ID 10 which supports Announcements))\n
Command to set subscription for Announcement:
Command entered in Console:  9 1 10 100 1 1 6 0 1 0
Command passed to the Middleware: \ref ssec_requestDataService "requestDataService"( DS_ANNOUNCEMENT, [{10, 95500, 4122, 3}], {UT_NOTIFICATION, 0}, {[{AT_ROAD_TRAFFIC, ACTIVE, 1]} )\n
Command to send an announcement:\n
Command entered in the Middleware console: 1 10 6\n
Command that is passed to the Client:\n
\ref ssec_announcement "announcement"( 10, AT_RoadTraffic )\n\n
To get a list of currently running announcements it is possible to ask the Client. (This function is not part of the interface)\n
Command entered in the Client console: 10\n
When the announcement is finished the Middleware sends automatically an \ref ssec_announcementFinished "announcementFinished" broadcast.

\section pageAbortAnnouncement Abort Annoucement

\subsection sec_DescrAbortAnn Description of 'Abort Annoucements'

The Test Case describes how the Client aborts an currently active announcement.

\subsection ssec_SequenceChartAbortAnn SequenceChart

\image html SeqChartAbortAnnouncement.jpg "Interaction Diagram: Abort Announcement"
\n
The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
First to see in the sequence diagram is that the announcement configuration is changed to enable the Client to receive announcements. (see \ref pageConfigAdditionalServiceComponents)\n
Then the Middleware signalises an incoming announcement by sending an \ref ssec_announcement "announcement" broadcast containing the \ref ssec_AnnouncementType "Announcement Type". \n
To finish a currently active announcement the Client sends an \ref ssec_requestDataService "requestDataService" command to the Middleware containing the ID_KEY of the broadcasting station of the announcement to be finished. After finshing an currently active Announcement the subscription will be cancelled. If the Client want to receive that Announcement next time again, it need to notify again.\n
The Middleware answers with an \ref ssec_AnnouncementFinished "AnnouncementFinished broadcast".

\subsection ssec_UsageAbortAnn Simulate Testcase in the PoC

The Client can abort a currently active announcement. For this an announcement needs to be active.\n
Command to abort an announcement:\n
Command entered in the Client console: 9 1 10 100 0 1 6 0\n\n
Command that is passed to the Middleware:\n
\ref ssec_requestDataService "requestDataService"( DS_ANNOUNCEMENT, [{10, 95500, 4122, 3}], {UT_NONE, 0}, {[{AT_ROAD_TRAFFIC, ACTIVE, 1]} )\n
The Announcement will be finished and does not appear any longer in the list of active Announcements.

\section pageConfiguration Configuration

\section pageRequestFunctionalityConfig Request Functionality Configuration

\subsection sec_RequestFuncConf Description Request Functionality Configuration

The Test Case 'Request Functionality Configuration' describes how the User can request the configuration of a functionality.

\subsection ssec_SequenceChartRequestFunctionalityConfiguration SequenceChart

\image html SeqChartRequestFunctionalityConfiguration.jpg "Interaction Diagram: Request Functionality Configuration"
\n
The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
First to see in the sequence diagram is that the Client sends an \ref ssec_requestFunctionalityConfiguration "requestFunctionalityConfiguration" call to the Middleware. The first parameter is a list of \ref ssec_FunctionalityTypes "Functionality Types". With the list type here it is possible to get the configuration of multiple \ref ssec_FunctionalityTypes "Functionality Types" with just one request.\n
The second parameter is a list containing a set of parameter to specify the request for every \ref ssec_FunctionalityTypes "Functionality Type".
The asynchronous broadcast \ref ssec_functionalityConfiguration "functionalityConfiguration" contains the list functionality types and a corresponding list containing functionality configuration appending to the particular \ref ssec_FunctionalityType "FunctionalityType" of the first parameter.

\subsection ssec_UsageIncomingAnn Simulate Testcase in the PoC

Requesting the configuration for different \ref ssec_FunctionalityTypes "Functionality Types".
Command to request functionality configuration for the \ref ssec_FunctionalityTypes "Functionality Types" COUNTRYVARIANT and FOLLOWING:\n
Command entered in the Client console: 12 1 3 2 0 1 1 6 2 0 5 0\n
Command that is passed to the Client:\n
\ref ssec_requestFunctionalityConfiguration "requestFunctionalityConfiguration"([COUNTRYVARIANT, FOLLOWING], [[AMFM, DAB], [DAB_FM, FM_INTERNAL]] )\n\n


\section pageChangeFunctionalityConfig Change Functionality Configuration

\subsection sec_ChangeFunctionalityConfig Description Change Functionality Configuration
The Test Case describes how the User can change the configuration of a functionality.

\subsection ssec_SequenceChartChangeFunctionalityConfiguration SequenceChart

\image html SeqChartChangeFunctionalityConfiguration.jpg "Interaction Diagram: Request Functionality Configuration"
\n
The Sequence Chart shows the commands between the Client (here HMI) and the Middleware. All the commands are part of the Tuner API.\n
First to see in the sequence diagram is that the Client sends a \ref ssec_changeFunctionalityConfiguration "changeFunctionalityConfiguration" call to the Middleware. The first parameter is a list of \ref ssec_functionalityTypes "functionalityTypes". With the list type here it is possible to change the configuration of multiple \ref ssec_functionalityTypes "functionalityTypes" with just one call.\n
The second parameter is a list containing a set of parameter that should be set for every  \ref ssec_functionalityTypes "functionalityType".
The asynchronous broadcast functionalityConfiguration contains the list \ref ssec_functionalityTypes "functionalityTypes" and a corresponding list containing functionality configuration appending to the particular \ref ssec_functionalityTypes "functionalityType" of the first parameter.

\subsection ssec_UsageIncomingAnn Simulate Testcase in the PoC

Set the configuration for different \ref ssec_FunctionalityTypes "Functionality Types".
Command to request functionality configuration for the \ref ssec_FunctionalityTypes "Functionality Types" COUNTRYVARIANT and FOLLOWING:\n
Command entered in the Client console: 11 1 3 2 0 2 1 3 1 6 2 0 0 5 0 0\n
Command that is passed to the Middleware:\n
\ref ssec_ChangeFunctionalityConfiguration "changeFunctionalityConfiguration"([COUNTRYVARIANT, FOLLOWING], [[[AMFM, DAB], [CV_EUROPE, CV_EUROPE_ROW]], [[DAB_FM, FM_INTERNAL], [ACTIVE, ACTIVE]]] )\n\n

*/
