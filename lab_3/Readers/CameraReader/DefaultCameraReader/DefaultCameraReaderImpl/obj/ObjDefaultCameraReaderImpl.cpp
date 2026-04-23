#include "ObjDefaultCameraReaderImpl.h"

#include <sstream>

ObjDefaultCameraReaderImpl::ObjDefaultCameraReaderImpl(const std::string& path):
    BaseDefaultCameraReaderImpl(path)
{ }

Vertex ObjDefaultCameraReaderImpl::readViewpoint()
{
    file.clear();
    file.seekg(0);
    std::string line;
    while (std::getline(file, line))
    {
        if (!line.starts_with("v "))
            continue;
        std::istringstream is(line.substr(2));
        double x = 0.0, y = 0.0, z = 0.0;
        is >> x >> y >> z;
        return Vertex(x, y, z);
    }
    return Vertex(0.0, 0.0, 0.0);
}

Quaternion ObjDefaultCameraReaderImpl::readQuaternion()
{
    return Quaternion();
}

double ObjDefaultCameraReaderImpl::readFovY()
{
    return 60.0;
}

double ObjDefaultCameraReaderImpl::readNearZ()
{
    return 0.1;
}

double ObjDefaultCameraReaderImpl::readFarZ()
{
    return 1000.0;
}
