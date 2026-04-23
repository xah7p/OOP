#pragma once

#include <memory>

class BaseVertexStructure {
public:
    BaseVertexStructure() = default;
    virtual ~BaseVertexStructure() = default;

    virtual double getX() const noexcept = 0;
    virtual double getY() const noexcept = 0;
    virtual double getZ() const noexcept = 0;
    virtual double getW() const noexcept = 0;

    virtual void setX(double value) noexcept = 0;
    virtual void setY(double value) noexcept = 0;
    virtual void setZ(double value) noexcept = 0;
    virtual void setW(double value) noexcept = 0;

    virtual std::shared_ptr<BaseVertexStructure> clone() const = 0;
};
