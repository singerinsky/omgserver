/*
 * CMatchManager.h
 *
 *  Created on: 2012-3-23
 *      Author: guanlei
 */

#ifndef CMATCHMANAGER_H_
#define CMATCHMANAGER_H_
#include "../common/head.h"
#include "match.h"

class IConnection;
struct ArenaMatchInfo{
	char	key[30];
	int		uid;
	int		op_uid;
	IConnection*	_conn;
};

struct FunctionPtrCmp{
	bool operator()(const char *ptr1,const char *ptr2)const
	{
		return strcmp(ptr1,ptr2) < 0;
	}
};

class CMatchManager {
public:
	CMatchManager();
	virtual ~CMatchManager();
	static CMatchManager* GetInstance() {
		if (_m_instance == NULL) {
			_m_instance = new CMatchManager();
		}
		return _m_instance;
	}

	void RemoveMatch(int mid){
		_lock.lock();
		MatchMapItr itr = _map.find(mid);
		if(itr != _map.end()){
			Match* match = itr->second;
			delete match;
			_map.erase(itr);
		}
		_lock.unlock();
	}

	int AddMatch(int mid, Match* match) {
		int rst = 0;
		_lock.lock();
		MatchMapItr itr = _map.find(mid);
		if (itr != _map.end()) {
			rst = 0;
		}else{
			_map[mid] = match;
			rst = 1;
		}
		_lock.unlock();
		return rst;
	}

	Match* GetMatch(int mid) {
		_lock.lock();
		MatchMapItr itr = _map.find(mid);
		if (itr != _map.end()) {
			_lock.unlock();
			return itr->second;
		}
		_lock.unlock();
		return NULL;

	}

	int GetMatchCount(){
		return _map.size();
	}

	void AddArenaWaitPair(char* key,ArenaMatchInfo* info){
		_lock.lock();
		_wait_id++;
		_arena_pair_map[key] = info;
		_lock.unlock();
	}

	int GetNewWaitId(){
		_lock.lock();
		_wait_id++;
		_lock.unlock();
		return _wait_id;
	}

	void RemoveArenaWaitPair(char* key){
		_lock.lock();
		ArenaPairMapItr itr = _arena_pair_map.find(key);
		if(itr != _arena_pair_map.end()){
			delete itr->first;
			delete itr->second;
			_arena_pair_map.erase(itr);
		}
		_lock.unlock();
	}

	ArenaMatchInfo* GetArenaWaitPair(char* key){
		_lock.lock();
		ArenaPairMapItr itr = _arena_pair_map.find(key);
		if(itr != _arena_pair_map.end()){
			_lock.unlock();
			return itr->second;
		}
		_lock.unlock();
		return NULL;
	}


private:
	typedef std::map<int, Match*> MatchMap;
	typedef std::map<int, Match*>::iterator MatchMapItr;

	typedef	map<char*,ArenaMatchInfo*,FunctionPtrCmp>	ArenaPairMap;
	typedef	map<char*,ArenaMatchInfo*,FunctionPtrCmp>::iterator	ArenaPairMapItr;
	MatchMap _map;
	ArenaPairMap	_arena_pair_map;
	omg::MutexLock _lock;
	static CMatchManager* _m_instance;
	int				_wait_id;
};

#endif /* CMATCHMANAGER_H_ */
