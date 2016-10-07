///////////////////////////////////////////////////////////
//  DataHelper.cpp
//  Implementation of the Class DataHelper
//  Created on:      09-Aug-2013 13:29:27
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Dataservices/DataHelper.h"


DataHelper::DataHelper( string serviceID ){
	m_serviceID = serviceID;
}

DataHelper::~DataHelper(){

}

string DataHelper::getServiceID(){
	return m_serviceID;
}

string DataHelper::findTag(string startTag, string endTag, string stream){

	size_t start = stream.find( startTag ) + startTag.length();
	size_t end   = stream.find( endTag   ) ;
	string tag;

	if ( start != std::string::npos && end != std::string::npos ){
		for ( ; start < end ; start++ ){
			tag += stream[start];
		}
	}
	return tag;
}

vector< string > DataHelper::findTags(string startTag, string endTag, string stream){
	vector< string > tmp;
	size_t start = stream.find( startTag ) + startTag.length();
	size_t end;
	string tag;
	while ( start != string::npos ){
		start = stream.find( startTag );
		size_t start_length;
		end   = stream.find( endTag   );
		tag = "";
		if ( start != std::string::npos && end != std::string::npos ){
			for ( ; start + startTag.length() < end ; start++ ){
				tag += stream[start + startTag.length()];
			}
		}
		stream = stream.substr( end + endTag.length() );
		tmp.push_back( tag );
	}
	return tmp;
}
