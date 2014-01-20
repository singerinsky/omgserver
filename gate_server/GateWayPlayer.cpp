/*
 * GateWayPlayer.cpp
 *
 *  Created on: 2012-9-11
 *      Author: guanlei
 */

#include "GateWayPlayer.h"
#include "../net/game_packet.h"
#include "../net/packet_message.h"

GateWayPlayer::GateWayPlayer(EPollSocket* socket,int player_id,timer_manager& mgr):_socket(socket),_player_id(player_id),_timer_mgr(mgr) {
	_player_state = LOGIN_SUCCESS;
	_login_time = time(NULL);
	_socket->update_socket_state(CONN_VRIFY);
	_match_watcher_id = 0;
	_club_attack_value = 0;
	_club_defend_value = 0;

    init();
}

void GateWayPlayer::on_timeout(timer_manager* timer_mgr)
{

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

void GateWayPlayer::forward_game_msg(const char* data,int data_size)
{
    cs_soccer_player_response response;
    response.body.set_player_id(111);
    response.body.set_player_name("guanlei");
    response.body.set_age(21);
    _socket->send_packet_msg(&response);
}

