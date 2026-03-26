#pragma once

#include "base_set.h"
#include "const_iterator.h"
#include "myconcepts.h"
#include <compare>
#include <ranges>
#include <memory>
#include <initializer_list>

template<SetElementType T>
class Set final: public BaseSet {
public:
    // Алиасы
    using value_type = T;
    using size_type = int;
    using iterator = ConstIterator<T>;
    using const_iterator = ConstIterator<T>;
    using reverse_iterator = std::reverse_iterator<ConstIterator<T>>;
    using const_reverse_iterator = std::reverse_iterator<ConstIterator<T>>;

    // Конструкторы стандартные
    Set() noexcept = default;

    Set(const Set<T>& other);

    Set(Set<T>&& other) noexcept;

    Set(size_type size, const T* array);

    explicit Set(std::initializer_list<T> il); 

    template<Convertible<T> U>
    explicit Set(const Set<U>& other);

    template<Convertible<T> U>
    Set(size_type size, const U* array);

    template<Convertible<T> U>
    explicit Set(std::initializer_list<U> il);

    // Конструктор от range
    template<ConvertibleInputRange<T> R>
    explicit Set(const R& range);

    // Конструктор от контейнера
    template<ConvertibleContainer<T> C>
    explicit Set(const C& Container);
    
    // Конструктор от итератора
    template<ConvertibleInputIterator<T> It, Sentinel<It> S>
    Set(const It& beginIt, const S& endIt);

    // Деструктор
    ~Set() noexcept override = default;

    // Операторы присваивания стандартные
    Set<T>& operator=(const Set& other);

    Set<T>& operator=(Set&& other) noexcept;

    Set<T>& operator=(std::initializer_list<T> il);

    template<Convertible<T> U>
    Set<T>& operator=(const Set<U>& other);

    template<Convertible<T> U>
    Set<T>& operator=(std::initializer_list<U> il);

    // Оператор присваивания от range 
    template<ConvertibleInputRange<T> R>
    Set<T>& operator=(const R& range);

    // Оператор присваивания от контейнера
    template<ConvertibleContainer<T> C>
    Set<T>& operator=(const C& container);
    
    // Добавление
    template<Convertible<T> U>
    bool add(const U& elem);

    template<Convertible<T> U>
    Set<T>& operator+=(const U& elem);

    template<Convertible<T> U>
    Set<T> operator+(const U& elem) const;

    // Удаление
    template<Convertible<T> U>
    bool erase(const U& elem) noexcept;

    template<Convertible<T> U>
    Set<T>& operator-=(const U& elem) noexcept;
    
    template<Convertible<T> U>
    Set<T> operator-(const U& elem) const; 

    // Очистка
    void clear() noexcept override;

    void operator!() noexcept;
    
    // Наличие элемента
    template<Convertible<T> U>
    [[nodiscard]] bool contains(const U& elem) const noexcept; 

    // Сравнение
    template<Convertible<T> U>
    [[nodiscard]] bool operator==(const Set<U>& other) const noexcept;

    template<Convertible<T> U>
    [[nodiscard]] std::strong_ordering operator<=>(const Set<U>&other) const noexcept;

    template<Convertible<T> U>
    [[nodiscard]] bool equal(const Set<U>& other) const noexcept;

    template<Convertible<T> U>
    [[nodiscard]] bool notEqual(const Set<U>& other) const noexcept;

    template<Convertible<T> U>
    [[nodiscard]] bool less(const Set<U>& other) const noexcept;

    template<Convertible<T> U>
    [[nodiscard]] bool lessEqual(const Set<U>& other) const noexcept;

    template<Convertible<T> U>
    [[nodiscard]] bool greater(const Set<U>& other) const noexcept;

    template<Convertible<T> U>
    [[nodiscard]] bool greaterEqual(const Set<U>& other) const noexcept;
    
    template<Convertible<T> U>
    [[nodiscard]] bool isSuperSetOf(const Set<U>& other) const noexcept;
    
    template<Convertible<T> U>
    [[nodiscard]] bool isSubSetOf(const Set<U>& other) const noexcept;

    [[nodiscard]] explicit operator bool() const noexcept;

    // Объединение
    template<Convertible<T> U>
    Set<T>& unity(const Set<U>& other);

    template<Convertible<T> U>
    Set<T>& operator+=(const Set<U>& other);

    template<Convertible<T> U>
    Set<T>& operator|=(const Set<U>& other);

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_union(const Set<U>& other) const;

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator+(const Set<U>& other) const;

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator|(const Set<U>& other) const;

    // Разность
    template<Convertible<T> U>
    Set<T>& difference(const Set<U>& other) noexcept;

    template<Convertible<T> U>
    Set<T>& operator-=(const Set<U>& other) noexcept;

    template<Convertible<T> U>
    Set<T>& operator/=(const Set<U>& other) noexcept;

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_difference(const Set<U>& other) const;

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator-(const Set<U>& other) const;

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator/(const Set<U>& other) const;

    // Пересечение
    template<Convertible<T> U>
    Set<T>& intersection(const Set<U>& other);

    template<Convertible<T> U>
    Set<T>& operator*=(const Set<U>& other);

    template<Convertible<T> U>
    Set<T>& operator&=(const Set<U>& other);

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_intersection(const Set<U>& other) const;

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator*(const Set<U>& other) const;

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator&(const Set<U>& other) const;

    // Симметрическая разность
    template<Convertible<T> U>
    Set<T>& symmetric_difference(const Set<U>& other);

    template<Convertible<T> U>
    Set<T>& operator^=(const Set<U>& other);

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_symmetric_difference(const Set<U>& other) const;

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator^(const Set<U>& other) const;

    // Получение итератора
    iterator begin() const noexcept;
    iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // Проверка размера
    [[nodiscard]] size_type power() const noexcept override;
    [[nodiscard]] size_type size() const noexcept override;
    [[nodiscard]] bool isEmpty() const noexcept override;
private:
    size_type find(const T& elem) const noexcept;

    void regrow();
    void normalize() noexcept;
    std::shared_ptr<size_type> allocSharedSize(size_type size) const;
    std::shared_ptr<T[]> allocSharedInner(size_type capacity) const;
    void allocMemory(size_type size, size_type capacity);
    void checkExpired() const override;
    
    std::shared_ptr<T[]> setInnerPtr;
    int setCapacity;

};

template<SetElementType T, Convertible<T> U>
Set<T> operator+(const U& elem, Set<T> set);

#include "set.hpp"

static_assert(std::ranges::contiguous_range<Set<int>>);
static_assert(Container<Set<int>>);