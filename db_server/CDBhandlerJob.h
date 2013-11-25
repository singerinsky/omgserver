/*
 * CDBhandlerJob.h
 *
 *  Created on: 2012-3-16
 *      Author: root
 */

#ifndef CDBHANDLERJOB_H_
#define CDBHANDLERJOB_H_

#include <sstream>
#include "../net/IMsgDispatcher.h"
#include "../common/IJob.h"
#include "../common/lock.h"
#include "../common/queue.h"
#include <mysql++/mysql++.h>
#include "DBConnectionPool.h"
#include "DBEvent.h"
#include "CNpcPlayerCache.h"

using namespace omg;

class CDBQueryhandlerJob: public omg::IJob {
public:
	CDBQueryhandlerJob(DBConnectionPool* pool,IMsgDispatcher* dispatcher,int number):_conn(*pool,true){
		_msg_dispatcher = dispatcher;
		_task_all = 0;
		_task_processed = 0;
		_id = number;
	};
	virtual ~CDBQueryhandlerJob();
	virtual void ExecuteJob();
	void 	AddTask(CMsgEvent *event);
	int		GetTaskInProcess(){
		return _task_all - _task_processed;
	}
	int getId(){
		return _id;
	}
private:
	mysqlpp::ScopedConnection _conn;
	IMsgDispatcher* _msg_dispatcher;
	int  _task_all;
	int  _task_processed;
	int  _id;

private:
	int QueryMatchOperate(int,int,int*,MsgMoveOperator&);
	void QueryFixtureInfo(int,int&,int&,int&,int&,int&);
	int  QueryPlayerAttrInfo(int,MsgPlayerInfo&);
	void GeneralPlayerInfoUnFound(int,MsgPlayerInfo&);
	void UpdateMatchStatus(int);
	void UpdateMatchResultInfo(MsgGameToDbServerMatchEnd*);
	void UpdatePlayersMatchInfo(MsgGameToDbServerPlayerUpdate*);
	void WriteBackMatchEvent(MsgGameEventDBWB*);
	void QueryTeamSkillInfo(int,MsgMoveOperator&);
	int  QueryTeamSkillBuff(int cid,int tactic_id);
	void ModiferNpcTeamAttribute(MsgMoveOperator& msg,int npc_player_rate);
	void StartArenaMatch(MsgMatchArenaStartArena* msg);
	void UpdateGServerInfo(MsgUpdateGServerInfo* msg);

private:
	omg::ConcurrenceQueue<CMsgEvent,omg::MutexLock,omg::NullLock>	_msg_queue;
	//omg::WRQueue<CMsgEvent,omg::MutexLock>	_msg_queue;

};

#endif /* CDBHANDLERJOB_H_ */
