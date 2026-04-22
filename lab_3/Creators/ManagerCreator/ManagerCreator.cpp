#include "ManagerCreator.h"

#include "DrawManager.h"
#include "TransformManager.h"
#include "HistoryManager.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "LoadManager.h"

std::shared_ptr<BaseManager> DrawManagerCreator::create() const
{
    return std::make_shared<DrawManager>();
}

std::shared_ptr<BaseManager> TransformManagerCreator::create() const
{
    return std::make_shared<TransformManager>();
}

std::shared_ptr<BaseManager> HistoryManagerCreator::create() const
{
    return std::make_shared<HistoryManager>();
}

std::shared_ptr<BaseManager> SceneManagerCreator::create() const
{
    return std::make_shared<SceneManager>();
}

std::shared_ptr<BaseManager> CameraManagerCreator::create() const
{
    return std::make_shared<CameraManager>();
}

std::shared_ptr<BaseManager> LoadManagerCreator::create() const
{
    return std::make_shared<LoadManager>();
}
