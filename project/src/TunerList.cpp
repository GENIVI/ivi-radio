///////////////////////////////////////////////////////////
//  TunerList.cpp
//  Implementation of the Class TunerList
//  Created on:      16-Jul-2013 16:47:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#include "includes/TunerList.h"


TunerList::TunerList(){

}

TunerList::~TunerList(){

}

void TunerList::addFMTuner (FMTuner  *fmTuner ) {
	m_tunerListFM.push_back(fmTuner);
}


void TunerList::addDABTuner(DABTuner *dabTuner){
	m_tunerListDAB.push_back(dabTuner);
}

Tuner* TunerList::getFreeTuner( IVIRadio::Types::Types::DeviceType device ){

	//search for an idle tuner in the correct list and return it if found, else return NULL
	if ( device == IVIRadio::Types::Types::DeviceType::AMFM ) {

		for (auto it = m_tunerListFM.cbegin(); it != m_tunerListFM.cend(); ++it) {
				if ((*it)->getState() == TunerState::IDLE) {
					return *it;
				}
			}
		}
	else if  ( device == IVIRadio::Types::Types::DeviceType::DAB ) {

			for (auto it = m_tunerListDAB.cbegin(); it != m_tunerListDAB.cend(); ++it) {
					if ((*it)->getState() == TunerState::IDLE) {
						return *it;
					}
				}
			}
	return NULL;
}

Tuner* TunerList::getFreeTuner( uint32_t device ){

	//search for an idle tuner in the correct list and return it if found, else return NULL; 1 is AMFM 2 is DAB
	if ( device == 255 ) {
		cout << "searc for a AMFM tuner... " << endl;
		for (auto it = m_tunerListFM.cbegin(); it != m_tunerListFM.cend(); ++it) {
				if ((*it)->getState() == TunerState::IDLE) {
					return *it;
				}
			}
		}
	else if  ( device == 16128 ) {
		cout << "searc for a DAB tuner... " << endl;
		for (auto it = m_tunerListDAB.cbegin(); it != m_tunerListDAB.cend(); ++it) {
				if ((*it)->getState() == TunerState::IDLE) {
					return *it;
				}
			}
		}
	return NULL;
}

/*TunerList* TunerList::getTunerList()
{
   // Mutex->lockMutex();

    return this;
}*/
