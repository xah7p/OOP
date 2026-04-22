#include "CameraAddCommand.h"

#include "ManagerPool.h"

CameraAddCommand::CameraAddCommand(const EntityId& id):
    cameraId(id),
    method(&CameraManager::addCamera),
    manager(std::static_pointer_cast<CameraManager>(ManagerPool::instance()->getManager(ManagerIds::Camera)))
{ }

void CameraAddCommand::execute()
{
    if (manager)
        ((*manager).*method)(cameraId);
}
