/*
 * CEventHandler.h
 *
 *  Created on: 2012-2-2
 *      Author: guanlei
 */

#ifndef C_TIMER_EVENT_H_
#define C_TIMER_EVENT_H_

#include "../common/head.h"
#include "../net/IMsgDispatcher.h"
#include "../common/queue.h"
#include "../common/lock.h"
#include "../common/CTimerEventHandler.h"
#include "../common/Timer.h"
#include "GateGameMsg.h"

using namespace omg;
class CGateTimerEventHandler:public CTimerEventHandler{
public:
	CGateTimerEventHandler(IMsgDispatcher* pDispatcher,int time_check=1):CTimerEventHandler(pDispatcher,time_check){

		add_arena_event();
	}
	virtual ~CGateTimerEventHandler();
public:
	void		check_timer();
	//添加等待挑战的事件
	void 		add_arena_event();
};
#endif /* CMSGDISPATCHER_H_ */
