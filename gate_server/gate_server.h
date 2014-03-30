#ifndef _GATE_SERVER_G_
#define _GATE_SERVER_G_

#include "../common/server_application.h"
#include "server_conns.h"

using namespace omg;

class GateServerGlobal
{
    public:
        bool init(epoll_handler*);
        static GateServerGlobal* get_instance(){
            if(_instance == NULL)
            {
                _instance = new GateServerGlobal(); 
            }
            return _instance;
        }

        bool forward_db_message(packet_info* info)
        {
            if(db_conn != NULL && db_conn->is_connected())
            {
                db_conn->forward_server_packet(info);
                return 1;
            }
            else
            {
                LOG(ERROR)<<"send db message to db error"; 
                return -1;
            }
        }

    public:
        db_connection* db_conn;
    private:
        static GateServerGlobal* _instance;
        epoll_handler* _handler;
};

#define GlobalServer    GateServerGlobal::get_instance()

#endif
