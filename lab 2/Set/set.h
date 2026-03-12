#pragma once

#include "base_set.h"
#include "const_iterator.h"
#include <compare>
#include <ranges>
#include <memory>
#include <initializer_list>

template<typename T>
class Set final: public BaseSet {
public:
    using value_type = T;
    using size_type = int;
    using iterator = ConstIterator<T>;
    using const_iterator = ConstIterator<T>;
    using reverse_iterator = std::reverse_iterator<ConstIterator<T>>;
    using const_reverse_iterator = std::reverse_iterator<ConstIterator<T>>;

    Set();
    Set(size_type size); 
    Set(std::initializer_list<T> il);
    Set(const Set& other);
    Set(Set&& other) noexcept;

    template<std::ranges::input_range Range>
    Set(Range&& range);

    Set<T>& operator=(const Set& other);
    Set<T>& operator=(Set&& other) noexcept;

    ~Set() noexcept override = default;

    bool add(const T& elem);
    bool erase(const T& elem);
    [[nodiscard]] bool isSubSetOf(const Set<T>& other) const; 
    [[nodiscard]] bool contains(const T& elem) const;
    [[nodiscard]] const_iterator find(const T& elem) const;

    [[nodiscard]] size_type size() const override;
    [[nodiscard]] bool isEmpty() const override;
    void clear() override;

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    
    Set<T>& unity(const Set<T>& other);
    Set<T>& operator+=(const Set<T>& other);
    Set<T>& operator|=(const Set<T>& other);
    Set<T> operator+(const Set<T>& other) const;
    Set<T> operator|(const Set<T>& other) const;

    Set<T>& difference(const Set<T>& other);
    Set<T>& operator-=(const Set<T>& other);
    Set<T>& operator/=(const Set<T>& other);
    Set<T> operator-(const Set<T>& other) const;
    Set<T> operator/(const Set<T>& other) const;

    Set<T>& intersection(const Set<T>& other);
    Set<T>& operator*=(const Set<T>& other);
    Set<T>& operator&=(const Set<T>& other);
    Set<T> operator*(const Set<T>& other) const;
    Set<T> operator&(const Set<T>& other) const;

    Set<T>& symmetric_difference(const Set<T>& other);
    Set<T>& operator^=(const Set<T>& other);
    Set<T> operator^(const Set<T>& other) const;

    [[nodiscard]] bool operator==(const Set<T>& other) const;
    [[nodiscard]] std::strong_ordering operator<=>(const Set<T>&other) const;
    [[nodiscard]] explicit operator bool() const noexcept;
private:
    void _CheckValidity() const override;
    std::shared_ptr<size_type> _SetAllocateSize(size_type size) const;
    std::shared_ptr<T[]> _SetAllocateArray(size_type capacity) const;
    size_type _find(const T& elem) const;
    void _Regrow();

    int setCapacity;
    std::shared_ptr<T[]> setInnerPtr;
};

#include "set.hpp"