#pragma once

#include "Concepts.h"
#include "Memento.h"

#include <memory>

class MementoCreator {
public:
    template<Derivative<BaseMemento> TMemento, typename... Args>
    requires NotAbstract<TMemento>
    static std::unique_ptr<BaseMemento> create(Args&&... args) {
        return std::unique_ptr<BaseMemento>(new TMemento(std::forward<Args>(args)...));
    }
};
