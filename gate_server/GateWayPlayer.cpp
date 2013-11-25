/*
 * GateWayPlayer.cpp
 *
 *  Created on: 2012-9-11
 *      Author: guanlei
 */

#include "GateWayPlayer.h"

GateWayPlayer::GateWayPlayer(EPollSocket* socket,int player_id):_socket(socket),_player_id(player_id) {
	_player_state = LOGIN_SUCCESS;
	_login_time = time(NULL);
	_socket->update_socket_state(CONN_VRIFY);
	_match_watcher_id = 0;
	_club_attack_value = 0;
	_club_defend_value = 0;

}

GateWayPlayer::~GateWayPlayer() {
	delete _socket;
	LOG(INFO)<<"delete gate way player "<<_player_id;
}

void GateWayPlayer::send_msg(const MsgBase* msg){
	if(_socket){
		int rst = _socket->send_msg(msg);
		if(rst == -1){
			LOG(ERROR)<<"ERROR SEND MESSAGE!!!"<<this->get_player_id();
		}
	}
}
