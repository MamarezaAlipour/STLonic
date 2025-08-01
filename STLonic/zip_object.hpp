#pragma once
#include <iterator>
#include <utility>

namespace stlonic {
	template <typename Iterable1, typename Iterable2>
	class zip_object {
		Iterable1& iterable1;
		Iterable2& iterable2;

	  public:
		zip_object(Iterable1& i1, Iterable2& i2)
			: iterable1(i1)
			, iterable2(i2) {}

		struct iterator {
			decltype(std::begin(iterable1)) it1;
			decltype(std::begin(iterable2)) it2;
			bool operator!=(const iterator& other) const {
				return it1 != other.it1 && it2 != other.it2;
			}
			void operator++() {
				++it1;
				++it2;
			}
			auto operator*() const {
				return std::make_pair(*it1, *it2);
			}
		};

		iterator begin() {
			return {std::begin(iterable1), std::begin(iterable2)};
		}
		iterator end() {
			return {std::end(iterable1), std::end(iterable2)};
		}
	};

	template <typename Iterable1, typename Iterable2>
	zip_object<Iterable1, Iterable2> zip(Iterable1& i1, Iterable2& i2) {
		return zip_object<Iterable1, Iterable2>(i1, i2);
	}
} // namespace stlonic