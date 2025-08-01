#pragma once
#include <type_traits>

namespace stlonic {
    template <typename T, typename... Ts>
    struct is_one_of : std::disjunction<std::is_same<T, Ts>...> {};

    template <typename T, typename... Ts>
    constexpr bool is_one_of_v = is_one_of<T, Ts...>::value;
}
