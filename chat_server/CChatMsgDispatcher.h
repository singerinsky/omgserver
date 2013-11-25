/*
 * CChatMsgDispatcher.h
 *
 *  Created on: 2012-7-17
 *      Author: guanlei
 */

#ifndef CCHATMSGDISPATCHER_H_
#define CCHATMSGDISPATCHER_H_

#include "../common/concurrence_queue.h"
#include "../net/IMsgDispatcher.h"
#include "../net/msg.h"
#include "../net/epoll_socket.h"
#include "../net/thread.h"
#include "Message.h"


using namespace omg;

class CChatMsgDispatcher:public IMsgDispatcher,public Thread {
public:
			CChatMsgDispatcher();
	virtual 	~CChatMsgDispatcher();
	virtual	void 	add_msg_to_queue(CMsgEvent*,EPollSocket* socket=0);
	virtual void	dispatch_msg();
	virtual void*	on_run(void);
	void 		do_login(CMsgEvent* event,EPollSocket* socket);
	bool 		check_msg_validae(CMsgEvent* event,EPollSocket* socket);
private:
	omg::ConcurrenceQueue<CMsgEvent,MutexLock,MutexLock>	_msg_queue;
};

#endif /* CCHATMSGDISPATCHER_H_ */
