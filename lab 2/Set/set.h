#pragma once

#include "base_set.h"
#include "const_iterator.h"
#include "concepts.h"
#include <compare>
#include <ranges>
#include <memory>
#include <initializer_list>

template<ContainerElementType T>
class Set final: public BaseSet {
public:
    // Алиасы
    using value_type = T;
    using size_type = int;
    using iterator = ConstIterator<T>;
    using const_iterator = ConstIterator<T>;
    using reverse_iterator = std::reverse_iterator<ConstIterator<T>>;
    using const_reverse_iterator = std::reverse_iterator<ConstIterator<T>>;

    // Конструкторы стандартные (не шаблонные)
    Set() noexcept = default;

    Set(const Set<T>& other);

    Set(Set<T>&& other) noexcept;

    Set(size_type size, const T* array); // TODO

    explicit Set(std::initializer_list<T> il); 

    // Конструкторы стандартные (шаблонные)
    template<Convertible<T> U>
    Set(const Set<U>& other); // TODO

    template<Convertible<T> U>
    Set(Set<T>&& other) noexcept; // TODO

    template<Convertible<T> U>
    Set(size_type size, const U* array); // TODO

    template<Convertible<T> U>
    explicit Set(std::initializer_list<U> il); // TODO

    // Конструкторы от range
    template<ConvertibleInputRange<T> R>
    Set(const R& range); // TODO

    template<ConvertibleInputRange<T> R>
    Set(R&& range); // TODO

    // Конструкторы от контейнера
    template<ConvertibleContainer<T> C>
    Set(const C& Container); // TODO

    template<ConvertibleContainer<T> C>
    Set(C&& Container); // TODO
    
    // Конструктор от итератора
    template<ConvertibleInputIterator<T> It, Sentinel<It> S>
    Set(const It& begin, const S& end); // TODO

    // Деструктор
    ~Set() noexcept override = default;

    // Операторы присваивания стандартные (не шаблонные)
    Set<T>& operator=(const Set& other);

    Set<T>& operator=(Set&& other) noexcept;

    Set<T>& operator=(std::initializer_list<T> il); // TODO

    // Операторы присваивания стандартные (шаблонные)
    template<Convertible<T> U>
    Set<T>& operator=(const Set<U>& other); // TODO

    template<Convertible<T> U>
    Set<T>& operator=(Set<U>&& other) noexcept; // TODO

    template<Convertible<T> U>
    Set<T>& operator=(std::initializer_list<U> il); // TODO

    // Операторы присваивания от range 
    template<ConvertibleInputRange<T> R>
    Set<T>& operator=(const R& range); // TODO

    template<ConvertibleInputRange<T> R>
    Set<T>& operator=(R&& range); // TODO

    // Операторы присваивания от контейнера
    template<ConvertibleContainer<T> C>
    Set<T>& operator=(const C& container); // TODO

    template<ConvertibleContainer<T> C>
    Set<T>& operator=(C&& container); // TODO
    
    // Добавление
    template<Convertible<T> U>
    bool add(const U& elem) noexcept; // TODO

    template<Convertible<T> U>
    Set<T> operator+(const U& elem) const; // TODO

    // Удаление
    template<Convertible<T> U>
    bool erase(const U& elem) noexcept; // TODO
    
    template<Convertible<T> U>
    Set<T> operator-(const U& elem) const; // TODO 

    // Очистка
    void clear() noexcept override;

    void operator!() noexcept; // TODO
    
    // Наличие элемента
    template<Convertible<T> U>
    [[nodiscard]] bool contains(const U& elem) const noexcept; // TODO 

    // Сравнение
    template<Convertible<T> U>
    [[nodiscard]] bool operator==(const Set<U>& other) const noexcept; // TODO

    template<Convertible<T> U>
    [[nodiscard]] std::strong_ordering operator<=>(const Set<U>&other) const noexcept; // TODO

    template<Convertible<T> U>
    [[nodiscard]] bool equal(const Set<U>& other) const noexcept; // TODO

    template<Convertible<T> U>
    [[nodiscard]] bool notEqual(const Set<U>& other) const noexcept; // TODO

    template<Convertible<T> U>
    [[nodiscard]] bool less(const Set<U>& other) const noexcept; // TODO

    template<Convertible<T> U>
    [[nodiscard]] bool lessEqual(const Set<U>& other) const noexcept; // TODO

    template<Convertible<T> U>
    [[nodiscard]] bool greater(const Set<U>& other) const noexcept; // TODO

    template<Convertible<T> U>
    [[nodiscard]] bool greaterEqual(const Set<U>& other) const noexcept; // TODO
    
    template<Convertible<T> U>
    [[nodiscard]] bool isSuperSetOf(const Set<U>& other) const noexcept; // TODO
    
    template<Convertible<T> U>
    [[nodiscard]] bool isSubSetOf(const Set<U>& other) const noexcept; // TODO

    [[nodiscard]] explicit operator bool() const noexcept;

    // Объединение
    template<Convertible<T> U>
    Set<T>& unity(const Set<U>& other) noexcept; // TODO

    template<Convertible<T> U>
    Set<T>& operator+=(const Set<U>& other) noexcept; // TODO

    template<Convertible<T> U>
    Set<T>& operator|=(const Set<U>& other) noexcept; // TODO

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator+(const Set<U>& other) const; // TODO

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator|(const Set<U>& other) const; // TODO

    // Разность
    template<Convertible<T> U>
    Set<T>& difference(const Set<U>& other) noexcept; // TODO

    template<Convertible<T> U>
    Set<T>& operator-=(const Set<U>& other) noexcept; // TODO

    template<Convertible<T> U>
    Set<T>& operator/=(const Set<U>& other) noexcept; // TODO

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator-(const Set<U>& other) const; // TODO

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator/(const Set<U>& other) const; // TODO

    // Пересечение
    template<Convertible<T> U>
    Set<T>& intersection(const Set<U>& other); // TODO

    template<Convertible<T> U>
    Set<T>& operator*=(const Set<U>& other); // TODO

    template<Convertible<T> U>
    Set<T>& operator&=(const Set<U>& other); // TODO

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator*(const Set<U>& other) const; // TODO

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator&(const Set<U>& other) const; // TODO

    // Симметрическая разность
    template<Convertible<T> U>
    Set<T>& symmetric_difference(const Set<U>& other); // TODO

    template<Convertible<T> U>
    Set<T>& operator^=(const Set<U>& other); // TODO

    template<HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator^(const Set<U>& other) const; // TODO

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
    [[nodiscard]] size_type size() const noexcept override;
    [[nodiscard]] bool isEmpty() const noexcept override;
private:
    size_type find(const T& elem) const noexcept;

    void regrow();
    std::shared_ptr<size_type> allocSharedSize(size_type size) const;
    std::shared_ptr<T[]> allocSharedInner(size_type capacity) const;
    
    void checkExpired() const override;
    
    std::shared_ptr<T[]> setInnerPtr;
    int setCapacity;
};

#include "set.hpp"

static_assert(std::ranges::contiguous_range<Set<int>>);