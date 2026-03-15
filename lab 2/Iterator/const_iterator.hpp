#pragma once

#include "const_iterator.h"
#include "errors.h"
#include <compare>
#include <ctime>
#include <typeinfo>

template<ContainerElementType T>
typename ConstIterator<T>::reference ConstIterator<T>::operator*() const {
    return *getCurrentPointer();
}

template<ContainerElementType T>
typename ConstIterator<T>::pointer ConstIterator<T>::operator->() const {
    return getCurrentPointer();
}

template<ContainerElementType T>
ConstIterator<T>& ConstIterator<T>::operator++() noexcept {
    ++index;
    return *this;
}

template<ContainerElementType T>
ConstIterator<T> ConstIterator<T>::operator++(int) noexcept {
    auto tmp(*this);
    ++index;
    return tmp;
}

template<ContainerElementType T>
ConstIterator<T>& ConstIterator<T>::operator--() noexcept {
    --index;
    return *this;
}

template<ContainerElementType T>
ConstIterator<T> ConstIterator<T>::operator--(int) noexcept {
    auto tmp(*this);
    --index;
    return tmp;
}

template<ContainerElementType T>
ConstIterator<T>::operator bool() const noexcept {
    return !containerPtr.expired() && !containerSize.expired();
}

template<ContainerElementType T>
bool ConstIterator<T>::operator==(const ConstIterator<T>& other) const noexcept {
    return containerPtr.lock() == other.containerPtr.lock() && 
           containerSize.lock() == other.containerSize.lock() &&
           index == other.index;
}

template<ContainerElementType T>
inline std::partial_ordering ConstIterator<T>::operator<=>(const ConstIterator<T>& other) const noexcept {
    auto thisPtr = containerPtr.lock();  
    auto otherPtr = other.containerPtr.lock();
    auto thisSize = containerSize.lock(); 
    auto otherSize = other.containerSize.lock();
    if (!thisPtr || !otherPtr || !thisSize || !otherSize || *thisPtr != *otherPtr)
        return std::partial_ordering::unordered;
    return index <=> other.index;
}

template<ContainerElementType T>
ConstIterator<T>& ConstIterator<T>::operator+=(typename ConstIterator<T>::difference_type n) noexcept {
    index += n;
    return *this;
}

template<ContainerElementType T>
ConstIterator<T> ConstIterator<T>::operator+(typename ConstIterator<T>::difference_type n) const noexcept {
    ConstIterator<T> it(*this);
    it.index += n;
    return it;
}

template<ContainerElementType T>
ConstIterator<T> operator+(typename ConstIterator<T>::difference_type n, const ConstIterator<T>& it) noexcept {
    return it + n;
}

template<ContainerElementType T>
ConstIterator<T>& ConstIterator<T>::operator-=(typename ConstIterator<T>::difference_type n) noexcept {
    index -= n;
    return *this;
}   

template<ContainerElementType T>
ConstIterator<T> ConstIterator<T>::operator-(typename ConstIterator<T>::difference_type n) const noexcept {
    ConstIterator<T> it(*this);
    it.index -= n;
    return it;
}

template<ContainerElementType T>
typename ConstIterator<T>::difference_type ConstIterator<T>::operator-(const ConstIterator<T>& other) const noexcept {
    return index - other.index;
}

template<ContainerElementType T>
typename ConstIterator<T>::reference ConstIterator<T>::operator[](typename ConstIterator<T>::difference_type index) const {
    return *(*this + index);
}

template<ContainerElementType T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<T[]>& innerPtr,
                                const std::shared_ptr<int>& sizePtr,
                                int start_index) noexcept {
    containerPtr = innerPtr;
    containerSize = sizePtr;
    index = start_index;
}

template<ContainerElementType T>
typename ConstIterator<T>::pointer ConstIterator<T>::getCurrentPointer() const {
    checkExpiredContainer(__LINE__);
    checkIndex(__LINE__);
    auto rawPtr = containerPtr.lock().get();
    return rawPtr + index;
}

template<ContainerElementType T>
void ConstIterator<T>::checkExpiredContainer(int line) const {
    if (containerPtr.expired() || containerSize.expired()) {
        time_t t = time(nullptr);
        throw DeletedObjectError(__FILE__, typeid(*this).name(), line, ctime(&t));
    }
}

template<ContainerElementType T>
void ConstIterator<T>::checkIndex(int line) const {
    checkExpiredContainer(line);
    if (index >= *(containerSize.lock())) {
        time_t t = time(nullptr);
        throw InvalidIteratorIndexError(__FILE__, typeid(*this).name(), line, ctime(&t));
    }
}

