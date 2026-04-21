#pragma once

#include "Concepts.h"
#include "BaseRemovingInvisibleLinesStrategy.h"
#include "ZBufferStrategy.h"

#include <memory>

template <typename BaseConvertCoordinatesStrategy, typename DerivedConvertCoordinatesStrategy, typename... Args>
requires Derivative<DerivedConvertCoordinatesStrategy, BaseConvertCoordinatesStrategy> && Constructible<DerivedConvertCoordinatesStrategy, Args...>
class ConvertCoordinatesStrategyCreator
{
public:
    ConvertCoordinatesStrategyCreator() = default;
    ~ConvertCoordinatesStrategyCreator() = default;

    template <typename... CallArgs>
    static std::shared_ptr<BaseConvertCoordinatesStrategy> create(CallArgs &&...args);
};

using DefaultConvertCoordinatesStrategyCreator = ConvertCoordinatesStrategyCreator<BaseRemovingInvisibleLinesStrategy, ZBufferStrategy>;
