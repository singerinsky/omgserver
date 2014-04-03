#include "server_conns.h"
#include "../message/message_define.h"

int  db_connection::process_msg(packet_info* info)
{
    int type = info->type;
    switch(type)
    {
        case CS_MSG_CLIENT_LOGIN_REP:
            do_login_response(info);              
            break;
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
        if(rst != 1)
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

void db_connection::do_login_response(packet_info* info)
{
   cs_client_login_response response;
   if(!response.decode(info->data,info->size))
   {
        LOG(ERROR)<<"decode failed ..."; 
        return;
   }

   LOG(INFO)<<"login name is "<<response.body.player_name();
   LOG(INFO)<<"login id is "<<response.body.player_id();
}
