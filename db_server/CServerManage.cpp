#include "CServerManage.h"

CServerManage* CServerManage::_m_instance;

void GameServerClient::on_timeout(timer_manager* timer_mgr)
{
    if(_connection_status == WAIT_LOGIN || _connection_status == HEART_BEAT_TIME_OUT)
    {
        LOG(INFO)<<"data client check time out in 5's ,should disconnect.";
        fini();
    }
    else
    {
        _timer.set_expired(ServerRun->get_run_ms() + 5000);
        if((_timer_mgr->add_timer(&_timer)) != 0 )
        {
            LOG(INFO)<<"add timer success"; 
        }
    }
}

void GameServerClient::reset()
{
    index = -1;
    _match_list.clear();
    _timer_mgr->del_timer(&_timer);
}

int GameServerClient::on_error()
{
    LOG(INFO)<<"gameserver client disconnet";
    reset();
    fini();
    return 1;
}

int GameServerClient::check_packet_info(char* data,int size,packet_info* info)
{
    cs_head* head = (cs_head*)data; 
    if(size < sizeof(cs_head))
    {
        //message not complete
        return  -1;
    }
    else
    {
        info->size = (int)head->length;
        info->type = (int)head->msgid;
    }

    //message error
    if(info->size <0 || info->size > MAX_MSG_SIZE || info->type < 0 )return -2;
    info->data = data;
    return info->size;
}

int GameServerClient::process_msg(packet_info* packet)
{
    //to some check like heart beat or other
    int packet_type = packet->type;

    int process_ret = 0;
    switch(packet_type)
    {
        case  CS_MSG_SOCCER_PLAYER_REQ:
            do_get_soccer_player_info(packet);
            //process_ret = _packet.decode(packet->data,packet->size);
        default:
            LOG(ERROR)<<"unknown message ";

    }
    return 1;

}

int GameServerClient::do_get_soccer_player_info(const packet_info* packet)
{
    cs_soccer_player_request request; 
    if(request.decode(packet->data,packet->size) != packet->size)return -1;
    LOG(INFO)<<"Message get soccer player info:size  "<<packet->size;
    _connection_status = ALREADY_LOGIN;
}



