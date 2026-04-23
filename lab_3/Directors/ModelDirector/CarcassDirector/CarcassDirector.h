#pragma once

#include "ModelDirector.h"

#include <memory>

class CarcassDirector: public ModelDirector {
public:
    CarcassDirector() = delete;
    CarcassDirector(
        const std::shared_ptr<BaseReader>& reader,
        EntityStructureKind structureKind,
        std::shared_ptr<BuilderSolution> builderSolution);

    ~CarcassDirector() override = default;

    std::shared_ptr<BaseEntity> create() const override;
};
