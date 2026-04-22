#pragma once

#include "Concepts.h"
#include "LoadStrategy.h"

#include <memory>

template <typename BaseLoadStrategyStrategy, typename DerivedLoadStrategyStrategy, typename... Args>
requires Derivative<DerivedLoadStrategyStrategy, BaseLoadStrategyStrategy> && Constructible<DerivedLoadStrategyStrategy, Args...>
class LoadStrategyStrategyCreator
{
public:
    LoadStrategyStrategyCreator() = default;
    ~LoadStrategyStrategyCreator() = default;

    template <typename... CallArgs>
    static std::shared_ptr<LoadStrategy> create(CallArgs &&...args);
};

using CarcassModelLoadStrategyCreator = LoadStrategyStrategyCreator<LoadStrategy, CarcassModelLoadStrategy>;
using CameraLoadStrategyCreator = LoadStrategyStrategyCreator<LoadStrategy, CameraLoadStrategy>;

