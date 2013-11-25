/*
 * serversocket.cpp
 *
 *  Created on: 2012-2-7
 *      Author: gl
 */

#include "serversocket.h"


INT set_socket_blocking(int fd,bool blocking) {
		assert(fd > 0);

		int flag = fcntl(fd, F_GETFL);
		if (flag == -1) {
			return -1;
		}

		if (blocking) {
			flag &= (~O_NONBLOCK);
		} else {
			flag |= O_NONBLOCK;
		}

		INT rv = fcntl(fd, F_SETFL, flag);

		return rv;
	}




server_socket::server_socket() {
	// TODO Auto-generated constructor stub

}

server_socket::~server_socket() {
	// TODO Auto-generated destructor stub
}

bool server_socket::initSocket(int port) {
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1) {
		VLOG(3) << "error of create socket";
		exit(1);
		return false;
	}

	//设置套接字为阻塞
	if (set_socket_blocking(_fd,true) == -1) {
		VLOG(3) << "error of set socket noblocking";
		exit(1);
		return false;
	}

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr=htonl(INADDR_ANY);
	//inet_aton("127.0.0.1", &(sin.sin_addr));
	sin.sin_port = htons(port);
	//允许端口重用
	int opt = SO_REUSEADDR;
	setsockopt(_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));

	//绑定套接字
	VLOG(1)<<"Bind port "<<port;
	int rcv = 0;
	rcv = ::bind(_fd, (const sockaddr*) &sin, sizeof(sin));
	if (rcv == -1) {
		VLOG(3) << "error of bind socket";
		exit(1);
		return false;
	}

	rcv = ::listen(_fd, 128);
	if (rcv == -1) {
		VLOG(3) << "error of listen socket";
		exit(1);
		return false;
	}

	return true;
}




CSocketClient* server_socket::startListening() {
	while(1){
		sockaddr_in in_sock;
		socklen_t addr_len = sizeof(struct sockaddr_in);
		int fd = -1;
		if(!(fd = accept(_fd,(struct sockaddr*)&in_sock,&addr_len))){
			LOG(ERROR)<<"ACCEPT SERVER SOCKET ERROR ！！！";
		}else{
			LOG(INFO)<<"Success get server connection ";
		}
		CSocketClient *client = new CSocketClient(fd,in_sock);
		client->set_connection(true);
		return client;
	}
}
