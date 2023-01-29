/*
	Author: Geek pww
	First Edit: July 15, 2022
*/

#ifndef _STLONIC_STD_EXTENSIONS_HPP
#define _STLONIC_STD_EXTENSIONS_HPP

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "conversion.hpp"
#include "types.hpp"

namespace std::inline stl_extensions {
	namespace stl = stlonic::types;

	using stl::common_type_exists_c;

	template <typename = void>
	std::ostream& operator<<(std::ostream& os, const wchar_t* str) {
		namespace cvr = stlonic::conversion;
		os << cvr::utf16_to_windows_codepage(str);
		return os;
	}

	template <typename = void>
	std::ostream& operator<<(std::ostream& os, const char8_t* str) {
		namespace cvr = stlonic::conversion;
		os << cvr::utf8_to_windows_codepage((const char*)str);
		return os;
	}

	template <typename = void>
	std::ostream& operator<<(std::ostream& os, std::stringstream const& stream) {
		os << stream.str();
		return os;
	}

	template <typename = void>
	std::ostream& operator<<(std::ostream& os, std::ostringstream const& stream) {
		os << stream.str();
		return os;
	}

	namespace hidden {
		template <typename... Ts, typename... Ss>
		constexpr auto tuple_connect_tail(std::tuple<Ts...>, std::tuple<Ss...>) {
			return std::tuple<Ts..., Ss...> {};
		}

		template <typename T, typename... Ss>
		constexpr auto tuple_pairs(T, std::tuple<Ss...>) // tuple_pairs
		{
			return std::tuple<std::tuple<T, Ss>...> {};
		}

		template <typename... Ts, typename... Ss>
		constexpr auto tuple_pairs(std::tuple<Ts...>, std::tuple<Ss...>) // tuple_pairs
		{
			return std::tuple<std::tuple<Ts..., Ss>...> {};
		}

		template <typename... TT, typename T, typename... Ts, typename... Ss>
		constexpr auto fn_tuple_cross_product(
			std::tuple<TT...> tt, std::tuple<T, Ts...> t, std::tuple<Ss...> s) {
			if constexpr (sizeof...(Ts) != 0)
				return fn_tuple_cross_product(
					tuple_connect_tail(tt, tuple_pairs(T {}, s)), std::tuple<Ts...> {}, s);
			else
				return tuple_connect_tail(tt, tuple_pairs(T {}, s));
		}
	} // namespace hidden
	// end of namespace hidden

	// for tuple cartesian product A x B
	// template<typename... Ts,  typename... Ss>
	// constexpr auto operator&&(std::tuple<Ts...> A, std::tuple<Ss...> B)
	// {
	//     return hidden::fn_tuple_cross_product(std::tuple{}, A, B);
	// }

	template <stl::tuple_flat_c T, stl::tuple_flat_c S, stl::tuple_flat_c... Tails>
	constexpr auto tuple_cartesian_product_type(T A, S B, Tails... tails) {
		if constexpr (sizeof...(tails) > 0) {
			return tuple_cartesian_product_type(hidden::fn_tuple_cross_product(std::tuple {}, A, B),
												tails...);
		} else {
			return hidden::fn_tuple_cross_product(std::tuple {}, A, B);
		}
	}

	namespace hidden {
		template <typename TupleA, typename... TupleTypes>
		using tuple_cross_product_t = decltype((TupleA {} >> ... >> TupleTypes {}));
	}
	// end of namespace hidden

	template <typename TupleA, typename... TupleTypes>
	using tuple_cross_product_t = hidden::tuple_cross_product_t<std::remove_cvref_t<TupleA>,
																std::remove_cvref_t<TupleTypes>...>;

	template <typename TupleA, typename... TupleTypes>
	using tuple_cartesian_product_t = tuple_cross_product_t<TupleA, TupleTypes...>;

	namespace hidden {
		template <typename L, typename R>
		constexpr auto fn_common_signed_tuple(L const&, R const&) {
			return stl::common_signed_t<L, R> {};
		}

		template <typename... Ls, typename... Rs>
		constexpr auto fn_common_signed_tuple(std::tuple<Ls...> L, std::tuple<Rs...> R) {
			return stl::for_stallion<sizeof...(Ls)>([]<auto... i>(stl::sequence<i...>) {
				return std::tuple {
					fn_common_signed_tuple(std::tuple_element_t<i, std::tuple<Ls...>> {},
										   std::tuple_element_t<i, std::tuple<Rs...>> {})...};
			});
		}

		template <typename TupleA, typename TupleB>
		using common_signed_tuple_pair = decltype(fn_common_signed_tuple(TupleA {}, TupleB {}));

		template <typename L, typename R>
		constexpr auto fn_common_unsigned_tuple(L const&, R const&) {
			return stl::common_unsigned_t<L, R> {};
		}

		template <typename... Ls, typename... Rs>
		constexpr auto fn_common_unsigned_tuple(std::tuple<Ls...> L, std::tuple<Rs...> R) {
			return stl::for_stallion<sizeof...(Ls)>([]<auto... i>(stl::sequence<i...>) {
				return std::tuple {
					fn_common_unsigned_tuple(std::tuple_element_t<i, std::tuple<Ls...>> {},
											 std::tuple_element_t<i, std::tuple<Rs...>> {})...};
			});
		}

		template <stl::tuple_flat_c TupleA, stl::tuple_flat_c TupleB>
		using common_unsigned_tuple_pair = decltype(fn_common_unsigned_tuple(TupleA {}, TupleB {}));

		template <stl::tuple_flat_c TupleType>
		constexpr auto fn_common_signed_tuples(TupleType Tuple) {
			return Tuple;
		}

		template <stl::tuple_flat_c TupleA,
				  stl::tuple_flat_c TupleB,
				  stl::tuple_flat_c... TupleTypes>
		constexpr auto fn_common_signed_tuples(TupleA A, TupleB B, TupleTypes... Tuples) {
			if constexpr (sizeof...(Tuples) == 0)
				return fn_common_signed_tuple(A, B);
			else
				return fn_common_signed_tuples(fn_common_signed_tuple(A, B), Tuples...);
		}

		template <stl::tuple_flat_c TupleType>
		constexpr auto fn_common_unsigned_tuples(TupleType Tuple) {
			return Tuple;
		}

		template <stl::tuple_flat_c TupleA,
				  stl::tuple_flat_c TupleB,
				  stl::tuple_flat_c... TupleTypes>
		constexpr auto fn_common_unsigned_tuples(TupleA A, TupleB B, TupleTypes... Tuples) {
			if constexpr (sizeof...(Tuples) == 0)
				return fn_common_unsigned_tuple(A, B);
			else
				return fn_common_unsigned_tuples(fn_common_unsigned_tuple(A, B), Tuples...);
		}

		// common signed tuple
		template <stl::tuple_flat_c TupleType, stl::tuple_flat_c... TupleTypes>
		using common_signed_tuple_t =
			decltype(hidden::fn_common_signed_tuples(TupleType {}, TupleTypes {}...));

		// common unsigned tuple
		template <stl::tuple_flat_c TupleType, stl::tuple_flat_c... TupleTypes>
		using common_unsigned_tuple_t =
			decltype(hidden::fn_common_unsigned_tuples(TupleType {}, TupleTypes {}...));
	} // namespace hidden
	// end of namespace hidden

	// common signed tuple
	template <stl::tuple_flat_c TupleType, stl::tuple_flat_c... TupleTypes>
	using common_signed_tuple_t = hidden::common_signed_tuple_t<std::remove_cvref_t<TupleType>,
																std::remove_cvref_t<TupleTypes>...>;

	// common unsigned tuple
	template <stl::tuple_flat_c TupleType, stl::tuple_flat_c... TupleTypes>
	using common_unsigned_tuple_t = hidden::common_unsigned_tuple_t<TupleType, TupleTypes...>;

	template <typename CharType, typename Type>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const std::optional<Type>& opt);

	template <typename CharType, typename FirstType, typename SecondType>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const std::pair<FirstType, SecondType>& pr) {
		os << "< " << pr.first << ", " << pr.second << " >";
		return os;
	}

	template <typename CharType, typename... Types>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const std::tuple<Types...>& container);

	// template<typename CharType, stl::stream_undefined_container_c ContainerType>
	// std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
	//     const ContainerType& container);

	template <typename CharType, typename Type, typename... Types>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const std::variant<Type, Types...>& v);

	template <typename CharType, typename ContainerType>
	requires(stl::std_array_flat_c<ContainerType> || stl::span_flat_c<ContainerType> ||
			 (stl::c_array_flat_c<ContainerType> &&
			  stl::non_chars_c<ContainerType>)) std::basic_ostream<CharType>
	&operator<<(std::basic_ostream<CharType>& os, ContainerType&& container);

	template <class F, typename T, std::size_t N>
	constexpr decltype(auto) apply(F&& f, T (&&c_array)[N]);

	template <class F, typename T, std::size_t N>
	constexpr decltype(auto) apply(F&& f, T (&c_array)[N]);

	template <std::size_t I, class T, std::size_t N>
	constexpr decltype(auto) get(T (&c_array)[N]) noexcept;

	template <std::size_t I, class T, std::size_t N>
	constexpr decltype(auto) get(T (&&c_array)[N]) noexcept;

	template <typename T, T... Indices>
	std::ostream& operator<<(std::ostream& os,
							 std::integer_sequence<T, Indices...> const& seq) noexcept;

	template <typename T>
	std::ostream& operator>>(std::ostream& os, T const& t);

	template <typename... Types>
	std::ostream& operator>>(std::ostream& os, std::tuple<Types...> const& t);

	namespace hidden {
		template <typename... Ls, typename... Rs>
		constexpr decltype(auto) tuple_cartesian_product(std::tuple<Ls...> const& A,
														 std::tuple<Rs...> const& B) {
			return stl::for_stallion_tuple<sizeof...(Ls), sizeof...(Rs)>(
				[&]<typename... seqs>(std::tuple<seqs...>) {
					auto append = [&]<auto ii, auto jj>(stl::sequence<ii, jj>) {
						return stl::tuple_append(std::get<ii>(A), std::get<jj>(B));
					};

					if constexpr (stl::all_the_same_flat_c<decltype(append(seqs {}))...>)
						return std::array {append(seqs {})...};
					else
						return std::tuple {append(seqs {})...};
				});
		}

		template <typename... Ls, typename R, std::size_t N2>
		constexpr decltype(auto) tuple_cartesian_product(std::tuple<Ls...> const& A,
														 std::array<R, N2> const& B) {
			return stl::for_stallion_tuple<sizeof...(Ls), N2>(
				[&]<typename... seqs>(std::tuple<seqs...>) {
					auto append = [&]<auto ii, auto jj>(stl::sequence<ii, jj>) {
						return stl::tuple_append(std::get<ii>(A), std::get<jj>(B));
					};

					if constexpr (stl::all_the_same_flat_c<decltype(append(seqs {}))...>)
						return std::array {append(seqs {})...};
					else
						return std::tuple {append(seqs {})...};
				});
		}

		template <typename L, std::size_t N1, typename... Rs>
		constexpr decltype(auto) tuple_cartesian_product(std::array<L, N1> const& A,
														 std::tuple<Rs...> const& B) {
			return stl::for_stallion_tuple<N1, sizeof...(Rs)>(
				[&]<typename... seqs>(std::tuple<seqs...>) {
					auto append = [&]<auto ii, auto jj>(stl::sequence<ii, jj>) {
						return stl::tuple_append(std::get<ii>(A), std::get<jj>(B));
					};

					if constexpr (stl::all_the_same_flat_c<decltype(append(seqs {}))...>)
						return std::array {append(seqs {})...};
					else
						return std::tuple {append(seqs {})...};
				});
		}

		template <typename L, std::size_t N1, typename R, std::size_t N2>
		constexpr decltype(auto) tuple_cartesian_product(std::array<L, N1> const& A,
														 std::array<R, N2> const& B) {
			return stl::for_stallion_tuple<N1, N2>([&]<typename... seqs>(std::tuple<seqs...>) {
				auto append = [&]<auto ii, auto jj>(stl::sequence<ii, jj>) {
					return stl::tuple_append(std::get<ii>(A), std::get<jj>(B));
				};

				if constexpr (stl::all_the_same_flat_c<decltype(append(seqs {}))...>)
					return std::array {append(seqs {})...};
				else
					return std::tuple {append(seqs {})...};
			});
		}
	} // namespace hidden
	// end of namespace hidden

	template <stl::either_array_or_tuple_flat_c T,
			  stl::either_array_or_tuple_flat_c S,
			  stl::either_array_or_tuple_flat_c... Tails>
	constexpr decltype(auto) tuple_cartesian_product(T&& A, S&& B, Tails&&... tails) {
		if constexpr (sizeof...(Tails) > 0) {
			return tuple_cartesian_product(hidden::tuple_cartesian_product(A, B), tails...);
		} else {
			return hidden::tuple_cartesian_product(A, B);
		}
	}

	template <typename T>
	std::ostream& operator>>(std::ostream& os, T const& t) {
		using flat_t = std::remove_cvref_t<T>;
		os << Stlonic_GetTypeName(flat_t);
		return os;
	}

	template <typename... Types>
	std::ostream& operator>>(std::ostream& os, std::tuple<Types...> const& t) {
		if constexpr (sizeof...(Types) != 0) {
			os << "< ";

			stl::for_workhorse<decltype(t)>([&os](auto i) {
				using ele_t = std::tuple_element_t<(std::size_t)i.value, std::tuple<Types...>>;

				os >> ele_t {};

				if (i.value != i.last)
					os << ", ";
			});

			os << "> ";
			return os;
		} else {
			os << "< >";
			return os;
		}
	}

	namespace hidden {
		template <std::size_t SIZE>
		void print_sequence(std::ostream& os, auto Index, auto count) {
			os << Index;
			if (count != SIZE)
				os << ", ";
		}
	} // namespace hidden
	// end of namespace hidden

	template <typename T, T... Indices>
	std::ostream& operator<<(std::ostream& os,
							 std::integer_sequence<T, Indices...> const& seq) noexcept {
		if constexpr (sizeof...(Indices) < 1) // count of Indices = 0
		{
			os << "< " << Stlonic_GetTypeName(T) << " >";
			return os;
		} else {
			constexpr auto SIZE = sizeof...(Indices);
			std::size_t count = 0;

			os << "< " << Stlonic_GetTypeName(T) << ": ";

			(hidden::print_sequence<SIZE>(os, Indices, ++count), ...);

			os << " >";
			return os;
		}
	}

	/*
		std::tuple_size(std::array) - https://en.cppreference.com/w/cpp/container/array/tuple_size
		std::get(std::array) - https://en.cppreference.com/w/cpp/container/array/get
	*/

	/*  T: int, const int - auto
		T&: int&, const int& - auto&
		T&&: int&&, const int&& - auto&&
			T&&, auto&&: rvalue reference, forwarding reference
				function return type auto&& - rvalue reference
				function parameter type auto&& - forwarding reference
		decltype(auto) - function return type - auto, auto&, auto&&
	*/
	template <std::size_t I, class T, std::size_t N>
	constexpr decltype(auto) get(T (&c_array)[N]) noexcept {
		return c_array[I];
	}

	template <std::size_t I, class T, std::size_t N>
	constexpr decltype(auto) get(T (&&c_array)[N]) noexcept {
		return std::move(c_array[I]);
	}

	template <class F, typename T, std::size_t N>
	constexpr decltype(auto) apply(F&& f, T (&&c_array)[N]) {
		using c_array_t = decltype(c_array);
		auto std_array = std::to_array(std::forward<c_array_t>(c_array));

		return std::apply(std::forward<F>(f), std::move(std_array));
	}

	template <class F, typename T, std::size_t N>
	constexpr decltype(auto) apply(F&& f, T (&c_array)[N]) {
		auto std_array = std::to_array(c_array);

		return std::apply(std::forward<F>(f), std::move(std_array));
	}

	template <class F, typename T, std::size_t N>
	constexpr decltype(auto) apply(F&& f, std::span<T, N>& sp) {
		stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			return std::apply(std::forward<F>(f), std::forward_as_tuple(sp[i]...));
		});
	}

	template <class F, typename T, std::size_t N>
	constexpr decltype(auto) apply(F&& f, const std::span<T, N>& sp) {
		stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			return std::apply(std::forward<F>(f), std::forward_as_tuple(sp[i]...));
		});
	}

	template <class F, typename T, std::size_t N>
	constexpr decltype(auto) apply(F&& f, std::span<T, N>&& sp) {
		stl::for_stallion<N>([&]<auto... i>(stl::sequence<i...>) {
			return std::apply(std::forward<F>(f), std::forward_as_tuple(sp[i]...));
		});
	}

	template <typename CharType, typename Type>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const std::optional<Type>& opt) {
		if (opt) {
			os << opt.value();
		}

		return os;
	}

	template <typename CharType, stl::stream_undefined_container_flat_c ContainerType>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const ContainerType& container) {
		if (container.empty()) {
			os << "{ }";
		} else {
			auto begin = container.begin();
			auto last = container.end();

			std::advance(last, -1); // --last; right before .end(), or iterator for the last element
									// of the container

			os << "{ ";

			for (auto itr = begin; itr != last; ++itr)
				os << *itr << ", ";

			os << *last << " }";
		}

		return os;
	}

	template <typename CharType, stl::map_c ContainerType>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const ContainerType& container) {
		if (container.empty()) {
			os << "{ }";
		} else {
			if constexpr (stl::std_map_c<ContainerType>) {
				auto begin = container.begin();
				auto last = container.end();

				std::advance(last, -1);

				os << "{ ";

				for (auto itr = begin; itr != last; ++itr) {
					os << *itr << ", ";
				}

				os << *last << " }";
			} else if constexpr (stl::tbb_map_c<ContainerType>) {
				auto begin = container.begin();
				auto last = container.end();

				std::advance(last, -1);

				os << "{ ";

				for (auto itr = begin; itr != last; ++itr) {
					os << *itr;

					auto ittr = itr;

					if (++ittr != last)
						os << ", ";
				}

				os << " }";
			}
		}

		return os;
	}

	/*
	template<typename CharType, stl::view_c ContainerType>
		requires (!stl::stream_undefined_container_flat_c<ContainerType>)
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
		ContainerType& container)
	{
		auto begin = std::ranges::begin(container);
		auto last = std::ranges::end(container);

		if(begin == last) // container is empty()
		{
			os << "{ }";
		}
		else
		{
			--last; // right before .end(), or iterator for the last element of the container

			os <<"{ ";

			for(auto itr = begin; itr != last; ++itr)
				os << *itr << ", ";

			os << *last << " }";
		}

		return os;
	}
	*/

	template <typename CharType, typename ContainerType>
	requires(stl::std_array_flat_c<ContainerType> || stl::span_flat_c<ContainerType> ||
			 (stl::c_array_flat_c<ContainerType> &&
			  stl::non_chars_c<ContainerType>)) std::basic_ostream<CharType>
	&operator<<(std::basic_ostream<CharType>& os, ContainerType&& container) {
		auto begin = std::ranges::begin(container);
		auto last = std::ranges::end(container);

		if (begin == last) // container is empty()
		{
			os << "< >";
		} else {
			--last; // right before .end(), or iterator for the last element of the container

			os << "< ";

			for (auto itr = begin; itr != last; ++itr)
				os << *itr << ", ";

			os << *last << " >";
		}

		return os;
	}

	/*
	template<typename CharType, typename Type, std::size_t N>
	  requires stl::non_chars_c<Type[N]>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
		const Type(&container)[N])
	{
		auto begin = std::ranges::begin(container);
		auto last = std::ranges::end(container);

		if(begin == last) // container is empty()
		{
			os << "{ }";
		}
		else
		{
			--last; // right before .end(), or iterator for the last element of the container

			os <<"{ ";

			for(auto itr = begin; itr != last; ++itr)
				os << *itr << ", ";

			os << *last << " }";
		}

		return os;
	}

	*/

	namespace hidden {
		template <size_t Index, typename CharType, typename... Types>
		void print_tuple(std::basic_ostream<CharType>& os, const std::tuple<Types...>& container) {
			constexpr size_t Size = sizeof...(Types);

			if constexpr (Index < Size - 1) // {0, 1, 2, ..., Index, Size - 1} < Size
			{
				os << std::get<Index>(container) << ", ";
				print_tuple<Index + 1>(os, container);
			} else if constexpr (Index == Size - 1) {
				os << std::get<Index>(container);
			}
		}
	} // end of namespace hidden

	template <typename CharType, typename... Types>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const std::tuple<Types...>& container) {
		if constexpr (sizeof...(Types) == 0) {
			os << "[ ]";
		} else {
			os << "[ ";
			hidden::print_tuple<0>(os, container);
			os << " ]";
		}

		return os;
	}

	template <typename CharType, typename Type, typename... Types>
	std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
											 const std::variant<Type, Types...>& v) {
		auto visit_target = [&os]<typename T>(T&& value) -> std::basic_ostream<CharType>& {
			if constexpr (stl::ostream_operator_available_c<std::remove_cvref_t<T>, CharType>)
				os << value;
			else {
				os << Stlonic_GetTypeCategory(value) << " does not support ostream operator<<()"
				   << std::endl;
			}

			return os;
		};

		return std::visit(visit_target, v);
	}

#ifdef _TPF_TYPES_HPP

	template <typename CharType, std::size_t N, typename T, typename deleter>
	std::basic_ostream<CharType>&
		operator<<(std::basic_ostream<CharType>& os,
				   tpf::types::unique_ptr_wrapper<N, T, deleter> const& upw) {
		os << upw.ref();
		return os;
	}

#endif

} // namespace std::inline stl_extensions

#endif // end of file _STLONIC_STD_EXTENSIONS_HPP
