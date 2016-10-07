///////////////////////////////////////////////////////////
//  EPGEvent.cpp
//  Implementation of the Class EPGEvent
//  Created on:      01-Aug-2013 14:41:27
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Dataservices/EPGEvent.h"


EPGEvent::EPGEvent( string event , string serviceID ) : DataHelper( serviceID ) {
	m_event = event;
	m_ID  		= findTag( "<ID>"  		, "</ID>"   , event	);
	m_ver 		= findTag( "<ver>" 		, "</ver>"  , event	);
	m_reco		= findTag( "<reco>"		, "</reco>" , event	);
	m_name		= findTag( "<name>"		, "</name>" , event	);
	m_time		= findTag( "<time>"		, "</time>" , event	);
	m_dur 		= findTag( "<dur>" 		, "</dur>"  , event	);
	m_fsc  		= findTag( "<fsc>" 		, "</fsc>"  , event	);
	m_desc 		= findTag( "<desc>"		, "</desc>" , event	);
}

EPGEvent::~EPGEvent(){

}

string EPGEvent::returnEventAsXML(  ){

	string xml;


	xml += "<EPGProgram>";
	xml += "<EPGEvent>";
	xml += "<ID>"   + m_ID   + "</ID>";
	xml += "<ver>"  + m_ver  + "</ver>";
	xml += "<reco>" + m_reco + "</reco>";
	xml += "<name>" + m_name +"</name>";
	xml += "<time>" + m_time + "</time>";
	xml += "<dur>"  + m_dur  + "</dur>";
	xml += "<fsc>"  + m_fsc  + "</fsc>";
	xml += "<desc>" + m_desc + "</desc>";
	xml += "</EPGEvent>";
	xml += "</EPGProgram>";


	return xml;
}
