#pragma once

#include <initializer_list>
#include <map>
#include <memory>
#include <utility>
#include "ManagerCreator.h"
#include "ManagerId.h"

class ManagerSolution {
public: 
    using CreateCreator = std::unique_ptr<ManagerCreator>(*)();
    using CallBackMap = std::map<size_t, CreateCreator>;
private:
    CallBackMap callbacks;
public:
    ManagerSolution() = default;
    ManagerSolution(std::initializer_list<std::pair<size_t, CreateCreator>>);
    ~ManagerSolution() = default;

    bool registrate(ManagerId id, CreateCreator createfun);

    std::unique_ptr<ManagerCreator> create(ManagerId id) const;
};