///////////////////////////////////////////////////////////
//  Announcement.cpp
//  Implementation of the Class Announcement
//  Created on:      30-Jul-2013 16:25:52
//  Original author: QX92858
///////////////////////////////////////////////////////////

#include "includes/Dataservices/Announcement.h"

#define LOG( a, b ) m_terminalIO->Log( a, b )

Announcement::Announcement(){
	m_terminalIO = TerminalIO::getInstance();
	m_announcementEnabled = IVIRadio::Types::Types::Activation::INACTIVE;
}

Announcement::~Announcement(){

}

void Announcement::setAnnouncementHandling(IVIRadio::Types::Types::Activation state)
{
    m_announcementEnabled = state;
    if (state == IVIRadio::Types::Types::Activation::INACTIVE) {
    	m_announcementType.clear();
    }
}

IVIRadio::Types::Types::Activation Announcement::getAnnouncementHandling()
{
    return m_announcementEnabled;
}

void Announcement::setAnnouncementConfiguration(IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType type, IVIRadio::Types::Types::Activation enabled, uint32_t priority,
		IVIRadio::Types::Types::StationSelector stationSelector, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState annState)
{
    AnnouncementConfig x;
    x.active 			= enabled;
    x.priority 			= priority;
    x.type 				= type;
    x.stationSelector 	= stationSelector;
    x.annState			= annState;
    m_vAnnouncementConfig.push_back(x);
    m_announcementType[type] = x;
}

IVIRadio::Types::Types::Activation Announcement::getAnnouncementConfigurationEnabled( IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType type){
    for (auto it = m_announcementType.cbegin(); it != m_announcementType.cend(); it++) {

    	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType x = (*it).first;
        AnnouncementConfig y = (*it).second;
        if ( x == type){
        	return y.active;
        }
    }
    return IVIRadio::Types::Types::Activation::INACTIVE;
}

IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations  Announcement::getAnnouncementConfiguration()
{
    /*
     * it is unclear, whether we should send back info about all possible announcement types,
     * even if they are currently not included in our map, or not. Consider that in the map there
     * may be entries that activate or deactivate entries. However for some other entries, there
     * may be no entry at all, we have to assume that this also means disabled.
     */
	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfigurations out;
    int n = m_announcementType.size();
    int i = 0;
    for (auto it = m_announcementType.cbegin(); it != m_announcementType.cend(); it++, i++) {
    	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementConfiguration tmp;
    	IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType x = (*it).first;
        AnnouncementConfig y = (*it).second;
        tmp.active 		= y.active;
        tmp.type   		= x;
        tmp.priority 	= y.priority;
    }

    return out;
}


bool Announcement::addActiveAnnouncement( IVIRadio::Types::Types::StationSelector stationSelector, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType announcementType)
{
    auto it = m_activeAnnouncements.find( stationSelector.id[0] );
    if (it != m_activeAnnouncements.end()) {
        // cannot insert same announcement twice
        return false;
    }
    m_activeAnnouncements[ stationSelector.id[0] ] = announcementType;
    return true;
}

bool Announcement::deleteActiveAnnouncement( IVIRadio::Types::Types::StationSelector stationSelector )
{
    auto it = m_activeAnnouncements.find( stationSelector.id[0] );
    if (it == m_activeAnnouncements.end()) {
        return false;
    } else {
        m_activeAnnouncements.erase( stationSelector.id[0] );
        return true;
    }
}

bool Announcement::isActiveAnnouncement( IVIRadio::Types::Types::StationSelector stationSelector )
{
    auto it = m_activeAnnouncements.find( stationSelector.id[0] );
    if (it == m_activeAnnouncements.end()) {
        return false;
    } else {
        return true;
    }
}

map< uint32_t, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType > Announcement::getActiveAnnouncements()
{
    return m_activeAnnouncements;
}

bool Announcement::getAnnouncementStates( IVIRadio::Types::Types::StationSelectors stationSelectors , IVIRadio::AdditionalService::AdditionalServiceTypesOptions::Announcement_Options annConf, IVIRadio::AdditionalService::AdditionalServiceTypes::arrayAnnouncementStates &arrAnnStates){
	for ( auto it_stSel = stationSelectors.cbegin(); it_stSel != stationSelectors.cend(); it_stSel++ ){
		IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementStates tmpAnnStates;
		for ( auto it = m_vAnnouncementConfig.cbegin(); it != m_vAnnouncementConfig.cend(); it++ ){
			if ( (*it).stationSelector.id[0] == (*it_stSel).id[0] ){
				for ( auto it_annConf = annConf.Type_Configurations.cbegin(); it_annConf != annConf.Type_Configurations.cend(); it_annConf++ ) {
					if ((*it_annConf).type == (*it).type ){
						tmpAnnStates.push_back((*it).annState);
					}
				}
			}
		}
		arrAnnStates.push_back(tmpAnnStates);
	}
	return true;
}

bool Announcement::changeAnnouncementType(IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementState annState, IVIRadio::Types::Types::StationSelector stationSelector, IVIRadio::AdditionalService::AdditionalServiceTypes::AnnouncementType annType ){
	vector <AnnouncementConfig> tmp_vAnnConf;
	bool bReVal = false;
	for ( auto it = m_vAnnouncementConfig.cbegin(); it != m_vAnnouncementConfig.cend(); it++ ){
		AnnouncementConfig tmp;
		tmp.active = (*it).active;
		tmp.priority = (*it).priority;
		tmp.stationSelector = (*it).stationSelector;
		tmp.type = (*it).type;
		if ((*it).stationSelector.id[0] == stationSelector.id[0] && (*it).type == annType ) {
			tmp.annState = annState;
			bReVal = true;
		}
		else{
			tmp.annState = (*it).annState;
		}
		tmp_vAnnConf.push_back(tmp);
	}
	m_vAnnouncementConfig = tmp_vAnnConf;
	return bReVal;
}

