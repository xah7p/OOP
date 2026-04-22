#include "BuilderSolution.h"

bool BuilderSolution::registrate(EntityKind kind, EntityStructureKind structureKind, CreateCreator createfun)
{
    const Key key = {kind, structureKind};
    if (!createfun || callbacks.contains(key))
        return false;
    callbacks[key] = createfun;
    return true;
}

std::unique_ptr<BaseBuilderCreator> BuilderSolution::create(EntityKind kind, EntityStructureKind structureKind) const
{
    const Key key = {kind, structureKind};
    if (!callbacks.contains(key))
        return nullptr;
    return callbacks.at(key)();
}
