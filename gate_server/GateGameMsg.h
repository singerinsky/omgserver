#ifndef _GATE_MSG_H_
#define _GATE_MSG_H_
#include "../net/msg.h"
#pragma pack(1)
///////////////////////////////////////////////////////////////////////
/***
 *
 * 玩家发送给服务器消息
 *
 *
 */
enum{
	MATCH_PVP_CHAT_MSG	=	3000//PVP比赛中聊天的信令
};


enum{
	MSG_TYPE_CLIENT_CHANGE_FORMATION = 1001,				//玩家换阵型卡
	MSG_TYPE_CLIENT_CHANGE_MOVE = 1002,						//玩家换阵型卡
	MSG_TYPE_CLIENT_CHANGE_PLAYER = 1003,					//玩家换人
	MSG_TYPE_CLIENT_COACH_SPEAK	=	1004,					//喊话
	MSG_TYPE_CLIENT_TERMINAL_MATCH	= 1005,					//结束比赛
	MSG_TYPE_CLIENT_PVN_MATCH_START	 = 1006,				//开始比赛
	MSG_TYPE_CLIENT_DO_ARENA_MATCHING	= 1007,				//开始匹配
	MSG_TYPE_CLIENT_MATCHING_SUCCESS	= 1008,				//匹配成功
	MSG_TYPE_CLIENT_MATCHING_SUCCESS_START	= 	1009,		//匹配比赛成功，且比赛的数据推送完成.
	MSG_TYPE_CLIENT_ENTER_ARENA				= 	1010,		//加入竞技场
	MSG_TYEP_SPEAK_BROCAST					= 	1011,		//喊话广播
	MSG_TYPE_CLIENT_USE_TEAM_SKILL			= 	1012,		//玩家使用技能
	MSG_TYPE_CLIENT_USE_TEAM_SKILL_BROCAST			= 	1013,		//玩家使用技能广播
	MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO			= 	1014,		//
	MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO_ACK			= 	1015,		//
	MSG_TYPE_CLIENT_REQUEST_MATCH_START_ACK				= 	1016,	//请求比赛开始反馈
	MSG_TYPE_CLIENT_DEPOIST_OPERATE						= 	1017,	//请求比赛托管
	MSG_TYPE_CLIENT_QUERY_FAST_MATCH					=	1018,	//跳过比赛
	MSG_TYPE_CLIENT_QUERY_FAST_MATCH_ACK					=	1019,	//跳过比赛
	MSG_TYPE_CLIENT_WATCH_MATCH					=	1020,			//观看比赛
	MSG_TYPE_CLIENT_WATCH_MATCH_ACK					=	1021			//观看比赛ACK
};

static char* gm_login_public_key="guanlei";

enum{
	MSG_TYPE_GM_LOGIN	= 10000,//gm login
	MSG_TYPE_GM_SERVER_INFO	= 10001,//获取服务器信息
	MSG_TYPE_GM_QUERY_MATCH_INFO,	//获取比赛的信息
	MSG_TYPE_GM_MODIFER_MATCH,		//修改比赛的信息
	MSG_TYPE_GM_QUERY_GATE_SERVER_PLAYER_ONLINE//获取在线的用户
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////GM MSG
////////////////////////////////////////////////////////////////////////////


///GM LOGIN......
struct GMMsgGmLogin:MsgBase{
	int gm_uid;
	int time;
	char code[20];
	GMMsgGmLogin(){
		msg_type = MSG_TYPE_GM_LOGIN;
		is_encode = 0;
		msg_size = sizeof(GMMsgGmLogin);
	}
};


struct GMMsgQueryPlayerInfo:MsgBase{
	GMMsgQueryPlayerInfo(){
		msg_size = sizeof(GMMsgQueryPlayerInfo);
		msg_type = MSG_TYPE_GM_QUERY_GATE_SERVER_PLAYER_ONLINE;
		is_encode = 0;
	}

};

//玩家的信息
struct GMMsgQueryPlayerInfoAck:MsgBase{
	int	player_count;
	int	player_id[1024];
	GMMsgQueryPlayerInfoAck(){
		msg_type = MSG_TYPE_GM_QUERY_GATE_SERVER_PLAYER_ONLINE;
		is_encode = 0;
	}
};

//服务器的信息
struct GMMsgQueryServerInfo:MsgBase{
	int server_count;
	char* server_list;
	GMMsgQueryServerInfo(){
		msg_type = MSG_TYPE_GM_SERVER_INFO;
		is_encode = 0;
	}
};

////////////////////////////////////////////
//比赛聊天的信令
struct MsgChatPVP:MsgBase{
	int	send_id;
	int recv_id;
	int send_zeit;
	short msg_len;
	char	msg_content[256];
	MsgChatPVP(){
		msg_type = MATCH_PVP_CHAT_MSG;
		is_encode = 0;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Client Msg Define Begin
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


//喊话
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

//客户端请求比赛开始发起比赛
struct MsgClientPVNStartMatch:MsgBase{
	int mid;
	int cid;
	int	match_type;
	MsgClientPVNStartMatch(){
		msg_type = MSG_TYPE_CLIENT_PVN_MATCH_START;
		msg_size = sizeof(MsgClientPVNStartMatch);
		is_encode = 0;
	}
};

//客户端请求比赛开始发起比赛
struct MsgClientWatchMatch:MsgBase{
	int mid;
	int cid;
	MsgClientWatchMatch(){
		msg_type = MSG_TYPE_CLIENT_WATCH_MATCH;
		msg_size = sizeof(MsgClientWatchMatch);
		is_encode = 0;
	}
};

struct MsgClientWatchMatchAck:MsgBase{
	int mid;
	bool rst;
	MsgClientWatchMatchAck(){
		msg_type = MSG_TYPE_CLIENT_WATCH_MATCH_ACK;
		msg_size = sizeof(MsgClientWatchMatchAck);
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

//服务器定时检测信令
struct MsgServerArenaDoMatch:MsgBase{
	MsgServerArenaDoMatch(){
		msg_type = MSG_TYPE_CLIENT_DO_ARENA_MATCHING;
		msg_size = sizeof(MsgServerArenaDoMatch);
		is_encode= 0;
	}
	int		zeit;
};

struct MsgServerMatchingSuccess:MsgBase{
	MsgServerMatchingSuccess(){
		msg_type = MSG_TYPE_CLIENT_MATCHING_SUCCESS;
		msg_size = sizeof(MsgServerMatchingSuccess);
		is_encode = 0;
	}
	int home_uid;
	int away_uid;
};


///////////////////////////////////////////////////////////////////////////

/////////////////////////////
//服务器消息
enum{
	MSG_TYPE_SERVER_REQ	= 2000,//server to server msg begin
	MSG_TYPE_GTOG_SERVER_NEW_MATCH=2004,//New match start
	MSG_TYPE_GTOG_SERVER_ROUND_PLAYER_DATA,//Match player data
	MSG_TYPE_GTOG_SERVER_ROUND_BALL_DATA,//match ball data
	MSG_TYPE_GTOG_SERVER_RESULT_DATA,//游戏的比赛结果
	MSG_TYPE_GTOG_SERVER_MATCH_END = 2009, //比赛结束
	MSG_TYPE_GTOG_SERVER_EVENT_DATA = 2011,//比赛的事件
	MSG_TYPE_GTOG_SERVER_SKILL_DATA = 2012,//比赛中球员使用的技能
	MSG_TYPE_GTOG_SERVER_TEAM_SKILL_DATA = 2014,//比赛中球员使用的技能
	MSG_TYPE_GTOG_TEAM_NEW_FORMATION = 2015,		//比赛换人返回
	MSG_TYPE_GTOG_SERVER_PENTLY_RESULT	=	2018	//点球
};

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

//msg send to gate server to told gate server new match
struct MsgGameServerMatchStart:MsgBase{
	int mid;
	int server_index;
	int	uid;
	int op_uid;
	int match_type;
	MsgGameServerMatchStart(){
		msg_size = sizeof(MsgGameServerMatchStart);
		msg_type = MSG_TYPE_GTOG_SERVER_NEW_MATCH;
		is_encode = 0;
	}
};



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

struct MsgMatchPlayerRoundData:MsgBase{
	MsgMatchPlayerRoundData(){
		msg_type = MSG_TYPE_GTOG_SERVER_ROUND_PLAYER_DATA;
		//msg_size = sizeof(MSG_TYPE_SERVER_ROUND_PLAYER_DATA);
	}
	int mid;
	//struct PlayerRoundInfo
	int	time_scale_start;
	int total_sacle_number;
	int is_round_end;
	int	is_match_end;
	int round_end_status;
	int	round_type;
	short is_half;
	bool	is_fast_match;
	int	player_count;
	char *_player_round_info;
};

//球的数据
struct MsgMatchBallRoundData:MsgBase{
	MsgMatchBallRoundData(){
		msg_type = MSG_TYPE_GTOG_SERVER_ROUND_BALL_DATA;
	}
	int mid;
	int	time_scale_start;
	int timescale;
	char *_ball_round_info;
};


//比赛的事件数据////////////////////////////////////
struct GameEvent{
	int time_scale;
	int src_pid;
	int	target_pid;
	int event_type;
};

struct MsgMatchEventRoundData:MsgBase{
	MsgMatchEventRoundData(){
		msg_type = MSG_TYPE_GTOG_SERVER_EVENT_DATA;
		is_encode = 1;
	}
	int mid;
	int time_scale_start;
	int event_count;
	char*	data;
};
///////////////////////////////////////////////////////

////////////////////////////////////////////////////////

//球员的技能
struct PlayerUseSkill{
	int time_scale;
	int pid;
	int skill_id;
};

//比赛中球员使用技能
struct MsgGamePlayerSkillData:MsgBase{
	MsgGamePlayerSkillData(){
		msg_type = MSG_TYPE_GTOG_SERVER_SKILL_DATA;
		is_encode = 1;
	}
	~MsgGamePlayerSkillData(){
		delete[] data;
	}
	int mid;
	int time_scale_start;
	int	skill_count;
	char data[1];
};


//比赛中球队使用技能
struct MsgGameTeamSkillData:MsgBase{
	MsgGameTeamSkillData(){
		msg_type = MSG_TYPE_GTOG_SERVER_TEAM_SKILL_DATA;
		msg_size = sizeof(MsgGameTeamSkillData);
		is_encode = 0;
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

///////////////////////////////////////////////////////




//比赛的结果
struct TeamPoint{
	int cid;
	int	point;
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
//比赛结束
struct MsgGameToGateServerMatchEnd:MsgBase{
	MsgGameToGateServerMatchEnd(){
		msg_type = MSG_TYPE_GTOG_SERVER_MATCH_END;
		msg_size = sizeof(MsgGameToGateServerMatchEnd);
		is_encode = 0;
	}
	int mid;
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


//通知客户端进入游戏，因为比赛数据已经OK
struct MsgArenaerMatchingSuccess:MsgBase{
	MsgArenaerMatchingSuccess(){
		msg_type = MSG_TYPE_CLIENT_MATCHING_SUCCESS_START;
		msg_size = sizeof(MsgArenaerMatchingSuccess);
		is_encode = 0;
	}
	int mid;
	int uid;
	int op_uid;
};

//客户端加入竞技场
struct MsgArenaerEnter:MsgBase{
	MsgArenaerEnter(){
		msg_type = MSG_TYPE_CLIENT_ENTER_ARENA;
		msg_size = sizeof(MsgArenaerEnter);
		is_encode = 0;
	}
	int stage_id;
	int player_id;
	int attack_value;
	int defend_value;
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

//玩家使用技能
struct MsgClientUseSkill:MsgBase{
	MsgClientUseSkill(){
		msg_type = MSG_TYPE_CLIENT_USE_TEAM_SKILL;//1012
		msg_size = sizeof(MsgClientUseSkill);
		is_encode = 0;
	}
	int	time_stamp;
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
	unsigned short success;
	unsigned short success_rate;
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
		msg_type = MSG_TYPE_CLIENT_DEPOIST_OPERATE;//1015
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
	int 	mid;
	int 	operate_cid;
	int 	time;
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
	int		cid;
	bool	rst;
};

#pragma pack()
#endif
