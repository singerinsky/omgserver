#ifndef _CDBMSG_DISPATCHER_
#define CDBMSG_DISPATCHER
#include "../common/head.h"
#include "../net/IMsgDispatcher.h"
#include "../common/CThreadManage.h"
#include "../net/thread.h"
#include "CDBTaskManage.h"
#include "DBEvent.h"
#include "CServerManage.h"

#define _DEBUG_SERVER_INFO
using namespace omg;
class CDBMsgDispatcher: public IMsgDispatcher, public Thread{
public:
	CDBMsgDispatcher();
	~CDBMsgDispatcher();
	bool add_msg_to_queue(CMsgEvent*,EPollSocket*);
	void dispatch_msg();
	virtual void*	on_run(void);
private:
	omg::WRQueue<CMsgEvent,MutexLock>	_msg_queue;
};



#endif
