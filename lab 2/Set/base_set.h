#pragma once

#include <memory>

class BaseSet
{
public:
    BaseSet() = default;
    explicit BaseSet(const BaseSet& other) = default;
    BaseSet(BaseSet&& other) noexcept = default;
    
    virtual ~BaseSet() noexcept = default;
    virtual int power() const = 0;
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() noexcept = 0;
protected:
    virtual void checkExpired() const = 0;
    std::shared_ptr<int> setSizePtr;
};