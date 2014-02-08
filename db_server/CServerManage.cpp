#include "CServerManage.h"

CServerManage* CServerManage::_m_instance;

void GameServerClient::on_timeout(timer_manager* timer_mgr)
{
    LOG(INFO)<<"check time out";
}

void GameServerClient::reset()
{
    _timer_mgr->del_timer(&_timer);
}

int GameServerClient::on_error()
{
    LOG(INFO)<<"gameserver client disconnet";
    reset();

    fini();
    return 1;
}
