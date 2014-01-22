#ifndef _CDBMSG_DISPATCHER_
#define CDBMSG_DISPATCHER
#include "../common/head.h"
#include "../net/IMsgDispatcher.h"
#include "../common/CThreadManage.h"
#include "../net/thread.h"
#include "CDBTaskManage.h"
#include "DBEvent.h"
#include "CServerManage.h"
#include "../common/system_util.h"
#include "../common/time_util.h"

#define _DEBUG_SERVER_INFO
using namespace omg;
class CDBMsgDispatcher: public IMsgDispatcher, public Thread{
public:
	CDBMsgDispatcher();
	~CDBMsgDispatcher();
	bool add_msg_to_queue(CMsgEvent*,EPollSocket*);
	void dispatch_msg();
	virtual void*	on_run(void);
    int64_t get_run_ms(){return rdtsc()/_tick_ms;}
private:
	omg::WRQueue<CMsgEvent,MutexLock>	_msg_queue;
    int64_t _ms_before_run;
    int64_t _tick_ms;
};



#endif
