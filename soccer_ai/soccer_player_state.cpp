#include "../common/head.h"

#include "common/rand_generator.h"
#include "pass_refer_table.h"
#include "soccer_config.h"
#include "soccer_match.h"
#include "soccer_player_state.h"
#include "soccer_team.h"
#include "soccer_formation.h"
#include "soccer_pitch.h"

IMPLEMENT_STATE_INSTANCE(kickOffState)
IMPLEMENT_STATE_INSTANCE(DribbleState)
IMPLEMENT_STATE_INSTANCE(SupportState)
IMPLEMENT_STATE_INSTANCE(GlobalPlayerState)
IMPLEMENT_STATE_INSTANCE(PassState)
IMPLEMENT_STATE_INSTANCE(ReceiveState)
IMPLEMENT_STATE_INSTANCE(ShootState)
IMPLEMENT_STATE_INSTANCE(PositionDefendState)
IMPLEMENT_STATE_INSTANCE(GoHomeState)
IMPLEMENT_STATE_INSTANCE(MoveState)
IMPLEMENT_STATE_INSTANCE(Penalty)
IMPLEMENT_STATE_INSTANCE(Free)
IMPLEMENT_STATE_INSTANCE(Cornor)
IMPLEMENT_STATE_INSTANCE(OffSideState)
IMPLEMENT_STATE_INSTANCE(TackleFailState)
IMPLEMENT_STATE_INSTANCE(GKKickOffState)
IMPLEMENT_STATE_INSTANCE(StopState)

// 防守状态
IMPLEMENT_STATE_INSTANCE(AreaDefendState)
IMPLEMENT_STATE_INSTANCE(MindOnPlayerState)
IMPLEMENT_STATE_INSTANCE(MindOnBallState)
IMPLEMENT_STATE_INSTANCE(RunState)
IMPLEMENT_STATE_INSTANCE(AirDefendState)

using namespace std;
using namespace std::tr1;

//////////////////////////////
// GlobalPlayerState
void GlobalPlayerState::on_message(SoccerPlayer &p, Telegram *message)
{
    PlayerTelegram *player_msg = (PlayerTelegram *)message;
//    VLOG(1)<<player_msg->message<<"---";
    switch (player_msg->message)
    {
		case TELE_PLAYER_DRIBBLE:
		{
			DribbleState *state = DribbleState::alloc();
			state->target_regions = player_msg->target_regions;
			p.set_state(state);
		}
		break;
		case TELE_PLAYER_SUPPORT:
		{
			SupportState *state = SupportState::alloc();
			state->target_regions = player_msg->target_regions;
			p.set_state(state);
		}
		break;
		case TELE_PLAYER_PASS:
		{
			PassState *state = PassState::alloc();
			state->target_id = player_msg->target_id;
			state->target_regions = player_msg->target_regions;
			state->is_quick_pass = false;
			p.set_state(state);
		}
		break;
		case TELE_PLAYER_CROSS:
		{
			CrossState *state = CrossState::alloc();
			state->target_id = player_msg->target_id;
			state->target_regions = player_msg->target_regions;
			p.set_state(state);
		}
		break;
		case TELE_PLAYER_RECEIVE:
		{
			p.set_state(ReceiveState::alloc());
		}
		break;
		case TELE_FORCE_CROSS: // 强制长传
		{
			ForceCrossState *state = ForceCrossState::alloc();
			state->target_id = player_msg->target_id;
			state->target_regions = player_msg->target_regions;
			p.set_state(state);
		}
		break;
		case TELE_FORCE_SHOOT: // 强制射门
		{
			p.set_state(ForceShootState::alloc());
		}
		break;
		case TELE_PLAYER_SHOOT:
		{
			p.set_state(ShootState::alloc());
		}
		break;
		case TELE_PLAYER_MOVE:
		{
			MoveState *state = MoveState::alloc();
			state->target_regions = player_msg->target_regions;
			p.set_state(state);
		}
		break;
		case TELE_PLAYER_AreaDefendState:
		{
			p.set_state(AreaDefendState::alloc());
		}
		break;
		case TELE_PLAYER_MIND_ON_PLAYER:
		{
			MindOnPlayerState *state = MindOnPlayerState::alloc();
			state->tagert_id = player_msg->target_id;
			p.set_state(state);
		}
		break;
		case TELE_PLAYER_MIND_ON_BALL:
		{
			p.set_state(MindOnBallState::alloc());
		}
		break;
		case TELE_PLAYER_KICK_OFF:
		{
			p.set_state(KickOffState::alloc());
		}
		break;
		case TELE_PLAYER_PENALTY:
		{
			p.set_state(Penalty::alloc());
		}
		break;
		case TELE_PLAYER_FREE:
		{
			p.set_state(Free::alloc());
		}
		break;
		case TELE_PLAYER_CORNOR:
		{
			p.set_state(Cornor::alloc());
		}
		break;
		case TELE_PLAYER_RUN://跑位
		{
			RunState *state = RunState::alloc();
			state->_target_player_id = -1;
			if(player_msg->target_id != -1){
				state->_target_player_id = player_msg->target_id;
				state->_targetVec = SoccerFormation::get_region_pos(player_msg->target_id);
			}else{
				state->_targetVec = player_msg->target_regions.center();
			}
			p.set_state(state);
		}
		break;
		case TELE_FORCE_PASS://快速短传
		{
			if(p.get_state()->get_type() == TYPE_PassState)
			{
				PassState* state = static_cast<PassState*>(p.get_state());
				state->is_quick_pass = true;
			}
		}
		break;
		default:
		{

		}
		break;
    }
}

//////////////////////////
// DribbleState
void DribbleState::enter(SoccerPlayer &p)
{
    _cd = COLD_DOWN;
    _count = 0;
    _finish = false;
}

void DribbleState::change_to_tmp_dir(Vector2D& tmp_dir){
	this->tmp_dir_target = tmp_dir;
	_is_in_tmp_dir = true;
}

void DribbleState::dribble_to_cold_down(SoccerPlayer &p)
{
    if (_cd == 0)
    {
        p.set_state(NULL);
        p.set_speed(0);
    }
    else
    {
        p.run_forward();
        --_cd;
    }
}

void DribbleState::execute(SoccerPlayer &p)
{
    if (_finish)
    {
        dribble_to_cold_down(p);
    }
    else
    {
    	//如果已经在该区域了，超过一定的时间片就直接算结束
    	if(this->target_regions.in(p.get_pos())){
    		//如果是正在边线的过程中，算结束
    		if(p._tmp_dirbble_cd > 0){
    			_finish = true;
    		}
    		//如果计数超过了规定的数量也算结束，目前是5
    		this->_count++;
    		if(this->_count == 5){
    			_finish = true;
    		}
    	}

    	//如果已经跑到了该点的话，直接结束
        if (p.is_at_pos(target_regions.center()))
        {
            _finish = true;
            dribble_to_cold_down(p);
        }
        else
        {
            p.dribble_to(target_regions.center());
            _cd = _cd ? _cd - 1 : DribbleState::COLD_DOWN;
        }
    }
}

////////////////////////////////////////
// SupportState
void SupportState::enter(SoccerPlayer &p){
	this->_counter = 0;
}


void SupportState::execute(SoccerPlayer &p)
{
	if(this->_counter <= 6){
		p.support_to(target_regions.center(),false);
		_counter++;
	}else{
		p.support_to(target_regions.center(),true);
	}
}



//////////////////////////////////
// PassState
void PassState::enter(SoccerPlayer& p){
}


void PassState::execute(SoccerPlayer &p)
{
    p.pass_to_supporter(target_regions,this->is_quick_pass);
}

//////////////////////////////////
// CrossState
void CrossState::execute(SoccerPlayer &p)
{
	p.cross_to_supporter(target_regions);
}

//////////////////////////////////
// ForceCrossState
void ForceCrossState::execute(SoccerPlayer &p)
{
	p.force_cross_to_supporter(target_regions);
}

//////////////////////////////////
// Penalty
void Penalty::execute(SoccerPlayer &p)
{
    p.penalty_ball();
}

//////////////////////////////////
// ForceRunToBall
void ForceRunToBall::execute(SoccerPlayer &p)
{
    p.force_run_to_ball();
}

//////////////////////////////////
// Cornor
void Cornor::execute(SoccerPlayer &p)
{
    p.cornor_ball();
}

//////////////////////////////////
// Free
void Free::execute(SoccerPlayer &p)
{
    p.free_ball();
}

/////////////////////////////////
// ReceiveState
void ReceiveState::enter(SoccerPlayer &p)
{
    p.decide_receive_type();
}

void ReceiveState::execute(SoccerPlayer &p)
{
    p.receive_ball();
}

///////////////////////////////////
// ShootState
void ShootState::enter(SoccerPlayer &p){
	//choose shoot position
	Vector2D shooter_pos = p.get_pos();
	Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);
	double x_pos = shooter_pos.x;
	double y_pos = shooter_pos.y;
	double distance_to_goal = shooter_pos.distance(goal_vector);
	int rand_x = RAND_INT%30 - 15;
	int rand_y = RAND_INT%40 - 20;
	_is_ready_far_shoot = false;
	if (x_pos < B_FORBIDDEN_AREA_X) // 小于 大禁区
	{
		double target_dis_x = (goal_vector.x - x_pos) * ((distance_to_goal - 12*METER_TO_POINT)/distance_to_goal);
		double target_dis_y = (goal_vector.y - y_pos) * ((distance_to_goal - 12*METER_TO_POINT)/distance_to_goal);
		_shoot_postion.x = x_pos + target_dis_x + rand_x;
		_shoot_postion.y = y_pos + target_dis_y + rand_y;
	}else{
		double target_dis_x = (goal_vector.x - x_pos) * ((distance_to_goal - 7*METER_TO_POINT)/distance_to_goal);
		double target_dis_y = (goal_vector.y - y_pos) * ((distance_to_goal - 7*METER_TO_POINT)/distance_to_goal);
		_shoot_postion.x = x_pos + target_dis_x;
		_shoot_postion.y = y_pos + target_dis_y;
	}
}


void ShootState::execute(SoccerPlayer &p)
{
	//判断是否要远射
	if(_is_ready_far_shoot == true){
		if(p.get_pos().distance(_shoot_postion) < METER_TO_POINT){
			p.fat_shoot_goal();
		}else{
			p.dribble_to(_shoot_postion);
		}
		return;
	}

	if(SoccerPitch::GetInstance()->fat_shoot_area.in(p.get_pos())){
		int formation_pos = p.get_formation_pos();
		if((formation_pos == 12)||(formation_pos == 13)||(formation_pos == 14)||(formation_pos==17)||(formation_pos==18)||(formation_pos==19)){
			_shoot_postion.y = p.get_pos().y + 8*METER_TO_POINT;
			_shoot_postion.x = p.get_pos().x + 1*METER_TO_POINT;
			_is_ready_far_shoot = true;
			return;
		}
	}

	if(p.get_pos().distance(_shoot_postion) < METER_TO_POINT){
		p.shoot_goal();
	}else{
		p.dribble_to(_shoot_postion);
	}

}

///////////////////////////////////
// ForceShootState
void ForceShootState::execute(SoccerPlayer &p)
{
    p.force_shoot_goal();
}

////////////////////////////////////
// PositionDefendState
void PositionDefendState::execute(SoccerPlayer &p)
{
    p.defend_home();
}

////////////////////////////////////
// GoHomeState
void GoHomeState::enter(SoccerPlayer &p)
{

}

void GoHomeState::execute(SoccerPlayer &p)
{
    p.go_home();
}

////////////////////////////////////
// DefGoHomeState
void DefGoHomeState::execute(SoccerPlayer &p)
{
    p.def_go_home();
}

////////////////////////////////////
// StopState
void StopState::execute(SoccerPlayer &p)
{
   // p.def_go_home();
	p.set_speed(0.0);
}

///////////////////////////////////////
// FrozenState
void FrozenState::enter(SoccerPlayer &p)
{
    _cd = COLD_DOWN;
}

void FrozenState::execute(SoccerPlayer &p)
{
    if (_cd > 0)
    {
        --_cd;
    }
    else
    {
        p.set_state(AreaDefendState::alloc());
    }
}

///////////////////////////////////////
// MarkState
void MarkState::enter(SoccerPlayer &p)
{
    p.marking();
}

void MarkState::execute(SoccerPlayer &p)
{
    p.follow_ball();
}

void MarkState::leave(SoccerPlayer &p)
{
    p.unmarking();
}

///////////////////////////////////////
// MoveState
void MoveState::execute(SoccerPlayer &p)
{
    p.run_to(target_regions.center());
}

///////////////////////////////////////
// KickOffState
void KickOffState::enter(SoccerPlayer &p)
{
	_cd = CLOD_DOWN;
}

void KickOffState::execute(SoccerPlayer &p)
{
	if (_cd > 0)
	{
		_cd -- ;
		p.parepre_kick_off();
	}
	else
	{
		p.set_state(GoHomeState::alloc());
	}
}

///////////////////////////////////////
// AreaDefendState
void AreaDefendState::execute(SoccerPlayer &p)
{
	p.area_defend();
}

///////////////////////////////////////
// MindOnPlayerState
void MindOnPlayerState::execute(SoccerPlayer &p)
{
	p.set_mindPlayer(this->tagert_id);
}

void MindOnPlayerState::leave(SoccerPlayer &p)
{
	p.set_BeMindedPlayer(NULL);
}

///////////////////////////////////////
// MindOnBallState
void MindOnBallState::execute(SoccerPlayer &p)
{
	p.set_mindBall(this->tagert_id);
}

void MindOnBallState::enter(SoccerPlayer &p)
{
    p.minding();
}

void MindOnBallState::leave(SoccerPlayer &p)
{
    p.unminding();
    p.reset_keep_distance_stage();
}

///////////////////////////////////////
// BackDefendState 跑回防守位置的状态
void BackDefendState::execute(SoccerPlayer &p)
{
	p.back_defend();
}

///////////////////////////////////////
// TackleSlideCDState 抢球/铲球状态
void TackleSlideCDState::execute(SoccerPlayer &p)
{
	if (_cd > 0)
	{
		_cd = _cd -1;
		if (_cd == 0)
		{
			p.set_state(FrozenState::alloc());
		}
	}
	else
	{
		bool rst = false;
		if (this->_typ == 1)
		{
			rst = p.ground_tackle();
		}

		if (this->_typ == 2)
		{
			rst = p.ground_slide();
		}

		if (rst == false)
		{
			_cd = CLOD_DOWN;
		}
	}
}

///////////////////////////////////////
// OffSideState
void OffSideState::enter(SoccerPlayer &p)
{
	_cd = CLOD_DOWN;
}

void OffSideState::execute(SoccerPlayer &p)
{
	if (_cd > 0)
	{
		p.off_side();
		_cd --;
	}
	else
	{
		p.set_state(GoHomeState::alloc());
	}
}

///////////////////////////////////////
// GoalState
void GoalState::enter(SoccerPlayer &p)
{
	_cd = CLOD_DOWN;
}

void GoalState::execute(SoccerPlayer &p)
{
	p.set_speed(0);
}

///////////////////////////////////////
// TackleFailState
void TackleFailState::enter(SoccerPlayer &p)
{
	_cd = CLOD_DOWN;
	Vector2D ballVec = p.get_match()->get_ball()->get_pos();
	this->_targetVec.x = ballVec.x + (RAND_INT % 10 - 20);
	this->_targetVec.y = ballVec.y + (RAND_INT % 10 - 20);
}


void TackleFailState::execute(SoccerPlayer &p)
{
	if (_cd > 0)
	{
		p.run_to(this->_targetVec, 0.8);
		_cd--;
	}
	else
	{
		p.set_state(AreaDefendState::alloc());
	}
}

void RunState::enter(SoccerPlayer& player)
{
	Vector2D vec = this->_targetVec;
	if (_target_player_id == -1)
	{
		int index = player.get_team()->getTeamFormation()->checkPointRegionIndex(vec);
		if (index != -1)
		{
			_target_player_id = index+1;
		}
	}
	if (_target_player_id != -1)
	{
		player.set_formation_pos(_target_player_id);
	}
}

void RunState::execute(SoccerPlayer& player)
{
	player.go_home();
	//player.run_to(this->_targetVec,1.0);
//	VLOG(1)<<"ZAI PAO WEI "<<player.get_pos().x<<"-"<<player.get_pos().y<<" ___ ";
	//VLOG(1)<<this->_targetVec.x<<"="<<this->_targetVec.y;
}

void RunState::leave(SoccerPlayer& player)
{
	//player.set_formation_pos(player.get_formation_pos_bak());
}
/////////////////////////////////////////////////////////////////////////////////////////
void AirDefendState::execute(SoccerPlayer& player)
{
	player.air_defend(this->_targetVec);
}

void AirDefendState::leave(SoccerPlayer& player)
{
	player.get_team()->set_air_defend_player(NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////
void PassDefendState::execute(SoccerPlayer& player)
{
	player.pass_defend(this->_targetVec);
}

void PassDefendState::leave(SoccerPlayer& player)
{
	player.get_team()->set_pass_defend_player(NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////
//GKKickOffState
void GKKickOffState::execute(SoccerPlayer& player){
	//Vector2D goal_vector(0, PITCH_HEIGHT / 2);
	player.run_to(_targetVec);
	LOG(INFO)<<"TEST...............";
	if(player.get_pos().distance(_targetVec) < 2*METER_TO_POINT){
		LOG(INFO)<<"KICK OFF............................";
//		player.set_state(StopState::alloc());
//		player.gk_kick_off();
	}
}

void GKKickOffState::leave(SoccerPlayer& player){

}

void UnitDefendState::execute(SoccerPlayer& player){
	if(_target_player->is_own_ball()){
		Vector2D vec = _target_player->get_pos();
		vec += this->_cmp_target_vec;
		player.run_to(vec);
	}else{
		player.set_state(AreaDefendState::alloc());
	}
}


/*void OffSideState::execute(SoccerPlayer& player){
	SoccerPlayer *pPlayer = player.get_match()->get_defend_team()->get_def_team_closest_to_offline();
	if(pPlayer->get_pos().x < player.get_pos().x){
		Vector2D vec = pPlayer->get_pos();
		vec.x = vec.x - 2*METER_TO_POINT;
		player.run_to(vec);
	}else{
		player.set_state(GoHomeState::alloc());
	}
}*/
