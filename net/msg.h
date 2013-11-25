#ifndef _MSG_H_
#define _MSG_H_

#include "../common/head.h"
#pragma pack(1)

/*
#define MSG_MIN_SIZE 0
#define MSG_MAX_SIZE 100000
*/

enum{
	MSG_TYPE_LOGIN = 1,
	MSG_TYPE_ALIVE = 2,
	MSG_TYPE_LOGIN_OUT = 3,
	MSG_TYPE_QQ_TGW = 4,
	MSG_TYPE_MAX   = 10000
};
struct MsgBase{
	int msg_size;
	int msg_type;
	int	is_encode;
};

//
class IConnection;
class CMsgEvent{
public:
	virtual ~CMsgEvent(){
		if(_msg_base != NULL){
			delete[] (char*)_msg_base;
			_msg_base = NULL;
		}
	}
	int _msg_type;
	int _client_id;
	IConnection*	_msg_from;
	MsgBase *_msg_base;
};

//login msg
struct MsgLogin: MsgBase{
	int uid;
	int mid;
	int zeit;
	int rand_int;
	char	code[16];
	MsgLogin(){
		msg_size = sizeof(MsgLogin);
		msg_type  = MSG_TYPE_LOGIN;
		is_encode = 0;
	}
};

struct MsgLoginAck: MsgBase{
	int ret;
	MsgLoginAck(){
		msg_size = sizeof(MsgLoginAck);
		msg_type  = MSG_TYPE_LOGIN;
		is_encode = 0;
	}
};


struct MsgAlive: MsgBase{
	int player_id;
	int zeit;
	MsgAlive(){
		msg_size = sizeof(MsgAlive);
		msg_type  = MSG_TYPE_ALIVE;	
		is_encode = 0;
	}
};

struct MsgLoginOut: MsgBase{
	int pid;
	MsgLoginOut(){
		msg_size = sizeof(MsgLoginOut);
		msg_type  = MSG_TYPE_LOGIN_OUT;
		is_encode = 0;
	}
};

//QQ网关通过包头
struct MsgQQTGW: MsgBase{
	int ret;
	MsgQQTGW(){
		msg_size = sizeof(MsgQQTGW);
		msg_type = MSG_TYPE_QQ_TGW;
		is_encode = 0;
	}
};


#pragma pack()
#endif
