#pragma once

#include "BaseEntity.h"

#include <cstddef>
#include <memory>

class BaseBuilder {
protected:
    std::shared_ptr<BaseEntity> entity;
    size_t part = 0;

    virtual std::shared_ptr<BaseEntity> createEntity() = 0;

public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;

    std::shared_ptr<BaseEntity> getEntity();
};
