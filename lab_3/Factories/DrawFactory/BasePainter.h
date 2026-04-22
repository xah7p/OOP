#pragma once

#include <cstddef>
#include "Vertex.h"

class BasePainter {
protected:
    size_t width;
    size_t height;
public:
    BasePainter() = default;
    virtual ~BasePainter() = default;

    virtual void drawLine(const Vertex& vertex1, const Vertex& vertex2);
    virtual void clear() = 0;

    virtual void setWidht(size_t width) const noexcept = 0;
    virtual void setHeight(size_t height) const noexcept = 0;

    virtual size_t getWidht() const noexcept = 0;
    virtual size_t getHeight() const noexcept = 0;
};