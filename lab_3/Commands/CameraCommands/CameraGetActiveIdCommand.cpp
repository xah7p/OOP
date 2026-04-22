#include "CameraGetActiveIdCommand.h"

#include "ManagerPool.h"

CameraGetActiveIdCommand::CameraGetActiveIdCommand(EntityId& outId):
    outId(outId),
    manager(std::static_pointer_cast<CameraManager>(ManagerPool::instance()->getManager(ManagerIds::Camera)))
{ }

void CameraGetActiveIdCommand::execute()
{
    if (manager)
        outId = manager->getActiveCameraId();
}
