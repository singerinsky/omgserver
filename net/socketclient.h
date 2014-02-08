/*
 * socketclient.h
 *
 *  Created on: 2014年1月24日
 *      Author: guanlei
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_
#include "IConnection.h"
#include "IMsgDispatcher.h"
#include <vector>
#include "packet.h"
#include "../common/head.h"
#include "../common/server_application.h"

namespace omg {
    
    class epoll_handler;
    typedef enum {
        CONN_UNCONFIRM = 1,
        CONN_CONFIRM = 2,
        CONN_WAITDEL = 3
    } CONN_STATE;

    class socket_client: public io_handler {
        public:
            socket_client(int fd,sockaddr_in& addr_in,epoll_handler* handler,IMsgDispatcher* dispatcher );
            virtual ~socket_client();
            int init();
            virtual int on_read();
            virtual int on_write();
            virtual int on_error();
            const connection_id& get_id() {
                return _conn_id;
            }
            CONN_STATE get_state() {
                return _conn_state;
            }

            void set_state(CONN_STATE value)
            {
                _conn_state = value;
            }

            int get_socket_fd() {
                return _socket_fd;
            }

            int check_msg_complete(char *data_head,int size);

            int send_packet_msg(packet* p);
            
            int send_msg(const char* data_head, int send_size);

            std::string get_ip_port_str(){
                return _ip_str; 
            }

            void fini();

            bool is_connected(){return _connected;}
        private:
            std::vector<char> _recv_buffer;
            std::vector<char> _send_buffer;
            connection_id _conn_id;
            CONN_STATE _conn_state;
            MutexLock _lock;
            epoll_handler* _epoll_handler;
            IMsgDispatcher* _msg_dispatcher;
        private:
            std::string _ip_str;
            int _epoll_mod;
            int _socket_fd;
            int _port;
            sockaddr_in _sin;
            bool _connected;
    };

} /* namespace omg */

#endif /* SOCKETCLIENT_H_ */
