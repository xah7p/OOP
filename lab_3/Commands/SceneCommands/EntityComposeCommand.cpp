#include "EntityComposeCommand.h"

#include "ManagerPool.h"

EntityComposeCommand::EntityComposeCommand(std::vector<EntityId> ids, bool& result):
    ids(std::move(ids)),
    result(result),
    manager(std::static_pointer_cast<SceneManager>(ManagerPool::instance()->getManager(ManagerIds::Scene)))
{ }

void EntityComposeCommand::execute()
{
    result = false;
    if (manager)
        result = manager->createComposite(ids);
}
