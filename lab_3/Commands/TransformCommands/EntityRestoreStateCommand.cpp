#include "EntityRestoreStateCommand.h"

#include "ManagerPool.h"

EntityRestoreStateCommand::EntityRestoreStateCommand(EntityId id):
    entityId(id),
    method(&HistoryManager::restoreState),
    manager(std::dynamic_pointer_cast<HistoryManager>(ManagerPool::instance()->getManager(ManagerIds::History)))
{ }

void EntityRestoreStateCommand::execute()
{
    if (manager)
        ((*manager).*method)(entityId);
}
