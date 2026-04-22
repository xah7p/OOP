#pragma once

#include "BaseDirector.h"

#include <memory>

class CameraDirector: public BaseDirector {
public:
    CameraDirector() = delete;
    CameraDirector(
        const std::shared_ptr<BaseReader>& reader,
        EntityStructureKind structureKind,
        std::shared_ptr<BuilderSolution> builderSolution);

    ~CameraDirector() override = default;

    std::shared_ptr<BaseEntity> create() const override;
};
