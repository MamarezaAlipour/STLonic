#pragma once
#include <vector>
#include <iterator>

namespace stlonic {
    template <typename Container>
    std::vector<Container> chunk(const Container& c, std::size_t chunk_size) {
        std::vector<Container> result;
        auto it = c.begin();
        while (it != c.end()) {
            Container temp;
            for (std::size_t i = 0; i < chunk_size && it != c.end(); ++i, ++it) {
                temp.push_back(*it);
            }
            result.push_back(std::move(temp));
        }
        return result;
    }
}