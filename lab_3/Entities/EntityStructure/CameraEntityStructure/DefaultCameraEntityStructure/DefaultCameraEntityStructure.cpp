#include "DefaultCameraEntityStructure.h"

#include "BaseVisitor.h"
#include <cmath>

DefaultCameraEntityStructure::DefaultCameraEntityStructure(const Vertex& viewpoint):
    quaternion(), fovY(90.0), nearZ(0.1), farZ(1000.0)
{
    this->viewpoint = viewpoint;
}

const Matrix<double> DefaultCameraEntityStructure::getLookMatrix() const noexcept
{
    auto rot = quaternion.inverse().toRotationMatrix4().getMatrix();
    Matrix<double> view = rot;
    const double vx = viewpoint.getX();
    const double vy = viewpoint.getY();
    const double vz = viewpoint.getZ();
    view[0][3] = -(view[0][0] * vx + view[0][1] * vy + view[0][2] * vz);
    view[1][3] = -(view[1][0] * vx + view[1][1] * vy + view[1][2] * vz);
    view[2][3] = -(view[2][0] * vx + view[2][1] * vy + view[2][2] * vz);
    return view;
}

const Matrix<double> DefaultCameraEntityStructure::getProjectionMatrix(double aspectRatio) const noexcept
{
    Matrix<double> p(4, 4, 0.0);
    const double fovRad = fovY * M_PI / 180.0;
    const double f = 1.0 / std::tan(fovRad * 0.5);
    p[0][0] = f / aspectRatio;
    p[1][1] = f;
    p[2][2] = (farZ + nearZ) / (nearZ - farZ);
    p[2][3] = (2.0 * farZ * nearZ) / (nearZ - farZ);
    p[3][2] = -1.0;
    return p;
}

void DefaultCameraEntityStructure::transform(std::shared_ptr<TransformData> data)
{
    if (!data)
        return;

    if (data->isMove())
    {
        viewpoint.transform(std::move(data));
        return;
    }

    if (data->isRotate())
    {
        const auto &matrix = data->getMatrix().getMatrix();
        const auto delta = Quaternion::fromRotationMatrix(matrix);
        quaternion = (delta * quaternion).normalized();
    }
}

void DefaultCameraEntityStructure::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(std::make_shared<DefaultCameraEntityStructure>(*this));
}

Vertex DefaultCameraEntityStructure::getViewpoint() const noexcept
{
    return viewpoint;
}
