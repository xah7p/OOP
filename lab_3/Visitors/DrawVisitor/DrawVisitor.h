#pragma once

#include "BaseVisitor.h"
#include "BaseCameraEntity.h"
#include "BasePainter.h"
#include "BaseProjectionStrategy.h"
#include "BaseCenterStrategy.h"
#include "BaseRemovingInvisibleLinesStrategy.h"
#include "DrawAccumulator.h"

class DrawVisitor: public BaseVisitor {
public:
    DrawVisitor() = delete;
    DrawVisitor(std::shared_ptr<BaseCameraEntity> activeCamera, 
        std::shared_ptr<BasePainter> painter,
        std::shared_ptr<BaseCenterStrategy> centerStrategy,
        std::shared_ptr<BaseProjectionStrategy> projectionStrategy,
        std::shared_ptr<BaseRemovingInvisibleLinesStrategy> removingInvisibleLinesStrategy);
    DrawVisitor(const DrawVisitor& other) = delete;
    DrawVisitor(DrawVisitor&& other) = default;

    DrawVisitor& operator=(const DrawVisitor& other) = delete;
    DrawVisitor& operator=(DrawVisitor&& other) = default;

    virtual ~DrawVisitor() override;

    virtual void visit(std::shared_ptr<CarcassModelStructure>) override;
    virtual void visit(std::shared_ptr<CameraEntityStructure>) override;
protected:
    std::shared_ptr<BasePainter> painter;
    std::shared_ptr<BaseCameraEntity> activeCamera;
    std::shared_ptr<BaseCenterStrategy> centerStrategy;
    std::shared_ptr<BaseProjectionStrategy> projectionStrategy;
    std::shared_ptr<BaseRemovingInvisibleLinesStrategy> removingInvisibleLinesStrategy;
    std::unique_ptr<DrawAccumulator> accumulator;
};