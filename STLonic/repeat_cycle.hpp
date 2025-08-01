#pragma once
#include <vector>

namespace stlonic {
    template <typename T>
    std::vector<T> repeat(const T& value, std::size_t n) {
        return std::vector<T>(n, value);
    }

    template <typename Container>
    std::vector<typename Container::value_type> cycle(const Container& c, std::size_t n) {
        std::vector<typename Container::value_type> result;
        if (c.empty() || n == 0) return result;
        result.reserve(c.size() * n);
        for (std::size_t i = 0; i < n; ++i)
            result.insert(result.end(), c.begin(), c.end());
        return result;
    }
}
