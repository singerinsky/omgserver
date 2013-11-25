/*
 * CChatWorld.cpp
 *
 *  Created on: 2012-7-16
 *      Author: guanlei
 */

#include "CChatWorld.h"

CChatWorld::CChatWorld() {
	// TODO Auto-generated constructor stub

}

CChatWorld::~CChatWorld() {
	// TODO Auto-generated destructor stub
}

void CChatWorld::InitChatWorld(){
	//创建世界频道
	_world_channel = static_cast<IChannel*>(new CChannel(WORLD_CHANNEL_ID));

}


void CChatWorld::SendMessageToWorld(Message* message){
	_world_channel->SendAllMessage(message);
}

void CChatWorld::SendMessageToChannel(Message*,CHANNEL_ID){


}

bool CChatWorld::EnterChatWorld(IChater* chater){
	std::map<int,IChater*>::iterator itr = this->_all_chaters.find(chater->GetChaterId());
	if(itr != _all_chaters.end()){
		return false;
	}
	_all_chaters[chater->GetChaterId()] = chater;

	_world_channel->AddChater(chater);
	return true;
}

void CChatWorld::LeftChatWorld(CHATER_ID){

}
