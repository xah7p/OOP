#include "ManagerFactory.h"

#include "ManagerPool.h"

namespace
{
std::unique_ptr<ManagerCreator> createDrawManagerCreator()
{
    return std::make_unique<DrawManagerCreator>();
}

std::unique_ptr<ManagerCreator> createTransformManagerCreator()
{
    return std::make_unique<TransformManagerCreator>();
}

std::unique_ptr<ManagerCreator> createHistoryManagerCreator()
{
    return std::make_unique<HistoryManagerCreator>();
}

std::unique_ptr<ManagerCreator> createSceneManagerCreator()
{
    return std::make_unique<SceneManagerCreator>();
}

std::unique_ptr<ManagerCreator> createCameraManagerCreator()
{
    return std::make_unique<CameraManagerCreator>();
}

std::unique_ptr<ManagerCreator> createLoadManagerCreator()
{
    return std::make_unique<LoadManagerCreator>();
}
}  

ManagerFactory::ManagerFactory()
{
    solution = std::make_unique<ManagerSolution>();
    solution->registrate(ManagerIds::Draw, createDrawManagerCreator);
    solution->registrate(ManagerIds::Transform, createTransformManagerCreator);
    solution->registrate(ManagerIds::History, createHistoryManagerCreator);
    solution->registrate(ManagerIds::Scene, createSceneManagerCreator);
    solution->registrate(ManagerIds::Camera, createCameraManagerCreator);
    solution->registrate(ManagerIds::Load, createLoadManagerCreator);
}

void ManagerFactory::configureManagerPool()
{
    auto pool = ManagerPool::instance();
    for (ManagerId id : {ManagerIds::Scene, ManagerIds::Draw, ManagerIds::Transform,
                         ManagerIds::Load, ManagerIds::Camera, ManagerIds::History})
    {
        auto creator = solution->create(id);
        if (creator)
            pool->registerManager(id, creator->create());
    }
}
