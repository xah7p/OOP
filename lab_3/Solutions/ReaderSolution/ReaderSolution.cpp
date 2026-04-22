#include "ReaderSolution.h"

#include <filesystem>

ReaderSolution::ReaderSolution(std::initializer_list<std::pair<Key, CreateCreator>> list):
    callbacks()
{
    for (const auto& item : list)
        callbacks[item.first] = item.second;
}

bool ReaderSolution::registrate(const std::string& path, EntityKind kind, CreateCreator createfun)
{
    const Key key = {path, kind};
    if (!createfun || callbacks.contains(key))
        return false;
    callbacks[key] = createfun;
    return true;
}

std::unique_ptr<BaseReaderCreator> ReaderSolution::create(const std::string& path, EntityKind kind) const
{
    auto extension = std::filesystem::path(path).extension().string();
    if (!extension.empty() && extension.front() == '.')
        extension = extension.substr(1);
    const Key key = {extension, kind};
    if (!callbacks.contains(key))
        return nullptr;
    return callbacks.at(key)();
}
