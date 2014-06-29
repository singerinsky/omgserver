#ifndef _CON_QUEUE_H_
#define _CON_QUEUE_H_
#include "lock.h"

namespace omg
{

	template<class T>
	class ConcurrenceQueue
	{
		struct ConcurrenceQueueNode
		{
			ConcurrenceQueueNode(void)
			{
				next = NULL;
				value = NULL;
			}
			T *value;
			ConcurrenceQueueNode *next;
		};

	public:
		ConcurrenceQueue(void)
		{
			ConcurrenceQueueNode *node = new ConcurrenceQueueNode();
			_head = _tail = node;
		}

		~ConcurrenceQueue(void)
		{
			for (;;)
			{
				T *event = dequeue();
				if (event == NULL)
				{
					break;
				}
				delete event;
			}
			delete _head;
		}

		void enqueue(T *value)
		{
			ConcurrenceQueueNode *node = new ConcurrenceQueueNode();
			node->value = value;
			_tail->next = node;
			_tail = node;
		}

		T *dequeue(void)
		{
			while(_head == NULL || _head->next == NULL)
			{
			    return NULL;
            }
                
			T *value = _head->next->value;
            ConcurrenceQueueNode* old_head = _head;
			_head = _head->next;
			delete old_head;
			return value;
		}

	private:
		ConcurrenceQueueNode *_head;
		ConcurrenceQueueNode *_tail;
	};


	template<class T,class Lock>
	class ConcurrenceLockQueue
	{
		struct ConcurrenceQueueNode
		{
			ConcurrenceQueueNode(void)
			{
				next = NULL;
				value = NULL;
			}
			T *value;
			ConcurrenceQueueNode *next;
		};

	public:
		ConcurrenceLockQueue(void)
		{
			ConcurrenceQueueNode *node = new ConcurrenceQueueNode();
			_head = _tail = node;
			_lock.init();
		}

		~ConcurrenceLockQueue(void)
		{
			for (;_head != _tail;)
			{
				T *event = dequeue();
				if (event == NULL)
				{
					break;
				}
				delete event;
			}
			delete _head;
		}

		void enqueue(T *value)
		{
            _lock.lock();
			ConcurrenceQueueNode *node = new ConcurrenceQueueNode();
			node->value = value;
			_tail->next = node;
			_tail = node;
            _lock.unlock();
            //tell other thread to start
            _lock.lock_continue();
		}

		T *dequeue(void)
		{
            _lock.lock();
			while(_head == NULL || _head->next == NULL)
			{
                _lock.lock_hold();
			}
                
			T *value = _head->next->value;
            ConcurrenceQueueNode* old_head = _head;
			_head = _head->next;
            _lock.unlock();
			delete old_head;
			return value;
		}

	private:
		ConcurrenceQueueNode *_head;
		ConcurrenceQueueNode *_tail;
		Lock _lock;
	};

    //mulitply read ,single write
	template<class T,class Lock>
	class WRQueue{
	private:
		ConcurrenceQueue<T> _in_queue;
		ConcurrenceQueue<T> _out_queue;

		ConcurrenceQueue<T>* volatile  _p_in_queue;
		ConcurrenceQueue<T>* volatile  _p_out_queue;
		Lock	_lock;
	public:
		WRQueue(){
			_lock.init();
			_p_in_queue = &_in_queue;
			_p_out_queue = &_out_queue;
		}
		void enqueue(T* value){
			_lock.lock();
			_p_in_queue->enqueue(value);
			_lock.unlock();
		}

		T* dequeue(){
			T* value = _p_out_queue->dequeue();
			if(value == NULL){
				exchange_r_w_queue();
				value = _p_out_queue->dequeue();
				return value;
			}else{
				return value;
			}
		}

		void exchange_r_w_queue(){
			_lock.lock();
			ConcurrenceQueue<T>* tmp_point;
			tmp_point = _p_in_queue;
			_p_in_queue = _p_out_queue;
			_p_out_queue = tmp_point;
			_lock.unlock();
		}

	};
}
#endif /* _SFL_CONCURRENCE_QUEUE_H_ */
