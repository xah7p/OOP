#pragma once

#include "vector"
#include "Vertex.h"
#include "Edge.h"
#include "TransformData.h"
#include <memory>

class CarcassModelStructure {
protected:
    Vertex center;
public:
    CarcassModelStructure() = default;
    virtual ~CarcassModelStructure() = default;
    
    virtual void setCenter(const Vertex& vertex) noexcept = 0;
    virtual void addVertex(const Vertex& vertex) = 0;
    virtual void addEdge(const Edge& edge) = 0;

    virtual void transform(std::shared_ptr<TransformData>) = 0;

    virtual Vertex getCenter() noexcept { return center; }
    virtual std::vector<Vertex> getVertices() const noexcept = 0;
    virtual std::vector<Edge> getEdges() const noexcept = 0;
    virtual std::shared_ptr<CarcassModelStructure> clone() const = 0;
};