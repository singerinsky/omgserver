#ifndef __PLAYER_SCORE_H__
#define __PLAYER_SCORE_H__

#include "../common/head.h"
#include "soccer_player.h"
#include "soccer_team.h"
#include "common/rand_generator.h"

typedef enum {
	SCORE_RUN_WITH_BALL_ATTACKING = 0, // 带球过人--对人抢断
	SCORE_RUN_WITH_BALL_INTERCEPT = 1, // 带球过人--对球抢断
	SCORE_PASS_BALL_ON_GROUND_INTERCEPT = 2, // 短传--对球断球
	SCORE_PASS_BALL_ON_GROUND_ATTACKING = 3, // 短传--对人断球
	SCORE_CROSS_BALL_HIGH_FROM_THE_BYLING_INTERCEPT = 4, // 长传高空球--对球断球
	SCORE_CROSS_BALL_HIGH_FROM_THE_BYLING_ATTACKING = 5, // 长传高空球--对人断球
	SCORE_HEAD_AT_GOAL = 6, // 头球射门和后卫比较
	SCORE_HEAD_AT_GOAL_GK = 7, // 头球射门和门将比较
	SCORE_SHOOT_AT_GOAL = 8, // 脚球射门和后门比较
	SCORE_SHOOT_AT_GOAL_GK = 9, // 脚球射门和门将比较
	SCORE_AIR_DEF_ATT = 10, // 防守方防高球
	SCORE_FREE_BALL = 11, // 任意球
	SCORE_RECIVE_BALL = 12, //接球
	SCORE_BACK_UP = 13,//'备用';
	SCORE_UNOFFSIDE = 14,//	$config_skill_event[$i++] = '反越位';			14
	SCORE_FAR_SHOOT = 15, // '远射和后卫比';		15
	SCORE_GK_FAR_SHOOT = 16, //'远射和门将比较';		16
	SCORE_PENTLY_BALL = 17, //'点球';			17
	SCORE_GK_KICK_OFF = 18, //守门员开球';		18

	SCORE_GOAL_KICK,//球门球
	SCORE_RUN_WITHOUT_BALL,//无球跑动	 扛人
	SCORE_PENALTY,//点球进球
	SCORE_DIRECT_FREE_KICK,//直接任意球进球
	SCORE_RECEIVE_BALL_FROM_PASS_ATTACKING,//接球和对方球员比较（对方对人）
	SCORE_RECEIVE_BALL_FROM_PASS_INTERCEPT,//接球和对方球员比较（对方对球）
	SCORE_LANG_HIGH_PASS_INTERCEPT,//长传起脚后的 对球
	SCORE_LANG_HIGH_PASS_ATTACKING,//长传起脚前 对人
	SCORE_RECEIVE_BALL_FROM_LONG_PASS_INTERCEPT,//接长传球 对球
	SCORE_RECEIVE_BALL_FROM_LONG_PASS_ATTACKING,//接长传球 对人
	SCORE_OFFSIDE,//越位
	SCORE_PASS_UNIT_DEFEND,//突破联合防守
	SCORE_END
} ScoreType;

//extern bool check_skill_can_use(SoccerPlayer*,ScoreType);
struct StatisCmpInfo{
	int type;
	int total_count;
	int roller_success_count;
	int roller_false_count;
	StatisCmpInfo(){
		total_count = 0;
		roller_success_count = 0;
		roller_false_count = 0;
	}
};

//static StatisCmpInfo	g_cmp_log[SCORE_END];

/* attr 进攻方， defr 防守方， flags 是否需要比较 */
inline bool calc_score_compare(SoccerPlayer* att_player,
		SoccerPlayer* def_player, ScoreType type, double distance = 0.,
		bool flags = false) {
	SoccerTeam* att_team = att_player->get_team();
	SoccerTeam* def_team = def_player->get_team();
	SoccerAttribute& attr = att_player->get_attr();
	SoccerAttribute& defr = def_player->get_attr();
	att_player->check_skill_can_use((int) type);
	def_player->check_skill_can_use((int) type);

	SoccerAttribute& skill_attr = att_player->get_skill_plus_attr();
	SoccerAttribute& skill_defr = def_player->get_skill_plus_attr();
	double soccer_a = 0; // attr
	double soccer_b = 1; // defr

	if (flags) {
		skill_attr.clear();
		skill_defr.clear();
		return flags;
	}
	//g_cmp_log[type].total_count++;
	switch (type) {
		case SCORE_RUN_WITH_BALL_ATTACKING: //带球过人
		case SCORE_RUN_WITH_BALL_INTERCEPT: {
			soccer_a = ((attr[ATT_BALL_CTRL] + skill_attr[ATT_BALL_CTRL]) * 7
					+ (attr[SPEED] + skill_attr[SPEED]) * 3) * 0.56;
			double max_value = max((defr[STRONG]+skill_defr[STRONG]),(defr[SPEED]+skill_defr[SPEED]));
			soccer_b= ((defr[ATT_DEFEND] + skill_defr[ATT_DEFEND]) * 7
						+ (max_value)* 3);
			}
			break;
		case SCORE_PASS_BALL_ON_GROUND_INTERCEPT://短传
		case SCORE_PASS_BALL_ON_GROUND_ATTACKING:
			{
				soccer_a = ((attr[ATT_PASS]+skill_attr[ATT_PASS])*9 + (attr[VISION]+skill_attr[VISION]));
				soccer_b = ((defr[ATT_DEFEND]+skill_defr[ATT_DEFEND])*8 + (defr[AGGRESSIVE]+skill_defr[AGGRESSIVE])*2);
				//if(att_team_id > 0 && def_team_id <0) {//对npc使用碾压
				if(soccer_a >= soccer_b *1.6) {
					break;
				} else if(soccer_a < soccer_b *0.66) {
					soccer_a = 0.;
				}else{
					soccer_a = soccer_a*0.72;
				}
			}
			break;
			case SCORE_CROSS_BALL_HIGH_FROM_THE_BYLING_INTERCEPT:
			case SCORE_CROSS_BALL_HIGH_FROM_THE_BYLING_ATTACKING:
			{
				soccer_a = ((attr[ATT_PASS]+skill_attr[ATT_PASS])*7 + (skill_attr[VISION]+attr[VISION])*3);
				soccer_b = ((skill_defr[ATT_DEFEND]+defr[ATT_DEFEND])*7 + (skill_defr[AGGRESSIVE]+defr[AGGRESSIVE])*3);
			//	if(att_team_id > 0 && def_team_id <0) {//对npc使用碾压
				if(soccer_a >= soccer_b *1.6) {
					break;
				} else if(soccer_a < soccer_b *0.66) {
					soccer_a = 0.;
				}else {
					soccer_a = soccer_a*0.72;
				}
			}
			break;
			case SCORE_AIR_DEF_ATT:
			{
				soccer_a = ((skill_attr[ATT_BALL_CTRL]+attr[ATT_BALL_CTRL])*7 + (attr[MOVES]+skill_attr[MOVES])*3);
				soccer_b = ((defr[ATT_DEFEND]+skill_defr[ATT_DEFEND])*7 + (skill_defr[BOUNCE]+defr[BOUNCE])*3);

				if(soccer_a >= soccer_b *1.4) {
					break;
				}else if(soccer_a < soccer_b *0.55) {
					soccer_a = 0.;	
				}else{
					soccer_a = soccer_a*0.5;
				}
			}
			break;
			case SCORE_HEAD_AT_GOAL:
			{
				soccer_a = ((attr[ATT_SHOOT]+skill_attr[ATT_SHOOT])*5+(attr[HEADER_ACCURACY]+skill_attr[HEADER_ACCURACY])*3 + (skill_attr[MOVES]+attr[MOVES])*2);
				soccer_b = ((skill_defr[ATT_DEFEND]+defr[ATT_DEFEND])*8 + (defr[BOUNCE]+skill_defr[BOUNCE])*2);
				if(soccer_a >= soccer_b *1.6) {
					break;
				} else if((soccer_a >= soccer_b*1.5) && (soccer_a < soccer_b * 1.6)) {
					soccer_a = soccer_a * 0.8;
				} else if((soccer_a >= soccer_b*1.28) && (soccer_a < soccer_b*1.5)) {
					soccer_a = soccer_a * 0.5;
				} else if(soccer_a <= soccer_b*0.66) {
					soccer_a = 0.;
				} else {
					soccer_a = soccer_a*0.7;
				}
			}
			break;
			case SCORE_HEAD_AT_GOAL_GK:
			{
				//用脚射门:a=射门*8+跑位*2 b=扑救*7+指挥防守*3 a/b>1.6时一定进 a/b>1.5时把30%提高到60% a/b>1.4时把30%提高到45%
				//	if(1||(att_team_id > 0)&&(def_team_id > 0)) {
				//先判断人品保护
				soccer_a = ((skill_attr[ATT_SHOOT]+attr[ATT_SHOOT])*6 + (skill_attr[HEADER_ACCURACY]+attr[HEADER_ACCURACY])*2 + (skill_attr[MOVES]+attr[MOVES])*2);
				soccer_b = ((defr[ATT_GK_SAVE]+skill_defr[ATT_GK_SAVE])*7 + (defr[ATT_GK_COM_DEF]+skill_defr[ATT_GK_COM_DEF])*3);
				double att_skill_plus = att_player->get_shoot_with_team_skill_plus();
				att_player->update_team_rp_pr(att_skill_plus);
				att_skill_plus = att_player->get_team_rp_pr();
				soccer_a = soccer_a * (1. + att_skill_plus);
				if(soccer_a >= soccer_b *1.6) {//结果就是碾压
					break;
				} else if((soccer_a >= soccer_b*1.5) && (soccer_a < soccer_b * 1.6)) {
					soccer_a = soccer_a * 0.8;
				} else if((soccer_a >= soccer_b*1.28) && (soccer_a < soccer_b*1.5)) {
					soccer_a = soccer_a * 0.5;
				} else if(soccer_a <= soccer_b*0.66) {
					soccer_a = 0.;
				} else {
					soccer_a = soccer_a*0.3;
				}
			}break;
			case SCORE_SHOOT_AT_GOAL:
			{
				//if(1||(att_team_id > 0) && (def_team_id> 0)) {
				soccer_a = ((skill_attr[ATT_BALL_CTRL]+attr[ATT_BALL_CTRL])*8 + (attr[SPEED]+skill_attr[SPEED])*2);
				soccer_b = ((skill_defr[ATT_DEFEND]+defr[ATT_DEFEND])*8 + (defr[STRONG]+skill_defr[STRONG])*2);
				if(soccer_a >= soccer_b*1.6) {
					break;
				} else if(soccer_a <= soccer_b*0.66) {
					soccer_a = 0.;
				} else {
					soccer_a = soccer_a*0.7;
				}
			}
			break;
			case SCORE_SHOOT_AT_GOAL_GK:
			{
				//	if((att_team_id > 0) && (def_team_id> 0) || ((att_team_id > 0 && def_team_id <0))) {
				soccer_a = ((skill_attr[ATT_SHOOT]+attr[ATT_SHOOT])*8 + (attr[MOVES]+skill_attr[MOVES])*2);
				soccer_b = ((skill_defr[ATT_GK_SAVE]+defr[ATT_GK_SAVE])*7 + (skill_defr[ATT_GK_COM_DEF]+defr[ATT_GK_COM_DEF])*3);
				double att_skill_plus = att_player->get_shoot_with_team_skill_plus();
				att_player->update_team_rp_pr(att_skill_plus);
				att_skill_plus = att_player->get_team_rp_pr();
				soccer_a = soccer_a * (1. + att_skill_plus);
				if(soccer_a >= soccer_b*1.6) {//结果本身即是碾压
					break;
				} else if((soccer_a >= soccer_b*1.5) && (soccer_a < soccer_b*1.6)) {
					soccer_a = soccer_a*0.8;
				} else if(soccer_a >= soccer_b*1.2 && (soccer_a < soccer_b*1.5)) {
					soccer_a = soccer_a*0.5;
				} else if(soccer_a <= soccer_b*0.66) {
					soccer_a = 0.;
				} else {
					soccer_a = soccer_a*0.3;
				}
			}
			break;
			case SCORE_FREE_BALL:
			{
				soccer_a = ((skill_attr[FREE_KICK]+attr[FREE_KICK])*10)*0.35;
				soccer_b = (skill_defr[ATT_GK_SAVE]+defr[ATT_GK_SAVE])*3 + (skill_defr[ATT_GK_COM_DEF]+defr[ATT_GK_COM_DEF]) *7;
			}
			break;
			case SCORE_RECIVE_BALL:
			{
				soccer_a = ((skill_attr[MOVES]+attr[MOVES])*6 + (attr[ATT_PASS]+skill_attr[ATT_PASS])*4);
				int max_value = max((defr[STRONG]+skill_defr[STRONG]),(defr[SPEED]+skill_defr[SPEED]));
				soccer_b = (max_value * 5 + (skill_defr[ATT_DEFEND]+defr[ATT_DEFEND])*5);
				double value = 0;
				if(distance < 5*METER_TO_POINT) {
					value = 1;
				} else if(distance >=5*METER_TO_POINT && distance < 10*METER_TO_POINT) {
					value = 0.9;
				} else if(distance >= 10*METER_TO_POINT && distance < 15*METER_TO_POINT) {
					value = 0.8;
				} else if(distance > 15*METER_TO_POINT) {
					value = 0.7;
				}

				soccer_a = soccer_a*value;
				if(soccer_a > soccer_b*1.2){
					break;
				}
			}
			break;
			case SCORE_PENALTY:
			{
				soccer_a = (attr[PENALTY] + skill_attr[PENALTY]) *3 + (attr[ATT_SHOOT] + attr[ATT_SHOOT])*7;
				soccer_b = (defr[ATT_GK_SAVE]+defr[ATT_GK_SAVE]) * 8;
				soccer_a = soccer_a *0.7;
			}
			break;
			case SCORE_GK_FAR_SHOOT:
			{
				soccer_a = (attr[ATT_SHOOT] + skill_attr[ATT_SHOOT]) *7 + (attr[LONG_RANGE] + attr[LONG_RANGE])*3;
				soccer_a = 0.2*soccer_a;
				soccer_b = (defr[ATT_GK_SAVE]+defr[ATT_GK_SAVE]) * 4+ (defr[ATT_GK_COM_DEF]+defr[ATT_GK_COM_DEF]) * 6;
			}
			break;
			case SCORE_GK_KICK_OFF:{
				soccer_a = attr[KICKOFF];
				soccer_b = defr[KICKOFF];
				if(soccer_a > soccer_b * 1.2){
					break;
				}
				soccer_a = soccer_a * 0.4;
			}
			break;
			default:
			{
				LOG(ERROR) << "error ScoreType:" << type;
			}
			break;
		}
		skill_attr.clear();
		skill_defr.clear();
		double rst = soccer_a/soccer_b;
		double rand_value = RAND_DBL;
		bool cmp_rst = rst > rand_value;
		if(cmp_rst) {
			if(type == SCORE_SHOOT_AT_GOAL_GK || type == SCORE_HEAD_AT_GOAL_GK){
				att_player->reset_team_rp_pr();
			}
		}
		att_team->log_team_cmp_info(att_player->get_union_pid(),def_player->get_union_pid(),type,cmp_rst);
		def_team->log_team_cmp_info(att_player->get_union_pid(),def_player->get_union_pid(),type,cmp_rst);
		return cmp_rst;
	}

#endif /* __PLAYER_SCORE_H__ */
