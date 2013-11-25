#ifndef _TIMER_H_
#define _TIMER_H_

#include "head.h"

typedef enum{
	MATCH_MOVE,				//推动比赛
	MATCH_STATUS_CHECK,		//循环检查比赛的内存回收
	MATCH_ARENA_MATCHING	//定时匹配
}TimerEventType;

struct TimerObject{
	time_t timeout;//time
	int type;
	int	param;
};

struct TimerSlot{
	typedef std::list<TimerObject> TimerObjectList;
	time_t timeout;
	TimerObjectList list;
};




#endif
