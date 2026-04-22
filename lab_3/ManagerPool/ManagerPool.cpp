#include "ManagerPool.h"

ManagerPool::ManagerPool() = default;

std::shared_ptr<BaseManager> ManagerPool::getManager(ManagerId id)
{
    if (!managers.contains(id))
        return nullptr;
    return managers.at(id);
}

bool ManagerPool::registerManager(ManagerId id, std::shared_ptr<BaseManager> manager)
{
    if (!manager || managers.contains(id))
        return false;

    managers[id] = std::move(manager);
    return true;
}

bool ManagerPool::unregisterManager(ManagerId id)
{
    return managers.erase(id) > 0;
}
