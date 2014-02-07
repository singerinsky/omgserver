#ifndef _EPOLL_HANDLER_H
#define _EPOLL_HANDLER_H
#include "../common/head.h"
#include "thread.h"
#include <glog/logging.h>
#include "msg.h"
#include "IMsgDispatcher.h"
#include "define.h"
#include "IConnection.h"

const int EPOLL_SIZE = 128*1024;
const int MAX_CLIENT = 10240;
#ifndef EPOLLRDHUP
	#define EPOLLRDHUP 0x2000
#endif

namespace omg{
    
    class socket_client;
	class epoll_handler : public Thread
	{
		public:
			epoll_handler(const char *name=NULL) : Thread(name){
				_epoll_create = 0;
                _is_final = true;
			}
			virtual ~epoll_handler();
			bool init_epoll(int epoll_size,const char* ip,int port,bool use_et_mod=false);
			void startListening();
			int  accept_conn(socket_client* s);
			void send_data(socket_client *socket,const char* msg,int msg_len);
			void recv_data(socket_client* socket);
			void do_close(socket_client*);

            int add_event_handler(int fd,io_handler* handler);
            int mod_epoll_status(int fd,io_handler* handler,int event_type);
            int del_event_handler(int fd);

		public:
			virtual void *on_run(void);
		
			void	set_msg_dispatcher(IMsgDispatcher* dispatcher){
				this->_msg_handler = dispatcher;
			}

            virtual void on_connection(int fd,sockaddr* addr);
		protected:
			void do_select();


		private :
			int _epoll_create;
			IMsgDispatcher* _msg_handler;
			epoll_event _events[EPOLL_SIZE];
			int	_port;
			StringBuffer	_ip_buffer;
            int 	_epoll_mod;
            bool    _is_final; 
            io_handler*  _handler[MAX_CLIENT];
	};
}

#endif
