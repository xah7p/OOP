#pragma once

#include "BaseRemovingInvisibleLinesStrategy.h"
#include "BaseCameraEntity.h"

class DrawAccumulator {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
public:
    DrawAccumulator() = default;
    ~DrawAccumulator() = default;

    void clear();
    void addObject(const std::vector<Vertex>& objectVertices, const std::vector<Edge>& objectEdges);
    std::vector<BaseRemovingInvisibleLinesStrategy::Edge2D> collectVisible(
        const std::shared_ptr<BaseRemovingInvisibleLinesStrategy>& strategy,
        const std::shared_ptr<BaseCameraEntity>& camera) const;
};
