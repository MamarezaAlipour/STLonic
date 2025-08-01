#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace stlonic {
    // For sequence containers (vector, list, deque, etc.)
    template <typename Container, typename T>
    bool contains(const Container& c, const T& value) {
        return std::find(std::begin(c), std::end(c), value) != std::end(c);
    }

    // For associative containers (set, unordered_set)
    template <typename Set, typename T>
    auto contains(const Set& s, const T& value) -> decltype(s.find(value), bool()) {
        return s.find(value) != s.end();
    }

    // For map-like containers (map, unordered_map)
    template <typename Map, typename Key>
    auto contains_key(const Map& m, const Key& key) -> decltype(m.find(key), bool()) {
        return m.find(key) != m.end();
    }

    template <typename Container, typename Predicate>
    void erase_if(Container& c, Predicate pred) {
        c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
    }

    template <typename Iterable>
    auto to_vector(const Iterable& iterable) {
        return std::vector<typename Iterable::value_type>(std::begin(iterable), std::end(iterable));
    }

    template <typename Iterable>
    auto to_set(const Iterable& iterable) {
        return std::set<typename Iterable::value_type>(std::begin(iterable), std::end(iterable));
    }

    template <typename Iterable>
    auto to_unordered_set(const Iterable& iterable) {
        return std::unordered_set<typename Iterable::value_type>(std::begin(iterable), std::end(iterable));
    }

    template <typename Iterable>
    auto to_map(const Iterable& iterable) {
        using pair_type = typename Iterable::value_type;
        using key_type = typename pair_type::first_type;
        using mapped_type = typename pair_type::second_type;
        return std::map<key_type, mapped_type>(std::begin(iterable), std::end(iterable));
    }

    template <typename Iterable>
    auto to_unordered_map(const Iterable& iterable) {
        using pair_type = typename Iterable::value_type;
        using key_type = typename pair_type::first_type;
        using mapped_type = typename pair_type::second_type;
        return std::unordered_map<key_type, mapped_type>(std::begin(iterable), std::end(iterable));
    }

    template <typename Iterable, typename Func>
    void for_each(const Iterable& iterable, Func&& func) {
        std::for_each(std::begin(iterable), std::end(iterable), std::forward<Func>(func));
    }

    template <typename Iterable, typename Predicate>
    bool all_of(const Iterable& iterable, Predicate pred) {
        return std::all_of(std::begin(iterable), std::end(iterable), pred);
    }

    template <typename Iterable, typename Predicate>
    bool any_of(const Iterable& iterable, Predicate pred) {
        return std::any_of(std::begin(iterable), std::end(iterable), pred);
    }

    template <typename Iterable, typename Predicate>
    bool none_of(const Iterable& iterable, Predicate pred) {
        return std::none_of(std::begin(iterable), std::end(iterable), pred);
    }

    template <typename Map, typename Key, typename Default>
    auto find_or(const Map& m, const Key& key, Default&& def) -> decltype(m.at(key)) {
        auto it = m.find(key);
        if (it != m.end())
            return it->second;
        return std::forward<Default>(def);
    }

    template <typename Container, typename T>
    std::ptrdiff_t index_of(const Container& c, const T& value) {
        auto it = std::find(std::begin(c), std::end(c), value);
        if (it == std::end(c))
            return -1;
        return std::distance(std::begin(c), it);
    }

    template <typename Container>
    Container reverse(const Container& c) {
        Container result = c;
        std::reverse(result.begin(), result.end());
        return result;
    }

    template <typename Container>
    Container unique(const Container& c) {
        Container result;
        std::set<typename Container::value_type> seen;
        for (const auto& item : c) {
            if (seen.insert(item).second)
                result.push_back(item);
        }
        return result;
    }

    template <typename Container>
	auto min_element(const Container& c) -> typename Container::value_type {
		return *std::min_element(c.begin(), c.end());
	}

	template <typename Container, typename Compare>
	auto min_element(const Container& c, Compare comp) -> typename Container::value_type {
		return *std::min_element(c.begin(), c.end(), comp);
	}

	template <typename Container>
	auto max_element(const Container& c) -> typename Container::value_type {
		return *std::max_element(c.begin(), c.end());
	}

	template <typename Container, typename Compare>
	auto max_element(const Container& c, Compare comp) -> typename Container::value_type {
		return *std::max_element(c.begin(), c.end(), comp);
	}

	template <typename Container>
	std::vector<Container> sliding_window(const Container& c, std::size_t window_size) {
		std::vector<Container> result;
		if (window_size == 0 || c.size() < window_size)
			return result;
		for (auto it = c.begin(); std::distance(it, c.end()) >= static_cast<ptrdiff_t>(window_size);
			 ++it) {
			auto last = it;
			std::advance(last, window_size);
			result.emplace_back(it, last);
		}
		return result;
	}

	template <typename Container, typename Predicate>
	std::pair<Container, Container> partition(const Container& c, Predicate pred) {
		Container t, f;
		for (const auto& x : c) {
			(pred(x) ? t : f).push_back(x);
		}
		return {t, f};
	}

	template <typename Container, typename KeyFunc>
	auto group_by(const Container& c, KeyFunc key_func) {
		using key_type = decltype(key_func(*c.begin()));
		using value_type = typename Container::value_type;
		std::map<key_type, std::vector<value_type>> result;
		for (const auto& x : c) {
			result[key_func(x)].push_back(x);
		}
		return result;
	}

	template <typename Container>
	Container take(const Container& c, std::size_t n) {
		auto it = c.begin();
		std::advance(it, std::min(n, c.size()));
		return Container(c.begin(), it);
	}

	template <typename Container>
	Container drop(const Container& c, std::size_t n) {
		auto it = c.begin();
		std::advance(it, std::min(n, c.size()));
		return Container(it, c.end());
	}
}