#pragma once
#define INIT_SET_CAPACITY 5

#include "set.h"
#include "errors.h"
#include <ctime>
#include <typeinfo>
#include <ranges>
#include <compare>
#include <iterator>
#include <algorithm>
#include <initializer_list>

template<ContainerElementType T>
Set<T>::Set(std::initializer_list<T> args) {
    setCapacity = args.size() > 0 ? static_cast<typename Set<T>::size_type>(args.size()) : INIT_SET_CAPACITY;
    setSizePtr = allocSharedSize(args.size());
    setInnerPtr = allocSharedInner(setCapacity);
    std::ranges::copy(args, setInnerPtr.get());
}

template<ContainerElementType T>
Set<T>::Set(const Set& other) {
    other.checkExpired();
    auto newSizePtr = allocSharedSize(other.size());
    auto newInnerPtr = allocSharedInner(other.setCapacity);
    std::ranges::copy(other.begin(), other.end(), newInnerPtr.get());
    setSizePtr = newSizePtr;
    setInnerPtr = newInnerPtr;
    setCapacity = other.setCapacity;
}

template<ContainerElementType T>
Set<T>::Set(Set&& other) noexcept : setCapacity(other.setCapacity),
                                    setInnerPtr(std::move(other.setInnerPtr)) {
    other.setCapacity = 0;
    setSizePtr = std::move(other.setSizePtr);
}

template<ContainerElementType T>
Set<T>& Set<T>::operator=(const Set& other) {
    if (this != &other) {
        other.checkExpired();
        auto newSizePtr = allocSharedSize(other.size());
        auto newInnerPtr = allocSharedInner(other.setCapacity);
        std::ranges::copy(other.begin(), other.end(), newInnerPtr.get());

        setSizePtr = newSizePtr;
        setInnerPtr = newInnerPtr;
        setCapacity = other.setCapacity;
    }
    return *this;
}

template<ContainerElementType T>
Set<T>& Set<T>::operator=(Set&& other) noexcept {
    if (this != &other) {
        setSizePtr = std::move(other.setSizePtr);
        setInnerPtr = std::move(other.setInnerPtr);
        setCapacity = other.setCapacity;
        other.setCapacity = 0;
    }
    return *this;
}

template<ContainerElementType T>
template<std::ranges::input_range R>
Set<T>::Set(R&& range) {
    auto n = static_cast<typename Set<T>::size_type>(std::ranges::size(range));
    if (n < 0) {
        time_t t = time(nullptr);
        throw InvalidCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    setCapacity = (n > 0 ? n : INIT_SET_CAPACITY);  
    setSizePtr = allocSharedSize(n);
    setInnerPtr = allocSharedInner(setCapacity);
    std::ranges::copy(range, setInnerPtr.get());
}

template<ContainerElementType T>
typename Set<T>::size_type Set<T>::size() const noexcept {
    checkExpired()
    return *setSizePtr;
}

template<ContainerElementType T>
bool Set<T>::isEmpty() const noexcept {
    checkExpired();
    return *setSizePtr == 0;
}

template<ContainerElementType T>
void Set<T>::clear() noexcept {
    checkExpired();
    *setSizePtr = 0;
}

template<ContainerElementType T>
typename Set<T>::iterator Set<T>::begin() const noexcept {
    return typename Set<T>::iterator(setInnerPtr, setSizePtr, 0);
}

template<ContainerElementType T>
typename Set<T>::iterator Set<T>::end() const noexcept {
    return begin() + *setSizePtr;
}

template<ContainerElementType T>
typename Set<T>::const_iterator Set<T>::cbegin() const noexcept {
    return begin();
}

template<ContainerElementType T>
typename Set<T>::const_iterator Set<T>::cend() const noexcept {
    return end();
}

template<ContainerElementType T>
typename Set<T>::reverse_iterator Set<T>::rbegin() const noexcept {
    return std::reverse_iterator(end());
}

template<ContainerElementType T>
typename Set<T>::reverse_iterator Set<T>::rend() const noexcept {
    return std::reverse_iterator(begin());
}

template<ContainerElementType T>
typename Set<T>::const_reverse_iterator Set<T>::crbegin() const noexcept {
    return std::reverse_iterator(end());
}

template<ContainerElementType T>
typename Set<T>::const_reverse_iterator Set<T>::crend() const noexcept {
    return std::reverse_iterator(begin());
}

template<ContainerElementType T>
bool Set<T>::add(const T& elem) noexcept {
    auto rawArrPtr = setInnerPtr.get();
    int index = find(elem);

    if (index < *setSizePtr && rawArrPtr[index] == elem)
        return false;
    
    if (*setSizePtr == setCapacity) {
        regrow();
        rawArrPtr = setInnerPtr.get();
    }

    for (int i = *setSizePtr; i > index ; i--) {
        rawArrPtr[i] = rawArrPtr[i - 1];
    }
    
    rawArrPtr[index] = elem;
    (*setSizePtr)++;
    return true;
}

template<ContainerElementType T>
bool Set<T>::erase(const T& elem) noexcept {
    auto rawArrPtr = setInnerPtr.get();
    int index = find(elem);
    if (index >= *setSizePtr || rawArrPtr[index] != elem)
        return false;
    for (int i = index; i < *setSizePtr - 1; i++) {
        rawArrPtr[i] = rawArrPtr[i + 1];
    }
    (*setSizePtr)--;
    return true;
}

template<ContainerElementType T>
bool Set<T>::isSubSetOf(const Set<T>& other) const noexcept {
    for (const auto& elem : *this) {
        if (!other.contains(elem))
            return false;
    }
    return true;
}

template<ContainerElementType T>
bool Set<T>::contains(const T& elem) const noexcept {
    int index = find(elem);
    return index < *setSizePtr && setInnerPtr.get()[index] == elem;
}

template<ContainerElementType T>
Set<T>& Set<T>::unity(const Set<T>& other) noexcept {
    for (const auto& elem : other) add(elem);
    return *this;
}

template<ContainerElementType T>
Set<T>& Set<T>::operator+=(const Set<T>& other) noexcept {
    return unity(other);
}

template<ContainerElementType T>
Set<T>& Set<T>::operator|=(const Set<T>& other) noexcept {
    return unity(other);
}

template<ContainerElementType T>
Set<T> Set<T>::operator+(const Set<T>& other) const {
    Set<T> newSet(*this);
    return newSet.unity(other);
}

template<ContainerElementType T>
Set<T> Set<T>::operator|(const Set<T>& other) const {
    return *this + other;
}

template<ContainerElementType T>
Set<T>& Set<T>::difference(const Set<T>& other) noexcept {
    for (const auto& elem : other) erase(elem);
    return *this;
}

template<ContainerElementType T>
Set<T>& Set<T>::operator-=(const Set<T>& other) noexcept {
    return difference(other);
}

template<ContainerElementType T>
Set<T>& Set<T>::operator/=(const Set<T>& other) noexcept {
    return difference(other);
}

template<ContainerElementType T>
Set<T> Set<T>::operator-(const Set<T>& other) const {
    Set<T> newSet(*this);
    return newSet.difference(other);
}

template<ContainerElementType T>
Set<T> Set<T>::operator/(const Set<T>& other) const {
    return *this - other;
}

template<ContainerElementType T>
Set<T>& Set<T>::intersection(const Set<T>& other) {
    Set<T> tmpSet(*this);
    for (const auto& elem : tmpSet) {
        if (!other.contains(elem))
            erase(elem);
    }
    return *this; 
}

template<ContainerElementType T>
Set<T>& Set<T>::operator*=(const Set<T>& other) {
    return intersection(other);
}

template<ContainerElementType T>
Set<T>& Set<T>::operator&=(const Set<T>& other) {
    return intersection(other);
}

template<ContainerElementType T>
Set<T> Set<T>::operator*(const Set<T>& other) const {
    Set<T> newSet(*this);
    return newSet.intersection(other);
}

template<ContainerElementType T>
Set<T> Set<T>::operator&(const Set<T>& other) const {
    return *this * other;
}

template<ContainerElementType T>
Set<T>& Set<T>::symmetric_difference(const Set<T>& other) {
    Set<T> tmpSet(*this);
    unity(other);
    for (const auto& elem : tmpSet)
        if (other.contains(elem))
            erase(elem);
    return *this;
}

template<ContainerElementType T>
Set<T>& Set<T>::operator^=(const Set<T>& other) noexcept {
    return symmetric_difference(other);
}

template<ContainerElementType T>
Set<T> Set<T>::operator^(const Set<T>& other) const {
    Set<T> newSet(*this);
    return newSet.symmetric_difference(other);
}

template<ContainerElementType T>
bool Set<T>::operator==(const Set<T>& other) const noexcept {
    if (*setSizePtr != *other.setSizePtr)
        return false;
    return std::ranges::equal(*this, other);
}

template<ContainerElementType T>
std::strong_ordering Set<T>::operator<=>(const Set<T>& other) const noexcept {
    auto it1 = begin();
    auto it2 = other.begin();
    auto end1 = end();
    auto end2 = other.end();

    for ( ; it1 != end1 && it2 != end2; ++it1, ++it2) {
        if (*it1 < *it2)
            return std::strong_ordering::less;
        if (*it2 < *it1)
            return std::strong_ordering::greater;
    }

    if (it1 == end1 && it2 == end2)
        return std::strong_ordering::equal;
    if (it1 == end1)
        return std::strong_ordering::less;
    return std::strong_ordering::greater;
}

template<ContainerElementType T>
Set<T>::operator bool() const noexcept {
    return setSizePtr && setInnerPtr;
}

template<ContainerElementType T>
std::ostream& operator<<(std::ostream& os, const Set<T>& s) {
    os << "{ ";
    for (const auto& elem : s) 
        os << elem << " ";
    os << "}";
    return os;
}

template<ContainerElementType T>
int Set<T>::find(const T& elem) const noexcept {
    auto rawArrPtr = setInnerPtr.get();
    int left = 0;
    int right = *setSizePtr;
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (rawArrPtr[middle] < elem)
            left = middle + 1;
        else 
            right = middle;
    }
    return left;
}

template<ContainerElementType T>
void Set<T>::regrow() {
    typename Set<T>::size_type newCapacity = setCapacity > 0 ? setCapacity * 2 : INIT_SET_CAPACITY;
    auto newSetInnerPtr = allocSharedInner(newCapacity);
    std::ranges::copy(begin(), end(), newSetInnerPtr.get());
    
    setCapacity = newCapacity;
    setInnerPtr = std::move(newSetInnerPtr);
}

template<ContainerElementType T>
std::shared_ptr<typename Set<T>::size_type> Set<T>::allocSharedSize(typename Set<T>::size_type size) const {
    try {
        return std::make_shared<typename Set<T>::size_type>(size);
    }
    catch (const std::bad_alloc&) {
        time_t t = time(nullptr);
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
}

template<ContainerElementType T>
std::shared_ptr<T[]> Set<T>::allocSharedInner(typename Set<T>::size_type capacity) const {
    if (capacity < 0) {
        time_t t = time(nullptr);
        throw InvalidCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }

    try {
        auto innerPtr = std::make_shared<T[]>(capacity);
        return innerPtr;
    }
    catch (const std::bad_alloc&) {
        time_t t = time(nullptr);
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
}

template<ContainerElementType T>
void Set<T>::checkExpired() const {
    if (!setSizePtr || !setInnerPtr) {
        time_t t = time(nullptr);
        throw DeletedObjectError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
}
