#pragma once

#include "CarcassModelStructure.h"
#include "vector"
#include "Vertex.h"
#include "Edge.h"

class MatrixCarcassModelStructure : public CarcassModelStructure {
private:
    std::vector<Vertex> vertixes;
    std::vector<std::vector<bool>> adjancencyMatrix;
    size_t sizeMatr = 0;
public:
    MatrixCarcassModelStructure() = default;
    virtual ~MatrixCarcassModelStructure() = default;
    
    virtual void setCenter(const Vertex& vertex) noexcept override;
    virtual void addVertex(const Vertex& vertex) override;
    virtual void addEdge(const Edge& edge) override;

    virtual void transform(std::shared_ptr<TransformData>) override;

    virtual Vertex getCenter() noexcept override;
    virtual std::vector<Vertex> getVertices() const noexcept override;
    virtual std::vector<Edge> getEdges() const noexcept override;
};