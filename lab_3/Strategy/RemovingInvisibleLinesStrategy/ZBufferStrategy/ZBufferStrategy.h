#pragma once

#include "BaseRemovingInvisibleLinesStrategy.h"
#include <array>
#include <vector>

class ZBufferStrategy: public BaseRemovingInvisibleLinesStrategy {
public:
    using Edge2D = std::pair<Vertex, Vertex>;
    ZBufferStrategy() = default;
    virtual ~ZBufferStrategy() override = default;

    virtual void prepare(std::vector<Edge2D>& visibleEdges, 
        const std::vector<Vertex>& vertices, 
        const std::vector<Edge>& edges,
        std::shared_ptr<BaseCameraEntity> camera) override;
private:
    struct Triangle
    {
        Vertex a;
        Vertex b;
        Vertex c;
    };

    static bool edgeExists(const std::vector<std::vector<size_t>>& adj, size_t a, size_t b);
    static std::vector<std::array<size_t, 4>> findQuadFaces(const std::vector<Edge>& edges, size_t vertexCount);
    static bool pointInTriangle(double px, double py, const Vertex& a, const Vertex& b, const Vertex& c, double& wa, double& wb, double& wc);
    static void appendVisibleRun(std::vector<Edge2D>& visibleEdges, const std::vector<Vertex>& run);
};