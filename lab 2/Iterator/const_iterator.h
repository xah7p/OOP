#pragma once

#include "base_iterator.h"
#include "set.h"
#include "concepts.h"
#include <cstddef>
#include <iterator>
#include <memory>
#include <compare>

template<ContainerElementType T>
class Set;

template<ContainerElementType T>    
class ConstIterator: public BaseIterator {
public: 
    // Алиасы
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    
    using element_type = const T;
    using iterator_concept = std::contiguous_iterator_tag;

    // Конструкторы
    ConstIterator() noexcept = default;
    ConstIterator(const ConstIterator<T>& other) noexcept = default;
    ConstIterator(ConstIterator<T>&& other) noexcept = default;

    // Операторы присваивания
    ConstIterator<T>& operator=(const ConstIterator<T>& other) noexcept = default;
    ConstIterator<T>& operator=(ConstIterator<T>&& other) noexcept = default;

    // Деструктор
    ~ConstIterator() noexcept override = default;

    // Доступ к элементам
    reference operator[](difference_type index) const;
    reference operator*() const;
    pointer operator->() const;

    // Изменение индекса
    ConstIterator<T>& operator++() noexcept;
    ConstIterator<T> operator++(int) noexcept;
    ConstIterator<T>& operator+=(difference_type n) noexcept;
    ConstIterator<T> operator+(difference_type n) const noexcept;

    ConstIterator<T>& operator--() noexcept;
    ConstIterator<T> operator--(int) noexcept;
    ConstIterator<T>& operator-=(difference_type n) noexcept;
    ConstIterator<T> operator-(difference_type n) const noexcept;
    difference_type operator-(const ConstIterator<T>& other) const noexcept;
    
    // Операторы сравнения
    [[nodiscard]] bool operator==(const ConstIterator& other) const noexcept;
    [[nodiscard]] std::partial_ordering operator<=>(const ConstIterator<T>& other) const noexcept;
    [[nodiscard]] explicit operator bool() const noexcept override;
private:
    friend class Set<T>;
    explicit ConstIterator(const std::shared_ptr<T[]>& innerPtr, 
             const std::shared_ptr<int>& sizePtr, 
             int start_index = 0) noexcept; // используется в Set<T>::begin()

    // Проверка объекта 
    void checkExpiredContainer(int) const override;
    // Проверка итератора
    void checkIndex(int) const override;

    pointer getCurrentPointer() const;
    std::weak_ptr<T[]> containerPtr;
};

template<typename T>
ConstIterator<T> operator+(typename ConstIterator<T>::difference_type n, const ConstIterator<T> &it) noexcept;

#include "const_iterator.hpp"

static_assert(std::contiguous_iterator<ConstIterator<int>>);
