/*
 * DBAccepter.cpp
 *
 *  Created on: 2014年1月20日
 *      Author: guanlei
 */

#include "DBAccepter.h"
#include "CServerManage.h"

db_accepter::~db_accepter() {
	// TODO Auto-generated destructor stub
}

int db_accepter::on_connection(int nfd,sockaddr* addr)
{
	LOG(INFO)<<"receive a new connection!";
    GameServerClient* client = new GameServerClient(nfd,*(sockaddr_in*)addr,get_epoll_handler(),get_msg_dispatcher(),ServerRun->get_timer_mgr());
    
    int rst =  client->init();
    if(rst == -1)return -1;
	return 1;
}
