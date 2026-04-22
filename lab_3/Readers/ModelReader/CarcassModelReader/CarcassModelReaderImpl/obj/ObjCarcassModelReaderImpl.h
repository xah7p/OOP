#pragma once

#include "CarcassModelReaderImpl.h"

class ObjCarcassModelReaderImpl: public BaseCarcassModelReaderImpl {
public:
    ObjCarcassModelReaderImpl() = delete;
    explicit ObjCarcassModelReaderImpl(const std::string& path);
    ~ObjCarcassModelReaderImpl() override = default;

    std::shared_ptr<std::vector<Vertex>> readVertixes() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};
