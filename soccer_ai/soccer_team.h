#ifndef _SOCCER_TEAM_H_
#define _SOCCER_TEAM_H_

#include "state.h"
#include "attack_order.h"
#include "move_define.h"
#include "soccer_player_state.h"
#include "soccer_team_state.h"
#include "soccer_formation.h"
#include "state_type.h"
#include "../game_server/GameConfigManage.h"

class SoccerPlayer;
class SoccerMatch;

enum
{
    GOAL_ATTR_ANTIC,
    GOAL_ATTR_CONCENTRATION,
    GOAL_ATTR_AERIAL,
    GOAL_ATTR_JUMP,
    GOAL_ATTR_DETERMINE,
    GOAL_ATTR_HANDLE
};

//喊话
enum{
	SPEAK_WAIT_FOR,			//别急，耐心寻找机会
	SPEAK_MORE_PASS,		//多传地面球
	SPEAK_MORE_CORSS,		//多传高球
	SPEAK_MORE_EMPTY_PASS,	//多往空当传球
	SPEAK_MORE_FOOT_PASS,	//多传脚下球
	SPEAK_MORE_SPACE,		//站位拉开些
	SPEAK_LESS_SPACE,		//站位紧凑些
	SPEAK_ATTACK_ATTACK,	//给我压上，压迫他们
	SPEAK_DEFEND_ATTACK,	//往回收，引蛇出洞
	SPEAK_KILL_KICK,		//往死里踢，废他几个
	SPEAK_GENTLEMEN,		//出脚温柔些
	SPEAK_END
};



//球队技能
typedef enum{
	TACTIC_MIDDLE_PUSH	=	1,	//中路推进
	TACTIC_LEFT_ATTACK,			//左边路强攻
	TACTIC_RIGHT_ATTACK,		//右边路强攻
	TACTIC_BOTH_ATTACK,			//两翼齐飞
	TACTIC_ALL_ATTACK,			//全线进攻
	TACTIC_ALL_DEFEND,			//龟缩防守
	TACTIC_FRONT_TACLE,			//前场逼抢
	TACTIC_BACK_INSERT,			//后排插上
	TACTIC_QUICK_STRIKE_BACK,	//快速反击
	TACTIC_MIDDLE_CTRL,			//中场控球
	TACTIC_FAKE_OUT,			//声东击西
	TACTIC_STONE_STRIKE_BACK,	//混凝土防反
	TACTIC_UNIVERSE_CTRL,		//宇宙队式控球
	TACTIC_GALAXY_QUICK_ATTACK,	//银河队式快攻
	TACTIC_ATT_DEF				//全攻全守
}TEAM_SKILL_TYPE;


struct ActionItem
{
    typedef enum
    {
        GOAL, 				// 进球
        SHOOT, 				// 射门
        CROSS, 				// 过人
        PASS, 				// 传球
        BEBREAK, 			// 抢断
        BESLIDE,
        PS_RED_CARD, 		// 红牌 > 0
        PS_YELLOW_CARD, 	// 黄牌 > 2
        PS_INJ, 			// 受伤 > 0
        GOAL_PENALTY, 		// 进点球
        GOAL_FREE, 			// 任意球进球
        SHOOT_OUTSIDE		// 射偏
    } Type;

    int union_pid;
    Type type;
};

struct GK_Pos_Item
{
	Vector2D _pos;
	int		 _time_scale;
};

typedef enum
{
	LOSER_MODE 	= 0, 	/* 必然不进球 */
	DS_MODE	   	= 1,	/* 普通 */
	GOD_MODE	= 2		/* 必然进球 */
}Team_mode;

struct TeamSkill{
	int tactic_id;
	int chance;
};

struct TeamCmpInfo{
	int pid;
	int op_pid;
	int type;
	bool rst;
};


class SoccerTeam : public GameEntityBase<SoccerTeam>
{
    enum { PLAYER_COUNT = 10 };

    friend class SoccerPlayer;



    State<SoccerTeam> *_state;
    std::map<int, double> goal_attr;

    SoccerPlayer *_receiving_player;
    SoccerPlayer *_closest_player;
    SoccerPlayer *_controlling_player;
    SoccerPlayer *_supporting_player;

    SoccerPlayer *_marking_player;
    SoccerPlayer *_minding_player;
    SoccerPlayer *_breaking_player;
    SoccerPlayer *_air_defend_player;
    SoccerPlayer *_pass_defend_player;

	typedef std::vector<SoccerPlayer*> PLAYER_VEC;
	typedef std::vector<SoccerPlayer*>::iterator PLAYER_ITR;

    std::vector<SoccerPlayer *> _players_on_pitch;
    std::map<int,TeamSkill>	_team_skills;

    typedef std::pair<double, SoccerPlayer *> PAIR_PLAYER_DIS;

    std::map<double, SoccerPlayer *> _players_distance_to_ball_map;
    MoveDefine *_move_define;
    AttackOrder *_order;
    SoccerMatch *_match;
    SoccerFormation _formation;
    int	_current_formation_id;
    int	current_move_id;

    std::vector<ActionItem> _action_list;
    SoccerTeam *_op_team;

    std::list<GK_Pos_Item> _gk_pos_list;
    int *player_mark_flag;

    SoccerPlayer *_gk_player;
    int _team_level;
    int _kick_off_player;
    int _kick_support_player;

    struct cornor_player
    {
    	cornor_player(void)
    	{
    		this->kick_support_player = 0;
    		this->x = 0;
    		this->y = 0;
    	}

    	cornor_player(int ki, double x, double y)
    	{
    		this->kick_support_player = ki;
    		this->x = x;
    		this->y = y;
    	}

        int kick_support_player;
        double x;
        double y;
    };

    std::map<int, cornor_player> _cornor_map;
    int _free;
    int _cornor;
    int _penalty;
    int _cornor_tactical;
    bool _card_can_avoid_offside;
    bool _card_can_force_offside;
    int _att_pid;
    std::map<int, double> _cons_effect_map;
    Vector2D _player_pos;
    int _auto_change_count;
    bool _who_kick_off;

    /* 球队的每个防线上的球员的数量 */
    int _line_number[10];

    /* 球队的最后一条防线的index */
    int _back_line;

    //球队的阵型等级
    int		_formation_level;
    /* 球队的攻防指数 */
    double _att_value;
    double _def_value;

    //球队的技能使用
    int _tactic_used_id;
    int	_last_round_tactic_used;

    /* 球队的控球率 */
    double _possession;

    int _has_offside;
    SoccerPlayer *_offside_player;
    int _team_club_id;
    bool _is_att_team;
    /* 球队的模式,是否是无敌模式 */
    Team_mode _team_mode;

    int _newbie_state;

    int _is_round_add;

    /* 当前用的move的卡牌复杂度*/
    int _move_complex;

    bool _is_att_side;

    int _total_attack_count;

    //球队当前的魔法值上限
    int _top_attack_mp;
    int _top_def_mp;

    //当前的球队的魔法值
    int _team_attack_mp;
    int _team_def_mp;

    double	_skill_success_rate;

public:
    SoccerTeam(int id, SoccerMatch *match);
    virtual ~SoccerTeam(void);

    int get_total_attatck_count(){
    	return this->_total_attack_count;
    }

    void set_total_attack_count(int value){
    	this->_total_attack_count = value;
    }

    void set_att_or_defend(bool is_att){
    	_is_att_side = is_att;
    }

    bool is_att_side(){
    	return _is_att_side;
    }

    void set_player_pos(double x, double y)
    {
        _player_pos.x = x;
        _player_pos.y = y;
    }

    void set_who_kick_off(bool i)
    {
        _who_kick_off = i;
    }

    bool get_who_kick_off(void)
    {
        return _who_kick_off;
    }

    void set_team_score(int socre)
    {
    	_score = socre;
    }

    void add_team_score(){
    	_score++;
    	//清除人品保护，因为进球了
    	this->_skill_rp_pr = 0;
    }

    int get_team_scroe(void)
    {
    	return _score;
    }

    void set_free_cornor_penalty(int free, int cornor, int penalty)
    {
        _free = free;
        _cornor = cornor;
        _penalty = penalty;
    }

    void set_team_attack_mp(int att_mp){
    	this->_team_attack_mp = att_mp;
    }

    int get_team_attack_mp(){
    	return this->_team_attack_mp;
    }

    int get_team_def_mp(){
    	return this->_team_def_mp;
    }

    void set_team_def_mp(int def_mp){
    	this->_team_def_mp = def_mp;
    }

    SoccerPlayer* get_minding_player(){
    	return _minding_player;
    }

    void set_op_team(SoccerTeam* op_team){this->_op_team = op_team;}

    void update_players(void);
    void init_formation(int position[]);
    void def_shootout_penalty(int position[]);
    void att_shootout_penalty(int position[]);
    void def_penalty_kick_off(int position[]);
    void att_penalty_kick_off(int position[]);
    void att_corner_kick_off(int position[], int flags);
    void set_cornor_kick_support_player(int flags, int i, double x, double y);
    double get_team_skill_success_rate(int skill_id,int speak_type);
    void def_corner_kick_off(int position[], int flags);
    void att_free_kick_off(int position[]);
    void kick_off_player(int pid, int position_id, int position[]);
    void def_free_kick_off(int position[]);
    Vector2D get_free_kick_off_wall_x_y(Vector2D & v, double d);
    void att_goal_kick_off(int position[]);

    //普通开局
    void def_normal_kick_off(int position[]);
    void att_normal_kick_off(int position[]);

    //防守反击开局
    void att_defend_att_kick_off();
    void def_defend_att_kick_off(int[]);

    /* 防守方普通中场开球 */
    void def_middle_kick_off(int position[]);
    static int check_position(int position);
    void prepare_for_kick_off(void);
    void update_formation(void);
    void adjust_order(void);
    void awake_frezon_player(void);
    void fix_formation_by_move_order(int move_typ, SoccerPlayer *pPlayer, bool resverse);
    void add_fake_order(void);
    void add_corner_order(int flags);
    void add_normal_order(void);
    void add_penalty_order(void);
    void add_free_order(void);
    void pick_player_by_pos(int player_typ, int *player_ids, int & player_count);
    void add_player_to_ball(SoccerPlayer* player,double distance);
    void clear_player_to_ball();

    SoccerPlayer *select_player_by_formation_pos(AttackOrder & order);
    SoccerPlayer *select_src_player_by_formation_pos(AttackOrder & order);
    void add_action(int union_pid, ActionItem::Type type)
    {
        ActionItem item;
        item.type = type;
        item.union_pid = union_pid;
        _action_list.push_back(item);
    }

    std::vector<ActionItem> & get_action_list(void)
    {
        return _action_list;
    }

    SoccerPlayer *get_by_player_id_on_pitch(int player_id)
    {
        return _players_on_pitch[player_id - 1];
    }

    SoccerPlayer* get_player_by_union_pid(int player_id){
    	std::vector<SoccerPlayer*>::iterator itr = _players_on_pitch.begin();
    	while(itr != _players_on_pitch.end()){
    		if((*itr)->get_union_pid() == player_id){
    			return *itr;
    		}
    		itr++;
    	}
    	return NULL;
    }


    std::vector<SoccerPlayer*> & get_all_player_on_pitch(void)
    {
        return _players_on_pitch;
    }

    SoccerMatch *get_match(void)
    {
        return _match;
    }

    int get_players_on_pitch_count(void)
    {
        return _players_on_pitch.size();
    }

    SoccerPlayer *get_player_on_pitch(int i)
    {
        return _players_on_pitch[i];
    }

    SoccerPlayer *get_player_by_formation_pos(int);
    int get_player_pos_by_formation_pos(int);
    SoccerPlayer* get_player_by_pos_index(int);

    void clear_move_def_define(){
    	if(_move_define != NULL){
    		delete _move_define;
    		_move_define = NULL;
    	}
    }

    void set_move_def_define(MoveDefine *move_define)
    {
        _move_define = move_define;
    }


    double calc_gk_pre(int count, ...);
    void update_gk_pos(void);
    SoccerPlayer *get_gk_player(void)
    {
        return this->_gk_player;
    }

    double get_cons_effect(int effect_typ);
    void set_cons_effect(int effect_typ, double effect_value);
    bool check_offside(int pid);
    void avoid_offside(void);
    bool can_force_offside(void);
    void set_can_force_offside(bool);
    bool can_avoid_offside(void);
    void set_can_avoid_offside(bool);
    double calc_gk_att_value();
    double calc_gk_def_value();

    double calc_team_def_value(int);
    double calc_team_att_value(int);

    void set_formation_level(int lev){
    	this->_formation_level = lev;
    }

    void set_team_level(int level){
    	this->_team_level = level;
    }

    int get_team_level(){
    	return this->_team_level;
    }

    void set_offside(int is_offside)
    {
        this->_has_offside = is_offside;
    }

    int has_offside(void)
    {
        return this->_has_offside;
    }

    SoccerPlayer *get_offside_player(void)
    {
        return this->_offside_player;
    }

    void set_offside_player(SoccerPlayer *pPlayer)
    {
        this->_offside_player = pPlayer;
    }

    void re_set(void);
    double getAtt_value(void) const
    {
        return _att_value;
    }

    double getDef_value(void) const
    {
        return _def_value;
    }

    void setAtt_value(double _att_value)
    {
        this->_att_value = _att_value;
        this->_team_attack_mp = 0;
        this->_top_attack_mp = static_cast<int>(_att_value);
    }

    void setDef_value(double _def_value)
    {
        this->_def_value = _def_value;
        this->_team_def_mp = 0;
        this->_top_def_mp = static_cast<int>(_def_value);
    }

    void update_att_mp(int mp_value){
    	this->_team_attack_mp += mp_value;
    	if(_team_attack_mp > _top_attack_mp){
    		_team_attack_mp = _top_attack_mp;
    	}
    }

    void update_def_mp(int mp_value){
    	this->_team_def_mp += mp_value;
    	if(_team_def_mp > _top_def_mp){
    		_team_def_mp = _top_def_mp;
    	}
    }

    void set_team_cid(int cid)
    {
        this->_team_club_id = cid;
    }

    void set_team_skill_success_rate(double success_rate){
    	this->_skill_success_rate = success_rate;
    }

    int get_team_cid(void)
    {
        return this->_team_club_id;
    }

    int get_auto_change_count(void)
    {
        return this->_auto_change_count;
    }

    void add_auto_change_count(void)
    {
        this->_auto_change_count++;
    }

    int get_lowest_cond_player(std::vector<int> & players){
    	std::vector<int>::iterator itr = players.begin();
    	int player_id = 0;
    	int cond = 100;
    	while(itr != players.end()){
    		SoccerPlayer* player = this->get_player_by_union_pid(*itr);
    		if(player == NULL){
    			LOG(ERROR)<<"null player "<<*itr;
    		}
    		if((player != NULL)&&(player->get_cond() < cond)){
    			player_id = player->get_union_pid();
    			cond = player->get_cond();
    		}
    		itr++;
    	}
    	return player_id;
    }

    void get_all_player_front(std::vector<int> & players)
    {
        PLAYER_ITR itr = _players_on_pitch.begin();
        int pos = 0;
        while (itr != _players_on_pitch.end())
        {
            pos = check_position((*itr)->get_formation_pos());
            if (pos == 1)
            {
                players.push_back((*itr)->get_union_pid());
            }
            itr++;
        }
    }

   SoccerPlayer* rand_pick_middle_player() {
		PLAYER_ITR itr = _players_on_pitch.begin();
		int pos = 0;
		while (itr != _players_on_pitch.end())
		{
			pos = check_position((*itr)->get_formation_pos());
			if (pos == 2)
			{
				return *itr;
			}
			itr++;
		}
		return NULL;
	}


    void get_all_player_middle(std::vector<int> & players)
    {
        PLAYER_ITR itr = _players_on_pitch.begin();
        int pos = 0;
        while (itr != _players_on_pitch.end())
        {
            pos = check_position((*itr)->get_formation_pos());
            if (pos == 2)
            {
                players.push_back((*itr)->get_union_pid());
            }
            itr++;
        }
    }

    void get_all_player_back(std::vector<int>& players)
	{
		PLAYER_ITR itr = _players_on_pitch.begin();
		int pos = 0;
		while (itr != _players_on_pitch.end())
		{
			pos = check_position((*itr)->get_formation_pos());
			if (pos == 3)
			{
				players.push_back((*itr)->get_union_pid());
			}
			itr++;	
		}				
	
	}	

    void set_current_move_card_id(int move_id){
    	this->current_move_id = move_id;
    }

    int get_current_move_card_id(){
    	return this->current_move_id;
    }

	void set_current_formation_card_id(int formation_card_id)
	{
		this->_current_formation_id = formation_card_id;
	}

	int get_current_formation_card_id(void)
	{
		return this->_current_formation_id;
	}

	void set_goal_state(void)
	{
		this->set_state(GoalingState::alloc());
	}

	void init_def_formation_before(int[]);

	void get_top_shooter(std::vector<SoccerPlayer*>&,int);

	void modifer_move_order_to_front();
	void modifer_move_order_to_back();

	void modifer_move_order_by_gk_skill();

	SoccerAttribute get_gk_attr(void)
	{
		return _gk_attr;
	}

	void set_newbie_state(int newbie_state)
	{
		this->_newbie_state = newbie_state;
	}

	int get_newbie_state(void)
	{
		return this->_newbie_state;
	}

	void set_is_round_add(int i)
	{
		_is_round_add = i;
	}

	bool is_round_add(void)
	{
		if (_is_round_add == 1)
		{
			return true;
		}

		return false;
	}

	void setTeamMode(Team_mode mode)
	{
		VLOG(3) << this->get_id() << "设置模式" << mode;
		this->_team_mode = mode;
	}

	bool isInGodMode(void)
	{
		if (this->_team_mode == GOD_MODE)
		{
			VLOG(3)<<"开启无敌模式，人当杀人，佛档杀佛2";
			return true;
		}

		return false;
	}

	bool isInLoserMode(void)
	{
		if (this->_team_mode == LOSER_MODE)
		{
			VLOG(3)<<"开启14模式，一碗热翔";
			return true;
		}

		return false;
	}

	int getBackLine(void)
	{
		return this->_back_line;
	}

	void setBackLine(int backLine)
	{
		this->_back_line = backLine;
	}

	SoccerFormation *getTeamFormation(void)
	{
		return &(this->_formation);
	}

	SoccerPlayer *choose_air_defend_player(const Vector2D &vec);

	void make_player_to_defend_air(const Vector2D& target);

	void make_player_to_defend_pass(const Vector2D& vec);

	SoccerPlayer *get_air_defend_player(void)
	{
		return this->_air_defend_player;
	}

	void set_air_defend_player(SoccerPlayer *player)
	{
		this->_air_defend_player = player;
	}

	SoccerPlayer *get_pass_defend_player(void)
		{
			return this->_pass_defend_player;
		}

	void set_pass_defend_player(SoccerPlayer *player)
	{
		this->_pass_defend_player = player;
	}

	SoccerPlayer* get_receveing_player(){
		return this->_receiving_player;
	}

	int get_move_complex(){
		return this->_move_define->get_move_complex();
	}

	SoccerPlayer* get_player_on_pitch_by_union_id(int pid){
		std::vector<SoccerPlayer*>::iterator itr =	this->_players_on_pitch.begin();
		while(itr != this->_players_on_pitch.end()){
			if((*itr)->get_union_pid() == pid){
				return *itr;
			}
			itr++;
		}
		return NULL;
	}

	void add_team_skill(int tactic_id,int chance){
		TeamSkill skill;
		skill.tactic_id = tactic_id;
		skill.chance  = chance;
		_team_skills[tactic_id] = skill;
	}

	TeamSkill* get_team_skill_info(int skill_id){
		std::map<int,TeamSkill>::iterator itr = _team_skills.find(skill_id);
		if(itr != _team_skills.end()){
			return &(itr->second);
		}
		return NULL;
	}

	bool check_team_skill(int skill_id){
		std::map<int,TeamSkill>::iterator itr = _team_skills.find(skill_id);
		if(itr != _team_skills.end()){
			return true;
		}
		return false;
	}

	TacticInfo* pick_skill_to_use_rand(){
		if(_team_skills.size() == 0){
			return NULL;
		}

		int index = RAND_INT%_team_skills.size();
		std::map<int,TeamSkill>::iterator itr = _team_skills.begin();
		TacticInfo* info = NULL;
		while(itr != _team_skills.end()){
			if(index-- == 0){
				info = CGameConfigManager::GetInstance()->GetTacticInfoById(itr->first);
				return info;
			}
			itr++;
		}
		return info;
	}


	std::vector<TacticInfo*> get_teamskill_can_use_list(){
		std::vector<TacticInfo*> skill_list_can_use;
		std::map<int,TeamSkill>::iterator itr = _team_skills.begin();
		while(itr != _team_skills.end()){
			TacticInfo* info = CGameConfigManager::GetInstance()->GetTacticInfoById(itr->first);
			if(info != NULL){
				if((info->coast_att_energy < this->_team_attack_mp) && (info->coast_def_energy < this->_team_def_mp))
				{
					skill_list_can_use.push_back(info);
				}
			}
			itr++;
		}
		return skill_list_can_use;
	}

	bool use_team_skill(TacticInfo *info);

	int use_team_skill();

	SoccerPlayer* pick_corner_ball_player();

	int	select_move_by_tactic_id(int);

	//准备防守反击
	void prepare_for_defend_and_attack();
	//
	void add_gk_kick_order();
	void pick_suitable_order(SoccerPlayer*);

	bool check_order_suitable(SoccerPlayer* ctrl_player);

	int get_order_cloest(SoccerPlayer* player);

	int get_skill_used(){
		return _tactic_used_id;
	}

	int get_last_round_skill_used(){
		return this->_last_round_tactic_used;
	}

	void reset_skill_used(){
		_last_round_tactic_used = _tactic_used_id;
		_tactic_used_id = 0;
	}

	TeamSkill get_team_skill(int tactic){
		return _team_skills[tactic];
	}
	
	void modifer_pass_point_coach_speak(Vector2D& vec);

	int team_ai_auto_use_skill();

//cocah speak effect 
public:	
	void clear_all_speak_effect(){
		for(int i=0;i< SPEAK_END;i++){
			_speak_effects[i] = false;
		}
	}

	void coach_speak_effect(int);

	int get_coach_speak_type(){
		for(int i=0;i<SPEAK_END;i++){
			if(_speak_effects[i] == true){
				return i;
			}
		}
		return -1;	
	}

	void dump_all_player_info(){
		std::ostringstream str;
		for(int i=0;i<10;i++){
			str<<":"<<_players_on_pitch[i]->get_state_type()<<"-"<<_players_on_pitch[i]->check_ball_enter_mindarea();
		}
		VLOG(1)<<str.str().c_str();
	}


	bool check_coach_speak(int speak_type){
		if(speak_type < SPEAK_WAIT_FOR){
			return false;
		}

		if(speak_type >= SPEAK_END){
			return false;
		}
		return _speak_effects[speak_type];
	}

	void set_team_despoit_state(bool d_player,bool d_use_skill){
		_deposit_change_player = d_player;
		_deposit_use_skill     = d_use_skill;
	}

	void get_team_despoit_state(bool& d_p,bool& d_u){
		d_p = _deposit_change_player;
		d_u = _deposit_use_skill;
		LOG(INFO)<<"_deposit_change_player"<<_deposit_change_player<<"  _deposit_use_skill"<<_deposit_use_skill;
	}

	int get_coach_effect_attack_defend(){
		int speak_type = get_coach_speak_type();
		int value =0;
		switch(speak_type){
			case 		SPEAK_MORE_PASS:	//保持控球，多倒脚
				value = 2;
			break;
			case 		SPEAK_MORE_CORSS:		//积极进攻，快速出球
				value = 7;
			break;
			case 		SPEAK_MORE_EMPTY_PASS:	//多往空当传球
				value = 5;
			break;
			case 		SPEAK_MORE_FOOT_PASS:	//多传脚下球
				value = 5;
			break;
			case 		SPEAK_WAIT_FOR:		//别急，耐心寻找机会
				value = 4;
			break;
			case		SPEAK_MORE_SPACE:		//站位拉开些
				value = 5;
			break;
			case 		SPEAK_LESS_SPACE:		//站位紧凑些
				value = 5;
			break;
			case 		SPEAK_ATTACK_ATTACK:	//给我压上，压迫他们
				value = 5;
			break;
			case		SPEAK_DEFEND_ATTACK:	//往回收，引蛇出洞
				value = 5;
			break;
			case		SPEAK_KILL_KICK:		//往死里踢，废他几个
				value = 4;
			break;
			case 		SPEAK_GENTLEMEN:		//出脚温柔些
				value = 6;
			break;
			default:
			{
				value = 4;
			}
			}
		return value;
	}

	bool is_team_all_attack(){
		return this->_is_all_attack;
	}

	void set_team_all_attack(bool value){
		this->_is_all_attack = value;
	}

	void add_inj_count(){
		_inj_count++;
	}

	int get_inj_count(){
		return _inj_count;
	}

	bool is_change_player_deposit(){
		return this->_deposit_change_player;
	}

	bool is_use_skill_deposit(){
		return this->_deposit_use_skill;
	}

	void set_alias_tactic_plus(double plus){
		this->_alias_tactic_plus = plus;
	}

	double get_alias_tactic_plus(){
		return _alias_tactic_plus;
	}

	void set_fitness_coach(short fitness_coach){
		this->_fitness_coach = fitness_coach;
	}

	short get_fitness_coach(){
		return this->_fitness_coach;
	}

	bool is_same_skill_last_use(int skill_id){
		if(this->_last_skill_list.empty()){
			return false;
		}

		int itr = this->_last_skill_list.back();
		if(itr == skill_id){
			return true;
		}else{
			return false;
		}
	}

	void update_team_skill_last_use(int skill_id){
		_last_skill_list.push_back(skill_id);
	}

	int get_team_skill_used_count(){
		return _last_skill_list.size();
	}

	bool check_is_last_skill_same(){
		if(_last_skill_list.size() < 2){
			return false;
		}
		std::list<int>::iterator itr = _last_skill_list.end();
		if(*itr == *(--itr)){
			return true;
		}else{
			return false;
		}
	}

	int get_last_skill_use_list(){
		if(_last_skill_list.size() < 1){
			return 0;
		}
		int skill_id = _last_skill_list.back();
		return skill_id;
	}

	double get_rp_pr(){
		return _skill_rp_pr;
	}

	void update_rp_pr(double value){
		_skill_rp_pr += value;
	}

	void reset_rp_pr(){
		_skill_rp_pr = 0.;
	}

	//查看是否要联合防守
	bool check_will_unit_defend();

	void log_team_cmp_info(int pid,int op_pid,int type,int rst){
		TeamCmpInfo info;
		info.pid = pid;
		info.op_pid = op_pid;
		info.type = type;
		info.rst = rst;
		_whole_match_cmp_log.push_back(info);
	}

	void dump_team_cmp_info(std::ostringstream &str){
		std::list<TeamCmpInfo>::const_iterator itr = _whole_match_cmp_log.begin();
		while(itr != _whole_match_cmp_log.end()){
			LOG(INFO)<<itr->pid<<"  "<<itr->op_pid<<"  "<<itr->type<<"  "<<itr->rst;
			str<<itr->pid;
			str<<":";
			str<<itr->op_pid;
			str<<":";
			str<<itr->type;
			str<<":"<<itr->rst;
			itr++;
			if(itr != _whole_match_cmp_log.end()){
				str<<"#";
			}
		}
	}

	void add_use_skill_goal(){
		_use_skill_goal++;
	}

	int get_skill_used_goal(){
		return _use_skill_goal;
	}

//speak effect
private:
	bool _speak_effects[SPEAK_END];
    //托管使用换人
    bool	_deposit_change_player;
    //托管使用技能
    bool	_deposit_use_skill;
    //当前受伤的人数
    int		_inj_count;
    //是否該比賽全部進攻
    bool	_is_all_attack;

    double  _alias_tactic_plus;

    short 	_fitness_coach;

    /* 当前进球数量 */
    int _score;

    //上次使用的技能
    std::list<int> _last_skill_list;

    double _skill_rp_pr;

    std::list<TeamCmpInfo>	_whole_match_cmp_log;    

    int	_use_skill_goal;

private:
    void next_order(void);

public:
    Vector2D		_gk_pos;
    SoccerAttribute _gk_attr;
    int				_gk_pid;
    double			_gk_att_value;
    double 			_gk_def_value;
};

#endif /* _SOCCER_TEAM_H_ */
