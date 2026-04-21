#pragma once

#include "TransformData.h"
#include <iostream>
#include <compare>
#include <ostream>
#include <memory>

class TransformState;

class Vertex final {
private:
    double x;
    double y;
    double z;
    double w;
public:
    Vertex() noexcept = default;
    Vertex(double x, double y, double z) noexcept;

    Vertex(const Vertex& other) noexcept = default;
    Vertex(Vertex&& other) noexcept = default;

    ~Vertex() noexcept = default;
    
    Vertex& operator=(const Vertex& other) noexcept = default;
    Vertex& operator=(Vertex&& other) noexcept = default;

    double getX() const noexcept;
    double getY() const noexcept;
    double getZ() const noexcept;
    double getW() const noexcept;

    void setX(double value) noexcept;
    void setY(double value) noexcept;
    void setZ(double value) noexcept;
    void setW(double value) noexcept;

    std::partial_ordering operator<=>(const Vertex& other) const noexcept = default;
    bool equal(const Vertex& other) const noexcept;
    bool notEqual(const Vertex& other) const noexcept;
    bool lessEqual(const Vertex& other) const noexcept;
    bool greaterEqual(const Vertex& other) const noexcept;
    bool less(const Vertex& other) const noexcept;
    bool greater(const Vertex& other) const noexcept;

    Vertex& add(const Vertex& other) noexcept;
    Vertex& operator+=(const Vertex& other) noexcept;

    Vertex makeSum(const Vertex& other) const;
    Vertex operator+(const Vertex& other) const;

    Vertex& subtract(const Vertex& other) noexcept;
    Vertex& operator-=(const Vertex& other) noexcept;

    Vertex makeDifference(const Vertex& other) const;
    Vertex operator-(const Vertex& other) const;

    double distance(const Vertex& other) const noexcept;
    void transform(std::shared_ptr<TransformData>) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Vertex& vertex);