/*
 * CSocketMap.h
 *
 *  Created on: 2012-2-1
 *      Author: guanlei
 */

#ifndef CSOCKETMAP_H_
#define CSOCKETMAP_H_
#include "../common/head.h"
#include "../common/omg_type.h"
#include "GateWayPlayer.h"

#include <map>
using namespace omg;

class packet;

typedef std::map<SocketFD,GateWayPlayer*> SocketMap;
typedef std::map<int,GateWayPlayer*>::iterator SMItr;

typedef std::map<int,GateWayPlayer*>	PlayerMap;

class GateWayPlayerManager {
public:
	GateWayPlayerManager();
	virtual 					~GateWayPlayerManager();
	bool						AddPlayerMap(int,GateWayPlayer* player);
	void						RemoveGatePlayerMap(GateWayPlayer* player);
	void						RemoveGatePlayerMap(int player_id);
	GateWayPlayer* 				GetGateWayPlayer(int);
	GateWayPlayer*				GetGateWayPlayerBySockFd(int);
	static GateWayPlayerManager*	GetInstance();
	int							GetGatePlayerCount();

	inline	void				SendMsgAll(packet* msg){
		_lock.lock();
		SMItr itr= _player_map.begin();
		while(itr != _player_map.end()){
			GateWayPlayer* player = itr->second;
			_lock.unlock();
			player->send_packet_msg(msg);
			_lock.lock();
			itr++;
		}
		_lock.unlock();
	}

	std::list<int>	export_all_player_online(){
		std::list<int> player_list;
		SMItr itr= _player_map.begin();
		while(itr != _player_map.end()){
			player_list.push_back(itr->first);
			itr++;
		}
		return player_list;
	}


private:
	static	GateWayPlayerManager*	_m_instance;
	PlayerMap	_player_map;
	//MutexLock	_lock;
	omg::NullLock	_lock;
};
#endif /* CSOCKETMAP_H_ */
