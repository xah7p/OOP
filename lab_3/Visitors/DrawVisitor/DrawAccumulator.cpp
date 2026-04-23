#include "DrawAccumulator.h"

void DrawAccumulator::clear()
{
    vertices.clear();
    edges.clear();
}

void DrawAccumulator::addObject(const std::vector<Vertex>& objectVertices, const std::vector<Edge>& objectEdges)
{
    const size_t vertexOffset = vertices.size();
    vertices.insert(vertices.end(), objectVertices.begin(), objectVertices.end());

    for (const auto& edge : objectEdges)
    {
        const size_t first = edge.getFirst();
        const size_t second = edge.getSecond();
        if (first >= objectVertices.size() || second >= objectVertices.size())
            continue;
        edges.emplace_back(first + vertexOffset, second + vertexOffset);
    }
}

std::vector<BaseRemovingInvisibleLinesStrategy::Edge2D> DrawAccumulator::collectVisible(
    const std::shared_ptr<BaseRemovingInvisibleLinesStrategy>& strategy,
    const std::shared_ptr<BaseCameraEntity>& camera) const
{
    std::vector<BaseRemovingInvisibleLinesStrategy::Edge2D> visibleEdges;
    if (!strategy || edges.empty())
        return visibleEdges;

    strategy->prepare(visibleEdges, vertices, edges, camera);
    return visibleEdges;
}
