#include "server_conns.h"
#include "../message/message_define.h"
//#include "../message/role_info.pb.h"
#include "../orm/role_info.h"
#include "role.h"
#include "gate_server.h"

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
           _conn_timer.set_expired(ServerRun->get_run_ms() + 5000);  
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
   game_role* role = new game_role(GlobalServer->get_db_connection());
   role_info& role_data = role->get_role_info_data();
   role_data.load_from_pb(response.body.role_data());

   int add_rst = role_manager::get_instance()->add_role(role,role->get_role_info_data().get_role_id());
   LOG(INFO)<<"GET role data info"<<role->get_role_info_data().get_tid();
   role->get_role_info_data().set_tid(time(NULL));
}

void db_connection::do_data_update(sql_binder* binder,int key)
{
    char sql_buff[8192] = {0}; 
    if(!binder->is_dirty())
        return;
    int buff_left = binder->sql_update(sql_buff,8192);
    if(buff_left <= 0)
    {
        LOG(INFO)<<"sql too long"<<key; 
        return ;
    }
    sql_buff[buff_left] = '\0';
    LOG(INFO)<<"do update sql"<<sql_buff;

    cs_data_common_update_ntf ntf;
    ntf.body.set_key(key);    
    ntf.body.set_sql_str(sql_buff);    
    send_packet_msg(&ntf);
    binder->clear_dirty();
}
