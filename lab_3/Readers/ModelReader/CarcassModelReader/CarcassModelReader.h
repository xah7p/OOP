#pragma once

#include "CarcassModelReaderImpl.h"
#include "ModelReader.h"
#include "Vertex.h"
#include "Edge.h"
#include <memory>
#include <vector>

class CarcassModelReader: public ModelReader {
private:
    std::shared_ptr<BaseCarcassModelReaderImpl> impl;
    std::vector<Vertex> vertixes;
    std::vector<Edge> edges;
public:
    CarcassModelReader() = delete;
    explicit CarcassModelReader(std::shared_ptr<BaseCarcassModelReaderImpl> impl);
    ~CarcassModelReader() = default;

    std::shared_ptr<std::vector<Vertex>> readVertixes();
    std::shared_ptr<std::vector<Edge>> readEdges();
};
