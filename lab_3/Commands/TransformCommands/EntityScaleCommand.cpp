#include "EntityScaleCommand.h"

#include "ManagerPool.h"

EntityScaleCommand::EntityScaleCommand(EntityId id, const ScaleArgs& args):
    entityId(id),
    args(args),
    method(&TransformManager::scaleObject),
    manager(std::dynamic_pointer_cast<TransformManager>(ManagerPool::instance()->getManager(ManagerIds::Transform)))
{ }

void EntityScaleCommand::execute()
{
    if (manager)
        ((*manager).*method)(entityId, args);
}
