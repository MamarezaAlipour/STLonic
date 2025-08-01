#pragma once
#include <vector>
#include <utility>

namespace stlonic {
    template <typename Container1, typename Container2>
    auto cartesian_product(const Container1& c1, const Container2& c2) {
        using T1 = typename Container1::value_type;
        using T2 = typename Container2::value_type;
        std::vector<std::pair<T1, T2>> result;
        for (const auto& a : c1)
            for (const auto& b : c2)
                result.emplace_back(a, b);
        return result;
    }
}
