#pragma once

#include <memory>

class BaseEntity;

class Memento {
private:
    std::unique_ptr<BaseEntity> entity;
public:
    Memento() = default;
    ~Memento();
    
    void set(std::unique_ptr<BaseEntity>);
    std::unique_ptr<BaseEntity> get();
};