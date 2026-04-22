#pragma once

#include "DefaultCameraReaderImpl.h"

class ObjDefaultCameraReaderImpl: public BaseDefaultCameraReaderImpl {
public:
    ObjDefaultCameraReaderImpl() = delete;
    explicit ObjDefaultCameraReaderImpl(const std::string& path);
    ~ObjDefaultCameraReaderImpl() override = default;

    Vertex readViewpoint() override;
    Quaternion readQuaternion() override;
    double readFovY() override;
    double readNearZ() override;
    double readFarZ() override;
};
