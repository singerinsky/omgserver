#include "epoll_handler.h"

namespace omg {

    Epollhandler::~Epollhandler() {
    }

    bool Epollhandler::init_epoll(int epoll_size, const char* ip, int port,bool use_et) {
        assert(epoll_size > 0);
        _epoll_create = epoll_create(epoll_size);
        _port = port;
        this->_ip_buffer = ip;
        assert(_epoll_create > 0);
        if(use_et)
        {
            _epoll_mod = EPOLLET;
        }
        else
        {
            _epoll_mod = 0; 
        }
        return true;
    }

    void Epollhandler::startListening() {

        EPollSocket *s;
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (fd == -1) {
            VLOG(3)<<"error of create socket";
            return;
        }
        //设置可复用
        int opt = SO_REUSEADDR;
        setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
        //设置缓冲区大小
        int window_size = 128 * 1024;
        if (-1 == ::setsockopt(fd,SOL_SOCKET,SO_RCVBUF,(char*)&window_size,sizeof(window_size)))
        {
            ::close(fd);
            return;
        }
        if (-1 == ::setsockopt(fd,SOL_SOCKET,SO_SNDBUF,(char*)&window_size,sizeof(window_size)))
        {
            ::close(fd);
            return;
        }
        s = new EPollSocket(fd,EPollSocket::LISTEN_SOCKET,_epoll_mod,_msg_handler,_epoll_create);

        //设置套接字为非阻塞
        if(s->set_blocking(false) == -1)
        {
            VLOG(3)<<"error of set socket noblocking";
            return;
        }

        sockaddr_in sin;
        sin.sin_family = AF_INET;
        inet_aton(this->_ip_buffer.c_str(),&(sin.sin_addr));
        sin.sin_port= htons(this->_port);
        VLOG(2)<<this->_ip_buffer.c_str();
        //绑定套接字
        int rcv = 0;
        rcv = ::bind(fd,(const sockaddr*)&sin,sizeof(sin));

        if(rcv == -1)
        {
            LOG(ERROR)<<"error of bind socket "<<this->_port<<":"<<_ip_buffer.c_str();
            exit(1);
        }

        rcv = ::listen(fd,128);
        if(rcv == -1) {
            VLOG(3)<<"error of listen socket";
            return;
        }

        int rst = s->add_epoll_event(EPOLLIN);
        if(rst != 0)
        {
            LOG(ERROR)<<"init epoll fd add"<<rst;
            exit(1);
        }
        return;
    }

    int Epollhandler::accept_conn(EPollSocket* listen_socket) {
        struct sockaddr_in sin;
        socklen_t len = sizeof(sockaddr_in);
        EPollSocket *socket_client = NULL;
        int nfd;

        while(true){
            if((nfd = accept(listen_socket->fd,(struct sockaddr*)&sin,&len)) == -1) {
                return -1;
            }

            on_connection(nfd,(struct sockaddr*)&sin);

            socket_client = new EPollSocket(nfd,EPollSocket::DATA_SOCKET,_epoll_mod,_msg_handler,_epoll_create);
            socket_client->_epoll_fd = _epoll_create;
            socket_client->set_blocking(false);
            socket_client->set_nodelay(true);
            socket_client->set_reuseaddr(true);
            socket_client->set_client_ip_address(sin);
            if(socket_client->add_epoll_event(EPOLLIN) != 0){
                LOG(ERROR)<<"accept connection error "; 
                delete socket_client;
                return -1;
            }
            VLOG(1)<<"Accept connection"<<socket_client->fd;
        }
    }

    void* Epollhandler::on_run(void) {
        while(_is_final) {
            do_select();
        }
        return NULL;
    }

    void Epollhandler::do_select() {
        while(1) {
            int fds = epoll_wait(_epoll_create,_events,EPOLL_SIZE,20);
            if(fds < 0) {
                VLOG(3)<<"epoll_wait error";
                break;
            }

            if(fds == 0)
            {
                VLOG(3)<<"no event";
                continue;
            }

            for(int i=0; i< fds; i++) {
                EPollSocket *epoll_socket = (EPollSocket*)_events[i].data.ptr;
                if(epoll_socket->_socket_type == EPollSocket::LISTEN_SOCKET)
                {
                    accept_conn(epoll_socket);
                } else if(epoll_socket->_socket_type == EPollSocket::DATA_SOCKET) {
                    if(_events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                        do_close(epoll_socket);
                    }else if(_events[i].events & EPOLLIN) {
                        int rst = epoll_socket->on_read();
                        if(rst == -1)
                        {
                            do_close(epoll_socket);
                        }
                    }else if(_events[i].events & EPOLLOUT) {
                        int rst = epoll_socket->on_write();
                        if(rst == -1)
                        {
                            do_close(epoll_socket);
                        }
                    }
                } else if(epoll_socket->_socket_type == EPollSocket::CONNECT_SOCKET){//主动连接socket
                    VLOG(3)<<"Connected Socket...";
                }
            }
        }
    }

    void Epollhandler::do_close(EPollSocket *socket) {
        //remove from socket map
        if(socket == NULL){
            return;
        }
        LOG(INFO)<<"close socket";
        epoll_event ev;
        ::epoll_ctl(_epoll_create, EPOLL_CTL_DEL,socket->fd , &ev);

        if(socket->_conn_state == CONN_VRIFY){//已经成功登录
            MsgLoginOut *out = new MsgLoginOut();
            CMsgEvent* event = new CMsgEvent();
            event->_client_id = socket->fd;
            event->_msg_base = out;
            event->_msg_type = MSG_TYPE_LOGIN_OUT;
            _msg_handler->add_msg_to_queue(event,NULL);
            return;
        }else if(socket->_conn_state == CONN_UNVRIFY){
            delete socket;
        }
    }

    void Epollhandler::send_data(EPollSocket *socket,const char* msg,int msg_len) {
        ::send(socket->fd,msg,msg_len,0);
    }

   void Epollhandler::on_connection(int fd,sockaddr* addr)
   {
   
   }
}

