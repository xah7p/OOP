#include "DefaultVertexStructure.h"

DefaultVertexStructure::DefaultVertexStructure(double x, double y, double z, double w) noexcept:
    x(x), y(y), z(z), w(w)
{ }

double DefaultVertexStructure::getX() const noexcept { return x; }
double DefaultVertexStructure::getY() const noexcept { return y; }
double DefaultVertexStructure::getZ() const noexcept { return z; }
double DefaultVertexStructure::getW() const noexcept { return w; }

void DefaultVertexStructure::setX(double value) noexcept { x = value; }
void DefaultVertexStructure::setY(double value) noexcept { y = value; }
void DefaultVertexStructure::setZ(double value) noexcept { z = value; }
void DefaultVertexStructure::setW(double value) noexcept { w = value; }

std::shared_ptr<BaseVertexStructure> DefaultVertexStructure::clone() const
{
    return std::make_shared<DefaultVertexStructure>(*this);
}
