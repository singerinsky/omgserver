/*
 * CChannel.cpp
 *
 *  Created on: 2012-7-17
 *      Author: guanlei
 */

#include "CChannel.h"

CChannel::CChannel(CHANNEL_ID channel_id) {
	// TODO Auto-generated constructor stub
	_channel_id = channel_id;
}

CChannel::~CChannel() {
	// TODO Auto-generated destructor stub
}

void	CChannel::AddChater(IChater* pNewChater){
	CHATER_MAP_ITER itr = _chater_map.find(pNewChater->GetChaterId());
	if(itr != _chater_map.end()){
		_chater_map[pNewChater->GetChaterId()] = pNewChater;
	}
}

void	CChannel::RemoveChaterById(CHATER_ID){

}

void	CChannel::RemoveChater(IChater*){

}

void	CChannel::SendAllMessage(Message* message){
	CHATER_MAP_ITER itr = _chater_map.begin();
	while(itr != _chater_map.end()){
		IChater* chater = itr->second;
		chater->RecvMessage(message);
		itr++;
	}
}

int		CChannel::GetChaterNumberInChannel(){
	return _chater_map.size();
}
