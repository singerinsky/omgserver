#ifndef _CMMMO_DEFINE_H_
#define _CMMMO_DEFINE_H_

typedef int user_id_t;
typedef int match_id_t;

#define FMT_UID "%u"

struct REAL_PLAYER_INFO
{
	int rp_id;
	int ca;
	float g_att;
	float g_def;
	float g_phy;
	float g_speed;
	float g_tec;
	float g_ment;
	float att_finish;
	float att_head;
	float att_drib;
	float att_creat;
	float def_mark;
	float def_tack;
	float def_posit;
	float def_aggr;
	float speed_pace;
	float speed_acc;
	float phy_str;
	float phy_sta;
	float tec_first_touch;
	float tec_cross;
	float tec_pass;
	float tec_move;
	float mental_cons;
	float mental_work;
};

enum TIMER_TYP
{
	timer_register = 10,
	timer_ping,
	timer_match_wait_time_out
};

struct MatchEvent
{
	int timescale;
	int type;
	int cid;
	int pid;
	int op_pid;
};

struct MatchSkillEvent
{
	int timescale;
	int skill_id;
	int pid;
};

struct PlayerRedYellowInj
{
	int pid;
	int red_card; // 红牌 > 0
	int yellow_card; // 黄牌 > 2
	int inj; // 受伤 > 0
};

struct MatchPentlyEvent{
	int		shooter_player_id;
	int		gk_player_id;
	short	shoot_success;
	short	is_in_gate;
	short	shoot_dir;
	short	save_dir;
	short	shooter_skill;
	short	keep_skill;
};

struct DefPlayerID
{
	DefPlayerID(void)
	{
		this->time_scale = 0;
		this->pid = 0;
	}

	DefPlayerID(int t, int p)
	{
		this->time_scale = t;
		this->pid = p;
	}

	int time_scale;
	int pid;
};

struct MatchEndStatus
{
	MatchEndStatus(void)
	{
		_current_end_status = 0;
		_current_end_sub_typ = 0;
		_next_round_typ = 0;
		_injured = 0;
		_at = 0;
		_total_time_scale = 0;
	}

	void ReSet(){
		_current_end_status = 0;
		_current_end_sub_typ = 0;
		_next_round_typ = 0;
		_injured = 0;
		_at = 0;
	}

	int _current_end_status; // 结束类型
	int _current_end_sub_typ; // 结束子类型
	int _next_round_typ; // 下一论类型
	int _injured; // 受伤 黄牌
	int _at;
	int	_total_time_scale;//所有比赛运行的时间
};

#endif /* _CMMMO_DEFINE_H_ */
