#include "DirectorCreator.h"

#include "CarcassDirector.h"
#include "CameraDirector.h"

std::unique_ptr<BaseDirector> CarcassDirectorCreator::create(
    const std::shared_ptr<BaseReader>& reader,
    EntityStructureKind structureKind,
    const std::shared_ptr<BuilderSolution>& builderSolution) const
{
    return std::make_unique<CarcassDirector>(reader, structureKind, builderSolution);
}

std::unique_ptr<BaseDirector> CameraDirectorCreator::create(
    const std::shared_ptr<BaseReader>& reader,
    EntityStructureKind structureKind,
    const std::shared_ptr<BuilderSolution>& builderSolution) const
{
    return std::make_unique<CameraDirector>(reader, structureKind, builderSolution);
}
