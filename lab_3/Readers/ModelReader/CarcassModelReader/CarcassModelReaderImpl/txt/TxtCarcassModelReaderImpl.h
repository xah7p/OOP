#pragma once

#include "CarcassModelReaderImpl.h"

class TxtCarcassModelReaderImpl: public BaseCarcassModelReaderImpl {
public:
    TxtCarcassModelReaderImpl() = delete;
    explicit TxtCarcassModelReaderImpl(const std::string& path);
    ~TxtCarcassModelReaderImpl() override = default;

    std::shared_ptr<std::vector<Vertex>> readVertixes() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};
