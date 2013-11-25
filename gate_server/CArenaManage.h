/*
 * CArenaManage.h
 *
 *  Created on: 2012-8-29
 *      Author: guanlei
 */

#ifndef CARENAMANAGE_H_
#define CARENAMANAGE_H_
#include "GateGameMsg.h"
#include "CMsgDispatcher.h"
#include "GateWayPlayer.h"
#include "GateUserManager.h"

class CArenaManage {
public:
	CArenaManage();
	virtual ~CArenaManage();

	void			pick_player_with_fight(GateWayPlayer* session);
	void			enter_arena(GateWayPlayer*);
	void			leave_arena(int club_id,int stage_id){
		std::list<GateWayPlayer*> *list;
		if(stage_id == 1){
			list = &(this->_all_arenaer_wait_a);
		}else if(stage_id == 2){
			list = &(this->_all_arenaer_wait_b);
		}else if(stage_id == 3){
			list = &(this->_all_arenaer_wait_c);
		}else{
			list = &(this->_all_arenaer_wait_d);
		}
		remove_from_wait_list(list,club_id);
	}

	static	CArenaManage*	get_instance(){
		if(_m_instance == NULL){
			_m_instance = new CArenaManage();
		}
		return 		_m_instance;
	}
	//做匹配
	void 			do_matching(int);
	void 			check_wait_time_out(std::list<GateWayPlayer*>* list_player);
	void			sort_club_by_def_attck(std::list<GateWayPlayer*>&);

	bool remove_from_wait_list(std::list<GateWayPlayer*>* list,int player_id) {
		std::list<GateWayPlayer*>::iterator itr = list->begin();
		while (itr != list->end()) {
			if (player_id == (*itr)->get_player_id()) {
				(*itr)->leave_arenaer();
				list->erase(itr);
				return true;
			}
			itr++;
		}
		return false;
	}

protected:
	static CArenaManage*	_m_instance;
protected:
	typedef	std::list<GateWayPlayer*>::iterator 	ArenaItr;
	std::list<GateWayPlayer*>						_all_arenaer_wait_a;
	std::list<GateWayPlayer*>						_all_arenaer_wait_b;
	std::list<GateWayPlayer*>						_all_arenaer_wait_c;
	std::list<GateWayPlayer*>						_all_arenaer_wait_d;
};

#endif /* CARENAMANAGE_H_ */
