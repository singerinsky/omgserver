#ifndef _STATE_H_
#define _STATE_H_

#include "telegram.h"

template<class T>
class State
{
public:
    State(void)
    {
    }

    virtual ~State(void)
    {
    }

    virtual void enter(T &e)
    {
    }

    virtual void on_message(T &e, Telegram *)
    {
    }

    virtual void execute(T &e)
    {
    }

    virtual void leave(T &e)
    {
    }

    virtual void destory(void) = 0;

    virtual const char *get_name(void) const = 0;

    virtual int get_type(void) = 0;
};

#define BEGIN_DECLARE_STATE(T, Entity) \
    class T : public State<Entity> \
    { \
    public: \
        int get_type(void) { \
            return TYPE_##T; \
        } \
        const char * get_name(void) const { \
            return #T; \
        } \
        virtual void destory(void) { \
            delete this; \
        } \
        static T * alloc(void) { \
            return new T(); \
        } \


#define END_DECLARE_STATE };

#define IMPLEMENT_STATE_INSTANCE(T) 

#endif /* _STATE_H_ */
