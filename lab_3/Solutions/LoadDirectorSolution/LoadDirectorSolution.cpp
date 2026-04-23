#include "LoadDirectorSolution.h"

LoadDirectorSolution::LoadDirectorSolution(std::initializer_list<std::pair<EntityKind, CreateCreator>> list):
    callbacks()
{
    for (const auto& item : list)
        callbacks[item.first] = item.second;
}

bool LoadDirectorSolution::registrate(EntityKind kind, CreateCreator createfun)
{
    if (!createfun || callbacks.contains(kind))
        return false;
    callbacks[kind] = createfun;
    return true;
}

std::unique_ptr<BaseDirectorCreator> LoadDirectorSolution::create(EntityKind kind) const
{
    if (!callbacks.contains(kind))
        return nullptr;
    return callbacks.at(kind)();
}
