/*
 * CChatWorld.h
 *
 *  Created on: 2012-7-16
 *      Author: guanlei
 */

#ifndef CCHATWORLD_H_
#define CCHATWORLD_H_
#include "Message.h"

#include "IChater.h"
#include "IChannel.h"
#include "CChannel.h"

class CChatWorld {
public:
	CChatWorld();
	virtual ~CChatWorld();
	void InitChatWorld();
	void SendMessageToWorld(Message*);
	void SendMessageToChannel(Message*,CHANNEL_ID);
	bool EnterChatWorld(IChater*);
	void LeftChatWorld(CHATER_ID);
private:
	//世界频道
	IChannel*				_world_channel;

	std::map<int,IChannel*> _all_channels;
	std::map<int,IChater*>	_all_chaters;
};

#endif /* CCHATWORLD_H_ */
