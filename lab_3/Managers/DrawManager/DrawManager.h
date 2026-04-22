#pragma once

#include "BaseManager.h"
#include "BasePainter.h"
#include <memory>

class DrawManager: public BaseManager {
private:
    std::shared_ptr<BasePainter> painter;
public:
    DrawManager() = default;
    virtual ~DrawManager() override = default;

    void setPainter(std::shared_ptr<BasePainter> painter);
    void draw();
};