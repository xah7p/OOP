#include "CameraSetActiveCommand.h"

#include "ManagerPool.h"

CameraSetActiveCommand::CameraSetActiveCommand(const EntityId& id):
    cameraId(id),
    method(&CameraManager::setActiveCamera),
    manager(std::dynamic_pointer_cast<CameraManager>(ManagerPool::instance()->getManager(ManagerIds::Camera)))
{ }

void CameraSetActiveCommand::execute()
{
    if (manager)
        ((*manager).*method)(cameraId);
}
