#ifndef _G_SERVER_INFO_
#define _G_SERVER_INFO_

#include "../common/head.h"
#include "../net/client_socket.h"

enum{
	CROSS_SERVER=-1,
	GATE_SERVER=1,
	GAME_SERVER,
	DB_SERVER
};

//all the server types
struct GServerInfo{
	GServerInfo(){
	}
	//1:have not been idfend 2:OK
	int			_status;
	std::string _ip;
	int			_port;
	int			_server_typ;	
	int			_index;
	CSocketClient* _c_socket;
	int	SendData(const char* msg,int msg_size){
		return _c_socket->sendData(msg,msg_size);
	}
};



#endif
