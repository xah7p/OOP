#include "DrawManager.h"

#include "ManagerPool.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "DrawVisitor.h"
#include "DefaultCenterStrategy.h"
#include "DefaultProjectionStrategy.h"
#include "ZBufferStrategy.h"

void DrawManager::setPainter(std::shared_ptr<BasePainter> painter)
{
    this->painter = std::move(painter);
}

void DrawManager::draw()
{
    if (!painter)
        return;

    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    auto cameraManager = std::static_pointer_cast<CameraManager>(
        ManagerPool::instance()->getManager(ManagerIds::Camera));
    if (!sceneManager)
        return;

    painter->clear();

    auto visitor = std::make_shared<DrawVisitor>(
        cameraManager ? cameraManager->getActiveCamera() : nullptr,
        painter,
        std::make_shared<DefaultCenterStrategy>(),
        std::make_shared<DefaultProjectionStrategy>(),
        std::make_shared<ZBufferStrategy>());

    auto scene = sceneManager->getScene();
    if (scene)
    {
        scene->accept(visitor);
        visitor->flush();
    }
}
