#include "BuilderSolution.h"

namespace
{
size_t makeKey(EntityKind kind, EntityStructureKind structureKind)
{
    return (static_cast<size_t>(kind) << 8U) | static_cast<size_t>(structureKind);
}
}  

BuilderSolution::BuilderSolution(std::initializer_list<std::pair<size_t, CreateCreator>> list):
    callbacks()
{
    for (const auto& item : list)
        callbacks[item.first] = item.second;
}

bool BuilderSolution::registrate(EntityKind kind, EntityStructureKind structureKind, CreateCreator createfun)
{
    const auto key = makeKey(kind, structureKind);
    if (!createfun || callbacks.contains(key))
        return false;
    callbacks[key] = createfun;
    return true;
}

std::unique_ptr<BaseBuilderCreator> BuilderSolution::create(EntityKind kind, EntityStructureKind structureKind) const
{
    const auto key = makeKey(kind, structureKind);
    if (!callbacks.contains(key))
        return nullptr;
    return callbacks.at(key)();
}
