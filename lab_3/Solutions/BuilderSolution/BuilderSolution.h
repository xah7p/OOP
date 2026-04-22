#pragma once

#include "LoadRequest.h"
#include "BuilderCreator.h"

#include <map>
#include <memory>
#include <utility>

class BuilderSolution {
public:
    using Key = std::pair<EntityKind, EntityStructureKind>;
    using CreateCreator = std::unique_ptr<BaseBuilderCreator>(*)();
    using CallBackMap = std::map<Key, CreateCreator>;
private:
    CallBackMap callbacks;
public:
    BuilderSolution() = default;
    ~BuilderSolution() = default;

    bool registrate(EntityKind kind, EntityStructureKind structureKind, CreateCreator createfun);
    std::unique_ptr<BaseBuilderCreator> create(EntityKind kind, EntityStructureKind structureKind) const;
};
