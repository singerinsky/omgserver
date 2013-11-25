/*
 * RunMatchJob.h
 *
 *  Created on: Mar 12, 2012
 *      Author: guanlei
 */

#ifndef RUNMATCHJOB_H_
#define RUNMATCHJOB_H_
#include "match.h"
#include "CMatchManager.h"
#include "../net/IConnection.h"
#include "../net/IMsgDispatcher.h"
#include "match_recorder.h"
#include "../common/IJob.h"
#include "CGameTimerEventHandler.h"
#include "../common/Timer.h"
#include "ConnectDBServerJob.h"
#include <sstream>

class RunMatchJob: public omg::IJob {
public:
	RunMatchJob(Match* match,CConnectToDB* PConnectionToDb);
	virtual ~RunMatchJob();

public:
	void ExecuteJob();
	Match* _match;
	int  get_job_id(){
		return _match->_match_id;
	}

protected:
	//导出所有的比赛数据
	void 	ExportAllMatchData(MatchRecorder& recoder,int pITimeScale,int);
	//加入下次自动的执行事件
	void	AddNextMatchMoveEvent(int,int);
	void 	SendNewTeamFormationPos(int);
	void	SendMatchEndMsg();
	CConnectToDB*	_connection_to_db;
	IMsgDispatcher*	_msg_dispatcher;
};

#endif /* RUNMATCHJOB_H_ */
