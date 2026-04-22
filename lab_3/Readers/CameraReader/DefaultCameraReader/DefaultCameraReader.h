#pragma once

#include "DefaultCameraReaderImpl.h"
#include "CameraReader.h"
#include "Quaternion.h"
#include "Vertex.h"
#include <memory>

class DefaultCameraReader: public CameraReader {
private:
    std::shared_ptr<BaseDefaultCameraReaderImpl> impl;
    Vertex viewpoint;
    Quaternion quaternion;
    double fovY;
    double nearZ;
    double farZ;
public:
    DefaultCameraReader() = delete;
    explicit DefaultCameraReader(std::shared_ptr<BaseDefaultCameraReaderImpl> impl);
    ~DefaultCameraReader() = default;
    
    Vertex readViewpoint();
    Quaternion readQuaternion();
    double readFovY();
    double readNearZ();
    double readFarZ();
};
