#include "CServerManage.h"

CServerManage* CServerManage::_m_instance;

void GameServerClient::on_timeout(timer_manager* timer_mgr)
{
    LOG(INFO)<<"check time out";
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
