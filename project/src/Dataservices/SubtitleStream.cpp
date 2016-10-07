///////////////////////////////////////////////////////////
//  SubtitleStream.cpp
//  Implementation of the Class SubtitleStream
//  Created on:      13-Aug-2013 11:08:27
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Dataservices/SubtitleStream.h"


SubtitleStream::SubtitleStream( string stream, string serviceID ) : DataHelper( serviceID ){

	m_stream = stream;
	m_disp   = findTag("<disp>"  , "</disp>"  ,  stream);
	m_disphh = findTag("<disphh>", "</disphh>",  stream);
	m_lan    = findTag("<lan>"   , "</lan>"   ,  stream);
	m_text   = findTag("<t>"     , "</t>"     ,  stream);
	m_color  = findTag("<color>" , "</color>" ,  stream);

}

SubtitleStream::~SubtitleStream(){

}

string SubtitleStream::returnEventAsXML( ) {
	string xml;

	xml += "<xml>";
	xml += "<Subtitle>";
	xml += "<disp>"   	+ m_disp   	+ "</disp>";
	xml += "<disphh>"  	+ m_disphh  + "</disphh>";
	xml += "<lan>" 		+ m_lan 	+ "</lan>";
	xml += "<Text>";
	xml += "<t>" 		+ m_text 	+ "</t>";
	xml += "<color>"  	+ m_color  	+ "</color>";
	xml += "</Text>";
	xml += "</Subtitle>";
	xml += "</xml>";

	return xml;
}



