#pragma once

#include "CarcassModelReaderImpl.h"

class BinCarcassModelReaderImpl: public BaseCarcassModelReaderImpl {
public:
    BinCarcassModelReaderImpl() = delete;
    explicit BinCarcassModelReaderImpl(const std::string& path);
    ~BinCarcassModelReaderImpl() override = default;

    std::shared_ptr<std::vector<Vertex>> readVertixes() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};
