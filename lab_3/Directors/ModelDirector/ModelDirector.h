#pragma once

#include "BaseDirector.h"

class ModelDirector: public BaseDirector {
public:
    explicit ModelDirector(std::shared_ptr<BuilderSolution> builderSolution):
        BaseDirector(std::move(builderSolution))
    { }
    ~ModelDirector() override = default;

    virtual std::shared_ptr<BaseEntity> create() const = 0;
};
