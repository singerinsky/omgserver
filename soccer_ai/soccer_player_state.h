#ifndef _SOCCER_PLAYER_STATE_H_
#define _SOCCER_PLAYER_STATE_H_

#include "soccer_player.h"
#include "../common/object_pool.h"
#include "state_type.h"

/////////////////////////////////
// GlobalPlayerState
BEGIN_DECLARE_STATE(GlobalPlayerState, SoccerPlayer)
public:
    void on_message(SoccerPlayer &p, Telegram *message);
END_DECLARE_STATE

/////////////////////////////////
// DribbleState
BEGIN_DECLARE_STATE(DribbleState, SoccerPlayer)
    enum { COLD_DOWN = 4 };
    int _cd;
    int _count;//倒计时，几个时间片后必须射门
    bool _finish;
    bool _is_in_tmp_dir;

public:
    RegionSet target_regions;
    Vector2D  tmp_dir_target;

    void change_to_tmp_dir(Vector2D& tmp_dir);
    void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
private:
    void dribble_to_cold_down(SoccerPlayer &p); 
END_DECLARE_STATE

/////////////////////////////////
// PassState
BEGIN_DECLARE_STATE(PassState, SoccerPlayer)
public:
    RegionSet target_regions;
    int target_id;
    bool is_quick_pass;
    void enter(SoccerPlayer& p);
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// CrossState
BEGIN_DECLARE_STATE(CrossState, SoccerPlayer)
public:
    RegionSet target_regions;
    int target_id;

    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// ForceCrossState
BEGIN_DECLARE_STATE(ForceCrossState, SoccerPlayer)
public:
    RegionSet target_regions;
    int target_id;

    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// ForceRunToBall
BEGIN_DECLARE_STATE(ForceRunToBall, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// Penalty
BEGIN_DECLARE_STATE(Penalty, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// Cornor
BEGIN_DECLARE_STATE(Cornor, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// Free
BEGIN_DECLARE_STATE(Free, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// SupportState
BEGIN_DECLARE_STATE(SupportState, SoccerPlayer)
public:
    RegionSet target_regions;
    int _counter;

    void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// ReceiveState
BEGIN_DECLARE_STATE(ReceiveState, SoccerPlayer)
public:
    void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// ShootState
BEGIN_DECLARE_STATE(ShootState, SoccerPlayer)
public:
	void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
    Vector2D	_shoot_postion;
    bool		_is_ready_far_shoot;
END_DECLARE_STATE

/////////////////////////////////
// ForceShootState
BEGIN_DECLARE_STATE(ForceShootState, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// PositionDefendState
BEGIN_DECLARE_STATE(PositionDefendState, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// GoHomeState
BEGIN_DECLARE_STATE(GoHomeState, SoccerPlayer)
public:
    void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// StopState
BEGIN_DECLARE_STATE(StopState, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// FrozenState
BEGIN_DECLARE_STATE(FrozenState, SoccerPlayer)
    enum { COLD_DOWN = 20 };
    int _cd;
public:
    void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// MarkState
BEGIN_DECLARE_STATE(MarkState, SoccerPlayer)
    void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
    void leave(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// MoveState
BEGIN_DECLARE_STATE(MoveState, SoccerPlayer)
public:
    RegionSet target_regions;
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// AreaDefendState
BEGIN_DECLARE_STATE(AreaDefendState, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// MindOnPlayerState
BEGIN_DECLARE_STATE(MindOnPlayerState, SoccerPlayer)
public:
	int tagert_id;
    void execute(SoccerPlayer &p);
    void leave(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// MindOnBallState
BEGIN_DECLARE_STATE(MindOnBallState, SoccerPlayer)
public:
	int tagert_id;
    void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
    void leave(SoccerPlayer &p);
END_DECLARE_STATE


/////////////////////////////////
// BackDefendState
BEGIN_DECLARE_STATE(BackDefendState, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// TackleSlideCDState
BEGIN_DECLARE_STATE(TackleSlideCDState, SoccerPlayer)
public:
	enum {CLOD_DOWN = 5};
	int _cd;
	int _typ;
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// KickOffState
//开球状态
BEGIN_DECLARE_STATE(KickOffState, SoccerPlayer)
public:
	enum {CLOD_DOWN = 10};
	int _cd;
	void enter(SoccerPlayer &p);
	void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// DefGoHomeState
//回防状态
BEGIN_DECLARE_STATE(DefGoHomeState, SoccerPlayer)
public:
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// OffSideState
//越位状态
BEGIN_DECLARE_STATE(OffSideState, SoccerPlayer)
public:
	enum{CLOD_DOWN = 10};
	int	_cd;
	void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// GoalState
//进球后所有的球员的状态
BEGIN_DECLARE_STATE(GoalState, SoccerPlayer)
public:
	enum{CLOD_DOWN = 10};
	int	_cd;
	void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

/////////////////////////////////
// TackleFailState
//抢断失败状态机
BEGIN_DECLARE_STATE(TackleFailState, SoccerPlayer)
public:
	enum{CLOD_DOWN = 15};
	Vector2D _targetVec;
	int	_cd;
	void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
END_DECLARE_STATE

//跑位状态机，球员接受到跑位就扮演该位置的球员的position。
BEGIN_DECLARE_STATE(RunState, SoccerPlayer)
public:
	RegionSet	_region;
	int	_target_player_id;
	Vector2D _targetVec;
	void enter(SoccerPlayer &p);
    void execute(SoccerPlayer &p);
    void leave(SoccerPlayer &p);
END_DECLARE_STATE

//防守高球状态机，球员直接跑位
BEGIN_DECLARE_STATE(AirDefendState, SoccerPlayer)
public:
	Vector2D _targetVec;
    void execute(SoccerPlayer &p);
    void leave(SoccerPlayer &p);
END_DECLARE_STATE

//防守地面传球状态机,球员直接跑位
BEGIN_DECLARE_STATE(PassDefendState,SoccerPlayer)
public:
	Vector2D _targetVec;
	void execute(SoccerPlayer &p);
	void leave(SoccerPlayer &p);
END_DECLARE_STATE

/*BEGIN_DECLARE_STATE(OffSideState,SoccerPlayer)
public:
	Vector2D _targetVec;
	void execute(SoccerPlayer &p);
	void leave(SoccerPlayer &p);
END_DECLARE_STATE*/
BEGIN_DECLARE_STATE(GKKickOffState,SoccerPlayer)
public:
	Vector2D _targetVec;
	void execute(SoccerPlayer &p);
	void leave(SoccerPlayer &p);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(UnitDefendState,SoccerPlayer)
public:
	SoccerPlayer* _target_player;
	Vector2D	  _cmp_target_vec;
	void execute(SoccerPlayer &p);
END_DECLARE_STATE


#endif /* _SOCCER_PLAYER_STATE_H_ */
