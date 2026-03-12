#pragma once

#include "base_iterator.h"
#include "set.h"
#include <cstddef>
#include <iterator>
#include <memory>
#include <compare>

template<class T>
class Set;

template<typename T>    
class ConstIterator: public BaseIterator {
public: 
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    
    using element_type = T;
    using iterator_concept = std::contiguous_iterator_tag;

    ConstIterator() = default;
    ConstIterator(const ConstIterator<T>& other) = default;
    ConstIterator(ConstIterator<T>&& other) noexcept = default;
    ConstIterator<T>& operator=(const ConstIterator<T>& other) = default;
    ConstIterator<T>& operator=(ConstIterator<T>&& other) noexcept = default;

    ~ConstIterator() noexcept override = default;

    // для итератора вывода
    reference operator*() const;
    ConstIterator<T>& operator++();
    ConstIterator<T> operator++(int);

    // для итератора ввода
    pointer operator->() const;
    explicit operator bool() const override;

    // для однонаправленного итератора
    [[nodiscard]] bool operator!=(const ConstIterator& other) const noexcept;
    [[nodiscard]] bool operator==(const ConstIterator& other) const noexcept;

    // для двунаправленного итератора
    ConstIterator<T>& operator--();
    ConstIterator<T> operator--(int);

    // для итератора с произвольным доступом
    std::strong_ordering operator<=>(const ConstIterator<T>& other) const;
    ConstIterator<T>& operator+=(difference_type n);
    ConstIterator<T>& operator-=(difference_type n);
    ConstIterator<T> operator+(difference_type n) const;
    ConstIterator<T> operator-(difference_type n) const;
    difference_type operator-(const ConstIterator<T>& other) const;
    reference operator[](difference_type index) const;

    // для непрерывного итератора
    // ничего не нужно, данные должны лежать последовательно в памяти
private:
    friend class Set<T>;
    explicit ConstIterator(const std::shared_ptr<T[]>& innerPtr, 
             const std::shared_ptr<int>& sizePtr, 
             int start_index = 0);
    void checkContainer(int) const override;
    void checkValidity(int) const override;

    pointer getCurrentPointer() const;
    std::weak_ptr<T[]> containerPtr;
};

template<typename T>
ConstIterator<T> operator+(typename ConstIterator<T>::difference_type n, const ConstIterator<T> &it);

#include "const_iterator.hpp"

static_assert(std::contiguous_iterator<ConstIterator<int>>);
