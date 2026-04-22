#include "CameraDeleteCommand.h"

#include "ManagerPool.h"

CameraDeleteCommand::CameraDeleteCommand(const EntityId& id):
    cameraId(id),
    method(&CameraManager::removeCamera),
    manager(std::static_pointer_cast<CameraManager>(ManagerPool::instance()->getManager(ManagerIds::Camera)))
{ }

void CameraDeleteCommand::execute()
{
    if (manager)
        ((*manager).*method)(cameraId);
}
