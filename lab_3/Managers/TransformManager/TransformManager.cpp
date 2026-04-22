#include "TransformManager.h"

#include "MoveVisitor.h"
#include "ScaleVisitor.h"
#include "RotateVisitor.h"
#include "ManagerPool.h"
#include "SceneManager.h"
#include "HistoryManager.h"
#include "BaseCameraEntity.h"

void TransformManager::moveObject(EntityId id, const MoveArgs& args)
{
    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (!sceneManager)
        return;
    auto entity = sceneManager->getEntity(id);
    if (!entity)
        return;
    auto history = std::static_pointer_cast<HistoryManager>(
        ManagerPool::instance()->getManager(ManagerIds::History));
    const bool isCamera = (std::static_pointer_cast<BaseCameraEntity>(entity) != nullptr);
    if (history && !isCamera)
        history->saveState(id);
    entity->accept(std::make_shared<MoveVisitor>(args));
}

void TransformManager::scaleObject(EntityId id, const ScaleArgs& args)
{
    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (!sceneManager)
        return;
    auto entity = sceneManager->getEntity(id);
    if (!entity)
        return;
    auto history = std::static_pointer_cast<HistoryManager>(
        ManagerPool::instance()->getManager(ManagerIds::History));
    if (history)
        history->saveState(id);
    auto camera = std::static_pointer_cast<BaseCameraEntity>(entity);
    if (camera)
    {
        entity->accept(std::make_shared<ScaleVisitor>(args));
        return;
    }

    auto center = entity->getCenter();
    if (!center)
        return;
    ScaleArgs centeredArgs(args.getK(), center->getX(), center->getY(), center->getZ());
    entity->accept(std::make_shared<ScaleVisitor>(centeredArgs));
}

void TransformManager::rotateObject(EntityId id, const RotateArgs& args)
{
    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (!sceneManager)
        return;
    auto entity = sceneManager->getEntity(id);
    if (!entity)
        return;
    auto history = std::static_pointer_cast<HistoryManager>(
        ManagerPool::instance()->getManager(ManagerIds::History));
    const bool isCamera = (std::static_pointer_cast<BaseCameraEntity>(entity) != nullptr);
    if (history && !isCamera)
        history->saveState(id);
    if (isCamera)
    {
        entity->accept(std::make_shared<RotateVisitor>(args));
        return;
    }

    auto center = entity->getCenter();
    if (!center)
        return;
    RotateArgs centeredArgs(
        args.getAngleX(), args.getAngleY(), args.getAngleZ(),
        center->getX(), center->getY(), center->getZ());
    entity->accept(std::make_shared<RotateVisitor>(centeredArgs));
}
