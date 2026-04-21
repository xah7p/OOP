#pragma once

#include <utility>
#include <BaseCameraEntity.h>

class BaseRemovingInvisibleLinesStrategy
{
public:
    using Edge2D = std::pair<Vertex, Vertex>;
    BaseRemovingInvisibleLinesStrategy() = default;
    virtual ~BaseRemovingInvisibleLinesStrategy() = default;

    virtual void prepare(std::vector<Edge2D>& visibleEdges, 
        const std::vector<Vertex>& vertices, 
        const std::vector<Edge>& edges,
        std::shared_ptr<BaseCameraEntity> camera) = 0;
};