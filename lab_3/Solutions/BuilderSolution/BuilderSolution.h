#pragma once

#include "LoadRequest.h"
#include "BuilderCreator.h"
#include "BaseBuilder.h"
#include "BaseReader.h"
#include "CarcassModelReader.h"
#include "DefaultCameraReader.h"
#include "CarcassModelStructure.h"

#include <initializer_list>
#include <cstddef>
#include <map>
#include <memory>
#include <utility>

class BuilderSolution {
private:
    using CreateCreator = std::unique_ptr<BaseBuilderCreator>(*)();
    using CallBackMap = std::map<size_t, CreateCreator>;
    CallBackMap callbacks;
public:
    BuilderSolution() = default;
    BuilderSolution(std::initializer_list<std::pair<size_t, CreateCreator>>);
    ~BuilderSolution() = default;

    bool registrate(EntityKind kind, EntityStructureKind structureKind, CreateCreator createfun);
    std::unique_ptr<BaseBuilderCreator> create(EntityKind kind, EntityStructureKind structureKind) const;
};