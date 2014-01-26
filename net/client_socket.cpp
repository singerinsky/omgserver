#include "client_socket.h"

CSocketClient::CSocketClient(short port, const char* ip) {
	_server_port = port;
	_server_ip = ip;
	_is_connected = false;

	_server_ip_port_str.append( _server_ip.c_str());
	_server_ip_port_str.append("_");
	char port_str[6];
	memset(port_str,'\0',sizeof(port_str));
	sprintf(port_str,"%d",port);
	_server_ip_port_str.append(port_str);
}

CSocketClient::~CSocketClient() {
}

bool CSocketClient::connectToServer() {
	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	set_socket_buffer_size(128*1024);
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(_server_port);
	server_addr.sin_addr.s_addr = inet_addr(_server_ip.c_str());
        int optVal = 64*1024 ;
   	int optLen = sizeof(int);
        setsockopt(_socket_fd, SOL_SOCKET,SO_RCVBUF,(char*)&optVal,optLen );
    int error;
    error = connect(_socket_fd, (struct sockaddr*) &server_addr,
    			sizeof(sockaddr));
	if (error == -1) {
		LOG(ERROR)<<"connect to server"<<_server_ip<<":"<<_server_port<<" failed.....";
		_is_connected = false;
		close(_socket_fd);
		return false;
	}
	_is_connected = true;
	//VLOG(3)<<"CONNECT OT SERVER SUCCESS";
	return true;
}

bool CSocketClient::set_block(bool block) {
	int flag = fcntl(_socket_fd, F_GETFL);
	if (flag == -1) {
		return false;
	}

	if (block) {
		flag &= (~O_NONBLOCK);
	} else {
		flag |= O_NONBLOCK;
	}
	fcntl(_socket_fd, F_SETFL, flag);
	return true;

}

int CSocketClient::send_data(const char *buffer, int buffer_size) {
	int ret = 0;

	while (ret < buffer_size) {
		int send_size = send(_socket_fd, buffer + ret, buffer_size - ret, 0);
		if (send_size == -1) {
			return -1;
		}
		ret = ret + send_size;
	}
	return ret;

}

int CSocketClient::recvData(char *buff, int len) {
	int ret = 0;
	if (-1 == (ret = recv(_socket_fd, buff, len, 0))) {
		return -1;
	}
	return ret;
}

int CSocketClient::recvData() {

	//先读出消息头
	int recv_head_size = sizeof(MsgBase);
	int ret = 0;
	char*	buffer_head = new char[sizeof(MsgBase)];
	char* buffer_head_peek = buffer_head;
	while(ret < recv_head_size){
		int tmp_recv_size = recv(_socket_fd, buffer_head_peek + ret, recv_head_size-ret, 0);
		if(tmp_recv_size == -1 || tmp_recv_size == 0){
			delete[] buffer_head;
			return tmp_recv_size;
		}
		ret += tmp_recv_size;
	}

	//读取消息体
	int msg_typ = ((MsgBase*)buffer_head)->msg_type;
	int msg_size = ((MsgBase*)buffer_head)->msg_size;
	char* buffer = new char[msg_size];
	if(buffer == NULL){
		LOG(ERROR)<<"ERROR OF MSG SIZE ALLOC"<<msg_size;
		exit(1);
	}
	memcpy(buffer,buffer_head,sizeof(MsgBase));
	//TODO can check the data is ok
	delete[] buffer_head;
	int len =0;
	//除去包头，还剩下的数据
	int data_remain = msg_size - sizeof(MsgBase);
	char *buffer_peek = buffer + sizeof(MsgBase);
	while(len < data_remain) {
		int recv_len = recv(_socket_fd,buffer_peek,(data_remain-len),0);
		if(recv_len == 0) {
			return 0;
		} else if(recv_len == -1) {
			return -1;
		}
		len = len+recv_len;
		buffer_peek = buffer_peek + recv_len;
	}
	CMsgEvent* event = new CMsgEvent();
	event->_msg_type = msg_typ;
	event->_msg_base = (MsgBase*)buffer;
	_msg_dispatcher->add_msg_to_queue(event);
	return ret;
}

