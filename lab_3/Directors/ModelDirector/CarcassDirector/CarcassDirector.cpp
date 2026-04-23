#include "CarcassDirector.h"

#include "BaseModelBuilder.h"

CarcassDirector::CarcassDirector(
    const std::shared_ptr<BaseReader>& reader,
    EntityStructureKind structureKind,
    std::shared_ptr<BuilderSolution> builderSolution):
    ModelDirector(std::move(builderSolution))
{
    builder = createBuilder(reader, EntityKind::Model, structureKind);
}

std::shared_ptr<BaseEntity> CarcassDirector::create() const
{
    auto modelBuilder = std::static_pointer_cast<BaseModelBuilder>(builder);
    if (!modelBuilder)
        return nullptr;

    modelBuilder->buildVertixes();
    modelBuilder->buildEdges();
    modelBuilder->buildCenter();
    return modelBuilder->getEntity();
}
