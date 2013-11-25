#include "thread.h"

namespace omg
{

void *__thread_fun(void *arg)
{
    Thread *thread = (Thread *)arg;
    if (thread->_thread_name[0] != '\0')
    {
        prctl(PR_SET_NAME, (unsigned long)thread->_thread_name);
    }

    void *result = thread->on_run();

    if (thread->_is_auto_delete)
    {
        thread->_pthread_id = 0;
        delete thread;
    }

    return result;
}

Thread::Thread(const char *name)
{
    _is_auto_delete = false;
    _pthread_id = 0;
    if (name == NULL)
    {
        _thread_name[0] = '\0';
    }
    else
    {
        strncpy(_thread_name, name, sizeof(_thread_name));
        _thread_name[sizeof(_thread_name) - 1] = '\0';
    }
}

Thread::~Thread(void)
{
    if(_pthread_id != 0)
    {
        void *result;
        pthread_join(_pthread_id, &result);
        _pthread_id = 0;
    }
}

int Thread::start(bool auto_delete)
{
    assert(_pthread_id == 0);

    _is_auto_delete = auto_delete;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if (_is_auto_delete)
    {
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    }

    int rv = pthread_create(&_pthread_id, &attr, __thread_fun, this);
    pthread_attr_destroy(&attr);
    if (rv == 0)
    {
        return 0;
    }

    _pthread_id = 0;

    return -1;
}

void *Thread::join(void)
{
    assert(_pthread_id != 0);
    assert(!_is_auto_delete);

    void *result;
    pthread_join(_pthread_id, &result);

    _pthread_id = 0;

    return result;
}

}
