#pragma once

#include "DefaultCameraReaderImpl.h"

class TxtDefaultCameraReaderImpl: public BaseDefaultCameraReaderImpl {
public:
    TxtDefaultCameraReaderImpl() = delete;
    explicit TxtDefaultCameraReaderImpl(const std::string& path);
    ~TxtDefaultCameraReaderImpl() override = default;

    Vertex readViewpoint() override;
    Quaternion readQuaternion() override;
    double readFovY() override;
    double readNearZ() override;
    double readFarZ() override;
};
