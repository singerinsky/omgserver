/*
 * GateConManager.cpp
 *
 *  Created on: 2013-4-3
 *      Author: guanlei
 */

#include "GateConManager.h"

GateConManager*	GateConManager::_instance;

GateConManager::GateConManager() {
	// TODO Auto-generated constructor stub
	_lock.init();
}

GateConManager::~GateConManager() {
	// TODO Auto-generated destructor stub
}
