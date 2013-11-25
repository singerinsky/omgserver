/*
 * Message.h
 *
 *  Created on: 2012-7-16
 *      Author: guanlei
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include "../net/msg.h"
#include "chat_server_define.h"

enum{
	MSG_LOGIN_CHAT_CHANNEL = 1,
	CHAT_MSG = 2,//用户发送的消息
	MSG_RECV = 3 //发送给用户的消息
};

//用户登录聊天的世界
struct ChaterLoginChatChannel:MsgBase{
	int 	user_id;
	char	user_name[20];
	int 	login_chat_channel_id;
	char    login_validate_code[16];
	short	world_id;
	ChaterLoginChatChannel(){
		msg_type = MSG_LOGIN_CHAT_CHANNEL;
		memset(user_name,0,20);
		memset(login_validate_code,0,16);
	}

};

//聊天用户的消息
struct UserChatMsg:MsgBase{
	char 	sender_name[20];
	short	world_id;
	int 	sender_id;
	int	recv_target_id;
	short 	message_type;
	short	message_len;
	char* 	message_content;
	UserChatMsg(){
		msg_type = CHAT_MSG;
		msg_size = message_len +  sizeof(UserChatMsg) - sizeof(char*);
		is_encode = false;
	}
};

//消息
class Message{
public:
	Message(UserChatMsg* msg){
		_source_id = msg->sender_id;
		_target_id = msg->recv_target_id;
		memcpy(_sender_name,msg->sender_name,20);
		_sender_name[19]= '\0';
		_message_type = (MessageType)msg->message_type;
		_message_len = msg->message_len;
		char* msg_tmp = new char[_message_len];
		memcpy(msg_tmp,msg,_message_len);
		_msg_base = (UserChatMsg*)msg_tmp;
		_msg_content = msg->message_content;
	}

	~Message(){
		delete[] (char*)_msg_base;
	}

public:
	int GetMessageLen(){
		return this->_message_len;
	}

	const UserChatMsg* GetMessageData(){
		return _msg_base;
	}

private:
	TARGET_ID	_source_id;
	TARGET_ID	_target_id;
	char		_sender_name[20];
	MessageType	_message_type;
	int			_message_len;
	UserChatMsg*		_msg_base;
	char*			_msg_content;
};
#endif /* MESSAGE_H_ */
