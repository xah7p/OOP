#pragma once

#include "ModelDirector.h"

#include <memory>

class CarcassDirector: public ModelDirector {
public:
    CarcassDirector() = delete;
    explicit CarcassDirector(std::shared_ptr<BaseBuilder> builder);

    ~CarcassDirector() override = default;

    std::shared_ptr<BaseEntity> create() const override;
};
