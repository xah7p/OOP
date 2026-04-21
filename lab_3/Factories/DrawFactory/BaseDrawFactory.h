#pragma once

#include <memory>
#include "BasePainter.h"

class BaseDrawFactory {
public: 
    BaseDrawFactory() = default;
    virtual ~BaseDrawFactory() = default;

    virtual std::shared_ptr<BasePainter> createPainter() = 0;
};