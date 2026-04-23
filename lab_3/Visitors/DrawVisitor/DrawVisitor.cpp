#include "DrawVisitor.h"
#include "CameraEntity.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseCameraEntity> activeCamera,
                         std::shared_ptr<BasePainter> painter,
                         std::shared_ptr<BaseCenterStrategy> centerStrategy,
                         std::shared_ptr<BaseProjectionStrategy> projectionStrategy,
                         std::shared_ptr<BaseRemovingInvisibleLinesStrategy> removingInvisibleLinesStrategy):
    painter(std::move(painter)),
    activeCamera(std::move(activeCamera)),
    centerStrategy(std::move(centerStrategy)),
    projectionStrategy(std::move(projectionStrategy)),
    removingInvisibleLinesStrategy(std::move(removingInvisibleLinesStrategy)),
    accumulator(std::make_unique<DrawAccumulator>())
{ }

void DrawVisitor::visit(std::shared_ptr<CarcassModelStructure> structure)
{
    if (!structure || !painter || !projectionStrategy || !centerStrategy || !removingInvisibleLinesStrategy)
        return;

    std::vector<Vertex> projected;
    std::shared_ptr<CameraEntityStructure> cameraStructure;
    if (activeCamera) {
        auto cameraEntity = std::dynamic_pointer_cast<CameraEntity>(activeCamera);
        if (cameraEntity)
            cameraStructure = cameraEntity->structure;
    }
    const double width = static_cast<double>(painter->getWidht());
    const double height = static_cast<double>(painter->getHeight());
    const double aspectRatio = (height > 1e-9) ? (width / height) : 1.0;
    projectionStrategy->prepare(projected, structure, cameraStructure, aspectRatio);
    centerStrategy->prepare(projected, painter->getWidht(), painter->getHeight());

    if (accumulator)
        accumulator->addObject(projected, structure->getEdges());
}

void DrawVisitor::visit(std::shared_ptr<CameraEntityStructure> structure)
{
    (void)structure;
}

DrawVisitor::~DrawVisitor() {
    const auto visibleEdges = accumulator->collectVisible(removingInvisibleLinesStrategy, activeCamera);
    for (const auto& edge : visibleEdges)
        painter->drawLine(edge.first, edge.second);
    accumulator->clear();
}
