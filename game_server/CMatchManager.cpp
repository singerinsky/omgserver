/*
 * CMatchManager.cpp
 *
 *  Created on: 2012-3-23
 *      Author: guanlei
 */

#include "CMatchManager.h"

CMatchManager* CMatchManager::_m_instance;
CMatchManager::CMatchManager() {
	// TODO Auto-generated constructor stub
	_lock.init();
	_wait_id = 0;
}

CMatchManager::~CMatchManager() {
	// TODO Auto-generated destructor stub
}
