#pragma once

#include "Vertex.h"
#include <vector>

class BaseCenterStrategy {
public:
    BaseCenterStrategy() = default;
    virtual ~BaseCenterStrategy() = default;

    virtual void prepare(std::vector<Vertex>& vertices, size_t width, size_t height) = 0;
};