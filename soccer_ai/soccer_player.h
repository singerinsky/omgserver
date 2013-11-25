#ifndef _SOCCER_PLAYER_H_
#define _SOCCER_PLAYER_H_

#include "game_entity.h"
#include "movable_entity.h"
#include "soccer_config.h"
#include "soccer_region.h"
#include "game_config.h"
#include "match_text.h"
#include <map>
#include "triangle.h"
#include "enum.h"
#include "../common/cmmmo_define.h"
//#include "soccer_pitch.h"

class SoccerTeam;
class SoccerMatch;

typedef enum
{
    PS_RUN = 1,
    PS_DRIBBLE,
    PS_SHOOT,
    PS_PASS,
    PS_CROSS_PASS,
    PS_STOP = 7,
    PS_TURN,
    PS_DRIBBLE_TURN
} PlayerMoveStatus;

typedef enum
{
	ATT_GK_SAVE	= 1,//扑救
	ATT_GK_COM_DEF,	//指挥防守
	ATT_PHY,		//身体
	ATT_CREAT,		//灵感
	ATT_SHOOT,		//射门
	ATT_PASS,		//传球
	ATT_BALL_CTRL,	//控球
	ATT_DEFEND,		//防守
	SPEED,			//速度
	BOUNCE,			//弹跳
	STRONG,			//强壮
	AGGRESSIVE,		//侵略性
	MOVES,			//跑位
	VISION,			//视野
	FREE_KICK,		//任意球精度
	HEADER_ACCURACY,//头球精度
	LONG_RANGE,		//远射
	PENALTY,		//点球
	KICKOFF	= 19,		//开球

	// 卡牌操作(buff) 35
	ATTR_GOAL_PROBABILIRY	= 35, // 进球概率
	ATTR_STATE 				= 36, // 球员状态

	ATTR_ROUND_ADD 			= 37, // 加round
	ATTR_CA 				= 38,
	BUFF_CUER 				= 39,
	REFEREE_BIAS 			= 40,// 裁判偏向性
	GLOBAL_ATTR_PLUS 		= 41,// 全局加成属性 --
	ADD_OFFSIDE_CANCEL 		= 42,// 给越位
	RE_OFFSIDE_CANCEL 		= 43,// 取消越位
	ADD_THE_PENALTY 		= 44,// 给点球
	RE_THE_PENALTY 			= 45,// 取消点球
	ADD_YELLOW_CARD 		= 46,// 给黄牌
	RE_YELLOW_CARD 			= 47,// 取消黄牌
	ADD_RED_CARD 			= 48,// 给红牌
	RE_RED_CARD 			= 49,// 取消黄牌
	GLOBAL_SPEED_ADD 		= 50,// 全局加速度属性
	GLOBAL_PHY_ADD 			= 51,// 全局加身体属性
	GLOBAL_DEF_ADD 			= 52,// 全局加防守属性
	GLOBAL_MENTAL_ADD 		= 53,// 全局加精神属性
	GLOBAL_TEC_ADD 			= 54,// 全局加技术属性
	GLOBAL_GK_ADD 			= 55,// 守门员加属性
	REFEREE_BIAS_PHP 		= 56,// 裁判偏向性-php
	SPECIAL_POINT			= 57,
    ATTR_END
} PlayerAttribueIndex;

//计算通用公式,WORK_RATE_VALUE
#define WORK_RATE_VALUE(x) (1 + (x->get_attr(MENTAL_WORK) - 50) * 0.005) + RAND_DBL

//#define NEW_WORK_RATE_VALUE(x) (1 + (x - 50) * 0.005)

////设置比赛结束
//player 触发球员，at 数据统计,end_typ 结束类型 sub_typ 结束子类型, next_start 下一轮类型， card 是否黄牌，是否受伤
#define MATCH_BREAK_NEW(from_player, to_player, at, end_typ, sub_typ, next_start, card) \
						if(this->get_team()->is_att_side()){\
							_match->get_attack_team()->add_action(from_player->_union_pid, at);}\
						else{\
							_match->get_defend_team()->add_action(from_player->_union_pid, at);\
						}	\
						_match->set_round_end(from_player->_union_pid, to_player->_union_pid, from_player->get_uid());\
						_match->set_status(end_typ);\
						_match->set_match_end_status((int)at, end_typ, sub_typ, next_start, card);\
						if (end_typ == END_BREAK)\
						{\
							if (from_player->get_pos().x >= B_FORBIDDEN_AREA_X\
								&& (from_player->get_pos().y >= B_FORBIDDEN_AREA_Y\
								&& from_player->get_pos().y <=  B_FORBIDDEN_AREA_Y + FORBIDDEN_AREA_HEIGHT))\
							{\
								_match->set_match_event_card_typ(ADD_THE_PENALTY);\
							}\
						}\
						VLOG(3)<<">>>>>>>>>>player "<<from_player->_union_pid << "," << to_player->_union_pid << "," << end_typ;

//取随机数
#define GET_RAND(x) srand(time(NULL));\
					rand() % x;
//获取本球队的进攻的move的complex
#define GET_MOVE_COMPLEX this->get_team()->get_move_complex()

extern std::map<int, std::string> g_player_attr_field_map;
extern std::map<int, std::string> g_player_attr_field_gk_map;
extern GameConfig g_game_config;

void init_player_attr_field_map(void);
void init_player_attr_field_gk_map(void);

typedef enum
{
    RECEIVE_USE_NONE,
    RECEIVE_USE_HEAD,
    RECEIVE_USE_FOOT
} ReceiveAction;

enum
{
	Minor_injured = 1,
	Midium_injured,
	Seriously_injured
};

class SoccerAttribute
{
    double _attrs[ATTR_END];
    double _attrs_bak[ATTR_END];

public:
    SoccerAttribute(void)
    {
        for (int i = 0; i < ATTR_END; ++i)
        {
            _attrs[i] = 0;
            _attrs_bak[i] = 0;
        }
    }

    double & operator[](int attr)
    {
    	LOG_IF(ERROR,attr>ATTR_END)<<"ERROR FO ATTRIBUTE";
        assert(attr < ATTR_END);
        return _attrs[attr];
    }

    double attr_bak(int attr){
    	LOG_IF(ERROR,attr>ATTR_END)<<"ERROR FO ATTRIBUTE";
    	assert(attr < ATTR_END);
        return _attrs_bak[attr];
    }

    void set_attr_bak(int attr,double v){
    	LOG_IF(ERROR,attr>ATTR_END)<<"ERROR FO ATTRIBUTE";
    	assert(attr < ATTR_END);
    	_attrs_bak[attr] = v;
    }

    void clear(){
        for (int i = 0; i < ATTR_END; ++i)
        {
            _attrs[i] = 0;
            _attrs_bak[i] = 0;
        }
    }
};

struct PlayerSkill{
	unsigned short skill_id;
	unsigned short skill_level;
	unsigned short skill_chance;
};


class SoccerPlayerSkill {
public:
	SoccerPlayerSkill(){
		_skill_count = 0;
	}

	PlayerSkill*	get_skill(unsigned short skill_typ){
		for(int i=0;i<_skill_count;i++){
			if(_skill[i].skill_id == skill_typ){
				return &_skill[i];
			}
		}
		return NULL;
	}

	PlayerSkill & operator[](int index)
    {
        return _skill[index];
    }

	int	get_skill_count()
	{
		return this->_skill_count;
	}

	void add_skill(int skill_id,int skill_level,int skill_chance){
		if(_skill_count > 6){
			return;
		}
		_skill[_skill_count].skill_id = skill_id;
		_skill[_skill_count].skill_level = skill_level;
		_skill[_skill_count].skill_chance = skill_chance;
		_skill_count++;
	}

	void dump_skill_info(){
		for(int i=0;i<_skill_count;i++){
			LOG(INFO)<<_skill[i].skill_id<<":"<<_skill[i].skill_chance;
		}
	}

private:
	PlayerSkill	_skill[10];
	int			_skill_count;

};

class SoccerPlayer : public MovableEntity, public GameEntityBase<SoccerPlayer>
{
    friend std::ostream & operator << (std::ostream &os, const SoccerPlayer &p);
    friend class PlayerKeyframe;
    friend class MatchRecorder;

    int _player_id;
    int _pos_index;
    char	_player_name[20];

    ReceiveAction _last_receive_action;
    ReceiveAction _receive_decision;
    PlayerMoveStatus _move_status;

    double _distance_to_ball;
    double _distance_to_offline;
    double _distance_to_goal;

    SoccerRegion _home;
    SoccerRegion _mindArea;
    SoccerRegion _markArea;

    int _formation_pos;
    /* 位置备份 */
    int _formation_pos_bak;

    int _mind_player_id;

    SoccerPlayer *_pMindPlayer;
    SoccerPlayer *_pMarkPlayer;
    SoccerPlayer *_pBeMindedPlayer;
    SoccerTeam *_team;
    SoccerTeam *_op_team;
    SoccerMatch *_match;
    int _uid;
    Vector2D _move_target;
    double _middle_modifer;

    //本身属性
    SoccerAttribute _attr;
    double _att_value;
    double _def_value;

    //skill plus attribute
    SoccerAttribute _skill_attr_plus;

    //
    double _per_time_scale_cond_dis;

    //球员的技能
    SoccerPlayerSkill	_skills;

    //比赛属性
    int _suitable;//在阵容中的适合位置属性
    int _red_card;
    int _yellow_card;
    int _inj;
    int _footedness;
    int _penalty_count;
    int _foul_count;
    int _foul_probability;
    double _player_score;
    int _behavior;
    double _tacklewill;
    double _blockwill;

    int _pass_run_to_count; // 传球前带球跑的时间片(短传)
    int _cross_run_to_count; // 传球前带球跑的时间片(长传)

    //玩家的朝向的三角形区域
    Triangle triangle;

    int _keep_distance_stage; // mind ball 上抢的阶段 1 快速 2 慢速 3 action 0 null

    //是否准备好接球
    bool _is_ready_for_recv;
    double  _cond;
    int  _show_time_scale;

public:


    int _union_pid;
    bool is_offside;
    int _column_index;
    int _row_index;
    Vector2D _init_pos;

    SoccerPlayer(int player_id, uint32_t id, SoccerTeam *team);
    virtual ~SoccerPlayer();

    void set_player_name(const char* player_name){
    	strncpy(_player_name,player_name,19);
    }

    const char* get_player_name(){
    	return this->_player_name;
    }

    void reset_keep_distance_stage(void)
    {
    	_keep_distance_stage = 0;
    }

    //进攻方或者防守方 1:进攻方，2：防守方
    int	attack_or_defend();

    double get_cond(){
    	return _cond;
    }

    void set_cond(double cond){
    	_cond = cond;
    }

    double get_per_time_scale_cond_dis(){
    	return this->_per_time_scale_cond_dis;
    }
///正常情况下是不可能低于10,如果已经低于10的话，就已经是受伤了。
    void down_player_cond(int time_scale){
    	if(this->_cond >= 10){
    		this->_cond = this->_cond - ((double)time_scale * this->_per_time_scale_cond_dis)*100;
    		if(this->_cond < 10){
    			this->_cond = 10;
    		}
    	}

    	for(int i=1 ; i<ATTR_END;i++){
    		this->_attr[i] = this->_attr.attr_bak(i) * (this->_cond / 100);
    	}
    }

    void set_per_time_scale_cond_dis(double value){
    	this->_per_time_scale_cond_dis = value;
    }

    int add_show_scale(int time_scale){
    	this->_show_time_scale += time_scale;
    	return this->_show_time_scale;
    }

    int get_show_scale(){
    	return this->_show_time_scale;
    }

    int get_behavior(void)
    {
        return _behavior;
    }

    void set_behavior(int b)
    {
        _behavior = b;
    }

    void set_foul_probability(int i)
    {
        _foul_probability = i;
    }

    double modifer_score(double score)
    {
    	if((this->_player_score + score) >= 10.){
    		this->_player_score = 10.;
    		return 10.;
    	}
    	this->_player_score = this->_player_score + score;
        return _player_score;
    }

    double get_player_score(void)
    {
        return this->_player_score;
    }

    int get_foul_probability(void)
    {
        return _foul_probability;
    }

    SoccerPlayerSkill* get_skills(){
    	return &_skills;
    }



    void set_foul_count(void)
    {
        _foul_count++;
    }

    int get_foul_count(void)
    {
        return _foul_count;
    }

    void set_penalty_count(int i)
    {
        _penalty_count = i;
    }

    int get_penalty_count(void)
    {
        return _penalty_count;
    }

    SoccerMatch *get_match(void)
    {
        return _match;
    }

    void set_footedness(int i)
    {
        _footedness = i;
    }

    int get_footedness(void)
    {
        return _footedness;
    }

    double get_distance_to_ball(void)
    {
        return _distance_to_ball;
    }

    void set_middle_modifer(double);
    double get_middle_modifer(void);

    //0:没有受伤 1:轻伤 2：中伤3：重伤
    int is_soccer_player_injs(void)
    {
    	if(this->get_cond() == 9){
    		return 1;
    	}else if(this->get_cond() == 8){
    		return 2;
    	}else if(this->get_cond() == 7){
    		return 3;
    	}

    	return 0;
    }

    void set_red_card(int i)
    {
        _red_card = i;
    }

    void set_red_card(void)
    {
        _red_card++;
    }

    int get_red_card(void)
    {
        return _red_card;
    }

    void set_yellow_card(void)
    {
        _yellow_card++;
        if (_yellow_card >= 2)
        {
            set_red_card();
            _yellow_card = 0;
        }
    }

    void set_yellow_card(int i)
    {
        _yellow_card = i;
    }

    int get_yellow_card(void)
    {
        return _yellow_card;
    }

    void set_inj(int inj)
    {
        _inj = inj;
    }

    int get_inj(void)
    {
        return _inj;
    }

    void set_union_pid(int u_pid)
    {
        _union_pid = u_pid;
    }

    bool is_gk();

    int get_union_pid(void)
    {
        return _union_pid;
    }

    void set_uid(int u)
    {
        _uid = u;
    }

    int get_uid(void)
    {
        return _uid;
    }

    int get_player_id(void)
    {
        return _player_id;
    }

    void set_pos_index(int pos_index){
    	this->_pos_index = pos_index;
    }

    int get_pos_index(){
    	return this->_pos_index;
    }

    void run_to(const Vector2D & target, double speed_per = 1.);
    void dribble_to(const Vector2D & target);
    void step_back(void);
    void run_forward(void);
    void set_home(const SoccerRegion & region);
    SoccerRegion get_home(void) const;
    void modifer_home(double x,double y);
    bool is_team(SoccerTeam *team);
    void set_mindArea(const SoccerRegion & region);
    void set_markArea(const SoccerRegion & region);
    void set_mindPlayer(int mindPlayer_id);
    void set_mindBall(int mindplayer_id);
    void set_markball(void);
    void init_pos(void);
    SoccerPlayer* get_minding_player();
    bool ball_in_home(void);
    double update_distance_to_ball(void);
    double update_distance_to_goal(void);
    double update_distance_to_offline(void);
    void player_break_ok(SoccerPlayer*, SoccerPlayer*, int sub_typ, int next_typ = 100);
    bool check_event_card_to_flash(SoccerPlayer *pPlayer, int flag);
    bool check_yellow_card(void);
    bool check_will_be_free_ball(SoccerPlayer*);
    void defend_home(void);
    void support_to(const Vector2D & pt,bool is_ready_time_out = false);
    void pass_to_supporter(const RegionSet & target_regions,bool is_quick_pass);
    void cross_to_supporter(const RegionSet & target_regions);
    void force_cross_to_supporter(const RegionSet & target_regions);
    void set_ball_goal_vector(int tmp);
    void penalty_ball(void);
    bool is_approach(void);
    void force_run_to_ball(void);
    bool is_ending(int nu);
    void free_ball(void);
    void cornor_ball(void);
    void decide_receive_type(void);
    void receive_ball(void);
    void back_defend(void);
    bool ground_slide(void);
    void shoot_goal(void);
    double get_shoot_with_team_skill_plus();
    double check_skill_speak_effect(int skill_id,int speak_typ);
    void force_shoot_goal(void);
    void fat_shoot_goal();
    void go_home(void);
    void def_go_home(void);
    void marking(void);
    void unmarking(void);
    void minding(void);
    void unminding(void);
    void follow_ball(double speed_per = 1.0);
    void follow_player(SoccerPlayer *pPlayer);
    bool ground_tackle(void);
    void defend_ground(void);
    SoccerRegion get_mind_area(void);
    SoccerPlayer *check_attack_player_enter_mindarea(void);
    SoccerPlayer *check_attack_player_enter_mindarea2(void);
    SoccerPlayer *can_mind_other_but(SoccerPlayer*);
    bool check_ball_enter_mindarea(void);
    bool is_at_pos(const Vector2D & target);
    bool in_corner_kick(SoccerPlayer *pPlayer, RoundEndSubTyp typ);
    int		get_state_type(){
    	return this->get_state()->get_type();
    }
    void set_attr(int attr, double v)
    {
        _attr[attr] = v;
    }

    double get_attr(int attr)
    {
        return _attr[attr];
    }

    void set_attr_bak(int attr,double v){
    	_attr.set_attr_bak(attr,v);
    }

    SoccerAttribute& get_skill_plus_attr(void){
    	return this->_skill_attr_plus;
    }

    SoccerAttribute& get_attr(void)
    {
        return _attr;
    }

    void set_formation_pos(int pFromation_pos)
    {
        this->_formation_pos_bak = this->_formation_pos;
        this->_formation_pos = pFromation_pos;
    }

    int get_formation_pos_bak(){
    	return this->_formation_pos_bak;
    }

    int get_formation_pos(void)
    {
        return this->_formation_pos;
    }

    SoccerPlayer *get_BeMindedPlayer(void)
    {
        return this->_pBeMindedPlayer;
    }

    void set_BeMindedPlayer(SoccerPlayer *pPlayer)
    {
        this->_pBeMindedPlayer = pPlayer;
    }

    void set_Suitable(int suitable)
    {
    	this->_suitable = suitable;
    }

    int get_Suitable(void)
    {
    	return this->_suitable;
    }

    void parepre_kick_off(void);
    void area_defend(void);
    void be_blocked(void);

    bool in_AirDefendState(void);
	
    SoccerTeam* get_op_team();

    SoccerTeam *get_team(void)
    {
        return this->_team;
    }

    Vector2D get_move_target(void)
    {
        return this->_move_target;
    }

    SoccerPlayer *get_player_by_formation_pos(int);
    void off_side(void);
    bool avoid_offside(void);
    double calc_score(int count, ...);
    double calc_attr_pre(int count, ...);
    void shoot_but_gk_keep(int);
    void shoot_but_miss(void);
    void halftime_resume_cond();

    double getAtt_value(void) const
    {
        return _att_value;
    }

    SoccerAttribute getAttr(void) const
    {
        return _attr;
    }

    double getDef_value(void) const
    {
        return _def_value;
    }

    void setAtt_value(double _att_value)
    {
        this->_att_value = _att_value;
    }

    void setAttr(SoccerAttribute _attr)
    {
        this->_attr = _attr;
    }

    void setDef_value(double _def_value)
    {
        this->_def_value = _def_value;
    }

    double calc_player_att_value();
    double calc_player_def_value();

    //检测是否有对方球员在他的前方三角形区域
    SoccerPlayer* check_player_in_front();

    //检测他前方三角区域内的防守球员的数量
    int get_player_counts_in_front();

    //检测是否有对方球员在他的射门路线
    SoccerPlayer* check_player_in_attack_way();
    //更新前方三角形区域
    void update_triangle_area();
    bool gk_kick_off();
    Vector2D change_dir_tmp(SoccerPlayer*);
    bool natrue_trackle_ball();
    //计算实际要传的落球点
    Vector2D calc_pass_real_point(const Vector2D& target_point);

    //是否准备好接球
    bool is_ready_for_recv(){
    	return this->_is_ready_for_recv;
    }

    void air_defend(Vector2D& vec);
    void pass_defend(Vector2D& vec);
    int check_skill_can_use(int);
    void use_skill(int);

    //直接计算点球
    bool do_pently_cmp(int,MatchPentlyEvent&);
    void dump_player_skill_info();
    int check_will_use_gk_skill();

    bool is_trigger_rp_pr();
    void reset_team_rp_pr();
    double get_team_rp_pr();
    void update_team_rp_pr(double);
    bool is_own_ball(void);

    int _tmp_dirbble_cd;
    int _change_count;
    Vector2D _tmp_dirblle_target_vec;

private:
    double head_receive_a_score(void);
    double head_receive_d_score(void);
    double foot_receive_a_score(void);
    double foot_receive_d_score(void);

    bool is_ball_in_action_radius(void);

    void keep_distance(int mindplayer_id);

    void keep_line(void)
	{
		def_go_home();
	}

    bool is_player_in_mind_area(const SoccerPlayer& );
    bool has_mind_ball_will(void);
    bool has_mind_player_will(void);
    SoccerPlayer *get_receiving_player(void);
    SoccerPlayer *get_mind_player(void);
    bool has_block_player_will(void);
    int compitition_result(double a, double d, double random_modify);
    void run_forward(const Vector2D & target, double speed_per = 1.);
    bool is_turn_need_punish(const Vector2D & target);
    bool has_beat_will(const Vector2D & target);
    void pass(const RegionSet & target_regions, SoccerPlayer *target,bool is_quick_pass=false);
    void cross(const RegionSet & target_regions, SoccerPlayer *target);
    void force_cross(const RegionSet & target_regions, SoccerPlayer *target);
    void defend_air(void);
    bool to_people_or_ball(void);
    bool cross_pass_combat(void);
    bool has_tackle_will(void);
    bool has_slide_will(void);
    bool has_mark_player_will(void);
    bool has_head_shoot_goal_will(double distance_to_goal);
    bool has_shoot_goal_will(double distance_to_goal);
    void shoot_goal_action(int);
    void adjust(void);
    bool has_head_receive_will(void);
    bool has_mark_ball_will(void);
    bool pass_ball(SoccerPlayer *target);
    void cross_ball(SoccerPlayer *target, double distance_to_support,bool is_forcss=false);
    SoccerRegion get_mark_area(void);
    bool check_ball_enter_markarea(void);
    bool is_in_home_pos(void);
    bool can_defend_attack_back();
    SoccerPlayer *get_markplayer(void);
    bool block_or_tackle(void)
    {
    	return true;
    }

    //检测是否受伤
    bool check_injuried(SoccerPlayer*);

    void set_last_skill_used(unsigned short skill_id){
    	_last_skill_used = skill_id;
    }

    unsigned short get_last_skill_used(){
    	return _last_skill_used;
    }

    //****************技能*****************************//
private:
    unsigned short _last_skill_used;
};

inline std::ostream & operator << (std::ostream &os, const SoccerPlayer &p)
{
    const State<SoccerPlayer> *state = p.get_state();
    const char *state_name;
    if (state)
    {
        state_name = state->get_name();
    }
    else
    {
        state_name = "None";
    }
    os << p._player_id << ",state:" << state_name << ",pos:" << p.get_pos();

    return os;
}

#endif /* _SOCCER_PLAYER_H_ */
