/*
 * IChannel.h
 *
 *  Created on: 2012-7-16
 *      Author: guanlei
 */

#ifndef ICHANNEL_H_
#define ICHANNEL_H_

#include "chat_server_define.h"
#include "IChater.h"
#include "../common/head.h"

class Message;
class IChannel{
public:
	IChannel(){}
	virtual 	~IChannel(){};
	virtual CHANNEL_ID GetChannelId() = 0;
	virtual void	AddChater(IChater*) = 0;
	virtual void	RemoveChaterById(CHATER_ID) = 0;
	virtual void	RemoveChater(IChater*) = 0;
	virtual void	SendAllMessage(Message*) = 0;
	virtual int		GetChaterNumberInChannel()	=	0;
	void 		SetMessageSendDelay(bool value){
		_is_send_delay = value;
	}

private:
	bool _is_send_delay;
};


#endif /* ICHANNEL_H_ */
