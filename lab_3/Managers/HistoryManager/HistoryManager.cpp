#include "HistoryManager.h"

#include "ManagerPool.h"
#include "SceneManager.h"

HistoryManager::HistoryManager():
    caretaker(std::make_shared<Caretaker>())
{ }

void HistoryManager::saveState(EntityId id)
{
    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (!sceneManager)
        return;
    auto entity = sceneManager->getEntity(id);
    if (!entity)
        return;
    caretaker->set(id, entity->createMemento());
}

void HistoryManager::restoreState(EntityId id)
{
    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (!sceneManager)
        return;
    auto entity = sceneManager->getEntity(id);
    if (!entity)
        return;
    entity->restoreMemento(caretaker->get(id));
}
