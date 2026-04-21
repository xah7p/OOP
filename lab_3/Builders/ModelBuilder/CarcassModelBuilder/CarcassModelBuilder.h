#pragma once

#include "BaseModelBuilder.h"
#include "CarcassModelEntity.h"
#include "CarcassModelStructure.h"

#include <memory>

class CarcassModelBuilder: public BaseModelBuilder {
private:
    std::shared_ptr<CarcassModelStructure> structure;
protected:
    std::shared_ptr<BaseEntity> createProduct() override;
public:
    CarcassModelBuilder() = delete;
    CarcassModelBuilder(std::shared_ptr<CarcassModelReader> reader, std::shared_ptr<CarcassModelStructure> structure);

    ~CarcassModelBuilder() override = default;

    bool buildVertixes() override;
    bool buildEdges() override;
    bool buildCenter() override;
};
