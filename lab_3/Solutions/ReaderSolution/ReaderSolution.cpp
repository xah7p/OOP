#include "ReaderSolution.h"

#include <filesystem>

namespace
{
size_t makeKey(const std::string& extension, EntityKind kind)
{
    return (std::hash<std::string>{}(extension) << 1U) ^ static_cast<size_t>(kind);
}
}  

ReaderSolution::ReaderSolution(std::initializer_list<std::pair<size_t, CreateCreator>> list):
    callbacks()
{
    for (const auto& item : list)
        callbacks[item.first] = item.second;
}

bool ReaderSolution::registrate(const std::string& path, EntityKind kind, CreateCreator createfun)
{
    const auto key = makeKey(path, kind);
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
    const auto key = makeKey(extension, kind);
    if (!callbacks.contains(key))
        return nullptr;
    return callbacks.at(key)();
}
