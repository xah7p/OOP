#pragma once

#include "Matrix.h"
#include "TransformArgs.h"

class Matrix4 {
private:
    Matrix<double> inner;
public:
    Matrix4() noexcept;
    explicit Matrix4(const Matrix<double>& matrix);
    explicit Matrix4(Matrix<double>&& matrix);

    static Matrix4 fromMoveArgs(const MoveArgs& args) noexcept;
    static Matrix4 fromScaleArgs(const ScaleArgs& args) noexcept;
    static Matrix4 fromRotationArgs(const RotateArgs& args) noexcept;

    Matrix4 makeProduct(const Matrix4& other) const;
    Matrix4 operator*(const Matrix4& other) const;

    Matrix4& multiply(const Matrix4& other);
    Matrix4& operator*=(const Matrix4& other);
};