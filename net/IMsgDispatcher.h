#ifndef _IMSG_DISPATCHER_
#define _IMSG_DISPATCHER_

struct CMsgEvent;
class io_handler;
class IMsgDispatcher{
public:
	//virtual ~IMsgDispatcher()=0;
	virtual	bool add_msg_to_queue(CMsgEvent*,io_handler* handler = 0)=0;
	virtual void dispatch_msg()=0; 

};


#endif
