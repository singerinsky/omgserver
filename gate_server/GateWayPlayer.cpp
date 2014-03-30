/*
 * GateWayPlayer.cpp
 *
 *  Created on: 2012-9-11
 *      Author: guanlei
 */

#include "GateWayPlayer.h"
#include "../net/game_packet.h"
#include "../message/message_define.h"
#include "gate_server.h"

GateWayPlayer::GateWayPlayer(int fd,sockaddr_in& addr ,epoll_handler* handler,timer_manager* mgr):socket_client(fd,addr,handler),_timer_mgr(mgr) {
    _player_state = WAIT_LOGIN;
    _login_time = time(NULL);
    _match_watcher_id = 0;
    _club_attack_value = 0;
    _club_defend_value = 0;
}

void GateWayPlayer::on_timeout(timer_manager* timer_mgr)
{
    if(_player_state == WAIT_LOGIN)
    {
        LOG(INFO)<<"server close ,wait for player login ,time out"<<get_socket_fd(); 
        fini();
    }
}

GateWayPlayer::~GateWayPlayer() {
    LOG(INFO)<<"delete gate way player "<<_player_id;
}


int GateWayPlayer::process_msg(packet_info* info)
{
    int msg_type = info->type;
    if(!is_login())
    {
        if(msg_type != CS_MSG_CLIENT_LOGIN_REQ)
        {
            LOG(ERROR)<<"require data before login"; 
            fini();
        }
    }
    
    switch(msg_type)
    {
        case CS_MSG_CLIENT_LOGIN_REQ:
            do_player_login_request(info);
            break; 
        default:
            LOG(ERROR)<<"get unhandler message ";
    }
    
    

    return 0;
}

void GateWayPlayer::forward_game_msg(const char* data,int data_size)
{
    cs_soccer_player_response response;
    response.body.set_player_id(111);
    response.body.set_player_name("guanlei");
    response.body.set_age(21);
    send_packet_msg(&response);
}

void GateWayPlayer::do_player_login_request(packet_info* info)
{
    LOG(INFO)<<"process login request";
    cs_client_login_request request;
    if(info->size != request.decode(info->data,info->size))
    {
        LOG(INFO)<<"decode message"<<info->type<<"error"; 
        return ;
    }
    LOG(INFO)<<"player request login"<<request.body.player_id();
    LOG(INFO)<<"player request login"<<request.body.player_pwd();
    LOG(INFO)<<"player request login"<<request.body.md5_code();
    GlobalServer->forward_db_message(info);
    //forward to db server 
}
