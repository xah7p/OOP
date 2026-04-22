#pragma once

#include <memory>

class BaseEntity;

class BaseMemento {
public:
    virtual ~BaseMemento() = default;
    virtual std::unique_ptr<BaseEntity> get() = 0;
};
