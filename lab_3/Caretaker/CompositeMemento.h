#pragma once

#include "BaseMemento.h"

#include <memory>

class BaseEntity;
class Composite;
class MementoCreator;

class CompositeMemento final : public BaseMemento {
private:
    friend class Composite;
    std::unique_ptr<BaseEntity> entity;
    
    void set(std::unique_ptr<BaseEntity> value);
    std::unique_ptr<BaseEntity> get() override;

public:
    explicit CompositeMemento(const Composite& value);
    ~CompositeMemento() override;
};
