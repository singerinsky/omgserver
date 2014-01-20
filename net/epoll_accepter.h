#ifndef _EPOLL_ACCEPTER
#define _EPOLL_ACCEPTER

#include "../common/head.h"
#include "../common/omg_type.h"
#include "packet.h"
#include "net_util.h"


using namespace omg;
#define MAX_ACCEPT_ONCE 256
class epoll_accepter:public io_handler {

	epoll_accepter(std::string ip_str,int port) {
		_fd = 0;
		_ip_str = ip_str;
		_port = port;
	}

	~epoll_accepter(void) {
		::epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, _fd, NULL);
		close(_fd);
	}

	int init(epoll_handler& handler)
	{
		init_sa_in(&_sin,_ip_str.c_str(),_port);
		_fd = start_tcp_service(&_sin);
		handler.add_event_handler(_fd,this);
		return _fd;
	}

    void on_read()
    {
    	struct sockaddr_in sin;
		socklen_t len = sizeof(sockaddr_in);
		EPollSocket *socket_client = NULL;
		int nfd;

		for(int i = 0;i<MAX_ACCEPT_ONCE;i++)
		{
			nfd = accept(_fd,(struct sockaddr*)&sin,&len));
			if(nfd > =0 )
			{
				on_connection(nfd,(struct sockaddr*)&sin);
			}
			else
			{
				if(errno == EAGAIN || errno ==EMFILE || errno ==ENFILE) break ;
				else if ( errno == EINTR || errno ==ECONNABORTED ) continue ;
				else on_error(_fd);
			}
    	}
    }



    int on_write()
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
public:
	virtual int on_connection(int nfd,sockaddr* addr) = 0;


private:
	std::string 	_ip_str;
    int				_port;
    sockaddr_in		_sin;
    int 			_fd;
};
#endif
