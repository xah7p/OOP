#include "ManagerSolution.h"

ManagerSolution::ManagerSolution(std::initializer_list<std::pair<size_t, CreateCreator>> list):
    callbacks()
{
    for (const auto& item : list)
        callbacks[item.first] = item.second;
}

bool ManagerSolution::registrate(ManagerId id, CreateCreator createfun)
{
    if (!createfun || callbacks.contains(id))
        return false;

    callbacks[id] = createfun;
    return true;
}

std::unique_ptr<ManagerCreator> ManagerSolution::create(ManagerId id) const
{
    if (!callbacks.contains(id))
        return nullptr;

    return callbacks.at(id)();
}
