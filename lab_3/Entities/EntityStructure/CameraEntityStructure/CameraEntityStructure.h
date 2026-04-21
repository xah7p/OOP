#pragma once

#include "Vertex.h"
#include "Matrix.h"
#include "TransformData.h"
#include <memory>

class BaseVisitor;

class CameraEntityStructure {
protected:
    Vertex viewpoint;
public:
    CameraEntityStructure() = default;
    virtual ~CameraEntityStructure() = 0;

    virtual const Matrix<double> getLookMatrix() const noexcept = 0;
    virtual const Matrix<double> getProjectionMatrix(double aspectRatio) const noexcept = 0;

    virtual void transform(std::shared_ptr<TransformData>) = 0;
    virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;
    virtual Vertex getViewpoint() const noexcept = 0;
};