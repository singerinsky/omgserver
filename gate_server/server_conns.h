#ifndef _DB_CONNECTION_H
#define _DB_CONNECTION_H
#include "../net/socketclient.h"
#include "../common/timer_manager.h"
#include "../common/server_application.h"

using namespace omg;

class db_connection: public socket_client
{
    public:
        db_connection(std::string ip,int port,epoll_handler* handler):socket_client(ip,port,handler)
        {
        }
        virtual int  process_msg(packet_info* info);
        void     on_timeout(timer_manager* time_mgr);
        virtual int on_error();
        void    forward_server_packet(packet_info* info);
    private:
        template_timer<db_connection,&db_connection::on_timeout> _conn_timer;
};
#endif
