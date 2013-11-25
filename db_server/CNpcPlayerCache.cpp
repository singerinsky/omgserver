/*
 * CNpcPlayerCache.cpp
 *
 *  Created on: 2012-7-20
 *      Author: guanlei
 */

#include "CNpcPlayerCache.h"

CNpcPlayerCache* CNpcPlayerCache::_m_instance;

CNpcPlayerCache::~CNpcPlayerCache() {
	// TODO Auto-generated destructor stub
}

MsgPlayerInfo*	CNpcPlayerCache::QueryPlayerInfo(PLAYER_ID player_id){
	_lock.lock();
	std::map<int,MsgPlayerInfo*>::iterator itr = _all_npc_player_map.find(player_id);
	if(itr != _all_npc_player_map.end()){
		MsgPlayerInfo* player_info = itr->second;
		_lock.unlock();
		return player_info;
	}
	_lock.unlock();
	return NULL;
}


void	CNpcPlayerCache::AddPlayerInfoToCache(PLAYER_ID player_id,MsgPlayerInfo* player_info){
	_lock.lock();
	MsgPlayerInfo *tmp_player_info = new MsgPlayerInfo();
	memcpy(tmp_player_info,player_info,sizeof(MsgPlayerInfo));
	_all_npc_player_map[player_id] = tmp_player_info;
	_lock.unlock();
}

void	CNpcPlayerCache::ClearPlayerCache(){
	_lock.lock();
	std::map<int,MsgPlayerInfo*>::iterator tmp_itr;
	std::map<int,MsgPlayerInfo*>::iterator itr = _all_npc_player_map.begin();
		while(itr != _all_npc_player_map.end()){
			tmp_itr = itr;
			itr++;
			MsgPlayerInfo* player_info = tmp_itr->second;
			delete player_info;
			_all_npc_player_map.erase(tmp_itr);
		}
	_lock.unlock();
}
