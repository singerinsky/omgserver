/*
 * CChatMsgDispatcher.cpp
 *
 *  Created on: 2012-7-17
 *      Author: guanlei
 */

#include "CChatMsgDispatcher.h"

CChatMsgDispatcher::CChatMsgDispatcher() {
	// TODO Auto-generated constructor stub

}

CChatMsgDispatcher::~CChatMsgDispatcher() {
	// TODO Auto-generated destructor stub
}

void CChatMsgDispatcher::add_msg_to_queue(CMsgEvent* msg_event,EPollSocket* socket){
	if (check_msg_validae(msg_event,socket)) {
		if (msg_event->_msg_type == MSG_TYPE_LOGIN) {
			do_login(msg_event, socket);
			return;
		}//else if(msg_event->_msg_type == MSG_TYPE_GM_LOGIN){
		//do_gm_login(msg_event,socket);
		//	return;
		//}
		else {
			this->_msg_queue.enqueue(msg_event);
		}
	} else {
		VLOG(3)<<"error msg.......";
	}



}

void CChatMsgDispatcher::dispatch_msg(){

	CMsgEvent* event = _msg_queue.dequeue();
	if (event != NULL) {
		int msg_type = event->_msg_type;
		switch (msg_type) {
			case MSG_LOGIN_CHAT_CHANNEL :
				{
					ChaterLoginChatChannel* msg = (ChaterLoginChatChannel*)event->_msg_base;					
					DLOG(INFO)<<msg->login_chat_channel_id;
					
				}
				break;
			case CHAT_MSG:
				{
				}
				break;
			default:
				LOG(ERROR)<<"Known message!";
		}
	}
}


void* CChatMsgDispatcher::on_run(){
	while (1) {
		dispatch_msg();
	}
	return NULL;
}

void CChatMsgDispatcher::do_login(CMsgEvent* event,EPollSocket* socket){


}

bool CChatMsgDispatcher::check_msg_validae(CMsgEvent* event,EPollSocket* socket){
	return true;
}
