#include "TransformManager.h"

#include "MoveVisitor.h"
#include "ScaleVisitor.h"
#include "RotateVisitor.h"
#include "ManagerPool.h"
#include "SceneManager.h"
#include "HistoryManager.h"
#include "BaseCameraEntity.h"

namespace
{
std::shared_ptr<SceneManager> getSceneManager()
{
    return std::dynamic_pointer_cast<SceneManager>(ManagerPool::instance()->getManager(ManagerIds::Scene));
}

std::shared_ptr<HistoryManager> getHistoryManager()
{
    return std::dynamic_pointer_cast<HistoryManager>(ManagerPool::instance()->getManager(ManagerIds::History));
}
}  

void TransformManager::moveObject(EntityId id, const MoveArgs& args)
{
    auto sceneManager = getSceneManager();
    if (!sceneManager)
        return;
    auto entity = sceneManager->getEntity(id);
    if (!entity)
        return;
    auto history = getHistoryManager();
    const bool isCamera = (std::dynamic_pointer_cast<BaseCameraEntity>(entity) != nullptr);
    if (history && !isCamera)
        history->saveState(id);
    entity->accept(std::make_shared<MoveVisitor>(args));
}

void TransformManager::scaleObject(EntityId id, const ScaleArgs& args)
{
    auto sceneManager = getSceneManager();
    if (!sceneManager)
        return;
    auto entity = sceneManager->getEntity(id);
    if (!entity)
        return;
    auto history = getHistoryManager();
    if (history)
        history->saveState(id);
    entity->accept(std::make_shared<ScaleVisitor>(args));
}

void TransformManager::rotateObject(EntityId id, const RotateArgs& args)
{
    auto sceneManager = getSceneManager();
    if (!sceneManager)
        return;
    auto entity = sceneManager->getEntity(id);
    if (!entity)
        return;
    auto history = getHistoryManager();
    const bool isCamera = (std::dynamic_pointer_cast<BaseCameraEntity>(entity) != nullptr);
    if (history && !isCamera)
        history->saveState(id);
    entity->accept(std::make_shared<RotateVisitor>(args));
}
