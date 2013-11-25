/*
 * SoccerPlayerSkill.h
 *
 *  Created on: 2012-4-28
 *      Author: guanlei
 */

#ifndef SOCCERPLAYERSKILL_H_
#define SOCCERPLAYERSKILL_H_
#include "../common/head.h"
#include "player_score.h"


struct SkillEventRef{
	int event_type;
	int	skill_count;
	int	all_skill_id[50];
	int skill_attack_or_defend[50];
	SkillEventRef(){
		skill_count = 0;
	}
	void add_skill(int skill_id,int attack_or_def){
		all_skill_id[skill_count] = skill_id;
		skill_attack_or_defend[skill_count] = attack_or_def;
		skill_count++;
	}

	int check_skill(int skill_id){
		for(int i=0;i< skill_count;i++){
			if(all_skill_id[i] == skill_id){
				return skill_attack_or_defend[i];
			}
		}
		return -1;
	}

};

struct EventSkillRef{
	int skill_id;
	int	all_events[SCORE_END];
	EventSkillRef(){
		skill_id = 0;
		memset(all_events,0,sizeof(all_events));
	}

	void add_event(int event_type){
		all_events[event_type] = 1;
	}

};

class SkillAndEventRefManager{
private:
	SkillEventRef	all_skill_ref[SCORE_END];
	static SkillAndEventRefManager* _m_instance;
public:
	SkillAndEventRefManager(){
		init();
	}

	static SkillAndEventRefManager* GetInstance(){
		if(_m_instance == NULL){
			_m_instance = new SkillAndEventRefManager();
		}
		return _m_instance;
	}

	SkillEventRef* get_all_skill_can_use_list(int type){
		if(type >= SCORE_END){
			return NULL;
		}
		SkillEventRef* ref = &(all_skill_ref[type]);
		return ref;
	}

	//从xml里面读数据
	void init(){
		TiXmlDocument doc("config_file/event_skill_ref.xml");
			bool rst = doc.LoadFile();
			if(rst == false){
				VLOG(1)<<"Error Load config_file/event_skill_ref.xml";
				exit(1);
			}
			TiXmlElement* root = doc.FirstChildElement( "all_event" );
			if (root)
			{
				TiXmlNode* event_node = NULL;
				for(event_node=root->FirstChild( "event" );event_node!= NULL;event_node=root->IterateChildren(event_node)){

					int event_type = 0;
					TiXmlElement* event_element = event_node->ToElement();
					event_element->QueryIntAttribute("event_typ",&event_type);
					TiXmlNode* skill_node = NULL;
					for(skill_node = event_node->FirstChild("skill"); skill_node != NULL;skill_node = event_node->IterateChildren(skill_node)){
						TiXmlElement* order_element = skill_node->ToElement();
						int skill_id = 0;
						order_element->QueryIntAttribute("skill_id",&skill_id);
						int skill_def_or_att = 1;
						order_element->QueryIntAttribute("attack_or_defend",&skill_def_or_att);
						all_skill_ref[event_type].add_skill(skill_id,skill_def_or_att);
					}
				}
			}
	}

};


#endif /* SOCCERPLAYERSKILL_H_ */
