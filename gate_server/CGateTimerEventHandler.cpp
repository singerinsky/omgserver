/*
 * CEventHandler.cpp
 *
 *  Created on: 2012-2-2
 *      Author: guanlei
 */

#include "CGateTimerEventHandler.h"


CGateTimerEventHandler::~CGateTimerEventHandler() {
	// TODO Auto-generated destructor stub
}


void CGateTimerEventHandler::check_timer(){
	_lock.lock();
	std::list<TimerSlot>::iterator itr = _timer_list.begin();
	int	time_now = time(NULL);
	while(itr != _timer_list.end()){
		int time_out = itr->timeout;
		if(time_out<=time_now)//时间到了
		{
			TimerSlot::TimerObjectList::iterator itr_tmp = itr->list.begin();
			while(itr_tmp != itr->list.end()){
				TimerObject object = *itr_tmp;
				if(object.type == MATCH_ARENA_MATCHING){
					_lock.unlock();
					CMsgEvent * event = new CMsgEvent();
					event->_msg_type = MSG_TYPE_CLIENT_DO_ARENA_MATCHING;
					MsgServerArenaDoMatch *msg = new MsgServerArenaDoMatch();
					msg->zeit = time_now;
					event->_msg_base = msg;
					_msg_dispatcher->add_msg_to_queue(event);
					//add_arena_event();
					_lock.lock();
				}

				itr_tmp++;
			}
			
			itr = _timer_list.erase(itr);	
		}else{
			itr++;
		}
	}
	_lock.unlock();
}

void CGateTimerEventHandler::add_arena_event() {
	time_t now;
	time(&now);
	int next_time_scale = 25;
	TimerObject object;
	object.timeout = time(NULL) + next_time_scale;
	object.type = MATCH_ARENA_MATCHING;
	AddTimer(object);
}

