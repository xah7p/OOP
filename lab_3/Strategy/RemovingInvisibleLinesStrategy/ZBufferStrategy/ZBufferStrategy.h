#pragma once

#include "BaseRemovingInvisibleLinesStrategy.h"

class ZBufferStrategy: public BaseRemovingInvisibleLinesStrategy {
public:
    using Edge2D = std::pair<Vertex, Vertex>;
    ZBufferStrategy() = default;
    virtual ~ZBufferStrategy() override = default;

    virtual void prepare(std::vector<Edge2D>& visibleEdges, 
        const std::vector<Vertex>& vertices, 
        const std::vector<Edge>& edges,
        std::shared_ptr<BaseCameraEntity> camera) override;
};