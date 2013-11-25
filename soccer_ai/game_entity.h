#ifndef _GAME_ENTITY_H_
#define _GAME_ENTITY_H_

#include "telegram.h"
#include "state.h"

class GameEntity
{
    int _id;

public:
    GameEntity(int id)
    {
        _id = id;
    }

    virtual ~GameEntity(void)
    {
    }

    virtual void handler_message(Telegram *telegram) = 0;

    int get_id(void) const
    {
        return _id;
    }
};

template<class T>
class GameEntityBase: public GameEntity
{
public:
    GameEntityBase(uint32_t id)
    	: GameEntity(id)
    {
        _global_state = NULL;
        _state = NULL;
    }

    virtual ~GameEntityBase(void)
    {
        if (_global_state)
        {
            _global_state->destory();
        }

        if (_state)
        {
            _state->destory();
        }
    }

    virtual void update(void)
    {
        if (_global_state)
        {
            _global_state->execute(*(T *)this);
        }

        if (_state)
        {
            _state->execute(*(T *)this);
        }
    }

    void handler_message(Telegram *telegram)
    {
        if (_global_state)
        {
            _global_state->on_message(*(T *)this, telegram);
        }

        if (_state)
        {
            _state->on_message(*(T *)this, telegram);
        }
    }

    void set_global_state(State<T> *state)
    {
        if (_global_state)
        {
            _global_state->destory();
        }
        _global_state = state;
    }

    void set_state(State<T> *state)
    {
        if (_state)
        {
            _state->leave(*(T *)this);
            _state->destory();
        }

        _state = state;

        if (_state)
        {
            _state->enter(*(T *)this);
        }
    }

    State<T> *get_state(void)
    {
        return _state;
    }

    const State<T> * get_state(void) const
    {
        return _state;
    }

private:
    State<T> *_state;
    State<T> *_global_state;
};

#endif /* _GAME_ENTITY_H_ */
