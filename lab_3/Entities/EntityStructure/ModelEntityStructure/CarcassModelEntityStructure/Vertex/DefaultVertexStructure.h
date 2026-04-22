#pragma once

#include "BaseVertexStructure.h"

class DefaultVertexStructure final : public BaseVertexStructure {
private:
    double x;
    double y;
    double z;
    double w;
public:
    DefaultVertexStructure(double x, double y, double z, double w) noexcept;
    ~DefaultVertexStructure() override = default;

    double getX() const noexcept override;
    double getY() const noexcept override;
    double getZ() const noexcept override;
    double getW() const noexcept override;

    void setX(double value) noexcept override;
    void setY(double value) noexcept override;
    void setZ(double value) noexcept override;
    void setW(double value) noexcept override;

    std::shared_ptr<BaseVertexStructure> clone() const override;
};
