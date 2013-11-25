#ifndef _PLAYER_QUEUE_H_
#define _PLAYER_QUEUE_H_

#include "soccer_player.h"

class PlayerQueueIter
{
    friend class PlayerQueue;
    typedef std::map<int, SoccerPlayer *> Queue;

    Queue::iterator _it;

    PlayerQueueIter(Queue::iterator it)
    {
        _it = it;
    }

public:
    bool operator==(const PlayerQueueIter &it) const
    {
        return _it == it._it;
    }

    bool operator!=(const PlayerQueueIter &it) const
    {
        return _it != it._it;
    }

    PlayerQueueIter &operator++(void)
    {
        ++_it;

        return *this;
    }

    SoccerPlayer *get_player(void)
    {
        return _it->second;
    }
};

class PlayerQueue
{
    typedef std::map<int, SoccerPlayer *> Queue;

    Queue _queue;
public:
    void clear(void);

    void insert(int distance, SoccerPlayer *player);

    int count(int radius, SoccerTeam *team);

    SoccerPlayer *get_closest(SoccerTeam *team);

    PlayerQueueIter begin(void)
    {
        return PlayerQueueIter(_queue.begin());
    }

    PlayerQueueIter end(void)
    {
        return PlayerQueueIter(_queue.end());
    }
};

#endif /* _PLAYER_QUEUE_H_ */
