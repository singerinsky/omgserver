#ifndef _SOCCER_TEAM_STATE_H_
#define _SOCCER_TEAM_STATE_H_

#include "soccer_team.h"

/////////////////////////////////
// DefendingState
BEGIN_DECLARE_STATE(DefendingState, SoccerTeam)
public:
    void execute(SoccerTeam &t);
END_DECLARE_STATE

/////////////////////////////////
// AttackingState
BEGIN_DECLARE_STATE(AttackingState, SoccerTeam)
public:
    void execute(SoccerTeam &t);
END_DECLARE_STATE

/////////////////////////////////
// GoalingState
BEGIN_DECLARE_STATE(GoalingState, SoccerTeam)
public:
    void execute(SoccerTeam &t);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(TeamAttackFailedState, SoccerTeam)
public:
    void enter(SoccerTeam& t);
	void execute(SoccerTeam &t);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(TeamDefendSuccessState, SoccerTeam)
public:
	void enter(SoccerTeam& t);
    void execute(SoccerTeam &t);
END_DECLARE_STATE

#endif /* _SOCCER_TEAM_STATE_H_ */
