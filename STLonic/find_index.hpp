#pragma once
#include <iterator>
#include <algorithm>

namespace stlonic {
    template <typename Container, typename T>
    std::ptrdiff_t find_index(const Container& c, const T& value) {
        auto it = std::find(c.begin(), c.end(), value);
        return it == c.end() ? -1 : std::distance(c.begin(), it);
    }

    template <typename Container, typename Predicate>
    std::ptrdiff_t find_index_if(const Container& c, Predicate pred) {
        auto it = std::find_if(c.begin(), c.end(), pred);
        return it == c.end() ? -1 : std::distance(c.begin(), it);
    }

    template <typename Container, typename T>
    std::ptrdiff_t find_last_index(const Container& c, const T& value) {
        auto rit = std::find(c.rbegin(), c.rend(), value);
        return rit == c.rend() ? -1 : std::distance(c.begin(), rit.base()) - 1;
    }
}
