/*
 * CardManager.cpp
 *
 *  Created on: 2012-3-16
 *      Author: guanlei
 */

#include "GameConfigManage.h"

CGameConfigManager* CGameConfigManager::_instance;

CGameConfigManager::CGameConfigManager() {
	// TODO Auto-generated constructor stub
	InitMoveCard();
	InitFormationCard();
	InitTacticTable();
	LoadCornorConfig();
}

CGameConfigManager::~CGameConfigManager() {
	// TODO Auto-generated destructor stub
}

CGameConfigManager* CGameConfigManager::GetInstance() {
	if (_instance == NULL) {
		_instance = new CGameConfigManager();
	}
	return _instance;
}

bool CGameConfigManager::InitMoveCard() {
	TiXmlDocument doc("config_file/move_tactic_config.xml");
	bool rst = doc.LoadFile();
	if (rst == false) {
		VLOG(1)<<"Error Load config_file/move_tactic_config.xml";
		exit(1);
	}
	TiXmlElement* root = doc.FirstChildElement( "all_move" );
	if ( root )
	{
		TiXmlNode* move_node = NULL;
		for(move_node=root->FirstChild( "move" );move_node!= NULL;move_node=root->IterateChildren(move_node)){
			MoveDefine* move_define = Template_Factory<MoveDefine>::create_instance();

			int move_id = 0;
			int move_type = 0;
			TiXmlElement* move_element = move_node->ToElement();
			move_element->QueryIntAttribute("move_id",&move_id);
			move_element->QueryIntAttribute("type",&move_type);
			move_define->set_move_id(move_id);
			move_define->set_move_typ(move_type);
			TiXmlNode* order_node = NULL;
			for(order_node = move_node->FirstChild("order"); order_node != NULL;order_node = move_node->IterateChildren(order_node)){
				TiXmlElement* order_element = order_node->ToElement();
				int behavior = 0;
				order_element->QueryIntAttribute("order_type",&behavior);
				AttackOrder *order = new AttackOrder((Behavior)behavior);
				order_element->QueryIntAttribute("target_lt",&(order->target_region_lt));
				order_element->QueryIntAttribute("target_rb",&(order->target_region_rb));
				order_element->QueryIntAttribute("target_player_id",&(order->target_player_id));
				order_element->QueryIntAttribute("src_lt",&(order->src_region_lt));
				order_element->QueryIntAttribute("src_rb",&(order->src_region_rb));
				order_element->QueryIntAttribute("src_player_id",&(order->src_player_id));
				if(order->src_player_id == 0){
					order->src_player_id = -1;
				}
				if(order->target_player_id == 0){
					order->target_player_id = -1;
				}
				move_define->add_order(order);
			}
			this->g_move_define_table[move_id] = move_define;
		}
	}

	return false;
}

bool CGameConfigManager::InitFormationCard() {
	TiXmlDocument doc("config_file/formaiton_config.xml");
	bool rst = doc.LoadFile();
	if (rst == false) {
		VLOG(1)<<"Error Load config_file/formation_config.xml";
		exit(1);
	}
	TiXmlElement* root = doc.FirstChildElement( "all_formation" );
	if ( root )
	{
		TiXmlNode* move_node = NULL;
		for(move_node=root->FirstChild( "formation" );move_node!= NULL;move_node=root->IterateChildren(move_node)) {
			FormationDefine* formation = new FormationDefine();

			TiXmlElement* move_element = move_node->ToElement();
			move_element->QueryIntAttribute("formation_id",&(formation->card_id));
			move_element->QueryIntAttribute("att_buff",&(formation->att_buff));
			move_element->QueryIntAttribute("def_buff",&(formation->def_buff));
			//std::string formation_name = move_element->Attribute("formation_name");
			//VLOG(1)<<"formation id"<<formation->card_id;
			TiXmlNode* order_node = NULL;
			for(order_node = move_node->FirstChild("position"); order_node != NULL;order_node = move_node->IterateChildren(order_node)) {
				TiXmlElement* order_element = order_node->ToElement();
				int index = 0;
				order_element->QueryIntAttribute("index",&index);
				order_element->QueryIntAttribute("pos",&(formation->formation[index-2]));
				//order_element->QueryIntAttribute("att_buff",&(formation->att_buff));
				//order_element->QueryIntAttribute("def_buff",&(formation->def_buff));
			}
			g_formation_table[formation->card_id] = formation;
		}
	}

	return false;
}

void CGameConfigManager::InitTacticTable() {

	TiXmlDocument doc("config_file/tactic_move_ref.xml");
	bool rst = doc.LoadFile();
	if (rst == false) {
		VLOG(1)<<"Error Load config_file/tactic_move_ref.xml";
		exit(1);
	}
	TiXmlElement* root = doc.FirstChildElement("all_tactic");
	if(root != NULL) {
		TiXmlNode* tactic_node = NULL;
		for(tactic_node=root->FirstChild( "tactic" );tactic_node!= NULL;tactic_node=root->IterateChildren(tactic_node)) {
			TacticInfo* info = new TacticInfo();

			TiXmlElement* move_element = tactic_node->ToElement();
			move_element->QueryIntAttribute("tactic_id",&(info->tactic_id));
			move_element->QueryIntAttribute("cost_att_energy",&(info->coast_att_energy));
			move_element->QueryIntAttribute("cost_def_energy",&(info->coast_def_energy));
			TiXmlNode* order_node = NULL;
			for(order_node = tactic_node->FirstChild("move"); order_node != NULL;order_node = tactic_node->IterateChildren(order_node)) {
				TiXmlElement* order_element = order_node->ToElement();
				int move_id = 0;
				order_element->QueryIntAttribute("move_id",&move_id);
				info->move_list.push_back(move_id);
			}
			g_tactic_table[info->tactic_id] = info;
		}
	}
}

void CGameConfigManager::LoadCornorConfig() {
	TiXmlDocument doc("config_file/corner_ball_player_position.xml");
	bool rst = doc.LoadFile();
	if (rst == false) {
		VLOG(1)<<"Error Load config_file/corner_ball_player_position.xml";
		exit(1);
	}
	TiXmlElement* root = doc.FirstChildElement("all_formation");
	if(root != NULL) {
		TiXmlNode* formation = NULL;
		for(formation=root->FirstChild("formation");formation!= NULL;formation=root->IterateChildren(formation)) {
			CORNER_PLAYER_CONFIG_LIST_PTR info = new CORNER_PLAYER_CONFIG_LIST();
			TiXmlNode* order_node = NULL;
			int id = 0;
			TiXmlElement* formation_element = formation->ToElement();
			formation_element->QueryIntAttribute("id",&id);
			for(order_node = formation->FirstChild("player"); order_node != NULL;order_node = formation->IterateChildren(order_node)) {
				TiXmlElement* order_element = order_node->ToElement();
				PlayerCornerInfo* player_info = new PlayerCornerInfo();
				order_element->QueryBoolAttribute("att_def",&player_info->is_att_side);
				order_element->QueryIntAttribute("position_index",&player_info->position_id);
				order_element->QueryIntAttribute("pos_x",&player_info->position_x);
				order_element->QueryIntAttribute("pos_y",&player_info->position_y);
				info->push_back(player_info);
			}
			_cornor_player_map[id] = info;	
		}

	}
}

CORNER_PLAYER_CONFIG_LIST_PTR	CGameConfigManager::GetCornerPlayerInfo(int corner_type){
	std::map<int,CORNER_PLAYER_CONFIG_LIST_PTR>::iterator it = _cornor_player_map.find(corner_type);
	if(it == _cornor_player_map.end()){
		return NULL;
	}
	return it->second;
}

MoveDefine* CGameConfigManager::GetMoveCardById(int move_id) {
	std::map<int, MoveDefine*>::iterator itr =
			g_move_define_table.find(move_id);
	if (itr != g_move_define_table.end()) {
		return itr->second;
	}
	return NULL;
}

FormationDefine* CGameConfigManager::GetFormationById(int formation_id) {
	std::map<int, FormationDefine*>::iterator itr =
			this->g_formation_table.find(formation_id);
	if (itr != g_formation_table.end()) {
		return itr->second;
	} else {
		std::map<int, FormationDefine*>::iterator it =
				this->g_formation_table.find(10);
		return it->second;
	}
}


TacticInfo* CGameConfigManager::GetTacticInfoById(int tactic_id){
	std::map<int, TacticInfo*>::iterator itr = g_tactic_table.find(tactic_id);
	if (itr != g_tactic_table.end()) {
		return itr->second;
	}
	return NULL;
}

int CGameConfigManager::GetMoveRandomByTactic(int tactic_id) {
	std::map<int, TacticInfo*>::iterator itr = g_tactic_table.find(tactic_id);
	if (itr != g_tactic_table.end()) {
		if ((itr->second)->move_list.size() <= 0) {
			return -1;
		}
		int index = RAND_INT % (itr->second)->move_list.size();
		int i = 0;
		std::list<int>::iterator itr_move = (itr->second)->move_list.begin();
		while (i < (index)) {
			itr_move++;
			i++;
		}
		return *itr_move;
	}
	return 0;
}

MoveDefine* CGameConfigManager::GetMoveRandom(){
	int total_size = this->g_move_define_table.size();
	int index = RAND_INT%total_size;
	int i = 0;
	std::map<int,MoveDefine*>::iterator itr = g_move_define_table.begin();
	while(i <= index && itr!= g_move_define_table.end()){
		if(i == index){
			return (itr->second);
		}
		i++;
		itr++;
	}
	LOG(ERROR)<<"ERROR RANDOM";
	return NULL;
}

