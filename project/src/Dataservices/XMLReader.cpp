///////////////////////////////////////////////////////////
//  XMLReader.cpp
//  Implementation of the Class XMLReader
//  Created on:      31-Jul-2013 13:34:52
//  Original author: QX92858
///////////////////////////////////////////////////////////

#include "includes/Dataservices/XMLReader.h"


XMLReader::XMLReader(){
	LoadData();
}

XMLReader::~XMLReader(){
}

//method returns the requested data for every component type as a byte buffer
//here it is possible to add some filter mechanism for the different component types. usual for the most component types is
//that the data belongs to a station; so most of the component types have a serviceID as member of the objects
bool XMLReader::getComponentData (
		IVIRadio::Types::Types::StationSelectors stationSelectors,
		IVIRadio::AdditionalService::AdditionalServiceTypes::DataService dataService,
		IVIRadio::AdditionalService::AdditionalServiceTypesOptions::DataServiceOption dataServiceOption,
		uint32_t objectID, CommonAPI::ByteBuffer &oBuff ) {

	IVIRadio::Types::Types::UInt32s stationIdentifiers;

	for ( auto it = stationSelectors.cbegin(); it != stationSelectors.cend(); it++ ){
		if ( (*it).deviceType == (uint32_t)IVIRadio::Types::Types::DeviceType::AMFM ){
			stationIdentifiers.push_back( (*it).id[2] );
		}
		if ( (*it).deviceType == (uint32_t)IVIRadio::Types::Types::DeviceType::DAB ) {
			stationIdentifiers.push_back( (*it).id[3] );
		}
	}
	cout << "objectID: " << objectID << endl;
	string tmp = "";
	if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_EPG ) {
		//filtering information
		//uint32_t devType = component_parameter.get<IVIRadio::AdditionalService::AdditionalServiceTypes::EPG_Parameter>().station.deviceType;
		string   genre   = dataServiceOption.get<IVIRadio::AdditionalService::AdditionalServiceTypesOptions::EPG_Options>().Genre;
		uint32_t evID    = objectID;
		string   strID   = to_string( evID ); //cast ID to string for to compare it afterward in the if clause
		//get whole set of data for that Station Identifier, filtering that data for genre; date; eventID etc must be done later
		tmp += "<xml>";
		for (auto it = m_vecEPGEvents.cbegin(); it != m_vecEPGEvents.cend(); it++) {
			for ( auto it2 = stationIdentifiers.cbegin(); it2 != stationIdentifiers.cend(); it2++ ){
				if ( ( *it )->getServiceID() == to_string((*it2)) ){
					tmp += ( *it )->returnEventAsXML();
				}
			}
		}
		tmp += "</xml>";
	}
	//filtering for ObjectID
	else if ( dataService == IVIRadio::AdditionalService::AdditionalServiceTypes::DataService::DS_JOURNALINE ) {

		for (auto it = m_vecJournalineObjects.cbegin(); it != m_vecJournalineObjects.cend(); it++) {
			if ( ( *it )->getObjectID( ) == objectID ){
				tmp = ( *it )->returnObjectAsXML();
			}
		}
	}

	//fill bytebuffer for for out parameter; this buffer will be send via the interface to the client
	for ( int i = 0; i < tmp.length(); i++ ){
		char c = tmp[i];
		uint8_t testint = uint8_t(c);
		oBuff.push_back(testint);
	}
	if ( tmp == "" ){
		return false;
	}
	return true;
}

void XMLReader::LoadData(){
	LoadEPGData       ();
	LoadJournalineData();
	LoadSubtitleData  ();
}

vector < string > XMLReader::LoadDirectory(string dirname){
	//load content of the directory /dirname into a vector; all files with the extension $dirname are loaded
	DIR *directory;
	string strdirectory = "AdditionalData/" + dirname;
	struct dirent *structEPGFile;
	vector < string > files_in_dir;
	if((directory  = opendir(strdirectory.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << strdirectory << endl;
		return files_in_dir;
	}
	//save the filenames of all $dirname files
	while ( ( structEPGFile = readdir( directory ) ) != NULL ) {
		files_in_dir.push_back(string( structEPGFile->d_name ) );
	}
	closedir(directory);
	return files_in_dir;
}

void XMLReader::LoadJournalineData(){
	string serviceID = "";
	vector< string > files_in_Journaline_dir = LoadDirectory( "Journaline" );
	//parse all the available .EPG files and save their content to an instance
	//of EPGEvent; those data is held in an vector during runtime
	for (auto it = files_in_Journaline_dir.cbegin(); it != files_in_Journaline_dir.cend(); it++) {
		string tmp = readFile( *it , "Journaline" );
		if ( ( *it ).length() > 11 )
			string serviceID = ( *it ).substr( 0, (*it).length() - 11 );
		if ( tmp != "" ){
			JournalineObject *journalineObject = new JournalineObject( tmp, serviceID ); //create EPG event and store it into the vector
			m_vecJournalineObjects.push_back( journalineObject );
		}
	}
}

void XMLReader::LoadEPGData(){
	//load content of the directory /EPG into a vector; all files with the extension .EPG are loaded
	vector< string > files_in_EPG_dir = LoadDirectory( "EPG" );
	//parse all the available .EPG files and save their content to an instance
	//of EPGEvent; those data is held in an vector during runtime
	for (auto it = files_in_EPG_dir.cbegin(); it != files_in_EPG_dir.cend(); it++) {
		if ( ( *it ).length() > 3 && ( *it ).substr( ( *it ).length() - 3 , 3 ) == "EPG" ){
			string file_name = "AdditionalData/EPG/" + ( *it );
			ifstream myfile;
			myfile.open( file_name );
			if (!myfile.is_open()) { //check availability of file
				cerr << "Unable to open file " << file_name << endl;
			}
			else {
				string line, file;
				while(myfile.good()) { //read all content of a .EPG file to a buffer
					getline(myfile, line);
					file += line;
				}
				//find service ID in EPG file and pass it to all EPGEvents belonging to that SID
				string service_start_tag = "<ServiceID>"  ;
				string service_end_tag   = "</ServiceID>" ;
				string serviceID = "";
				size_t start_service = file.find( service_start_tag );
				size_t end_service = file.find( service_end_tag );
				if ( start_service != string::npos ) {
					for ( ; start_service + service_start_tag.length() < end_service ; start_service++)
						serviceID += file[start_service + service_start_tag.length()];
				}
				string start_tag = "<EPGEvent>" ;
				string end_tag   = "</EPGEvent>";
				//since a .EPG file can contain more than one EPG Event it is necessary to get them all
				while ( file.find( "EPGEvent" ) != string::npos ) {
					size_t start = file.find( start_tag ) + start_tag.length();
					size_t end   = file.find( "</EPGEvent>") ;
					string tag = "";
					//save the stream between starttag and endtag to a buffer and create for each an instance of EPG event
					if ( start != std::string::npos && end != std::string::npos ){
						for ( ; start < end ; start++ ){
							tag += file[start];
						}
						file = file.substr(end + end_tag.length() ); //buffer the whole stream less the previous event
					}
					EPGEvent *epgEvent = new EPGEvent(tag, serviceID); //create EPG event and store it into the vector
					m_vecEPGEvents.push_back( epgEvent );
				}
			}
		}
	}
}

void XMLReader::LoadSubtitleData  (){
	vector< string > files_in_Subtitle_dir = LoadDirectory( "Subtitle" );
	//parse all the available .Subtitle files and save their content to an instance
	//of SubtitleEvent; those data is held in an vector during runtime
	for (auto it = files_in_Subtitle_dir.cbegin(); it != files_in_Subtitle_dir.cend(); it++) {
		string serviceID = ( *it ).substr( 0, (*it).length() - 9 );
		string tmp;
		tmp = readFile( *it , "Subtitle" );
		if ( tmp != "" ){
			SubtitleStream *subtitleStream = new SubtitleStream( tmp, serviceID ); //create EPG event and store it into the vector
			m_vecSubtitleStreams.push_back( subtitleStream );
		}
	}
}

string XMLReader::readFile( string file_name, string type ){
	string file = "";
	if ( file_name.length() > 3 && file_name.substr( file_name .length() - type.length() , type.length() ) == type ){
		string file_name_with_folder = "AdditionalData/" + type + "/" + file_name;
		ifstream myfile;
		myfile.open( file_name_with_folder );
		if (!myfile.is_open()) { //check availability of file
			cerr << "Unable to open file " << file_name_with_folder << endl;
		}
		else {
			string line;
			while(myfile.good()) { //read all content of a .EPG file to a buffer
				getline(myfile, line);
				file += line;
			}
		}
	}
	return file;
}




