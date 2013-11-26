#ifndef _EPOLL_SOCKET_
#define _EPOLL_SOCKET_
#include "../common/head.h"
#include "msg.h"
#include "../common/omg_type.h"

enum{
	CONN_UNVRIFY = 1,//未验证
	CONN_VRIFY,	//验证OK
	WILL_DEL};	//待删除

struct EPollSocket {
	enum {
		LISTEN_SOCKET, CONNECT_SOCKET, DATA_SOCKET
	};

	EPollSocket(void) {
		fd = 0;
		this->_conn_state = CONN_UNVRIFY;
	}

    EPollSocket(int sock_type)
    {
        this->socket_type = sock_type;
    }

	~EPollSocket(void) {
		::epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
		close(fd);
	}

	INT set_nodelay(bool nodelay) {
		assert(fd > 0);

		INT flag;
		if (nodelay) {
			flag = 1;
		} else {
			flag = 0;
		}

		INT rv = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));

		return rv;
	}

	INT set_reuseaddr(bool reuse) {
		assert(fd > 0);
		INT flag;

		if (reuse) {
			flag = 1;
		} else {
			flag = 0;
		}

		INT rv = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

		return rv;
	}

	INT set_blocking(bool blocking) {
		assert(fd > 0);

		int flag = fcntl(fd, F_GETFL);
		if (flag == -1) {
			return -1;
		}

		if (blocking) {
			flag &= (~O_NONBLOCK);
		} else {
			flag |= O_NONBLOCK;
		}

		INT rv = fcntl(fd, F_SETFL, flag);

		return rv;
	}

	int send_msg(const MsgBase* base){
		//TODO need more work
		int data_has_send = 0;
		char* data_head = (char*)base;
		int timeout = 0;
		while(data_has_send < base->msg_size){
			int rst = ::send(fd,data_head+data_has_send,base->msg_size - data_has_send,0);
			if(rst == -1){
				if(errno == EAGAIN){//缓冲区满了。
					timeout++;
					if(timeout> 10){
						return -1;
					}else{
						continue;
					}
				}
				return -1;
			}
			data_has_send += rst;
		}
		return data_has_send;
	}

	void set_client_ip_address(sockaddr_in& sin){
		_sin = sin;
		_ip_str = inet_ntoa(_sin.sin_addr);
		_port 	=_sin.sin_port;
	};

	sockaddr_in get_client_ip_address(){
		return _sin;
	}

	std::string get_client_ip_str(){
		return _ip_str;
	}

	void dump_client_ip_info(){
		LOG(INFO)<<"client :"<<_ip_str.c_str()<<":"<<_port;
	}

	void update_socket_state(int state){
		_conn_state = state;
	}

	int get_socket_state(){
		return _conn_state;
	}

	EPOLL_SOCKET_FD _epoll_fd;
	INT fd;
	INT type;
	INT	_conn_state;
	std::string 	_ip_str;
	int				_port;
	sockaddr_in		_sin;
};
#endif
