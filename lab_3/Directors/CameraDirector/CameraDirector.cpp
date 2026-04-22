#include "CameraDirector.h"

#include "BaseCameraBuilder.h"

CameraDirector::CameraDirector(
    const std::shared_ptr<BaseReader>& reader,
    EntityStructureKind structureKind,
    std::shared_ptr<BuilderSolution> builderSolution):
    BaseDirector(std::move(builderSolution))
{
    builder = createBuilder(reader, EntityKind::Camera, structureKind);
}

std::shared_ptr<BaseEntity> CameraDirector::create() const
{
    auto cameraBuilder = std::static_pointer_cast<BaseCameraBuilder>(builder);
    if (!cameraBuilder)
        return nullptr;

    cameraBuilder->buildViewpoint();
    cameraBuilder->buildQuaternion();
    cameraBuilder->buildProjection();
    return cameraBuilder->getEntity();
}
