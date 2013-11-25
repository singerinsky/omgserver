#include "../common/head.h"

#include "../common/rand_generator.h"
#include "../common/cmmmo_define.h"
#include "pass_refer_table.h"
#include "soccer_match.h"
#include "soccer_player.h"
#include "soccer_player_state.h"
#include "soccer_team.h"
#include "speed_refer_table.h"
#include "player_score.h"
#include "soccer_player_skill.h"

std::map<int, std::string> g_player_attr_field_map; // 球员属性
std::map<int, std::string> g_player_attr_field_gk_map; // 门将属性

void init_player_attr_field_map(void) {
	g_player_attr_field_map[ATT_GK_SAVE] = "att_gk_save";
	g_player_attr_field_map[ATT_GK_COM_DEF] = "att_gk_com_def";
	g_player_attr_field_map[ATT_PHY] = "att_phy";
	g_player_attr_field_map[ATT_CREAT] = "att_creat";
	g_player_attr_field_map[ATT_SHOOT] = "att_shoot";
	g_player_attr_field_map[ATT_PASS] = "att_pass";
	g_player_attr_field_map[ATT_BALL_CTRL] = "att_ball_ctrl";
	g_player_attr_field_map[ATT_DEFEND] = "att_defend";

	g_player_attr_field_map[SPEED] = "speed";
	g_player_attr_field_map[BOUNCE] = "bounce";
	g_player_attr_field_map[STRONG] = "strong";
	g_player_attr_field_map[AGGRESSIVE] = "aggressive";

	g_player_attr_field_map[MOVES] = "moves";
	g_player_attr_field_map[VISION] = "vision";

	g_player_attr_field_map[FREE_KICK] = "free_kick";
	g_player_attr_field_map[HEADER_ACCURACY] = "header_accuracy";
	g_player_attr_field_map[LONG_RANGE] = "long_range";
	g_player_attr_field_map[PENALTY] = "penalty";
	g_player_attr_field_map[KICKOFF] = "kickoff";
}

SoccerPlayer::SoccerPlayer(int player_id, uint32_t id, SoccerTeam *team) :
	GameEntityBase<SoccerPlayer> (id) {
	_team = team;
	_match = team->get_match();
	_move_status = PS_STOP;
	_player_id = player_id;
	_last_receive_action = RECEIVE_USE_NONE;
	_distance_to_ball = 0;
	_mind_player_id = 0;
	_pBeMindedPlayer = NULL;
	_union_pid = 0; // 球员PID
	_uid = team->get_team_cid(); // team ID
	_middle_modifer = 0.;
	_red_card = 0; // 红牌 > 0
	_yellow_card = 0; // 黄牌 > 2
	_inj = 0; // 受伤 > 0
	_footedness = 2;
	_penalty_count = 0;
	_foul_count = 0;
	_foul_probability = 0;
	_player_score = 6; //初始化分数
	_behavior = 0;
	_pass_run_to_count = 0;
	_cross_run_to_count = 0;
	_keep_distance_stage = 0;
	_tmp_dirbble_cd = 0;
	_show_time_scale = 0;//上场时间片
	_per_time_scale_cond_dis = 0.;
	_last_skill_used = 0;
}

SoccerPlayer::~SoccerPlayer() {

}
//断球成功
void SoccerPlayer::player_break_ok(SoccerPlayer *src_player,
		SoccerPlayer *rst_player, int sub_typ, int next_typ) {
	/*if((src_player->get_team()->isInGodMode() == true) || rst_player->get_team()->isInGodMode() == true){
	 exit(1);
	 }*/

	//VLOG(0)<<"Break.................";
	//判断是否要防守反击
	if (can_defend_attack_back()) {
		rst_player->modifer_score(0.2);
		MATCH_BREAK_NEW(src_player, rst_player, ActionItem::BEBREAK, END_BREAK, sub_typ, N_STRIKE_BACK, C_NULL);//断球成功
	} else {
		rst_player->modifer_score(0.2);
		MATCH_BREAK_NEW(src_player, rst_player, ActionItem::BEBREAK, END_BREAK, sub_typ, next_typ, C_NULL);//断球成功
	}
}

// 犯规概率的处罚 点球,flag:0=>带球过人，dribbe_to, 1=>断球，2=>传球, 3=>mark player
bool SoccerPlayer::check_event_card_to_flash(SoccerPlayer *pPlayer, int flag) {

	int tmp = RAND_INT % 100;
	if (true || tmp < 20) // 判断犯规
	{
		// 点球
		/*
		 if (pPlayer->get_pos().x >= B_FORBIDDEN_AREA_X && (pPlayer->get_pos().y
		 >= B_FORBIDDEN_AREA_Y && pPlayer->get_pos().y
		 <= B_FORBIDDEN_AREA_Y + FORBIDDEN_AREA_HEIGHT)) {
		 if (_match->_count_penalty >= 1) {
		 return false;
		 }
		 _match->_count_penalty++;
		 //禁区内可能发生的犯规行为
		 uint sum_typ = 0;
		 sum_typ
		 = RAND_ARRAY(2, IN_RESTRICTED_HAND_BALL, IN_RESTRICTED_FOUL_SLIDE);
		 MATCH_BREAK_NEW(pPlayer, this, type, END_FOULED, sum_typ, N_PENALTY_KICK, C_NULL);
		 _match->set_match_event_card_typ(RE_THE_PENALTY);
		 _match->set_event_frames(pPlayer->get_team()->get_team_cid(),
		 pPlayer->get_union_pid(), 0, 34);
		 //创造点球，加分,被创造点球扣分
		 this->modifer_score(0.7);
		 pPlayer->modifer_score(-0.7);
		 } else // 不在给点球的范围,也不在给任意球范围之内 任意球*/
		/*		{
		 uint t2 = 0; // 黄牌
		 uint t1 = 0; //结束类型
		 bool will_be_free = pPlayer->check_will_be_free_ball(this);
		 if (will_be_free) {
		 t1 = N_FREE_KICK;
		 if (pPlayer->check_yellow_card()) {
		 t2 = C_YELLOW_CARD;
		 }
		 } else {
		 t1 = N_NORMAL_KICK;
		 }

		 MATCH_BREAK_NEW(pPlayer, this, type, END_FOULED, sum_typ, t1, t2);
		 //创造对方的犯规加分,被创造扣分
		 this->modifer_score(0.2);
		 pPlayer->modifer_score(-0.2);
		 }*/

		return true;
	}

	return false;
}

bool SoccerPlayer::check_will_be_free_ball(SoccerPlayer* att_player) {
	if (_match->_count_free >= 2) {
		return false;
	}
	int att_pos_x = att_player->get_pos().x;
//	int att_pos_y = att_player->get_pos().y;

	if ((att_pos_x < B_FORBIDDEN_AREA_X) && (att_pos_x > (PITCH_WIDTH/2))) {
		_match->set_player_pos(att_player->get_pos().x, att_player->get_pos().y);
		_match->set_event_frames(att_player->get_uid(),
				att_player->get_union_pid(), 0, 33);
		_match->_count_free++;
		return true;
	}
	return false;
}

bool SoccerPlayer::check_yellow_card(void) // 黄牌 > 2
{
	if (this->get_yellow_card() >= 1) {
		return false;
	}

	int rand_int = RAND_INT % 100;
	if (rand_int < 30) {
		set_yellow_card();
	}

	_match->set_match_event_card_typ(ADD_YELLOW_CARD); // 给黄牌
	return false;
}

double SoccerPlayer::update_distance_to_ball(void) {
	_distance_to_ball = get_pos().distance(
			_team->get_match()->get_ball()->get_pos());
	return _distance_to_ball;
}

double SoccerPlayer::update_distance_to_goal(void) {
	Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);
	_distance_to_goal = get_pos().distance(goal_vector);
	return _distance_to_goal;
}

double SoccerPlayer::update_distance_to_offline(void) {
	return PITCH_WIDTH - OUTSIDE_WIDTH - this->get_pos().x;
}

bool SoccerPlayer::is_at_pos(const Vector2D &target) {
	if (get_pos() == target) {
		return true;
	}

	return false;
}

bool SoccerPlayer::is_turn_need_punish(const Vector2D &target) {
	return false;

	Vector2D to_direction = target - get_pos();
	to_direction.normalize();
	if (to_direction.dot(get_heading()) <= 0.94) {
		return true;
	}

	return false;
}

bool SoccerPlayer::is_own_ball(void) {
	if (_match->get_ball()->get_owner() == this) {
		return true;
	}

	return false;
}

void SoccerPlayer::step_back(void) {
	Vector2D tmpVec = this->get_pos();
	tmpVec.x += 100;
	_move_status = PS_RUN;
	run_to(tmpVec, 0.3);
}

void SoccerPlayer::run_forward(void) {
	set_pos(get_pos() + get_heading() * get_speed());
}

void SoccerPlayer::run_forward(const Vector2D &target, double speed_per) {
	double speed = get_speed();
	double top_speed = speed_refer_table_get((int) _attr[SPEED]) * speed_per;
	if (speed < top_speed) {
		speed += acceleration_refer_table_get((int) _attr[SPEED]) * speed_per;
	}

	if (speed > top_speed) {
		speed = top_speed;
	}

	if (get_pos().distance(target) <= speed) {
		set_pos(target);
	} else {
		set_pos(get_pos() + get_heading() * speed);
		set_speed(speed);
	}
}

void SoccerPlayer::run_to(const Vector2D &param_target, double speed_per) {
	Vector2D target = param_target;
	if (target.x > PITCH_WIDTH) {
		target.x = PITCH_WIDTH - METER_TO_POINT;
	}

	if (target.x < 0) {
		target.x = METER_TO_POINT;
	}

	if (target.y > PITCH_HEIGHT) {
		target.y = PITCH_HEIGHT - METER_TO_POINT;
	}

	if (target.y < 0) {
		target.y = METER_TO_POINT;
	}

	if (is_at_pos(target)) {
		if (is_own_ball()) {

		} else {
			_move_status = PS_STOP;
		}
		return;
	}

	if (is_turn_need_punish(target)) {
		heading_to(target);
		if (is_own_ball()) {
			_move_status = PS_DRIBBLE_TURN;
		} else {
			_move_status = PS_TURN;
		}
		//        return;
	}

	if (is_own_ball()) {
		_move_status = PS_DRIBBLE;
	} else /* 防止无球队员的越位 */
	{
		if (false && this->get_team()->is_att_side()) {
			SoccerPlayer *player = this->_match->get_closest_to_ball_def();
			if (this->get_pos().x > (player->get_pos().x + RAND_INT % (2
					* METER_TO_POINT))) {
				Vector2D tmp = target;
				tmp.x = target.x - 4 * METER_TO_POINT;
				heading_to(tmp);
				run_forward(tmp, speed_per);
				_move_status = PS_RUN;
				return;
			}
		}
		_move_status = PS_RUN;
	}

	heading_to(target);
	this->_move_target = target;
	run_forward(target, speed_per);
}

double SoccerPlayer::calc_score(int count, ...) {
	va_list ap; // 初始化指向可变参数列表的指针
	double score = 0;
	va_start(ap, count); // 将第一个可变参数的地址付给ap，即ap指向可变参数列表的开始
	for (int i = 0; i < count; ++i) {
		int attr = va_arg(ap, int);
		int modify = va_arg(ap, int);
		score += (_attr[attr] / modify);
	}
	va_end(ap); // ap付值为0，没什么实际用处，主要是为程序健壮性
	score *= this->get_cond();
	score = score / 100;

	//_attr[ATTR_STATE] -= 0.02;

	return score;
}

double SoccerPlayer::calc_attr_pre(int count, ...) {
	va_list ap; // 初始化指向可变参数列表的指针
	double score = 0;
	va_start(ap, count); // 将第一个可变参数的地址付给ap，即ap指向可变参数列表的开始
	for (int i = 0; i < count; ++i) {
		int attr = va_arg(ap, int);
		int modify = va_arg(ap, int);
		score += (_attr[attr] / modify);
	}
	va_end(ap); // ap付值为0，没什么实际用处，主要是为程序健壮性

	return score;
}

// if attack(first) win return 1 else return -1
int SoccerPlayer::compitition_result(double a, double d, double random_modify) {
	if ((a + RAND_DBL * random_modify) >= (d + RAND_DBL * random_modify)) {
		return 1;
	}

	return -1;
}

SoccerPlayer *SoccerPlayer::get_mind_player(void) {
	return _match->get_defend_team()->_minding_player;
}

void SoccerPlayer::set_middle_modifer(double y) {
	this->_middle_modifer = y;
}

double SoccerPlayer::get_middle_modifer(void) {
	return this->_middle_modifer;
}

//run with ball ,带球
//TODO
void SoccerPlayer::dribble_to(const Vector2D &target) {
	Vector2D vec_target = target;

	if (!(this->get_team()->isInGodMode())) {
		if (has_beat_will(vec_target)) {
			SoccerPlayer *minding_player = this->get_mind_player(); // 盯他的人
			if (minding_player != NULL
					&& minding_player->is_ball_in_action_radius()) {
				bool cmp_rst;
				if (this->get_team()->isInGodMode()) {
					cmp_rst = true;
				} else {
					cmp_rst = calc_score_compare(this, minding_player,
							SCORE_RUN_WITH_BALL_INTERCEPT, 0,
							_team->get_who_kick_off());
					//this->_match->update_compare_log(SCORE_RUN_WITH_BALL_INTERCEPT,_union_pid,minding_player->get_union_pid(),cmp_rst);
				}

				if (!cmp_rst) { //tackle this player
					player_break_ok(minding_player, this, BREAK_TACKLE); //断球成功
					_match->set_event_frames(minding_player->get_uid(),
							minding_player->get_union_pid(),
							this->get_union_pid(), 43);
					return;
				}

				minding_player->set_state(FrozenState::alloc());
				_match->set_event_frames(this->get_uid(), _union_pid,
						minding_player->_union_pid, 65);//带球过人
			}
		}
	}
	_match->get_ball()->set_pos(this->get_pos());
	run_to(vec_target, 0.9);
}

bool SoccerPlayer::has_beat_will(const Vector2D &target) {
	SoccerPlayer *minding_player = _match->get_defend_team()->_minding_player;
	if (minding_player == NULL) {
		return false;
	}

	double distance_to_dribble = 11000 - 100 * get_pos().distance(target);
	double beat_point = distance_to_dribble + _attr[ATT_BALL_CTRL] * 50
			+ _attr[STRONG] * 2000;
	if (RAND_DBL * 10000 < beat_point) {
		return true;
	}

	return false;
}

void SoccerPlayer::defend_home(void) {
	SoccerBall *ball = _match->get_ball();
	if (ball->get_motion_type() == SoccerBall::CROSS) {
		defend_air();
	} else {
		defend_ground();
	}
}

void SoccerPlayer::support_to(const Vector2D &pt, bool is_ready_time_out) {
	if (is_ready_time_out || is_at_pos(pt)) {
		set_speed(0);
		_team->_receiving_player = this;
		this->_is_ready_for_recv = true;
	} else {
		run_to(pt);
	}
}

void SoccerPlayer::defend_air(void) {
	SoccerBall *ball = _match->get_ball();
	SoccerPlayer *receiving_player =
			_match->get_attack_team()->_receiving_player;

	if (receiving_player == NULL) {
		LOG(WARNING) << "defend_air(), but receiving player not found";
		return;
	}

	Vector2D target_vec = (receiving_player->_receive_decision
			== RECEIVE_USE_HEAD) ? ball->get_head_vec()
			: ball->get_target_vec();

	if (_home.in(target_vec)) {
		run_to(target_vec);
	}
}

SoccerPlayer *SoccerPlayer::get_receiving_player(void) {
	SoccerTeam *team = _match->get_attack_team();
	if (team->_receiving_player != NULL) {
		return team->_receiving_player;
	}

	return team->_controlling_player;
}

bool SoccerPlayer::ground_tackle(void) // 断球
{
	/* 进攻方 接球人 */
	SoccerPlayer *receiving_player = get_receiving_player();
	if (receiving_player == NULL) {
		return false;
	}
	/* 球的 主人 */
	if (!(receiving_player->get_team()->isInGodMode())) {
		if ((_match->get_ball()->get_owner() == NULL)) {
			if ((receiving_player->_distance_to_ball)
					> (g_game_config.get_player_config("action_radius") * 2)) {
				player_break_ok(this, receiving_player,
						BREAK_INTERUPT_FREE_BALL); /* 断球成功 */
				_match->set_event_frames(this->get_uid(),
						this->get_union_pid(),
						receiving_player->get_union_pid(), 43);
				//this->_match->update_compare_log(SCORE_RUN_WITH_BALL_INTERCEPT,receiving_player->get_union_pid(),_union_pid,true);
				return true;
			}
		}
	}

	bool cmp_rst;
	if (receiving_player->get_team()->isInGodMode()) {
		cmp_rst = true;
	} else {
		cmp_rst = calc_score_compare(receiving_player, this,
				SCORE_RUN_WITH_BALL_INTERCEPT);
	}
	this->_match->update_compare_log(SCORE_RUN_WITH_BALL_INTERCEPT,receiving_player->get_union_pid(),_union_pid,cmp_rst);

	if (!cmp_rst) { /* 抢断成功了。判断是否会受伤,进攻方是否受伤 */
		if (this->check_injuried(receiving_player)) {
			int typ;
			if (receiving_player->get_cond() == 9) {
				typ = 68;
			} else if (receiving_player->get_cond() == 8) {
				typ = 69;
			} else if (receiving_player->get_cond() == 7) {
				typ = 70;
			}
			_match->set_event_frames(this->get_uid(), this->get_union_pid(),
					receiving_player->get_union_pid(), typ);

			bool rst = this->check_will_be_free_ball(receiving_player);
			LOG(INFO)<<"test....";
			if (rst) {//给任意球
				uint sum_typ = 0; // 犯规类型
				LOG(INFO)<<"free ball success..";
				sum_typ = RAND_ARRAY(5
						, OUT_RESTRICTED_HAND_BALL
						, FOUL_PULL_SHIRT
						, OUT_RESTRICTED_FOUL_SLIDE
						, OUT_RESTRICTED_FOUL_ELBOW
						, OUT_RESTRICTED_FOUL_CHARGE);
				MATCH_BREAK_NEW(this, receiving_player, ActionItem::BEBREAK, END_FOULED, sum_typ, N_FREE_KICK, 0);
				return true;
			}
		} else {
			_match->set_event_frames(this->get_uid(), this->get_union_pid(),
					receiving_player->get_union_pid(), 46);
			player_break_ok(this, receiving_player, BREAK_INTERUPT_RECV_PASS);
		}
		return true;
	} else { /* 断球失败 */
		_match->set_event_frames(this->get_uid(), this->get_union_pid(),
				receiving_player->get_union_pid(), 46);
		this->set_state(FrozenState::alloc());
	}

	return false;
}

bool SoccerPlayer::ground_slide(void) // 铲球
{
	return false;

	//	VLOG(3) << "##################" << _union_pid << "try ground slide";
	//	if (!this->_match->is_match_real_begin())
	//	{
	//		FrozenState* pState = FrozenState::alloc();
	//		pState->enter(*this);
	//		set_state(pState);
	//		_match->set_event_frames(_union_pid, _pMarkPlayer->_union_pid, GROUND_BALL_FL); //铲球失败
	//
	//        return false;
	//	}
	//
	//	SoccerPlayer *receiving_player = get_receiving_player();
	//	if (receiving_player == NULL)
	//	{
	//		return false;
	//	}
	//
	//	if ((_match->get_ball()->get_owner() == NULL))
	//	{
	//		if (receiving_player->_distance_to_ball > g_game_config.get_player_config("action_radius") * 2)
	//		{
	//			player_break_ok( this,receiving_player,BREAK_INTERUPT_FREE_BALL);//断球成功  铲球无主人的球
	//
	//			return true;
	//		}
	//	}
	//
	//	double a_score = receiving_player->calc_score(7
	//												, TEC_MOVE, 4
	//												, SPEED_PACE, 4
	//												, SPEED_ACC, 4
	//												, PHY_STR, 4
	//												, ATT_DRIB, 2
	//												, MENTAL_WORK, 8
	//												, ATT_CREAT, 8);
	//	double d_score = calc_score(7
	//							  , DEF_MARK, 4
	//							  , DEF_TACK, 2
	//							  , DEF_POSIT, 4
	//							  , SPEED_ACC, 8
	//							  , PHY_STR, 4
	//							  , DEF_AGGR, 8
	//							  , MENTAL_WORK, 8);
	//
	//	if (compitition_result(a_score, d_score, 30) == -1)
	//	{
	//		player_break_ok(this,receiving_player,BREAK_TACKLE);//断球成功 铲球有主人的球
	//
	//		return true;
	//	}
	//	else
	//	{
	//		//VLOG(3) << "player:" << _player_id << ", tackle slide fail";
	//		_match->set_event_frames(_union_pid, receiving_player->_union_pid, GROUND_BALL_FL);//52铲球失败
	//	}
	//
	//	return false;
}

void SoccerPlayer::defend_ground(void) {
	SoccerBall *ball = _match->get_ball();

	if (is_ball_in_action_radius()) {
		if (ball->get_owner() == NULL) { //如果是无主球，经过该球员的区域一定去抢断。
			double cmp_rst = 0.1;
			if (cmp_rst > RAND_DBL && (this->get_op_team()->isInGodMode()
					!= true)) {
				MATCH_BREAK_NEW(this, this, ActionItem::BEBREAK, END_BREAK, BREAK_INTERUPT_RECV_PASS, N_NORMAL_KICK, C_NULL);
				_match->set_event_frames(this->get_uid(),
						this->get_union_pid(), 0, 45);
				return;
			} else {
				this->set_state(FrozenState::alloc());
				return;
			}
		}

	//	if (has_tackle_will()) {
		ground_tackle(); /* 断球 */
		//return;
	//	}
		if (_pMarkPlayer == NULL) {
			set_state(MarkState::alloc());
			_pMarkPlayer = this;
		}
		return;
	}

	if (!_home.in(ball->get_pos())) {
		def_go_home();
		return;
	}

	if (is_turn_need_punish(ball->get_pos())) {
		heading_to(ball->get_pos());
		return;
	}

	if ((ball->get_owner() == NULL) && (ball->get_speed() == 0)) {
		run_to(ball->get_pos());
		return;
	}

	double relative_heading = 0;
	double target_speed = 0;

	if (ball->get_owner() == NULL) {
		relative_heading = ball->get_heading().dot(get_heading());
		target_speed = ball->get_speed();
	} else {
		relative_heading = ball->get_owner()->get_heading().dot(get_heading());
		target_speed = ball->get_owner()->get_speed();
	}

	if (relative_heading < -0.95) {
		run_to(ball->get_pos());
	} else {
		Vector2D to_direction = ball->get_pos() - get_pos();
		to_direction.normalize();
		double lookahead_time = to_direction.length() / (_attr[SPEED]
				+ target_speed);
		Vector2D predict_vec = ball->get_pos();
		if (ball->get_owner() == NULL) {
			predict_vec += (ball->get_heading() * ball->get_speed()
					* lookahead_time);
		} else {
			predict_vec += (ball->get_owner()->get_heading()
					* ball->get_owner()->get_speed() * lookahead_time);
		}
		run_to(predict_vec);
	}
}

bool SoccerPlayer::has_tackle_will(void) { // 断球概率
	return true;
}

//TODO 计算铲球的意愿
bool SoccerPlayer::has_slide_will(void) { // 铲球概率
	//在一定的距离才会抢断，不能太近，也不能太远，ATTR_AGGRESSIVE属性影响,角度判断
	if (_distance_to_ball > SLIDE_RADIUS && _distance_to_ball
			< g_game_config.get_player_config("action_radius")) {
		return true;
	}

	return false;
}

bool SoccerPlayer::has_mark_player_will(void) {
	double dis = get_pos().distance(_home.center());
	if (dis > g_game_config.get_player_config("dis_go_home")) {
		return false;
	}

	return true;
}

bool SoccerPlayer::gk_kick_off(){
	SoccerPlayer* target_player = NULL;
	//取在前场最牛逼的前锋
	std::vector<SoccerPlayer*> list;
	this->get_team()->get_top_shooter(list,1);
	target_player = list[0];
	int pre_fix = (int) (g_game_config.get_player_config("pass_prefix"));
	Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
	Vector2D target_pos = target_player->get_pos();

	Vector2D perfect_point = target_pos + (vec2d_normalize((goal_vector
			- target_pos))) * pre_fix * METER_TO_POINT;

	// double distance_to_support = get_pos().distance(perfect_point);

	Vector2D target(perfect_point.x, perfect_point.y);
	_match->get_ball()->set_target_vec(target);

	PlayerTelegram *player_msg = new PlayerTelegram(get_id(),
			target_player->get_id(), TELE_PLAYER_RECEIVE);
	_match->notify(player_msg);

	_team->_controlling_player = NULL;
	_match->get_ball()->set_owner(NULL);

	const PassReferItem &item =
			pass_refer_get((int) get_pos().distance(target));

	BallTelegram *ball_msg = new BallTelegram(get_id(),
			_match->get_ball()->get_id(), TELE_BALL_KICK);
	ball_msg->heading = target - get_pos();
	ball_msg->heading.normalize();
	ball_msg->speed = (int) item.speed_init;
	_match->notify(ball_msg);
	_match->set_event_frames(this->get_uid(), this->get_union_pid(), 0, 55);
	set_state(StopState::alloc());
	_move_status = PS_PASS;
	return true;
}

bool SoccerPlayer::pass_ball(SoccerPlayer *target_player) {
	int pre_fix = (int) (g_game_config.get_player_config("pass_prefix"));
	Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
	Vector2D target_pos = target_player->get_pos();

	Vector2D perfect_point = target_pos + (vec2d_normalize((goal_vector
			- target_pos))) * pre_fix * METER_TO_POINT;
	if (this->get_team()->check_coach_speak(SPEAK_MORE_EMPTY_PASS)) {
		perfect_point.x = perfect_point.x + 2 * METER_TO_POINT;
	} else if (this->get_team()->check_coach_speak(SPEAK_MORE_FOOT_PASS)) {
		perfect_point.x = perfect_point.x - 2 * METER_TO_POINT;
	}

	// double distance_to_support = get_pos().distance(perfect_point);

	SoccerPlayer *minding_player = NULL;
	int pos = _team->check_position(get_formation_pos());
	if(pos == 1 || pos == 2){
		minding_player = _match->get_defend_team()->_minding_player;
		if(minding_player == NULL){
			minding_player = _match->get_closest_to_ball_def();
		}
	}

	if (minding_player != NULL && (!this->is_gk())) {
		bool has_tackle_will = minding_player->has_tackle_will();
		if (has_tackle_will) {
			bool cmp_rst;
			if (this->get_team()->isInGodMode()) {
				cmp_rst = true;
			} else {
				cmp_rst = calc_score_compare(this, minding_player,
						SCORE_PASS_BALL_ON_GROUND_ATTACKING, 0,
						_team->get_who_kick_off());
			}

			if (!cmp_rst) {
				this->_match->update_compare_log(SCORE_PASS_BALL_ON_GROUND_ATTACKING,_union_pid,minding_player->get_union_pid(),cmp_rst);
				if (minding_player->check_injuried(this)) {
					int typ;
					if (this->get_cond() == 9) {
						typ = 68;
					} else if (this->get_cond() == 8) {
						typ = 69;
					} else if (this->get_cond() == 7) {
						typ = 70;
					}
					_match->set_event_frames(minding_player->get_uid(),
							minding_player->get_union_pid(), get_union_pid(),
							typ);
					//判断是否给任意球
					bool rst = minding_player->check_will_be_free_ball(this);
					LOG(INFO)<<"test....";
					uint sum_typ = 0; // 犯规类型
					sum_typ = RAND_ARRAY(5
							, OUT_RESTRICTED_HAND_BALL
							, FOUL_PULL_SHIRT
							, OUT_RESTRICTED_FOUL_SLIDE
							, OUT_RESTRICTED_FOUL_ELBOW
							, OUT_RESTRICTED_FOUL_CHARGE);
					if (rst) {
						MATCH_BREAK_NEW(minding_player, this, ActionItem::BEBREAK, END_FOULED, sum_typ, N_FREE_KICK, 0);
					} else {
						player_break_ok(minding_player, this, BREAK_TACKLE_PASS);
					}
				} else {
					player_break_ok(minding_player, this, BREAK_TACKLE_PASS);//断球成功
					_match->set_event_frames(minding_player->get_uid(),
							minding_player->get_union_pid(),
							this->get_union_pid(), 45);
				}
				return false;
			} else {
				_match->set_event_frames(minding_player->get_uid(),
						minding_player->get_union_pid(), this->get_union_pid(),
						45);
				minding_player->set_state(FrozenState::alloc());
			}

			/*			if (check_event_card_to_flash(minding_player, 2)) {
			 return false;
			 }*/

			minding_player->set_state(FrozenState::alloc());
		}
	}

	Vector2D target(perfect_point.x, perfect_point.y);
	_match->get_ball()->set_target_vec(target);

	PlayerTelegram *player_msg = new PlayerTelegram(get_id(),
			target_player->get_id(), TELE_PLAYER_RECEIVE);
	_match->notify(player_msg);

	_team->_controlling_player = NULL;
	_match->get_ball()->set_owner(NULL);

	const PassReferItem &item =
			pass_refer_get((int) get_pos().distance(target));

	BallTelegram *ball_msg = new BallTelegram(get_id(),
			_match->get_ball()->get_id(), TELE_BALL_KICK);
	ball_msg->heading = target - get_pos();
	ball_msg->heading.normalize();
	ball_msg->speed = (int) item.speed_init;
	_match->notify(ball_msg);
	_match->set_event_frames(this->get_uid(), this->get_union_pid(), 0, 55);
	if(this->is_gk()){
		set_state(StopState::alloc());
	}else{
		set_state(GoHomeState::alloc());
	}
	_move_status = PS_PASS;

	return true;
}

bool SoccerPlayer::to_people_or_ball(void) {
	return false;
}

bool SoccerPlayer::cross_pass_combat(void) /* 长传 */
{
	SoccerPlayer *minding_player = NULL;

	int pos = _team->check_position(get_formation_pos());
	if(pos == 1 || pos == 2){
		minding_player = _match->get_defend_team()->_minding_player;
		if(minding_player == NULL){
			minding_player = _match->get_closest_to_ball_def();
		}
	}

	if (minding_player != NULL) {
		bool willing = minding_player->has_block_player_will();
		if (willing) /* 对人 */
		{
			bool cmp_rst;
			if (this->get_team()->isInGodMode()) {
				cmp_rst = true;
			} else {
				cmp_rst = calc_score_compare(this, minding_player,
						SCORE_CROSS_BALL_HIGH_FROM_THE_BYLING_INTERCEPT, 0,
						_team->get_who_kick_off());
			}

			if (!cmp_rst) {
				this->_match->update_compare_log(SCORE_CROSS_BALL_HIGH_FROM_THE_BYLING_INTERCEPT,_union_pid,minding_player->get_union_pid(),cmp_rst);
				player_break_ok(minding_player, this, BREAK_CHARGE); /* 断球成功 */
				_match->set_event_frames(minding_player->get_uid(),
						minding_player->get_union_pid(), this->get_union_pid(),
						44);
				return false;
			}
		}

		willing = minding_player->has_tackle_will();
		if (willing) /* 对球 */
		{
			bool cmp_rst;
			if (this->get_team()->isInGodMode()) {
				cmp_rst = true;
			} else {
				cmp_rst = calc_score_compare(this, minding_player,
						SCORE_CROSS_BALL_HIGH_FROM_THE_BYLING_ATTACKING, 0,
						_team->get_who_kick_off());
			}

			if (!cmp_rst) {
				this->_match->update_compare_log(SCORE_CROSS_BALL_HIGH_FROM_THE_BYLING_ATTACKING,_union_pid,minding_player->get_union_pid(),cmp_rst);
				player_break_ok(minding_player, this, BREAK_INTERUPT_PASS); /* 断球成功 */
				_match->set_event_frames(minding_player->get_uid(),
						minding_player->get_union_pid(), this->get_union_pid(),
						43);
				return false;
			} else {
				_match->set_event_frames(minding_player->get_uid(),
						minding_player->get_union_pid(), this->get_union_pid(),
						45);
				minding_player->set_state(FrozenState::alloc());
			}
			/*
			 if (check_event_card_to_flash(minding_player, 0)) {
			 return false;
			 }*/
		}
	}

	return true;
}

void SoccerPlayer::cross_ball(SoccerPlayer *target_player,
		double distance_to_support, bool is_forcss) {
	if(!is_gk()){
		if (!cross_pass_combat()) {
			return;
		}
	}

	//double tec_pass = 0.;

	//tec_pass = _attr[ATT_PASS];

	//和传球一样，计算完美落点和真实落点
	int pre_fix = (int) (g_game_config.get_player_config("cross_prefix"));
	Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
	Vector2D target_pos = target_player->get_pos();
	Vector2D perfect_point;
	if (is_forcss == false) {
		perfect_point = target_pos + (vec2d_normalize(
				(goal_vector - target_pos))) * pre_fix * METER_TO_POINT;
	} else {
		perfect_point = target_pos;
	}

	//和传球一样，计算完美落点和真实落点
	pre_fix = (int) (g_game_config.get_player_config("cross_prefix"));
	target_pos = target_player->get_pos();
	perfect_point = target_pos + (vec2d_normalize((goal_vector - target_pos)))
			* pre_fix * METER_TO_POINT;

	Vector2D target(perfect_point.x, perfect_point.y);
	const CrossReferItem &item = cross_refer_get((int) get_pos().distance(
			target));
	Vector2D head_vec = (target - get_pos()) * item.head_distance_percent;

	_match->get_ball()->set_target_vec(target);
	_match->get_ball()->set_head_vec(head_vec);

	PlayerTelegram *player_msg = new PlayerTelegram(get_id(),
			target_player->get_id(), TELE_PLAYER_RECEIVE);
	_match->notify(player_msg);
	_team->_controlling_player = NULL;
	_match->get_ball()->set_owner(NULL);

	if(this->is_gk()){
		set_state(StopState::alloc());
	}else{
		set_state(NULL);
	}

	BallTelegram *ball_msg = new BallTelegram(get_id(), _match->get_ball()->get_id(), TELE_BALL_CROSS);
		ball_msg->heading = target - get_pos();
		ball_msg->heading.normalize();
		ball_msg->speed = (int)item.speed_init;
		ball_msg->speed_z = (int)item.speed_init_z;
		_match->notify(ball_msg);

		_move_status = PS_CROSS_PASS;
		_match->set_event_frames(this->get_uid(),_union_pid, target_player->_union_pid, 57);//长传成功
	}

void SoccerPlayer::pass(const RegionSet &target_regions,
		SoccerPlayer *target_player, bool is_quick_pass) {

	//传球的人在某个位置的时候，前方没有人，则直接射门
	/*	if(this->_distance_to_goal < 25 * METER_TO_POINT){
	 SoccerPlayer* player_in_way = this->check_player_in_attack_way();
	 if(player_in_way == NULL){
	 shoot_goal();
	 }
	 }*/
	if (is_quick_pass == false) {
		//要传递的目标，不在位置的话。先向前跑动
		if (!target_player->is_ready_for_recv() || (_pass_run_to_count
				< RUN_TO_COUNT)) {
			Vector2D vec = this->get_pos();
			vec.x = vec.x + 2 * METER_TO_POINT;
			this->run_to(vec);
			//***********************************************************************************
			_match->set_ball_owner(get_uid(), _union_pid, 0, 65); // 带球跑dd
			_pass_run_to_count++;
			return;
		}
	}
	if(this->is_gk()){
		if(_pass_run_to_count <RUN_TO_COUNT){
			_pass_run_to_count++;
			return;
		}
	}


	_pass_run_to_count = 0;
	bool success = pass_ball(target_player);
	if (success) {
		//传球成功,该球员加分
		this->modifer_score(0.1);
		_team->add_action(_union_pid, ActionItem::PASS);
		//_match->set_event_frames(this->get_uid(),_union_pid, target_player->_union_pid, 55); //传球成功
	} else {
		this->modifer_score(-0.2);
	}
}

void SoccerPlayer::force_cross(const RegionSet &target_regions,
		SoccerPlayer *target_player) {
	if (target_player == NULL) {
		LOG(ERROR) << "target_player is NULL!";
		return;
	}
	double distance_to_support = get_pos().distance(target_player->get_pos());
	this->cross_ball(target_player, distance_to_support, true);
	//传球成功，加分
	this->modifer_score(0.1);
	_team->add_action(_union_pid, ActionItem::CROSS);
	_match->set_event_frames(this->get_uid(), _union_pid,
			target_player->_union_pid, 55); //传球成功
}

void SoccerPlayer::cross(const RegionSet &target_regions,
		SoccerPlayer *target_player) {
	if (target_player == NULL) {
		LOG(ERROR) << "target_player is NULL!";
		return;
	}

	if(this->is_gk()){
		if(_pass_run_to_count <RUN_TO_COUNT){
			_pass_run_to_count++;
			return;
		}
	}

	//要传递的目标，不在位置的话。先向前跑动
	if (!target_regions.in(target_player->get_pos())) {
		if (_cross_run_to_count < RUN_TO_COUNT) {
			Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
			this->run_to(goal_vector);
			_match->set_ball_owner(get_uid(), _union_pid, 0, 65); // 带球跑
			_cross_run_to_count++;
			//VLOG(3)<<"CROSS THE FUCKING BALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL";
			return;
		}
	}
	_cross_run_to_count = 0;
	double distance_to_support = get_pos().distance(target_player->get_pos());
	this->cross_ball(target_player, distance_to_support);
	//传球成功，加分
	this->modifer_score(0.1);
	_team->add_action(_union_pid, ActionItem::CROSS);
	_match->set_event_frames(this->get_uid(), _union_pid,
			target_player->_union_pid, 55); //传球成功
}

void SoccerPlayer::decide_receive_type(void) {
	SoccerBall *ball = _match->get_ball();
	//    Vector2D receive_vec;
	if (ball->get_state()->get_type() == TYPE_BallCrossState) {
		if (has_head_receive_will()) {
			_receive_decision = RECEIVE_USE_HEAD;
		} else {
			_receive_decision = RECEIVE_USE_FOOT;
		}
	} else {
		_receive_decision = RECEIVE_USE_FOOT;
	}

	if (_team->_supporting_player == this) {
		_team->_supporting_player = NULL;
	}
	_team->_receiving_player = this;
}

//如果旁边有人的话，就用头，否则用脚.第一时间射门时，禁区不头球，短传不头球
bool SoccerPlayer::has_head_receive_will(void) {
	double value = RAND_DBL;
	if(value < 0.7){
		return true;
	}else{
		return false;
	}
	/*SoccerPlayer *player = this->get_op_team()->get_air_defend_player();
	if(player == NULL){
		return false;
	}

	double distance = player->get_pos().distance(this->get_pos());
	if (distance < g_game_config.get_player_config("action_radius")) {
		return true;
	}
	return false;
*/
}

double SoccerPlayer::foot_receive_a_score(void) {
	/*    return calc_score(5
	 , SPEED_PACE, 4
	 , SPEED_ACC, 4
	 , PHY_STR, 2
	 , DEF_POSIT, 2
	 , MENTAL_WORK, 8);*/
	return 0.1;
}

//TODO
double SoccerPlayer::foot_receive_d_score(void) {
	/*    return calc_score(5
	 , SPEED_PACE, 4
	 , SPEED_ACC, 4
	 , PHY_STR, 2
	 , DEF_POSIT, 2
	 , MENTAL_WORK, 8);*/
	return 0.1;
}
//TODO
double SoccerPlayer::head_receive_a_score(void) {
	/*    return calc_score(6
	 , SPEED_PACE, 4
	 , SPEED_ACC, 4
	 , PHY_STR, 2
	 , TEC_MOVE, 2
	 , MENTAL_WORK, 8
	 , ATT_CREAT, 8);*/
	return 0.1;
}
//TODO
double SoccerPlayer::head_receive_d_score(void) {
	/* return calc_score(6
	 , SPEED_PACE, 4
	 , SPEED_ACC, 4
	 , PHY_STR, 2
	 , DEF_POSIT, 2
	 , DEF_AGGR, 8
	 , MENTAL_WORK, 8);*/
	return 0.1;
}

void SoccerPlayer::receive_ball(void) {
	SoccerBall *ball = _match->get_ball();
	/*	 接球前先判断是否已经被判断越位，如果是的，就直接退出。距离超过1米的，肯定是越位的
	 if (this->get_team()->has_offside() == 2) {
	 MATCH_BREAK_NEW(this->get_team()->get_offside_player(), this, ActionItem::BEBREAK, END_FOULED, FOUL_OFFLINE, N_NORMAL_KICK, C_NULL);
	 _match->set_event_frames(this->get_uid(),
	 this->get_team()->get_offside_player()->get_union_pid(), 0, 39);
	 return;
	 }*/

	if (ball->get_motion_type() == SoccerBall::OUTSIZE) {
		uint sub_typ = 0;
		if (ball->get_pos().y > PITCH_HEIGHT - OUTSIDE_WIDTH
				|| ball->get_pos().y < OUTSIDE_HEIGHT) { /* 边线 */
			sub_typ = OUTSIDE_SIDELINE;
			_match->set_event_frames(this->get_uid(), 0, 0, 49);
		} else { /* 底线 */
			sub_typ = OUTSIDE_ENDLINE;
			_match->set_event_frames(this->get_uid(), 0, 0, 50);
		}
		MATCH_BREAK_NEW(ball->get_previous_owner(), this, ActionItem::BEBREAK, END_ATTACK_MISTAKE, sub_typ, N_NORMAL_KICK, C_NULL);
		return;
	}

	Vector2D target_vec = (_receive_decision == RECEIVE_USE_FOOT)
	? ball->get_target_vec()
	: ball->get_head_vec();

	bool is_ball_in_action = is_ball_in_action_radius();
	if (is_at_pos(target_vec) || is_ball_in_action)
	{
		if ((ball->get_speed() < 7) && (!is_ball_in_action))
		{
			run_to(ball->get_pos());
			return;
		} else {
			set_speed(0);
			heading_to(ball->get_pos());
		}
	}
	else
	{
		if (ball->get_speed() < 5)
		{
			run_to(ball->get_pos());
			return;
		}
		run_to(target_vec);
	}
	if (!is_ball_in_action)
	{
		return;
	}

	if(this->get_team()->isInGodMode() != true) {
		PlayerQueue *queue = _match->get_queue_to_ball();
		PlayerQueueIter it = queue->begin();
		for (; it != queue->end(); ++it)
		{
			SoccerPlayer *player = it.get_player();
			if (!player->is_ball_in_action_radius())
			{
				break;
			}

			if (player->_team->get_id() == _team->get_id())
			{
				continue;
			}
			bool rst = calc_score_compare(this,player,SCORE_RECIVE_BALL,5*METER_TO_POINT);
				if (!rst)
				{
					this->_match->update_compare_log(SCORE_RECIVE_BALL,_union_pid,player->get_union_pid(),rst);
					player_break_ok(player, this, BREAK_INTERUPT_RECV_PASS);//断球成功
					_match->set_event_frames(player->get_uid(),player->get_union_pid(), this->get_union_pid(), 45);
					return;
				} else {
					player->set_state(FrozenState::alloc());
					_match->set_event_frames(player->get_uid(),player->get_union_pid(), this->get_union_pid(), 45);
				}
			}
		}

		ball->set_z(0);
		set_speed(0);

		_match->set_event_frames(this->get_uid(),this->get_union_pid(),0, 67);
		ball->set_owner(this);

		//_match->set_ball_owner(this->_union_pid, RECEIVE_BALL_OK);

		_team->_receiving_player = NULL;
		_team->_controlling_player = this;

		set_state(NULL);
		_last_receive_action = _receive_decision;
	}

bool SoccerPlayer::is_ball_in_action_radius(void) {
	if (_distance_to_ball <= g_game_config.get_player_config("action_radius")) {
		return true;
	}

	return false;
}

void SoccerPlayer::keep_distance(int mindplayer_id) {
	SoccerPlayer *pplayer = NULL;
	pplayer = _match->get_player_by_entityId(mindplayer_id);
	if (pplayer == NULL) {
		//VLOG(1) << "DefGoHomeState NULL";
		set_state(DefGoHomeState::alloc());
		return;
	}

	Vector2D tmp = pplayer->get_pos();

	if (_keep_distance_stage == 1) {
		double x = this->get_pos().x - tmp.x;
		double y = this->get_pos().y - tmp.y;
		tmp.x += 3 * METER_TO_POINT;

		if (y > -1 * METER_TO_POINT && y < 1 * METER_TO_POINT && x < 3
				* METER_TO_POINT) {
			_keep_distance_stage = 2;
		}
		run_to(tmp);
	} else {
		tmp.x += 3 * METER_TO_POINT;

		run_to(tmp, 0.5);
	}
}

bool SoccerPlayer::is_player_in_mind_area(const SoccerPlayer &player) {
	return true;
}

bool SoccerPlayer::has_mind_ball_will(void) {
	return true;
}

bool SoccerPlayer::has_mind_player_will(void) {
	return true;
}

bool SoccerPlayer::has_head_shoot_goal_will(double distance_to_goal) {
	//double distance_to_goal_point = 13135. - distance_to_goal * 95 / 300;
	//double arounding_modifier = _match->get_queue_to_ball()->count(
	//		g_game_config.get_player_config("action_radius") * 2, NULL) * 1000;
	//double head_shoot_will_point = _attr[HEADER_ACCURACY] * 20
//			+ distance_to_goal_point - arounding_modifier
//			+ _attr[HEADER_ACCURACY] * 10;
	//if ((RAND_DBL * 10000) < head_shoot_will_point)
	if ((RAND_DBL) < 0.5) {
		return true;
	}

	return false;
}

bool SoccerPlayer::in_corner_kick(SoccerPlayer *pPlayer, RoundEndSubTyp typ) {
	if (_match->_count_corent <= 2) {
		int in_pro = 20;
		if (_match->_round_time >= 45) {
			in_pro = 50;
		} else if (_match->_round_time >= 90) {
			in_pro = 100;
		}
		int tmp = RAND_INT % 100;
		if (tmp <= in_pro) {
			pPlayer->modifer_score(0.2);
			MATCH_BREAK_NEW(this, pPlayer, ActionItem::BEBREAK, END_GOAL_FAIL, typ, N_CORNER_KICK, C_NULL);//断球成功
			_match->set_event_frames(pPlayer->get_uid(),
					pPlayer->get_union_pid(), 0, 12);
			_match->_count_corent++;
			this->set_state(StopState::alloc());
			return true;
		}
	}
	return false;
}

double SoccerPlayer::get_shoot_with_team_skill_plus() {
	int skill_id = this->get_team()->get_last_round_skill_used();
	if (skill_id != 0) {
		double modifer = check_skill_speak_effect(skill_id,
				this->get_op_team()->get_coach_speak_type());
		TeamSkill* skill = this->get_team()->get_team_skill_info(skill_id);
		double chance = (((this->get_team()->get_alias_tactic_plus()+((double)skill->chance)) / 10000.)) * modifer;
		if(this->get_team()->check_is_last_skill_same()){
			chance = 0.5*chance;
		}
		this->get_team()->set_team_skill_success_rate(chance);
		return chance;
	}
	return 0.;
}

double SoccerPlayer::check_skill_speak_effect(int skill_id, int speak_type) {
	switch (skill_id) {
	case 1: {
		if (speak_type == SPEAK_MORE_SPACE)
			return 1.3;
		if (speak_type == SPEAK_LESS_SPACE)
			return 0.7;
	}
		break;
	case 2: {
		if (speak_type == SPEAK_MORE_SPACE)
			return 0.7;
		if (speak_type == SPEAK_LESS_SPACE)
			return 1.3;
	}
		break;
	case 3: {
		if (speak_type == SPEAK_MORE_SPACE)
			return 0.7;
		if (speak_type == SPEAK_LESS_SPACE)
			return 1.3;
	}
		break;
	case 4: {
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 0.7;
	}
		break;
	case 5: {
		if (speak_type == SPEAK_MORE_FOOT_PASS)
			return 1.3;
		if (speak_type == SPEAK_MORE_EMPTY_PASS)
			return 0.7;
	}
		break;
	case 6: {
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 0.7;
	}
		break;
	case 7: {
		if (speak_type == SPEAK_MORE_FOOT_PASS)
			return 1.3;
		if (speak_type == SPEAK_MORE_EMPTY_PASS)
			return 0.7;
	}
		break;
	case 8: {
		if (speak_type == SPEAK_MORE_CORSS)
			return 1.3;
		if (speak_type == SPEAK_MORE_PASS)
			return 0.7;
	}
		break;
	case 9: {
		if (speak_type == SPEAK_MORE_CORSS)
			return 1.3;
		if (speak_type == SPEAK_MORE_PASS)
			return 0.7;
	}
		break;
	case 10: {
		if (speak_type == SPEAK_MORE_EMPTY_PASS)
			return 1.3;
		if (speak_type == SPEAK_MORE_FOOT_PASS)
			return 0.7;
	}
		break;
	case 11: {
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 0.7;
	}
		break;
	case 12: {
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 0.7;
	}
		break;
	case 13: {
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_LESS_SPACE)
			return 1.3;
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 0.7;
		if (speak_type == SPEAK_MORE_SPACE)
			return 0.7;
	}
		break;
	case 14: {
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_MORE_SPACE)
			return 1.3;
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 0.7;
		if (speak_type == SPEAK_LESS_SPACE)
			return 0.7;
	}
		break;
	case 15: {
		if (speak_type == SPEAK_MORE_PASS)
			return 1.3;
		if (speak_type == SPEAK_MORE_CORSS)
			return 0.7;
		break;
	}
	default:
		return 1.;
	}
	return 1.;
}

void SoccerPlayer::shoot_goal(void) {
	/* 球门中心点 */
	Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);
	/* 防守人 */
	SoccerPlayer *pPlayer = get_mind_player();
	if(pPlayer == NULL){
		pPlayer = _match->get_closest_to_ball_def();
	}

	/* 到球门中心点的距离 */
	double distance_to_goal = get_pos().distance(goal_vector);
	/* 和守门员之间的距离 */
	//Vector2D vec = this->_match->get_defend_team()->get_gk_player()->get_pos();
	//double distance_to_gk = this->get_pos().distance(vec);

	/*	if (this->get_pos().x < B_FORBIDDEN_AREA_X - 50) // 小于 大禁区
	 {
	 this->dribble_to(goal_vector);
	 return;
	 } else {
	 if (distance_to_goal > 12 * METER_TO_POINT) {
	 if (distance_to_gk > 5 * METER_TO_POINT) {
	 this->dribble_to(goal_vector);
	 return;
	 }
	 }
	 }*/

	/* 判断是否是新手任务模式,做特殊处理 */
	if ((this->get_team()->get_newbie_state() == 0)
			&& (this->get_team()->get_team_scroe() < 2)) {
		this->_move_status = PS_SHOOT;
		shoot_goal_action(GOAL_FOOT);
		return;
	}

	bool is_att_god_mode = this->get_team()->isInGodMode();
	bool is_att_lose_mode = this->get_team()->isInLoserMode();
	int total_score = this->get_team()->get_team_scroe();
	if (is_att_lose_mode || (total_score >= 8)) {
		_match->get_defend_team()->_gk_player->modifer_score(0.4);
		this->modifer_score(-0.4);
		_match->set_round_end(_match->get_defend_team()->_gk_pid, _union_pid,
				_uid);
		uint sum_typ = 0; // 被扑出的类型
		sum_typ = RAND_ARRAY(2
				, SHOT_FOOT_FAIL_GK_SAVE
				, SHOT_FOOT_FAIL_GK_PUSH);
		this->_move_status = PS_SHOOT;
		shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
		MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
		return;
	}

	if (_last_receive_action == RECEIVE_USE_HEAD) {
		//头球函数：先和落点附近最近的一个比大小，如果成功和门将比
		if (has_head_shoot_goal_will(distance_to_goal)) // 头球
		{
			if ((!is_att_god_mode) && pPlayer != NULL) {
				if (!calc_score_compare(this, pPlayer, SCORE_HEAD_AT_GOAL, 0)) {
					this->_match->update_compare_log(SCORE_HEAD_AT_GOAL,_union_pid,pPlayer->get_union_pid(),false);
					if (in_corner_kick(pPlayer, SHOT_FAIL_GK_OUTSIDE))//进入角球
					{
						return;
					}
					//防守成功的话，获取一个防守的头球
					pPlayer->modifer_score(0.2);
					MATCH_BREAK_NEW(pPlayer, this, ActionItem::BEBREAK, END_GOAL_FAIL, SHOT_DEFENDER_INTERUPT, N_NORMAL_KICK, C_NULL);//断球成功
					_match->set_event_frames(pPlayer->get_uid(),
							pPlayer->get_union_pid(), 0, 47);
					return;
				}
			}

			// 完成，和门将比
			bool b_gk = calc_score_compare(this,
					this->_match->get_defend_team()->get_gk_player(),
					SCORE_HEAD_AT_GOAL_GK, distance_to_goal);
			if (!b_gk) {
				if (pPlayer != NULL) {
					pPlayer->set_state(FrozenState::alloc());
				}
				this->_match->update_compare_log(SCORE_HEAD_AT_GOAL_GK,_union_pid,this->_match->get_defend_team()->get_gk_player()->get_union_pid(),b_gk);
				if (this->get_team()->get_last_round_skill_used() != 0) {
					if (this->in_corner_kick(
							this->_match->get_defend_team()->get_gk_player(),
							SHOT_FAIL_GK_OUTSIDE)) {
						return;
					}
				}

				int rand = RAND_INT % 100;
				if (rand <= 40) { //被成功扑救了,守门员加分
					_match->get_defend_team()->_gk_player->modifer_score(0.4);
					_match->set_round_end(_match->get_defend_team()->_gk_pid,
							_union_pid, _uid);
					uint sum_typ = 0; // 被扑出的类型
					sum_typ = RAND_ARRAY(3
							, SHOT_HEAD_FAIL_GK_SAVE
							, SHOT_HEAD_FAIL_GK_PUSH
							, SHOT_HEAD_FAIL_GK_PUSH_OUTSIDE);
					shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
					MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
				} else {
					if (in_corner_kick(pPlayer, SHOT_FAIL_GK_OUTSIDE))//进入角球
					{
						return;
					}
					uint sum_typ = 0; // 射偏的类型
					sum_typ = RAND_ARRAY(3
							, SHOT_FORWARD_OUTTARGET
							, SHOT_FORWARD_CROSSBAR
							, SHOT_FORWARD_GOALPOST);
					MATCH_BREAK_NEW(this, this, ActionItem::SHOOT_OUTSIDE, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
					shoot_but_miss();
					this->modifer_score(-0.4);
				}

				return;
			}

			shoot_goal_action(GOAL_HEAD);
			return;
		}

		_last_receive_action = RECEIVE_USE_FOOT;
		return;
	}

	if (has_shoot_goal_will(distance_to_goal)) // 踢球
	{
		if ((!is_att_god_mode) && pPlayer != NULL) {
			if (!calc_score_compare(this, pPlayer, SCORE_SHOOT_AT_GOAL, 0)) {
				this->_match->update_compare_log(SCORE_SHOOT_AT_GOAL,_union_pid,pPlayer->get_union_pid(),false);
				if (in_corner_kick(pPlayer, SHOT_DEFENDER_INTERUPT_OUTSIDE))//进入角球
				{
					return;
				}
				//普通被打断
				MATCH_BREAK_NEW(pPlayer, this, ActionItem::BEBREAK, END_GOAL_FAIL, SHOT_DEFENDER_INTERUPT,N_NORMAL_KICK,C_NULL);//断球成功
				_match->set_event_frames(pPlayer->get_uid(),
						pPlayer->get_union_pid(), 0, 44);
				return;
			}
		}

		//计算GK
		bool b_gk = calc_score_compare(this,
				this->_match->get_defend_team()->get_gk_player(),
				SCORE_SHOOT_AT_GOAL_GK, distance_to_goal);
		if (!b_gk) { // 完成，被守门员成功防守
			//this->_match->update_compare_log(SCORE_SHOOT_AT_GOAL_GK,_union_pid,this->_match->get_defend_team()->get_gk_player()->get_union_pid(),false);
			if (pPlayer != NULL) {
				pPlayer->set_state(FrozenState::alloc());
			}
			//如果使用了技能，至少有个角球
			if (this->get_team()->get_last_round_skill_used() != 0) {
				if(this->in_corner_kick(
						this->_match->get_defend_team()->get_gk_player(),
						SHOT_FAIL_GK_OUTSIDE)){
					return;
				}
			}

			_match->get_defend_team()->_gk_player->modifer_score(0.4);

			this->modifer_score(-0.4);
			_match->set_round_end(_match->get_defend_team()->_gk_pid,
					_union_pid, _uid);
			uint sum_typ = 0; // 被扑出的类型
			sum_typ = RAND_ARRAY(2
					, SHOT_FOOT_FAIL_GK_SAVE
					, SHOT_FOOT_FAIL_GK_PUSH);
			this->_move_status = PS_SHOOT;
			shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
			MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
			return;
		}

		if (in_corner_kick(pPlayer, SHOT_FAIL_GK_OUTSIDE))//进入角球
		{
			return;
		}
		this->_move_status = PS_SHOOT;
		shoot_goal_action(GOAL_FOOT);
		return;
	} else {
		dribble_to(goal_vector);
	}

	adjust();
}

void SoccerPlayer::fat_shoot_goal(){
	/* 球门中心点 */
		Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);
	/* 到球门中心点的距离 */
	double distance_to_goal = get_pos().distance(goal_vector);
	/* 和守门员之间的距离 */
	//Vector2D vec = this->_match->get_defend_team()->get_gk_player()->get_pos();
	/* 判断是否是新手任务模式,做特殊处理 */
	if ((this->get_team()->get_newbie_state() == 0)
			&& (this->get_team()->get_team_scroe() < 2)) {
		this->_move_status = PS_SHOOT;
		shoot_goal_action(GOAL_FOOT);
		return;
	}

	bool is_att_lose_mode = this->get_team()->isInLoserMode();
	int total_score = this->get_team()->get_team_scroe();
	if (is_att_lose_mode || (total_score >= 8)) {
		_match->get_defend_team()->_gk_player->modifer_score(0.4);
		this->modifer_score(-0.4);
		_match->set_round_end(_match->get_defend_team()->_gk_pid, _union_pid,
				_uid);
		uint sum_typ = 0; // 被扑出的类型
		sum_typ = RAND_ARRAY(2
				, SHOT_FOOT_FAIL_GK_SAVE
				, SHOT_FOOT_FAIL_GK_PUSH);
		this->_move_status = PS_SHOOT;
		shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
		MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
		return;
	}

	//计算GK
	bool b_gk = calc_score_compare(this,
			this->_match->get_defend_team()->get_gk_player(),
					SCORE_GK_FAR_SHOOT, distance_to_goal);
	if (!b_gk) { // 完成，被守门员成功防守
		this->_match->update_compare_log(SCORE_GK_FAR_SHOOT,_union_pid,this->_match->get_defend_team()->get_gk_player()->get_union_pid(),false);
		//如果使用了技能，至少有个角球
		if (this->get_team()->get_last_round_skill_used() != 0) {
			if(this->in_corner_kick(
					this->_match->get_defend_team()->get_gk_player(),
					SHOT_FAIL_GK_OUTSIDE)){
				return;
			}
		}

		_match->get_defend_team()->_gk_player->modifer_score(0.4);

		this->modifer_score(-0.4);
		_match->set_round_end(_match->get_defend_team()->_gk_pid,
				_union_pid, _uid);
		uint sum_typ = 0; // 被扑出的类型
		sum_typ = RAND_ARRAY(2
				, SHOT_FOOT_FAIL_GK_SAVE
				, SHOT_FOOT_FAIL_GK_PUSH);
		this->_move_status = PS_SHOOT;
		shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
		MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
		return;
	}

	this->_move_status = PS_SHOOT;
	shoot_goal_action(GOAL_FOOT);
	return;
}


void SoccerPlayer::force_shoot_goal(void) {
	Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);
	SoccerPlayer *pPlayer = get_mind_player();
	double distance_to_goal = get_pos().distance(goal_vector);

	if (this->get_pos().x < B_FORBIDDEN_AREA_X) // 小于 大禁区
	{
		this->dribble_to(goal_vector);
		return;
	} else {
		double shoot_will = 1.05 - (abs(1332 - (int) this->get_pos().x))
				* 0.005;
		if (RAND_DBL > shoot_will) {
			this->dribble_to(goal_vector);
			return;
		}
	}
	int total_score = this->get_team()->get_team_scroe();
	if (total_score >= 8) {
		_match->get_defend_team()->_gk_player->modifer_score(0.4);
		this->modifer_score(-0.4);
		_match->set_round_end(_match->get_defend_team()->_gk_pid, _union_pid,
				_uid);
		uint sum_typ = 0; // 被扑出的类型
		sum_typ = RAND_ARRAY(2
				, SHOT_FOOT_FAIL_GK_SAVE
				, SHOT_FOOT_FAIL_GK_PUSH);
		this->_move_status = PS_SHOOT;
		shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
		MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
		return;
	}


	if (_last_receive_action == RECEIVE_USE_HEAD) {
		//头球函数：先和落点附近最近的一个比大小，如果成功和门将比
		if (has_head_shoot_goal_will(distance_to_goal)) {
			if (pPlayer != NULL) {
				if (!calc_score_compare(this, pPlayer, SCORE_HEAD_AT_GOAL, 0,
						_team->get_who_kick_off())) {
					this->_match->update_compare_log(SCORE_HEAD_AT_GOAL,_union_pid,pPlayer->get_union_pid(),false);
					//防守成功的话，获取一个防守的头球
					pPlayer->modifer_score(0.2);
					MATCH_BREAK_NEW(pPlayer, this, ActionItem::BEBREAK, END_GOAL_FAIL, SHOT_DEFENDER_INTERUPT, N_NORMAL_KICK, C_NULL);//断球成功
					//set_ball_goal_vector(SHOT_DEFENDER_INTERUPT);
					_match->set_event_frames(pPlayer->get_uid(),
							pPlayer->get_union_pid(), 0, 47);
					return;
				}
			}

			bool b_gk = calc_score_compare(this,
					this->_match->get_defend_team()->get_gk_player(),
					SCORE_HEAD_AT_GOAL_GK, distance_to_goal);
			if (!b_gk) {

				//完成，和门将比
				this->_match->update_compare_log(SCORE_HEAD_AT_GOAL_GK,_union_pid,this->_match->get_defend_team()->get_gk_player()->get_union_pid(),b_gk);
				int rand = RAND_INT % 100;
				if (rand <= 40) { //被成功扑救了,守门员加分
					_match->get_defend_team()->_gk_player->modifer_score(0.4);
					_match->set_round_end(_match->get_defend_team()->_gk_pid,
							_union_pid, _uid);
					uint sum_typ = 0; // 被扑出的类型
					sum_typ = RAND_ARRAY(3
							, SHOT_HEAD_FAIL_GK_SAVE
							, SHOT_HEAD_FAIL_GK_PUSH
							, SHOT_HEAD_FAIL_GK_PUSH_OUTSIDE);
					shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
					MATCH_BREAK_NEW(pPlayer, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
					this->modifer_score(-0.4);
				} else {
					uint sum_typ = 0; // 射门射偏
					sum_typ = RAND_ARRAY(3
							, SHOT_FORWARD_OUTTARGET
							, SHOT_FORWARD_CROSSBAR
							, SHOT_FORWARD_GOALPOST);
					this->_move_status = PS_SHOOT;
					shoot_but_miss();
					MATCH_BREAK_NEW(this, this, ActionItem::SHOOT_OUTSIDE, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
					this->modifer_score(-0.4);
				}
				return;
			}

			this->_move_status = PS_SHOOT;
			shoot_goal_action(GOAL_HEAD);
			return;
		}

		_last_receive_action = RECEIVE_USE_FOOT;
	} else // 脚踢球
	{
		if (pPlayer != NULL) {
			if (!calc_score_compare(this, pPlayer, SCORE_SHOOT_AT_GOAL, 0,
					_team->get_who_kick_off())) {
				//普通被打断
				this->_match->update_compare_log(SCORE_SHOOT_AT_GOAL,_union_pid,pPlayer->get_union_pid(),false);
				MATCH_BREAK_NEW(pPlayer,this, ActionItem::BEBREAK, END_GOAL_FAIL,SHOT_DEFENDER_INTERUPT,N_NORMAL_KICK,C_NULL);//断球成功
				_match->set_event_frames(pPlayer->get_uid(),
						pPlayer->get_union_pid(), 0, 32);
				return;
			}
		}

		bool b_gk = calc_score_compare(this,
				this->_match->get_defend_team()->get_gk_player(),
				SCORE_HEAD_AT_GOAL_GK, distance_to_goal);
		if (!b_gk) {
			//计算GK
			this->_match->update_compare_log(SCORE_SHOOT_AT_GOAL,_union_pid,_match->get_defend_team()->_gk_player->get_union_pid(),false);
			_match->get_defend_team()->_gk_player->modifer_score(0.4);
			this->modifer_score(-0.4);
			_match->set_round_end(_match->get_defend_team()->_gk_pid,
					_union_pid, _uid);

			uint sum_typ = 0; // 被扑出的类型
			sum_typ = RAND_ARRAY(2
					, SHOT_FOOT_FAIL_GK_SAVE
					, SHOT_FOOT_FAIL_GK_PUSH);
			this->_move_status = PS_SHOOT;
			shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
			MATCH_BREAK_NEW(this,this, ActionItem::SHOOT, END_GOAL_FAIL,sum_typ,N_NORMAL_KICK,C_NULL);
			return;
		}

		shoot_goal_action(GOAL_FOOT);
	}
}

void SoccerPlayer::adjust(void) {
	Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);
	heading_to(goal_vector);
	run_to(goal_vector);
}

//射门意愿:禁区外每半秒判断一次,20%几率,禁区内每半秒判断一次,50%几率,25米外的射门算远射
bool SoccerPlayer::has_shoot_goal_will(double distance_to_goal) {
	return true;
	double value = RAND_DBL;
	int time_scale = this->get_match()->time_scale();
	if (time_scale % 2 == 0) {
		if (this->get_pos().x < B_FORBIDDEN_AREA_X) {
			if (value < 0.1) {
				return true;
			}
		}

		if (this->get_pos().x > B_FORBIDDEN_AREA_X && this->get_pos().x
				<= B_GOAL_AREA_X) {
			if (value < 0.2) {
				return true;
			}
		}
	}

	if (this->get_pos().x > B_GOAL_AREA_X) {
		return true;
	}

	return false;
}

//TODO 关注球的意愿
bool SoccerPlayer::has_mark_ball_will(void) {
	if (time(NULL) % 2 == 1) {
		return true;
	}

	return false;
}

//TODO 是否有block人的意愿
bool SoccerPlayer::has_block_player_will(void) {
	_blockwill = 0.055 + this->_attr[ATT_DEFEND] * 0.0005;
	if ((RAND_INT % 100) < _blockwill) {
		_blockwill = 0.;
		return true;
	}

	_blockwill += 0.0005;
	return false;
	/*	int rst = this->get_team()->check_position(this->get_formation_pos());

	 int index = rand() % 5 + 1;
	 unsigned int rand = (unsigned int)(this->_attr[PHY_STR] / 5  + index);
	 if (rst == 1)
	 {
	 rand = (int)(rand / 3.5);
	 }
	 else if (rst == 2)
	 {
	 rand = (int)(rand / 1.7);
	 }
	 else
	 {
	 rand = rand * 2;
	 }

	 if ((RAND_INT % 100) < rand)
	 {
	 return true;
	 }

	 return false;
	 */
}

void SoccerPlayer::shoot_goal_action(int goal_typ) {
	Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
	set_state( NULL);

	_team->_controlling_player = NULL;
	_match->get_ball()->set_owner(NULL);

	Vector2D shoot_target = goal_vector;
	const PassReferItem &item = pass_refer_get((int) get_pos().distance(
			shoot_target));
	BallTelegram *ball_msg = new BallTelegram(get_id(),
			_match->get_ball()->get_id(), TELE_BALL_GOAL_FLY);

	ball_msg->heading = shoot_target - get_pos();
	ball_msg->heading.normalize();
	ball_msg->speed = item.speed_init;
	_match->get_ball()->set_target_vec(shoot_target);

	_match->notify(ball_msg);

	_match->set_round_end(_union_pid, 0, _uid);
	this->get_team()->add_team_score();
	this->modifer_score(2);
	//根据射门的部位，随机进球的类型
	int goal_dir = 1;
	if(goal_typ == GOAL_FOOT){
		goal_dir = RAND_INT%5 + 1;
	}else{
		goal_dir = 6+ RAND_INT%4;
	}

	_match->set_event_frames(get_team()->get_team_cid(),get_union_pid(), 0, goal_dir);
	MATCH_BREAK_NEW(this, this, ActionItem::GOAL, END_GOAL, goal_typ, N_MIDDLE_KICK, 0);
}

void SoccerPlayer::pass_to_supporter(const RegionSet &target_regions,
		bool is_quick_pass) {
	pass(target_regions, _team->_supporting_player, is_quick_pass);
}

void SoccerPlayer::force_cross_to_supporter(const RegionSet &target_regions) {
	if (!(is_approach())) {
		return;
	}
	this->force_cross(target_regions, _team->_supporting_player);
}

void SoccerPlayer::cross_to_supporter(const RegionSet &target_regions) {
	this->cross(target_regions, _team->_supporting_player);
}

//设置球的路线
void SoccerPlayer::set_ball_goal_vector(int tmp) {
	int x = (int) (PITCH_WIDTH - OUTSIDE_WIDTH);
	int y = (int) (PITCH_HEIGHT / 2);
	int t_rand = rand() % (int) (GOAL_WIDTH / 2);

	switch (tmp) {
	case SHOT_HEAD_FAIL_GK_SAVE: //门将扑住头球射门	6		球门前	1前锋，1门将，1后卫
	case SHOT_HEAD_FAIL_GK_PUSH: //门将扑出头球射门	7		球门前	1前锋，1门将，1后卫
	case SHOT_HEAD_FAIL_GK_PUSH_OUTSIDE: //门将扑出头球射门，出底线	8		球门前	1前锋，1门将，1后卫
	case SHOT_FOOT_FAIL_GK_SAVE: //门将扑住用脚射门	9		球门前	1前锋，1门将，1后卫
	case SHOT_FOOT_FAIL_GK_PUSH: //门将扑出用脚射门	10		球门前	1前锋，1门将，1后卫
	case SHOT_FOOT_FAIL_GK_PUSH_OUTSIDE: //门将扑出用脚射门，出底线	11		球门前	1前锋，1门将，1后卫
	case SHOT_PENALTY_FAIL_GK_SAVE: //门将扑住点球	12		点球点	1前锋，1门将
	case SHOT_PENALTY_FAIL_GK_PUSH: //门将扑出点球	13		点球点	1前锋，1门将
	case SHOT_DIRECT_FREE_KICK_FAIL_GK_SAVE: //门将扑住任意球	14		禁区外	1前锋，1门将，人墙
	case SHOT_DIRECT_FREE_KICK_FAIL_GK_PUSH: //门将扑出任意球	15		禁区外	1前锋，1门将，人墙
	{
		if (rand() % 100 >= 50) {
			t_rand = t_rand * -1;
		}
		y = (int) (PITCH_HEIGHT / 2 + t_rand);
	}
		break;
	case SHOT_PENALTY_FORWARD_OUTTARGET: //点球前锋射门偏出	16		点球点	1前锋，1门将
	case SHOT_PENALTY_FORWARD_CROSSBAR: //点球前锋射中门楣	17		点球点	1前锋，1门将
	case SHOT_PENALTY_FORWARD_GOALPOST: //点球前锋射中门柱	18		点球点	1前锋，1门将
	{
		y = (int) (PITCH_HEIGHT / 2)
				- (GOAL_WIDTH / 2 + (2.5 * METER_TO_POINT));
		if (rand() % 100 >= 50) {
			y = (int) (PITCH_HEIGHT / 2) + (GOAL_WIDTH / 2 + (2.5
					* METER_TO_POINT));
		}
	}
		break;
	case SHOT_DIRECT_FREE_KICK_FORWARD_OUTTARGET: //直接任意球前锋射门偏出	19		禁区外	1前锋，1门将，人墙
	case SHOT_DIRECT_FREE_KICK_FORWARD_CROSSBAR: //直接任意球前锋射中门楣	20		禁区外	1前锋，1门将，人墙
	case SHOT_DIRECT_FREE_KICK_FORWARD_GOALPOST: //直接任意球前锋射中门柱	21		禁区外	1前锋，1门将，人墙
	case SHOT_FORWARD_OUTTARGET: //前锋射门偏出	22		球门前	1前锋，1门将，1后卫
	case SHOT_FORWARD_CROSSBAR: //前锋射中门楣	23		球门前	1前锋，1门将，1后卫
	case SHOT_FORWARD_GOALPOST: //前锋射中门柱	24		球门前	1前锋，1门将，1后卫
	case SHOT_DIRECT_FREE_KICK_WALL: //前锋任意球打人墙	25		禁区外	1前锋，1门将，人墙
	case SHOT_DEFENDER_INTERUPT: //被后卫挡出底线	26		球门前	1前锋，1门将，1后卫
	case SHOT_DEFENDER_INTERUPT_OUTSIDE: //被后卫挡出，未出界	27		球门前	1前锋，1门将，1后卫
	{
		if (rand() % 100 >= 50) {
			t_rand = (int) ((t_rand + 0.5 * METER_TO_POINT) * -1);
		}
		y = (int) (PITCH_HEIGHT / 2 + t_rand);
	}
		break;
	case GOAL_FOOT:
	case GOAL_HEAD:
	case GOAL_PENALTY: //点球进球
	case GOAL_DIRECT_FREE_KICK: //直接任意球进球
	{
		if (rand() % 100 >= 50) {
			t_rand = t_rand * -1;
		}
		y = (int) (PITCH_HEIGHT / 2 + t_rand);
	}
		break;
	default: {

	}
		break;
	}

	int rand_index = RAND_INT % 2;
	y = 0;
	if (rand_index == 0) {
		y = PITCH_HEIGHT / 2 - 15 * METER_TO_POINT;
	} else {
		y = PITCH_HEIGHT / 2 + 15 * METER_TO_POINT;
	}
	x = PITCH_WIDTH;
	Vector2D goal_vector(x, y);
	set_state( NULL);
	_team->_controlling_player = NULL;
	_match->get_ball()->set_owner(NULL);

	BallTelegram *ball_msg = new BallTelegram(get_id(),
			_match->get_ball()->get_id(), TELE_BALL_KICK);

	ball_msg->heading = goal_vector - get_pos();
	ball_msg->heading.normalize();
	ball_msg->speed = 50;
	_match->notify(ball_msg);
}

void SoccerPlayer::cornor_ball(void) // 角球
{
	double soccer_a = 0;//_attr[ATT_FINISH] / 2 + _attr[MENTAL_CONS] / 2 + rand() % 300;
	double soccer_gk = 0;//this->_match->get_defend_team()->_gk_attr[GK_SAVE_STOP] / 2 + this->_match->get_defend_team()->_gk_attr[GK_TEMP_ECCENT] / 2 + rand() % 100;

	int total_score = this->get_team()->get_team_scroe();
	if (total_score >= 8) {
		_match->get_defend_team()->_gk_player->modifer_score(0.4);
		this->modifer_score(-0.4);
		_match->set_round_end(_match->get_defend_team()->_gk_pid, _union_pid,
				_uid);
		uint sum_typ = 0; // 被扑出的类型
		sum_typ = RAND_ARRAY(2
				, SHOT_FOOT_FAIL_GK_SAVE
				, SHOT_FOOT_FAIL_GK_PUSH);
		this->_move_status = PS_SHOOT;
		shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
		MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
		return;
	}

	if (soccer_gk > soccer_a) {
		int rand = RAND_INT % 100;
		if (rand <= 40) { //完成，被成功扑救了
			uint sum_typ = 0; // 扑救类型
			sum_typ
					= RAND_ARRAY(2, SHOT_HEAD_FAIL_GK_SAVE, SHOT_HEAD_FAIL_GK_PUSH);
			MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
			shoot_but_gk_keep(this->_match->get_defend_team()->get_gk_player()->get_union_pid());
		} else { //射偏了
			uint sum_typ = 0; // 被扑出的类型
			sum_typ
					= RAND_ARRAY(3, SHOT_FORWARD_OUTTARGET, SHOT_FORWARD_CROSSBAR, SHOT_FORWARD_GOALPOST);
			MATCH_BREAK_NEW(this, this, ActionItem::SHOOT_OUTSIDE, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
			shoot_but_miss();
		}
	} else {
		shoot_goal_action(GOAL_HEAD);
	}
}

bool SoccerPlayer::is_ending(int nu) {
	if (_match->get_fake_shoot_ending() > 0) {
		return false;
	}

	_match->set_fake_shoot_ending(nu);
	return true;
}

void SoccerPlayer::force_run_to_ball(void) {
	Vector2D target = _match->get_ball()->get_pos();
	Vector2D target2 = this->get_pos();

	if (target != target2) {
		run_to(target);
	}
}

bool SoccerPlayer::is_approach(void) // 助跑
{
	Vector2D target_ball = _match->get_ball()->get_pos();
	//Vector2D target_player = this->get_pos();
	if (this->get_pos().distance(target_ball)
			> g_game_config.get_player_config("action_radius")) {
		//follow_ball();
		run_to(target_ball, 0.7);
		return false;
	}

	return true;
}

void SoccerPlayer::penalty_ball(void) // 点球
{
	if (!is_approach()) {
		return;
	}

	_match->set_fake_shoot_ending(8);
	//	double soccer_a = _attr[ATT_FINISH] / 2 + _attr[MENTAL_CONS] / 2 + rand() % 300;
	//	double soccer_gk = this->_match->get_defend_team()->_gk_attr[GK_SAVE_STOP] / 2 + this->_match->get_defend_team()->_gk_attr[GK_TEMP_ECCENT] / 2 + rand() % 100;
	Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);
	// 到球门中心点的距离
	double distance_to_goal = get_pos().distance(goal_vector);
	bool b_gk = calc_score_compare(this,
			this->_match->get_defend_team()->get_gk_player(),
			SCORE_SHOOT_AT_GOAL_GK, distance_to_goal);


	if (!b_gk) {
		//this->_match->update_compare_log(SCORE_SHOOT_AT_GOAL_GK,_union_pid,_match->get_defend_team()->_gk_player->get_union_pid(),false);
		int rand = RAND_INT % 100;
		if (rand <= 40) {
			// 完成，被守门员成功防守 被成功扑救了
			_match->get_defend_team()->_gk_player->modifer_score(0.4);

			this->modifer_score(-0.4);
			uint sum_typ = 0; // 扑救类型
			sum_typ = RAND_ARRAY(2
					, SHOT_PENALTY_FAIL_GK_SAVE
					, SHOT_PENALTY_FAIL_GK_PUSH);

			MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
			shoot_but_gk_keep(_match->get_defend_team()->_gk_player->get_union_pid());
		} else {
			uint sum_typ = 0;
			sum_typ = RAND_ARRAY(3
					, SHOT_PENALTY_FORWARD_OUTTARGET
					, SHOT_PENALTY_FORWARD_CROSSBAR
					, SHOT_PENALTY_FORWARD_GOALPOST);

			MATCH_BREAK_NEW(this, this, ActionItem::SHOOT_OUTSIDE, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
			shoot_but_miss();
		}
	} else {
		shoot_goal_action(GOAL_FOOT);
	}
}

void SoccerPlayer::free_ball(void) // 任意球
{
	LOG(INFO) << "free_ball";
	if (!is_approach()) {
		return;
	}
	int total_score = this->get_team()->get_team_scroe();
	if (total_score >= 8) {
		_match->get_defend_team()->_gk_player->modifer_score(0.4);
		this->modifer_score(-0.4);
		_match->set_round_end(_match->get_defend_team()->_gk_pid, _union_pid,
				_uid);
		uint sum_typ = 0; // 被扑出的类型
		sum_typ = RAND_ARRAY(2
				, SHOT_FOOT_FAIL_GK_SAVE
				, SHOT_FOOT_FAIL_GK_PUSH);
		this->_move_status = PS_SHOOT;
		shoot_but_gk_keep(_match->get_defend_team()->_gk_pid);
		MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK, C_NULL);
		return;
	}

	_match->set_fake_shoot_ending(10);
	bool rst = calc_score_compare(this,
			_match->get_defend_team()->get_gk_player(), SCORE_FREE_BALL);

	if (!rst) { //防守方赢，30%几率被GK扑住，35%几率射偏，35%几率打人墙弹出
		this->_match->update_compare_log(SCORE_FREE_BALL,_union_pid,_match->get_defend_team()->_gk_player->get_union_pid(),rst);
		int rand = RAND_INT % 100;
		if (rand <= 30) { //完成，被成功扑救了
			//			_match->get_defend_team()->add_action(1, ActionItem::GOAL_FREE);
			_match->set_round_end(_match->get_defend_team()->_gk_pid,
					_union_pid, _uid);
			uint sum_typ = 0; // 扑救类型
			sum_typ = RAND_ARRAY(2
					, SHOT_DIRECT_FREE_KICK_FAIL_GK_SAVE
					, SHOT_DIRECT_FREE_KICK_FAIL_GK_PUSH);

			MATCH_BREAK_NEW(this, this, ActionItem::SHOOT, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK,C_NULL);
			shoot_but_miss();
		} else if (rand <= 65) // 35%几率射偏
		{ //射偏了
			uint sum_typ = 0; // 射偏类型
			sum_typ = RAND_ARRAY(3
					, SHOT_DIRECT_FREE_KICK_FORWARD_OUTTARGET
					, SHOT_DIRECT_FREE_KICK_FORWARD_CROSSBAR
					, SHOT_DIRECT_FREE_KICK_FORWARD_GOALPOST);

			MATCH_BREAK_NEW(this, this, ActionItem::BEBREAK, END_GOAL_FAIL, sum_typ, N_NORMAL_KICK,C_NULL);
			shoot_but_miss();
		} else // 打人墙弹出
		{
			MATCH_BREAK_NEW(this, this, ActionItem::BEBREAK, END_GOAL_FAIL, SHOT_DIRECT_FREE_KICK_WALL,N_NORMAL_KICK,C_NULL);
			shoot_but_miss();
		}
	} else {
		shoot_goal_action(GOAL_FOOT);
	}
}

void SoccerPlayer::go_home(void) {
	if (!this->avoid_offside()) {
		if (is_at_pos(_home.center())) {
			//TODO fix heading
			//heading_to(_match->get_ball()->get_pos());
			set_speed(0);
		} else {
			run_to(_home.center());
		}
	}
}

bool SoccerPlayer::avoid_offside() {
	SoccerPlayer* player = this->_match->get_def_team_closest_to_offline();
	if (this->get_pos().x > (player->get_pos().x)) {
		this->set_state(OffSideState::alloc());
		return true;
	}
	return false;
}

void SoccerPlayer::def_go_home(void) {
	double distance = this->get_pos().distance(_home.center());
	if (distance < 30) {
		//TODO fix heading
		//heading_to(_match->get_ball()->get_pos());
		set_speed(0);
		set_state(AreaDefendState::alloc());
	} else {
		run_to(_home.center());
	}
}

void SoccerPlayer::set_home(const SoccerRegion &region) {
	_home = region;
}

SoccerRegion SoccerPlayer::get_home(void) const {
	return _home;
}

void SoccerPlayer::modifer_home(double x, double y) {
	_home.x1 += x;
	_home.x2 += x;
	_home.y1 += y;
	_home.y2 += y;
}

void SoccerPlayer::set_mindArea(const SoccerRegion &region) {
	this->_mindArea = region;
}

void SoccerPlayer::set_markArea(const SoccerRegion &region) {
	this->_markArea = region;
}

void SoccerPlayer::set_mindPlayer(int mindplayer_id) {
	/* 如果是无主球，经过该球员的区域一定去抢断。 */
	SoccerBall *pBall = _match->get_ball();
	if (is_ball_in_action_radius()) {
		if ((pBall->get_owner() == NULL)
				&& (_match->get_ball()->get_motion_type() != SoccerBall::CROSS)
				&& (_match->get_attack_team()->isInGodMode() != true)) {
			double cmp_rst = 0.1;
			if (cmp_rst > RAND_DBL) {
				MATCH_BREAK_NEW(this, this, ActionItem::BEBREAK, END_BREAK, BREAK_INTERUPT_RECV_PASS, N_NORMAL_KICK, C_NULL);
				_match->set_event_frames(this->get_uid(),
						this->get_union_pid(), 0, 45);
			} else {
				this->set_state(FrozenState::alloc());
			}

			return;
		}
	}

	SoccerMatch *_match = this->_match;
	SoccerPlayer *pMindplayer = NULL;
	pMindplayer = _match->get_player_by_entityId(mindplayer_id);

	Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
	double tmp = pMindplayer->get_pos().distance(goal_vector);
	SoccerPlayer *t_pPlayer = NULL;

	SoccerTeam *pTeam = _match->get_attack_team();
	for (int i = 0; i < 10; ++i) {
		SoccerPlayer *pPlayer = pTeam->get_player_on_pitch(i);
		if (pPlayer->get_BeMindedPlayer() == NULL) {
			if (this->_mindArea.in(pPlayer->get_pos())) {
				double distance_to_goal = pPlayer->get_pos().distance(
						goal_vector);
				if (distance_to_goal + 2 * METER_TO_POINT < tmp) {
					t_pPlayer = pPlayer;
					tmp = distance_to_goal;
				}
			}
		}
	}

	if (t_pPlayer != NULL) {
		t_pPlayer->set_BeMindedPlayer(this);
		MindOnPlayerState *pState = MindOnPlayerState::alloc();
		pState->tagert_id = t_pPlayer->get_id();
		set_state(pState);
		return;
	}

	double dis = this->get_pos().distance(_home.center());
	int pos = _team->check_position(get_formation_pos());
	if (pBall->get_pos().x < PITCH_WIDTH / 2) /* 没过中线 */
	{
		if (pos == 1 || pos == 2) /* 前锋 中场 */
		{
			/* 出了home区域就回去 */
			if (dis > g_game_config.get_player_config("dis_go_home")) {
				// 策划
				set_state(DefGoHomeState::alloc());
			} else {
				follow_player(pMindplayer);
			}
			return;
		} else /* 后卫 */
		{
			keep_line(); /* 保持防线 */
		}
	} else /* 过中线 */
	{
		if (pos == 1 || pos == 2) /* 前锋 中场 */
		{
			if (pMindplayer->get_pos().x > B_FORBIDDEN_AREA_X) /* x是否 到后卫防线 */
			{
				keep_line(); /* 保持防线 */
			} else {
				follow_player(pMindplayer);
			}
		} else /* 后卫 */
		{
			if (pMindplayer->get_pos().x > B_FORBIDDEN_AREA_X) /* 是 在危险区域 */
			{
				if (dis > g_game_config.get_player_config("dis_go_home")) {
					// 策划
					set_state(DefGoHomeState::alloc());
				} else {
					keep_line(); /* 保持防线 */
				}
			} else {
				follow_player(pMindplayer);
			}
		}
	}
}

void SoccerPlayer::set_mindBall(int mindplayer_id) {
	SoccerBall *pBall = this->_match->get_ball();
	Vector2D ballVector = this->get_pos() - pBall->get_pos();
	ballVector.normalize();
	this->set_heading(ballVector);

	follow_ball();

	/* 球是否在mind区域 */
	if (!check_ball_enter_mindarea()) {
		set_state(AreaDefendState::alloc());
		return;
	}

	if (_team->check_position(get_formation_pos()) == 1) /* 前锋 */
	{
		/* 球是否在action区域 */
		if (is_ball_in_action_radius()
				&& !(_match->get_ball()->get_motion_type() == SoccerBall::CROSS)) {
			ground_tackle();
		}
		return;
	} else /* 中场 后卫 */
	{
		/* 球是否在action区域 */
		if ((this->get_pos().distance(_match->get_ball()->get_pos()) < 8 * METER_TO_POINT)
				&& !(_match->get_ball()->get_motion_type() == SoccerBall::CROSS)) {
			ground_tackle();
			return;
		}
		//def_go_home();
		/*		if (mindplayer_id != -1) {
		 keep_distance(mindplayer_id); // 保持距离
		 }*/
	}

}

/* 盯球状态 */
void SoccerPlayer::set_markball(void) {
	_match->set_dpid(this->get_union_pid());
	//1.盯防,保护
	SoccerBall* pBall = _match->get_ball();
	//set_heading(pBall->get_head_vec());

	//3.监视球是否离开mark区域
	if (!_markArea.in(pBall->get_pos())) {
		set_state(MindOnBallState::alloc());
		return;
	}

	double dis = get_pos().distance(_home.center());
	if (dis > g_game_config.get_player_config("dis_go_home")) {
		set_state(AreaDefendState::alloc());
		return;
	}

	if (pBall->get_owner() != NULL) {
		//2.监视球是否进入action区域
		if (!(_match->get_ball()->get_motion_type() == SoccerBall::CROSS)) {
			if (is_ball_in_action_radius()) {
				if (has_tackle_will()) {
					TackleSlideCDState *pState = TackleSlideCDState::alloc();
					if (has_slide_will()) {
						pState->_typ = 2;
					} else {
						pState->_typ = 1;
					}
					set_state(pState);
				}
				return;
			}
		}

		follow_ball();
	} else {
		if (pBall->get_speed() < 5.) {
			follow_ball();
		} else {
			step_back();
		}
	}
}

//跑回防守位置状态
void SoccerPlayer::back_defend(void) {
	if (is_at_pos(this->get_home().center())) {
		set_state(AreaDefendState::alloc());
	} else {
		def_go_home();
	}
}

bool SoccerPlayer::is_in_home_pos(void) {
	return this->get_home().in(this->get_pos());
}

bool SoccerPlayer::is_team(SoccerTeam *team) {
	return team == _team;
}

void SoccerPlayer::init_pos(void) {
	set_pos(_home.center());
}

SoccerPlayer* SoccerPlayer::get_minding_player() {
	return this->get_op_team()->_minding_player;
}

void SoccerPlayer::minding(void) {
	_team->_minding_player = this;
}

void SoccerPlayer::unminding(void) {
	_team->_minding_player = NULL;
}

void SoccerPlayer::marking(void) {
	_team->_marking_player = this;
}

void SoccerPlayer::unmarking(void) {
	_team->_marking_player = NULL;
}

void SoccerPlayer::follow_ball(double speed_per) {
	//VLOG(1) << "player id" << this->get_id() << "," << this->get_pos().x << "," << this->get_pos().y;
	//VLOG(1) << "_markArea pos" << _markArea.x1 << "," << _markArea.y1 << "," << _markArea.x2 << "," << _markArea.y2;
	run_to(_match->get_ball()->get_pos(), speed_per);
}

void SoccerPlayer::follow_player(SoccerPlayer *pPlayer) {
	if (pPlayer == NULL) {
		set_state(DefGoHomeState::alloc());
		return;
	}

	double distance = keep_distance_to_player;//g_game_config.get_player_config("keep_distance_to_player");
	Vector2D tmpVec = pPlayer->get_pos();
	if (tmpVec.y > get_pos().y) {
		tmpVec.y = tmpVec.y - distance;
	} else {
		tmpVec.y = tmpVec.y + distance;
	}
	tmpVec.x -= distance;
	run_to(tmpVec);
}

SoccerRegion SoccerPlayer::get_mind_area(void) {
	return this->_mindArea;
}

SoccerRegion SoccerPlayer::get_mark_area(void) {
	return this->_markArea;
}

SoccerPlayer *SoccerPlayer::can_mind_other_but(SoccerPlayer *Player) {
	SoccerTeam *pTeam = _match->get_attack_team();
	for (int i = 0; i < 10; ++i) {
		SoccerPlayer *pPlayer = pTeam->get_player_on_pitch(i);
		if ((Player->get_id() != pPlayer->get_id())
				&& (pPlayer->get_BeMindedPlayer() == NULL)) {
			if (_mindArea.in(pPlayer->get_pos())) {
				pPlayer->set_BeMindedPlayer(this);
				return pPlayer;
			}
		}
	}

	return NULL;
}

SoccerPlayer *SoccerPlayer::check_attack_player_enter_mindarea(void) {
	/* 找出所有在mind区域没有人盯的离球门中心点最近的 */
	double tmp = 10000;
	SoccerPlayer *t_pPlayer = NULL;

	SoccerTeam *pTeam = _match->get_attack_team();
	for (int i = 0; i < 10; ++i) {
		SoccerPlayer *pPlayer = pTeam->get_player_on_pitch(i);
		if (pPlayer->get_BeMindedPlayer() == NULL) {
			if (this->_mindArea.in(pPlayer->get_pos())) {
				Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
				double distance_to_goal = pPlayer->get_pos().distance(
						goal_vector);
				if (distance_to_goal < tmp) {
					t_pPlayer = pPlayer;
					tmp = distance_to_goal;
				}
			}
		}
	}

	if (t_pPlayer != NULL) {
		t_pPlayer->set_BeMindedPlayer(this);
		return t_pPlayer;
	}

	return NULL;
}

SoccerPlayer *SoccerPlayer::check_attack_player_enter_mindarea2(void) {
	/* 找出所有在mind区域没有人盯的离球门中心点最近的 */
	double tmp = 10000;
	SoccerPlayer *t_pPlayer = NULL;

	SoccerTeam *pTeam = _match->get_attack_team();
	for (int i = 0; i < 10; ++i) {
		SoccerPlayer *pPlayer = pTeam->get_player_on_pitch(i);
		if (pPlayer->get_BeMindedPlayer() == NULL) {
			if (this->_mindArea.in(pPlayer->get_pos())) {
				Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
				double distance_to_goal = pPlayer->get_pos().distance(
						goal_vector);
				if (distance_to_goal < tmp) {
					t_pPlayer = pPlayer;
					tmp = distance_to_goal;
				}
			}
		}
	}

	if (t_pPlayer != NULL) {
		t_pPlayer->set_BeMindedPlayer(this);
		return t_pPlayer;
	}

	return NULL;
}

bool SoccerPlayer::check_ball_enter_mindarea(void) {
	SoccerBall *pBall = _match->get_ball();
	if (this->_mindArea.in(pBall->get_pos())) {
		return true;
	}

	return false;
}

bool SoccerPlayer::check_ball_enter_markarea(void) {
	SoccerBall *pBall = _match->get_ball();
	if (this->_markArea.in(pBall->get_pos())) {
		return true;
	}

	return false;
}

SoccerPlayer *SoccerPlayer::get_markplayer(void) {
	return this->_pMarkPlayer;
}
bool SoccerPlayer::is_trigger_rp_pr(){
	//double value = RAND_DBL;
	//if(value )
	if(this->_team->get_rp_pr() == 15){
		return true;
	}
	return false;
}

void SoccerPlayer::reset_team_rp_pr(){
	this->_team->reset_rp_pr();
}

double SoccerPlayer::get_team_rp_pr(){
	return this->_team->get_rp_pr();
}

void SoccerPlayer::update_team_rp_pr(double value){
	this->get_team()->update_rp_pr(value);
}

int SoccerPlayer::check_will_use_gk_skill(){
	int rst = this->check_skill_can_use(SCORE_GK_KICK_OFF);
	LOG(INFO)<<"守门员使用技能"<<rst;
	return rst;
}

//开球状态
void SoccerPlayer::parepre_kick_off(void) {
	const Vector2D vec = this->_match->get_goal_vec();
	this->run_to(vec, 0.3);
}

bool SoccerPlayer::in_AirDefendState(void) {
	SoccerBall *pBall = _match->get_ball();

	if ((pBall->get_motion_type() == SoccerBall::CROSS)
			&& (_team->get_air_defend_player() == NULL)) {
		SoccerPlayer *player = _team->choose_air_defend_player(
				pBall->get_target_vec());
		if (player != NULL) {
			AirDefendState *state = AirDefendState::alloc();
			state->_targetVec = pBall->get_target_vec();
			player->set_state(state);
			return true;
		}
	}

	return false;
}

SoccerTeam* SoccerPlayer::get_op_team() {
	if (_match->get_team(1)->get_team_cid() == _team->get_team_cid()) {
		return this->_match->get_team(2);
	} else {
		return this->_match->get_team(1);
	}
}

void SoccerPlayer::area_defend(void) {
	/* 进入防守高空球状态 1 */
	if (in_AirDefendState()) {
		return;
	}

	SoccerBall *pBall = _match->get_ball();
	/* 进入盯球状态 3 */
	if (check_ball_enter_mindarea() /* 球如果进入mind区域 */
	&& _match->get_ball()->get_motion_type() != SoccerBall::CROSS) {
		if (pBall->get_owner() != NULL /* 带球的人 */
		&& this->_team->_minding_player == NULL /* 没有人去mind他 */
		&& this->_team->_air_defend_player == NULL) /* 没有人去防守高球 */
		{
			_match->set_event_frames(this->get_uid(), this->get_union_pid(), 0,
					46);
			MindOnBallState *pState = MindOnBallState::alloc();
			pState->tagert_id = pBall->get_owner()->get_id();
			this->_keep_distance_stage = 1;
			set_state(pState); /* 盯带球的人状态 */
			return;
		} else if ((pBall->get_owner() == NULL) && (pBall->get_speed() < 1)) /* 没有主人的球 ，而且在控制范围之内*/
		{
			if (this->_team->_minding_player == NULL) {
				_match->set_event_frames(this->get_uid(),
						this->get_union_pid(), 0, 46);
				run_to(pBall->get_pos(), 0.6);
				MindOnBallState *pState = MindOnBallState::alloc();
				pState->tagert_id = -1;
				this->_keep_distance_stage = 2;
				set_state(pState); /* 盯带球的人状态 */
			}
		}
	}

	//如果是无主球就安排一个人去追
	if ((pBall->get_owner() == NULL) && (pBall->get_speed() < 1)) {
		SoccerPlayer* closest_to_ball =
				this->get_match()->get_closest_to_ball_def();
		if (closest_to_ball->get_union_pid() == this->get_union_pid()) {
			MindOnBallState *pState = MindOnBallState::alloc();
			pState->tagert_id = -1;
			this->_keep_distance_stage = 2;
			set_state(pState); /* 盯带球的人状态 */
		}
	}

	/* 默认是保持阵型 */
	def_go_home();
}

//被阻挡的函数没有完成,速度减半
void SoccerPlayer::be_blocked(void) {
	double speed = this->get_speed();
	this->set_speed(speed / 2);
}

//重做:体力70%以下时,在防守方进行抢断行为时5%概率受伤,体力60%以下时10%概率,体力50%以下时20%概率受伤
//           确定受伤的情况下:轻伤60%,中伤30%,重伤10%
bool SoccerPlayer::check_injuried(SoccerPlayer* att_player) {
	SoccerTeam* attack_team = att_player->get_team();
	if (attack_team->get_inj_count() > 2) {
		return false;
	}
	double rand_value = RAND_DBL;
	bool is_injureied = false;
	double injure_rate = 0.;
	double speak_effect = 0.;
	if(this->get_team()->get_coach_speak_type() == SPEAK_GENTLEMEN){
		speak_effect = -5.;
	}else if(this->get_team()->get_coach_speak_type() == SPEAK_ATTACK_ATTACK){
		speak_effect = 10.;
	}

	//如果防守方的侵略性比进攻方的要低，就不受伤
	if(this->get_attr(AGGRESSIVE) < att_player->get_attr(STRONG)){
		return false;
	}

	double tmp_value = this->get_attr(AGGRESSIVE)/att_player->get_attr(STRONG);
	tmp_value = min(tmp_value,3.);
	injure_rate = (85. - att_player->get_cond() + speak_effect)*0.01*tmp_value;
	if(injure_rate < 0){
		injure_rate = 0.;
	}else if(injure_rate > 0.4){
		injure_rate = 0.4;
	}
	if(rand_value <= injure_rate){
		is_injureied = true;
	}

	if (is_injureied) {
		LOG(INFO) << att_player->get_union_pid() << "受伤了。。。。。。。";
		rand_value = RAND_DBL;
		if (rand_value <= 0.05) {//重伤
			att_player->set_cond(7);
			att_player->get_team()->add_inj_count();
		} else if (rand_value > 0.05 && rand_value <= 0.30) {//中伤
			att_player->set_cond(8);
			att_player->get_team()->add_inj_count();
		} else if (rand_value > 0.3) {//轻伤
			if(att_player->get_cond() < 15){
				att_player->set_cond(10);
			}else{
				att_player->set_cond(att_player->get_cond() - 5);
			}

		}
		return true;
	}
	return false;

}

void SoccerPlayer::halftime_resume_cond(){
	int cond_add = round(this->get_team()->get_fitness_coach()/10);
	this->_cond += cond_add;
	if(this->_cond > 100){
		this->_cond = 100;
	}
}


//TODO 球员越位,进攻球员向前移动，防守球员向同一水平线移动
void SoccerPlayer::off_side(void) {
	SoccerPlayer *player = this->_match->get_def_team_closest_to_offline();
	Vector2D vec = this->get_pos();
	vec.x = player->get_pos().x + 10;
	this->run_to(vec);
}

void SoccerPlayer::shoot_but_miss(void) {
	Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
	set_state( NULL);

	_team->_controlling_player = NULL;
	_match->get_ball()->set_owner(NULL);

	Vector2D shoot_target = goal_vector;
	//const PassReferItem &item = pass_refer_get((int) get_pos().distance(
	//		shoot_target));
	BallTelegram *ball_msg = new BallTelegram(get_id(),
			_match->get_ball()->get_id(), TELE_BALL_GOAL_FLY);

	ball_msg->heading = shoot_target - get_pos();
	ball_msg->heading.normalize();
	ball_msg->speed = 0;//item.speed_init;
	_match->get_ball()->set_target_vec(shoot_target);
	_match->notify(ball_msg);
	_match->set_round_end(_union_pid, 0, _uid);
	//随机射偏的类型
	int rand_step = RAND_INT%10;
	int miss_typ =0;
	if(rand_step <2){
		miss_typ = RAND_ARRAY(4,10,12,13,16);
	}else{
		miss_typ = RAND_ARRAY(3,11,14,15);
	}

	_match->set_event_frames(this->get_uid(),this->get_union_pid(), 0, miss_typ);
}

void SoccerPlayer::shoot_but_gk_keep(int gk_pid) {
	Vector2D goal_vector(PITCH_WIDTH, PITCH_HEIGHT / 2);
	set_state( NULL);

	_team->_controlling_player = NULL;
	_match->get_ball()->set_owner(NULL);

	Vector2D shoot_target = goal_vector;
	//const PassReferItem &item = pass_refer_get((int) get_pos().distance(
	//		shoot_target));
	BallTelegram *ball_msg = new BallTelegram(get_id(),
			_match->get_ball()->get_id(), TELE_BALL_GOAL_FLY);

	ball_msg->heading = shoot_target - get_pos();
	ball_msg->heading.normalize();
	ball_msg->speed = 0;//item.speed_init;
	_match->get_ball()->set_target_vec(shoot_target);
	_match->notify(ball_msg);
	_match->set_round_end(gk_pid,_union_pid,_uid);
	//随机射偏的类型
	int rand_step = RAND_INT%10;
	int miss_typ = 0;
	if(rand_step < 2){
		//miss_typ = RAND_ARRAY(3,12,13,16);
		miss_typ = RAND_ARRAY(4,10,12,13,16);
	}else{
		miss_typ = RAND_ARRAY(3,11,14,15);
	}
	
	_match->set_event_frames(this->get_uid(),this->get_union_pid(), 0, miss_typ);
}

//计算该球员的进攻指数
double SoccerPlayer::calc_player_att_value(void) {
	return this->_att_value;
}

//计算该球员的防守指数
double SoccerPlayer::calc_player_def_value(void) {
	return this->_def_value;
}

//更新球员的位置
void SoccerPlayer::update_triangle_area() {

	this->triangle.point_a = this->get_pos();
	//this->triangle.point_b = this->
}

SoccerPlayer* SoccerPlayer::check_player_in_front() {
	for (int i = 0; i < 10; i++) {
		SoccerPlayer* player =
				this->get_match()->get_defend_team()->get_player_on_pitch(i);
		if (this->triangle.check_point_in_triangle(player->get_pos())) {
			return player;
		}
	}
	return NULL;
}

int SoccerPlayer::get_player_counts_in_front() {
	int count = 0;
	for (int i = 0; i < 10; i++) {
		SoccerPlayer* player =
				this->get_match()->get_defend_team()->get_player_on_pitch(i);
		if (this->triangle.check_point_in_triangle(player->get_pos())) {
			count++;
		}
	}
	return count;
}

//检测是否有人在他的射门路线上
SoccerPlayer* SoccerPlayer::check_player_in_attack_way() {
	//	double range_to_line = 2*METER_TO_POINT;
	Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);

	double stanrd_area = METER_TO_POINT * this->_distance_to_goal / 2;
	for (int i = 0; i < 10; i++) {
		SoccerPlayer* player =
				this->get_match()->get_defend_team()->get_player_on_pitch(i);
		if (this->get_pos().x < player->get_pos().x) {
			Triangle tr;
			double player_tmp_area = tr.TriangleGetArea(goal_vector,
					this->get_pos(), player->get_pos());
			if (player_tmp_area > stanrd_area) {
				return player;
			}
		}
	}

	return NULL;
}

//变线躲避来的球员,需要测试
Vector2D SoccerPlayer::change_dir_tmp(SoccerPlayer* playerInFront) {
	Vector2D tmp_dir = playerInFront->get_pos();
	double distance = this->get_pos().distance(playerInFront->get_pos());
	double a =
			asin((playerInFront->get_pos().y - this->get_pos().y) / distance)
					+ M_PI / 4;
	tmp_dir.x = 3 * METER_TO_POINT * cos(a) + this->get_pos().x;
	tmp_dir.y = 3 * METER_TO_POINT * sin(a) + this->get_pos().y;
	this->_tmp_dirbble_cd = 3;
	this->_tmp_dirblle_target_vec = tmp_dir;
	return tmp_dir;
}

bool SoccerPlayer::natrue_trackle_ball(void) {
	/* 如果是无主球，经过该球员的区域一定去抢断。 */
	//自然反映去断球
	//	double distance_to_ball = this->get_pos().distance(_match->get_ball()->get_pos());
	double cmp_rst = 0.1;
	if (cmp_rst > RAND_DBL) {
		MATCH_BREAK_NEW(this, this, ActionItem::BEBREAK, END_BREAK, BREAK_INTERUPT_RECV_PASS, N_NORMAL_KICK, C_NULL);
		_match->set_event_frames(this->get_uid(), this->get_union_pid(), 0, 45);
		return true;
	} else {
		this->set_state(FrozenState::alloc());
		return false;
	}
}

Vector2D SoccerPlayer::calc_pass_real_point(const Vector2D& target_point) {
	Vector2D real_point;
	return target_point;
}

void SoccerPlayer::air_defend(Vector2D &vec) {
	bool is_in_god_mod = this->_match->get_attack_team()->isInGodMode();

	SoccerBall *pBall = this->_match->get_ball();
	if (is_ball_in_action_radius()) /* Action */
	{
		if (pBall->get_owner() == NULL) {
			//			double distance_to_ball = this->get_pos().distance(pBall->get_pos());
			double cmp_rst = 0.1;
			if ((cmp_rst > RAND_DBL) && (!is_in_god_mod)) {
				MATCH_BREAK_NEW(this, this, ActionItem::BEBREAK, END_BREAK, BREAK_INTERUPT_RECV_PASS, N_NORMAL_KICK, C_NULL);
				_match->set_event_frames(this->get_uid(),
						this->get_union_pid(), 0, 45);
			} else {
				FrozenState *state = FrozenState::alloc();
				state->_cd = 10;
				this->set_state(state);
			}

			return;
		}
	}

	if (pBall->get_owner() != NULL) {
		if(pBall->get_owner()->get_pos().distance(this->get_pos()) < 5*METER_TO_POINT){
			bool cmp_rst;
			cmp_rst = calc_score_compare(pBall->get_owner(), this,
					SCORE_AIR_DEF_ATT);

			if ((!cmp_rst) && (!is_in_god_mod)) {
				this->_match->update_compare_log(SCORE_AIR_DEF_ATT,pBall->get_owner()->get_union_pid(),_union_pid,cmp_rst);
				if (this->check_injuried(pBall->get_owner())) {
					MATCH_BREAK_NEW(this,pBall->get_owner(), ActionItem::BEBREAK, END_FOULED, END_INJURED, N_NORMAL_KICK, C_INJURED);
					int typ;
					if (pBall->get_owner()->get_cond() == 9) {
						typ = 68;
					} else if (pBall->get_owner()->get_cond() == 8) {
						typ = 69;
					} else if (pBall->get_owner()->get_cond() == 7) {
						typ = 70;
					}
					_match->set_event_frames(this->get_uid(),
							this->get_union_pid(),
							pBall->get_owner()->get_union_pid(), typ);
					//判断是否给任意球
					bool will_free = this->check_will_be_free_ball(
							pBall->get_owner());
					uint sum_typ = 0; // 犯规类型
					sum_typ = RAND_ARRAY(5
							, OUT_RESTRICTED_HAND_BALL
							, FOUL_PULL_SHIRT
							, OUT_RESTRICTED_FOUL_SLIDE
							, OUT_RESTRICTED_FOUL_ELBOW
							, OUT_RESTRICTED_FOUL_CHARGE);
					if (will_free) {
						MATCH_BREAK_NEW(this, pBall->get_owner(), ActionItem::BEBREAK, END_FOULED, sum_typ, N_FREE_KICK, 0);
					} else {
						player_break_ok(this, pBall->get_owner(), BREAK_TACKLE_PASS);
					}
					return;
				} else {
					player_break_ok(this, pBall->get_owner(),
							BREAK_INTERUPT_RECV_PASS);//断球成功
					_match->set_event_frames(this->get_uid(),
							this->get_union_pid(),
							pBall->get_owner()->get_union_pid(), 45);
					return;
				}
			}
			FrozenState *frone_state = FrozenState::alloc();
			frone_state->_cd = 10;//
			this->set_state(frone_state);
			return;
		}
	}

	run_to(vec, 0.8);
}

void SoccerPlayer::pass_defend(Vector2D &vec) {
	//bool is_in_god_mod = this->_match->get_attack_team()->isInGodMode();
	SoccerBall *pBall = this->_match->get_ball();
	if (is_ball_in_action_radius()) /* Action */
	{
		if (pBall->get_owner() == NULL) {
			//			double distance_to_ball = this->get_pos().distance(pBall->get_pos());
			double cmp_rst = 0.1;
			if (cmp_rst > RAND_DBL) {
				MATCH_BREAK_NEW(this, this, ActionItem::BEBREAK, END_BREAK, BREAK_INTERUPT_RECV_PASS, N_NORMAL_KICK, C_NULL);
				_match->set_event_frames(this->get_uid(),
						this->get_union_pid(), 0, 45);
			} else {
				FrozenState *state = FrozenState::alloc();
				state->_cd = 6;
				this->set_state(state);
			}
			return;
		}
	}

	/*if (pBall->get_owner() != NULL) {
		bool cmp_rst;
		cmp_rst = calc_score_compare(pBall->get_owner(), this,
				SCORE_RUN_WITH_BALL_INTERCEPT);

		if ((!cmp_rst) && (!is_in_god_mod)) {
			this->_match->update_compare_log(SCORE_RUN_WITH_BALL_INTERCEPT,pBall->get_owner()->get_union_pid(),_union_pid,cmp_rst);
			if (this->check_injuried(pBall->get_owner())) {
				int typ = 0;
				if (pBall->get_owner()->get_cond() == 9) {
					typ = 68;
				} else if (pBall->get_owner()->get_cond() == 8) {
					typ = 69;
				} else if (pBall->get_owner()->get_cond() == 7) {
					typ = 70;
				}
				_match->set_event_frames(this->get_uid(),
						this->get_union_pid(),
						pBall->get_owner()->get_union_pid(), typ);
				//判断是否给任意球
				bool rst = this->check_will_be_free_ball(pBall->get_owner());
				LOG(INFO)<<"test....";
				uint sum_typ = 0; // 犯规类型
				sum_typ = RAND_ARRAY(5
						, OUT_RESTRICTED_HAND_BALL
						, FOUL_PULL_SHIRT
						, OUT_RESTRICTED_FOUL_SLIDE
						, OUT_RESTRICTED_FOUL_ELBOW
						, OUT_RESTRICTED_FOUL_CHARGE);
				if (rst) {
					MATCH_BREAK_NEW(this, pBall->get_owner(), ActionItem::BEBREAK, END_FOULED, sum_typ, N_FREE_KICK, 0);
				} else {
					player_break_ok(this, pBall->get_owner(), BREAK_TACKLE_PASS);
				}
			} else {
				player_break_ok(this, pBall->get_owner(),
						BREAK_INTERUPT_RECV_PASS);//断球成功
				_match->set_event_frames(this->get_uid(),
						this->get_union_pid(),
						pBall->get_owner()->get_union_pid(), 45);
				return;
			}
		}
		FrozenState *frone_state = FrozenState::alloc();
		frone_state->_cd = 6;//
		this->set_state(frone_state);
	} else */
	//{
		run_to(vec, 0.8);
		if(vec.distance(this->get_pos()) < (2*METER_TO_POINT)){
			this->set_state(AreaDefendState::alloc());
		//}

	}
}

//检查是否有技能可以使用
int SoccerPlayer::check_skill_can_use(int event_type) {
	this->set_last_skill_used(0);
	SoccerPlayerSkill* player_skill = (this->get_skills());
	SkillEventRef* skill_can_use =
			SkillAndEventRefManager::GetInstance()->get_all_skill_can_use_list(
					event_type);
	std::vector<PlayerSkill*> skill_list;
	for (int i = 0; i < player_skill->get_skill_count(); i++) {
		int skill_status = skill_can_use->check_skill(
				player_skill->operator [](i).skill_id);
		if (skill_status != -1) {
			if((this->attack_or_defend() == skill_status) || (skill_status == 3)){
				skill_list.push_back(&(player_skill->operator [](i)));
			}
		}
	}

	if (skill_list.size() <= 0) {
		return -1;
	}
	int rand_value = RAND_INT % 100;
	std::vector<PlayerSkill*>::iterator itr = skill_list.begin();
	if(itr != skill_list.end()){//判断触发不触发
		if((*itr)->skill_chance < rand_value){
			return -1;
		}
	}

	int size = skill_list.size();
	int rand_index = RAND_INT%size;
	PlayerSkill* skill = skill_list[rand_index];

	//使用该技能
	use_skill(skill->skill_id);
	return skill->skill_id;
}

void SoccerPlayer::use_skill(int skill_id) {
	PlayerSkill* skill = this->get_skills()->get_skill(skill_id);
	int skill_level = skill->skill_level;
	if (skill == NULL) {
		return;
	}
	this->_match->add_skill_frames(skill_id, this->get_union_pid());
	SoccerAttribute& plus = this->get_skill_plus_attr();
	//SoccerAttribute& attr = this->get_attr();
	switch (skill_id) {
	case 1://	"罗宾逊的开球",不會用到的比較大小
	{
	//	plus[KICKOFF] = attr[KICKOFF] * 0.1 * skill_level;
	}
		break;
	case 2://	"鱼跃扑救"
	{
		plus[ATT_GK_SAVE] = 2 * skill_level;
	}
		break;
	case 3://	"卡恩的怒吼"
	{
		plus[ATT_GK_COM_DEF] = 2 * skill_level;
	}
		break;
	case 5://	"宇宙队传球"
	{
		plus[ATT_PASS] = 2 * skill_level;
	}
		break;
	case 7://	"卡纳瓦罗的断球"
	{
		plus[ATT_DEFEND] = 2 * skill_level;
	}
		break;
	case 9://	"圆月弯刀"
	{
		plus[FREE_KICK] = 2 * skill_level;
	}
		break;
	case 11://	"魔兽"
	{
		plus[STRONG] = 2 * skill_level;
	}
		break;
	case 13://	"外脚背抽射"
	{
		plus[LONG_RANGE] = 2 * skill_level;
	}
		break;
	case 15://	"里克尔梅（视野）"
	{
		plus[VISION] = 2 * skill_level;
	}
		break;
	case 16://	"鱼跃冲顶"
	{
		plus[HEADER_ACCURACY] = 2 * skill_level;
	}
		break;
	case 17://	"罗马里奥（弹跳）"
	{
		plus[BOUNCE] = 2 * skill_level;
	}
	break;
	case 28://雜耍彈射
	{
		plus[ATT_SHOOT] = 2 * skill_level;
	}
		break;
	case 36://克鲁伊夫盘带
	{
		plus[ATT_BALL_CTRL] = 2 * skill_level;
	}
		break;
	case 43:
	{
		plus[PENALTY] = 2 * skill_level;
	}
		break;
	case 61://	积极跑动"
	{ 
		plus[MOVES] = 2 * skill_level;
	}
		break;
	case 71://无影脚
	{
		plus[AGGRESSIVE] = 2 * skill_level;
	}
		break;

	case 86://联防技能
	{
		break;
	}
	default:
		LOG(ERROR)<<"no such skill ~~~"<<skill_id;
		break;
	}
	_last_skill_used = skill_id;
}

		//检测是否能够防守反击
bool SoccerPlayer::can_defend_attack_back() {
	if (this->get_match()->get_attack_team()->is_team_all_attack()) {
		return false;
	}

	int	defend_speak_type =
					this->get_match()->get_defend_team()->get_coach_effect_attack_defend();
	int	attack_speak_type =
					this->get_match()->get_attack_team()->get_coach_effect_attack_defend();
	int total_value = (defend_speak_type + attack_speak_type) / 2;
	double rate = 0.;
	rate = total_value * 0.1;
	if (RAND_DBL < rate) {
		return true;
	}
	return false;
}

//直接检测点球,1:一定赢，0:无所谓,-1:一定输
bool SoccerPlayer::do_pently_cmp(int force_rst, MatchPentlyEvent &event) {
	SoccerPlayer* gk_player = this->get_op_team()->get_gk_player();
	bool rst = false;
	if (force_rst == -1) {
		rst = false;
	} else if (force_rst == 1) {
		this->get_team()->add_action(this->get_union_pid(),
				ActionItem::GOAL_PENALTY);
		rst = true;
	} else {
		bool b_gk = calc_score_compare(this, gk_player, SCORE_PENALTY, 0);
		if (!b_gk) {
			//计算GK
			this->_match->update_compare_log(SCORE_PENALTY,_union_pid,gk_player->get_union_pid(),b_gk);
		} else {
			this->get_team()->add_action(this->get_union_pid(),
					ActionItem::GOAL_PENALTY);
		}
		rst = b_gk;
	}

	event.gk_player_id = gk_player->get_union_pid();
	event.shooter_player_id = this->get_union_pid();
	event.shoot_success = rst;
	event.shooter_skill = this->get_last_skill_used();
	event.keep_skill = gk_player->get_last_skill_used();
	int is_in_gate = RAND_INT % 2;
	int save_dir = RAND_INT % 3;
	int shoot_dir = RAND_INT % 3;
	event.is_in_gate = is_in_gate;
	event.save_dir = save_dir;
	event.shoot_dir = shoot_dir;
	return rst;
}

bool SoccerPlayer::is_gk(){
	if(this->_union_pid == this->_team->get_gk_player()->get_union_pid()){
		return true;
	}
	return false;
}

int SoccerPlayer::attack_or_defend(){
	if(this->_team->is_att_side()){
		return 1;
	}else{
		return 2;
	}
}

void SoccerPlayer::dump_player_skill_info(){
	VLOG(1)<<"player "<<this->_union_pid<<" has skill lists:";
	for(int count=0;count<_skills.get_skill_count();count++){
		PlayerSkill& skill = _skills[count];
		VLOG(1)<<skill.skill_id<<":"<<skill.skill_level<<":"<<skill.skill_chance;
	}
}
