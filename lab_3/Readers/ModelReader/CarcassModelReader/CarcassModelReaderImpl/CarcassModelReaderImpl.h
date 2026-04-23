#pragma once

#include "Vertex.h"
#include "Edge.h"
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class BaseCarcassModelReaderImpl {
protected:
    std::ifstream file;
public:
    BaseCarcassModelReaderImpl() = delete;
    explicit BaseCarcassModelReaderImpl(const std::string& path);
    virtual ~BaseCarcassModelReaderImpl() = default;

    virtual std::shared_ptr<std::vector<Vertex>> readVertixes() = 0;
    virtual std::shared_ptr<std::vector<Edge>> readEdges() = 0;
};