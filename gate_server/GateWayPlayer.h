/*
 * GateWayPlayer.h
 *
 *  Created on: 2012-9-11
 *      Author: guanlei
 */

#ifndef GATEWAYPLAYER_H_
#define GATEWAYPLAYER_H_

#include "../common/head.h"
#include "../common/timer_manager.h"
#include "../net/socketclient.h"
#include "../common/server_application.h"

using namespace omg;

typedef int PLAYER_ID;
typedef int MATCH_ID;

//连接客户端的状态
typedef enum{
    LOGIN_SUCCESS,					//登陆成功
    OFFLINE,						//下线
    WAIT_FOR_ARENAER_MACHING,		//等待竞技场匹配
    MACHING_SUCCESS_FOR_MATCH_START//匹配成功，等待比赛开始
}PLAYER_STATE;

class GateWayPlayer: public socket_client {
    public:
        GateWayPlayer(int fd,sockaddr_in& addr ,epoll_handler* handler,timer_manager* mgr);
        virtual ~GateWayPlayer();

        void init()
        {
            _gate_player_timer.set_owner(this); 
            _gate_player_timer.set_expired(ServerRun->get_run_ms()+5000);
            int ret = _timer_mgr->add_timer(&_gate_player_timer); 
            if(ret != 0)
            {
                LOG(INFO)<<"add timer error !"<<ret;
            }
        }
        
        int get_player_id(){return _player_id;}
        int get_client_sock_fd(){return 0;}
        void on_timeout(timer_manager*);
        void forward_game_msg(const char* data,int data_size);
        int  check_packet_info(char* msg_data,int size,packet_info*);

    private:
        int				_match_watcher_id;
        PLAYER_ID		_player_id;
        time_t			_login_time;
        PLAYER_STATE	_player_state;
        int			_arenaer_stage_id;
        MATCH_ID	_match_watching;
        int			_game_server_binding;
        int 		_zeit_enter_arenar;
        int			_club_attack_value;
        int			_club_defend_value;
        timer_manager* _timer_mgr;
        template_timer<GateWayPlayer,&GateWayPlayer::on_timeout> _gate_player_timer;
};

#endif /* GATEWAYPLAYER_H_ */
