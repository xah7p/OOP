#include "BaseDirector.h"

BaseDirector::BaseDirector(std::shared_ptr<BuilderSolution> builderSolution):
    builderSolution(std::move(builderSolution))
{ }

std::shared_ptr<BaseBuilder> BaseDirector::createBuilder(
    const std::shared_ptr<BaseReader>& reader,
    EntityKind kind,
    EntityStructureKind structureKind) const
{
    if (!builderSolution)
        return nullptr;
    auto creator = builderSolution->create(kind, structureKind);
    if (!creator)
        return nullptr;
    return creator->create(reader);
}
