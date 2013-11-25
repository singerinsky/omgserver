#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include "game_entity.h"
using namespace std;

class EntityManager
{
public:
    EntityManager(void);

    void enregister(GameEntity *entity);

    void unregister(uint32_t id);

    GameEntity *get(uint32_t id);

private:
    typedef std::tr1::unordered_map<uint32_t, GameEntity *> Map;
    typedef Map::iterator MapIter;

    Map _map;
};

#endif /* _ENTITY_MANAGER_H_ */
