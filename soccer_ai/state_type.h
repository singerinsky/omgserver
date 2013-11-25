#ifndef _STATE_TYPE_H_
#define _STATE_TYPE_H_

typedef enum
{
    TYPE_AttackingState,
    TYPE_BallCrossState,
    TYPE_BallDribbledState,
    TYPE_BallRollState,
    TYPE_BallStopState,
    TYPE_CameraFollowState,
    TYPE_CameraStayState,
    TYPE_DefendingState =7,
    TYPE_DribbleState,
    TYPE_FrozenState,
    TYPE_GlobalBallState,
    TYPE_GlobalPlayerState,
    TYPE_GoHomeState,
    TYPE_MarkState,
    TYPE_MoveState,
    TYPE_PassState,
    TYPE_PositionDefendState,
    TYPE_ReceiveState,//17
    TYPE_ShootState,
    TYPE_SupportState,
    TYPE_AreaDefendState,
    TYPE_MindOnPlayerState,
    TYPE_MindOnBallState,
    TYPE_MarkPlayerState,
    TYPE_MarkBallState,
    TYPE_TackleSlideCDState,//25
    TYPE_BackDefendState,
    TYPE_KickOffState,
    TYPE_DefGoHomeState,
    TYPE_Penalty,
    TYPE_Free,
    TYPE_OffSideState,
    TYPE_CrossState,
    TYPE_Cornor,
    TYPE_ForceShootState,//34
    TYPE_ForceCrossState,
    TYPE_ForceRunToBall,
    TYPE_StopState,
    TYPE_GoalState,
    TYPE_GoalingState,
    TYPE_TackleFailState,
    TYPE_PenaltyState,
    TYPE_FreeState,
    TYPE_CornerState,
    TYPE_RunState,
    TYPE_AirDefendState,
    TYPE_PassDefendState,
    TYPE_OffSide,
    TYPE_BallGoalFlyState,
    TYPE_TeamAttackFailedState,
    TYPE_TeamDefendSuccessState,
    TYPE_GKKickOffState,
    TYPE_UnitDefendState,//联防
    TYPE_End
} SoccerPlayerType;

#endif /* _STATE_TYPE_H_ */
