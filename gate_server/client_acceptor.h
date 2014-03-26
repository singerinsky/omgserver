#ifndef _CLIENT_ACCEPTOR_
#define _CLIENT_ACCEPTOR_

#include "../common/head.h"
#include "../net/epoll_accepter.h"
#include "../net/epoll_handler.h"

class client_acceptor: public epoll_accepter
{
    public:
	    int on_connection(int nfd,sockaddr* addr);
    private:
        
};

int client_acceptor::on_connection(int nfd,sockaddr* addr)
{
    LOG(INFO)<<"GET CLENT Connect";
}


#endif
