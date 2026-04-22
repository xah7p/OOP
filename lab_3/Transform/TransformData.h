#pragma once

#include "TransformKind.h"
#include "TransformArgs.h"
#include "Matrix4.h"

class TransformData {
private:
    TransformKind kind;
    Matrix4 matrix;
public:
    TransformData() noexcept;
    TransformData(TransformKind kind, const Matrix4 &matrix) noexcept;
    TransformData(TransformKind kind, Matrix4 &&matrix) noexcept;

    TransformData(const MoveArgs &args) noexcept;
    TransformData(const RotateArgs &args) noexcept;
    TransformData(const ScaleArgs &args) noexcept;

    TransformKind getKind() const noexcept;
    const Matrix4 &getMatrix() const noexcept;
    Matrix4 &getMatrix() noexcept;

    [[nodiscard]] bool isMove() const noexcept;
    [[nodiscard]] bool isRotate() const noexcept;
    [[nodiscard]] bool isScale() const noexcept;
};