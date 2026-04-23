#include "TransformData.h"

TransformData::TransformData() noexcept:
    kind(TransformKind::Move), matrix()
{ }

TransformData::TransformData(TransformKind kind, const Matrix4& matrix) noexcept:
    kind(kind), matrix(matrix)
{ }

TransformData::TransformData(TransformKind kind, Matrix4&& matrix) noexcept:
    kind(kind), matrix(std::move(matrix))
{ }

TransformData::TransformData(const MoveArgs& args) noexcept:
    kind(TransformKind::Move), matrix(Matrix4::fromMoveArgs(args))
{ }

TransformData::TransformData(const RotateArgs& args) noexcept:
    kind(TransformKind::Rotate), matrix(Matrix4::fromRotationArgs(args))
{ }

TransformData::TransformData(const ScaleArgs& args) noexcept:
    kind(TransformKind::Scale), matrix(Matrix4::fromScaleArgs(args))
{ }

TransformKind TransformData::getKind() const noexcept
{
    return kind;
}

const Matrix4& TransformData::getMatrix() const noexcept
{
    return matrix;
}

Matrix4& TransformData::getMatrix() noexcept
{
    return matrix;
}

bool TransformData::isMove() const noexcept
{
    return kind == TransformKind::Move;
}

bool TransformData::isRotate() const noexcept
{
    return kind == TransformKind::Rotate;
}

bool TransformData::isScale() const noexcept
{
    return kind == TransformKind::Scale;
}
