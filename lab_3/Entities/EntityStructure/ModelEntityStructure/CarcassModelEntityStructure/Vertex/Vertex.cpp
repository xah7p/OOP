#include "Vertex.h"

#include <cmath>

Vertex::Vertex(double x, double y, double z) noexcept:
    x(x), y(y), z(z), w(1.0)
{ }

double Vertex::getX() const noexcept { return x; }
double Vertex::getY() const noexcept { return y; }
double Vertex::getZ() const noexcept { return z; }
double Vertex::getW() const noexcept { return w; }

void Vertex::setX(double value) noexcept { x = value; }
void Vertex::setY(double value) noexcept { y = value; }
void Vertex::setZ(double value) noexcept { z = value; }
void Vertex::setW(double value) noexcept { w = value; }

bool Vertex::equal(const Vertex& other) const noexcept { return *this == other; }
bool Vertex::notEqual(const Vertex& other) const noexcept { return !equal(other); }
bool Vertex::lessEqual(const Vertex& other) const noexcept { return (*this < other) || equal(other); }
bool Vertex::greaterEqual(const Vertex& other) const noexcept { return (*this > other) || equal(other); }
bool Vertex::less(const Vertex& other) const noexcept { return *this < other; }
bool Vertex::greater(const Vertex& other) const noexcept { return *this > other; }

Vertex& Vertex::add(const Vertex& other) noexcept
{
    x += other.x;
    y += other.y;
    z += other.z;
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
    x -= other.x;
    y -= other.y;
    z -= other.z;
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
    const auto dx = x - other.x;
    const auto dy = y - other.y;
    const auto dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void Vertex::transform(std::shared_ptr<TransformData> data) noexcept
{
    if (!data)
        return;

    Matrix<double> p(4, 1, 0.0);
    p[0][0] = x;
    p[1][0] = y;
    p[2][0] = z;
    p[3][0] = w;

    p = data->getMatrix().getMatrix() * p;
    x = p[0][0];
    y = p[1][0];
    z = p[2][0];
    w = p[3][0];
}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
    os << "(" << vertex.getX() << "; " << vertex.getY() << "; " << vertex.getZ() << ")";
    return os;
}