#ifndef _ENUM_H_
#define _ENUM_H_

#include "def.h"

enum BALL_POS{
	FRONT_POS	=	1,//前场
	MIDDLE_POS	=	2,//中场
	BACK_POS	=	3//后场
};


enum KICK_TYP
{
	NORMAL_KICK 		= 0, // 普通
	MIDDLE_INJURY_KICK 	= 1, // 中场补时
	END_INJURY_KICK 	= 2, // 下半场补时
	MIDDLE_KICK_OFF 	= 3, // 下半场开球
	KICK_OFF 			= 4, // 上半场开场
	GOAL_KICK_OFF 		= 5, // 进球
	FREE_KICK_OFF 		= 6, // 任意球
	PENALTY_KICK_OFF 	= 7, // 点球
	CORNER_KICK_UP_OFF 	= 8, // 角球上
	GK_KICK_OFF 		= 9, // 门将开球
	THROW_IN 			= 10,
	COUNTER_ATTACK 		= 11,
    ADD_ROUND_VALUE 	= 12, // 添加round
    SHOOTOUT_PENALTY 	= 13, // 点球大战
    CORNER_KICK_DOWN_OFF= 14, // 角球下
    DEFEND_AND_ATTCK    = 15, // 防守反击

    ENUM_END_KICK_TYP
};

/*此类型主要是为了显示flash端的图片 ,下一轮的开始的类型*/
enum NextRoundTyp
{
	N_NORMAL_KICK = 100,//普通开始
	N_MIDDLE_KICK,//中间开球
	N_CORNER_KICK,//角球
	N_FREE_KICK,//任意球
	N_PENALTY_KICK,//点球
	N_SHOOTOUT_PENALTY_KICK,//点球大战
	N_INJURY_KICK,//补时
	N_MATCH_END,//比赛结束(换球衣)
	N_SEC_HALF_KICK,//下半场开始
	N_PLUS_KICK=109,		//附加赛
	N_CARD_ADD_ROUND_KICK,	//卡牌添加
	N_STRIKE_BACK			//防守反击
};

/*此类型主要是为了显示flash端的图片，此轮比赛结束的大类型 */
enum RoundEndTyp
{
	END_GOAL = 200,		//进球
	END_GOAL_FAIL,		//射门没有进
	END_FOULED,			//犯规
	END_BREAK,			//正常断球
	END_ATTACK_MISTAKE,	//进攻失误
	END_NORMAL_END,		//普通结束
	END_TIMEOUT,		//超时
	END_HALF_TIME		//半场时间
};

/*此类型主要是为了显示flash端的图片，此轮比赛结束的子类型 */
enum RoundEndSubTyp
{
	PLAY = 0,
	GOAL_HEAD = 1,						//头球进球	1
	GOAL_FOOT,							//用脚进球
	GOAL_PENALTY,						//点球进球
	GOAL_DIRECT_FREE_KICK,				//直接任意球进球
	GOAL_OWN,							//乌龙球
	SHOT_HEAD_FAIL_GK_SAVE,				//门将扑住头球射门	6		球门前	1前锋，1门将，1后卫
	SHOT_HEAD_FAIL_GK_PUSH,				//门将扑出头球射门	7		球门前	1前锋，1门将，1后卫
	SHOT_HEAD_FAIL_GK_PUSH_OUTSIDE,		//门将扑出头球射门，出底线	8		球门前	1前锋，1门将，1后卫
	SHOT_FOOT_FAIL_GK_SAVE,				//门将扑住用脚射门	9		球门前	1前锋，1门将，1后卫
	SHOT_FOOT_FAIL_GK_PUSH,				//门将扑出用脚射门	10		球门前	1前锋，1门将，1后卫
	SHOT_FOOT_FAIL_GK_PUSH_OUTSIDE,		//门将扑出用脚射门，出底线	11		球门前	1前锋，1门将，1后卫
	SHOT_PENALTY_FAIL_GK_SAVE,			//门将扑住点球	12		点球点	1前锋，1门将
	SHOT_PENALTY_FAIL_GK_PUSH,			//门将扑出点球	13		点球点	1前锋，1门将
	SHOT_DIRECT_FREE_KICK_FAIL_GK_SAVE,	//门将扑住任意球	14		禁区外	1前锋，1门将，人墙
	SHOT_DIRECT_FREE_KICK_FAIL_GK_PUSH, //门将扑出任意球	15		禁区外	1前锋，1门将，人墙
	SHOT_PENALTY_FORWARD_OUTTARGET,		//点球前锋射门偏出	16		点球点	1前锋，1门将
	SHOT_PENALTY_FORWARD_CROSSBAR,		//点球前锋射中门楣	17		点球点	1前锋，1门将
	SHOT_PENALTY_FORWARD_GOALPOST,		//点球前锋射中门柱	18		点球点	1前锋，1门将
	SHOT_DIRECT_FREE_KICK_FORWARD_OUTTARGET,	//直接任意球前锋射门偏出	19		禁区外	1前锋，1门将，人墙
	SHOT_DIRECT_FREE_KICK_FORWARD_CROSSBAR,		//直接任意球前锋射中门楣	20		禁区外	1前锋，1门将，人墙
	SHOT_DIRECT_FREE_KICK_FORWARD_GOALPOST,		//直接任意球前锋射中门柱	21		禁区外	1前锋，1门将，人墙
	SHOT_FORWARD_OUTTARGET,						//前锋射门偏出	22		球门前	1前锋，1门将，1后卫
	SHOT_FORWARD_CROSSBAR,						//前锋射中门楣	23		球门前	1前锋，1门将，1后卫
	SHOT_FORWARD_GOALPOST,						//前锋射中门柱	24		球门前	1前锋，1门将，1后卫
	SHOT_DIRECT_FREE_KICK_WALL,					//前锋任意球打人墙	25		禁区外	1前锋，1门将，人墙
	SHOT_DEFENDER_INTERUPT_OUTSIDE,				//被后卫挡出底线	26		球门前	1前锋，1门将，1后卫
	SHOT_DEFENDER_INTERUPT,						//被后卫挡出，未出界	27		球门前	1前锋，1门将，1后卫
	FOUL_OFFLINE,								//越位	28		球场中	2前锋，3后卫
	IN_RESTRICTED_HAND_BALL,					//禁区内手球	29		禁区内	1前锋，1后卫
	OUT_RESTRICTED_HAND_BALL,					//禁区外手球	30		禁区外	1前锋，1后卫
	FOUL_PULL_SHIRT,							//禁区外拉球衣	31		禁区外	1前锋，1后卫
	IN_RESTRICTED_FOUL_SLIDE,					//禁区内铲倒人	32		禁区内	1前锋，1后卫
	OUT_RESTRICTED_FOUL_SLIDE,					//禁区外铲倒人	33		禁区外	1前锋，1后卫
	OUT_RESTRICTED_FOUL_HEAD,					//禁区外头球压人	34		禁区外	1前锋，1后卫	FOUL_HEAD
	OUT_RESTRICTED_FOUL_ELBOW,					//禁区外肘击	35		禁区外	1前锋，1后卫
	OUT_RESTRICTED_FOUL_CHARGE,					//禁区外撞人	36		禁区外	1前锋，1后卫
	BREAK_TACKLE,								//抢断带球	37		球场中	1前锋，1后卫
	BREAK_CHARGE,								//合理冲撞	38		球场中	1前锋，1后卫
	BREAK_TACKLE_PASS,							//铲球传球瞬间	39		球场中	1前锋，1后卫
	BREAK_INTERUPT_PASS,						//打断传出球	40		球场中	1前锋，1后卫
	BREAK_INTERUPT_RECV_PASS,					//拦截接地面球	41		球场中	1前锋，1后卫
	BREAK_INTERUPT_RECV_CROSS,					//拦截接高空球	42		球场中	1前锋，1后卫
	BREAK_INTERUPT_FREE_BALL,					//拦截无主球	43		球场中	1前锋，1后卫
	BREAK_INTERUPT_GOAL_KICK,					//拦截门球开球	44		禁区内	1前锋，1门将
	BREAK_GK_GET_CORNER,						//角球门将摘高球	45		球门前	4前锋，6后卫，1门将
	BREAK_GK_GET_CROSS,							//长传门将摘高球	46		禁区内	1前锋，1后卫，1门将
	OUTSIDE_SIDELINE,							//球出边线	47		边线	1前锋，1后卫
	OUTSIDE_ENDLINE,							//球出底线	48		底线	1前锋，1后卫
	OVERTIME,									//超时	49		球场中	无人
	END_YELLOW_CARD,							//黄牌	50
	END_YELLOW_TO_RED,							//黄牌变红牌	51
	END_INJURED,								//受伤	52
	FIRST_HALF_END,								//上半场结束	53
	SHOT_FAIL_GK_OUTSIDE,						//被后卫挡出底线	26		球门前	1前锋，1门将，1后卫
	SECOND_HALF_END								//下半场结束	54
};

enum
{
	C_NULL = 0,
	C_YELLOW_CARD = 1,								//黄牌
	C_YELLOW_TO_RED,								//黄牌变红牌
	C_INJURED								//受伤
};

//建筑物对球队造成的影响.
enum ConEffect
{
	HOSPITAL_EFFECT = 5
};

#endif
