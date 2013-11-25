/*
 * CardManager.h
 *
 *  Created on: 2012-3-16
 *      Author: guanlei
 */

#ifndef CARDMANAGER_H_
#define CARDMANAGER_H_
#include "../common/head.h"
#include "../soccer_ai/move_define.h"

struct FormationDefine
{
	int card_id;
	int card_name;
	int att_buff;
	int def_buff;
	int quality;
	int complex;
	int formation[10];
};

struct TacticInfo{
	int tactic_id;
	int need_level;
	int attr_affect_num;
	int	coast_att_energy;
	int coast_def_energy;
	std::list<int> move_list;
	void dump_all_info(){
		std::list<int>::iterator itr = move_list.begin();
		while(itr != move_list.end()){
			itr++;
			LOG(INFO)<<"tactic "<<tactic_id<<":"<<*itr;
		}
	}
};

struct PlayerCornerInfo{
	int 	position_id;
	bool	is_att_side;
	int		position_x;
	int		position_y;
};

typedef	std::list<PlayerCornerInfo*>	CORNER_PLAYER_CONFIG_LIST;
typedef	CORNER_PLAYER_CONFIG_LIST*		CORNER_PLAYER_CONFIG_LIST_PTR;

class CGameConfigManager {

protected:
	CGameConfigManager();
public:
	virtual ~CGameConfigManager();
	static CGameConfigManager* GetInstance();

	MoveDefine*	GetMoveCardById(int move_card_id);

	FormationDefine* GetFormationById(int formation_id);

	int 	        GetMoveRandomByTactic(int);
	TacticInfo*				GetTacticInfoById(int tactic_id);
	MoveDefine*				GetMoveRandom();
	void			LoadCornorConfig();
	CORNER_PLAYER_CONFIG_LIST_PTR		GetCornerPlayerInfo(int corner_type);

private:
	bool	InitMoveCard();
	bool 	InitFormationCard();
	void	InitTacticTable();
	static CGameConfigManager* _instance;

	std::map<int, MoveDefine *> g_move_define_table;
	std::map<int,FormationDefine*> g_formation_table;
	std::map<int,TacticInfo*>	g_tactic_table;
	std::map<int,CORNER_PLAYER_CONFIG_LIST_PTR>	_cornor_player_map;
};

#endif /* CARDMANAGER_H_ */
