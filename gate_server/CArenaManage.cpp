/*
 * CArenaManage.cpp
 *
 *  Created on: 2012-8-29
 *      Author: guanlei
 */

#include "CArenaManage.h"
#include "CMsgDispatcher.h"

CArenaManage *CArenaManage::_m_instance;

bool cmp(GateWayPlayer* player1,GateWayPlayer* player2){
	return player1->get_attack_defend_value()>player2->get_attack_defend_value();

}

CArenaManage::CArenaManage() {
}

CArenaManage::~CArenaManage() {
}

void CArenaManage::enter_arena(GateWayPlayer* player) {
	std::list<GateWayPlayer*>* list_player = NULL;
	if (player->get_arenaer_stage_id() == 1) {
		list_player = &this->_all_arenaer_wait_a;
	} else if (player->get_arenaer_stage_id() == 2) {
		list_player = &this->_all_arenaer_wait_b;
	} else if (player->get_arenaer_stage_id() == 3) {
		list_player = &this->_all_arenaer_wait_c;
	} else {
		list_player = &this->_all_arenaer_wait_d;
	}

	ArenaItr itr = list_player->begin();
	while(itr != list_player->end()){
		if((*itr)->get_player_id() == player->get_player_id()){
			//delete *itr;
			*itr = player;
			return;
		}
		itr++;
	}
	VLOG(1)<<"player "<<player->get_player_id()<<" enter arenar"<<player->get_arenaer_stage_id();
	list_player->push_back(player);
}

void CArenaManage::do_matching(int arenaer_level){
	std::list<GateWayPlayer*> *arenaer_wait =	NULL;
	if(arenaer_level == 1){
		arenaer_wait = &_all_arenaer_wait_a;
	}else if(arenaer_level == 2){
		arenaer_wait = &_all_arenaer_wait_b;
	}else if(arenaer_level == 3){
		arenaer_wait = &_all_arenaer_wait_c;
	}else{
		arenaer_wait = &_all_arenaer_wait_d;
	}
	if(arenaer_wait->empty()){
		return;
	}

	//按照攻防值排序
	sort_club_by_def_attck(*arenaer_wait);

	std::list<int> _match_success_list;
	ArenaItr itr = arenaer_wait->begin();
	while(itr != arenaer_wait->end()){
		ArenaItr first_itr = itr;
		ArenaItr sec_itr = ++itr;
		GateWayPlayer* first_player = *first_itr;
		if(sec_itr == arenaer_wait->end()){
			break;
		}
		GateWayPlayer* second_player	= *sec_itr;
		MsgServerMatchingSuccess* msg = new MsgServerMatchingSuccess();
		msg->home_uid = first_player->get_player_id();
		msg->away_uid = second_player->get_player_id();
		CMsgEvent *event = new CMsgEvent();
		event->_msg_base = msg;
		event->_msg_type = msg->msg_type;
		CMsgDispatcher::GetInstance()->add_msg_to_queue(event,NULL);
		_match_success_list.push_back(msg->home_uid);
		_match_success_list.push_back(msg->away_uid);
		itr++;
	}

	if(_match_success_list.size()>0){
		std::list<int>::iterator success_itr = _match_success_list.begin();
		while(success_itr != _match_success_list.end()){
			remove_from_wait_list(arenaer_wait,*success_itr);
			success_itr++;
		}
	}


	if(arenaer_wait->size() != 0){
		if(arenaer_level == 3 || arenaer_level == 4){
			check_wait_time_out(arenaer_wait);
			return;
		}else{
			//加入机器人
			time_t	now_time = time(NULL);
			std::list<GateWayPlayer*>::iterator itr_time_out = arenaer_wait->begin();
			while(itr_time_out != arenaer_wait->end()){
				int	start_wait_time = (*itr_time_out)->get_enter_arenar_zeit();
				if(now_time > (start_wait_time + 45)){
					MsgServerMatchingSuccess* msg = new MsgServerMatchingSuccess();
					msg->home_uid = (*itr_time_out)->get_player_id();
					msg->away_uid = -1;
					CMsgEvent *event = new CMsgEvent();
					event->_msg_base = msg;
					event->_msg_type = msg->msg_type;
					CMsgDispatcher::GetInstance()->add_msg_to_queue(event,NULL);
					_match_success_list.push_back(msg->home_uid);
					_match_success_list.push_back(msg->away_uid);
					itr_time_out=arenaer_wait->erase(itr_time_out);
				}else{
					itr_time_out++;
				}
			}
		}
	}

}

void CArenaManage::check_wait_time_out(std::list<GateWayPlayer*>* list_player){
	std::list<GateWayPlayer*>::iterator itr = list_player->begin();
	while(itr != list_player->end()){
		int	start_wait_time = (*itr)->get_enter_arenar_zeit();
		time_t	now_time = time(NULL);
		if(now_time > (start_wait_time + 60)){
			MsgServerMatchingSuccess msg;
			msg.away_uid = 0;
			msg.home_uid = 0;
			(*itr)->send_msg(&msg);
			itr=list_player->erase(itr);
		}else{
			itr++;
		}
	}
}

void CArenaManage::sort_club_by_def_attck(std::list<GateWayPlayer*>& player_list){
	player_list.sort(cmp);
}


