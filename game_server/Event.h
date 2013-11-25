#ifndef _EVENT_H_
#define _EVENT_H_

#include "msg.h"



struct MatchBuff
{
	int mid;
	int round_id;
	int pid;
	int buff_typ;
	int buff_value;
	int op_buff_typ;
	int position_id;
	int uid;
	int op_uid;
};



struct MoveOperator
{
    int uid;
    int card_id;
    int move_id;
    int def_id;
    int free; // 任意球
    int cornor; // 角球
    int penalty; // 点球
    int att_value;
    int def_value;
};

struct MoveOperatorResultEvent
{
    uint match_id;

    bool success;
    MoveOperator op1; // 挑战者
    MoveOperator op2; // 被挑战者

    std::vector<MatchBuff> vac_match_buff; // 玩家使用卡牌

    int player_pid_1[16]; // 挑战者
    int player_pid_2[16]; // 被挑战者

    int player_pid_1_suitable[11];
    int player_pid_2_suitable[11];

	int player_pid_1_buff[16];
	int player_pid_2_buff[16];

    /* 比赛结束类型 事件 */
    int match_end_typ; 		// 结束类型
    int match_end_sub_typ; 	// 结束的子类型
	int start_typ; 			// round开始类型
	int next_start_typ; 	// 下一个round开始类型
	int injured;			// 受伤 黄牌
	int match_event_card_typ;

    int union_pid; // 球员唯一ID
    int union_op_pid;

	int zeit; // 事件开始时间
	int uid; // team ID

	int gk_pid_1;
	int gk_pid_2;

	bool is_db_info_error;
};



#endif
