#ifndef _EPOLL_ACCEPTER 
#define _EPOLL_ACCEPTER

#include "../common/head.h"
#include "../common/omg_type.h"
#include "packet.h"
#include "net_util.h"
#include "IConnection.h"

using namespace omg;
#define MAX_ACCEPT_ONCE 256

class epoll_accepter:public io_handler {

public:
	epoll_accepter() {
		_fd = 0;
	}

    virtual	~epoll_accepter(void) {
        _fd = -1;
		close(_fd);
	}

public:
	int init(std::string ip_str,int port)
	{
        _ip_str = ip_str;
        _port = port;
		init_sa_in(&_sin,_ip_str.c_str(),_port);
		_fd = start_tcp_service(&_sin);
		LOG_IF(INFO,_fd > 0)<<"start listening in"<<_port;
        //handler->add_event_handler(_fd,this);
		return _fd;
	}

    virtual void on_read()
    {
        LOG(INFO)<<"acceptor recving....";
    	struct sockaddr_in sin;
		socklen_t len = sizeof(sockaddr_in);
		int nfd;
		for(int i = 0;i<MAX_ACCEPT_ONCE;i++)
		{
			nfd = accept(_fd,(struct sockaddr*)&sin,&len);
			if(nfd >= 0)
			{
				on_connection(nfd,(struct sockaddr*)&sin);
			}
			else
			{
				if(errno == EAGAIN || errno ==EMFILE || errno ==ENFILE) break ;
				else if ( errno == EINTR || errno ==ECONNABORTED ) continue ;
				else on_error();
			}
    	}
    }



    virtual void on_write()
    {
    }

	sockaddr_in get_client_ip_address(){
		return _sin;
	}

	std::string get_client_ip_str(){
		return _ip_str;
	}

	void dump_client_ip_info(){
		LOG(INFO)<<"client :"<<_ip_str.c_str()<<":"<<_port;
	}

	int get_sock_fd()
	{
		return _fd;
	}
public:
	virtual int on_connection(int nfd,sockaddr* addr) = 0;

    virtual void on_error() = 0;

private:
	std::string 	_ip_str;
    int				_port;
    sockaddr_in		_sin;
    int 			_fd;
};
#endif
