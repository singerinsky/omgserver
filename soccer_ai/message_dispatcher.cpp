#include "../common/head.h"

#include "message_dispatcher.h"

MessageDispatcher::MessageDispatcher(EntityManager *entity_manager)
{
    _entity_manager = entity_manager;
}

bool MessageDispatcher::dispatche(Telegram *message)
{
    GameEntity *entity = _entity_manager->get(message->dest_id);
    bool result;
    if (entity != NULL)
    {
        entity->handler_message(message);
        result = true;
    }
    else
    {
        result = false;
    }

    delete message;

    return result;
}
