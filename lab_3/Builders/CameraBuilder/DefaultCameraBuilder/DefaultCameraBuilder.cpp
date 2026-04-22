#include "DefaultCameraBuilder.h"

DefaultCameraBuilder::DefaultCameraBuilder(std::shared_ptr<DefaultCameraReader> reader):
    BaseCameraBuilder(std::move(reader)), viewpoint(0.0, 0.0, 0.0),
    quaternion(), fovY(60.0), nearZ(0.1), farZ(1000.0)
{ }

std::shared_ptr<BaseEntity> DefaultCameraBuilder::createEntity()
{
    auto structure = std::make_shared<DefaultCameraEntityStructure>(viewpoint);
    (void)quaternion;
    (void)fovY;
    (void)nearZ;
    (void)farZ;
    return std::make_shared<CameraEntity>(structure);
}

bool DefaultCameraBuilder::buildViewpoint()
{
    if (!reader)
        return false;
    viewpoint = reader->readViewpoint();
    part = static_cast<size_t>(CameraBuildPart::Quaternion);
    return true;
}

bool DefaultCameraBuilder::buildQuaternion()
{
    if (!reader)
        return false;
    quaternion = reader->readQuaternion();
    part = static_cast<size_t>(CameraBuildPart::Projection);
    return true;
}

bool DefaultCameraBuilder::buildProjection()
{
    if (!reader)
        return false;
    fovY = reader->readFovY();
    nearZ = reader->readNearZ();
    farZ = reader->readFarZ();
    part = static_cast<size_t>(CameraBuildPart::Projection) + 1;
    return true;
}
