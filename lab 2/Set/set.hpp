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
#include <ostream>

template<ContainerElementType T>
Set<T>::Set(const Set<T>& other) {
    other.checkExpired();
    allocMemory(other.size(), other.setCapacity);
    std::ranges::copy(other.begin(), other.end(), setInnerPtr.get());
}

template<ContainerElementType T>
Set<T>::Set(Set<T>&& other) noexcept
    : setInnerPtr(std::move(other.setInnerPtr)), 
      setCapacity(other.setCapacity) {
    setSizePtr = std::move(other.setSizePtr);
    other.setCapacity = 0;
}

template<ContainerElementType T>
Set<T>::Set(typename Set<T>::size_type size, const T* array) {
    if (size < 0) {
        time_t t = time(NULL);
        throw InvalidSizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    if (!array) {
        time_t t = time(NULL);
        throw InvalidCPointerError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    allocMemory(size, size > 0 ? size : INIT_SET_CAPACITY);
    std::ranges::copy(array, array + size, setInnerPtr.get());
}

template<ContainerElementType T>
Set<T>::Set(std::initializer_list<T> args) {
    auto n = static_cast<typename Set<T>::size_type>(args.size());
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    std::ranges::copy(args, setInnerPtr.get());
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>::Set(const Set<U>& other) {
    auto n = other.size(); 
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    std::ranges::copy(other.begin(), other.end(), setInnerPtr.get());
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>::Set(Set<U>&& other) noexcept {
    auto n = other.size(); 
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY); 
    std::ranges::move(other.begin(), other.end(), setInnerPtr.get());
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>::Set(typename Set<T>::size_type size, const U* array) {
    if (size < 0) {
        time_t t = time(NULL);
        throw InvalidSizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    if (!array) {
        time_t t = time(NULL);
        throw InvalidCPointerError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    allocMemory(size, size > 0 ? size : INIT_SET_CAPACITY);
    std::ranges::copy(array, array + size, setInnerPtr.get());
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>::Set(std::initializer_list<U> il) {
    auto n = static_cast<typename Set<T>::size_type>(il.size());
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    std::ranges::copy(il, setInnerPtr.get());
}

template<ContainerElementType T>
template<ConvertibleInputRange<T> R>
Set<T>::Set(R&& range) { 
    auto n = static_cast<typename Set<T>::size_type>(std::ranges::size(range));
    if (n < 0) {
        time_t t = time(nullptr);
        throw InvalidCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    
    if constexpr (std::is_rvalue_reference_v<R&&>)
        std::ranges::move(range, setInnerPtr.get());
    else 
        std::ranges::copy(range, setInnerPtr.get());
}

template<ContainerElementType T>
template<ConvertibleContainer<T> C>
Set<T>::Set(C&& container) {
    auto n = static_cast<typename Set<T>::size_type>(container.size());
    if (n < 0) {
        time_t t = time(nullptr);
        throw InvalidCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    
    if constexpr (std::is_rvalue_reference_v<C&&>)
        std::ranges::move(container.begin(), container.end(), setInnerPtr.get());
    else 
        std::ranges::copy(container.cbegin(), container.cend(), setInnerPtr.get());
}

template<ContainerElementType T>
template<ConvertibleInputIterator<T> It, Sentinel<It> S>
Set<T>::Set(const It& beginIt, const S& endIt) {
    auto n = static_cast<typename Set<T>::size_type>(std::ranges::distance(beginIt, endIt));
    if (n < 0) {
        time_t t = time(nullptr);
        throw InvalidCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    std::ranges::copy(beginIt, endIt, setInnerPtr.get());
}

template<ContainerElementType T>
Set<T>& Set<T>::operator=(const Set<T>& other) {
    if (this != &other) {
        other.checkExpired();
        allocMemory(other.size(), other.setCapacity);
        std::ranges::copy(other.begin(), other.end(), setInnerPtr.get());
    }
    return *this;
}

template<ContainerElementType T>
Set<T>& Set<T>::operator=(Set<T>&& other) noexcept {
    if (this != &other) {
        setSizePtr = std::move(other.setSizePtr);
        setInnerPtr = std::move(other.setInnerPtr);
        setCapacity = other.setCapacity;
        other.setCapacity = 0;
    }
    return *this;
}

template<ContainerElementType T>
Set<T>& Set<T>::operator=(std::initializer_list<T> il) {
    auto n = static_cast<typename Set<T>::size_type>(il.size());
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    std::ranges::copy(il, setInnerPtr.get());
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator=(const Set<U>& other) {
    auto n = other.size(); 
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY); 
    std::ranges::copy(other.begin(), other.end(), setInnerPtr.get());
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator=(Set<U>&& other) noexcept {
    auto n = other.size(); 
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY); 
    std::ranges::move(other.begin(), other.end(), setInnerPtr.get()); 
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator=(std::initializer_list<U> il) {
    auto n = static_cast<typename Set<T>::size_type>(il.size());
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    std::ranges::copy(il, setInnerPtr.get());
    return *this;
}

template<ContainerElementType T>
template<ConvertibleInputRange<T> R>
Set<T>& Set<T>::operator=(R&& range) {
    auto n = static_cast<typename Set<T>::size_type>(std::ranges::size(range));
    if (n < 0) {
        time_t t = time(nullptr);
        throw InvalidCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    if constexpr (std::is_rvalue_reference_v<R&&>)
        std::ranges::move(range, setInnerPtr.get());
    else 
        std::ranges::copy(range, setInnerPtr.get());
    return *this;
}

template<ContainerElementType T>
template<ConvertibleContainer<T> C>
Set<T>& Set<T>::operator=(C&& container) {
    auto n = static_cast<typename Set<T>::size_type>(container.size());
    if (n < 0) {
        time_t t = time(nullptr);
        throw InvalidCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    
    allocMemory(n, n > 0 ? n : INIT_SET_CAPACITY);
    if constexpr (std::is_rvalue_reference_v<C&&>)
        std::ranges::move(container.begin(), container.end(), setInnerPtr.get());
    else 
        std::ranges::copy(container.cbegin(), container.cend(), setInnerPtr.get());  
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::add(const U& elem) {
    T value = static_cast<T>(elem);
    if (!setInnerPtr || !setSizePtr) return false;
    auto rawArrPtr = setInnerPtr.get();
    int index = find(value);

    if (index < *setSizePtr && rawArrPtr[index] == value) return false;

    if (*setSizePtr == setCapacity) {
        regrow();
        rawArrPtr = setInnerPtr.get();
    }
    std::ranges::move_backward(rawArrPtr + index, rawArrPtr + *setSizePtr, rawArrPtr + *setSizePtr + 1);
    rawArrPtr[index] = value;
    ++(*setSizePtr);
    return true;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator+=(const U& elem) {
    add(elem);
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T> Set<T>::operator+(const U& elem) const {
    auto tmpSet(*this);
    tmpSet.add(elem);
    return tmpSet;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::erase(const U& elem) noexcept {
    T value = static_cast<T>(elem);
    if (!setInnerPtr || !setSizePtr) return false;
    auto rawArrPtr = setInnerPtr.get();
    int index = find(value);

    if (index >= *setSizePtr || rawArrPtr[index] != value) {
        return false;
    }

    std::ranges::move(rawArrPtr + index + 1, rawArrPtr + *setSizePtr, rawArrPtr + index);
    (*setSizePtr)--;
    return true;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator-=(const U& elem) noexcept {
    erase(elem);
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T> Set<T>::operator-(const U& elem) const {
    auto tmpSet(*this);
    tmpSet.erase(elem);
    return tmpSet;
}

template<ContainerElementType T>
void Set<T>::clear() noexcept {
    if (setSizePtr) *setSizePtr = 0;
    if (setInnerPtr) setInnerPtr = allocSharedInner(INIT_SET_CAPACITY); 
}


template<ContainerElementType T>
void Set<T>::operator!() noexcept {
    clear();
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::contains(const U& elem) const noexcept {
    T value = static_cast<T>(elem);
    if (!setInnerPtr || !setSizePtr) return false;
    int index = find(value);
    return index < *setSizePtr && setInnerPtr.get()[index] == value;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::operator==(const Set<U>& other) const noexcept {
    if (*setSizePtr != other.size()) {
        return false;
    }
    return std::ranges::equal(*this, other);
}

template<ContainerElementType T>
template<Convertible<T> U>
std::strong_ordering Set<T>::operator<=>(const Set<U>& other) const noexcept {
    return std::lexicographical_compare_three_way(begin(), end(), other.begin(), other.end());
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::equal(const Set<U>& other) const noexcept {
    return *this == other;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::notEqual(const Set<U>& other) const noexcept {
    return *this != other;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::less(const Set<U>& other) const noexcept {
    return *this < other;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::lessEqual(const Set<U>& other) const noexcept {
    return *this <= other;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::greater(const Set<U>& other) const noexcept {
    return *this > other;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::greaterEqual(const Set<U>& other) const noexcept {
    return *this >= other;
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::isSuperSetOf(const Set<U>& other) const noexcept {
    if (!setSizePtr || ! setInnerPtr) return false;
    return std::ranges::includes(*this, other);
}

template<ContainerElementType T>
template<Convertible<T> U>
bool Set<T>::isSubSetOf(const Set<U>& other) const noexcept {
    return std::ranges::includes(other, *this);

}

template<ContainerElementType T>
Set<T>::operator bool() const noexcept {
    return setSizePtr && setInnerPtr;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::unity(const Set<U>& other) {
    if (other.isEmpty()) return *this;
    if (this->isEmpty()) { 
        *this = other; 
        return *this; 
    }
    auto max_size = this->size() + other.size();
    auto newInnerPtr = allocSharedInner(max_size);
    auto result = std::ranges::set_union(*this, other, newInnerPtr.get());    
    auto real_size = std::ranges::distance(newInnerPtr.get(), result.out);
    
    setInnerPtr = std::move(newInnerPtr);
    *setSizePtr = real_size;
    setCapacity = max_size; 
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator+=(const Set<U>& other) {
    return unity(other);
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator|=(const Set<U>& other) {
    return unity(other);
}

template<ContainerElementType T>
template<HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator+(const Set<U>& other) const {
    Set<T> newSet(*this);
    return newSet.unity(other);
}

template<ContainerElementType T>
template<HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator|(const Set<U>& other) const {
    return *this + other;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::difference(const Set<U>& other) noexcept {
        if (other.isEmpty()) return *this;
    if (this->isEmpty()) { 
        *this = other; 
        return *this; 
    }
    auto max_size = this->size();
    auto newInnerPtr = allocSharedInner(max_size);
    auto result = std::ranges::set_difference(*this, other, newInnerPtr.get());    
    auto real_size = std::ranges::distance(newInnerPtr.get(), result.out);
    
    setInnerPtr = std::move(newInnerPtr);
    *setSizePtr = real_size;
    setCapacity = max_size; 
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator-=(const Set<U>& other) noexcept {
    return difference(other);
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator/=(const Set<U>& other) noexcept {
    return difference(other);
}

template<ContainerElementType T>
template<HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator-(const Set<U>& other) const {
    Set<T> newSet(*this);
    return newSet.difference(other);
}

template<ContainerElementType T>
template<HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator/(const Set<U>& other) const {
    return *this - other;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::intersection(const Set<U>& other) {
    if (other.isEmpty()) return *this;
    if (this->isEmpty()) { 
        *this = other; 
        return *this; 
    }
    auto max_size = this->size() + other.size();
    auto newInnerPtr = allocSharedInner(max_size);
    auto result = std::ranges::set_intersection(*this, other, newInnerPtr.get());    
    auto real_size = std::ranges::distance(newInnerPtr.get(), result.out);
    
    setInnerPtr = std::move(newInnerPtr);
    *setSizePtr = real_size;
    setCapacity = max_size; 
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator*=(const Set<U>& other) {
    return intersection(other);
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator&=(const Set<U>& other) {
    return intersection(other);
}

template<ContainerElementType T>
template<HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator*(const Set<U>& other) const {
    Set<T> newSet(*this);
    return newSet.intersection(other);
}

template<ContainerElementType T>
template<HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator&(const Set<U>& other) const {
    return *this * other;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::symmetric_difference(const Set<U>& other) {
    if (other.isEmpty()) return *this;
    if (this->isEmpty()) { 
        *this = other; 
        return *this; 
    }
    auto max_size = this->size() + other.size();
    auto newInnerPtr = allocSharedInner(max_size);
    auto result = std::ranges::set_symmetric_difference(*this, other, newInnerPtr.get());    
    auto real_size = std::ranges::distance(newInnerPtr.get(), result.out);
    
    setInnerPtr = std::move(newInnerPtr);
    *setSizePtr = real_size;
    setCapacity = max_size; 
    return *this;
}

template<ContainerElementType T>
template<Convertible<T> U>
Set<T>& Set<T>::operator^=(const Set<U>& other) {
    return symmetric_difference(other);
}

template<ContainerElementType T>
template<HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator^(const Set<U>& other) const {
    Set<T> newSet(*this);
    return newSet.symmetric_difference(other);
}

template<ContainerElementType T>
typename Set<T>::iterator Set<T>::begin() const noexcept {
    return typename Set<T>::iterator(setInnerPtr, setSizePtr, 0);
}

template<ContainerElementType T>
typename Set<T>::iterator Set<T>::end() const noexcept {
    if (!setSizePtr) return begin();
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
typename Set<T>::size_type Set<T>::size() const noexcept {
    if (!setSizePtr) return 0;
    return *setSizePtr;
}

template<ContainerElementType T>
bool Set<T>::isEmpty() const noexcept {
    if (!setSizePtr) return true;
    return *setSizePtr == 0;
}

template<ContainerElementType T>
typename Set<T>::size_type Set<T>::find(const T& elem) const noexcept {
    if (!setSizePtr || !setInnerPtr) return -1;
    auto it = std::ranges::lower_bound(cbegin(), cend(), elem);
    return static_cast<typename Set<T>::size_type>(std::ranges::distance(cbegin(), it));
}

template<ContainerElementType T>
void Set<T>::regrow() {
    typename Set<T>::size_type newCapacity =
        setCapacity > 0 ? setCapacity * 2 : INIT_SET_CAPACITY;
    auto newSetInnerPtr = allocSharedInner(newCapacity);
    std::ranges::copy(begin(), end(), newSetInnerPtr.get());

    setCapacity = newCapacity;
    setInnerPtr = std::move(newSetInnerPtr);
}

template<ContainerElementType T>
std::shared_ptr<typename Set<T>::size_type>
Set<T>::allocSharedSize(typename Set<T>::size_type size) const {
    if (size < 0) {
        time_t t = time(nullptr);
        throw InvalidSizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t));
    }
    try {
        return std::make_shared<typename Set<T>::size_type>(size);
    } catch (const std::bad_alloc&) {
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
    } catch (const std::bad_alloc&) {
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

template <ContainerElementType T> 
void Set<T>::allocMemory(typename Set<T>::size_type size, typename Set<T>::size_type capacity) {
    setSizePtr = allocSharedSize(size);
    setInnerPtr = allocSharedInner(capacity);
    setCapacity = capacity;
}

template<ContainerElementType T>
std::ostream& operator<<(std::ostream& os, const Set<T>& s) {
    os << "{ ";
    std::ranges::copy(s, std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}