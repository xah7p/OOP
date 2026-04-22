#include "LoadCommand.h"

#include "ManagerPool.h"

LoadCommand::LoadCommand(EntityId id, const LoadRequest& req):
    entityId(id),
    req(req),
    method(&LoadManager::loadEntity),
    manager(std::static_pointer_cast<LoadManager>(ManagerPool::instance()->getManager(ManagerIds::Load)))
{ }

void LoadCommand::execute()
{
    if (manager)
        ((*manager).*method)(entityId, req);
}
