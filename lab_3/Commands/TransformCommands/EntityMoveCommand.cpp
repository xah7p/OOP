#include "EntityMoveCommand.h"

#include "ManagerPool.h"

EntityMoveCommand::EntityMoveCommand(EntityId id, const MoveArgs& args):
    entityId(id),
    args(args),
    method(&TransformManager::moveObject),
    manager(std::dynamic_pointer_cast<TransformManager>(ManagerPool::instance()->getManager(ManagerIds::Transform)))
{ }

void EntityMoveCommand::execute()
{
    if (manager)
        ((*manager).*method)(entityId, args);
}
