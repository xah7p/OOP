#include "Matrix4.h"

#include <cmath>

Matrix4::Matrix4() noexcept:
    inner(4, 4, 0.0)
{
    for (size_t i = 0; i < 4; ++i)
        inner[i][i] = 1.0;
}

Matrix4::Matrix4(const Matrix<double>& matrix):
    inner(matrix)
{ }

Matrix4::Matrix4(Matrix<double>&& matrix):
    inner(std::move(matrix))
{ }

Matrix4 Matrix4::fromMoveArgs(const MoveArgs& args) noexcept
{
    Matrix4 out;
    out.inner[0][3] = args.getOffsetX();
    out.inner[1][3] = args.getOffsetY();
    out.inner[2][3] = args.getOffsetZ();
    return out;
}

Matrix4 Matrix4::fromScaleArgs(const ScaleArgs& args) noexcept
{
    Matrix4 out;
    const double k = args.getK();
    out.inner[0][0] = k;
    out.inner[1][1] = k;
    out.inner[2][2] = k;
    out.inner[0][3] = args.getCenterX() * (1.0 - k);
    out.inner[1][3] = args.getCenterY() * (1.0 - k);
    out.inner[2][3] = args.getCenterZ() * (1.0 - k);
    return out;
}

Matrix4 Matrix4::fromRotationArgs(const RotateArgs& args) noexcept
{
    const double cx = std::cos(args.getAngleX());
    const double sx = std::sin(args.getAngleX());
    const double cy = std::cos(args.getAngleY());
    const double sy = std::sin(args.getAngleY());
    const double cz = std::cos(args.getAngleZ());
    const double sz = std::sin(args.getAngleZ());

    Matrix4 rx;
    rx.inner[1][1] = cx;
    rx.inner[1][2] = -sx;
    rx.inner[2][1] = sx;
    rx.inner[2][2] = cx;

    Matrix4 ry;
    ry.inner[0][0] = cy;
    ry.inner[0][2] = sy;
    ry.inner[2][0] = -sy;
    ry.inner[2][2] = cy;

    Matrix4 rz;
    rz.inner[0][0] = cz;
    rz.inner[0][1] = -sz;
    rz.inner[1][0] = sz;
    rz.inner[1][1] = cz;

    Matrix4 toOrigin = fromMoveArgs(MoveArgs(-args.getCenterX(), -args.getCenterY(), -args.getCenterZ()));
    Matrix4 back = fromMoveArgs(MoveArgs(args.getCenterX(), args.getCenterY(), args.getCenterZ()));
    return back * rz * ry * rx * toOrigin;
}

Matrix4 Matrix4::makeProduct(const Matrix4& other) const
{
    return Matrix4(inner * other.inner);
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
    return makeProduct(other);
}

Matrix4& Matrix4::multiply(const Matrix4& other)
{
    inner *= other.inner;
    return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
    return multiply(other);
}

const Matrix<double>& Matrix4::getMatrix() const noexcept
{
    return inner;
}

Matrix<double>& Matrix4::getMatrix() noexcept
{
    return inner;
}
