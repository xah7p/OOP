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
    using Key = std::pair<std::string, EntityKind>;
    using CallBackMap = std::map<Key, CreateCreator>;
private:
    CallBackMap callbacks;
public:
    ReaderSolution() = default;
    ReaderSolution(std::initializer_list<std::pair<Key, CreateCreator>>);
    ~ReaderSolution() = default;

    bool registrate(const std::string& path, EntityKind kind, CreateCreator createfun);

    std::unique_ptr<BaseReaderCreator> create(const std::string& path, EntityKind kind) const;
};