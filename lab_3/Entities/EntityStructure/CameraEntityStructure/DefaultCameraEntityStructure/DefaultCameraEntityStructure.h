#pragma once

#include "Quaternion.h"
#include "CameraEntityStructure.h"

class DefaultCameraEntityStructure: public CameraEntityStructure {
private:
    Quaternion quaternion;
    double fovY;
    double nearZ;
    double farZ;
public:
    DefaultCameraEntityStructure() = delete;
    DefaultCameraEntityStructure(const Vertex& viewpoint);
    virtual ~DefaultCameraEntityStructure() override = default;

    const Matrix<double> getLookMatrix() const noexcept override;
    const Matrix<double> getProjectionMatrix(double aspectRatio) const noexcept override;

    void transform(std::shared_ptr<TransformData>) override;
    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    Vertex getViewpoint() const noexcept override;
    std::shared_ptr<CameraEntityStructure> clone() const override;
};

