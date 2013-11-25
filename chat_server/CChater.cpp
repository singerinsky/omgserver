/*
 * CChater.cpp
 *
 *  Created on: 2012-7-17
 *      Author: guanlei
 */

#include "CChater.h"

CChater::CChater(CHATER_ID chat_id,CSession* session):IChater(chat_id) {
	// TODO Auto-generated constructor stub
	this->_client_session = session;
}

CChater::~CChater() {
	// TODO Auto-generated destructor stub
}

void CChater::SendMessageToChater(CHATER_ID,Message*){

}

void CChater::SendMessageToChannel(CHANNEL_ID,Message*){

}
void CChater::RecvMessage(Message* message){
	if(message != NULL){
		_client_session->send_msg((const  MsgBase*)message->GetMessageData());
	}
}

void CChater::EnterChannel(IChannel* channel){
	std::list<IChannel*>::iterator itr = _channel_player_join.begin();
	if(itr == _channel_player_join.end()){
		_channel_player_join.push_back(channel);
	}else{
		LOG(ERROR)<<"ReJoin Channel"<<channel->GetChannelId();
	}

}
