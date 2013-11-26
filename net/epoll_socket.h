#ifndef _EPOLL_SOCKET_
#define _EPOLL_SOCKET_
#include "../common/head.h"
#include "msg.h"
#include "../common/omg_type.h"
#include "../common/lock.h"
using namespace omg;

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
        _recv_buffer.resize(32*1024);
        _send_buffer.resize(32*1024);
        _lock.init();
	}

    EPollSocket(int sock_fd,int sock_type)
    {
        fd = sock_fd; 
        _socket_type = sock_type;
        _recv_buffer.resize(32*1024);
        _send_buffer.resize(32*1024);
        _lock.init();
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

    int on_write()
    {
       if(_send_buffer.size() <= 0 )
       {
            return 0;
       }
    
       int rst  = send_msg(_send_buffer.data(),_send_buffer.size());

       return rst; 
    }

    int send_msg(const MsgBase* msg)
    {
       return send_msg((const char*)msg,msg->msg_size);
    }


	int send_msg(const char* data_head,int send_size){
        //if send buffer has data ,push data into buffer
        //send lock 
        ScopeLock<MutexLock> lock(_lock);
        if(_send_buffer.size() > 0 )
        {
            _send_buffer.insert(_send_buffer.end(),data_head,data_head+send_size);
            mod_epoll_status(EPOLLIN|EPOLLOUT);
            return 0;
        }
       //send unlock 
		int rst = ::send(fd,data_head,send_size,0);
		if(rst < 0 ){
			if(errno == EAGAIN || errno== EINTR){//缓冲区满了。
				return 0;
			}
            //error should disconnect
            return -1;
		}
        _send_buffer.erase(_send_buffer.begin(),_send_buffer.begin()+rst);
        //have data not send ,register write epoll event
        if(rst < send_size)
        {
             mod_epoll_status(EPOLLIN|EPOLLOUT); 
        }
		
        return 0;
	}

    
    void mod_epoll_status(int status)
    {
        epoll_event event = {0};
        event.events = status;
        event.data.ptr = this;
        ::epoll_ctl(_epoll_fd,EPOLL_CTL_MOD,fd,&event); 
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
	INT _socket_type;
	INT	_conn_state;
	std::string 	_ip_str;
	int				_port;
    MutexLock       _lock;
	sockaddr_in		_sin;
    std::vector<char>   _recv_buffer;
    std::vector<char>   _send_buffer;
};
#endif
