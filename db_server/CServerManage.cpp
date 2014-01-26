#include "CServerManage.h"

CServerManage* CServerManage::_m_instance;

void GameServerClient::on_timeout(timer_manager* timer_mgr)
{
    LOG(INFO)<<"check time out";
}

