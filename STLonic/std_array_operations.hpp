/*
	Author: Geek pww
	Edit: Oct. 08, 2022
*/

#ifndef _STLONIC_STD_ARRAY_OPERATIONS_HPP
#define _STLONIC_STD_ARRAY_OPERATIONS_HPP

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "types.hpp"

namespace std::inline stl_extensions {
	namespace stl = stlonic::types;

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) &&
			(stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
			 stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>) ||
		(stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		 stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>)&&stl::
			common_std_array_c<LeftType, RightType> constexpr decltype(auto)
				operator+(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::same_as<container_t_a, container_t_b> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(A[i]) + stl::sbo(B[i]);

			return std::move(A);
		} else if constexpr (std::same_as<container_t_a, container_t_b> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = stl::sbo(A[i]) + stl::sbo(B[i]);

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(A[i]) + stl::sbo(B[i]);

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) &&
			(stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
			 stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>) ||
		(stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		 stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>)&&stl::
			common_std_array_c<LeftType, RightType> constexpr decltype(auto)
				operator-(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::same_as<container_t_a, container_t_b> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(A[i]) - stl::sbo(B[i]);

			return std::move(A);
		} else if constexpr (std::same_as<container_t_a, container_t_b> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = stl::sbo(A[i]) - stl::sbo(B[i]);

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C {};

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(A[i]) - stl::sbo(B[i]);

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) &&
			(stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
			 stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>) ||
		(stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		 stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>)&&stl::
			common_std_array_c<LeftType, RightType> constexpr decltype(auto)
				operator*(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::same_as<container_t_a, container_t_b> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(A[i]) * stl::sbo(B[i]);

			return std::move(A);
		} else if constexpr (std::same_as<container_t_a, container_t_b> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = stl::sbo(A[i]) * stl::sbo(B[i]);

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(A[i]) * stl::sbo(B[i]);

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) &&
			(stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
			 stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>) ||
		(stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		 stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>)&&stl::
			common_std_array_c<LeftType, RightType> constexpr decltype(auto)
				operator/(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::same_as<container_t_a, container_t_b> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(A[i]) / stl::sbo(B[i]);

			return std::move(A);
		} else if constexpr (std::same_as<container_t_a, container_t_b> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = stl::sbo(A[i]) / stl::sbo(B[i]);

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(A[i]) / stl::sbo(B[i]);

			return C;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// vector cross product - operator% has high precedence
	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) &&
		((std::tuple_size_v<std::remove_cvref_t<LeftType>> == 3) ||
		 (std::tuple_size_v<std::remove_cvref_t<LeftType>> == 4)) &&
		stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>>&& stl::numerical_c<
			std::tuple_element_t<0, std::remove_cvref_t<RightType>>>&& stl::
			common_std_array_c<LeftType, RightType> constexpr decltype(auto)
				operator%(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		using c_t = stl::common_std_array_t<LeftType, RightType>;
		c_t C;

		C[0] = stl::sbo(A[1]) * stl::sbo(B[2]) - stl::sbo(B[1]) * stl::sbo(A[2]);
		C[1] = stl::sbo(A[2]) * stl::sbo(B[0]) - stl::sbo(B[2]) * stl::sbo(A[0]);
		C[2] = stl::sbo(A[0]) * stl::sbo(B[1]) - stl::sbo(B[0]) * stl::sbo(A[1]);

		if constexpr (std::tuple_size_v<std::remove_cvref_t<LeftType>> == 4)
			C[3] = 1;

		return C;
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) &&
		stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>>&& stl::std_array_c<
			std::tuple_element_t<0, std::remove_cvref_t<RightType>>>&& stl::
			common_std_array_c<LeftType, RightType> constexpr decltype(auto)
				operator%(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::same_as<container_t_a, container_t_b> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = A[i] % B[i];

			return std::move(A);
		} else if constexpr (std::same_as<container_t_a, container_t_b> &&
							 std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = A[i] % B[i];

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A[i] % B[i];

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator%(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = A[i] % B;

			return std::move(A);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A[i] % B;

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator%(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<RightType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = A % B[i];

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			// std::cout <<"A    type: " >> A << std::endl;
			// std::cout <<"B[0] type: " >> B[0] << std::endl;
			// std::cout <<"C[0] type: " >> C[0] << std::endl;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A % B[i];

			return C;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	// vector inner product - operator& has low precedence
	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) &&
		stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>>&& stl::numerical_c<
			std::tuple_element_t<0, std::remove_cvref_t<RightType>>>&& stl::
			common_std_array_c<LeftType, RightType> constexpr decltype(auto)
				operator&(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		using c_t = stl::common_std_array_t<LeftType, RightType>;

		using element_t = std::tuple_element_t<0, c_t>;

		element_t R {};

		for (std::size_t i = 0; i < N; ++i)
			R += stl::sbo(A[i]) * stl::sbo(B[i]);

		return R;
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires(std::tuple_size_v<std::remove_cvref_t<LeftType>> ==
			 std::tuple_size_v<std::remove_cvref_t<RightType>>) &&
		stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>>&& stl::std_array_c<
			std::tuple_element_t<0, std::remove_cvref_t<RightType>>>&& stl::
			common_std_array_c<LeftType, RightType> constexpr decltype(auto)
				operator&(LeftType&& A, RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		using c_t = stl::common_std_array_t<LeftType, RightType>;
		using element_t = std::tuple_element_t<0, std::tuple_element_t<0, c_t>>;
		using array_t = std::array<element_t, N>;

		array_t C;

		for (std::size_t i = 0; i < N; ++i)
			C[i] = A[i] & B[i];

		return C;
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>
	constexpr decltype(auto) operator&(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using a_t = std::tuple_element_t<0, std::tuple_element_t<0, container_t_a>>;

		using container_t_b = std::remove_cvref_t<RightType>;
		using b_t = std::tuple_element_t<0, container_t_b>;

		constexpr std::size_t N = std::tuple_size_v<container_t_a>;

		using c_t = std::array<stl::common_signed_t<a_t, b_t>, N>;
		c_t C;

		for (std::size_t i = 0; i < N; ++i)
			C[i] = A[i] & B;

		return C;
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>>
	constexpr decltype(auto) operator&(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using a_t = std::tuple_element_t<0, container_t_a>;

		using container_t_b = std::remove_cvref_t<RightType>;
		using b_t = std::tuple_element_t<0, std::tuple_element_t<0, container_t_b>>;

		constexpr std::size_t N = std::tuple_size_v<container_t_b>;

		using c_t = std::array<stl::common_signed_t<a_t, b_t>, N>;
		c_t C;

		// std::cout <<"A    type: " >> A << std::endl;
		// std::cout <<"B[0] type: " >> B[0] << std::endl;
		// std::cout <<"C[0] type: " >> C[0] << std::endl;

		for (std::size_t i = 0; i < N; ++i)
			C[i] = A & B[i];

		return C;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator+(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = A[i] + B;

			return std::move(A);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A[i] + B;

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator+(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<RightType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = A + B[i];

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A + B[i];

			return C;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator-(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = A[i] - B;

			return std::move(A);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A[i] - B;

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator-(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<RightType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = A - B[i];

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A - B[i];

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator*(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = A[i] * B;

			return std::move(A);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A[i] * B;

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator*(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<RightType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = A * B[i];

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A * B[i];

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator/(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<LeftType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = A[i] / B;

			return std::move(A);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A[i] / B;

			return C;
		}
	}

	template <stl::std_array_flat_c LeftType, stl::std_array_flat_c RightType>
	requires stl::numerical_c<std::tuple_element_t<0, std::remove_cvref_t<LeftType>>> &&
		stl::std_array_c<std::tuple_element_t<0, std::remove_cvref_t<RightType>>> &&
		stl::common_std_array_c<LeftType, RightType>
	constexpr decltype(auto) operator/(LeftType&& A,
									   RightType&& B) noexcept(!stlonic::bDetectOverFlow) {
		using container_t_a = std::remove_cvref_t<LeftType>;
		using container_t_b = std::remove_cvref_t<RightType>;

		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<RightType>>;

		if constexpr (std::is_rvalue_reference_v<decltype(B)>) {
			for (std::size_t i {}; i < N; ++i)
				B[i] = A / B[i];

			return std::move(B);
		} else {
			using c_t = stl::common_std_array_t<LeftType, RightType>;
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = A / B[i];

			return C;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	template <stl::std_array_flat_c ArrayType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator+(ArrayType&& A,
									   ScalarType s) noexcept(!stlonic::bDetectOverFlow) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<ArrayType>>;

		using c_t = stl::common_std_array_t<ArrayType, ScalarType>;

		if constexpr (std::same_as<c_t, std::remove_cvref_t<ArrayType>> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(A[i]) + stl::sbo(s);

			return std::move(A);
		} else {
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(A[i]) + stl::sbo(s);

			return C;
		}
	}

	template <stl::numerical_c ScalarType, stl::std_array_flat_c ArrayType>
	constexpr decltype(auto) operator+(ScalarType s,
									   ArrayType&& A) noexcept(!stlonic::bDetectOverFlow) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<ArrayType>>;

		using c_t = stl::common_std_array_t<ScalarType, ArrayType>;

		if constexpr (std::same_as<c_t, std::remove_cvref_t<ArrayType>> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(s) + stl::sbo(A[i]);

			return std::move(A);
		} else {
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(s) + stl::sbo(A[i]);

			return C;
		}
	}

	template <stl::std_array_flat_c ArrayType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator-(ArrayType&& A,
									   ScalarType s) noexcept(!stlonic::bDetectOverFlow) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<ArrayType>>;

		using c_t = stl::common_std_array_t<ArrayType, ScalarType>;

		if constexpr (std::same_as<c_t, std::remove_cvref_t<ArrayType>> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(A[i]) - stl::sbo(s);

			return std::move(A);
		} else {
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(A[i]) - stl::sbo(s);

			return C;
		}
	}

	template <stl::numerical_c ScalarType, stl::std_array_flat_c ArrayType>
	constexpr decltype(auto) operator-(ScalarType s,
									   ArrayType&& A) noexcept(!stlonic::bDetectOverFlow) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<ArrayType>>;

		using c_t = stl::common_std_array_t<ScalarType, ArrayType>;

		if constexpr (std::same_as<c_t, std::remove_cvref_t<ArrayType>> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(s) - stl::sbo(A[i]);

			return std::move(A);
		} else {
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(s) - stl::sbo(A[i]);

			return C;
		}
	}

	template <stl::std_array_flat_c ArrayType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator*(ArrayType&& A,
									   ScalarType s) noexcept(!stlonic::bDetectOverFlow) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<ArrayType>>;

		using c_t = stl::common_std_array_t<ArrayType, ScalarType>;

		if constexpr (std::same_as<c_t, std::remove_cvref_t<ArrayType>> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(A[i]) * stl::sbo(s);

			return std::move(A);
		} else {
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(A[i]) * stl::sbo(s);

			return C;
		}
	}

	template <stl::numerical_c ScalarType, stl::std_array_flat_c ArrayType>
	constexpr decltype(auto) operator*(ScalarType s,
									   ArrayType&& A) noexcept(!stlonic::bDetectOverFlow) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<ArrayType>>;

		using c_t = stl::common_std_array_t<ScalarType, ArrayType>;

		if constexpr (std::same_as<c_t, std::remove_cvref_t<ArrayType>> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(s) * stl::sbo(A[i]);

			return std::move(A);
		} else {
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(s) * stl::sbo(A[i]);

			return C;
		}
	}

	template <stl::std_array_flat_c ArrayType, stl::numerical_c ScalarType>
	constexpr decltype(auto) operator/(ArrayType&& A,
									   ScalarType s) noexcept(!stlonic::bDetectOverFlow) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<ArrayType>>;

		using c_t = stl::common_std_array_t<ArrayType, ScalarType>;

		if constexpr (std::same_as<c_t, std::remove_cvref_t<ArrayType>> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(A[i]) / stl::sbo(s);

			return std::move(A);
		} else {
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(A[i]) / stl::sbo(s);

			return C;
		}
	}

	template <stl::numerical_c ScalarType, stl::std_array_flat_c ArrayType>
	constexpr decltype(auto) operator/(ScalarType s,
									   ArrayType&& A) noexcept(!stlonic::bDetectOverFlow) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<ArrayType>>;

		using c_t = stl::common_std_array_t<ScalarType, ArrayType>;

		if constexpr (std::same_as<c_t, std::remove_cvref_t<ArrayType>> &&
					  std::is_rvalue_reference_v<decltype(A)>) {
			for (std::size_t i {}; i < N; ++i)
				A[i] = stl::sbo(s) / stl::sbo(A[i]);

			return std::move(A);
		} else {
			c_t C;

			for (std::size_t i = 0; i < N; ++i)
				C[i] = stl::sbo(s) / stl::sbo(A[i]);

			return C;
		}
	}
} // namespace std::inline stl_extensions

#endif
// end of file
