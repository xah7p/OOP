#pragma once

#include "BaseBuilder.h"
#include "BaseEntity.h"
#include "BaseReader.h"
#include "LoadRequest.h"
#include "BuilderSolution.h"

#include <memory>

class BaseDirector {
protected:
    std::shared_ptr<BaseBuilder> builder;
    std::shared_ptr<BuilderSolution> builderSolution;
    std::shared_ptr<BaseBuilder> createBuilder(
        const std::shared_ptr<BaseReader>& reader,
        EntityKind kind,
        EntityStructureKind structureKind) const;
public:
    BaseDirector() = default;
    explicit BaseDirector(std::shared_ptr<BuilderSolution> builderSolution);
    virtual ~BaseDirector() = default;

    virtual std::shared_ptr<BaseEntity> create() const = 0;
};
