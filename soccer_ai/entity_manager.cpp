#include "../common/head.h"

#include "entity_manager.h"

EntityManager::EntityManager(void)
	: _map(64)
{
}

void EntityManager::enregister(GameEntity *entity)
{
    std::pair<MapIter, bool> insert_result;
    insert_result = _map.insert(Map::value_type(entity->get_id(), entity));
    LOG_IF(FATAL, insert_result.second == false) << "entity id dup";
}

void EntityManager::unregister(uint32_t id)
{
    _map.erase(id);
}

GameEntity *EntityManager::get(uint32_t id)
{
    Map::iterator iter = _map.find(id);
    if (iter != _map.end())
    {
        return iter->second;
    }

    return NULL;
}
