#include "server_conns.h"
#include "../message/message_define.h"

int  db_connection::process_msg(packet_info* info)
{
    int type = info->type;
    switch(type)
    {
        default:
            LOG(ERROR)<<"unknown message not handler"<<type;
    }
}

void db_connection::on_timeout(timer_manager* time_mgr)
{
    if(!is_connected())
    {
        LOG(INFO)<<"do reconnect";
        int rst = re_connect();    
        if(rst != 0)
        {
           _conn_timer.set_expired(ServerRun->get_run_ms()+5000);  
           if(time_mgr->add_timer(&_conn_timer) != 0 )
           {
                LOG(ERROR)<<"error add timer"; 
           }
        }
    }
}

int db_connection::on_error()
{
    LOG(ERROR)<<"db connection disconnect,reconnect in sec's";
    set_state(CONN_UNCONNECT); 
    on_timeout(ServerRun->get_timer_mgr());
    return 1;
}

void db_connection::forward_server_packet(packet_info* info)
{
    send_msg(info->data,info->size);
}
 
void db_connection::send_register_message()
{
    cs_gate_register_request request;
    request.body.set_server_index(1);
    send_packet_msg(&request);
}
