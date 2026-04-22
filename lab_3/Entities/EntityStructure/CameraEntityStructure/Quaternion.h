#pragma once

#include "Matrix4.h"
#include <cmath>

class Quaternion
{
private:
    double w;
    double x;
    double y;
    double z;
public:
    Quaternion() noexcept;
    Quaternion(double w, double x, double y, double z) noexcept;

    double getW() const noexcept;
    double getX() const noexcept;
    double getY() const noexcept;
    double getZ() const noexcept;

    Quaternion normalized() const noexcept;
    Quaternion conjugate() const noexcept;
    Quaternion inverse() const noexcept;
    Quaternion multiply(const Quaternion& other) const noexcept;
    Quaternion operator*(const Quaternion& other) const noexcept;

    static Quaternion fromRotationMatrix(const Matrix<double>& matrix) noexcept;

    Matrix4 toRotationMatrix4() const;
};