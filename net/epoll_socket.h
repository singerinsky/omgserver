#ifndef _EPOLL_SOCKET_
#define _EPOLL_SOCKET_
#include "../common/head.h"
#include "msg.h"
#include "../common/omg_type.h"
#include "../common/lock.h"
#include "IMsgDispatcher.h"
#include "packet.h"

using namespace omg;

enum{
	CONN_UNVRIFY = 1,//未验证
	CONN_VRIFY,	//验证OK
	WILL_DEL};	//待删除

struct EPollSocket {
	enum {
		LISTEN_SOCKET, CONNECT_SOCKET, DATA_SOCKET
	};

	EPollSocket(IMsgDispatcher* dispatcher) {
		fd = 0;
		this->_conn_state = CONN_UNVRIFY;
        _lock.init();
        _msg_dispatcher = dispatcher;
	}

    EPollSocket(int sock_fd,int sock_type,int epoll_mod,IMsgDispatcher* dispatcher,int ep_fd)
    {
        fd = sock_fd; 
        _socket_type = sock_type;
        _epoll_mod = epoll_mod;
        _lock.init();
        _msg_dispatcher = dispatcher;
        _epoll_fd = ep_fd;
    }

	~EPollSocket(void) {
		::epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
		close(fd);
	}


	int on_read()
    {
        char msg_buffer[2048] = {0};
        int len = 0;
        while(true){
            len = recv(fd,msg_buffer,2048,0);
            if(len ==0) {
                LOG(INFO)<<"client close socket .......";
                //do_close(socket);
                return -1;
            }

            if(len == -1)
            {
                if(errno != EAGAIN && errno != EINTR)
                {
                    LOG(ERROR)<<"system error,close client"; 
                    //do_close(this);
                    return -1;
                }
            }

            if(len > 0 )
            {
                _recv_buffer.insert(_recv_buffer.end(),msg_buffer,msg_buffer+len); 
                int msg_len = -1;
                while((_recv_buffer.size()>0 ) && (msg_len = check_msg_complete(_recv_buffer.data(),_recv_buffer.size())) != -1){
                    if(msg_len > 12*1024 || msg_len < 0 )
                    {
                        return -1;
                    }
                    char* msg_data = new char[msg_len];
                    memcpy(msg_data,_recv_buffer.data(),msg_len);
                    MsgBase* msg_base = (MsgBase*)msg_data;
                    CMsgEvent* event = new CMsgEvent();
                    event->_msg_type = msg_base->msg_type; 
                    event->_client_id._fd = fd;
                    event->_client_id._timestamp = time(NULL);
                    event->_msg_base = msg_base;
                    _recv_buffer.erase(_recv_buffer.begin(),_recv_buffer.begin()+msg_len);
                    bool add_rst = _msg_dispatcher->add_msg_to_queue(event,this);
                    if(add_rst == false)
                    {
                        delete[] msg_data;
                        return -1;
                    }
                }
            } 
        }
        return 0;
    }



    int on_write()
    {
       if(_send_buffer.size() <= 0 )
       {
            return 0;
       }
         //send lock 
        ScopeLock<MutexLock> lock(_lock);
       
        //send unlock 
		int rst = ::send(fd,_send_buffer.data(),_send_buffer.size(),0);
		if(rst < 0 ){
			if(errno == EAGAIN || errno== EINTR){//缓冲区满了。
				return 0;
			}
            //error should disconnect
            return -1;
		}
        //have data not send ,register write epoll event
        if(rst < (int)_send_buffer.size())
        {
             mod_epoll_status(EPOLLIN|EPOLLOUT); 
        }
    
        if(rst == (int)_send_buffer.size())
        {
            mod_epoll_status(EPOLLIN);
        }
        if(rst != 0){
            _send_buffer.erase(_send_buffer.begin(),_send_buffer.begin()+rst);
        }

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
        //have data not send ,register write epoll event
        if(rst < send_size)
        {
             mod_epoll_status(EPOLLIN|EPOLLOUT); 
             _send_buffer.insert(_send_buffer.end(),data_head + rst,data_head + send_size);
        }
		
        return 0;
	}


    int send_packet_msg(packet* p)
    {
       int size = p->encode_size();
       if(size < 1)return -1;
       char buffer[1024*8] = {0};
       size = p->encode(buffer,1024*8);
       if(size < 1)return -1;
       return send_msg(buffer,size);   
    }
    

    
    int mod_epoll_status(int status)
    {
        epoll_event event = {0};
        event.events = status;
        event.events |= _epoll_mod;
        event.data.ptr = this;
        return ::epoll_ctl(_epoll_fd,EPOLL_CTL_MOD,fd,&event); 
    }

    int add_epoll_event(int status)
    {
        epoll_event event = {0};
        event.events = status;
        event.events |= _epoll_mod;
        event.data.ptr = this;
        return ::epoll_ctl(_epoll_fd,EPOLL_CTL_ADD,fd,&event); 
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

    int check_msg_complete(char *data_head,int size)
    {
        MsgBase* msg_head = (MsgBase*)data_head;
        if(size >= msg_head->msg_size)
        {
            return msg_head->msg_size;
        }
        return -1;
    }

    EPOLL_SOCKET_FD _epoll_fd;
    int             _epoll_mod;
    INT fd;
    INT _socket_type;
    INT	_conn_state;
    std::string 	_ip_str;
    int				_port;
    MutexLock       _lock;
    sockaddr_in		_sin;
    std::vector<char>   _recv_buffer;
    std::vector<char>   _send_buffer;
    IMsgDispatcher*     _msg_dispatcher;
};
#endif
