#pragma once

#include <cstddef>

using ManagerId = size_t;

namespace ManagerIds
{
    inline constexpr ManagerId Scene = 0;
    inline constexpr ManagerId Draw = 1;
    inline constexpr ManagerId Transform = 2;
    inline constexpr ManagerId Load = 3;
    inline constexpr ManagerId Camera = 4;
    inline constexpr ManagerId History = 5;
}