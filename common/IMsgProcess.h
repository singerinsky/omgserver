#ifndef _IMSG_PROCESS_
#define _IMSG_PROCESS_

class socket_client; 
class MsgBase;
class msg_process
{
    public:
        virtual void process_msg(MsgBase*,socket_client*) = 0;
};
#endif
