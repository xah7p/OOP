#pragma once

#include <cstddef>
#include <memory>
#include "BasePainter.h"
#include "BaseGraphicsScene.h"

class BaseDrawFactory {
public: 
    BaseDrawFactory() = default;
    virtual ~BaseDrawFactory() = default;

    virtual std::shared_ptr<BaseGraphicsScene> createGraphicsScene(size_t width, size_t height) = 0;
    virtual std::shared_ptr<BasePainter> createPainter(std::shared_ptr<BaseGraphicsScene> scene) = 0;
};