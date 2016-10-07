///////////////////////////////////////////////////////////
//  JournalineObject.cpp
//  Implementation of the Class JournalineObject
//  Created on:      09-Aug-2013 13:04:37
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/Dataservices/JournalineObject.h"


JournalineObject::JournalineObject(string file, string serviceID)  : DataHelper( serviceID ) {

	m_ID			= findTag("<ID>"    ,"</ID>"    , file);
	m_type			= findTag("<type>"  ,"</type>"  , file);
	m_jstatic		= findTag("<static>","</static>", file);
	m_title			= findTag("<title>" ,"</title>" , file);
	m_dlan			= findTag("<dlan>"  ,"</dlan>"  , file);
	m_jlink_descr	= findTag("<descr>" ,"</descr>" , file);
	m_jlink_id		= findTag("<id>"    ,"</id>"    , file);
	//vector; of those objects more than one tags can exist per object
	//need solution
	m_Text			= findTags("<Text>" ,"</Text>"  , file);
	m_jlist			= findTags("<text>" ,"</text>"  , file);

}

JournalineObject::~JournalineObject(){

}

string JournalineObject::returnObjectAsXML(){

	string tmp = "<xml>";
	tmp += "<JObject>";
	tmp += "<ID>"      + m_ID          + "</ID>";
	tmp += "<type>"    + m_type        +"</type>";
	tmp += "<static>"  + m_jstatic     + "</static>";
	tmp += "<title>"   + m_title       + "</title>";
	tmp += "<dlan>"    + m_dlan        + "</dlan>";
	tmp += "<jlink>";
	tmp += "<descr>"   + m_jlink_descr + "</descr>";
	tmp += "<id>"      + m_jlink_id    + "</id>";
	tmp += "</jlink>";
	for ( auto it = m_jlist.cbegin(); it != m_jlist.cend(); ++it ){
		tmp += "<Text>" + ( *it ) + "</Text>";
	}
	tmp += "</JObject>";
	tmp += "<jlist>";
	for ( auto it = m_jlist.cbegin(); it != m_jlist.cend(); ++it ){
		tmp += "<text>" + (*it) + "</text>";
	}
	tmp += "</jlist>";
	tmp += "</xml>";

	return  tmp;
}
