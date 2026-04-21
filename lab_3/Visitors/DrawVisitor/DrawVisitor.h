#pragma once

#include "BaseVisitor.h"
#include "BaseCameraEntity.h"
#include "BasePainter.h"
#include "BaseProjectionStrategy.h"
#include "BaseCenterStrategy.h"
#include "BaseRemovingInvisibleLinesStrategy.h"

class DrawVisitor: public BaseVisitor {
public:
    DrawVisitor() = delete;
    DrawVisitor(std::shared_ptr<BaseCameraEntity> activeCamera, 
        std::shared_ptr<BasePainter> painter,
        std::shared_ptr<BaseCenterStrategy> centerStrategy,
        std::shared_ptr<BaseProjectionStrategy> projectionStrategy,
        std::shared_ptr<BaseRemovingInvisibleLinesStrategy> removingInvisibleLinesStrategy);
    DrawVisitor(const DrawVisitor& other) = default;
    DrawVisitor(DrawVisitor&& other) = default;

    DrawVisitor& operator=(const DrawVisitor& other) = default;
    DrawVisitor& operator=(DrawVisitor&& other) = default;

    virtual ~DrawVisitor() override;

    virtual void visit(std::shared_ptr<CarcassModelStructure>) const override;
    virtual void visit(std::shared_ptr<CameraEntityStructure>) const override;
protected:
    std::shared_ptr<BasePainter> painter;
    std::shared_ptr<BaseCameraEntity> activeCamera;
    std::shared_ptr<BaseCenterStrategy> centerStrategy;
    std::shared_ptr<BaseProjectionStrategy> projectionStrategy;
    std::shared_ptr<BaseRemovingInvisibleLinesStrategy> removingInvisibleLinesStrategy;
    mutable std::vector<Vertex> collectedVertices;
    mutable std::vector<Edge> collectedEdges;
};