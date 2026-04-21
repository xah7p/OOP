#include <type_traits>

template<typename Derived, typename Base>
concept Derivative = std::is_abstract_v<Base> && std::is_base_of_v<Base, Derived>;

template<typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;

template<typename Type, typename... Args>
concept Constructible = std::is_constructible_v<Type, Args...>;