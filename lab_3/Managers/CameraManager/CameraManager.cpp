#include "CameraManager.h"

#include "DefaultCameraEntityStructure.h"
#include "CameraEntity.h"
#include "SceneManager.h"
#include "ManagerPool.h"
#include "CameraManagerException.h"

CameraManager::CameraManager() = default;

void CameraManager::addCamera(const EntityId& id)
{
    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (!sceneManager)
        return;

    auto structure = std::make_shared<DefaultCameraEntityStructure>(Vertex(0.0, 0.0, 500.0));
    auto camera = std::make_shared<CameraEntity>(structure);
    (void)sceneManager->addEntity(camera);

    if (!activeCamera)
        setActiveCamera(id);
}

void CameraManager::removeCamera(const EntityId& id)
{
    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (!sceneManager)
        return;

    (void)sceneManager->removeEntity(id);
    if (id == activeCameraId)
    {
        activeCamera.reset();
    }
}

void CameraManager::setActiveCamera(const EntityId& id)
{
    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (!sceneManager)
        throw CameraManagerException("Scene manager is not available.");

    auto entity = sceneManager->getEntity(id);
    auto camera = std::static_pointer_cast<BaseCameraEntity>(entity);
    if (!camera)
        throw CameraManagerInvalidIdException("Invalid camera id.");

    activeCamera = camera;
    activeCameraId = id;
}

std::shared_ptr<BaseCameraEntity> CameraManager::getActiveCamera()
{
    return activeCamera;
}

EntityId CameraManager::getActiveCameraId() const noexcept
{
    return activeCameraId;
}
