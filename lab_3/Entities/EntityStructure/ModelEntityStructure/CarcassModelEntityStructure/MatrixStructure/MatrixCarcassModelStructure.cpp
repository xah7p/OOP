#include "MatrixCarcassModelStructure.h"

void MatrixCarcassModelStructure::setCenter(const Vertex& vertex) noexcept
{
    center = vertex;
}

void MatrixCarcassModelStructure::addVertex(const Vertex& vertex)
{
    vertixes.push_back(vertex);
    ++sizeMatr;
    for (auto& row : adjancencyMatrix)
        row.push_back(false);
    adjancencyMatrix.emplace_back(sizeMatr, false);
}

void MatrixCarcassModelStructure::addEdge(const Edge& edge)
{
    if (edge.getFirst() >= sizeMatr || edge.getSecond() >= sizeMatr)
        return;
    adjancencyMatrix[edge.getFirst()][edge.getSecond()] = true;
    adjancencyMatrix[edge.getSecond()][edge.getFirst()] = true;
}

void MatrixCarcassModelStructure::transform(std::shared_ptr<TransformData> data)
{
    center.transform(data);
    for (auto& v : vertixes)
        v.transform(data);
}

Vertex MatrixCarcassModelStructure::getCenter() noexcept
{
    return center;
}

std::vector<Vertex> MatrixCarcassModelStructure::getVertices() const noexcept
{
    return vertixes;
}

std::vector<Edge> MatrixCarcassModelStructure::getEdges() const noexcept
{
    std::vector<Edge> edges;
    for (size_t i = 0; i < sizeMatr; ++i)
    {
        for (size_t j = i + 1; j < sizeMatr; ++j)
        {
            if (adjancencyMatrix[i][j])
                edges.emplace_back(i, j);
        }
    }
    return edges;
}

std::shared_ptr<CarcassModelStructure> MatrixCarcassModelStructure::clone() const
{
    return std::make_shared<MatrixCarcassModelStructure>(*this);
}
