#ifndef _THREAD_H_
#define _THREAD_H_

#include "../common/head.h"
namespace omg
{
	class Thread
	{
		pthread_t 	_pthread_id;
		bool 		_is_auto_delete;
		char 		_thread_name[16];

		friend void *__thread_fun(void *arg);

	public:
		Thread(const char *name = NULL);

		virtual ~Thread(void);

		int start(bool auto_delete = true);

		virtual void *on_run(void) = 0;

		void *join(void);
	};

}

#endif /* _SFL_THREAD_H_ */
