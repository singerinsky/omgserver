#ifndef _IMSG_DISPATCHER_
#define _IMSG_DISPATCHER_

struct CMsgEvent;
class EPollSocket;
class IMsgDispatcher{
public:
	//virtual ~IMsgDispatcher()=0;
	virtual	bool add_msg_to_queue(CMsgEvent*,EPollSocket* socket=0)=0;
	virtual void dispatch_msg()=0; 

};


#endif
