#include "CServerManage.h"

CServerManage* CServerManage::_m_instance;

void GameServerClient::on_timeout(timer_manager* timer_mgr)
{
    LOG(INFO)<<"check time out";
}


int GameServerClient::on_error()
{
    LOG(INFO)<<"gameserver client disconnet";
    fini();
    return 1;
}
