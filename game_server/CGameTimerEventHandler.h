/*
 * CEventHandler.h
 *
 *  Created on: 2012-2-2
 *      Author: guanlei
 */

#ifndef C_GAME_TIMER_EVENT_H_
#define C_GAME_TIMER_EVENT_H_

#include "../common/head.h"
#include "../net/IMsgDispatcher.h"
#include "../common/queue.h"
#include "../common/lock.h"
#include "../common/CTimerEventHandler.h"
#include "msg.h"
#include "match.h"

using namespace omg;
class CGameTimerEventHandler: public CTimerEventHandler{
public:
	CGameTimerEventHandler(IMsgDispatcher* pDispatcher,int time_check=1):CTimerEventHandler(pDispatcher,1){
	}
	virtual ~CGameTimerEventHandler();
protected:
	void		check_timer();
};
#endif /* CMSGDISPATCHER_H_ */
