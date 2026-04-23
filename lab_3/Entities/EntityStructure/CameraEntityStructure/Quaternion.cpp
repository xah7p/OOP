#include "Quaternion.h"

Quaternion::Quaternion() noexcept:
    w(1.0), x(0.0), y(0.0), z(0.0)
{ }

Quaternion::Quaternion(double w, double x, double y, double z) noexcept:
    w(w), x(x), y(y), z(z)
{ }

double Quaternion::getW() const noexcept { return w; }
double Quaternion::getX() const noexcept { return x; }
double Quaternion::getY() const noexcept { return y; }
double Quaternion::getZ() const noexcept { return z; }

Quaternion Quaternion::normalized() const noexcept
{
    const double n = std::sqrt(w * w + x * x + y * y + z * z);
    if (n == 0.0)
        return Quaternion();
    return Quaternion(w / n, x / n, y / n, z / n);
}

Quaternion Quaternion::conjugate() const noexcept
{
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::inverse() const noexcept
{
    const double n2 = w * w + x * x + y * y + z * z;
    if (n2 == 0.0)
        return Quaternion();
    const auto c = conjugate();
    return Quaternion(c.w / n2, c.x / n2, c.y / n2, c.z / n2);
}

Quaternion Quaternion::multiply(const Quaternion& other) const noexcept
{
    return Quaternion(
        w * other.w - x * other.x - y * other.y - z * other.z,
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w);
}

Quaternion Quaternion::operator*(const Quaternion& other) const noexcept
{
    return multiply(other);
}

Quaternion Quaternion::fromRotationMatrix(const Matrix<double>& matrix) noexcept
{
    if (matrix.getRowsCount() < 3 || matrix.getColsCount() < 3)
        return Quaternion();

    const double m00 = matrix[0][0], m01 = matrix[0][1], m02 = matrix[0][2];
    const double m10 = matrix[1][0], m11 = matrix[1][1], m12 = matrix[1][2];
    const double m20 = matrix[2][0], m21 = matrix[2][1], m22 = matrix[2][2];

    const double trace = m00 + m11 + m22;
    Quaternion q;
    if (trace > 0.0)
    {
        const double s = std::sqrt(trace + 1.0) * 2.0;
        q = Quaternion(0.25 * s, (m21 - m12) / s, (m02 - m20) / s, (m10 - m01) / s);
    }
    else if (m00 > m11 && m00 > m22)
    {
        const double s = std::sqrt(1.0 + m00 - m11 - m22) * 2.0;
        q = Quaternion((m21 - m12) / s, 0.25 * s, (m01 + m10) / s, (m02 + m20) / s);
    }
    else if (m11 > m22)
    {
        const double s = std::sqrt(1.0 + m11 - m00 - m22) * 2.0;
        q = Quaternion((m02 - m20) / s, (m01 + m10) / s, 0.25 * s, (m12 + m21) / s);
    }
    else
    {
        const double s = std::sqrt(1.0 + m22 - m00 - m11) * 2.0;
        q = Quaternion((m10 - m01) / s, (m02 + m20) / s, (m12 + m21) / s, 0.25 * s);
    }

    return q.normalized();
}

Matrix4 Quaternion::toRotationMatrix4() const
{
    const auto q = normalized();
    Matrix<double> m(4, 4, 0.0);
    m[0][0] = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
    m[0][1] = 2.0 * (q.x * q.y - q.z * q.w);
    m[0][2] = 2.0 * (q.x * q.z + q.y * q.w);
    m[1][0] = 2.0 * (q.x * q.y + q.z * q.w);
    m[1][1] = 1.0 - 2.0 * (q.x * q.x + q.z * q.z);
    m[1][2] = 2.0 * (q.y * q.z - q.x * q.w);
    m[2][0] = 2.0 * (q.x * q.z - q.y * q.w);
    m[2][1] = 2.0 * (q.y * q.z + q.x * q.w);
    m[2][2] = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
    m[3][3] = 1.0;
    return Matrix4(std::move(m));
}
