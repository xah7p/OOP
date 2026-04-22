#pragma once

#include "Concepts.h"
#include "BaseVertexStructure.h"

class VertexStructureCreator {
public:
    VertexStructureCreator() = delete;
    template<Derivative<BaseVertexStructure> TVertexStructure, typename... Args>
    requires NotAbstract<TVertexStructure> && Constructible<TVertexStructure, Args...>
    static std::shared_ptr<BaseVertexStructure> create(Args&&... args) {
        return std::make_shared<TVertexStructure>(std::forward<Args>(args)...);
    }
};
