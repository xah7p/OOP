#pragma once

#include "Quaternion.h"
#include "Vertex.h"
#include <fstream>
#include <string>

class BaseDefaultCameraReaderImpl {
protected:
    std::ifstream file;
public:
    BaseDefaultCameraReaderImpl() = delete;
    explicit BaseDefaultCameraReaderImpl(const std::string& path);
    virtual ~BaseDefaultCameraReaderImpl() = default;

    virtual Vertex readViewpoint() = 0;
    virtual Quaternion readQuaternion() = 0;
    virtual double readFovY() = 0;
    virtual double readNearZ() = 0;
    virtual double readFarZ() = 0;
};