#pragma once

#include "BaseBuilder.h"
#include "CarcassModelReader.h"

#include <memory>
#include <utility>

enum class ModelBuildPart : size_t {
    Vertixes = 0,
    Edges,
    Center
};

class BaseModelBuilder: public BaseBuilder {
protected:
    std::shared_ptr<CarcassModelReader> reader;
public:
    BaseModelBuilder() = delete;
    explicit BaseModelBuilder(std::shared_ptr<CarcassModelReader> reader);
    ~BaseModelBuilder() override = default;

    virtual bool buildVertixes() = 0;
    virtual bool buildEdges() = 0;
    virtual bool buildCenter() = 0;
};
