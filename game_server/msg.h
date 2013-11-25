#ifndef _GAME_MSG_H_
#define _GAME_MSG_H_

#include "../common/head.h"
#include "../net/msg.h"
#pragma pack(1)
/*
 * 玩家传到客户端的消息
 *
 */
#define GAME_SERVER_VERSION "2012.11.14"

typedef enum{
	MSG_TYPE_CLIENT_CHANGE_FORMATION 	= 1001,//玩家换阵型卡
	MSG_TYPE_CLIENT_CHANGE_MOVE			= 1002,//玩家换阵型卡
	MSG_TYPE_CLIENT_CHANGE_PLAYER 		= 1003,//玩家换人
	MSG_TYPE_CLIENT_COACH_SPEAK			= 1004,//喊话
	MSG_TYPE_CLIENT_TERMINAL_MATCH 		= 1005,//快速结束比赛
	MSG_TYPE_CLIENT_PVN_MATCH_START 	= 1006,//
	MSG_TYPE_CLIENT_MATCHING_SUCCESS 	= 1008,//匹配成功
	MSG_TYPE_CLIENT_MATCHING_SUCCESS_START	= 1009,//
	MSG_TYEP_SPEAK_BROCAST				= 1011,		//喊话广播
	MSG_TYPE_CLIENT_USE_TEAM_SKILL		= 1012,	//使用技能成功
	MSG_TYPE_CLIENT_USE_TEAM_SKILL_BROCAST = 1013,//广播
	MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO			= 	1014,		//
	MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO_ACK			= 	1015,		//使用技能信息反馈
	MSG_TYPE_CLIENT_REQUEST_MATCH_START_ACK				= 	1016,	//请求比赛开始反馈
	MSG_TYPE_CLIENT_DEPOIST_OPERATE						= 1017,		//挂机
	MSG_TYPE_CLIENT_QUERY_FAST_MATCH					= 1018,
	MSG_TYPE_CLIENT_QUERY_FAST_MATCH_ACK				= 1019
} PLAYER_ACTION_TYPE;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 玩家到服务器的信息
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//玩家换阵形卡
struct MsgClientChangeFormation:MsgBase{
	int	mid;
	int cid;
	int	time;
	int	formation_id;
	char code[16];
	MsgClientChangeFormation(){
		msg_type = MSG_TYPE_CLIENT_CHANGE_FORMATION;
		msg_size = sizeof(MsgClientChangeFormation);
		is_encode = 0;
	}
};


//换攻击卡
struct MsgClientChangeMove:MsgBase{
	int mid;
	int cid;
	int time;
	int move_id;
	char code[16];
	MsgClientChangeMove(){
		msg_type = MSG_TYPE_CLIENT_CHANGE_MOVE;
		msg_size = sizeof(MsgClientChangeMove);
		is_encode = 0;
	}
};


//换人
struct MsgClientChangePlayer:MsgBase{
	int mid;
	int cid;
	int time;
	int new_formation_pos_map_pid[16];
	int new_suitable[16];
	char code[16];
	MsgClientChangePlayer(){
		msg_type = MSG_TYPE_CLIENT_CHANGE_PLAYER;
		msg_size = sizeof(MsgClientChangePlayer);
		is_encode = 0;
	}
};

//换人
struct MsgClientCoachSpeak:MsgBase{
	int mid;
	int cid;
	int time;
	int speak_type;
	char	code[16];
	MsgClientCoachSpeak(){
		msg_type = MSG_TYPE_CLIENT_COACH_SPEAK;
		msg_size = sizeof(MsgClientCoachSpeak);
		is_encode = 0 ;
	}

};

//客户端快速结束比赛
struct MsgClientTerminalMatch:MsgBase{
	int mid;
	int cid;
	int time;
	char code[16];
	MsgClientTerminalMatch(){
		msg_type = MSG_TYPE_CLIENT_TERMINAL_MATCH;
		msg_size = sizeof(MsgClientTerminalMatch);
		is_encode = 0;
	}
};


//玩家使用技能
struct MsgClientUseSkill:MsgBase{
	MsgClientUseSkill(){
		msg_type = MSG_TYPE_CLIENT_USE_TEAM_SKILL;
		msg_size = sizeof(MsgClientUseSkill);
		is_encode = 0;
	}
	int time_stamp;
	int mid;
	int cid;
	unsigned short team_skill_id;
};

//玩家使用技能广播
struct MsgClientUseSkillBrocast:MsgBase{
	MsgClientUseSkillBrocast(){
		msg_type = MSG_TYPE_CLIENT_USE_TEAM_SKILL_BROCAST;//1013
		msg_size = sizeof(MsgClientUseSkillBrocast);
		is_encode = 0;
	}
	int time_stamp;
	int mid;
	int cid;
	unsigned short team_skill_id;
	unsigned short skill_success_rate;
	unsigned short skill_temp_rate;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * GTOG 游戏服务器传到网关服务器
 */
enum{
	MSG_TYPE_SERVER_REQ	=2000,//server to server msg begin
	MSG_TYPE_MATCH_INFO =2002,
	MSG_TYPE_SERVER_REGISTER = 2003,
	MSG_TYPE_GTOG_SERVER_NEW_MATCH	= 2004,
	MSG_TYPE_GTOG_SERVER_ROUND_PLAYER_DATA = 2005,
	MSG_TYPE_GTOG_SERVER_ROUND_BALL_DATA = 2006,
	MSG_TYPE_GTOG_SERVER_RESULT_DATA = 2007,
	MSG_TYPE_MATCH_MOVE		=2008,	//运行比赛
	MSG_TYPE_GTOG_SERVER_MATCH_END,	//通知gate比赛结束
	MSG_TYPE_GTODB_SERVER_MATCH_END,// 通知数据服务器比赛结束
	MSG_TYPE_GTOG_SERVER_ROUND_EVENT_DATA,//比赛的事件
	MSG_TYPE_GTOG_PLAYER_SKILL_DATA = 2012,//比赛的技能
	MSG_TYPE_GTODB_PLAYER_UPDATE 	= 2013,		//比赛结束后的球员的属性写回
	MSG_TYPE_GTOG_TEAM_SKILL		= 2014,		//比赛的球队的技能使用
	MSG_TYPE_GTOG_TEAM_NEW_FORMATION = 2015,		//新的球队的阵容
	MSG_TYPE_MATCH_CHECK				= 2016,		//检查比赛状态
	MSG_TYPE_GTODB_MATCH_EVENT_WB		= 2017, 		//事件
	MSG_TYPE_GTOG_SERVER_PENTLY_RESULT	= 2018,			//比赛的点球结果
	MSG_TYPE_GTODB_START_ARENA			= 2019
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Client Msg Define Begin
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Server Msg Define Begin
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MsgServerReq: MsgBase{
	int _server_typ;
	int _index;
	MsgServerReq(){
		msg_size = sizeof(MsgServerReq);
		msg_type = MSG_TYPE_SERVER_REQ;
		is_encode = 0;
	}
};


struct MsgServerRegister: MsgBase{
	int _server_type;
	int _index;
	char _version[20];
	MsgServerRegister(){
		msg_size = sizeof(MsgServerRegister);
		msg_type = MSG_TYPE_SERVER_REGISTER;
		is_encode = 0;
	}
};


//通知客户端进入游戏，因为比赛数据已经OK
struct MsgArenaerMatchingSuccessAck:MsgBase{
	MsgArenaerMatchingSuccessAck(){
		msg_type = MSG_TYPE_CLIENT_MATCHING_SUCCESS_START;
		msg_size = sizeof(MsgArenaerMatchingSuccessAck);
		is_encode = 0;
	}
	int mid;
	int uid;
	int op_uid;
};


///////////////////////////////////////////////////////////////////////////////////
//球员的技能
struct MsgPlayerSkill{
	unsigned short skill_id;
	unsigned short skill_level;
	unsigned short skill_chance;
};
//球员的信息
struct MsgPlayerInfo{
	MsgPlayerInfo(){
		memset(player_name,0,20);
	}
	int pid;
	char player_name[20];
	int  level;
	int pos_index;
	short is_gk;
	int attr_numbers;
	int att_value;
	int def_value;
	unsigned short cond;
	unsigned short attr[19];
	unsigned short skill_count;
	MsgPlayerSkill	    player_skills[10];
};

//球队的技能
struct MsgTeamSkill{
	int tactic_id;
	int chance;
};

struct MsgMoveOperator{
	int		uid;
	int 	club_level;
	int		formation_id;
	int 	formation_level;
	int		tactic_id;
	int		propaganda_id;
	int		att_value;
	int		def_value;
	int		default_att_value;
	int		default_def_value;
	int		default_coach_speak;
	int		alias_tactic_plus;
	short	fitness_coach;
	MsgPlayerInfo	player_info[16];
	int team_skill_count;
	MsgTeamSkill	team_skills[10];
};


struct MsgMatchTeamInfo:MsgBase{
	MsgMatchTeamInfo(){
		msg_type = MSG_TYPE_MATCH_INFO;
		msg_size = sizeof(MsgMatchTeamInfo);
		is_encode = 0;
	}

	int mid;
	int type;
	bool need_win;
	bool is_home_all_attack;
	int is_home_in_new_bie;
	int npc_rate;
	int total_time_scale;
	int match_key;
	MsgMoveOperator	op1;
	MsgMoveOperator	op2;
	int	formation1[16];
	int	formation2[16];
};
///////////////////////////////////////////////////////////////////////////////////
struct TimeScalePlayerInfo{
	short time_scale;
	short	pos_x;
	short	pos_y;
	short	state;
};

struct PlayerRoundInfo{
	int	pid;
	short cond;
	int time_sacle_numbers;
	char *_player_info;
};


//比赛的球员的数据
struct MsgMatchPlayerRoundData:MsgBase{
	MsgMatchPlayerRoundData(){
		msg_type = MSG_TYPE_GTOG_SERVER_ROUND_PLAYER_DATA;
		//msg_size = sizeof(MSG_TYPE_SERVER_ROUND_PLAYER_DATA);
		is_encode = 1;
	}
	int mid;
	int	time_scale_start;
	int	total_sacle_number;
	int	is_new_round;
	int	is_match_end;
	int round_end_status;
	int round_type;
	short half_time;
	bool	is_fast_match;
	//struct PlayerRoundInfo
	int	player_count;
	char *_player_round_info;
};

struct BallRoundInfo{
	int time_scale;
	int	x;
	int	y;
	int	z;
	int state;
};

//比赛的求的数据
//*************************************************************************/
struct MsgGameBallRoundData:MsgBase{
	MsgGameBallRoundData(){
		msg_type = MSG_TYPE_GTOG_SERVER_ROUND_BALL_DATA;
		is_encode = 1;
	}
	int mid;
	int	time_scale_start;
	int time_counts;
	char *_ball_round_info;
};


//比赛的事件数据
struct GameEvent{
	int time_scale;
	int src_pid;
	int target_pid;
	int event_type;
};

//比赛中的事件
struct MsgGameEventRoundData:MsgBase{
	MsgGameEventRoundData(){
		msg_type = MSG_TYPE_GTOG_SERVER_ROUND_EVENT_DATA;
		is_encode = 1;
	}
	int mid;
	int	time_scale_start;
	int event_count;
	int time_scale;
	unsigned short cmp_type;
	int from_pid;
	int to_pid;
	bool rst;
	char*	data;
};

//球员的技能
struct PlayerUseSkill{
	int time_scale;
	int pid;
	int skill_id;
};

//比赛中球员使用技能
struct MsgGamePlayerSkillData:MsgBase{
	MsgGamePlayerSkillData(){
		msg_type = MSG_TYPE_GTOG_PLAYER_SKILL_DATA;
		is_encode = 1;
	}

	int mid;
	int time_scale_start;
	int	skill_count;
	char* data;
};

//比赛中球队使用技能
struct MsgGameTeamSkillData:MsgBase{
	MsgGameTeamSkillData(){
		msg_type = MSG_TYPE_GTOG_TEAM_SKILL;
		is_encode = 0;
		msg_size= sizeof(MsgGameTeamSkillData);
	}
	int mid;
	int time_scale_start;
	int team_cid_1;
	int team_cid_2;
	int team_skill_1;
	int	team1_att_energy;
	int	team1_def_energy;
	int	team2_att_energy;
	int	team2_def_energy;
};

struct TeamPoint{
	int cid;
	int	point;
};

//点球数据
struct PentlyResult{
	int		shooter_player_id;
	int		gk_player_id;
	short	shoot_type;
	short	save_type;
	short	shooter_skill;
	short	keep_skill;
	short	shoot_success;
};

//杯赛结束，必须要
struct MsgMatchPentlyResultData:MsgBase{
	MsgMatchPentlyResultData(){
		msg_type = MSG_TYPE_GTOG_SERVER_PENTLY_RESULT;
		msg_size = sizeof(MsgMatchPentlyResultData);
		is_encode = 0;
	}

	int 	mid;
	short 	round_count;
	PentlyResult	pently[10];
};

//
struct MsgMatchArenaStartArena:MsgBase{
	MsgMatchArenaStartArena(){
		msg_type = MSG_TYPE_GTODB_START_ARENA;
		msg_size = sizeof(MsgMatchArenaStartArena);
		is_encode = 0;
	}
	int home_cid;
	int away_cid;
	int	key;
};

struct MsgMatchResultData:MsgBase{
	MsgMatchResultData(){
		msg_type = MSG_TYPE_GTOG_SERVER_RESULT_DATA;
		msg_size = sizeof(MsgMatchResultData);
		is_encode = 0;
	}
	int mid;
	int	time_scale_start;
	TeamPoint	team1;
	TeamPoint	team2;
};
///////////////////////////////////////////////////////////////////////////////////

//游戏服务器的消息，有新比赛
struct MsgGameServerMatchStart:MsgBase{
	int mid;
	int server_index;
	int	uid;
	int	op_uid;
	int match_type;
	MsgGameServerMatchStart(){
		msg_size = sizeof(MsgGameServerMatchStart);
		msg_type = MSG_TYPE_GTOG_SERVER_NEW_MATCH;
		is_encode = 0;
	}
};
///////////////////////////////////////////////////////////////////////////////////
//网关服务器比赛结束
struct MsgGameToGateServerMatchEnd:MsgBase{
	int mid;
	MsgGameToGateServerMatchEnd(){
		msg_size = sizeof(MsgGameToGateServerMatchEnd);
		msg_type = MSG_TYPE_GTOG_SERVER_MATCH_END;
	}
};

//球员的属性写回
struct MsgGameToDbServerPlayerUpdate:MsgBase{
	int 	mid;
	int		strlen;
	char	data[3000];
	MsgGameToDbServerPlayerUpdate(){
		msg_type = MSG_TYPE_GTODB_PLAYER_UPDATE;
		msg_size = sizeof(MsgGameToDbServerPlayerUpdate);
		is_encode = 0;
	}
};

//比赛结束写回比赛的整体数据
struct MsgGameToDbServerMatchEnd:MsgBase{
	int mid;
	int home_cid;
	int away_cid;
	int typ;
	unsigned short home_score;
	unsigned short away_score;
	unsigned short home_possession;
	unsigned short away_possession;
	unsigned short shot_h;
	unsigned short shot_a;
	unsigned short shot_on_h;
	unsigned short shot_on_a;
	unsigned short pently_h;
	unsigned short pently_a;
	char		   statis_data[1];
	MsgGameToDbServerMatchEnd(){
		msg_size = sizeof(MsgGameToDbServerMatchEnd);
		msg_type = MSG_TYPE_GTODB_SERVER_MATCH_END;
		is_encode = 0;
	}
};

struct MsgTeamNewPlayerFormationPos:MsgBase{
	int mid;
	int time_scale_start;
	int home_cid;
	int away_cid;
	int home_new_formation_pos[11];
	int away_new_formation_pos[11];
	MsgTeamNewPlayerFormationPos(){
		msg_size = sizeof(MsgTeamNewPlayerFormationPos);
		msg_type = MSG_TYPE_GTOG_TEAM_NEW_FORMATION;
		is_encode = 0;
	}

};

///////////////////////////////////////////////////////////////////////////////////
//收到DB或者定时器中的事件，开始运行比赛
struct MsgGameRunMatch:MsgBase{
	int mid;
	MsgGameRunMatch(){
		msg_size = sizeof(MsgGameRunMatch);
		msg_type = MSG_TYPE_MATCH_MOVE;
		is_encode = 0;
	}
};

struct MsgGameMatchStatusCheck:MsgBase{
	int mid;
	MsgGameMatchStatusCheck(){
		msg_size = sizeof(MsgGameMatchStatusCheck);
		msg_type = MSG_TYPE_MATCH_CHECK;
		is_encode = 0;
	}
};


//客户端login 成功后发起比赛
struct MsgClientPVNStartMatch:MsgBase{
	int mid;
	int cid;
	int match_type;
	MsgClientPVNStartMatch(){
		msg_type = MSG_TYPE_CLIENT_PVN_MATCH_START;
		msg_size = sizeof(MsgClientPVNStartMatch);
		is_encode = 0;
	}
};

//请求比赛开始的反馈
struct MsgClientStartMatchAck:MsgBase{
	int mid;
	int cid;
	int server_index;
	int	rst;
	bool depoist_change_player;
	bool depoist_use_skill;
	MsgClientStartMatchAck(){
		msg_type = MSG_TYPE_CLIENT_REQUEST_MATCH_START_ACK;
		msg_size = sizeof(MsgClientStartMatchAck);
		is_encode = 0;
	}
};


//挑战成功
struct MsgServerMatchingSuccess:MsgBase{
	MsgServerMatchingSuccess(){
		msg_type = MSG_TYPE_CLIENT_MATCHING_SUCCESS;
		msg_size = sizeof(MsgServerMatchingSuccess);
		is_encode = 0;
	}
	int home_uid;
	int away_uid;
};

//球员喊话广播
struct MsgClientSpeakBrocast:MsgBase{
	MsgClientSpeakBrocast(){
		msg_type = MSG_TYEP_SPEAK_BROCAST;
		msg_size = sizeof(MsgClientSpeakBrocast);
		is_encode = 0;
	}
	int mid;
	int cid;
	unsigned short speak_type;
};

struct MatchEventWB
{
	int timescale;
	int type;
	int cid;
	int pid;
	int op_pid;
};

//比赛中的事件写回数据库
struct MsgGameEventDBWB:MsgBase{
	MsgGameEventDBWB(){
		msg_type = MSG_TYPE_GTODB_MATCH_EVENT_WB;
		is_encode = 0;
		msg_size = sizeof(MsgGameEventDBWB);
	}
	int mid;
	int	time_scale_start;
	int event_count;
	MatchEventWB event[2];
	//GameEvent	data[1];
};

struct MsgClientRequestSkillInfo:MsgBase{
	MsgClientRequestSkillInfo(){
		msg_type = MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO;//1014
		msg_size = sizeof(MsgClientRequestSkillInfo);
		is_encode = 0;
	}
	int time_stamp;
	int mid;
	int cid;
};

//ACK
struct MsgClientRequestSkillInfoAck:MsgBase{
	MsgClientRequestSkillInfoAck(){
		msg_type = MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO_ACK;//1015
		msg_size = sizeof(MsgClientRequestSkillInfoAck);
		is_encode = 0;
	}
	int time_stamp;
	int mid;
	int cid;
	int	state;
};

//托管信令
struct MsgClientDepoistOperate:MsgBase{
	MsgClientDepoistOperate(){
		msg_type = MSG_TYPE_CLIENT_DEPOIST_OPERATE;//1017
		msg_size = sizeof(MsgClientDepoistOperate);
		is_encode = 0;
	}
	int mid;
	int cid;
	bool	depoist_change_player;
	bool	depoist_use_skill;
};


//跳过比赛
struct MsgClientQueryFastMatch:MsgBase{
	MsgClientQueryFastMatch(){
		msg_type = MSG_TYPE_CLIENT_QUERY_FAST_MATCH;
		msg_size = sizeof(MsgClientQueryFastMatch);
		is_encode = 0;
	}
	int mid;
	int operate_cid;
	int time;
	char	code[16];
};

//跳过比赛
struct MsgClientQueryFastMatchAck:MsgBase{
	MsgClientQueryFastMatchAck(){
		msg_type = MSG_TYPE_CLIENT_QUERY_FAST_MATCH_ACK;
		msg_size = sizeof(MsgClientQueryFastMatchAck);
		is_encode = 0;
	}
	int 	mid;
	int 	cid;
	bool	rst;
};


#pragma pack()
#endif
