#pragma once

#include "BaseDirector.h"

class ModelDirector: public BaseDirector {
public:
    ModelDirector() = default;
    ~ModelDirector() override = default;

    virtual std::shared_ptr<BaseEntity> create() const = 0;
};
