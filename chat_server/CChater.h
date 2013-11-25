/*
 * CChater.h
 *
 *  Created on: 2012-7-17
 *      Author: guanlei
 */

#ifndef CCHATER_H_
#define CCHATER_H_

#include "IChater.h"
#include "../net/session.h"
#include "Message.h"
#include "IChannel.h"

class CChater:public IChater {
public:
	CChater(CHATER_ID chat_id,CSession* session);
	virtual ~CChater();
	virtual void    SendMessageToChater(CHATER_ID,Message*);
	virtual void    SendMessageToChannel(CHANNEL_ID,Message*);
	virtual void 	RecvMessage(Message*);
	virtual void 	EnterChannel(IChannel*);	

private:
	CSession* _client_session;
	std::list<IChannel*>	_channel_player_join;
};

#endif /* CCHATER_H_ */
