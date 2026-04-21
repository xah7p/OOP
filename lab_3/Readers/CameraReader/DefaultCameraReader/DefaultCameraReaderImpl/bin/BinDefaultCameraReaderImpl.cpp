#include "BinDefaultCameraReaderImpl.h"

BinDefaultCameraReaderImpl::BinDefaultCameraReaderImpl(const std::string& path):
    BaseDefaultCameraReaderImpl(path)
{ }

Vertex BinDefaultCameraReaderImpl::readViewpoint()
{
    file.clear();
    file.seekg(0);
    double x = 0.0, y = 0.0, z = 0.0;
    file.read(reinterpret_cast<char*>(&x), sizeof(double));
    file.read(reinterpret_cast<char*>(&y), sizeof(double));
    file.read(reinterpret_cast<char*>(&z), sizeof(double));
    return Vertex(x, y, z);
}

Quaternion BinDefaultCameraReaderImpl::readQuaternion()
{
    double w = 1.0, x = 0.0, y = 0.0, z = 0.0;
    file.read(reinterpret_cast<char*>(&w), sizeof(double));
    file.read(reinterpret_cast<char*>(&x), sizeof(double));
    file.read(reinterpret_cast<char*>(&y), sizeof(double));
    file.read(reinterpret_cast<char*>(&z), sizeof(double));
    return Quaternion(w, x, y, z);
}

double BinDefaultCameraReaderImpl::readFovY()
{
    return 60.0;
}

double BinDefaultCameraReaderImpl::readNearZ()
{
    return 0.1;
}

double BinDefaultCameraReaderImpl::readFarZ()
{
    return 1000.0;
}
