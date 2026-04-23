#pragma once

#include "VisibleEntity.h"
#include "CarcassModelStructure.h"

class BaseModelEntity : public VisibleEntity {
public:
    virtual ~BaseModelEntity() override = default;
    virtual std::shared_ptr<CarcassModelStructure> accept() const = 0;
};