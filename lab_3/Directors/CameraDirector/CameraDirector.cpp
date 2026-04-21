#include "CameraDirector.h"

#include "BaseCameraBuilder.h"

CameraDirector::CameraDirector(std::shared_ptr<BaseBuilder> builder)
{
    this->builder = std::move(builder);
}

std::shared_ptr<BaseEntity> CameraDirector::create() const
{
    auto cameraBuilder = std::dynamic_pointer_cast<BaseCameraBuilder>(builder);
    if (!cameraBuilder)
        return nullptr;

    cameraBuilder->buildViewpoint();
    cameraBuilder->buildQuaternion();
    cameraBuilder->buildProjection();
    return cameraBuilder->getEntity();
}
