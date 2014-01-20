#ifndef _SOCKET_CLIENT_H_
#define _SOCKET_CLIENT_H_

#include "../common/head.h"
#include "../common/omg_type.h"
#include "../net/msg.h"
#include "../net/IMsgDispatcher.h"
#include "../net/IConnection.h"

class CSocketClient:public IConnection
{
	public:
		CSocketClient(int fd,sockaddr_in& sock_addr){
			_socket_fd = fd;
			_is_connected = false;
			_sock_addr = sock_addr;
			_server_ip = inet_ntoa(_sock_addr.sin_addr);
			_server_port	=_sock_addr.sin_port;
			_server_ip_port_str.append( _server_ip.c_str());
			_server_ip_port_str.append("_");
			char port[6];
			memset(port,'\0',sizeof(port));
			sprintf(port,"%d",_server_port);
			_server_ip.append(port);
		};
		CSocketClient(short port,const char* server_ip);
		virtual ~CSocketClient();
		int  get_connection_id(){
			return _socket_fd;
		}
		bool set_block(bool);	
		bool connectToServer();
		int recvData();
		int recvData(char* buff,int len);
		int send_data(const char*,int);
		void set_msg_dispatcher(IMsgDispatcher* dispatcher){
			this->_msg_dispatcher = dispatcher;
		}
		bool connected(){
			return _is_connected;
		}

		void set_connection(bool state){
			_is_connected = state;
		}

		void set_socket_buffer_size(int size){
			int optLen = sizeof(int);
			setsockopt(_socket_fd, SOL_SOCKET,SO_RCVBUF,(char*)&size,optLen );
			setsockopt(_socket_fd, SOL_SOCKET,SO_SNDBUF,(char*)&size,optLen );
		}

		StringBuffer	get_socket_ip(){
			return _server_ip;
		}

		int get_socket_port(){
			return _server_port;
		}

		StringBuffer	get_socket_ip_port_info(){
			return _server_ip_port_str;
		}

	private:
		bool _is_connected;
		int _server_port;
		StringBuffer _server_ip;
		StringBuffer _server_ip_port_str;
		int	_socket_fd;
		sockaddr_in _sock_addr;
		IMsgDispatcher *_msg_dispatcher;
};

#endif
