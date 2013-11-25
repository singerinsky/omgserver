#include "../common/head.h"

#include "player_queue.h"

void PlayerQueue::clear(void)
{
    _queue.clear();
}

void PlayerQueue::insert(int distance, SoccerPlayer *player)
{
    _queue.insert(Queue::value_type(distance, player));
}

int PlayerQueue::count(int radius, SoccerTeam *team)
{
    int result = 0;
    Queue::iterator it;
    for (it = _queue.begin(); it != _queue.end(); ++it)
    {
        if (it->first <= radius)
        {
            if ((team == NULL) || it->second->is_team(team))
            {
                ++result;
            }
        }
        else
        {
            return result;
        }
    }

    return 0;
}

SoccerPlayer *PlayerQueue::get_closest(SoccerTeam *team)
{
	double distance = 100000;
	SoccerPlayer* player = NULL;
    Queue::iterator it;
    for (it = _queue.begin(); it != _queue.end(); ++it)
    {
        if (it->second->is_team(team))
        {
        	if(it->first < distance){
        		player = it->second;
        		distance = it->first;
        	}
        }
    }

    return player;
}
