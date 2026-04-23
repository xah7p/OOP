#pragma once

#include "BaseManager.h"
#include "TransformArgs.h"
#include "EntityId.h"

class TransformManager : public BaseManager {
public:
    TransformManager() = default;
    virtual ~TransformManager() = default;

    void moveObject(EntityId id, const MoveArgs& args);
    void scaleObject(EntityId id, const ScaleArgs& args);
    void rotateObject(EntityId id, const RotateArgs& args);
};