#ifndef _CON_QUEUE_H_
#define _CON_QUEUE_H_
namespace omg
{

	template<class T, class HeadLock, class TailLock>
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
			_head_lock.init();
			_tail_lock.init();
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
			_tail_lock.lock();
			_head_lock.lock();
			_tail->next = node;
			_tail = node;
			_head_lock.lock_continue();
			_head_lock.unlock();
			_tail_lock.unlock();
		}

		T *dequeue(void)
		{
			_head_lock.lock();

			ConcurrenceQueueNode *node = _head;
			ConcurrenceQueueNode *new_head = node->next;
			if (new_head == NULL)
			{
				//_head_lock.unlock();
				//wait for the cond
/*				_head_lock.lock_hold();
				node = _head;
				new_head = node->next;
				T* value = new_head->value;
				_head = new_head;*/

				_head_lock.unlock();
				//return value;
				return NULL;
			}
			T *value = new_head->value;
			_head = new_head;
			_head_lock.unlock();

			delete node;

			return value;
		}

	private:
		ConcurrenceQueueNode *_head;
		ConcurrenceQueueNode *_tail;
		HeadLock _head_lock;
		TailLock _tail_lock;
	};

	template<class T,class Lock>
	class WRQueue{
	private:
		ConcurrenceQueue<T,NullLock,NullLock> _in_queue;
		ConcurrenceQueue<T,NullLock,NullLock> _out_queue;

		ConcurrenceQueue<T,NullLock,NullLock>* volatile  _p_in_queue;
		ConcurrenceQueue<T,NullLock,NullLock>* volatile  _p_out_queue;
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
			ConcurrenceQueue<T,NullLock,NullLock>* tmp_point;
			tmp_point = _p_in_queue;
			_p_in_queue = _p_out_queue;
			_p_out_queue = tmp_point;
			_lock.unlock();
		}

	};
}
#endif /* _SFL_CONCURRENCE_QUEUE_H_ */
