#pragma once
#include <cstddef>
#include <iterator>
#include <utility>

namespace stlonic {
    template <typename Iterable>
    class enumerate_object {
        Iterable& iterable;
    public:
        enumerate_object(Iterable& iterable) : iterable(iterable) {}

        struct iterator {
            std::size_t idx;
            decltype(std::begin(iterable)) it;
            bool operator!=(const iterator& other) const { return it != other.it; }
            void operator++() { ++idx; ++it; }
            auto operator*() const { return std::make_pair(idx, *it); }
        };

        iterator begin() { return {0, std::begin(iterable)}; }
        iterator end() { return {0, std::end(iterable)}; }
    };

    template <typename Iterable>
    enumerate_object<Iterable> enumerate(Iterable& iterable) {
        return enumerate_object<Iterable>(iterable);
    }
}