#include "SceneManager.h"

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

void SceneManager::clear()
{
    if (scene)
        scene->clear();
}
