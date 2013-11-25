/*
 * CTimerEventHandler.h
 *
 *  Created on: 2012-8-30
 *      Author: guanlei
 */

#ifndef CTIMEREVENTHANDLER_H_
#define CTIMEREVENTHANDLER_H_

#include "IJob.h"
#include "Timer.h"
#include "../net/IMsgDispatcher.h"

class CTimerEventHandler: public omg::IJob {
public:
	CTimerEventHandler(IMsgDispatcher* pDispatcher, int time_check = 1) {
		_msg_dispatcher = pDispatcher;
		_timer_check = time_check;
		_lock.init();
		_m_instance = this;
	}
	virtual ~CTimerEventHandler() {
	}

public:
	virtual void AddTimer(TimerObject timer_object) {
		_lock.lock();
		std::list<TimerSlot>::iterator itr = _timer_list.begin();
		while (itr != _timer_list.end()) {
			if (itr->timeout == timer_object.timeout) {
				itr->list.push_back(timer_object);
				break;
			}
			itr++;
		}

		if (itr == _timer_list.end()) {
			TimerSlot timer_slot;
			timer_slot.timeout = timer_object.timeout;
			timer_slot.list.push_back(timer_object);
			_timer_list.push_back(timer_slot);
		}
		_lock.unlock();
	}
	void RemoveTimer(TimerObject timer_object);

	virtual void ExecuteJob() {
		while (1) {
			check_timer();
			struct timespec ts;
			ts.tv_sec = _timer_check;
			ts.tv_nsec = 0;
			nanosleep(&ts, NULL);
		}
	}

	static CTimerEventHandler* GetInstance() {
		return _m_instance;
	}
	virtual void check_timer()=0;
protected:
	omg::MutexLock _lock;
	IMsgDispatcher* _msg_dispatcher;
	std::list<TimerSlot> _timer_list;
	int _timer_check;
	static CTimerEventHandler* _m_instance;
};

#endif /* CTIMEREVENTHANDLER_H_ */
