#pragma once
#include <iterator>

namespace stlonic {
    template <typename OuterContainer>
    auto flatten(const OuterContainer& outer) {
        using Inner = typename OuterContainer::value_type;
        using T = typename Inner::value_type;
        std::vector<T> result;
        for (const auto& inner : outer) {
            result.insert(result.end(), inner.begin(), inner.end());
        }
        return result;
    }
}