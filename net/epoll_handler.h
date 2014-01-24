#ifndef _EPOLL_HANDLER_H
#define _EPOLL_HANDLER_H
#include "epoll_socket.h"
#include "../common/head.h"
#include "thread.h"
#include <glog/logging.h>
#include "msg.h"
#include "IMsgDispatcher.h"
#include "define.h"
#include "IConnection.h"

const int EPOLL_SIZE = 128*1024;

#ifndef EPOLLRDHUP
	#define EPOLLRDHUP 0x2000
#endif

namespace omg{
	class epoll_handler : public Thread
	{
		public:
			epoll_handler(const char *name=NULL) : Thread(name){
				VLOG(3)<<"STARTING epoll thread"<<name;
				_epoll_create = 0;
                _is_final = true;
			}
			virtual ~epoll_handler();
			bool init_epoll(int epoll_size,const char* ip,int port,bool use_et_mod=false);
			void startListening();
			int  accept_conn(EPollSocket* s);
			void send_data(EPollSocket *socket,const char* msg,int msg_len);
			void recv_data(EPollSocket* socket);
			void do_close(EPollSocket*);

            int add_event_handler(int fd,io_handler* handler);
            int mod_epoll_status(int fd,io_handler* handler,int event_type);

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
	};
}

#endif
