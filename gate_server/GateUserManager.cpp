/*
 * CSocketMap.cpp
 *
 *  Created on: 2012-2-1
 *      Author: guanlei
 */

#include "../common/objectfactory.h"
#include "GateUserManager.h"

GateWayPlayerManager* GateWayPlayerManager::_m_instance;

GateWayPlayerManager* GateWayPlayerManager::GetInstance() {
	if (_m_instance == NULL) {
		_m_instance = new GateWayPlayerManager();
	}
	return _m_instance;
}

GateWayPlayerManager::GateWayPlayerManager() {
	// TODO Auto-generated constructor stub
}

GateWayPlayerManager::~GateWayPlayerManager() {
	// TODO Auto-generated destructor stub
}

bool GateWayPlayerManager::AddPlayerMap(int player_id, GateWayPlayer* player) {
	assert(player != NULL);
	SMItr itr = this->_player_map.find(player_id);
	if (itr == _player_map.end()) {
		_player_map[player_id] = player;
		return true;
	} else {
		VLOG(3)<<"client has connection....";
		return false;
	}
}

void GateWayPlayerManager::RemoveGatePlayerMap(GateWayPlayer* player) {
	assert(player != NULL);
	SMItr itr = this->_player_map.find(player->get_player_id());
	if(itr != _player_map.end()) {
		delete itr->second;
		_player_map.erase(itr);
	}
}

void GateWayPlayerManager::RemoveGatePlayerMap(int player_id) {
	SMItr itr = this->_player_map.find(player_id);
	if(itr != _player_map.end()) {
		delete itr->second;
		_player_map.erase(itr);
	}
}

int GateWayPlayerManager::GetGatePlayerCount() {
	return _player_map.size();
}

GateWayPlayer* GateWayPlayerManager::GetGateWayPlayer(int player_id) {
	SMItr itr = _player_map.find(player_id);
	if(itr != _player_map.end()) {
		return itr->second;
	}
	return NULL;
}

GateWayPlayer* GateWayPlayerManager::GetGateWayPlayerBySockFd(int socket_fd){
	SMItr itr = _player_map.begin();
	while(itr != _player_map.end()){
		if(itr->second->get_client_sock_fd() == socket_fd){
			return itr->second;
		}
		itr++;
	}
	return NULL;
}



