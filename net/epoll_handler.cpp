#include "epoll_handler.h"

namespace omg {

    Epollhandler::~Epollhandler() {

    }

    bool Epollhandler::init_epoll(int epoll_size, const char* ip, int port) {
        assert(epoll_size > 0);
        _epoll_create = epoll_create(epoll_size);
        _port = port;
        this->_ip_buffer = ip;
        assert(_epoll_create > 0);
        return true;
    }

    int Epollhandler::set_event(epoll_event *ev, int fd, int epoll_op,
            EPollSocket* s) {
        ev->data.ptr = s;
        return epoll_ctl(_epoll_create, epoll_op, fd, ev);
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
        s = new EPollSocket();
        s->fd = fd;
        s->type = EPollSocket::LISTEN_SOCKET;

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

        epoll_event ev;
        ev.events = EPOLLIN|EPOLLET;
        rcv = set_event(&ev,fd,EPOLL_CTL_ADD,s);
        if(rcv != 0 ) {
            VLOG(3)<<"ERROR OF SET LISTENING SOCKET";
        }
        return;
    }

    int Epollhandler::accept_conn(EPollSocket* epoll_socket) {
        struct sockaddr_in sin;
        socklen_t len = sizeof(sockaddr_in);
        EPollSocket *socket_client = NULL;
        int nfd;

        while(true){
            if((nfd = accept(epoll_socket->fd,(struct sockaddr*)&sin,&len)) == -1) {
                VLOG(3)<<"ERROR OF SOCKET::ACCEpT";
                return -1;
            }

            socket_client = new EPollSocket();
            socket_client->fd = nfd;
            socket_client->type = EPollSocket::DATA_SOCKET;
            socket_client->_epoll_fd = _epoll_create;
            socket_client->set_blocking(false);
            socket_client->set_nodelay(true);
            socket_client->set_reuseaddr(true);
            epoll_event event;
            event.events = EPOLLIN;
            event.data.ptr = socket_client;
            if(::epoll_ctl(_epoll_create,EPOLL_CTL_ADD,nfd,&event) == -1) {
                VLOG(3)<<"ERROR OF SOCKET EPOLLCTL";
                return -1;
            }
            VLOG(1)<<"Accept connection"<<socket_client->fd;
            socket_client->set_client_ip_address(sin);
        }
    }
    void Epollhandler::recv_data(EPollSocket* socket) {
        int len;
        MsgBase msg_base;
        len = recv(socket->fd,(char*)&msg_base,sizeof(MsgBase),0);
        if(len == -1 || len ==0) {
            LOG(INFO)<<"close socket .......";
            do_close(socket);
            return;
        }

        if(len != sizeof(MsgBase)){
            do_close(socket);
            return;
        }

        //do check qq tgw 
#ifdef	_QQ_PLATM_
        char tmp[64];
        memcpy(tmp,&msg_base,sizeof(msg_base));
        tmp[sizeof(msg_base)] = '\0';
        if(strncmp(tmp,"tgw_l7_forwa",sizeof(MsgBase)) == 0){
            VLOG(1)<<"Recv socket"<<socket->fd<<":tgw info";
            char	buffer[1024];
            int host_len = recv(socket->fd,buffer,1024,0);
            buffer[host_len] = '\0';
            MsgQQTGW msg_send;
            msg_send.ret = 1;
            send_data(socket,(const char*)&msg_send,msg_send.msg_size);
            return;
        }


#endif

        int data_remain = msg_base.msg_size - sizeof(MsgBase);
        if(msg_base.msg_size <= 0 || msg_base.msg_size>32768||msg_base.msg_type <= 0 || msg_base.msg_type > 50000) {
            LOG(ERROR)<<"error msg"<<socket->get_client_ip_str().c_str()<<"msg len:"<<len<<" msg size"<<msg_base.msg_size<<" msg type"<<msg_base.msg_type<<(const char*)&msg_base;
            do_close(socket);
            return;
        }

        // receive data

        char *buff = new char[msg_base.msg_size];
        char *buff_peek = buff;
        memcpy(buff,(const char*)&msg_base,sizeof(MsgBase));
        buff_peek += sizeof(MsgBase);
        for(;;) {
            len = recv(socket->fd, buff_peek,data_remain, 0);
            if(len == data_remain || data_remain == 0) {
                MsgBase* msg = (MsgBase*)buff;
                CMsgEvent* event = new CMsgEvent();
                event->_msg_base = msg;
                event->_msg_type = msg->msg_type;
                bool add_rst = _msg_handler->add_msg_to_queue(event,socket);
                if(!add_rst)
                {
                    LOG(ERROR)<<"error add msg "; 
                    delete[] buff;
                    do_close(socket);
                }
                return;
            } else if(len == 0) {//the client socket ?³é                VLOG(3)<<"CLOSE SOCKET!!!";
                delete[] buff;
                do_close(socket);
                return;
            } else if(len <0) {//the client socket?.
                delete[] buff;
                do_close(socket);
                return;
            }
            data_remain = data_remain -len;
            buff_peek += len;
        }
    }

    void* Epollhandler::on_run(void) {
        while(1) {
            VLOG(3)<<"net thread running";
            do_select();
        }
        return NULL;
    }

    void Epollhandler::do_select() {
        while(1) {
            int fds = epoll_wait(_epoll_create,_events,EPOLL_SIZE,50);
            if(fds < 0) {
                VLOG(3)<<"epoll_wait error";
                break;
            }
            for(int i=0; i< fds; i++) {
                EPollSocket *epoll_socket = (EPollSocket*)_events[i].data.ptr;
                if(epoll_socket->type == EPollSocket::LISTEN_SOCKET)
                {
                    accept_conn(epoll_socket);
                } else if(epoll_socket->type == EPollSocket::DATA_SOCKET) {
                    if(_events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                        do_close(epoll_socket);
                    } else {
                        if(_events[i].events & EPOLLIN) {
                            this->recv_data(epoll_socket);
                        }

                        if(_events[i].events & EPOLLOUT) {
                            VLOG(3)<<"DO WRITE ACTION";
                        }
                    }
                } else if(epoll_socket->type == EPollSocket::CONNECT_SOCKET){//主动连接socket
                    VLOG(3)<<"Connected Socket...";
                }else{
                    VLOG(3)<<"EPOLL_WAIT ERROR";
                }
            }
        }
    }

    void Epollhandler::do_close(EPollSocket *socket) {
        //remove from socket map
        if(socket == NULL){
            return;
        }
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

}

