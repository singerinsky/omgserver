#ifndef _SOCCER_MATCH_H_
#define _SOCCER_MATCH_H_

#include "message_dispatcher.h"
#include "soccer_team.h"
#include "soccer_ball.h"
#include "game_entity.h"
#include "player_queue.h"
#include "../common/cmmmo_define.h"
#include "enum.h"
#include "../common/rand_generator.h"

class SoccerJudge;
class SoccerMatch : public GameEntityBase<SoccerMatch>
{
    EntityManager _entity_manager;
    MessageDispatcher _message_dispatcher;
    SoccerTeam _team1;
    SoccerTeam _team2;
    SoccerTeam*	_attack_team;
    SoccerTeam*	_defend_team;

    SoccerBall _ball;
    //SoccerCamera _camera;
    int _time_scale;
    PlayerQueue _player_queue; /* 球员到球的距离 */
    PlayerQueue _player_queue_to_offline;
    PlayerQueue _player_queue_to_goal; /* 球员到球门中心点的距离 */
    int _status;
    bool is_goal_succ;

    std::vector<MatchEvent> _event_frames;
    std::vector<MatchSkillEvent> _skill_frames;
    std::vector<MatchPentlyEvent> _pently_frames;

	 struct PlayerUseSkill{
		int time_scale;
		int pid;
		unsigned short skill_id;
	};

	struct MatchCompareLog {
		int 			time_scale;
		unsigned short	compare_type;
		int 			from_pid;
		int 			to_pid;
		bool 			result;
	};

    std::vector<PlayerUseSkill> _player_skill_used;
    std::vector<DefPlayerID> _dpid;

    Vector2D goal_vec;
    int _kick_typ;

    int union_pid; // 球员PID
    int union_op_pid; // 球员PID
    int uid; // team ID

    int _tema1_player_size;
    int _team2_player_size;

    int _is_number_inj;

    int _fake_shoot_ending; // 假的射门结束

    std::vector<int> _ball_owner; // 当前球的主人

    int _match_event_card_typ; // 触发事件卡类型

    Vector2D _player_pos;

    MatchEndStatus *endStatus;//end type of match

    MatchCompareLog cmp_log;

public:
    SoccerJudge *_judges[3];

    int _count_corent;
    int _count_penalty;
    int _count_free;

    int _round_time;

    SoccerMatch(void);

    ~SoccerMatch(void);

    void set_ball_owner(int cid,int pid, int op_pid, int typ)
    {
    	if (_ball_owner.size() == 0)
    	{
    		_ball_owner.push_back(pid);
    		set_event_frames(cid,pid, op_pid, typ);
    		return;
    	}

    	std::vector<int>::reverse_iterator it = _ball_owner.rbegin();
    	if (it != _ball_owner.rend())
    	{
    		if (*it != pid)
    		{
    			_ball_owner.push_back(pid);
    			set_event_frames(cid,pid, op_pid, typ);
    		}
    	}
    }

    void set_player_pos(double x, double y)
    {
    	_player_pos.x = x;
    	_player_pos.y = y;
    }

    Vector2D get_player_pos(void)
    {
    	return _player_pos;
    }

    int get_match_event_card_typ(void)
    {
    	return _match_event_card_typ;
    }

    void set_match_event_card_typ(int i)
    {
    	_match_event_card_typ = i;
    }

    std::vector<int> get_ball_owner(void)
	{
    	return _ball_owner;
	}

    void enregister(GameEntity *entity)
    {
        _entity_manager.enregister(entity);
    }

    void set_fake_shoot_ending(int i)
    {
    	_fake_shoot_ending = i;
    }

    int get_fake_shoot_ending(void)
    {
    	return _fake_shoot_ending;
    }

    void update_compare_log(unsigned short com_type,
			int from_pid, int to_pid, bool rst) {
		cmp_log.time_scale = this->_time_scale;
		cmp_log.compare_type = com_type;
		cmp_log.from_pid = from_pid;
		cmp_log.to_pid = to_pid;
		cmp_log.result = rst;
	}

    MatchCompareLog* get_compare_log(){
    	return &cmp_log;
    }

    void add_is_number_inj(void)
    {
    	_is_number_inj = _is_number_inj + 1;
    }

    int get_is_number_inj(void)
    {
    	return _is_number_inj;
    }

    int get_union_pid(void)
    {
    	return union_pid;
    }

    void set_union_pid(int pid){
    	this->union_pid = pid;
    }

    int get_union_op_pid(void)
    {
    	return union_op_pid;
    }

    int get_uid(void)
    {
    	return uid;
    }

    void notify(Telegram *message)
    {
        _message_dispatcher.dispatche(message);
    }

    void reset_timer(void)
    {
        _time_scale = 1;
    }

    SoccerBall *get_ball(void)
    {
        return &_ball;
    }

    void set_round_end(int union_pid, int union_op_pid, int uid)
    {
    	this->union_pid 	= union_pid;
    	this->union_op_pid  = union_op_pid;
    	this->uid 			= uid;
    }

//    SoccerCamera *get_camera(void)
//    {
//        return &_camera;
//    }

    std::vector<MatchEvent> *get_event_frames(void)
	{
    	return &_event_frames;
	}

    std::vector<MatchSkillEvent>* get_skill_frames(void){
    	return &_skill_frames;
    }

    std::vector<MatchPentlyEvent>* get_pently_frames(){
    	return &_pently_frames;
    }

    std::vector<DefPlayerID> *get_dpid(void)
	{
		return &_dpid;
	}

    void set_event_frames(int cid,int pid, int op_pid, int type)
	{
    	MatchEvent me;
    	me.pid 			= pid;
    	me.op_pid 		= op_pid;
    	me.cid 			= cid;
    	me.timescale 	= _time_scale;
    	me.type 		= type;
    	_event_frames.push_back(me);
	}

    void set_dpid(int pid)
	{
    	DefPlayerID dp(_time_scale, pid);
		_dpid.push_back(dp);
	}

    virtual void update(void);

    MatchEndStatus *update_match(void);

    int time_scale(void) const
    {
        return _time_scale;
    }

    void set_status(int status)
    {
        _status = status;
    }

    int get_status(void)
    {
        return _status;
    }

    void init_match(int kick_typ
    			  , MoveDefine *attack_move_define
    			  , int formation1[]
    			  , int formation2[]);

    SoccerPlayer *get_player(int team, int index_in_team)
    {
        return (team == 1 ? &_team1 : &_team2)->get_player_on_pitch(index_in_team);
    }

    void set_team1_free_cornor_penalty(int free, int cornor, int penalty);
    void set_team2_free_cornor_penalty(int free, int cornor, int penalty);
    void set_team_att_pid(int i);
    void set_team_goal_state(void);
    void set_team_is_who_kick_off(bool i);
    void set_team_score(int u1_score, int u2_score);
    void set_team_player_pos(double x, double y);

    SoccerPlayer *get_player_by_entityId(int id)
    {
    	GameEntity *pTmp = this->_entity_manager.get(id);
    	if (pTmp == NULL)
    	{
    		return NULL;
    	}

    	return static_cast<SoccerPlayer *>(pTmp);
    }

    PlayerQueue *get_queue_to_ball(void)
    {
        return &_player_queue;
    }

    SoccerTeam *get_team(int index)
    {
        return index == 1 ? &_team1 : &_team2;
    }

    SoccerTeam *get_home_team(){
    	return &(this->_team1);
    }

    SoccerTeam* get_away_team(){
    	return &(this->_team2);
    }

    SoccerTeam *get_attack_team(){
    	return this->_attack_team;
    }

    void set_attack_and_defend_team(SoccerTeam* pAttackTeam,SoccerTeam* pDefendTeam){
    	this->_attack_team = pAttackTeam;
    	this->_attack_team->set_att_or_defend(true);
    	this->_attack_team->set_op_team(pDefendTeam);
    	this->_defend_team = pDefendTeam;
    	this->_defend_team->set_att_or_defend(false);
    	this->_defend_team->set_op_team(pAttackTeam);
    }

    SoccerTeam *get_defend_team(){
        return this->_defend_team;
    }

    SoccerTeam *get_team_by_cid(int cid){
    	return (_team1.get_team_cid() == cid) ? &_team1:&_team2;
    }

    void update_queue_to_ball_and_goal(void);

    void update_queue_to_offline(void);

    void do_judge(void);

    Vector2D &get_goal_vec(void);

    void start_real_match(void)
    {
    	this->_is_match_real_begin = true;
    }

    bool is_match_real_begin(void)
    {
    	return this->_is_match_real_begin;
    }

    int get_round_typ(void)
    {
    	return this->_kick_typ;
    }

    int get_round_index(void)
    {
    	return this->_round_index;
    }

    void set_round_index(int index)
    {
    	this->_round_index = index;
    }

    //计算点球数据
    void calc_pently_match(int&,int&);

    void general_all_attack_pently();

    SoccerPlayer *get_closest_to_ball_def(void);

    SoccerPlayer *get_def_team_closest_to_offline(void);

    SoccerPlayer *get_att_team_closest_to_offline(void);

    void set_team1_current_formation(int);

    void set_team2_current_formation(int);

    void set_match_end_status(int,int,int,int,int);

    void goal_show(void);

    void set_newbie(int newbie)
    {
    	this->_newbie = newbie;
    }

    int get_newbie(void)
    {
    	return this->_newbie;
    }

    MatchEndStatus* get_match_last_end_status(){
    	return this->endStatus;
    };

    void add_skill_frames(int skill_id,int pid){
    	MatchSkillEvent skill;
    	skill.pid = pid;
    	skill.skill_id = skill_id;
    	skill.timescale = this->_time_scale;
    	this->_skill_frames.push_back(skill);
    }

private:
    bool is_outside(void);

    bool _is_match_real_begin;

    int _round_index;

    int _newbie;
};

#endif /* _SOCCER_MATCH_H_ */
