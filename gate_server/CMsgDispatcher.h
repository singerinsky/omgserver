/*
 * CMsgDispatcher.h
 *
 *  Created on: 2012-2-2
 *      Author: guanlei
 */

#ifndef CMSGDISPATCHER_H_
#define CMSGDISPATCHER_H_

#include "../common/head.h"
#include "zlib.h"
#include "../common/queue.h"
#include "../common/lock.h"
#include "../common/MD5.h"
#include "../common/timer_manager.h"
#include "../net/thread.h"
#include "../net/epoll_socket.h"
#include "../net/client_socket.h"
#include "../net/IMsgDispatcher.h"
#include "GServer.h"
#include "GateClientMsg.h"
#include "GateGameMsg.h"
#include "GateWayPlayer.h"
#include <string>
#include <sstream>

extern char* public_key;


using namespace omg;
struct GameServerInfo{
	int _index;
	int _fd;
	StringBuffer _ip;
	int	_port;
	CSocketClient* _socket;
	int _state;//0:disconnect 1:connect
	GameServerInfo(){
		_socket = NULL;
		_state = 0;	
	}
};

struct MatchInfo{
	MatchInfo(){
	}
	int server_index;
	int match_type;
	std::list<int>	_watch_list;

	void add_watch_player(int uid){
		_watch_list.push_back(uid);
	}

	bool is_player_in(int uid){
		std::list<int>::iterator itr = _watch_list.begin();
		while(itr != _watch_list.end()){
			if(*itr == uid){
				return true;
			}
			itr++;
		}
		return false;
	}

	void remove_watcher_player(int uid){
		std::list<int>::iterator itr = _watch_list.begin();
		while(itr != _watch_list.end()){
			if(*itr == uid){
				_watch_list.erase(itr);
				return;
			}
			itr++;
		}
	}

	void dump_all_player_info(){
		std::list<int>::iterator itr = _watch_list.begin();
		while(itr != _watch_list.end()){
			VLOG(1)<<"WATCHER "<<*itr;
			itr++;
		}
	}

};

class CGateTimerEventHandler;

class CMsgDispatcher:public IMsgDispatcher, public Thread {
public:
	CMsgDispatcher(const char* name=NULL):Thread(name)
    {
		_pass_msg_count++;
        tick_msg = get_tsc_us()*1000;
        _timer_mgr.init(get_run_ms(),14);
        _dispatcher_timer.set_owner(this);
	}
	virtual ~CMsgDispatcher();
	virtual void*	on_run(void);	
public:
	static CMsgDispatcher* GetInstance(){
		if(_m_instance == NULL){
			_m_instance = new CMsgDispatcher();
		}
		return _m_instance;
	}
	virtual	bool	add_msg_to_queue(CMsgEvent*,EPollSocket*);
	virtual void 	dispatch_msg();
	bool		check_msg_valide(CMsgEvent*,EPollSocket*);
	bool		do_login(CMsgEvent*,EPollSocket*);
	bool		do_logout(GateWayPlayer*,int rst=-1);
	bool		dis_connection(EPollSocket*socket,int error);
	void		SendMatchPlayerData(MsgMatchPlayerRoundData*);
	void		SendMatchBallData(MsgMatchBallRoundData*);
	void		SendMatchResultData(MsgMatchResultData*);
	void		SendTeamSkillInfoToPlayer(MsgClientRequestSkillInfoAck*msg);
	void		SendStartMatchAckTOPlayer(MsgClientStartMatchAck* msg);
	void		SendMatchEventData(MsgMatchEventRoundData*);
	void        SendMatchSkillData(MsgGamePlayerSkillData* m);
	void        SendMatchTeamSkillData(MsgGameTeamSkillData* m);
	void        SendMatchTeamNewFormation(MsgTeamNewPlayerFormationPos* m);
	void		send_match_pently_to_all_watch(MsgMatchPentlyResultData* m);
	void		send_arena_matching_success(int,int,int);
	void 		borcast_player_speak(int mid,MsgClientSpeakBrocast* m);
	MsgBase*	CompressMsg(MsgBase*);
	void		RemoveMatch(int mid);
	GServerInfo*	GetMatchRunServer(int);
	GServerInfo*	PickMatchServer();
	GServerInfo*	GetDefaultServer();
	void		gm_command(CMsgEvent* base);
	void 		send_match_info_to_all_watch(MatchInfo* info,MsgBase* msg);
	void		remove_all_watcher(MatchInfo* info, bool need_logout);
	//转发到指定游戏服务器
	void 		forward_to_game_server(MsgBase*,int);
	//广播所有的信息到注册的玩家	//
	void		BrocastAllServer(const char*,int);
	//广播所有的信息到注册的玩家
	void 		brocast_msg_to_match_watcher(int,MsgBase*);

	//GMM...................
	bool do_gm_login(CMsgEvent*,EPollSocket*);

	void set_timer_hander(CGateTimerEventHandler* handler){
		this->_timer_handler = handler;
	}

    int64_t get_run_ms(){return rdtsc()/tick_ms;}

    void on_timeout(timer_manager* timer_mgr);

protected:
	typedef std::map<int,MatchInfo*>::iterator MATCH_WATCH_ITR;
	std::map<int, MatchInfo*>	_match_watcher;
//	omg::ConcurrenceQueue<CMsgEvent,MutexLock,MutexLock>	_msg_queue;
	omg::WRQueue<CMsgEvent,MutexLock>			_msg_queue;
	int		_pass_msg_count;
	static CMsgDispatcher* _m_instance;
	CGateTimerEventHandler*	_timer_handler;
    timer_manager   _timer_mgr;
    int64_t tick_ms;

private:
    template_timer<CMsgDispatcher,&CMsgDispatcher::on_timeout> _dispatcher_timer;

};
#endif /* CMSGDISPATCHER_H_ */
