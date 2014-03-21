#include "epoll_handler.h"
#include "net_util.h"
#include "socketclient.h"

namespace omg {

    epoll_handler::~epoll_handler() {

    }

    bool epoll_handler::init_epoll(int epoll_size, int wait_ms,bool use_et) {
        assert(epoll_size > 0);
        memset(_handler,0,sizeof(_handler));
        _epoll_create = epoll_create(epoll_size);
        _epoll_wait_ms = wait_ms;
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

    void* epoll_handler::on_run(void) {
        while(_is_final) {
           // _timer_mgr->run_until();
            do_select();
        }
        return NULL;
    }

    void epoll_handler::do_select() {
        int fds = epoll_wait(_epoll_create,_events,EPOLL_SIZE,_epoll_wait_ms);
        if(fds < 0) {
            VLOG(3)<<"epoll_wait error";
            _is_final = false;
            return;
        }

        if(fds == 0)
        {
            return;
        }

        for(int i=0; i< fds; i++) {
            //io_handler *handler = (io_handler*)_events[i].data.ptr;
            int event_fd = _events[i].data.fd;
            if((_handler[event_fd] == NULL) || event_fd < 0 || event_fd > MAX_CLIENT)
            {
                return ;
            }
            if(_events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                _handler[event_fd]->on_error();
                //do_close(epoll_socket);
            }
            else
            {
                if(_events[i].events & EPOLLIN) {
                    int rst = _handler[event_fd]->on_read();
                    if(rst == -1)
                    {
                        _handler[event_fd]->on_error();
                    }
                }else if(_events[i].events & EPOLLOUT) {
                    int rst = _handler[event_fd]->on_write();
                    if(rst == -1)
                    {
                        _handler[event_fd]->on_error();
                    }
                }
            }
        } 
    }

    void epoll_handler::do_close(socket_client *socket) {
        //remove from socket map
        if(socket == NULL){
            return;
        }
        LOG(INFO)<<"close socket";
        epoll_event ev;
        ::epoll_ctl(_epoll_create, EPOLL_CTL_DEL,socket->get_socket_fd() , &ev);

        if(socket->get_state() == CONN_CONFIRM){//已经成功登录
            MsgLoginOut *out = new MsgLoginOut();
            CMsgEvent* event = new CMsgEvent();
            event->_client_id = socket->get_id();
            event->_msg_base = out;
            event->_msg_type = MSG_TYPE_LOGIN_OUT;
            _msg_handler->add_msg_to_queue(event);
            return;
        }else if(socket->get_state() == CONN_UNCONFIRM){
            delete socket;
        }
    }

    void epoll_handler::send_data(socket_client *socket,const char* msg,int msg_len) {
        ::send(socket->get_socket_fd(),msg,msg_len,0);
    }

    void epoll_handler::on_connection(int fd,sockaddr* addr)
    {

    }

    int epoll_handler::add_event_handler(int fd,io_handler* handler)
    {
        epoll_event event = {0};
        event.events |= EPOLLIN;
        event.events |= _epoll_mod;
        event.events |= EPOLLRDHUP;
        event.data.fd = fd;
        _handler[fd] = handler;
        return ::epoll_ctl(_epoll_create,EPOLL_CTL_ADD,fd,&event);
    }

    int epoll_handler::mod_epoll_status(int fd,io_handler* handler,int event_type) {
        epoll_event event = { 0 };
        event.events |= event_type;
        event.events |= _epoll_mod;
        event.data.fd = fd;
        return ::epoll_ctl(_epoll_create, EPOLL_CTL_MOD, fd, &event);
    }

    int epoll_handler::del_event_handler(int fd)
    {
        if(fd < 0 )return -1; 
        if(_epoll_create< 0)return -2;
        _handler[fd] = NULL;
        epoll_ctl(_epoll_create,EPOLL_CTL_DEL,fd,NULL);
        return 0;
    }

}

