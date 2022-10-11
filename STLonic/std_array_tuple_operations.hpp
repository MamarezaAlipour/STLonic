/*
	Author: Parisa Khaleghi
	Edit: Oct. 10, 2022
*/

#ifndef _STLONIC_STD_ARRAY_TUPLE_OPERATIONS_HPP
#define _STLONIC_STD_ARRAY_TUPLE_OPERATIONS_HPP

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "std_array_operations.hpp"
#include "tuple_operations.hpp"

namespace std::inline stl_extensions {
	namespace stl = stlonic::types;

	template <stl::numerical_c H, stl::numerical_c... Ts>
	constexpr decltype(auto) tuple_to_array(std::tuple<H, Ts...> const& tuple) noexcept {
		using element_t = stl::common_signed_t<H, Ts...>;

		return stl::for_stallion<sizeof...(Ts) + 1>([&]<auto... i>(stl::sequence<i...>) {
			return std::array {static_cast<element_t>(std::get<i>(tuple))...};
		});
	}

	template <stl::tuple_flat_c H, stl::tuple_flat_c... Ts>
	requires(!stl::all_same_flat_c<H, Ts...>) &&
		(std::tuple_size_v<H> == ... == std::tuple_size_v<Ts>)constexpr decltype(auto)
			tuple_to_array(std::tuple<H, Ts...> const& tuple) noexcept {
		using tt = decltype(signed_tuple_operation(H {}, Ts {}...));

		return stl::for_stallion<sizeof...(Ts) + 1>([&]<auto... i>(stl::sequence<i...>) {
			return std::array {tuple_to_array(static_cast<tt>(std::get<i>(tuple)))...};
		});
	}

	template <stl::tuple_flat_c H, stl::tuple_flat_c... Ts>
	requires stl::all_same_flat_c<H, Ts...>
	constexpr decltype(auto) tuple_to_array(std::tuple<H, Ts...> const& tuple) noexcept {
		return stl::for_stallion<sizeof...(Ts) + 1>([&]<auto... i>(stl::sequence<i...>) {
			return std::array {tuple_to_array(std::get<i>(tuple))...};
		});
	}

	template <stl::numerical_c E, std::size_t N>
	constexpr decltype(auto) array_to_tuple(std::array<E, N> const& array) noexcept {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			return std::tuple {std::get<i>(array)...};
		});
	}

	template <stl::std_array_flat_c E, std::size_t N>
	constexpr decltype(auto) array_to_tuple(std::array<E, N> const& array) noexcept {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			return std::tuple {array_to_tuple(std::get<i>(array))...};
		});
	}

	///////////////////////////////////////////////////////////////////////////////////////
	template <stl::numerical_c E, std::size_t N, stl::numerical_c H, stl::numerical_c... Ts>
	requires(N == sizeof...(Ts) + 1) constexpr decltype(auto)
		operator+(std::array<E, N> const& A,
				  std::tuple<H, Ts...> const& T) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {stl::sbo(std::get<i>(A)) + stl::sbo(std::get<i>(T))...};
			else
				return std::tuple {stl::sbo(std::get<i>(A)) + stl::sbo(std::get<i>(T))...};
		});
	}

	template <stl::numerical_c E, std::size_t N, stl::numerical_c H, stl::numerical_c... Ts>
	requires(N == sizeof...(Ts) + 1) constexpr decltype(auto)
		operator+(std::tuple<H, Ts...> const& T,
				  std::array<E, N> const& A) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {stl::sbo(std::get<i>(A)) + stl::sbo(std::get<i>(T))...};
			else
				return std::tuple {stl::sbo(std::get<i>(A)) + stl::sbo(std::get<i>(T))...};
		});
	}

	template <typename E, std::size_t N, typename H, typename... Ts>
	requires(N == sizeof...(Ts) + 1) &&
		(!(stl::numerical_c<E> &&
		   (stl::numerical_c<H> && ... && stl::numerical_c<Ts>))) constexpr decltype(auto)
			operator+(std::array<E, N> const& A,
					  std::tuple<H, Ts...> const& T) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {std::get<i>(A) + std::get<i>(T)...};
			else
				return std::tuple {std::get<i>(A) + std::get<i>(T)...};
		});
	}

	template <typename E, std::size_t N, typename H, typename... Ts>
	requires(N == sizeof...(Ts) + 1) &&
		(!(stl::numerical_c<E> &&
		   (stl::numerical_c<H> && ... && stl::numerical_c<Ts>))) constexpr decltype(auto)
			operator+(std::tuple<H, Ts...> const& T,
					  std::array<E, N> const& A) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {std::get<i>(T) + std::get<i>(A)...};
			else
				return std::tuple {std::get<i>(T) + std::get<i>(A)...};
		});
	}

	///////////////////////////////////////////////////////////////////////////////////////

	template <stl::numerical_c E, std::size_t N, stl::numerical_c H, stl::numerical_c... Ts>
	requires(N == sizeof...(Ts) + 1) constexpr decltype(auto)
		operator-(std::array<E, N> const& A,
				  std::tuple<H, Ts...> const& T) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {stl::sbo(std::get<i>(A)) - stl::sbo(std::get<i>(T))...};
			else
				return std::tuple {stl::sbo(std::get<i>(A)) - stl::sbo(std::get<i>(T))...};
		});
	}

	template <stl::numerical_c E, std::size_t N, stl::numerical_c H, stl::numerical_c... Ts>
	requires(N == sizeof...(Ts) + 1) constexpr decltype(auto)
		operator-(std::tuple<H, Ts...> const& T,
				  std::array<E, N> const& A) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {stl::sbo(std::get<i>(T)) - stl::sbo(std::get<i>(A))...};
			else
				return std::tuple {stl::sbo(std::get<i>(T)) - stl::sbo(std::get<i>(A))...};
		});
	}

	template <typename E, std::size_t N, typename H, typename... Ts>
	requires(N == sizeof...(Ts) + 1) &&
		(!(stl::numerical_c<E> &&
		   (stl::numerical_c<H> && ... && stl::numerical_c<Ts>))) constexpr decltype(auto)
			operator-(std::array<E, N> const& A,
					  std::tuple<H, Ts...> const& T) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {std::get<i>(A) - std::get<i>(T)...};
			else
				return std::tuple {std::get<i>(A) - std::get<i>(T)...};
		});
	}

	template <typename E, std::size_t N, typename H, typename... Ts>
	requires(N == sizeof...(Ts) + 1) &&
		(!(stl::numerical_c<E> &&
		   (stl::numerical_c<H> && ... && stl::numerical_c<Ts>))) constexpr decltype(auto)
			operator-(std::tuple<H, Ts...> const& T,
					  std::array<E, N> const& A) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {std::get<i>(T) - std::get<i>(A)...};
			else
				return std::tuple {std::get<i>(T) - std::get<i>(A)...};
		});
	}

	///////////////////////////////////////////////////////////////////////////////////////

	template <stl::numerical_c E, std::size_t N, stl::numerical_c H, stl::numerical_c... Ts>
	requires(N == sizeof...(Ts) + 1) constexpr decltype(auto)
		operator*(std::array<E, N> const& A,
				  std::tuple<H, Ts...> const& T) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {stl::sbo(std::get<i>(A)) * stl::sbo(std::get<i>(T))...};
			else
				return std::tuple {stl::sbo(std::get<i>(A)) * stl::sbo(std::get<i>(T))...};
		});
	}

	template <stl::numerical_c E, std::size_t N, stl::numerical_c H, stl::numerical_c... Ts>
	requires(N == sizeof...(Ts) + 1) constexpr decltype(auto)
		operator*(std::tuple<H, Ts...> const& T,
				  std::array<E, N> const& A) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {stl::sbo(std::get<i>(T)) * stl::sbo(std::get<i>(A))...};
			else
				return std::tuple {stl::sbo(std::get<i>(T)) * stl::sbo(std::get<i>(A))...};
		});
	}

	template <typename E, std::size_t N, typename H, typename... Ts>
	requires(N == sizeof...(Ts) + 1) &&
		(!(stl::numerical_c<E> &&
		   (stl::numerical_c<H> && ... && stl::numerical_c<Ts>))) constexpr decltype(auto)
			operator*(std::array<E, N> const& A,
					  std::tuple<H, Ts...> const& T) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {std::get<i>(A) * std::get<i>(T)...};
			else
				return std::tuple {std::get<i>(A) * std::get<i>(T)...};
		});
	}

	template <typename E, std::size_t N, typename H, typename... Ts>
	requires(N == sizeof...(Ts) + 1) &&
		(!(stl::numerical_c<E> &&
		   (stl::numerical_c<H> && ... && stl::numerical_c<Ts>))) constexpr decltype(auto)
			operator*(std::tuple<H, Ts...> const& T,
					  std::array<E, N> const& A) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {std::get<i>(T) * std::get<i>(A)...};
			else
				return std::tuple {std::get<i>(T) * std::get<i>(A)...};
		});
	}

	////////////////////////////////////////////////////////////////////////////////////////

	template <stl::numerical_c E, std::size_t N, stl::numerical_c H, stl::numerical_c... Ts>
	requires(N == sizeof...(Ts) + 1) constexpr decltype(auto)
		operator/(std::array<E, N> const& A,
				  std::tuple<H, Ts...> const& T) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {stl::sbo(std::get<i>(A)) / stl::sbo(std::get<i>(T))...};
			else
				return std::tuple {stl::sbo(std::get<i>(A)) / stl::sbo(std::get<i>(T))...};
		});
	}

	template <stl::numerical_c E, std::size_t N, stl::numerical_c H, stl::numerical_c... Ts>
	requires(N == sizeof...(Ts) + 1) constexpr decltype(auto)
		operator/(std::tuple<H, Ts...> const& T,
				  std::array<E, N> const& A) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {stl::sbo(std::get<i>(T)) / stl::sbo(std::get<i>(A))...};
			else
				return std::tuple {stl::sbo(std::get<i>(T)) / stl::sbo(std::get<i>(A))...};
		});
	}

	template <typename E, std::size_t N, typename H, typename... Ts>
	requires(N == sizeof...(Ts) + 1) &&
		(!(stl::numerical_c<E> &&
		   (stl::numerical_c<H> && ... && stl::numerical_c<Ts>))) constexpr decltype(auto)
			operator/(std::array<E, N> const& A,
					  std::tuple<H, Ts...> const& T) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {std::get<i>(A) / std::get<i>(T)...};
			else
				return std::tuple {std::get<i>(A) / std::get<i>(T)...};
		});
	}

	template <typename E, std::size_t N, typename H, typename... Ts>
	requires(N == sizeof...(Ts) + 1) &&
		(!(stl::numerical_c<E> &&
		   (stl::numerical_c<H> && ... && stl::numerical_c<Ts>))) constexpr decltype(auto)
			operator/(std::tuple<H, Ts...> const& T,
					  std::array<E, N> const& A) noexcept(!stlonic::bDetectOverFlow) {
		return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			if constexpr (stl::all_same_c<H, Ts...>)
				return std::array {std::get<i>(T) / std::get<i>(A)...};
			else
				return std::tuple {std::get<i>(T) / std::get<i>(A)...};
		});
	}
} // namespace std::inline stl_extensions
// end of namespace std

#endif
// end of file 