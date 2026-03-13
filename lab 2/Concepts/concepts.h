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
concept GreaterComparable = requires(const T& t1, const T& t2) {
    { t1 < t2 } -> std::convertible_to<bool>;
    { t2 < t1 } -> std::convertible_to<bool>;
};

template<typename T>
concept EqualityComparable = requires(const T& t1, const T& t2) {
    { t1 == t2 } -> std::convertible_to<bool>;
    { t1 != t2 } -> std::convertible_to<bool>;
    { t2 == t1 } -> std::convertible_to<bool>;
    { t2 != t1 } -> std::convertible_to<bool>;
};

template<typename T>
concept IncreasingComparable = GreaterComparable<T> && EqualityComparable<T>;

template<typename T>
concept ContainerElementType = CopyMoveAssignable<T> 
                            && CopyMoveConstructible<T>
                            && std::destructible<T> 
                            && IncreasingComparable<T>;

template<typename From, typename To>
concept Convertible = std::same_as<From, To> || std::convertible_to<From, To>;

template<typename T, typename U>
concept HasCommon = requires { typename std::common_type_t<T, U>; };

template<typename C>
concept Container = CopyMoveConstructible<C> && std::destructible<C> && requires(C c) {
    typename std::remove_reference_t<C>::value_type;
    typename std::remove_reference_t<C>::size_type;
    typename std::remove_reference_t<C>::iterator;
    typename std::remove_reference_t<C>::const_iterator;

    { c.cbegin() } noexcept -> std::same_as<typename std::remove_reference_t<C>::const_iterator>;
    { c.cend() } noexcept -> std::same_as<typename std::remove_reference_t<C>::const_iterator>;
};

template<typename C, typename T>
concept ConvertibleContainer = Container<C> && Convertible<typename std::remove_reference_t<C>::value_type, T>;

template<typename It>
concept InputIterator = std::input_iterator<It>;

template<typename It, typename T>
concept ConvertibleInputIterator = InputIterator<It> && Convertible<typename std::remove_reference_t<It>::value_type, T>;

template<typename S, typename It>
concept Sentinel = std::sentinel_for<S, It>;

template<typename R>
concept InputRange = std::ranges::input_range<R>;

template<typename R, typename T>
concept ConvertibleInputRange = InputRange<R> && Convertible<std::ranges::range_value_t<R>, T>;