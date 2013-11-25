/*
 * CEventHandler.cpp
 *
 *  Created on: 2012-2-2
 *      Author: guanlei
 */

#include "CGameTimerEventHandler.h"

CGameTimerEventHandler::~CGameTimerEventHandler() {
	// TODO Auto-generated destructor stub
}

void CGameTimerEventHandler::check_timer(){
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
				if(object.type == MATCH_MOVE){
					CMsgEvent *event = new CMsgEvent();
					MsgGameRunMatch *msg = new MsgGameRunMatch();
					msg->mid = object.param;
					event->_msg_type = msg->msg_type;
					event->_msg_base = msg;
					_msg_dispatcher->add_msg_to_queue(event);
				}else if(object.type == MATCH_STATUS_CHECK){
					CMsgEvent* event = new CMsgEvent();
					MsgGameMatchStatusCheck * msg = new MsgGameMatchStatusCheck();
					msg->mid = object.param;
					event->_msg_type = msg->msg_type;
					event->_msg_base = msg;
					_msg_dispatcher->add_msg_to_queue(event);
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

//void CEventHandler::transfer_msg_to_gs(int server_index, StringBuffer* buffer){

//}








