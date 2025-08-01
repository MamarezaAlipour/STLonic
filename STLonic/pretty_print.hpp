// Add this to STLonic/pretty_print.hpp if not already present

#pragma once
#include <ostream>
#include <map>

namespace stlonic {

// Pretty print for std::map<K, V>
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) os << ", ";
        os << kv.first << ": " << kv.second;
        first = false;
    }
    os << "}";
    return os;
}

} // namespace stlonic
