#include "TxtDefaultCameraReaderImpl.h"

TxtDefaultCameraReaderImpl::TxtDefaultCameraReaderImpl(const std::string& path):
    BaseDefaultCameraReaderImpl(path)
{ }

Vertex TxtDefaultCameraReaderImpl::readViewpoint()
{
    file.clear();
    file.seekg(0);
    double x = 0.0, y = 0.0, z = 0.0;
    file >> x >> y >> z;
    return Vertex(x, y, z);
}

Quaternion TxtDefaultCameraReaderImpl::readQuaternion()
{
    file.clear();
    file.seekg(0);
    double vx = 0.0, vy = 0.0, vz = 0.0;
    double w = 1.0, x = 0.0, y = 0.0, z = 0.0;
    file >> vx >> vy >> vz >> w >> x >> y >> z;
    return Quaternion(w, x, y, z);
}

double TxtDefaultCameraReaderImpl::readFovY()
{
    return 60.0;
}

double TxtDefaultCameraReaderImpl::readNearZ()
{
    return 0.1;
}

double TxtDefaultCameraReaderImpl::readFarZ()
{
    return 1000.0;
}
