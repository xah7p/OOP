#pragma once

#include "BaseManager.h"
#include "TransformArgs.h"
#include <cstddef>

class TransformManager : public BaseManager {
public:
    TransformManager() = default;
    virtual ~TransformManager() = default;

    void moveObject(size_t id, const MoveArgs& args);
    void scaleObject(size_t id, const ScaleArgs& args);
    void rotateObject(size_t id, const RotateArgs& args);
};