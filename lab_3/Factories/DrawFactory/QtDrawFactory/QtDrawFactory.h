#pragma once

#include <memory>
#include "BaseDrawFactory.h"

class QtDrawFactory: public BaseDrawFactory {
public: 
    QtDrawFactory() = default;
    virtual ~QtDrawFactory() override = default;

    virtual std::shared_ptr<BaseGraphicsScene> createGraphicsScene(size_t width, size_t height) override;
    virtual std::shared_ptr<BasePainter> createPainter(std::shared_ptr<BaseGraphicsScene> scene) override;
};