///////////////////////////////////////////////////////////
//  HMIList.cpp
//  Implementation of the Class HMIList
//  Created on:      16-Jul-2013 16:47:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/HMIList.h"


HMIList::HMIList(){

	m_hmiList.clear();
	cout << "Created HMI list." << endl;
}

HMIList::~HMIList(){
}

void HMIList::addHMI(HMI *m_hmi)
{
	m_hmiList.insert(m_hmi);
}

void HMIList::deleteHMIbyNumber(int m_hmiId)
{
    HMI *hmiFound;
    bool found = false;
    for (auto it = m_hmiList.cbegin(); it != m_hmiList.cend(); ++it) {
        if ((*it)->getHMIId() == m_hmiId) {
            hmiFound = (*it);
            found = true;
            break;
        }
    }
    if (found) {
    	m_hmiList.erase(hmiFound);
        delete hmiFound;
    }
}

HMI *HMIList::getHMIbyNumber(int hmi_number)
{
    for (auto it = m_hmiList.cbegin(); it != m_hmiList.cend(); ++it) {
        if ((*it)->getHMIId() == hmi_number) {
            return (*it);
        }
    }
    return NULL;
}

void HMIList::deleteHMI(HMI *hmi)
{
	m_hmiList.erase(hmi);
    delete hmi;
}
