#ifndef _MESSAGE_DISPATCHER_H_
#define _MESSAGE_DISPATCHER_H_

#include "entity_manager.h"
#include "telegram.h"

class MessageDispatcher
{
public:
    MessageDispatcher(EntityManager *entity_manager);

    bool dispatche(Telegram *message);

private:
    EntityManager *_entity_manager;
};

#endif /* _MESSAGE_DISPATCHER_H_ */
