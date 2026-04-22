#pragma once

#include <memory>

#include "BaseDirector.h"
#include "BaseBuilder.h"
#include "BaseReader.h"
#include "LoadRequest.h"
#include "BuilderSolution.h"

class BaseDirectorCreator {
public:
    virtual ~BaseDirectorCreator() = default;
    virtual std::unique_ptr<BaseDirector> create(
        const std::shared_ptr<BaseReader>& reader,
        EntityStructureKind structureKind,
        const std::shared_ptr<BuilderSolution>& builderSolution) const = 0;
};

class CarcassDirectorCreator: public BaseDirectorCreator {
public:
    std::unique_ptr<BaseDirector> create(
        const std::shared_ptr<BaseReader>& reader,
        EntityStructureKind structureKind,
        const std::shared_ptr<BuilderSolution>& builderSolution) const override;
};

class CameraDirectorCreator: public BaseDirectorCreator {
public:
    std::unique_ptr<BaseDirector> create(
        const std::shared_ptr<BaseReader>& reader,
        EntityStructureKind structureKind,
        const std::shared_ptr<BuilderSolution>& builderSolution) const override;
};

class DirectorCreatorMaker {
public:
    template <typename TCreator>
    static std::unique_ptr<BaseDirectorCreator> createCreator()
    {
        return std::make_unique<TCreator>();
    }
};
