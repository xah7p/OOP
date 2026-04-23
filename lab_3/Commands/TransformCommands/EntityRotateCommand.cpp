#include "EntityRotateCommand.h"

#include "ManagerPool.h"

EntityRotateCommand::EntityRotateCommand(EntityId id, const RotateArgs& args):
    entityId(id),
    args(args),
    method(&TransformManager::rotateObject),
    manager(std::static_pointer_cast<TransformManager>(ManagerPool::instance()->getManager(ManagerIds::Transform)))
{ }

void EntityRotateCommand::execute()
{
    if (manager)
        ((*manager).*method)(entityId, args);
}
