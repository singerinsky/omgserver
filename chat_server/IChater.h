/*
 * IChater.h
 *
 *  Created on: 2012-7-16
 *      Author: guanlei
 */

#ifndef ICHATER_H_
#define ICHATER_H_

#include "chat_server_define.h"
class Message;

class IChater{
public:
	IChater(CHATER_ID chater_id){
		_chater_id = chater_id;
	}

	virtual void    SendMessageToChater(CHATER_ID,Message*) = 0;
	virtual void    SendMessageToChannel(CHANNEL_ID,Message*) = 0;
	virtual void 	RecvMessage(Message*) = 0;
	CHATER_ID	GetChaterId(){
		return		_chater_id;
	}

private:
	CHATER_ID		_chater_id;
};

#endif /* ICHATER_H_ */
