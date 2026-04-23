#include "SceneManager.h"
#include "Composite.h"

SceneManager::SceneManager():
    scene(Scene::instance())
{ }

std::shared_ptr<Scene> SceneManager::getScene()
{
    return scene;
}

void SceneManager::setScene(std::shared_ptr<Scene> newScene)
{
    if (newScene)
        scene = std::move(newScene);
}

std::shared_ptr<BaseEntity> SceneManager::getEntity(EntityId id)
{
    return scene ? scene->getEntity(id) : nullptr;
}

bool SceneManager::addEntity(std::shared_ptr<BaseEntity> entity)
{
    return scene ? scene->addEntity(std::move(entity)) : false;
}

bool SceneManager::removeEntity(EntityId id)
{
    return scene ? scene->removeEntity(id) : false;
}

bool SceneManager::createComposite(const std::vector<EntityId>& ids)
{
    if (!scene || ids.size() < 2)
        return false;

    auto composite = std::make_shared<Composite>();
    size_t added = 0;
    for (const auto id : ids)
    {
        auto entity = scene->getEntity(id);
        if (!entity || !entity->isVisible())
            continue;
        composite->add({entity});
        ++added;
    }
    if (added < 2)
        return false;
    return scene->addEntity(composite);
}

void SceneManager::clear()
{
    if (scene)
        scene->clear();
}
