#pragma once

#include <memory>

class BaseSet
{
public:
    BaseSet() = default;
    explicit BaseSet(const BaseSet& other) = default;
    explicit BaseSet(BaseSet&& other) noexcept = default;
    
    virtual ~BaseSet() noexcept = default;
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
protected:
    virtual void _CheckValidity() const = 0;
    std::shared_ptr<int> setSizePtr;
};