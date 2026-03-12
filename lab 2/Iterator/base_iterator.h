#pragma once

#include <memory>

class BaseIterator {
public:
    // explicit BaseIterator(const BaseIterator& other) = default;
    // explicit BaseIterator(BaseIterator&& other) noexcept = default;
    virtual ~BaseIterator() = default;
protected:
    virtual explicit operator bool() const = 0;
    virtual void checkContainer(int) const = 0;
    virtual void checkValidity(int) const = 0;
    std::weak_ptr<int> containerSize;
    int index = 0;
};
