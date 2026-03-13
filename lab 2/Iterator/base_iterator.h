#pragma once

#include <memory>

class BaseIterator {
public:
    BaseIterator() = default;
    explicit BaseIterator(const BaseIterator& other) = default;
    explicit BaseIterator(BaseIterator&& other) noexcept = default;
    BaseIterator& operator=(const BaseIterator& other) = default;
    BaseIterator& operator=(BaseIterator&& other) noexcept = default;

    virtual ~BaseIterator() = default;
protected:
    virtual explicit operator bool() const = 0;
    virtual void checkExpiredContainer(int) const = 0;
    virtual void checkIndex(int) const = 0;
    
    std::weak_ptr<int> containerSize;
    int index = 0;
};
