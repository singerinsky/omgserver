#ifndef _EPOLL_HANDLER_H
#define _EPOLL_HANDLER_H
#include "epoll_socket.h"
#include "../common/head.h"
#include "thread.h"
#include <glog/logging.h>
#include "msg.h"
#include "IMsgDispatcher.h"
#include "define.h"

const int EPOLL_SIZE = 128*1024;
#ifndef EPOLLRDHUP
	#define EPOLLRDHUP 0x2000
#endif

namespace omg{
	class Epollhandler : public Thread
	{
		public:
			Epollhandler(const char *name=NULL) : Thread(name){
				VLOG(3)<<"STARTING epoll thread"<<name;
				_epoll_create = 0;
			}
			virtual ~Epollhandler();
			bool init_epoll(int epoll_size,const char* ip,int port);
			void startListening();
			int	 set_event(epoll_event *ev,int fd,int epoll_op,EPollSocket* s);
			int  accept_conn(EPollSocket* s);
			void send_data(EPollSocket *socket,const char* msg,int msg_len);
			void recv_data(EPollSocket* socket);
			void do_close(EPollSocket*);

		public:
			virtual void *on_run(void);
		
			void	set_msg_dispatcher(IMsgDispatcher* dispatcher){
				this->_msg_handler = dispatcher;
			}

		protected:
			void do_select();


		private :
			int _epoll_create;
			IMsgDispatcher* _msg_handler;
			epoll_event _events[EPOLL_SIZE];
			int	_port;
			StringBuffer	_ip_buffer;
	};
}

#endif
