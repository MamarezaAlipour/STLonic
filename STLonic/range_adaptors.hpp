#pragma once
#include <vector>
#include <iterator>
#include <algorithm>
#include <type_traits>

namespace stlonic {

    // filter adaptor: returns a vector of elements passing the predicate
    template <typename Iterable, typename Predicate>
    auto filter(const Iterable& iterable, Predicate pred) {
        std::vector<typename Iterable::value_type> result;
        for (const auto& item : iterable) {
            if (pred(item)) result.push_back(item);
        }
        return result;
    }

    // map adaptor: returns a vector of transformed elements
    template <typename Iterable, typename Func>
    auto map(const Iterable& iterable, Func func) {
        using result_type = std::decay_t<decltype(func(*std::begin(iterable)))>;
        std::vector<result_type> result;
        for (const auto& item : iterable) {
            result.push_back(func(item));
        }
        return result;
    }

}