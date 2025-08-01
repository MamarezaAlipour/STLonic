#pragma once
#include <optional>
#include <utility>

namespace stlonic {
    template <typename Optional, typename Default>
    auto value_or(const Optional& opt, Default&& def) -> decltype(opt.value()) {
        return opt ? *opt : std::forward<Default>(def);
    }
}