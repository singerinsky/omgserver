#include "../net/socketclient.h"
#include "../common/timer_manager.h"
#include "../common/template_timer.h"

class db_connection: public socket_client
{
    public:
        virtual int  process_msg(packet_info* info);
        int     on_timeout(timer_manager* time_mgr);
    private:
        template_timer<db_connection,db_connection::on_timeout> _conn_timer;
};

int db_connection::on_timeout(timer_manager* timer_mgr)
{
    connect();
    init();
    if(!is_connected())
    {
        _conn_timer.set_owner(this);    
        _conn_timer.set_expired(ServerRun->get_run_ms() + 5000);
        timer_mgr->add_timer(&_conn_timer);
    }
    return 1;
}

int db_connection::process_msg(packet_info* info)
{
    int msg_type = info->type;
    switch(msg_type)
    {
         
        default:
            LOG(ERROR)<<"unknown message"<<msg_type;
    }
    return 0;
}


