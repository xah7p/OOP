#include "DefaultCameraReader.h"

DefaultCameraReader::DefaultCameraReader(std::shared_ptr<BaseDefaultCameraReaderImpl> impl):
    impl(std::move(impl)),
    viewpoint(0.0, 0.0, 0.0),
    quaternion(),
    fovY(60.0),
    nearZ(0.1),
    farZ(1000.0)
{ }

Vertex DefaultCameraReader::readViewpoint()
{
    if (impl)
        viewpoint = impl->readViewpoint();
    return viewpoint;
}

Quaternion DefaultCameraReader::readQuaternion()
{
    if (impl)
        quaternion = impl->readQuaternion();
    return quaternion;
}

double DefaultCameraReader::readFovY()
{
    if (impl)
        fovY = impl->readFovY();
    return fovY;
}

double DefaultCameraReader::readNearZ()
{
    if (impl)
        nearZ = impl->readNearZ();
    return nearZ;
}

double DefaultCameraReader::readFarZ()
{
    if (impl)
        farZ = impl->readFarZ();
    return farZ;
}
