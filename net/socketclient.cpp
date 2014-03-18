/*
 * socketclient.cpp
 *
 *  Created on: 2014年1月24日
 *      Author: guanlei
 */

#include "socketclient.h"
#include "msg.h"
#include "epoll_handler.h"
#include "net_util.h"

namespace omg {

//#define _MSG_BASE_
#define _MSG_PACKET_

socket_client::socket_client(int fd, sockaddr_in& addr, epoll_handler* handler,IMsgDispatcher* dispatcher) {
	// TODO Auto-generated constructor stub
	_socket_fd = fd;
	_conn_state = CONN_UNCONFIRM;
	_lock.init();
	_epoll_handler = handler;
	_conn_id._fd = fd;
	_conn_id._timestamp = time(NULL);
    _sin = addr;
    _msg_dispatcher = dispatcher;
}

socket_client::~socket_client() {
	// TODO Auto-generated destructor stub
}

int socket_client::init()
{
    if(_socket_fd < 0 || _epoll_handler == NULL)return -1;
    set_nodelay(_socket_fd,false);
    set_sock_noblock(_socket_fd,true);
    _epoll_handler->add_event_handler(_socket_fd,this);    
    return 1;
}

void socket_client::fini()
{
    _epoll_handler->del_event_handler(_socket_fd);
    close(_socket_fd);
}


#define MSG_BUFF_SIZE 2048
int socket_client::on_read() {
	char msg_buffer[MSG_BUFF_SIZE] = { 0 };
	int len = 0;
	while (true) {
		len = recv(_socket_fd, msg_buffer, MSG_BUFF_SIZE, 0);
		if (len == 0) {
			LOG(INFO)<<"client close socket .......";
			return -1;
		}

		if (len == -1) {
			if (errno != EAGAIN && errno != EINTR) {
				LOG(ERROR)<<"system error,close client";
				return -1;
			}
		}

		if (len > 0) {
			_recv_buffer.insert(_recv_buffer.end(), msg_buffer,
					msg_buffer + len);
			int msg_len = -1;
			while (_recv_buffer.size() > 0)
			{
#ifdef  _MSG_BASE_ 
				msg_len = check_msg_complete(_recv_buffer.data(),_recv_buffer.size());
                if(msg_len == -1)//message not complete 
                {
                    break; 
                }

				if (msg_len > MAX_MSG_SIZE) {
					return -1;
				}
#endif

#ifdef _MSG_PACKET_
                packet_info packet;
                msg_len = check_packet_info(_recv_buffer.data(),_recv_buffer.size(),&packet);
                if(msg_len < 0 )return msg_len;//error of message decode
                int rst = process_msg(&packet); 

#endif
				char* msg_data = new char[msg_len];
				memcpy(msg_data, _recv_buffer.data(), msg_len);
				MsgBase* msg_base = (MsgBase*) msg_data;
				CMsgEvent* event = new CMsgEvent(msg_base->msg_type, _conn_id,
						msg_base);
				_recv_buffer.erase(_recv_buffer.begin(),
						_recv_buffer.begin() + msg_len);

			    bool add_rst = _msg_dispatcher->add_msg_to_queue(event);
				if (add_rst == false) {
					delete[] msg_data;
					return -1;
				}
			}
		}
	}
	return 0;
}

int socket_client::on_write() {
	if (_send_buffer.size() <= 0) {
		return 0;
	}
	//send lock
	ScopeLock<MutexLock> lock(_lock);

	//send unlock
	int rst = ::send(_socket_fd, _send_buffer.data(), _send_buffer.size(), 0);
        if (rst < 0) {
            if (errno == EAGAIN || errno == EINTR) { //缓冲区满了。
                return 0;
            }
            //error should disconnect
            return -1;
        }
        //have data not send ,register write epoll event
        if (rst < (int) _send_buffer.size()) {
            _epoll_handler->mod_epoll_status(_socket_fd,this,EPOLLIN | EPOLLOUT);
        }

        if (rst == (int) _send_buffer.size()) {
            _epoll_handler->mod_epoll_status (_socket_fd,this,EPOLLIN);
        }
        if (rst != 0) {
            _send_buffer.erase(_send_buffer.begin(), _send_buffer.begin() + rst);
        }

        return rst;
    }

    int socket_client::on_error() {
        return 1;        
    }


    int socket_client::send_msg(const char* data_head, int send_size) {
        //if send buffer has data ,push data into buffer
        //send lock
        ScopeLock<MutexLock> lock(_lock);
        if (_send_buffer.size() > 0) {
		_send_buffer.insert(_send_buffer.end(), data_head,
				data_head + send_size);
		_epoll_handler->mod_epoll_status(_socket_fd,this,EPOLLIN | EPOLLOUT);
		return 0;
	}

	//send unlock
	int rst = ::send(_socket_fd, data_head, send_size, 0);
	if (rst < 0) {
		if (errno == EAGAIN || errno == EINTR) {        
			return 0;
		}
		//error should disconnect
		return -1;
	}
	//have data not send ,register write epoll event
	if (rst < send_size) {
		_epoll_handler->mod_epoll_status(_socket_fd,this,EPOLLIN | EPOLLOUT);
		_send_buffer.insert(_send_buffer.end(), data_head + rst,
				data_head + send_size);
	}

	return 0;
}

int socket_client::send_packet_msg(packet* p) {
	int size = p->encode_size();
	if (size < 1)
		return -1;
	char buffer[1024 * 8] = { 0 };
	size = p->encode(buffer, 1024 * 8);
	if (size < 1)
		return -1;
	return send_msg(buffer, size);
}

int socket_client::check_msg_complete(char *data_head, int size) {
	MsgBase* msg_head = (MsgBase*) data_head;
	if (size >= msg_head->msg_size) {
		return msg_head->msg_size;
	}
	return -1;
}

} /* namespace omg */
