#ifndef _MATCH_H_
#define _MATCH_H_

#include "../soccer_ai/move_define.h"
#include "../soccer_ai/action_define.h"
#include "../soccer_ai/event_define.h"
#include "../soccer_ai/soccer_config.h"
#include "../soccer_ai/soccer_player.h"
#include "../soccer_ai/enum.h"
#include "../net/IConnection.h"
#include "GameConfigManage.h"
#include "match_recorder.h"
#include "match_engine_events.h"
#include <algorithm>
#include "Event.h"

struct ROUND_TIME {
	int typ;
	int home_away_player_typ;
	int time_interval;
};

typedef std::map<int, ROUND_TIME> VET_ROUND_TIME;
typedef std::map<int, VET_ROUND_TIME> ROUND_TIME_MAP;

void init_move_define_100(MoveDefine *move_define);
omg::String *str_compress(const char *buffer, int len);
ROUND_TIME_MAP get_g_round_time_map();
bool get_is_test();

extern std::map<int, ActionDefine*> g_action_define_table;
//随机的选择一个对应的quality的action

ActionDefine* pickup_random_action_by_quality(int quality);
EventDefine *kup_random_event_by_quality(int quality);

struct round_log_info{
	int mid;
	int home_att;
	int away_att;
	int home_round_count;
	int away_round_count;
	round_log_info(){
		away_att = 0;
		home_att = 0;
		home_round_count = 0;
		away_round_count = 0;
	}
};


struct RoundDetail {
	user_id_t att_uid; // 主场ID
	user_id_t def_uid; // 客场ID
	user_id_t home_uid;
	user_id_t away_uid;
	unsigned index; // 索引
	int round_typ; // 配置文件中配置的本回合类型
	int typ; // 程序中定义的本回合类型
	int start_time_scale; // 开始时间
	int is_first_half; // 暂时无用
	int time_interval; // 减少体力的时间间隔
	int pid; // 球员ID
	bool is_who_kick_off; // 阵型卡确定谁开球
	int	 att_team_skill_id;	//
	int	 round_end_type;
	round_log_info* _round_split_log_info;
	RoundDetail(void) {
		att_uid = 0;
		def_uid = 0;
		index = 0;
		round_typ = 0;
		typ = 0;
		start_time_scale = 0;
		is_first_half = 0;
		time_interval = 0;
		pid = 0;
	}

	void set_RoundDetail(user_id_t att_uid // 主场ID
			, user_id_t def_uid // 客场ID
			, int round_typ // 配置文件中配置的本回合类型
			, int typ // 程序中定义的本回合类型
			, int time_interval // 减少体力的时间间隔
			, int pid // 球员ID
			, int start_time_scale // 开始时间
	) {
		this->att_uid = att_uid;
		this->def_uid = def_uid;
		this->round_typ = round_typ;
		this->typ = typ;
		this->time_interval = time_interval;
		this->pid = pid;
		this->start_time_scale = start_time_scale;
		att_team_skill_id = 0;
		if(att_uid == home_uid){
			_round_split_log_info->home_round_count++;
		}else{
			_round_split_log_info->away_round_count++;
		}
	}
};

//find function for the list
typedef struct finder_t {
	finder_t(int n) :
		age(n) {
	}

	bool operator()(RoundDetail *p) {
		return (int) (p->index) == age;
	}

	int age;
} finder_t;

typedef struct finder_order {
	finder_order(int p) :
		att_uid(p) {
	}

	bool operator()(RoundDetail *p) {
		return (int) (p->att_uid) == att_uid;
	}

	int att_uid;
} finder_order;

class Match {
public:
	int _time_scale;

	user_id_t _uid1;
	user_id_t _uid2;

	bool _uid1_ready_status;
	bool _uid2_ready_status;

	bool _player1_online_status;
	bool _player2_online_status;

	match_id_t _match_id;

	int _match_typ;
	int _total_time_scale;
	bool _need_win;

	int home_player_id;

	int away_player_id;

	unsigned _round_id;

	//是否快速结束
	bool _quick_terminal;

	bool _first_half;

	RoundDetail _round_info;

	round_log_info _round_split_log_info;


	SoccerMatch *_soccer_match;

	FixtureInfo *_fixture_info;

	std::vector<PlayerRedYellowInj> prcyci;

	int _penalty_count; // 点球次数

	std::map<int, PlayerRedYellowInj> _pid_info;

	Vector2D _player_pos;

	//双方的控球率
	double _possession_home;

	double _possession_away;

	int _count_corent;
	int _count_penalty;
	int _count_free;
	int _match_init_zeit;
private:
	bool _is_fast_match;
	std::list<MatchSkillEvent> _all_player_skill_used;

private:
	std::map<int,IConnection*>	_listen_gate_map;

public:
	Match(FixtureInfo *fixture_info, match_id_t match_id, int match_typ,
			user_id_t uid1, user_id_t uid2);
	Match();
	void Init(FixtureInfo *, match_id_t ,int,user_id_t , user_id_t);
	~Match(void);

	void set_penalty_count(int i) {
		_penalty_count = _penalty_count + i;
	}

	void add_listener_list(int key,IConnection* conn){
		_listen_gate_map[key] = conn;
	}

	map<int,IConnection*>& get_listener_map(){
		return _listen_gate_map;
	}

	void borcast_all_gate(const char* msg,int msg_size){
		std::map<int,IConnection*>::iterator itr = _listen_gate_map.begin();
		while(itr != _listen_gate_map.end()){
			if(((itr->second))->connected()){
				((itr->second))->send_data(msg,msg_size);
			}
			itr++;
		}
	}

	int get_penalty_count(void) {
		return _penalty_count;
	}

	int get_home_player_id(void) {
		return home_player_id;
	}

	int get_away_player_id(void) {
		return away_player_id;
	}

	unsigned get_round_id(void) const {
		return _round_id;
	}

	void player_attribute_update(int);

	void update_player_info(FixtureInfo *fixture_info, bool reverse,
			int time_interval);

	void update_player_info_end(FixtureInfo *fixture_info, bool reverse);

	void set_pid_info(int pid, int player_id, bool reverse, int inj,
			int red_card, int yellow_card);

	match_id_t get_match_id(void) const {
		return _match_id;
	}

	int get_team_soccer(int team_id) {
		return _soccer_match->get_team_by_cid(team_id)->get_team_scroe();
	}

	int get_team_possession(int team_id) {
		if (_fixture_info->u1.uid == team_id) {
			return _fixture_info->u1.possession;
		} else {
			return _fixture_info->u2.possession;
		}
	}

	int get_team_shot_count(int team_id) {
		if (_fixture_info->u1.uid == team_id) {
			return _fixture_info->u1.shoot_count
					+ _fixture_info->u1.ms_shoot_count;
		} else {
			return _fixture_info->u2.shoot_count
					+ _fixture_info->u2.ms_shoot_count;
		}
	}

	int get_team_shot_on_count(int team_id) {
		if (_fixture_info->u1.uid == team_id) {
			return _fixture_info->u1.shoot_count;
		} else {
			return _fixture_info->u2.shoot_count;
		}
	}

	int get_team_pently_on_count(int team_id) {
		if (_fixture_info->u1.uid == team_id) {
			return _fixture_info->u1.score_penalty;
		} else {
			return _fixture_info->u2.score_penalty;
		}
	}

	user_id_t get_uid1(void) const {
		return _uid1;
	}

	user_id_t get_uid2(void) const {
		return _uid2;
	}

	FixtureInfo *get_fixture_info(void) {
		return _fixture_info;
	}

	void init_round_list(void) {
	}

	//设置球队的阵形等
	void set_team_info(FixtureInfo*);

	void full_back_team_energy(SoccerTeam*,int);

	int do_match_loop(MatchRecorder &recorder,int&);

	bool player_team_use_skill(int team_id,int skill_id,int&,int&);

	//设置球队的技能
	void set_team_skill_info(MsgMatchTeamInfo&);
	//从fixtureinfo 读入player_info
	void load_player(SoccerPlayer* player, PlayerInfo& player_info);

	void set_new_formation(int cid, int formation_pos[], int suite_able[]);

	//根据pid换人
	bool change_player_use_pid(int cid);

	//检查是否换人等，操作
	void check_team_op_before_move();
	//判断进攻方和防守方的归属
	void judge_attack_defend(MatchEndStatus*);

	SoccerMatch *get_move(void) {
		if (_soccer_match == NULL) {
			_soccer_match = new SoccerMatch();
		}

		return _soccer_match;
	}

	void calc_assist_or_goal_score(SoccerTeam *team, SoccerTeam* op_team,
			bool reverse);

	void who_kick_off(int t_sub_card_typ, RoundDetail *pRoundDetail);

	int match_new_move(MatchRecorder *recorder, int&);
	int match_continue_move(MatchRecorder *recorder, int& run_time_scale);

	//void add_match_buff(std::vector<MatchBuff>::const_iterator cite, SquadInfo &u1, MatchRecorder *recorder);

	void set_prcyci(int red_card, int inj, int pid);

	int get_time_scale(void) {
		return _time_scale;
	}

	//获取当前的轮数
	RoundDetail& get_current_round_info(void) {
		return this->_round_info;
	}

	void get_team_depoist_state(int in_cid,bool& out_des_c,bool& out_use_skill){
		SoccerTeam* team = _soccer_match->get_team_by_cid(in_cid);
		team->get_team_despoit_state(out_des_c,out_use_skill);
	}

	void make_ai_choose(SoccerTeam *team, SquadInfo *squad_info,
			SquadInfo *op_squad_info);

	/* 调整下一轮的进攻顺序，根据round的被中断的类型调整 */
	void fix_next_round(RoundDetail *pCurrent, int match, int uid) {
	}

	void export_all_skill_player_used(std::ostringstream &);

	void export_all_team_cmp_info(std::ostringstream&);

	void export_team_round_split(std::ostringstream&);

	void export_team_skill_info(std::ostringstream&);

	int export_match_statis_info(std::string&);

	bool change_team_middle_one_player(SoccerTeam* team, SquadInfo* squad_info);

	bool change_team_back_one_player(SoccerTeam* team, SquadInfo* squad_info);

	bool change_team_front_one_player(SoccerTeam* team, SquadInfo* squad_info);

	void change_player(SoccerTeam* team, SquadInfo *squad_info, int r_pos,
			int i_pos);

	void npc_choose_move_card(SoccerTeam* team, SquadInfo* squad_info,
			SquadInfo* op_squad_info);

	void npc_choose_action_card(SoccerTeam* team, SquadInfo* squad_info,
			SquadInfo* op_squad_info);

	void npc_choose_event_card(SoccerTeam* team, SquadInfo* squad_info,
			SquadInfo* op_squad_info);

	bool is_match_end();

	void set_quick_terminal(bool);
	bool is_quick_terminal();

	int check_team_skill_use(SoccerTeam* attack_team,int match_typ);

	//是否需要点球
	bool need_pently_shoot() {
		return _need_win;
	}

	bool is_fast_match(){
		return _is_fast_match;
	}

	void set_fast_match(bool fast_match){
		_is_fast_match = fast_match;
	}

	bool is_half_time_now(){
		if(_total_time_scale/2 == _time_scale){
			return true;
		}
		return false;
	}

	void update_player_cond_half_time() {
		SoccerTeam* team = this->_soccer_match->get_team(1);
		for (int i = 0; i < team->get_players_on_pitch_count(); i++) {
			SoccerPlayer* player = team->get_player_on_pitch(i);
			if (player->get_cond() >= 10) {
				player->halftime_resume_cond();
			}
		}

		team = this->_soccer_match->get_team(2);
		for (int i = 0; i < team->get_players_on_pitch_count(); i++) {
			SoccerPlayer* player = team->get_player_on_pitch(i);
			if (player->get_cond() >= 10) {
				player->halftime_resume_cond();
			}
		}
	}
};

#endif /* _MATCH_H_ */
