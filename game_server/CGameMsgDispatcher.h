/*
 * CGameMsgDispatcher.h
 *
 *  Created on: 2012-2-2
 *      Author: guanlei
 */

#ifndef CGAMEMSGDISPATCHER_H_
#define CGAMEMSGDISPATCHER_H_

#include "../common/head.h"
#include "../common/queue.h"
#include "../common/lock.h"
#include "../common/CThreadManage.h"
#include "../common/Timer.h"
#include "../common/MD5.h"
#include "../net/thread.h"
#include "../net/client_socket.h"
#include "../net/IMsgDispatcher.h"
#include "../net/IConnection.h"
#include "GateConManager.h"

#include "zlib.h"

#include "CMatchManager.h"
#include "RunMatchJob.h"
#include "match_engine_events.h"
#include "match.h"
#include "msg.h"
#include "CGameTimerEventHandler.h"
#include <sstream>
#include "MatchProcessThread.h"

using namespace omg;
extern char* public_key;

//std::map<int,GameServerInfo*>	all_game_server;
class EPollSocket;
class CGameMsgDispatcher:public IMsgDispatcher, public Thread {
public:
	CGameMsgDispatcher(int process_number,const char* name=NULL):Thread(name){
		_pass_msg_count++;
		_is_final = false;
		init_rst(process_number);
		LOG(INFO)<<process_number;
	}
	virtual ~CGameMsgDispatcher();
	virtual void*	on_run(void);	
public:
//	void	transfer_msg_to_gs(int server_index,StringBuffer *msg);
	void init_rst(int process_number){
		LOG(INFO)<<process_number;
		for(int count = 0;count<process_number;count++){
			_process_list.push_back(new MatchProcessThread(count));
			_process_list[count]->start();
			LOG(INFO)<<"开启比赛处理线程"<<count;
		}
	}


	virtual	bool	add_msg_to_queue(CMsgEvent*,EPollSocket*);
	virtual void 	dispatch_msg();
	bool		check_msg_valide(CMsgEvent*);
	void		AddMatchStatusCheckTimeEvent(int,int);
	void		CheckMatchStatus(int);
	void		BrocastAllGateServer(MsgBase*);
	void 		SignGateMatchInfo(Match*,IConnection*);
	void 		set_connection_to_gate(IConnection* conn){
				_connection_to_gate = conn;
			}
	void 		set_connection_to_db(CConnectToDB* conn){
				_connection_to_db = conn;
			}
	MsgBase* CompressMsg(MsgBase*);
	int VerifyOperate(int mid,int cid,int operate_type,int zeit_time,const char* key,const char* code);
	int VerifyChangePlayerOperate(int mid,int cid,int pid,int operate_type,int zeit_time,const char* key,const char* code);
	bool is_final(){
		return _is_final;
	}	

protected:
	//omg::ConcurrenceQueue<CMsgEvent,MutexLock,MutexLock>	_msg_queue;
	omg::WRQueue<CMsgEvent,MutexLock>	_msg_queue;
	int					_pass_msg_count;
	IConnection*		_connection_to_gate;
	CConnectToDB*		_connection_to_db;
	//is game world end
	bool			_is_final;

	//vector of process
	std::vector<MatchProcessThread*> _process_list;

};
#endif /* CMSGDISPATCHER_H_ */
