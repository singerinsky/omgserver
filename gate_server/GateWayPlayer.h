/*
 * GateWayPlayer.h
 *
 *  Created on: 2012-9-11
 *      Author: guanlei
 */

#ifndef GATEWAYPLAYER_H_
#define GATEWAYPLAYER_H_

#include "../common/head.h"
#include "../net/epoll_socket.h"

typedef int PLAYER_ID;
typedef int MATCH_ID;

//连接客户端的状态
typedef enum{
	LOGIN_SUCCESS,					//登陆成功
	OFFLINE,						//下线
	WAIT_FOR_ARENAER_MACHING,		//等待竞技场匹配
	MACHING_SUCCESS_FOR_MATCH_START//匹配成功，等待比赛开始
}PLAYER_STATE;

class GateWayPlayer {
public:
	GateWayPlayer(EPollSocket* socket,PLAYER_ID player_id);
	virtual ~GateWayPlayer();

	void 	reload_player_info(EPollSocket* socket,PLAYER_ID player_id){
		_login_time = time(NULL);
		this->_socket = socket;
		this->_player_id = player_id;
		_socket->update_socket_state(CONN_VRIFY);
	}
	void	send_msg(const MsgBase*);
	void	destory_me(){
		delete _socket;
		_player_state = OFFLINE;
	}

	void set_arenaer_stage_id(int stage_id){
		_arenaer_stage_id = stage_id;
	}

	int get_arenaer_stage_id(){
		return _arenaer_stage_id;
	}

	int get_client_sock_fd(){
		return _socket->fd;
	}

	PLAYER_ID	get_player_id(){
		return _player_id;
	}

	bool enter_arenar(int stage_id){
		_zeit_enter_arenar = time(NULL);
		_arenaer_stage_id= stage_id;
		_player_state = WAIT_FOR_ARENAER_MACHING;
	}

	void leave_arenaer(){
		_player_state = LOGIN_SUCCESS;
		_arenaer_stage_id = 0;
	}

	int get_enter_arenar_zeit(){
		return this->_zeit_enter_arenar;
	}

	EPollSocket*	get_epoll_socket(){
		return this->_socket;
	}

	PLAYER_STATE	get_player_state(){
		return this->_player_state;
	}

	void add_match_watch(int mid){
		_match_watcher_id = mid;
	}

	int get_match_watch(){
		return _match_watcher_id;
	}

	void set_attack_value(int value){
		this->_club_attack_value = value;
	}

	void set_defend_value(int value){
		this->_club_defend_value = value;
	}

	int get_attack_defend_value(){
		return _club_attack_value+_club_defend_value;
	}

	// bool operator < (GateWayPlayer* t1) {
	//	 return get_attack_defend_value() < t1->get_attack_defend_value();
	 //}

private:
	int				_match_watcher_id;
	PLAYER_ID		_player_id;
	EPollSocket* 	_socket;
	time_t			_login_time;
	PLAYER_STATE	_player_state;
	int			_arenaer_stage_id;
	MATCH_ID	_match_watching;
	int			_game_server_binding;
	int 		_zeit_enter_arenar;
	int			_club_attack_value;
	int			_club_defend_value;
};

#endif /* GATEWAYPLAYER_H_ */
