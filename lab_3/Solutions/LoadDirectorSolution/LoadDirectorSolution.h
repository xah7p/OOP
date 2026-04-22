#pragma once

#include "LoadRequest.h"
#include "DirectorCreator.h"

#include <initializer_list>
#include <map>
#include <memory>
#include <utility>

class LoadDirectorSolution {
private:
    using CreateCreator = std::unique_ptr<BaseDirectorCreator>(*)();
    using CallBackMap = std::map<EntityKind, CreateCreator>;
    CallBackMap callbacks;
public:
    LoadDirectorSolution() = default;
    LoadDirectorSolution(std::initializer_list<std::pair<EntityKind, CreateCreator>>);

    ~LoadDirectorSolution() = default;

    bool registrate(EntityKind kind, CreateCreator createfun);
    std::unique_ptr<BaseDirectorCreator> create(EntityKind kind) const;
};