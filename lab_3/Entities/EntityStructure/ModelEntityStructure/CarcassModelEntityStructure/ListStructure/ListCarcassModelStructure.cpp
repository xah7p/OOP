#include "ListCarcassModelStructure.h"

void ListCarcassModelStructure::setCenter(const Vertex& vertex) noexcept
{
    center = vertex;
}

void ListCarcassModelStructure::addVertex(const Vertex& vertex)
{
    vertixes.push_back(vertex);
}

void ListCarcassModelStructure::addEdge(const Edge& edge)
{
    edges.push_back(edge);
}

void ListCarcassModelStructure::transform(std::shared_ptr<TransformData> data)
{
    center.transform(data);
    for (auto& v : vertixes)
        v.transform(data);
}

Vertex ListCarcassModelStructure::getCenter() noexcept
{
    return center;
}

std::vector<Vertex> ListCarcassModelStructure::getVertices() const noexcept
{
    return vertixes;
}

std::vector<Edge> ListCarcassModelStructure::getEdges() const noexcept
{
    return edges;
}
