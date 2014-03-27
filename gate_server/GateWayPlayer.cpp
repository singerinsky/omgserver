/*
 * GateWayPlayer.cpp
 *
 *  Created on: 2012-9-11
 *      Author: guanlei
 */

#include "GateWayPlayer.h"
#include "../net/game_packet.h"
#include "../message/message_define.h"

GateWayPlayer::GateWayPlayer(int fd,sockaddr_in& addr ,epoll_handler* handler,timer_manager* mgr):socket_client(fd,addr,handler),_timer_mgr(mgr) {
	_player_state = LOGIN_SUCCESS;
	_login_time = time(NULL);
	_match_watcher_id = 0;
	_club_attack_value = 0;
	_club_defend_value = 0;
}

void GateWayPlayer::on_timeout(timer_manager* timer_mgr)
{
    LOG(INFO)<<"gate way  player timer out";
}
GateWayPlayer::~GateWayPlayer() {
	LOG(INFO)<<"delete gate way player "<<_player_id;
}

int GateWayPlayer::check_packet_info(char* msg_data,int size,packet_info*)
{
    return 1;
}

void GateWayPlayer::forward_game_msg(const char* data,int data_size)
{
    cs_soccer_player_response response;
    response.body.set_player_id(111);
    response.body.set_player_name("guanlei");
    response.body.set_age(21);
    send_packet_msg(&response);
}

