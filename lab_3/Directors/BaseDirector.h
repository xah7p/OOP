#pragma once

#include "BaseBuilder.h"
#include "BaseEntity.h"

#include <memory>

class BaseDirector {
protected:
    std::shared_ptr<BaseBuilder> builder;
public:
    BaseDirector() = default;
    virtual ~BaseDirector() = default;

    virtual std::shared_ptr<BaseEntity> create() const = 0;
};
