#include "DefaultCameraReaderImpl.h"
#include "CameraException.h"

BaseDefaultCameraReaderImpl::BaseDefaultCameraReaderImpl(const std::string& path):
    file(path, std::ios::binary)
{
    if (!file.is_open())
        throw CameraException("Failed to open camera file.");
}
