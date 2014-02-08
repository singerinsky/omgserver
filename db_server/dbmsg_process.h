#ifndef _DBMSG_PROCESS_
#define _DBMSG_PROCESS_
#include "../common/IMsgProcess.h"

class dbmsg_process:public msg_process
{
    public:
        void msg_process(MsgBase*,socket_client*);
};

#endif
