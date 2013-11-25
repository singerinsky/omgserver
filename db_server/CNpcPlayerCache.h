/*
 * CNpcPlayerCache.h
 *
 *  Created on: 2012-7-20
 *      Author: guanlei
 */

#ifndef CNPCPLAYERCACHE_H_
#define CNPCPLAYERCACHE_H_

typedef int	PLAYER_ID;

#include "../common/head.h"
#include "DBEvent.h"

class CNpcPlayerCache {
protected:
	CNpcPlayerCache(){
		_lock.init();
	}

public:
	virtual ~CNpcPlayerCache();
	static	CNpcPlayerCache*	GetInstance(){
		if(_m_instance == NULL){
			_m_instance = new CNpcPlayerCache();
		}
		return _m_instance;
	}
	MsgPlayerInfo*				QueryPlayerInfo(PLAYER_ID);
	void						AddPlayerInfoToCache(PLAYER_ID,MsgPlayerInfo*);
	void						ClearPlayerCache();

private:
	std::map<PLAYER_ID,MsgPlayerInfo*> _all_npc_player_map;
	static CNpcPlayerCache*	_m_instance;
	omg::MutexLock			_lock;
};

#endif /* CNPCPLAYERCACHE_H_ */
