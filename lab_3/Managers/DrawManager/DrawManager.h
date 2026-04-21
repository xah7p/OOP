#pragma once

#include "BaseDrawFactory.h"
#include "BaseManager.h"
#include "BasePainter.h"
#include <memory>

class DrawManager: public BaseManager {
private:
    std::shared_ptr<BasePainter> painter;
    std::shared_ptr<BaseDrawFactory> drawFactory;
public:
    DrawManager() = default;
    void setPainter(std::shared_ptr<BasePainter> painter);
    virtual ~DrawManager() override = default;

    void draw();
};