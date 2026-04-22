#pragma once

#include "BaseMemento.h"

#include <memory>

class BaseEntity;
class CarcassModelEntity;
class MementoCreator;

class CarcassModelMemento final : public BaseMemento {
private:
    std::unique_ptr<BaseEntity> entity;

    void set(std::unique_ptr<BaseEntity> value);
    std::unique_ptr<BaseEntity> get() override;

    friend class CarcassModelEntity;
public:
    explicit CarcassModelMemento(const CarcassModelEntity& value);
    ~CarcassModelMemento() override;
};
