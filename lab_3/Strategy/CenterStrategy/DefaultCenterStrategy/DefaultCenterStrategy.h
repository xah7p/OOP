#pragma once

#include "BaseCenterStrategy.h"

class DefaultCenterStrategy: public BaseCenterStrategy {
public:
    DefaultCenterStrategy() = default;
    virtual ~DefaultCenterStrategy() override = default;

    virtual void prepare(std::vector<Vertex>& vertices, size_t width, size_t height) override;
};