#pragma once

#include "BaseMemento.h"

#include <memory>

class BaseEntity;
class CameraEntity;
class MementoCreator;

class CameraMemento final : public BaseMemento {
private:
    std::unique_ptr<BaseEntity> entity;

    void set(std::unique_ptr<BaseEntity> value);
    std::unique_ptr<BaseEntity> get() override;

    friend class CameraEntity;
public:
    explicit CameraMemento(const CameraEntity& value);
    ~CameraMemento() override;
};
