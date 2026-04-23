#include "Scene.h"

bool Scene::addEntity(std::shared_ptr<BaseEntity> entity)
{
    if (!entity)
        return false;

    entities[size++] = std::move(entity);
    return true;
}

bool Scene::removeEntity(EntityId id)
{
    return entities.erase(id) > 0;
}

std::shared_ptr<BaseEntity> Scene::getEntity(EntityId id)
{
    if (!entities.contains(id))
        return nullptr;
    return entities.at(id);
}

Scene::iterator Scene::begin()
{
    return entities.begin();
}

Scene::iterator Scene::end()
{
    return entities.end();
}

Scene::const_iterator Scene::cbegin()
{
    return entities.cbegin();
}

Scene::const_iterator Scene::cend()
{
    return entities.cend();
}

void Scene::accept(std::shared_ptr<BaseVisitor> visitor)
{
    for (auto &item : entities)
        item.second->accept(visitor);
}

void Scene::clear()
{
    entities.clear();
    size = 0;
}
