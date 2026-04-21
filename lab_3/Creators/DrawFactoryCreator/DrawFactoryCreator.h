#pragma once

#include <memory>
#include "Concepts.h"
#include "BaseDrawFactory.h"

class DrawFactoryCreator {
public:
    template<Derivative<BaseDrawFactory> TFactory, typename... Args>
    requires NotAbstract<TFactory> && Constructible<TFactory, Args...>
    static std::unique_ptr<BaseDrawFactory> create(Args&&... args) {
        return std::make_unique<TFactory>(std::forward<Args>(args)...);
    }
};

    