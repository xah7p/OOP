#include "Vertex.h"
#include "VertexStructureCreator.h"
#include "DefaultVertexStructure.h"

#include <cmath>

Vertex::Vertex() noexcept:
    structure(VertexStructureCreator::create<DefaultVertexStructure>(0.0, 0.0, 0.0, 1.0))
{ }

Vertex::Vertex(double x, double y, double z) noexcept:
    structure(VertexStructureCreator::create<DefaultVertexStructure>(x, y, z, 1.0))
{ }

Vertex::Vertex(const Vertex& other) noexcept:
    structure(other.structure ? other.structure->clone() : nullptr)
{ }

Vertex& Vertex::operator=(const Vertex& other) noexcept
{
    if (this != &other)
        structure = other.structure ? other.structure->clone() : nullptr;
    return *this;
}

double Vertex::getX() const noexcept { return structure ? structure->getX() : 0.0; }
double Vertex::getY() const noexcept { return structure ? structure->getY() : 0.0; }
double Vertex::getZ() const noexcept { return structure ? structure->getZ() : 0.0; }
double Vertex::getW() const noexcept { return structure ? structure->getW() : 0.0; }

void Vertex::setX(double value) noexcept { if (structure) structure->setX(value); }
void Vertex::setY(double value) noexcept { if (structure) structure->setY(value); }
void Vertex::setZ(double value) noexcept { if (structure) structure->setZ(value); }
void Vertex::setW(double value) noexcept { if (structure) structure->setW(value); }

std::partial_ordering Vertex::operator<=>(const Vertex& other) const noexcept
{
    if (auto cmp = getX() <=> other.getX(); cmp != 0)
        return cmp;
    if (auto cmp = getY() <=> other.getY(); cmp != 0)
        return cmp;
    if (auto cmp = getZ() <=> other.getZ(); cmp != 0)
        return cmp;
    return getW() <=> other.getW();
}

bool Vertex::operator==(const Vertex& other) const noexcept
{
    return getX() == other.getX()
        && getY() == other.getY()
        && getZ() == other.getZ()
        && getW() == other.getW();
}

bool Vertex::equal(const Vertex& other) const noexcept { return *this == other; }
bool Vertex::notEqual(const Vertex& other) const noexcept { return !equal(other); }
bool Vertex::lessEqual(const Vertex& other) const noexcept { return (*this < other) || equal(other); }
bool Vertex::greaterEqual(const Vertex& other) const noexcept { return (*this > other) || equal(other); }
bool Vertex::less(const Vertex& other) const noexcept { return *this < other; }
bool Vertex::greater(const Vertex& other) const noexcept { return *this > other; }

Vertex& Vertex::add(const Vertex& other) noexcept
{
    setX(getX() + other.getX());
    setY(getY() + other.getY());
    setZ(getZ() + other.getZ());
    return *this;
}

Vertex& Vertex::operator+=(const Vertex& other) noexcept
{
    return add(other);
}

Vertex Vertex::makeSum(const Vertex& other) const
{
    Vertex out(*this);
    out += other;
    return out;
}

Vertex Vertex::operator+(const Vertex& other) const
{
    return makeSum(other);
}

Vertex& Vertex::subtract(const Vertex& other) noexcept
{
    setX(getX() - other.getX());
    setY(getY() - other.getY());
    setZ(getZ() - other.getZ());
    return *this;
}

Vertex& Vertex::operator-=(const Vertex& other) noexcept
{
    return subtract(other);
}

Vertex Vertex::makeDifference(const Vertex& other) const
{
    Vertex out(*this);
    out -= other;
    return out;
}

Vertex Vertex::operator-(const Vertex& other) const
{
    return makeDifference(other);
}

double Vertex::distance(const Vertex& other) const noexcept
{
    const auto dx = getX() - other.getX();
    const auto dy = getY() - other.getY();
    const auto dz = getZ() - other.getZ();
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void Vertex::transform(std::shared_ptr<TransformData> data) noexcept
{
    if (!data)
        return;

    Matrix<double> p(4, 1, 0.0);
    p[0][0] = getX();
    p[1][0] = getY();
    p[2][0] = getZ();
    p[3][0] = getW();

    p = data->getMatrix().getMatrix() * p;
    setX(p[0][0]);
    setY(p[1][0]);
    setZ(p[2][0]);
    setW(p[3][0]);
}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
    os << "(" << vertex.getX() << "; " << vertex.getY() << "; " << vertex.getZ() << ")";
    return os;
}