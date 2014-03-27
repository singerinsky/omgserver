#ifndef _CLIENT_ACCEPTOR_
#define _CLIENT_ACCEPTOR_

#include "../common/head.h"
#include "../net/epoll_accepter.h"
#include "../net/epoll_handler.h"
#include "GateWayPlayer.h"

using namespace omg;

class client_accepter: public epoll_accepter
{
    public:
        client_accepter(epoll_handler* handler):epoll_accepter(handler)
        {
            _epoll_handler = handler;
        }
	    int on_connection(int nfd,sockaddr* addr);
        int on_error();
    private:
        epoll_handler* _epoll_handler;
        
};

int client_accepter::on_connection(int nfd,sockaddr* addr)
{
    LOG(INFO)<<"GET CLENT Connect";
    GateWayPlayer* player = new GateWayPlayer(nfd,*(sockaddr_in*)addr,_epoll_handler,ServerRun->get_timer_mgr());
    player->init_timer();
}

int client_accepter::on_error()
{
    LOG(INFO)<<"error of epoll acceptor!";
}

#endif
