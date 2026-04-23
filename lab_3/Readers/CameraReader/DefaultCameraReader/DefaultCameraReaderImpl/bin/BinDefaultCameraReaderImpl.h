#pragma once

#include "DefaultCameraReaderImpl.h"

class BinDefaultCameraReaderImpl: public BaseDefaultCameraReaderImpl {
public:
    BinDefaultCameraReaderImpl() = delete;
    explicit BinDefaultCameraReaderImpl(const std::string& path);
    ~BinDefaultCameraReaderImpl() override = default;

    Vertex readViewpoint() override;
    Quaternion readQuaternion() override;
    double readFovY() override;
    double readNearZ() override;
    double readFarZ() override;
};
