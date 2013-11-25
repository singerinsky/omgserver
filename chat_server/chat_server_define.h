
#ifndef _CHAT_SERVER_DEFINE_H_
#define _CHAT_SERVER_DEFINE_H_

typedef int CHATER_ID;
typedef int CHANNEL_ID;
typedef int TARGET_ID;

typedef enum{
	PRIVATE_CHAT	= 1,//私聊
	CHANNEL_CHAT    = 2,//频道聊天
	WORLD_CHAT      = 3,    //世界聊天
	UNIVERSITY_CHAT = 4,	//宇宙聊天
}MessageType;

#define WORLD_CHANNEL_ID 0
#endif
