#pragma once

#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include "LoadRequest.h"
#include "ReaderCreator.h"

class ReaderSolution {
public: 
    using CreateCreator = std::unique_ptr<BaseReaderCreator>(*)();
    using CallBackMap = std::map<size_t, CreateCreator>;
private:
    CallBackMap callbacks;
public:
    ReaderSolution() = default;
    ReaderSolution(std::initializer_list<std::pair<size_t, CreateCreator>>);
    ~ReaderSolution() = default;

    bool registrate(const std::string& path, EntityKind kind, CreateCreator createfun);

    std::unique_ptr<BaseReaderCreator> create(const std::string& path, EntityKind kind) const;
};