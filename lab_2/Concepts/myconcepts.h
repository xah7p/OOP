#pragma once

#include <compare>
#include <concepts>
#include <iterator>

template<typename T>
concept CopyMoveConstructible = std::copy_constructible<T> && std::move_constructible<T>;

template<typename T>
concept CopyAssignable = requires(T& t1, T& t2) { t1 = t2; } && requires(T& t1, const T& t2) { t1 = t2; };

template<typename T>
concept MoveAssignable = requires(T& t1, T&& t2) { { t1 = t2 } noexcept; };

template<typename T>
concept CopyMoveAssignable = CopyAssignable<T> && MoveAssignable<T>;

template<typename T>
concept Comparable = requires(const T& t1, const T& t2) {
    { t1 <=> t2 } -> std::convertible_to<std::strong_ordering>;
    { t1 == t2 } -> std::convertible_to<bool>;

};

template<typename T>
concept SetElementType = CopyMoveAssignable<T> 
                            && CopyMoveConstructible<T>
                            && std::destructible<T> 
                            && Comparable<T>;

template<typename From, typename To>
concept Convertible = std::convertible_to<From, To>;

template<typename T, typename U>
concept HasCommon = requires { typename std::common_type_t<T, U>; };

template<typename C>
concept Container = CopyMoveConstructible<C> && std::destructible<C> && requires(C c) {
    typename std::remove_reference_t<C>::value_type;
    typename std::remove_reference_t<C>::size_type;
    typename std::remove_reference_t<C>::iterator;
    typename std::remove_reference_t<C>::const_iterator;

    { c.begin() } noexcept -> std::same_as<typename std::remove_reference_t<C>::iterator>;
    { c.end() } noexcept -> std::same_as<typename std::remove_reference_t<C>::iterator>;
    { c.size() } noexcept -> std::same_as<typename std::remove_reference_t<C>::size_type>;
};

template<SetElementType T>
class Set; 

template<typename C>
concept IsSet = requires {
    typename std::remove_reference_t<C>::value_type;
} && std::same_as<
    Set<typename std::remove_reference_t<C>::value_type>,
    std::remove_reference_t<C>>;

template<typename C, typename T>
concept ConvertibleContainer = !IsSet<C> && Container<C> && Convertible<typename std::remove_reference_t<C>::value_type, T>;

template<typename It>
concept InputIterator = std::input_iterator<It>;

template<typename It>
concept Iterator = requires(It it) {
    typename std::remove_reference_t<It>::pointer;
    typename std::remove_reference_t<It>::reference;
    typename std::remove_reference_t<It>::difference_type;
    typename std::remove_reference_t<It>::iterator_category;
    { ++it } noexcept -> std::same_as<It&>;
    { it++ } noexcept -> std::same_as<It>;

};

template<typename It, typename T>
concept ConvertibleInputIterator = InputIterator<It> && Convertible<typename std::remove_reference_t<It>::value_type, T>;

template<typename S, typename It>
concept Sentinel = std::sentinel_for<S, It>;

template<typename R>
concept InputRange = std::ranges::input_range<R>;

template<typename R, typename T>
concept ConvertibleInputRange = !ConvertibleContainer<R, T> && InputRange<R> && Convertible<std::ranges::range_value_t<R>, T>;