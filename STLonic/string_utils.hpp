#pragma once
#include <string>
#include <sstream>
#include <iterator>

namespace stlonic {
    template <typename Iterable>
    std::string join(const Iterable& iterable, const std::string& separator) {
        std::ostringstream oss;
        auto it = std::begin(iterable);
        if (it != std::end(iterable)) {
            oss << *it;
            ++it;
        }
        while (it != std::end(iterable)) {
            oss << separator << *it;
            ++it;
        }
        return oss.str();
    }
}