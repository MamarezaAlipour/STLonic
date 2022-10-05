/*
Author: Parisa Khaleghi
Edit: Oct. 04, 2022 - safe binary operation
*/

#ifndef _STLONIC_TUPLE_OPERATIONS_HPP
#define _STLONIC_TUPLE_OPERATIONS_HPP

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "types.hpp"

namespace std::inline stl_extensions {
	namespace stl = stlonic::types;

	namespace hidden {
		template <bool bSigned, stl::numerical_c Left, stl::numerical_c Right>
		constexpr auto tuple_common_elements(Left, Right) noexcept {
			if constexpr (bSigned)
				return stl::common_signed_t<Left, Right> {};
			else
				return stl::common_unsigned_t<Left, Right> {};
		}

		template <bool bSigned = true, typename... Elements, stl::non_tuple_c Scalar>
		constexpr auto tuple_common_elements(std::tuple<Elements...>, Scalar) noexcept {
			return std::tuple {tuple_common_elements<bSigned>(Elements {}, Scalar {})...};
		}

		template <bool bSigned = true, typename T, std::size_t N, stl::numerical_c Scalar>
		constexpr auto tuple_common_elements(std::array<T, N>, Scalar) noexcept {
			return std::array<stl::common_signed_t<T, Scalar>, N> {};
		}

		template <bool bSigned = true, typename T, std::size_t N, stl::numerical_c Scalar>
		constexpr auto tuple_common_elements(Scalar, std::array<T, N>) noexcept {
			return std::array<stl::common_signed_t<T, Scalar>, N> {};
		}

		template <bool bSigned = true, typename T, stl::numerical_c Scalar>
		constexpr auto tuple_common_elements(std::vector<T>, Scalar) noexcept {
			return std::vector<stl::common_signed_t<T, Scalar>> {};
		}

		template <bool bSigned = true, typename T, stl::numerical_c Scalar>
		constexpr auto tuple_common_elements(Scalar, std::vector<T>) noexcept {
			return std::vector<stl::common_signed_t<T, Scalar>> {};
		}

		template <bool bSigned = true, typename... Lefts, typename... Rights>
		requires(sizeof...(Lefts) == sizeof...(Rights)) constexpr auto tuple_common_elements(
			std::tuple<Lefts...>, std::tuple<Rights...>) noexcept {
			return std::tuple {tuple_common_elements<bSigned>(Lefts {}, Rights {})...};
		}

		// signed common
		template <typename... Lefts, typename... Rights>
		requires(sizeof...(Lefts) == sizeof...(Rights)) constexpr auto
			operator|(std::tuple<Lefts...>, std::tuple<Rights...>) noexcept {
			return std::tuple {tuple_common_elements<true>(Lefts {}, Rights {})...};
		}

		template <typename... Elements, stl::non_tuple_c Scalar>
		constexpr auto operator|(std::tuple<Elements...>, Scalar) noexcept {
			using c_t = std::tuple<Elements...>;
			return std::tuple {tuple_common_elements<true>(Elements {}, Scalar {})...};
		}

		template <typename... Elements, stl::non_tuple_c Scalar>
		constexpr auto operator|(Scalar, std::tuple<Elements...>) noexcept {
			using c_t = std::tuple<Elements...>;
			return std::tuple {tuple_common_elements<true>(Scalar {}, Elements {})...};
		}

		// unsigned common
		template <typename... Lefts, typename... Rights>
		requires(sizeof...(Lefts) == sizeof...(Rights)) constexpr auto
			operator||(std::tuple<Lefts...>, std::tuple<Rights...>) noexcept {
			return std::tuple {tuple_common_elements<false>(Lefts {}, Rights {})...};
		}

		template <typename... Elements, stl::non_tuple_c Scalar>
		constexpr auto operator||(std::tuple<Elements...>, Scalar) noexcept {
			using c_t = std::tuple<Elements...>;
			return std::tuple {tuple_common_elements<false>(Elements {}, Scalar {})...};
		}
	} // namespace hidden
	// end of namespace hidde

	template <typename T, typename... Tails>
	constexpr auto signed_tuple_operation(T arg, Tails... args) noexcept {
		using namespace hidden;
		return (arg | ... | args);
	}

	template <typename T, typename... Tails>
	constexpr auto unsigned_tuple_operation(T arg, Tails... args) noexcept {
		using namespace hidden;
		return (arg || ... || args);
	}

	template <stl::tuple_flat_c LeftType, stl::tuple_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) constexpr decltype(auto)
		operator+(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_a_t = std::remove_cvref_t<LeftType>;
		using container_b_t = std::remove_cvref_t<RightType>;

		if constexpr (std::same_as<container_a_t, container_b_t> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(a) + stl::sbo(std::get<i.value>(B));
			});

			return std::move(A);
		} else if constexpr (std::same_as<container_a_t, container_b_t> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			stl::for_workhorse(B, [&](auto i, auto&& b) {
				b = stl::sbo(b) + stl::sbo(std::get<i.value>(A));
			});

			return std::move(B);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_a_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				auto opr = []<typename L, typename R>(L& a, R& b) {
					return stl::sbo(a) + stl::sbo(b);
				};

				return std::tuple {opr(std::get<i>(A), std::get<i>(B))...};
			});
		}
	}

	template <stl::tuple_flat_c LeftType, stl::tuple_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) constexpr decltype(auto)
		operator-(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_a_t = std::remove_cvref_t<LeftType>;
		using container_b_t = std::remove_cvref_t<RightType>;

		if constexpr (std::same_as<container_a_t, container_b_t> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(a) - stl::sbo(std::get<i.value>(B));
			});

			return std::move(A);
		} else if constexpr (std::same_as<container_a_t, container_b_t> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			stl::for_workhorse(B, [&](auto i, auto&& b) {
				b = stl::sbo(b) - stl::sbo(std::get<i.value>(A));
			});

			return std::move(B);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_a_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				auto opr = []<typename L, typename R>(L& a, R& b) {
					return stl::sbo(a) - stl::sbo(b);
				};

				return std::tuple {opr(std::get<i>(A), std::get<i>(B))...};
			});
		}
	}

	template <stl::tuple_flat_c LeftType, stl::tuple_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) constexpr decltype(auto)
		operator*(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_a_t = std::remove_cvref_t<LeftType>;
		using container_b_t = std::remove_cvref_t<RightType>;

		if constexpr (std::same_as<container_a_t, container_b_t> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(a) * stl::sbo(std::get<i.value>(B));
			});

			return std::move(A);
		} else if constexpr (std::same_as<container_a_t, container_b_t> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			stl::for_workhorse(B, [&](auto i, auto&& b) {
				b = stl::sbo(b) * stl::sbo(std::get<i.value>(A));
			});

			return std::move(B);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_a_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				auto opr = []<typename L, typename R>(L& a, R& b) {
					return stl::sbo(a) * stl::sbo(b);
				};

				return std::tuple {opr(std::get<i>(A), std::get<i>(B))...};
			});
		}
	}

	template <stl::tuple_flat_c LeftType, stl::tuple_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) constexpr decltype(auto)
		operator/(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_a_t = std::remove_cvref_t<LeftType>;
		using container_b_t = std::remove_cvref_t<RightType>;

		if constexpr (std::same_as<container_a_t, container_b_t> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(a) / stl::sbo(std::get<i.value>(B));
			});

			return std::move(A);
		} else if constexpr (std::same_as<container_a_t, container_b_t> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			stl::for_workhorse(B, [&](auto i, auto&& b) {
				b = stl::sbo(b) / stl::sbo(std::get<i.value>(A));
			});

			return std::move(B);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_a_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				auto opr = []<typename L, typename R>(L& a, R& b) {
					return stl::sbo(a) / stl::sbo(b);
				};

				return std::tuple {opr(std::get<i>(A), std::get<i>(B))...};
			});
		}
	}

	////////////////////////////////////////////////////////////////////////////

	namespace hidden {
		template <typename T, typename S>
		struct st_tuple_scalar_signed_cast {
			using type = stl::common_signed_t<T, S>;
		};

		template <typename... Types, stl::non_tuple_c ScalarType>
		struct st_tuple_scalar_signed_cast<std::tuple<Types...>, ScalarType> {
			using type = ScalarType;
		};

		template <typename T, typename S>
		struct st_tuple_scalar_unsigned_cast {
			using type = stl::common_unsigned_t<T, S>;
		};

		template <typename... Types, stl::non_tuple_c ScalarType>
		struct st_tuple_scalar_unsigned_cast<std::tuple<Types...>, ScalarType> {
			using type = ScalarType;
		};
	} // namespace hidden
	// end of namespace hidden

	template <typename T, typename S>
	using tuple_scalar_signed_cast = typename hidden::st_tuple_scalar_signed_cast<T, S>::type;

	template <typename T, typename S>
	using tuple_scalar_unsigned_cast = typename hidden::st_tuple_scalar_unsigned_cast<T, S>::type;

	template <stl::tuple_flat_c TupleType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator+(TupleType&& A,
									   ScalarType scalar) noexcept(!stlonic::bDetectOverFlow) {
		using container_t = std::remove_cvref_t<TupleType>;
		using c_t = decltype(signed_tuple_operation(A, scalar));

		if constexpr (std::same_as<container_t, c_t> && std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(a) + stl::sbo(scalar);
			});

			return std::move(A);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				return c_t {stl::sbo(std::get<i>(A)) + stl::sbo(scalar)...};
			});
		}
	}

	template <stl::tuple_flat_c TupleType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator+(ScalarType scalar,
									   TupleType&& A) noexcept(!stlonic::bDetectOverFlow) {
		using container_t = std::remove_cvref_t<TupleType>;
		using c_t = decltype(signed_tuple_operation(A, scalar));

		if constexpr (std::same_as<container_t, c_t> && std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(scalar) + stl::sbo(a);
			});

			return std::move(A);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				return c_t {stl::sbo(scalar) + stl::sbo(std::get<i>(A))...};
			});
		}
	}

	template <stl::tuple_flat_c TupleType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator-(TupleType&& A,
									   ScalarType scalar) noexcept(!stlonic::bDetectOverFlow) {
		using container_t = std::remove_cvref_t<TupleType>;
		using c_t = decltype(signed_tuple_operation(A, scalar));

		if constexpr (std::same_as<container_t, c_t> && std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(a) - stl::sbo(scalar);
			});

			return std::move(A);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				return c_t {stl::sbo(std::get<i>(A)) - stl::sbo(scalar)...};
			});
		}
	}

	template <stl::tuple_flat_c TupleType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator-(ScalarType scalar,
									   TupleType&& A) noexcept(!stlonic::bDetectOverFlow) {
		using container_t = std::remove_cvref_t<TupleType>;
		using c_t = decltype(signed_tuple_operation(A, scalar));

		if constexpr (std::same_as<container_t, c_t> && std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(scalar) - stl::sbo(a);
			});

			return std::move(A);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				return c_t {stl::sbo(scalar) - stl::sbo(std::get<i>(A))...};
			});
		}
	}

	template <stl::tuple_flat_c TupleType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator*(TupleType&& A,
									   ScalarType scalar) noexcept(!stlonic::bDetectOverFlow) {
		using container_t = std::remove_cvref_t<TupleType>;
		using c_t = decltype(signed_tuple_operation(A, scalar));

		if constexpr (std::same_as<container_t, c_t> && std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(a) * stl::sbo(scalar);
			});

			return std::move(A);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				return c_t {stl::sbo(std::get<i>(A)) * stl::sbo(scalar)...};
			});
		}
	}

	template <stl::tuple_flat_c TupleType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator*(ScalarType scalar,
									   TupleType&& A) noexcept(!stlonic::bDetectOverFlow) {
		using container_t = std::remove_cvref_t<TupleType>;
		using c_t = decltype(signed_tuple_operation(A, scalar));

		if constexpr (std::same_as<container_t, c_t> && std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(scalar) * stl::sbo(a);
			});

			return std::move(A);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				return c_t {stl::sbo(scalar) * stl::sbo(std::get<i>(A))...};
			});
		}
	}

	template <stl::tuple_flat_c TupleType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator/(TupleType&& A,
									   ScalarType scalar) noexcept(!stlonic::bDetectOverFlow) {
		using container_t = std::remove_cvref_t<TupleType>;
		using c_t = decltype(signed_tuple_operation(A, scalar));

		if constexpr (std::same_as<container_t, c_t> && std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(a) / stl::sbo(scalar);
			});

			return std::move(A);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				return c_t {stl::sbo(std::get<i>(A)) / stl::sbo(scalar)...};
			});
		}
	}

	template <stl::tuple_flat_c TupleType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator/(ScalarType scalar,
									   TupleType&& A) noexcept(!stlonic::bDetectOverFlow) {
		using container_t = std::remove_cvref_t<TupleType>;
		using c_t = decltype(signed_tuple_operation(A, scalar));

		if constexpr (std::same_as<container_t, c_t> && std::is_rvalue_reference_v<decltype(A)>) {
			stl::for_workhorse(A, [&](auto i, auto&& a) {
				a = stl::sbo(scalar) / stl::sbo(a);
			});

			return std::move(A);
		} else {
			constexpr std::size_t N = std::tuple_size_v<container_t>;
			return stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
				return c_t {stl::sbo(scalar) / stl::sbo(std::get<i>(A))...};
			});
		}
	}
} // namespace std::inline stl_extensions
// end of namespace std

#endif // end of file