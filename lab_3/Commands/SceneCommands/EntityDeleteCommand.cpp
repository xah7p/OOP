#include "EntityDeleteCommand.h"

#include "ManagerPool.h"

EntityDeleteCommand::EntityDeleteCommand(EntityId id):
    id(id),
    manager(std::static_pointer_cast<SceneManager>(ManagerPool::instance()->getManager(ManagerIds::Scene)))
{ }

void EntityDeleteCommand::execute()
{
    if (manager)
        (void)manager->removeEntity(id);
}
