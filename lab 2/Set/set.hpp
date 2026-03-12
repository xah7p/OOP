#pragma once
#define INIT_SET_CAPACITY 5

#include "set.h"
#include "errors.h"
#include <ctime>
#include <typeinfo>
#include <ranges>
#include <algorithm>

template<typename T>
Set<T>::Set() : setCapacity(INIT_SET_CAPACITY) {
    setSizePtr = _SetAllocateSize(0);
    setInnerPtr = _SetAllocateArray(setCapacity);
}

template<typename T>
Set<T>::Set(size_type capacity) {
    setCapacity = capacity > 0 ? capacity : INIT_SET_CAPACITY;
    setSizePtr = _SetAllocateSize(0);
    setInnerPtr = _SetAllocateArray(setCapacity);
}

template<typename T>
Set<T>::Set(std::initializer_list<T> args) {
    setCapacity = args.size() > 0 ? static_cast<typename Set<T>::size_type>(args.size()) : INIT_SET_CAPACITY;
    setSizePtr = _SetAllocateSize(args.size());
    setInnerPtr = _SetAllocateArray(setCapacity);
    std::ranges::copy(args, setInnerPtr.get());
}

template<typename T>
Set<T>::Set(const Set& other) {
    other._CheckValidity();
    auto newSizePtr = _SetAllocateSize(other.size());
    auto newInnerPtr = _SetAllocateArray(other.setCapacity);
    std::ranges::copy(other.begin(), other.end(), newInnerPtr.get());
    setSizePtr = newSizePtr;
    setInnerPtr = newInnerPtr;
    setCapacity = other.setCapacity;
}

template<typename T>
Set<T>::Set(Set&& other) noexcept : setCapacity(other.setCapacity),
                                    setInnerPtr(std::move(other.setInnerPtr)) {
    other.setCapacity = 0;
    setSizePtr = std::move(other.setSizePtr);
}

template<typename T>
Set<T>& Set<T>::operator=(const Set& other) {
    if (this != &other) {
        other._CheckValidity();
        auto newSizePtr = _SetAllocateSize(other.size());
        auto newInnerPtr = _SetAllocateArray(other.setCapacity);
        std::ranges::copy(other.begin(), other.end(), newInnerPtr.get());

        setSizePtr = newSizePtr;
        setInnerPtr = newInnerPtr;
        setCapacity = other.setCapacity;
    }
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator=(Set&& other) noexcept {
    if (this != &other) {
        setSizePtr = std::move(other.setSizePtr);
        setInnerPtr = std::move(other.setInnerPtr);
        setCapacity = other.setCapacity;
        other.setCapacity = 0;
    }
    return *this;
}

template<typename T>
template<std::ranges::input_range Range>
Set<T>::Set(Range&& range) {
    auto n = static_cast<typename Set<T>::size_type>(std::ranges::size(range));
    if (n < 0) {
        time_t t = time(nullptr);
        throw InvalidCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    setCapacity = (n > 0 ? n : INIT_SET_CAPACITY);  
    setSizePtr = _SetAllocateSize(n);
    setInnerPtr = _SetAllocateArray(setCapacity);
    std::ranges::copy(range, setInnerPtr.get());
}

template<typename T>
typename Set<T>::size_type Set<T>::size() const {
    _CheckValidity();
    return *setSizePtr;
}

template<typename T>
bool Set<T>::isEmpty() const {
    _CheckValidity();
    return *setSizePtr == 0;
}

template<typename T>
void Set<T>::clear() {
    _CheckValidity();
    *setSizePtr = 0;
}

template<typename T>
typename Set<T>::iterator Set<T>::begin() const {
    _CheckValidity();
    return ConstIterator<T>(setInnerPtr, setSizePtr, 0);
}

template<typename T>
typename Set<T>::iterator Set<T>::end() const {
    return begin() + *setSizePtr;
}

template<typename T>
typename Set<T>::const_iterator Set<T>::cbegin() const {
    return begin();
}

template<typename T>
typename Set<T>::const_iterator Set<T>::cend() const {
    return end();
}

template<typename T>
typename Set<T>::reverse_iterator Set<T>::rbegin() const {
    _CheckValidity();
    return reverse_iterator(end());
}

template<typename T>
typename Set<T>::reverse_iterator Set<T>::rend() const {
    _CheckValidity();
    return reverse_iterator(begin());
}

template<typename T>
typename Set<T>::const_reverse_iterator Set<T>::crbegin() const {
    _CheckValidity();
    return const_reverse_iterator(end());
}

template<typename T>
typename Set<T>::const_reverse_iterator Set<T>::crend() const {
    _CheckValidity();
    return const_reverse_iterator(begin());
}

template<typename T>
int Set<T>::_find(const T& elem) const {
    _CheckValidity();
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

template<typename T>
typename Set<T>::const_iterator Set<T>::find(const T& elem) const {
    _CheckValidity();
    int idx = _find(elem);
    auto rawArrPtr = setInnerPtr.get();
    if (idx < *setSizePtr && rawArrPtr[idx] == elem)
        return ConstIterator<T>(setInnerPtr, setSizePtr, idx);
    return cend();
}

template<typename T>
bool Set<T>::add(const T& elem) {
    _CheckValidity();
    auto rawArrPtr = setInnerPtr.get();
    int index = _find(elem);

    if (index < *setSizePtr && rawArrPtr[index] == elem)
        return false;
    
    if (*setSizePtr == setCapacity) {
        _Regrow();
        rawArrPtr = setInnerPtr.get();
    }

    for (int i = *setSizePtr; i > index ; i--) {
        rawArrPtr[i] = rawArrPtr[i - 1];
    }
    
    rawArrPtr[index] = elem;
    (*setSizePtr)++;
    return true;
}

template<typename T>
bool Set<T>::erase(const T& elem) {
    _CheckValidity();
    auto rawArrPtr = setInnerPtr.get();
    int index = _find(elem);
    if (index >= *setSizePtr || rawArrPtr[index] != elem)
        return false;
    for (int i = index; i < *setSizePtr - 1; i++) {
        rawArrPtr[i] = rawArrPtr[i + 1];
    }
    (*setSizePtr)--;
    return true;
}

template<typename T>
bool Set<T>::isSubSetOf(const Set<T>& other) const {
    _CheckValidity();
    other._CheckValidity();
    for (const auto& elem : *this) {
        if (!other.contains(elem))
            return false;
    }
    return true;
}

template<typename T>
bool Set<T>::contains(const T& elem) const {
    _CheckValidity();
    int index = _find(elem);
    return index < *setSizePtr && setInnerPtr.get()[index] == elem;
}

template<typename T>
Set<T>& Set<T>::unity(const Set<T>& other) {
    _CheckValidity();
    other._CheckValidity();
    for (const auto& elem : other) add(elem);
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator+=(const Set<T>& other) {
    return unity(other);
}

template<typename T>
Set<T>& Set<T>::operator|=(const Set<T>& other) {
    return unity(other);
}

template<typename T>
Set<T> Set<T>::operator+(const Set<T>& other) const {
    _CheckValidity();
    other._CheckValidity();
    Set<T> newSet(*this);
    return newSet.unity(other);
}

template<typename T>
Set<T> Set<T>::operator|(const Set<T>& other) const {
    return *this + other;
}

template<typename T>
Set<T>& Set<T>::difference(const Set<T>& other) {
    _CheckValidity();
    other._CheckValidity();
    for (const auto& elem : other) erase(elem);
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator-=(const Set<T>& other) {
    return difference(other);
}

template<typename T>
Set<T>& Set<T>::operator/=(const Set<T>& other) {
    return difference(other);
}

template<typename T>
Set<T> Set<T>::operator-(const Set<T>& other) const {
    _CheckValidity();
    other._CheckValidity();
    Set<T> newSet(*this);
    return newSet.difference(other);
}

template<typename T>
Set<T> Set<T>::operator/(const Set<T>& other) const {
    return *this - other;
}

template<typename T>
Set<T>& Set<T>::intersection(const Set<T>& other) {
    _CheckValidity();
    other._CheckValidity();
    Set<T> tmpSet(*this);
    for (const auto& elem : tmpSet) {
        if (!other.contains(elem))
            erase(elem);
    }
    return *this; 
}

template<typename T>
Set<T>& Set<T>::operator*=(const Set<T>& other) {
    return intersection(other);
}

template<typename T>
Set<T>& Set<T>::operator&=(const Set<T>& other) {
    return intersection(other);
}

template<typename T>
Set<T> Set<T>::operator*(const Set<T>& other) const {
    _CheckValidity();
    other._CheckValidity();
    Set<T> newSet(*this);
    return newSet.intersection(other);
}

template<typename T>
Set<T> Set<T>::operator&(const Set<T>& other) const {
    return *this * other;
}

template<typename T>
Set<T>& Set<T>::symmetric_difference(const Set<T>& other) {
    _CheckValidity();
    other._CheckValidity();
    Set<T> tmpSet(*this);
    unity(other);
    for (const auto& elem : tmpSet)
        if (other.contains(elem))
            erase(elem);
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator^=(const Set<T>& other) {
    return symmetric_difference(other);
}

template<typename T>
Set<T> Set<T>::operator^(const Set<T>& other) const {
    _CheckValidity();
    other._CheckValidity();
    Set<T> newSet(*this);
    return newSet.symmetric_difference(other);
}

template<typename T>
bool Set<T>::operator==(const Set<T>& other) const {
    _CheckValidity();
    other._CheckValidity();

    if (*setSizePtr != *other.setSizePtr)
        return false;

    return std::ranges::equal(*this, other);
}

template<typename T>
std::strong_ordering Set<T>::operator<=>(const Set<T>& other) const {
    _CheckValidity();
    other._CheckValidity();

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

template<typename T>
Set<T>::operator bool() const noexcept {
    return setSizePtr && setInnerPtr;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Set<T>& s) {
    os << "{ ";
    for (const auto& elem : s) 
        os << elem << " ";
    os << "}";
    return os;
}

template<typename T>
std::shared_ptr<typename Set<T>::size_type> Set<T>::_SetAllocateSize(typename Set<T>::size_type size) const {
    try {
        return std::make_shared<typename Set<T>::size_type>(size);
    }
    catch (const std::bad_alloc&) {
        time_t t = time(nullptr);
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
}

template<typename T>
std::shared_ptr<T[]> Set<T>::_SetAllocateArray(typename Set<T>::size_type capacity) const {
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

template<typename T>
void Set<T>::_Regrow() {
    typename Set<T>::size_type newCapacity = setCapacity > 0 ? setCapacity * 2 : INIT_SET_CAPACITY;
    auto newSetInnerPtr = _SetAllocateArray(newCapacity);
    std::ranges::copy(begin(), end(), newSetInnerPtr.get());
    
    setCapacity = newCapacity;
    setInnerPtr = std::move(newSetInnerPtr);
}

template<typename T>
void Set<T>::_CheckValidity() const {
    if (!setSizePtr || !setInnerPtr) {
        time_t t = time(nullptr);
        throw DeletedObjectError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
}
