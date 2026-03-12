#pragma once

#include "const_iterator.h"
#include "errors.h"
#include <compare>
#include <ctime>
#include <typeinfo>

template<typename T>
typename ConstIterator<T>::reference ConstIterator<T>::operator*() const {
    checkValidity(__LINE__);
    return *getCurrentPointer();
}

template<typename T>
typename ConstIterator<T>::pointer ConstIterator<T>::operator->() const {
    checkValidity(__LINE__);
    return getCurrentPointer();
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator++() {
    checkContainer(__LINE__); // убрать исключения
    if (index < *(containerSize.lock()))
        index++;
    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) {
    checkContainer(__LINE__);
    ConstIterator<T> tmp(*this);
    ++(*this);
    return tmp;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator--() {
    checkContainer(__LINE__);
    if (index != 0)
        index--;
    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator--(int) {
    checkContainer(__LINE__);
    ConstIterator<T> tmp(*this);
    --(*this);
    return tmp;
}

template<typename T>
ConstIterator<T>::operator bool() const {
    return !containerPtr.expired() && !containerSize.expired();
}

template<typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T>& other) const noexcept {
    return containerPtr.lock() == other.containerPtr.lock() && 
           containerSize.lock() == other.containerSize.lock() &&
           index == other.index;
}

template<typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T>& other) const noexcept {
    return !(*this == other);
}

template<typename T>
std::strong_ordering ConstIterator<T>::operator<=>(const ConstIterator<T>& other) const {
    auto thisPtr = containerPtr.lock();  
    auto otherPtr = other.containerPtr.lock();
    auto thisSize = containerSize.lock(); 
    auto otherSize = other.containerSize.lock();

    if (!thisPtr || !otherPtr || !thisSize || !otherSize) {
        time_t t = time(nullptr);
        throw DeletedObjectError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }

    if (thisPtr != otherPtr) {
        time_t t = time(nullptr); 
        throw ComparingDifferentIterators(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    return index <=> other.index;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator+=(typename ConstIterator<T>::difference_type n) {
    checkContainer(__LINE__);
    if (index + n <= *(containerSize.lock()))
        index += n;
    return *this;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator-=(typename ConstIterator<T>::difference_type n) {
    checkContainer(__LINE__);
    if (index >= n)
        index -= n;
    return *this;
}   

template<typename T>
ConstIterator<T> ConstIterator<T>::operator+(typename ConstIterator<T>::difference_type n) const {
    ConstIterator<T> it(*this);
    it += n;
    return it;
}

template<typename T>
ConstIterator<T> operator+(typename ConstIterator<T>::difference_type n, const ConstIterator<T>& it) {
    return it + n;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator-(typename ConstIterator<T>::difference_type n) const {
    ConstIterator<T> it(*this);
    it -= n;
    return it;
}

template<typename T>
typename ConstIterator<T>::difference_type ConstIterator<T>::operator-(const ConstIterator<T>& other) const {
    return index - other.index;
}

template<typename T>
typename ConstIterator<T>::reference ConstIterator<T>::operator[](typename ConstIterator<T>::difference_type index) const {
    return *(*this + index);
}

template<typename T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<T[]>& innerPtr,
                                const std::shared_ptr<int>& sizePtr,
                                int start_index) : BaseIterator{}, containerPtr(innerPtr) {
    containerSize = sizePtr;
    index = start_index;
}


template<typename T>
typename ConstIterator<T>::pointer ConstIterator<T>::getCurrentPointer() const {
    auto rawPtr = containerPtr.lock().get();
    return rawPtr + index;
}

template<typename T>
void ConstIterator<T>::checkContainer(int line) const {
    if (containerPtr.expired() || containerSize.expired()) {
        time_t t = time(nullptr);
        throw DeletedObjectError(__FILE__, typeid(*this).name(), line, ctime(&t));
    }
}

template<typename T>
void ConstIterator<T>::checkValidity(int line) const {
    checkContainer(line);
    if (index >= *(containerSize.lock())) {
        time_t t = time(nullptr);
        throw InvalidIteratorIndex(__FILE__, typeid(*this).name(), line, ctime(&t));
    }
}

