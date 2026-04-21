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
    removingInvisibleLinesStrategy(std::move(removingInvisibleLinesStrategy))
{ }

DrawVisitor::~DrawVisitor()
{
    if (!painter || !removingInvisibleLinesStrategy || collectedEdges.empty())
        return;

    std::vector<BaseRemovingInvisibleLinesStrategy::Edge2D> visibleEdges;
    removingInvisibleLinesStrategy->prepare(visibleEdges, collectedVertices, collectedEdges, activeCamera);
    for (const auto& edge : visibleEdges)
        painter->drawLine(edge.first, edge.second);
}

void DrawVisitor::visit(std::shared_ptr<CarcassModelStructure> structure) const
{
    if (!structure || !painter || !projectionStrategy || !centerStrategy || !removingInvisibleLinesStrategy)
        return;

    std::vector<Vertex> projected;
    std::shared_ptr<CameraEntityStructure> cameraStructure;
    if (activeCamera)
    {
        auto concreteCamera = std::dynamic_pointer_cast<CameraEntity>(activeCamera);
        if (concreteCamera)
            cameraStructure = concreteCamera->getStructure();
    }
    const double width = static_cast<double>(painter->getWidht());
    const double height = static_cast<double>(painter->getHeight());
    const double aspectRatio = (height > 1e-9) ? (width / height) : 1.0;
    projectionStrategy->prepare(projected, structure, cameraStructure, aspectRatio);
    centerStrategy->prepare(projected, painter->getWidht(), painter->getHeight());

    const size_t vertexOffset = collectedVertices.size();
    collectedVertices.insert(collectedVertices.end(), projected.begin(), projected.end());
    for (const auto& edge : structure->getEdges())
    {
        const size_t first = edge.getFirst();
        const size_t second = edge.getSecond();
        if (first >= projected.size() || second >= projected.size())
            continue;
        collectedEdges.emplace_back(first + vertexOffset, second + vertexOffset);
    }
}

void DrawVisitor::visit(std::shared_ptr<CameraEntityStructure> structure) const
{
    (void)structure;
}
