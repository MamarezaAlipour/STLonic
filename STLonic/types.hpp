/*
	Author: Geek pww
	First Edit: June 12, 2022
	Second Edit: July. 07, 2022
	Third Edit: Aug. 09, 2022 - safe binary operation - sbo()
*/

#ifndef _STLONIC_TYPES_HPP
#define _STLONIC_TYPES_HPP

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef STLONIC_PREVIEW_CONCURRENT_ORDERED_CONTAINERS
#define STLONIC_PREVIEW_CONCURRENT_ORDERED_CONTAINERS 1
#endif

#ifndef STLONIC_SUPPRESS_DEPRECATED_MESSAGES
#define STLONIC_SUPPRESS_DEPRECATED_MESSAGES 1
#else
#undef STLONIC_SUPPRESS_DEPRECATED_MESSAGES
#define STLONIC_SUPPRESS_DEPRECATED_MESSAGES 1
#endif // end of STLONIC_SUPPRESS_DEPRECATED_MESSAGES

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <deque>
#include <execution>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <numbers>
#include <optional>
#include <ranges>
#include <set>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <tbb/tbb.h>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#if defined(_DEBUG) || defined(DEBUG) || defined(STLONIC_DEBUG) || !defined(STLONIC_SAFE_OPERATION)
#define STLONIC_SAFE_OPERATION 2LL
#endif

#if defined(STLONIC_SAFE_OPERATION) && ((STLONIC_SAFE_OPERATION < 0) || (STLONIC_SAFE_OPERATION > 2))
#error Macro STLONIC_SAFE_OPERATION should be in the range [0, 2] inclusive
#endif

/*
	if STLONIC_SAFE_OPERATION==0
	perform type cast only

	if STLONIC_SAFE_OPERATION==1LL
	detect integral overflow and division by zero - (DEFAULT)

	if _DEBUG || DEBUG || STLONIC_SAFE_OPERATION=2LL || STLONIC_SAFE_NUMERICAL_OPERATION==2LL
	detect integral/floating-point overflow and division by zero
*/

#if defined(_DEBUG) || defined(DEBUG) || defined(STLONIC_DEBUG)
#define StlonicSafe(arg) stlonic::types::sbo<STLONIC_SAFE_OPERATION>(arg)
#else
#define StlonicSafe(arg) arg
#endif

namespace std {
	/*
	std::tuple_size(std::array) - https://en.cppreference.com/w/cpp/container/array/tuple_size
	std::get(std::array) - https://en.cppreference.com/w/cpp/container/array/get
	*/

	template <class T, std::size_t N>
	struct tuple_size<T[N]> : std::integral_constant<std::size_t, N> {};

	template <class T, std::size_t N>
	struct tuple_size<const T[N]> : std::integral_constant<std::size_t, N> {};

	template <class T, std::size_t N>
	struct tuple_size<T (&)[N]> : std::integral_constant<std::size_t, N> {};

	template <class T, std::size_t N>
	struct tuple_size<const T (&)[N]> : std::integral_constant<std::size_t, N> {};

	template <class T, std::size_t N>
	struct tuple_size<T (&&)[N]> : std::integral_constant<std::size_t, N> {};

	template <class T, std::size_t N>
	struct tuple_size<const T (&&)[N]> : std::integral_constant<std::size_t, N> {};

	///////////////////////////////////////////

	template <class... Ts>
	struct tuple_size<std::variant<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)> {};

	template <class... Ts>
	struct tuple_size<const std::variant<Ts...>>
		: std::integral_constant<std::size_t, sizeof...(Ts)> {};

	template <class... Ts>
	struct tuple_size<std::variant<Ts...>&> : std::integral_constant<std::size_t, sizeof...(Ts)> {};

	template <class... Ts>
	struct tuple_size<const std::variant<Ts...>&>
		: std::integral_constant<std::size_t, sizeof...(Ts)> {};

	template <class... Ts>
	struct tuple_size<std::variant<Ts...>&&> : std::integral_constant<std::size_t, sizeof...(Ts)> {
	};

	template <class... Ts>
	struct tuple_size<const std::variant<Ts...>&&>
		: std::integral_constant<std::size_t, sizeof...(Ts)> {};
} // namespace std
// end of namespace std

namespace stlonic::literals {
	inline constexpr std::size_t operator""_size_t(unsigned long long value) {
		return static_cast<std::size_t>(value);
	}

	inline constexpr short operator""_short(unsigned long long value) {
		return static_cast<short>(value);
	}

	inline constexpr unsigned short operator""_ushort(unsigned long long value) {
		return static_cast<unsigned short>(value);
	}

	inline constexpr char operator""_char(unsigned long long value) {
		return static_cast<char>(value);
	}

	inline constexpr unsigned char operator""_uchar(unsigned long long value) {
		return static_cast<unsigned char>(value);
	}
} // namespace stlonic::literals
// end of namespace stlonic::literals

namespace stlonic // C++ Programmers' Group
{
	namespace types {
		template <typename Type>
		std::string type_tO_sTring() {
#ifdef __NVCC__
			{
				std::string fname = typeid(hidden::st_dummy_type_container<Type>).name();

				const char* to_str = "struct tpf::types::hidden::st_dummy_type_container<";

				std::size_t len = strlen(to_str);

				auto pos = fname.find(to_str);

				if (pos != fname.npos) // we found substring
					fname = fname.substr(pos + len);

				// remove trailing "> "
				fname.pop_back();

				//////////////////////////////////////////////

				to_str = " __ptr64";
				len = strlen(to_str);
				while ((pos = fname.find(to_str)) != fname.npos)
					fname.erase(pos, len);

				to_str = " __ptr32";
				len = strlen(to_str);
				while ((pos = fname.find(to_str)) != fname.npos)
					fname.erase(pos, len);

				to_str = "enum class";
				len = strlen(to_str);
				while ((pos = fname.find(to_str)) != fname.npos)
					fname.erase(pos, len);

				to_str = "enum";
				len = strlen(to_str);
				while ((pos = fname.find(to_str)) != fname.npos)
					fname.erase(pos, len);

				to_str = "class";
				len = strlen(to_str);
				while ((pos = fname.find(to_str)) != fname.npos)
					fname.erase(pos, len);

				to_str = "struct";
				len = strlen(to_str);
				while ((pos = fname.find(to_str)) != fname.npos)
					fname.erase(pos, len);

				while (fname.back() == ' ')
					fname.pop_back();

				return fname;
			}

#elif defined(__FUNCSIG__)
			std::string fname(__FUNCSIG__);
			const char* to_str = "tO_sTring<";
			size_t len = strlen(to_str);
			auto pos = fname.find("tO_sTring<");
			fname = fname.substr(pos + len);
			fname = fname.substr(0, fname.find_last_of('>'));

			//////////////////////////////////////////////

			to_str = " __ptr64";
			len = strlen(to_str);
			while ((pos = fname.find(to_str)) != fname.npos)
				fname.erase(pos, len);

			to_str = " __ptr32";
			len = strlen(to_str);
			while ((pos = fname.find(to_str)) != fname.npos)
				fname.erase(pos, len);

			to_str = "enum class";
			len = strlen(to_str);
			while ((pos = fname.find(to_str)) != fname.npos)
				fname.erase(pos, len);

			to_str = "enum";
			len = strlen(to_str);
			while ((pos = fname.find(to_str)) != fname.npos)
				fname.erase(pos, len);

			to_str = "class";
			len = strlen(to_str);
			while ((pos = fname.find(to_str)) != fname.npos)
				fname.erase(pos, len);

			to_str = "struct";
			len = strlen(to_str);
			while ((pos = fname.find(to_str)) != fname.npos)
				fname.erase(pos, len);

			while (fname.back() == ' ')
				fname.pop_back();

			return fname;
#else

			std::string fname(__PRETTY_FUNCTION__);

#ifdef __clang_major__
			const char* ftext = "[Type = ";
			auto pos = fname.find(ftext) + strlen(ftext);
			fname = fname.substr(pos);
			fname.pop_back();
			return fname;

#elif defined(__ICL)
			const char* ftext = "type_tO_sTring<";
			auto pos = fname.find(ftext) + strlen(ftext);
			fname = fname.substr(pos);
			pos = fname.find_last_of('>');
			return fname.substr(0, pos);
#else
			const char* ftext = "[with Type = ";
			auto pos = fname.find(ftext) + strlen(ftext);
			fname = fname.substr(pos);
			pos = fname.find_first_of(';');
			return fname.substr(0, pos);
#endif
#endif

		} // end of type_tO_sTring()
	}	  // namespace types
} // namespace stlonic

/*
	With best respect to Hyunho Cho:

	#define get_type_name(T, ...) type_name<T, ##__VA_ARGS__>()
	#define get_type_category(V, ...) type_name<decltype(V, ##__VA_ARGS__)>()
*/
#define Stlonic_GetTypeName(type_arg, ...) stlonic::types::type_tO_sTring<type_arg, ##__VA_ARGS__>()

#define Stlonic_GetTypeCategory(instance_arg, ...) \
	stlonic::types::type_tO_sTring<decltype(instance_arg, ##__VA_ARGS__)>()

namespace stlonic {

#if defined(STLONIC_SAFE_OPERATION) && (STLONIC_SAFE_OPERATION > 0)
	constexpr const bool bDetectOverFlow = true;
#else
	constexpr const bool bDetectOverFlow = false;
#endif

	namespace types {
		struct no_type {};

		template <typename Type>
		struct range {
			Type begin;

			union {
				Type span;
				Type end;
			};
		};

		template <typename Type>
		std::ostream& operator<<(std::ostream& os, range<Type> const& r) {
			os << "< " << r.begin << ", " << r.end << ">";
			return os;
		}

		template <typename Type>
		range(Type) -> range<Type>;

		template <typename Type>
		range(Type, Type) -> range<Type>;

		template <auto Id, auto... Ids>
		using index_t = std::index_sequence<(std::size_t)Id, (std::size_t)Ids...>;

		template <auto N>
		using make_index_t = std::make_index_sequence<(std::size_t)N>;

		template <typename... Types>
		using index_for = std::make_index_sequence<sizeof...(Types)>;

		template <typename T, T Value>
		struct indexer_type {
			using type = T;
			static constexpr T Index = Value;
			static constexpr T Size = Value;
		};

		template <auto Index>
		using indexer_t = indexer_type<std::remove_cvref_t<decltype(Index)>, Index>;

		template <typename P>
		concept pointer_c = std::is_pointer_v<std::remove_cvref_t<P>>;

		template <typename FuncType, typename PointerType>
		concept pointer_callable_c = pointer_c<PointerType> &&
			requires(PointerType p, FuncType func) {
			func(p);
		};

		template <pointer_c PointerType, pointer_callable_c<PointerType> FuncType>
		auto raii_create_object(PointerType object_ptr, FuncType func) {
			auto deleter = [func](auto ptr) {
				if (ptr)
					func(ptr);
			};

			return std::unique_ptr<std::remove_pointer_t<PointerType>, decltype(deleter)> {
				object_ptr, deleter};
		}

		template <typename CharType>
		std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
												 no_type const& oh_no) {
			os << "no_type or void";
			return os;
		}

		template <typename T>
		concept no_type_c = std::same_as<std::remove_cvref_t<T>, no_type>;

		template <typename T>
		concept valid_type_c = !(std::is_void_v<T> || no_type_c<T>);

		template <typename T>
		concept resize_available_c = requires(T o) {
			o.resize(std::size_t {1});
		};

		template <typename ContainerType>
		concept push_back_available_c = requires(ContainerType container) {
			typename ContainerType::value_type;

			container.push_back(typename ContainerType::value_type {});
		};

		namespace hidden {
			template <typename T>
			struct st_signed_type;

			template <std::integral T>
			struct st_signed_type<T> {
				using type = std::make_signed_t<T>;
			};

			template <std::floating_point T>
			struct st_signed_type<T> {
				using type = T;
			};

			////////////////////////////
			template <typename T>
			struct st_unsigned_type;

			template <std::integral T>
			struct st_unsigned_type<T> {
				using type = std::make_unsigned_t<T>;
			};

			template <std::floating_point T>
			struct st_unsigned_type<T> {
				using type = T;
			};
		} // namespace hidden
		// end of namespace hidden

		template <typename T>
		using make_signed_t = typename hidden::st_signed_type<std::remove_cvref_t<T>>::type;

		template <typename T>
		using make_unsigned_t = typename hidden::st_unsigned_type<std::remove_cvref_t<T>>::type;

		template <typename T>
		concept numerical_c =
			std::integral<std::remove_cvref_t<T>> || std::floating_point<std::remove_cvref_t<T>>;

		template <typename... Types>
		using common_signed_t = make_signed_t<std::common_type_t<std::remove_cvref_t<Types>...>>;

		template <typename... Types>
		using common_unsigned_t =
			make_unsigned_t<std::common_type_t<std::remove_cvref_t<Types>...>>;

		template <typename... Types>
		concept common_type_exists_c = requires {
			// std::common_type<Types...> 내에
			// Type requirement
			typename std::common_type<Types...>::type;
		};

		template <typename P, typename T>
		concept same_flat_c = std::same_as<std::remove_cvref_t<P>, std::remove_cvref_t<T>>;

		template <typename P, typename... Types>
		concept all_same_c = (std::same_as<P, Types> && ...);

		template <std::signed_integral T, std::signed_integral S> // (s, s)
		constexpr decltype(auto) numeric_cast(S s) {
			if (std::numeric_limits<T>::min() <= s && s <= std::numeric_limits<T>::max())
				return std::optional<T> {static_cast<T>(s)};
			else
				return std::optional<T> {};
		}

		template <std::signed_integral T, std::unsigned_integral U> // (s, u)
		constexpr decltype(auto) numeric_cast(U u) {
			if (u <= std::numeric_limits<T>::max())
				return std::optional<T> {static_cast<T>(u)};
			else
				return std::optional<T> {};
		}

		template <std::unsigned_integral T, std::signed_integral S> // (u, s)
		constexpr decltype(auto) numeric_cast(S s) {
			if (s >= 0 && s <= std::numeric_limits<T>::max())
				return std::optional<T> {static_cast<T>(s)};
			else
				return std::optional<T> {};
		}

		template <std::unsigned_integral T, std::unsigned_integral U> // (u, u)
		constexpr decltype(auto) numeric_cast(U u) {
			if (u <= std::numeric_limits<T>::max())
				return std::optional<T> {static_cast<T>(u)};
			else
				return std::optional<T> {};
		}

		template <std::floating_point T, numerical_c S>
		constexpr decltype(auto) numeric_cast(S s) {
			if (std::numeric_limits<T>::min() <= s && s <= std::numeric_limits<T>::max())
				return std::optional<T> {static_cast<T>(s)};
			else
				return std::optional<T> {};
		}

		template <numerical_c... ArgTypes>
		constexpr decltype(auto) signed_cast(ArgTypes... args) {
			using c_t = common_signed_t<ArgTypes...>;

			return std::tuple {numeric_cast<c_t>(args)...};
		}

		template <numerical_c... ArgTypes>
		constexpr decltype(auto) unsigned_cast(ArgTypes... args) {
			using c_t = common_unsigned_t<ArgTypes...>;

			return std::tuple {numeric_cast<c_t>(args)...};
		}

		template <typename T>
		constexpr auto check_operation_validity(T&& target) {
			if constexpr (std::floating_point<std::remove_cvref_t<T>>) {
				if (target != target) // test if not a number or nan
					return false;
				else if (target == target + 1) // positive or negative infinity
					return false;
				else
					return true;
			} else
				return true;
		}

		////////////////////////////////////////////////////////////////

		namespace hidden {
			template <typename S, typename T>
			struct st_common_container {
				using type = no_type;
			};

			template <template <typename, typename...> class ContainerTmpl, typename S,
					  typename... S_tail, typename T, typename... T_tail>
			requires(
				common_type_exists_c<S, T> &&
				!std::is_same_v<
					ContainerTmpl<S, S_tail...>,
					std::tuple<
						S, S_tail...>>) struct st_common_container<ContainerTmpl<S, S_tail...>,
																   ContainerTmpl<T, T_tail...>> {
				using common_t = std::common_type_t<S, T>;

				using type =
					std::conditional_t<std::is_same_v<S, common_t>, ContainerTmpl<S, S_tail...>,
									   ContainerTmpl<T, T_tail...>>;
			};

			template <template <typename, std::size_t> class ContainerTmpl, typename S, typename T,
					  std::size_t M, std::size_t N>
			requires(common_type_exists_c<S, T>) struct st_common_container<ContainerTmpl<S, M>,
																			ContainerTmpl<T, N>> {
				using common_t = std::common_type_t<S, T>;
				using type = ContainerTmpl<common_t, M + N>;
			};

			template <template <typename, std::size_t> class ContainerTmpl, typename S, typename T,
					  std::size_t N>
			requires(common_type_exists_c<S, T>) struct st_common_container<ContainerTmpl<S, N>,
																			ContainerTmpl<T, N>> {
				using common_t = std::common_type_t<S, T>;
				using type = ContainerTmpl<common_t, N>;
			};

			template <typename... Ss, typename... Ts>
			requires(sizeof...(Ss) == sizeof...(Ts) &&
					 (common_type_exists_c<Ss, Ts> &&
					  ...)) struct st_common_container<std::tuple<Ss...>, std::tuple<Ts...>> {
				using type = std::tuple<std::common_type_t<Ss, Ts>...>;
			};
		} // namespace hidden
		// end of namespace hidden

		template <typename S, typename T>
		using common_container_t = typename hidden::st_common_container<S, T>::type;

		namespace hidden {
			template <typename FuncType, typename... ArgTypes>
			auto safe_apply(FuncType&& f, std::tuple<ArgTypes...> const& args)
				-> decltype(f(std::declval<ArgTypes>()...));

			template <typename FuncType, typename ArgType, std::size_t N, std::size_t... Ints>
			auto array_apply(FuncType&& f, std::array<ArgType, N> const& args,
							 std::index_sequence<Ints...>) -> decltype(f(std::get<Ints>(args)...));

			no_type array_apply(...); // fall-back function, catch-all function

			template <typename FuncType, typename ArgType, std::size_t N>
			auto safe_apply(FuncType&& f, std::array<ArgType, N> const& args)
				-> decltype(array_apply(f, args, std::make_index_sequence<N> {}));

			no_type safe_apply(...); // fall-back function, catch-all function

			template <typename FuncType, typename TupleType>
			auto fn_apply(FuncType&& f, TupleType&& args) -> decltype(safe_apply(f, args));
			no_type fn_apply(...); // fall-back function, catch-all function
		}						   // namespace hidden

		template <typename FuncType, typename TupleType>
		using apply_return_t =
			decltype(hidden::fn_apply(std::declval<FuncType>(), std::declval<TupleType>()));

		template <typename FuncType, typename... TupleTypes>
		using common_apply_t = std::common_type_t<apply_return_t<FuncType, TupleTypes>...>;

		template <typename FuncType, typename TupleType>
		constexpr bool is_apply_v = !no_type_c<apply_return_t<FuncType, TupleType>>;

		template <typename FuncType, typename... TupleTypes>
		constexpr bool all_apply_v = (is_apply_v<FuncType, TupleTypes> && ...);

		template <typename FuncType, typename... TupleTypes>
		constexpr bool common_apply_v = all_apply_v<FuncType, TupleTypes...>&&
			common_type_exists_c<apply_return_t<FuncType, TupleTypes>...>;

		template <typename ReturnType, typename FuncType, typename... TupleTypes>
		using enable_if_all_apply_t =
			std::enable_if_t<all_apply_v<FuncType, TupleTypes...>, ReturnType>;

		template <typename FuncType, typename... TupleTypes>
		using apply_return_tuple_t = std::tuple<apply_return_t<FuncType, TupleTypes>...>;

		template <typename FuncType, typename... TupleTypes>
		using apply_return_array_t =
			std::array<std::common_type_t<apply_return_t<FuncType, TupleTypes>...>,
					   sizeof...(TupleTypes)>;

		template <typename FuncType, typename... TupleTypes>
		using apply_return_vector_t =
			std::vector<std::common_type_t<apply_return_t<FuncType, TupleTypes>...>>;

		template <typename FuncType, typename... TupleTypes>
		using void_if_all_apply_t = enable_if_all_apply_t<void, FuncType, TupleTypes...>;

		template <typename FuncType, typename... TupleTypes>
		using tuple_if_all_apply_t =
			enable_if_all_apply_t<apply_return_tuple_t<FuncType, TupleTypes...>, FuncType,
								  TupleTypes...>;

		template <typename FuncType, typename... TupleTypes>
		using array_if_all_apply_t =
			enable_if_all_apply_t<apply_return_array_t<FuncType, TupleTypes...>, FuncType,
								  TupleTypes...>;

		template <typename FuncType, typename... TupleTypes>
		using vector_if_all_apply_t =
			enable_if_all_apply_t<apply_return_vector_t<FuncType, TupleTypes...>, FuncType,
								  TupleTypes...>;

		template <typename FuncType, typename... TupleTypes>
		using common_type_if_all_apply_t =
			std::enable_if_t<common_apply_v<FuncType, TupleTypes...>,
							 std::common_type_t<apply_return_t<FuncType, TupleTypes>...>>;

		template <typename FuncType, typename... ArgTypes>
		types::tuple_if_all_apply_t<FuncType, ArgTypes...> apply_tuple(FuncType&& f,
																	   ArgTypes&&... args) {
			return {std::apply(f, args)...};
		}

		template <typename FuncType, typename... ArgTypes>
		types::vector_if_all_apply_t<FuncType, ArgTypes...> apply_vector(FuncType&& f,
																		 ArgTypes&&... args) {
			using ele_t = types::common_apply_t<FuncType, ArgTypes...>;
			return {(ele_t)std::apply(f, args)...};
		}

		template <typename FuncType, typename... ArgTypes>
		types::array_if_all_apply_t<FuncType, ArgTypes...> apply_array(FuncType&& f,
																	   ArgTypes&&... args) {
			using ele_t = types::common_apply_t<FuncType, ArgTypes...>;
			return {(ele_t)std::apply(f, args)...};
		}

		////////////////////////////////////////////////////////////////

		// safe_cast_operation - smart type cast and do not detect overflow
		template <typename T>
		struct safe_cast_operation {
			const T& value;
			safe_cast_operation(const T& v)
				: value {v} {}
		};

		template <numerical_c T>
		struct safe_cast_operation<T> {
			T value;
			safe_cast_operation(T v)
				: value {std::move(v)} {}
		};

		namespace hidden {
			template <typename T>
			struct st_safe_cast_operation : std::false_type {};

			template <typename T>
			struct st_safe_cast_operation<safe_cast_operation<T>> : std::true_type {};
		}; // namespace hidden

		template <typename T>
		concept safe_co_c = hidden::st_safe_cast_operation<std::remove_cvref_t<T>>::value;

		template <typename T>
		concept non_safe_co_c = !safe_co_c<T>;

		template <typename L, typename R>
		constexpr auto operator+(safe_cast_operation<L> const& a,
								 safe_cast_operation<R> const& b) noexcept {
			if constexpr (numerical_c<L> && numerical_c<R>) {
				using r_t = common_signed_t<L, R>;

				auto aa = numeric_cast<r_t>(a.value);
				auto bb = numeric_cast<r_t>(b.value);

				if (aa.has_value() && bb.has_value())
					return aa.value() + bb.value();
				else {
					std::cout << "In ADDITION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") + (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Addition - Casting failed!");
				}
			} else
				return a.value + b.value;
		}

		template <typename L, typename R>
		constexpr auto operator-(safe_cast_operation<L> const& a,
								 safe_cast_operation<R> const& b) noexcept {
			if constexpr (numerical_c<L> && numerical_c<R>) {
				using r_t = common_signed_t<L, R>;

				auto aa = numeric_cast<r_t>(a.value);
				auto bb = numeric_cast<r_t>(b.value);

				if (aa.has_value() && bb.has_value())
					return aa.value() - bb.value();
				else {
					std::cout << "In SUBTRACTION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") - (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Subtraction - Casting failed!");
				}
			} else
				return a.value + b.value;
		}

		template <typename L, typename R>
		constexpr auto operator*(safe_cast_operation<L> const& a,
								 safe_cast_operation<R> const& b) noexcept {
			if constexpr (numerical_c<L> && numerical_c<R>) {
				using r_t = common_signed_t<L, R>;

				auto aa = numeric_cast<r_t>(a.value);
				auto bb = numeric_cast<r_t>(b.value);

				if (aa.has_value() && bb.has_value())
					return aa.value() * bb.value();
				else {
					std::cout << "In ADDITION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") * (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Multiplication - Casting failed!");
				}
			} else
				return a.value + b.value;
		}

		template <typename L, typename R>
		constexpr auto operator/(safe_cast_operation<L> const& a,
								 safe_cast_operation<R> const& b) noexcept {
			if constexpr (numerical_c<L> && numerical_c<R>) {
				using r_t = common_signed_t<L, R>;

				auto aa = numeric_cast<r_t>(a.value);
				auto bb = numeric_cast<r_t>(b.value);

				if (aa.has_value() && bb.has_value())
					return aa.value() / bb.value();
				else {
					std::cout << "In DIVISION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") / (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Division - Casting failed!");
				}
			} else
				return a.value + b.value;
		}

		template <non_safe_co_c L, typename R>
		constexpr auto operator+(L&& a, safe_cast_operation<R> const& b) {
			return safe_cast_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) + b;
		}

		template <typename L, non_safe_co_c R>
		constexpr auto operator+(safe_cast_operation<L> const& a, R&& b) {
			return a + safe_cast_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_co_c L, typename R>
		constexpr auto operator-(L&& a, safe_cast_operation<R> const& b) {
			return safe_cast_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) - b;
		}

		template <typename L, non_safe_co_c R>
		constexpr auto operator-(safe_cast_operation<L> const& a, R&& b) {
			return a - safe_cast_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_co_c L, typename R>
		constexpr auto operator*(L&& a, safe_cast_operation<R> const& b) {
			return safe_cast_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) * b;
		}

		template <typename L, non_safe_co_c R>
		constexpr auto operator*(safe_cast_operation<L> const& a, R&& b) {
			return a * safe_cast_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_co_c L, typename R>
		constexpr auto operator/(L&& a, safe_cast_operation<R> const& b) {
			return safe_cast_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) / b;
		}

		template <typename L, non_safe_co_c R>
		constexpr auto operator/(safe_cast_operation<L> const& a, R&& b) {
			return a / safe_cast_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		//////////////////////////////////////////////////////////////////////////

		// safe_integral_operation - detect integer overflow and smart type cast
		template <typename T>
		struct safe_integral_operation {
			const T& value;
			safe_integral_operation(const T& v)
				: value {v} {}
		};

		template <numerical_c T>
		struct safe_integral_operation<T> {
			T value;
			safe_integral_operation(T v)
				: value {std::move(v)} {}
		};

		namespace hidden {
			template <typename T>
			struct st_safe_integral_operation : std::false_type {};

			template <typename T>
			struct st_safe_integral_operation<safe_integral_operation<T>> : std::true_type {};
		}; // namespace hidden

		template <typename T>
		concept safe_io_c = hidden::st_safe_integral_operation<std::remove_cvref_t<T>>::value;

		template <typename T>
		concept non_safe_io_c = !safe_io_c<T>;

		template <typename L, typename R>
		constexpr auto operator+(safe_integral_operation<L> const& a,
								 safe_integral_operation<R> const& b) {
			if constexpr (std::integral<L> && std::integral<R>) {
				using r_t = common_signed_t<L, R>;

				// auto aa = numeric_cast<r_t>(a.value);
				// auto bb = numeric_cast<r_t>(b.value);

				auto [aa, bb] = signed_cast(a.value, b.value);

				if (!aa.has_value() || !bb.has_value()) {
					std::cout << "In ADDITION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") + (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Addition - Casting failed!");
				}

				r_t result = aa.value() + bb.value();

				if ((a.value > 0 && b.value > 0 && result < 0) ||
					(a.value < 0 && b.value < 0 && result > 0)) {
					std::cout << "In ADDITION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") + (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Addition - Overflow!");
				} else
					return result;
			} else
				return a.value + b.value;
		}

		template <typename L, typename R>
		constexpr auto operator-(safe_integral_operation<L> const& a,
								 safe_integral_operation<R> const& b) {
			if constexpr (std::integral<L> && std::integral<R>) {
				using r_t = common_signed_t<L, R>;

				auto aa = numeric_cast<r_t>(a.value);
				auto bb = numeric_cast<r_t>(b.value);

				if (!aa.has_value() || !bb.has_value()) {
					std::cout << "In SUBTRACTION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") - (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Subtraction - Casting failed!");
				}

				bb = -bb.value();
				r_t result = aa.value() + bb.value();

				if ((aa.value() > 0 && bb.value() > 0 && result < 0) ||
					(aa.value() < 0 && bb.value() < 0 && result > 0)) {
					std::cout << "In SUBTRACTION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") - (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Subtraction - Overflow!");
				} else
					return result;
			} else
				return a.value - b.value;
		}

		template <typename L, typename R>
		constexpr auto operator*(safe_integral_operation<L> const& a,
								 safe_integral_operation<R> const& b) {
			if constexpr (std::integral<L> && std::integral<R>) {
				using r_t = common_signed_t<L, R>;

				auto aa = numeric_cast<r_t>(a.value);
				auto bb = numeric_cast<r_t>(b.value);

				if (!aa.has_value() || !bb.has_value()) {
					std::cout << "In MULTIPLICATION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") * (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Multiplication - Casting failed!");
				}

				r_t result = aa.value() * bb.value();

				if (bb.value() == 0)
					return result;
				else if (result / bb.value() == aa.value())
					return result;
				else {
					std::cout << "In MULTIPLICATION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") * (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer multiplication - Overflow!");
				}
			} else
				return a.value * b.value;
		}

		template <typename L, typename R>
		constexpr auto operator/(safe_integral_operation<L> const& a,
								 safe_integral_operation<R> const& b) {
			if constexpr (std::integral<L> && std::integral<R>) {
				if (b.value != 0) {
					using r_t = common_signed_t<L, R>;

					auto aa = numeric_cast<r_t>(a.value);
					auto bb = numeric_cast<r_t>(b.value);

					if (aa.has_value() && bb.has_value())
						return aa.value() / bb.value();
					else {
						std::cout << "In DIVISION: (" << a.value << ")(" << Stlonic_GetTypeName(L)
								  << ") / (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
								  << std::endl;

						throw std::runtime_error("Integer Division - Casting failed!");
					}
				} else {
					std::cout << "In Division: (" << a.value << ")(" << Stlonic_GetTypeName(L)
							  << ") / (" << b.value << ")(" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					throw std::runtime_error("Integer Division By Zero!");
				}
			} else
				return a.value / b.value;
		}

		template <non_safe_io_c L, typename R>
		constexpr auto operator+(L&& a, safe_integral_operation<R> const& b) {
			return safe_integral_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) + b;
		}

		template <typename L, non_safe_io_c R>
		constexpr auto operator+(safe_integral_operation<L> const& a, R&& b) {
			return a + safe_integral_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_io_c L, typename R>
		constexpr auto operator-(L&& a, safe_integral_operation<R> const& b) {
			return safe_integral_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) - b;
		}

		template <typename L, non_safe_io_c R>
		constexpr auto operator-(safe_integral_operation<L> const& a, R&& b) {
			return a - safe_integral_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_io_c L, typename R>
		constexpr auto operator*(L&& a, safe_integral_operation<R> const& b) {
			return safe_integral_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) * b;
		}

		template <typename L, non_safe_io_c R>
		constexpr auto operator*(safe_integral_operation<L> const& a, R&& b) {
			return a * safe_integral_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_io_c L, typename R>
		constexpr auto operator/(L&& a, safe_integral_operation<R> const& b) {
			return safe_integral_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) / b;
		}

		template <typename L, non_safe_io_c R>
		constexpr auto operator/(safe_integral_operation<L> const& a, R&& b) {
			return a / safe_integral_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		// safe_numerical_operation - detect numerical overflow and smart type cast
		template <typename T>
		struct safe_numerical_operation {
			const T& value;
			safe_numerical_operation(const T& v)
				: value {v} {}
		};

		template <numerical_c T>
		struct safe_numerical_operation<T> {
			T value;
			safe_numerical_operation(T v)
				: value {std::move(v)} {}
		};

		namespace hidden {
			template <typename T>
			struct st_safe_numerical_operation : std::false_type {};

			template <typename T>
			struct st_safe_numerical_operation<safe_numerical_operation<T>> : std::true_type {};
		}; // namespace hidden

		template <typename T>
		concept safe_no_c = hidden::st_safe_numerical_operation<std::remove_cvref_t<T>>::value;

		template <typename T>
		concept non_safe_no_c = !safe_no_c<T>;

		template <typename L, typename R>
		constexpr auto operator+(safe_numerical_operation<L> const& a,
								 safe_numerical_operation<R> const& b) {
			if constexpr (std::integral<L> && std::integral<R>) {
				return safe_integral_operation {a.value} + safe_integral_operation {b.value};
			} else if constexpr (std::floating_point<L> && std::floating_point<R>) {
				using R_t = common_signed_t<L, R>;

				R_t result = static_cast<R_t>(a.value) + static_cast<R_t>(b.value);

				if (check_operation_validity(result))
					return result;
				else {
					std::cout << "Floating-point Addition accuracy failure!" << std::endl;

					std::cout << "In ADDITION: " << a.value << " (" << Stlonic_GetTypeName(L) << ") + "
							  << b.value << " (" << Stlonic_GetTypeName(R) << ")" << std::endl;

					std::cout << "Possibly floating point operation error!" << std::endl;

					throw std::runtime_error("binary addition failure");
				}

				// for compiler type parsing
				return R_t {};
			} else
				return a.value + b.value;
		}

		template <typename L, typename R>
		constexpr auto operator-(safe_numerical_operation<L> const& a,
								 safe_numerical_operation<R> const& b) {
			if constexpr (std::integral<L> && std::integral<R>) {
				return safe_integral_operation {a.value} - safe_integral_operation {b.value};
			} else if constexpr (std::floating_point<L> && std::floating_point<R>) {
				using R_t = common_signed_t<L, R>;

				R_t result = static_cast<R_t>(a.value) - static_cast<R_t>(b.value);

				if (check_operation_validity(result))
					return result;
				else {
					std::cout << "Floating-point Subtraction accuracy failure!" << std::endl;
					std::cout << "In SUBTRACTION: " << a.value << " (" << Stlonic_GetTypeName(L)
							  << ") - " << b.value << " (" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					std::cout << "Possibly floating point operation error!" << std::endl;

					throw std::runtime_error("binary subtraction failure");
				}

				// for compiler type parsing
				return R_t {};
			} else
				return a.value - b.value;
		}

		template <typename L, typename R>
		constexpr auto operator*(safe_numerical_operation<L> const& a,
								 safe_numerical_operation<R> const& b) {
			if constexpr (std::integral<L> && std::integral<R>) {
				return safe_integral_operation {a.value} * safe_integral_operation {b.value};
			} else if constexpr (std::floating_point<L> && std::floating_point<R>) {
				using R_t = common_signed_t<L, R>;

				R_t result = static_cast<R_t>(a.value) * static_cast<R_t>(b.value);

				if (check_operation_validity(result))
					return result;
				else {
					std::cout << "Floating-point Mulitiplication accuracy failure!" << std::endl;

					std::cout << "In MULTIPLICATION: " << a.value << " (" << Stlonic_GetTypeName(L)
							  << ") * " << b.value << " (" << Stlonic_GetTypeName(R) << ")"
							  << std::endl;

					std::cout << "Possibly floating point operation error!" << std::endl;

					throw std::runtime_error("binary multiplication failure");
				}

				// for compiler type parsing
				return R_t {};
			} else
				return a.value * b.value;
		}

		template <typename L, typename R>
		constexpr auto operator/(safe_numerical_operation<L> const& a,
								 safe_numerical_operation<R> const& b) {
			if constexpr (std::integral<L> && std::integral<R>) {
				return safe_integral_operation {a.value} / safe_integral_operation {b.value};
			} else if constexpr (std::floating_point<L> && std::floating_point<R>) {
				using R_t = common_signed_t<L, R>;

				if (b.value != 0) {
					R_t result = static_cast<R_t>(a.value) / static_cast<R_t>(b.value);

					if (check_operation_validity(result))
						return result;
				}

				std::cout << "Floating-point Division by Zero!" << std::endl;

				std::cout << "In DIVISION: " << a.value << " (" << Stlonic_GetTypeName(L) << ") / "
						  << b.value << " (" << Stlonic_GetTypeName(R) << ")" << std::endl;

				throw std::runtime_error("Division by Zero");

				// for compiler type parsing
				return R_t {};
			} else
				return a.value / b.value;
		}

		template <non_safe_no_c L, typename R>
		constexpr auto operator+(L&& a, safe_numerical_operation<R> const& b) {
			return safe_numerical_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) + b;
		}

		template <typename L, non_safe_no_c R>
		constexpr auto operator+(safe_numerical_operation<L> const& a, R&& b) {
			return a + safe_numerical_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_no_c L, typename R>
		constexpr auto operator-(L&& a, safe_numerical_operation<R> const& b) {
			return safe_numerical_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) - b;
		}

		template <typename L, non_safe_no_c R>
		constexpr auto operator-(safe_numerical_operation<L> const& a, R&& b) {
			return a - safe_numerical_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_no_c L, typename R>
		constexpr auto operator*(L&& a, safe_numerical_operation<R> const& b) {
			return safe_numerical_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) * b;
		}

		template <typename L, non_safe_no_c R>
		constexpr auto operator*(safe_numerical_operation<L> const& a, R&& b) {
			return a * safe_numerical_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		template <non_safe_no_c L, typename R>
		constexpr auto operator/(L&& a, safe_numerical_operation<R> const& b) {
			return safe_numerical_operation<std::remove_cvref_t<L>>(std::forward<L>(a)) / b;
		}

		template <typename L, non_safe_no_c R>
		constexpr auto operator/(safe_numerical_operation<L> const& a, R&& b) {
			return a / safe_numerical_operation<std::remove_cvref_t<R>>(std::forward<R>(b));
		}

		// safe binary operation, if STLONIC_SAFE_NUMERICL_OPERATIONS=1,
		//   detect overflow and "integer division by zero"
		// otherwise, safe cast for integeral numbers
		template <long long DebugMode = 2, typename T = int>
		constexpr auto sbo(T&& value) noexcept(!stlonic::bDetectOverFlow) {
			if constexpr (DebugMode == 1)
				return safe_integral_operation<std::remove_cvref_t<T>>(std::forward<T>(value));
			else if constexpr (DebugMode == 2)
				return safe_numerical_operation<std::remove_cvref_t<T>>(std::forward<T>(value));
			else
				return safe_cast_operation<std::remove_cvref_t<T>>(std::forward<T>(value));
		}

		namespace hidden {
			template <typename... Types>
			struct st_all_same;

			template <>
			struct st_all_same<> : std::true_type {};

			template <typename P, typename... Types>
			struct st_all_same<P, Types...> : std::bool_constant<all_same_c<P, Types...>> {};
		} // namespace hidden
		// end of namespace hidden

		template <typename... Types>
		concept all_the_same_c = hidden::st_all_same<Types...>::value;

		template <typename P, typename... Types>
		concept all_same_flat_c = all_same_c<std::remove_cvref_t<P>, std::remove_cvref_t<Types>...>;

		template <typename... Types>
		concept all_the_same_flat_c = all_the_same_c<std::remove_cvref_t<Types>...>;

		namespace hidden {
			// [int, short, float, short] = (int != short) && (int != float) && (int != short)
			template <typename P, typename... Types>
			concept partial_different_c = (!std::same_as<P, Types> && ...);

			template <typename P, typename... Types>
			consteval bool fn_all_different() {
				if constexpr (sizeof...(Types) == 0)
					return partial_different_c<P>;
				else
					return partial_different_c<P, Types...> && fn_all_different<Types...>();
			}

			template <typename T, typename S>
			struct st_same_container : std::false_type {};

			template <template <typename, typename...> class ContainerType, typename T1,
					  typename T2, typename... Tails>
			struct st_same_container<ContainerType<T1, Tails...>, ContainerType<T2, Tails...>>
				: std::true_type {};

			template <typename T>
			struct st_is_vector : std::false_type {};

			template <typename T>
			struct st_is_vector<std::vector<T>> : std::true_type {};

			template <typename T>
			struct st_first_element {
				using type = no_type;
			};

			template <template <typename, typename...> class ContainerType, typename T,
					  typename... Types>
			struct st_first_element<ContainerType<T, Types...>> {
				using type = T;
			};

			template <template <typename, auto...> class ContainerType, typename T, auto... Values>
			struct st_first_element<ContainerType<T, Values...>> {
				using type = T;
			};

			template <template <typename, std::size_t> class ContainerType, typename T,
					  std::size_t N>
			struct st_first_element<ContainerType<T, N>> {
				using type = T;
			};
		} // namespace hidden
		// end of namespace hidden

		template <typename T>
		concept vector_c = hidden::st_is_vector<std::remove_cvref_t<T>>::value;

		template <typename T>
		using first_type_t = typename hidden::st_first_element<std::remove_cvref_t<T>>::type;

		template <typename T, typename S>
		concept same_container_c =
			hidden::st_same_container<std::remove_cvref_t<T>, std::remove_cvref_t<S>>::value;

		template <typename P, typename... Types>
		concept all_different_c = hidden::fn_all_different<P, Types...>();

		template <typename P, typename... Types>
		concept all_different_flat_c =
			all_different_c<std::remove_cvref_t<P>, std::remove_cvref_t<Types>...>;

		template <typename P, typename Q, typename... Types>
		concept partially_different_c =
			!all_same_c<P, Q, Types...> && !all_different_c<P, Q, Types...>;

		template <typename P, typename Q, typename... Types>
		concept partially_different_flat_c =
			partially_different_c<std::remove_cvref_t<P>, std::remove_cvref_t<Q>,
								  std::remove_cvref_t<Types>...>;

		template <auto... Indices>
		requires all_the_same_c<decltype(Indices)...>
		using sequence =
			std::integer_sequence<std::common_type_t<std::remove_cvref_t<decltype(Indices)>...>,
								  Indices...>;

		template <typename... Types>
		struct type_container {};

		template <typename Type> // Type = char, const_ptr_t<char> = const char* - pointer to const
								 // char
								 using const_ptr_t = std::add_pointer_t<std::add_const_t<Type>>;

		template <typename T>
		constexpr decltype(auto) decay_value(T&& value) noexcept {
			if constexpr (std::is_function_v<std::remove_reference_t<T>> ||
						  std::is_array_v<std::remove_reference_t<T>>) {
				return static_cast<std::decay_t<std::remove_reference_t<T>>>(value);
			} else {
				return std::forward<T>(value);
			}
		}

		template <template <typename...> class ContainerType, typename... ArgTypes>
		constexpr decltype(auto) create_container(ArgTypes&&... args) {
			return ContainerType {decay_value(std::forward<ArgTypes>(args))...};
		}

		template <template <typename, auto> class ContainerType, all_the_same_flat_c... ArgTypes>
		constexpr decltype(auto) create_container(ArgTypes&&... args) {
			return ContainerType {decay_value(std::forward<ArgTypes>(args))...};
		}

		namespace hidden {
			template <typename>
			struct st_is_type_container : std::false_type {};

			template <typename... Types>
			struct st_is_type_container<type_container<Types...>> : std::true_type {};

		} // namespace hidden

		template <typename T>
		concept type_container_c = hidden::st_is_type_container<T>::value;

		template <typename T>
		concept non_type_container_c = !hidden::st_is_type_container<T>::value;

		namespace hidden {
			template <typename A, typename B>
			struct st_common_vector {
				using type = no_type;
			};

			template <numerical_c A, numerical_c B>
			struct st_common_vector<A, B> {
				using type = common_signed_t<A, B>;
			};

			template <numerical_c A, numerical_c B>
			struct st_common_vector<std::vector<A>, std::vector<B>> {
				using type = std::vector<typename st_common_vector<A, B>::type>;
			};

			template <vector_c A, vector_c B>
			struct st_common_vector<std::vector<A>, std::vector<B>> {
				using type = std::vector<typename st_common_vector<A, B>::type>;
			};

			template <numerical_c A, numerical_c B>
			struct st_common_vector<std::vector<A>, B> {
				using type = std::vector<typename st_common_vector<A, B>::type>;
			};

			template <numerical_c A, numerical_c B>
			struct st_common_vector<A, std::vector<B>> {
				using type = std::vector<typename st_common_vector<A, B>::type>;
			};

			template <vector_c A, numerical_c B>
			struct st_common_vector<std::vector<A>, B> {
				using type = std::vector<typename st_common_vector<A, B>::type>;
			};

			template <numerical_c A, vector_c B>
			struct st_common_vector<A, std::vector<B>> {
				using type = std::vector<typename st_common_vector<A, B>::type>;
			};

			template <typename A, typename B, std::size_t N>
			struct st_common_vector<std::vector<std::array<A, N>>, std::vector<std::array<B, N>>> {
				using type = std::vector<std::array<typename st_common_vector<A, B>::type, N>>;
			};

			template <numerical_c A, typename B, std::size_t N>
			struct st_common_vector<A, std::vector<std::array<B, N>>> {
				using type = std::vector<std::array<typename st_common_vector<A, B>::type, N>>;
			};

			template <typename A, numerical_c B, std::size_t N>
			struct st_common_vector<std::vector<std::array<A, N>>, B> {
				using type = std::vector<std::array<typename st_common_vector<A, B>::type, N>>;
			};

			template <numerical_c A, numerical_c B, std::size_t N>
			struct st_common_vector<std::vector<std::array<A, N>>, std::array<B, N>> {
				using type = std::vector<std::array<typename st_common_vector<A, B>::type, N>>;
			};

			template <numerical_c A, numerical_c B, std::size_t N>
			struct st_common_vector<std::array<A, N>, std::vector<std::array<B, N>>> {
				using type = std::vector<std::array<typename st_common_vector<A, B>::type, N>>;
			};
		} // namespace hidden
		// end of namespace hidden

		template <typename A, typename B>
		using common_vector_t =
			typename hidden::st_common_vector<std::remove_cvref_t<A>, std::remove_cvref_t<B>>::type;

		template <typename A, typename B>
		concept non_common_vector_c = no_type_c<common_vector_t<A, B>>;

		template <typename A, typename B>
		concept common_vector_c = !non_common_vector_c<A, B>;

		// FIX-LATER - a = 5;
		template <typename TargetChar = char, typename SourceChar = char>
		std::basic_string<TargetChar> smart_convert(const std::basic_string<SourceChar>& src) {
			return src;
		}

		template <typename TagetCharPtr = const char*, typename SourceCharPtr = const char*>
		TagetCharPtr smart_convert(SourceCharPtr ptr) {
			return ptr;
		}

		template <typename CharType, typename... Types>
		std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
												 const type_container<Types...>& tc);

		//////////////////////////// Implementation ///////////////////////////
		namespace hidden {
			template <typename CharType, typename Type, typename... Types>
			std::basic_ostream<CharType>&
				print_type_container(std::basic_ostream<CharType>& os,
									 const type_container<Type, Types...>& tc) {
				using char_ptr = const_ptr_t<CharType>;

				if constexpr (sizeof...(Types) == 0) {
					if constexpr (type_container_c<Type>)
						os << Type {}; // climax of recursion
					else
						os << smart_convert<CharType>(Stlonic_GetTypeName(Type));

					return os;
				} else {
					if constexpr (type_container_c<Type>)
						os << Type {}; // climax of recursion
					else
						os << smart_convert<CharType>(Stlonic_GetTypeName(Type));

					os << smart_convert<char_ptr>(", ");

					return print_type_container(os, type_container<Types...> {});
				}
			}

		} // end of namespace hidden

		template <typename CharType, typename... Types>
		std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os,
												 const type_container<Types...>& tc) {
			using char_ptr = const_ptr_t<CharType>;

			if constexpr (sizeof...(Types) == 0) {
				os << smart_convert<char_ptr>("< >");

				return os;
			} else {
				os << smart_convert<char_ptr>("< ");

				hidden::print_type_container(os, tc);

				os << smart_convert<char_ptr>(" >");

				return os;
			}
		}

		namespace hidden {
			// primary class template - <P, int, short, double> = (P == int) || (P == short) || (P
			// == double) determins the count of template parameters
			template <typename P, typename... Types>
			struct st_type_in_container;

			// from onward specialization, do not concern about
			// template parameter list, but concentrate on template arguments.
			template <typename P>
			struct st_type_in_container<P> {
				static constexpr bool value = false;
			};

			template <typename P, non_type_container_c Type, typename... Tails>
			struct st_type_in_container<P, Type, Tails...> {
				static constexpr bool value =
					std::same_as<P, Type> || st_type_in_container<P, Tails...>::value;
			};

			template <typename P, typename... Types, typename... Tails>
			struct st_type_in_container<P, type_container<Types...>, Tails...> {
				static constexpr bool value = st_type_in_container<P, Types...>::value ||
					st_type_in_container<P, Tails...>::value;
			};

		} // end of namespace hidden

		template <typename P, typename... Types>
		concept is_in_type_container_c = hidden::st_type_in_container<P, Types...>::value;

		namespace hidden {
			// primary class template - determines the count of template parameters
			template <typename...>
			struct st_pop_front_t;

			template <>
			struct st_pop_front_t<> {
				using type = type_container<>;
			};

			template <typename Type, typename... Types>
			struct st_pop_front_t<Type, Types...> {
				using type = type_container<Types...>;
			};

			template <typename... Types>
			struct st_pop_front_t<type_container<Types...>> {
				using type = typename st_pop_front_t<Types...>::type;
			};

		} // end of namespace hidden

		template <typename... Types>
		using pop_front_t = typename hidden::st_pop_front_t<Types...>::type;

		namespace hidden {
			template <typename... LeftTypes>
			constexpr auto fn_pop_back(type_container<LeftTypes...> left, type_container<> right) {
				std::cout << left << " - " << right << std::endl;

				return left;
			}

			template <typename... LeftTypes, typename Head>
			constexpr auto fn_pop_back(type_container<LeftTypes...> left,
									   type_container<Head> right) {
				std::cout << left << " - " << right << std::endl;
				std::cout << "Return: " << left << std::endl;

				return left;
			}

			template <typename... LeftTypes, typename First, typename Second, typename... Tails>
			constexpr auto fn_pop_back(type_container<LeftTypes...> left,
									   type_container<First, Second, Tails...> right) {
				std::cout << left << " - " << right << std::endl;

				return fn_pop_back(type_container<LeftTypes..., First> {},
								   type_container<Second, Tails...> {});
			}

			template <typename... Types>
			struct st_pop_back_t;

			template <>
			struct st_pop_back_t<> {
				using type = type_container<>;
			};

			template <non_type_container_c Type, non_type_container_c... Types>
			struct st_pop_back_t<Type, Types...> {
				using type =
					decltype(fn_pop_back(type_container<> {}, type_container<Type, Types...> {}));
			};

			template <typename... Types>
			struct st_pop_back_t<type_container<Types...>> {
				using type =
					decltype(fn_pop_back(type_container<> {}, type_container<Types...> {}));
			};

		} // end of namespace hidden

		template <typename... Types>
		using pop_back_t = typename hidden::st_pop_back_t<Types...>::type;

		template <typename Type>
		concept iterator_available_c = requires {
			typename Type::iterator;
		};

		template <typename Type>
		concept reverse_iterator_available_c = requires {
			typename Type::reverse_iterator;
		};

		namespace hidden {
			// primary class template
			// primary class template determines (1) the template parameter count
			// (2) parameter category
			// (3) declares struct or class name
			// (4) enables default parameter initialization
			template <typename T>
			struct st_stl_container {
				constexpr static bool value = false;
			};

			template <typename Type, typename... Types,
					  template <typename, typename...> class ContainerTemplate>
			struct st_stl_container<ContainerTemplate<Type, Types...>> {
				static constexpr bool value =
					iterator_available_c<ContainerTemplate<Type, Types...>>;
			};

			template <typename T>
			struct st_std_map_container {
				constexpr static bool value = false;
			};

			template <typename KeyType, typename ValueType, typename... Types>
			struct st_std_map_container<std::map<KeyType, ValueType, Types...>> {
				constexpr static bool value = true;
			};

			template <typename KeyType, typename ValueType, typename... Types>
			struct st_std_map_container<std::unordered_map<KeyType, ValueType, Types...>> {
				constexpr static bool value = true;
			};

			template <typename T>
			struct st_tbb_map_container {
				constexpr static bool value = false;
			};

			template <typename KeyType, typename ValueType, typename... Types>
			struct st_tbb_map_container<tbb::concurrent_map<KeyType, ValueType, Types...>> {
				constexpr static bool value = true;
			};

			template <typename KeyType, typename ValueType, typename... Types>
			struct st_tbb_map_container<
				tbb::concurrent_unordered_map<KeyType, ValueType, Types...>> {
				constexpr static bool value = true;
			};

		} // end of namespace hidden

		template <class T>
		concept view_c = // std::ranges::view<T>
			std::ranges::range<T> && std::movable<T> && std::ranges::enable_view<T>;

		template <class T>
		concept view_flat_c = view_c<std::remove_cvref_t<T>>;

		template <typename T>
		concept stl_container_c = // MSVC++ 2019, c++latest, MSVC++ 2022
			hidden::st_stl_container<T>::value && !view_c<T>;

		/*
			strings library -
				https://en.cppreference.com/w/cpp/string

			Standard library header - string_view
				https://en.cppreference.com/w/cpp/header/string_view

			String and character literals (C++)
				https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=msvc-170

		*/
		using string_containers =
			types::type_container<std::string, std::wstring, std::u8string, std::u16string,
								  std::u32string, std::string_view, std::u8string_view,
								  std::u16string_view, std::u32string_view, std::wstring_view>;

		template <typename P>
		concept std_map_c = hidden::st_std_map_container<std::remove_cvref_t<P>>::value;

		template <typename P>
		concept tbb_map_c = hidden::st_tbb_map_container<std::remove_cvref_t<P>>::value;

		template <typename P>
		concept map_c = std_map_c<P> || tbb_map_c<P>;

		template <typename P>
		concept stream_undefined_container_c =
			(stl_container_c<P> || view_c<P>)&&!is_in_type_container_c<P, string_containers> &&
			!map_c<P>;

		template <typename P>
		concept stream_undefined_container_flat_c =
			stream_undefined_container_c<std::remove_cvref_t<P>>;

		namespace hidden {
			template <typename... Types>
			struct st_make_unique_types;

			template <>
			struct st_make_unique_types<> {
				using type = type_container<>;
			};

			template <typename Type, typename... Types>
			struct st_make_unique_types<Type, Types...> {
				// using type = decltype(fn_make_unique_types(type_container<>{},
				// type_container<Type, Types...>{}));
				using type = typename st_make_unique_types<type_container<>,
														   type_container<Type, Types...>>::type;
			};

			template <typename... Types>
			struct st_make_unique_types<type_container<Types...>> {
				// using type = decltype(fn_make_unique_types(type_container<>{},
				// type_container<Types...>{}));

				using type =
					typename st_make_unique_types<type_container<>, type_container<Types...>>::type;
			};

			template <typename... LeftTypes, typename Head>
			struct st_make_unique_types<type_container<LeftTypes...>, type_container<Head>> {
				using type =
					std::conditional_t<is_in_type_container_c<Head, type_container<LeftTypes...>>,
									   type_container<LeftTypes...>,
									   type_container<LeftTypes..., Head>>;
			};

			template <typename... LeftTypes, typename First, typename Second, typename... Tails>
			struct st_make_unique_types<type_container<LeftTypes...>,
										type_container<First, Second, Tails...>> {
				using new_left_t = typename st_make_unique_types<type_container<LeftTypes...>,
																 type_container<First>>::type;

				using type = typename st_make_unique_types<new_left_t,
														   type_container<Second, Tails...>>::type;
			};

		} // end of namespace hidden

		template <typename... Types>
		using make_unique_types_t = typename hidden::st_make_unique_types<Types...>::type;

		// P is a Prototype parameter
		template <typename P, typename CharType>
		concept ostream_operator_available_c = requires(P obj, std::basic_ostream<CharType>& os) {
			os << obj; // Simple Requirements
		};

		namespace hidden {
			template <typename... Types>
			consteval auto fn_type_container_to_variant(types::type_container<Types...>) {
				return std::variant<Types...> {};
			}

			template <typename... Types>
			consteval auto fn_make_unique_variant(
				std::variant<Types...>) // std::variant<int, double, int, double, short>
										// std::variant<int, double, short>
			{
				using unique_types = types::make_unique_types_t<std::monostate, Types...>;

				return fn_type_container_to_variant(unique_types {});
			}
		} // namespace hidden
		// end of namespace hidden

		template <typename VariantType>
		using make_unique_variant_t = decltype(hidden::fn_make_unique_variant(VariantType {}));

		template <typename... Types>
		auto make_vector_of_variants(Types... args) {
			using variant_t = types::make_unique_variant_t<std::variant<Types...>>;

			return std::vector<variant_t> {args...};
		}

		/////////////////////////////////////////////////////////////////////////////

		namespace hidden {
			template <typename T>
			struct st_is_variant : std::false_type {};

			template <typename... Types>
			struct st_is_variant<std::variant<Types...>> : std::true_type {};

			template <typename T>
			struct st_is_tuple : std::false_type {};

			template <typename... Types>
			struct st_is_tuple<std::tuple<Types...>> : std::true_type {};

			template <typename T>
			struct st_is_std_array : std::false_type {};

			template <typename T, std::size_t N>
			struct st_is_std_array<std::array<T, N>> : std::true_type {};

			template <typename T>
			struct st_is_span : std::false_type {};

			template <typename T, std::size_t N>
			struct st_is_span<std::span<T, N>> : std::true_type {};

			template <typename T>
			struct st_is_c_array : std::false_type {};

			template <typename T, std::size_t N>
			struct st_is_c_array<T[N]> : std::true_type {};

			template <typename T>
			struct st_is_pair : std::false_type {};

			template <typename T, typename S>
			struct st_is_pair<std::pair<T, S>> : std::true_type {};

			////////////////////////////////////////////////////////
			template <typename T, T START, T END, T STEP, T... Indices>
			constexpr auto fn_make_sequence(std::integer_sequence<T, Indices...> seq) {
				if constexpr (STEP > 0 && START < END) // [START, END)<STEP - positive>
				{
					return fn_make_sequence<T, START + STEP, END, STEP>(
						std::integer_sequence<T, Indices..., START> {});
				} else if constexpr (STEP < 0 && START > END) // [START, END)<STEP - negative>
				{
					return fn_make_sequence<T, START + STEP, END, STEP>(
						std::integer_sequence<T, Indices..., START> {});
				} else
					return seq;
			}

			template <typename T>
			struct st_const_chars : std::false_type {};

			template <std::size_t N>
			struct st_const_chars<const char[N]> : std::true_type {};

			template <std::size_t N>
			struct st_const_chars<const wchar_t[N]> : std::true_type {};

			template <>
			struct st_const_chars<const char*> : std::true_type {};

			template <>
			struct st_const_chars<const wchar_t*> : std::true_type {};

			template <std::size_t N>
			struct st_const_chars<const char8_t[N]> : std::true_type {};

			template <>
			struct st_const_chars<const char8_t*> : std::true_type {};

			template <std::size_t N>
			struct st_const_chars<const char16_t[N]> : std::true_type {};

			template <>
			struct st_const_chars<const char16_t*> : std::true_type {};

			template <std::size_t N>
			struct st_const_chars<const char32_t[N]> : std::true_type {};

			template <>
			struct st_const_chars<const char32_t*> : std::true_type {};

			/////////////////////////////////

			template <typename T>
			struct st_non_const_chars : std::false_type {};

			template <std::size_t N>
			struct st_non_const_chars<char[N]> : std::true_type {};

			template <std::size_t N>
			struct st_non_const_chars<wchar_t[N]> : std::true_type {};

			template <>
			struct st_non_const_chars<char*> : std::true_type {};

			template <>
			struct st_non_const_chars<wchar_t*> : std::true_type {};

			template <std::size_t N>
			struct st_non_const_chars<char8_t[N]> : std::true_type {};

			template <>
			struct st_non_const_chars<char8_t*> : std::true_type {};

			template <std::size_t N>
			struct st_non_const_chars<char16_t[N]> : std::true_type {};

			template <>
			struct st_non_const_chars<char16_t*> : std::true_type {};

			template <std::size_t N>
			struct st_non_const_chars<char32_t[N]> : std::true_type {};

			template <>
			struct st_non_const_chars<char32_t*> : std::true_type {};

		} // namespace hidden
		// end of namespace hidden

		template <typename T>
		concept const_chars_c = hidden::st_const_chars<std::remove_reference_t<T>>::value;

		template <typename T>
		concept non_const_chars_c = hidden::st_non_const_chars<std::remove_reference_t<T>>::value;

		template <typename T>
		concept chars_c = const_chars_c<T> || non_const_chars_c<T>;

		template <typename T>
		concept non_chars_c = !chars_c<T>;

		template <typename T, T START, T END, T STEP>
		using make_sequence =
			decltype(hidden::fn_make_sequence<T, START, END, STEP>(std::integer_sequence<T> {}));

		template <typename T>
		concept variant_c = hidden::st_is_variant<T>::value;

		template <typename T>
		concept variant_flat_c = variant_c<std::remove_cvref_t<T>>;

		template <typename T>
		concept tuple_c = hidden::st_is_tuple<T>::value;

		template <typename T>
		concept tuple_flat_c = tuple_c<std::remove_cvref_t<T>>;

		template <typename T>
		concept non_tuple_c = !tuple_c<std::remove_cvref_t<T>>;

		template <typename T>
		concept std_array_c = hidden::st_is_std_array<T>::value;

		template <typename T>
		concept std_array_flat_c = std_array_c<std::remove_cvref_t<T>>;

		template <typename T>
		concept non_std_array_c = !std_array_c<std::remove_cvref_t<T>>;

		template <typename T>
		concept either_array_or_tuple_c = std_array_c<T> || tuple_c<T>;

		template <typename T>
		concept either_array_or_tuple_flat_c = std_array_flat_c<T> || tuple_flat_c<T>;

		template <typename T>
		concept neither_array_nor_tuple_c = !either_array_or_tuple_c<T>;

		template <typename T>
		concept neither_array_nor_tuple_flat_c = !either_array_or_tuple_flat_c<T>;

		template <typename T> // T가 const, lvalue reference, rvalue reference (X)
		concept span_c = hidden::st_is_span<T>::value;

		template <typename T> // T가 const, volatile, lvalue reference, rvalue reference (O)
		concept span_flat_c = span_c<std::remove_cvref_t<T>>;

		template <typename T> // T가 const, volatile, lvalue reference, rvalue reference (O)
		concept non_span_c = !span_c<std::remove_cvref_t<T>>;

		template <typename T>
		concept std_array_span_c = std_array_flat_c<T> || span_flat_c<T>;

		template <typename T>
		concept non_std_array_span_c = !std_array_span_c<T>;

		template <typename T>
		concept c_array_c = hidden::st_is_c_array<T>::value;

		template <typename T>
		concept c_array_flat_c = c_array_c<std::remove_cvref_t<T>>;

		template <typename T>
		concept pair_c = hidden::st_is_pair<T>::value;

		template <typename T>
		concept pair_flat_c = pair_c<std::remove_cvref_t<T>>;

		template <vector_c... ContainerTypes, auto N = sizeof...(ContainerTypes)>
		requires(N > 0) constexpr auto element_counts_are_the_same(ContainerTypes&&... containers) {
			auto Vs = std::forward_as_tuple(containers...);
			auto A_size = std::get<0>(Vs).size();

			// N for A, B, C..., e.g. wn. N == 0, get<N>(Vs) == A
			return for_stallion<N>([&]<auto... k>(sequence<k...>) {
				return ((A_size == std::get<k>(Vs).size()) && ...);
			});
		}

		template <std_array_flat_c... ContainerTypes, auto N = sizeof...(ContainerTypes)>
		requires(N > 0) constexpr auto element_counts_are_the_same(ContainerTypes... containers) {
			auto Vs = std::tuple(containers...);

			using A_t = std::tuple_element_t<0, decltype(Vs)>;
			auto A_size = std::tuple_size_v<A_t>;

			// N for A, B, C..., e.g. wn. N == 0, get<N>(Vs) == A
			return for_stallion<N>([=]<auto... k>(sequence<k...>) {
				return ((A_size == std::tuple_size_v<std::tuple_element_t<k, decltype(Vs)>>)&&...);
			});
		}

		template <std::size_t N, vector_c VectorType>
		constexpr decltype(auto) make_span(VectorType&& v) {
			using element_t = first_type_t<VectorType>;
			return std::span<element_t, N> {v};
		}

		template <std_array_flat_c ArrayType>
		constexpr decltype(auto) make_span(ArrayType&& array) {
			return std::span {array};
		}

		template <typename T, std::size_t N>
		constexpr decltype(auto) make_span(T (&array)[N]) {
			return std::span {array};
		}

		// end of namespace hidden

		///////////////////////////////////////////////////////
		namespace hidden {
			template <typename A, typename B>
			struct st_std_common_array {
				using type = no_type;
			};

			template <numerical_c A, numerical_c B>
			struct st_std_common_array<A, B> {
				using type = common_signed_t<A, B>;
			};

			template <numerical_c A, numerical_c B, std::size_t N>
			struct st_std_common_array<std::array<A, N>, std::array<B, N>> {
				using type = std::array<typename st_std_common_array<A, B>::type, N>;
			};

			template <std_array_c A, std_array_c B, std::size_t N>
			struct st_std_common_array<std::array<A, N>, std::array<B, N>> {
				using type = std::array<typename st_std_common_array<A, B>::type, N>;
			};

			template <numerical_c A, numerical_c B, std::size_t N>
			struct st_std_common_array<std::array<A, N>, B> {
				using type = std::array<typename st_std_common_array<A, B>::type, N>;
			};

			template <numerical_c A, numerical_c B, std::size_t N>
			struct st_std_common_array<A, std::array<B, N>> {
				using type = std::array<typename st_std_common_array<A, B>::type, N>;
			};

			template <std_array_c A, numerical_c B, std::size_t N>
			struct st_std_common_array<std::array<A, N>, B> {
				using type = std::array<typename st_std_common_array<A, B>::type, N>;
			};

			template <numerical_c A, std_array_c B, std::size_t N>
			struct st_std_common_array<A, std::array<B, N>> {
				using type = std::array<typename st_std_common_array<A, B>::type, N>;
			};

			////////////////////////////////////////////////////////////////////////
			template <numerical_c A, std_array_c B, std::size_t N>
			struct st_std_common_array<std::array<A, N>, std::array<B, N>> {
				using type = std::array<typename st_std_common_array<A, B>::type, N>;
			};

			template <std_array_c A, numerical_c B, std::size_t N>
			struct st_std_common_array<std::array<A, N>, std::array<B, N>> {
				using type = std::array<typename st_std_common_array<A, B>::type, N>;
			};

			//////////////////////////////////////////////////////////////////////////////

			template <numerical_c A, std::size_t M, std_array_c B, std::size_t N>
			struct st_std_common_array<std::array<A, M>, std::array<B, N>> {
				using ele_t = common_signed_t<A, std::tuple_element_t<0, B>>;
				using type = std::array<std::array<ele_t, M>, N>;
			};

			template <std_array_c A, std::size_t M, numerical_c B, std::size_t N>
			struct st_std_common_array<std::array<A, M>, std::array<B, N>> {
				using ele_t = common_signed_t<std::tuple_element_t<0, A>, B>;
				using type = std::array<std::array<ele_t, N>, M>;
			};

		} // namespace hidden
		// end of namespace hidden

		template <typename A, typename B>
		using common_std_array_t =
			typename hidden::st_std_common_array<std::remove_cvref_t<A>,
												 std::remove_cvref_t<B>>::type;

		template <typename A, typename B>
		concept common_std_array_c = !no_type_c<common_std_array_t<A, B>>;

		//////////////////////////////////////////////////////
		template <typename... ArgTypes>
		class exit_workhorse : public std::runtime_error {
		  private:
			std::tuple<ArgTypes...> m_tuple;

		  public:
			exit_workhorse(ArgTypes... args)
				: std::runtime_error {"From workhorse"}
				, m_tuple {std::move(args)...} {}

			void please() {
				throw *this; // throw itself!!
			}

			const auto& tuple() const noexcept {
				return this->m_tuple;
			}

			virtual ~exit_workhorse() {}
		};

		namespace hidden {
			// C++ compiler interprets this function
			template <typename T, T START, T END, T STEP>
			consteval T compute_last_index() {
				if (START != END) {
					T r = (END - START) % STEP;
					T q = (END - START) / STEP;

					if (r == 0)
						return START + (q - 1) * STEP;
					else
						return START + q * STEP;
				} else
					return START;
			}

		} // namespace hidden
		// end of namespace hidden

		template <typename T, T START, T END, T STEP, T Index>
		struct item_index {
			constexpr static auto start = START;
			constexpr static auto value = Index;

			constexpr static auto last = hidden::compute_last_index<T, START, END, STEP>();

			constexpr static auto end = END;
			constexpr static auto step = STEP;
		};

		template <typename T, T START, T END, T STEP, T Index>
		std::ostream& operator<<(std::ostream& os,
								 item_index<T, START, END, STEP, Index> const& item) {
			os << "{ type=" << Stlonic_GetTypeName(T) << " | start(index)=" << item.start
			   << " | value(cur. idx)=" << item.value << " | last(max idx)=" << item.last
			   << " | end(count)=" << item.end << " | step(incr'nt)=" << item.step << " }";
			return os;
		}

		namespace hidden {
			template <auto... Args>
			struct st_create_sequence;

			template <>
			struct st_create_sequence<> {
				using type = std::integer_sequence<long long>;
			};

			template <auto END>
			struct st_create_sequence<END> {
				using no_t = decltype(END);
				using type = make_sequence<no_t, (no_t)0, END, 1>;
			};

			template <auto START, auto END>
			struct st_create_sequence<START, END> {
				using no_t = decltype(START);
				using type = make_sequence < no_t, START,
					  (no_t)END, START<END ? (no_t)1 : (no_t)-1>;
			};

			template <auto START, auto END, auto STEP>
			struct st_create_sequence<START, END, STEP> {
				using no_t = decltype(START);
				using type = make_sequence<no_t, START, (no_t)END, (no_t)STEP>;
			};
		} // namespace hidden
		// end of namespace hidden

		template <auto... Indices>
		requires(sizeof...(Indices) < 4) ||
			requires // constraints expression
		{
			requires sizeof...(Indices) == 2;						  // nested requirements
			requires(std::signed_integral<decltype(Indices)> && ...); // nested requirements
		}
		using create_sequence = typename hidden::st_create_sequence<Indices...>::type;

		////////////////////////////////////////////////////////////////////////////////

		template <typename T, T Row, T Column, T Index>
		struct row_column_value {
			constexpr static T row = Row;
			constexpr static T column = Column;
			constexpr static T value = Index;
			constexpr static T size = Row * Column;
		};

		template <auto Row, auto Column, auto Index>
		using row_column_index = row_column_value<decltype(Row), Row, Column, Index>;

		template <typename T, T Height, T Row, T Column, T Index>
		struct height_row_column_value {
			constexpr static T height = Height;
			constexpr static T row = Row;
			constexpr static T column = Column;
			constexpr static T value = Index;
			constexpr static T size = Height * Row * Column;
		};

		template <auto Height, auto Row, auto Column, auto Index>
		using height_row_column_index =
			height_row_column_value<decltype(Height), Height, Row, Column, Index>;

		namespace hidden {
			template <typename T>
			struct st_row_column_value : std::false_type {};

			template <typename T, T Row, T Column, T Index>
			struct st_row_column_value<row_column_value<T, Row, Column, Index>> : std::true_type {};

			template <typename T>
			struct st_height_row_column_value : std::false_type {};

			template <typename T, T Height, T Row, T Column, T Index>
			struct st_height_row_column_value<
				height_row_column_value<T, Height, Row, Column, Index>> : std::true_type {};
		} // namespace hidden

		template <typename T>
		concept row_column_value_c = hidden::st_row_column_value<T>::value;

		template <typename T>
		concept height_row_column_value_c = hidden::st_height_row_column_value<T>::value;

		template <typename T, T Row, T Column, T Index>
		std::ostream& operator<<(std::ostream& os,
								 row_column_value<T, Row, Column, Index> const& idx) {
			os << "< " << Row << ", " << Column << ", " << Index << ", " << idx.size << " >";
			return os;
		}

		template <typename T, T Height, T Row, T Column, T Index>
		std::ostream&
			operator<<(std::ostream& os,
					   height_row_column_value<T, Height, Row, Column, Index> const& idx) {
			os << " < " << Height << ", " << Row << ", " << Column << ", " << Index << ", "
			   << idx.size << " > ";
			return os;
		}

		template <std::size_t... Ints, typename FuncType>
		auto for_tuple(FuncType&& f, std::index_sequence<Ints...>) {
			return std::tuple {f(indexer_t<Ints> {})...};
		}

		template <std::size_t... Ints, typename FuncType>
		auto for_tuple(std::index_sequence<Ints...>, FuncType&& f) {
			return std::tuple {f(indexer_t<Ints> {})...};
		}

		template <std::size_t N, typename FuncType>
		auto for_tuple(FuncType&& f) {
			return for_tuple(f, std::make_index_sequence<N> {});
		}

		template <std::size_t... Ints, typename FuncType>
		auto for_array(FuncType&& f, std::index_sequence<Ints...>) {
			return std::array {f(indexer_t<Ints> {})...};
		}

		template <std::size_t... Ints, typename FuncType>
		auto for_array(std::index_sequence<Ints...>, FuncType&& f) {
			return std::array {f(indexer_t<Ints> {})...};
		}

		template <std::size_t N, typename FuncType>
		auto for_array(FuncType&& f) {
			return for_array(f, std::make_index_sequence<N> {});
		}

		template <std::size_t... Ints, typename FuncType>
		auto for_vector(FuncType&& f, std::index_sequence<Ints...>) {
			return std::vector {f(indexer_t<Ints> {})...};
		}

		template <std::size_t... Ints, typename FuncType>
		auto for_vector(std::index_sequence<Ints...>, FuncType&& f) {
			return std::vector {f(indexer_t<Ints> {})...};
		}

		template <std::size_t N, typename FuncType>
		auto for_vector(FuncType&& f) {
			return for_vector(f, std::make_index_sequence<N> {});
		}

		namespace hidden {
			template <typename T, T START, T END, T STEP, typename WorkType, T... Indices,
					  typename... ArgTypes>
			void for_workhorse(WorkType&& work, std::integer_sequence<T, Indices...>,
							   ArgTypes&&... args) requires requires {
				work(item_index<T, START, END, STEP, START> {}, std::forward<ArgTypes>(args)...);
			}
			{
				(...,
				 (void)work(item_index<T, START, END, STEP, Indices> {},
							std::forward<ArgTypes>(args)...));
			}

			template <typename T, T START, T END, T STEP, typename ContainerType, typename WorkType,
					  T... Indices, typename... ArgTypes>
			void for_workhorse(ContainerType&& container, WorkType&& work,
							   std::integer_sequence<T, Indices...>,
							   ArgTypes&&... args) requires requires {
				work(item_index<T, START, END, STEP, START> {},
					 std::get<START>(std::forward<ContainerType>(container)),
					 std::forward<ArgTypes>(args)...);
			}
			{
				(...,
				 (void)work(item_index<T, START, END, STEP, Indices> {},
							std::get<Indices>(std::forward<ContainerType>(container)),
							std::forward<ArgTypes>(args)...));
			}

			template <typename T, T START, T END, T STEP, typename ContainerType, typename WorkType,
					  T... Indices, typename... ArgTypes>
			void for_workhorse(ContainerType&& container, WorkType&& work,
							   std::integer_sequence<T, Indices...>,
							   ArgTypes&&... args) requires requires {
				work(std::get<0>(std::forward<ContainerType>(container)),
					 std::forward<ArgTypes>(args)...);
			}
			{
				(...,
				 (void)work(std::get<Indices>(std::forward<ContainerType>(container)),
							std::forward<ArgTypes>(args)...));
			}

			///////////////////////////////////////////////////////

			template <typename T, T START, T END, T STEP, typename WorkType, T... Indices,
					  typename... ArgTypes>
			constexpr decltype(auto) for_stallion(WorkType&& work,
												  std::integer_sequence<T, Indices...>,
												  ArgTypes&&... args) requires requires {
				work(item_index<T, START, END, STEP, START> {}, sequence<Indices...> {},
					 std::forward<ArgTypes>(args)...);
			}
			{
				return work(item_index<T, START, END, STEP, START> {}, sequence<Indices...> {},
							std::forward<ArgTypes>(args)...);
			}

			template <typename T, T START, T END, T STEP, typename WorkType, T... Indices,
					  typename... ArgTypes>
			constexpr decltype(auto) for_stallion(WorkType&& work,
												  std::integer_sequence<T, Indices...>,
												  ArgTypes&&... args) requires requires {
				work(sequence<Indices...> {}, item_index<T, START, END, STEP, START> {},
					 std::forward<ArgTypes>(args)...);
			}
			{
				return work(sequence<Indices...> {}, item_index<T, START, END, STEP, START> {},
							std::forward<ArgTypes>(args)...);
			}

			template <typename T, T START, T END, T STEP, typename WorkType, T... Indices,
					  typename... ArgTypes>
			constexpr decltype(auto) for_stallion(WorkType&& work,
												  std::integer_sequence<T, Indices...>,
												  ArgTypes&&... args) requires requires {
				work(sequence<Indices...> {}, std::forward<ArgTypes>(args)...);
			}
			{ return work(sequence<Indices...> {}, std::forward<ArgTypes>(args)...); }

			template <typename T, T Rows, T Columns>
			constexpr auto generate_row_column_value() {
				return for_stallion<T, T {}, Rows * Columns, T {1}>(
					[]<auto... k>(sequence<k...>) {
						return std::tuple<row_column_value<T, k / Columns, k % Columns, k>...> {};
					},
					std::make_integer_sequence<T, Rows * Columns> {});
			}

			template <typename T, T Heights, T Rows, T Columns>
			constexpr auto generate_height_row_column_value() {
				return for_stallion<T, T {}, Heights * Rows * Columns, T {1}>(
					[]<auto... k>(sequence<k...>) {
						return std::tuple<height_row_column_value<
							T, k / (Rows * Columns), (k % (Rows * Columns)) / Columns,
							(k % (Rows * Columns)) % Columns, k>...> {};
					},
					std::make_integer_sequence<T, Heights * Rows * Columns> {});
			}
		} // namespace hidden
		// end of namespace hidden

		template <typename T, T Rows, T Columns>
		using generate_row_column_value =
			decltype(hidden::generate_row_column_value<T, Rows, Columns>());

		template <auto Rows, auto Columns>
		using create_row_column_value_t =
			decltype(hidden::generate_row_column_value<decltype(Rows), Rows, Columns>());

		template <typename T, T Heights, T Rows, T Columns>
		using generate_height_row_column_value =
			decltype(hidden::generate_height_row_column_value<T, Heights, Rows, Columns>());

		template <auto Heights, auto Rows, auto Columns>
		using create_height_row_column_value_t =
			decltype(generate_height_row_column_value<decltype(Heights), Heights, Rows, Columns>());

		namespace hidden {
			template <typename... Ls, typename... Rs, auto... Li, auto... Ri>
			constexpr auto tuple_append(std::tuple<Ls...> const& A, sequence<Li...>,
										std::tuple<Rs...> const& B, sequence<Ri...>) noexcept {
				if constexpr (all_the_same_flat_c<Ls..., Rs...>)
					return std::array {std::get<Li>(A)..., std::get<Ri>(B)...};
				else
					return std::tuple {std::get<Li>(A)..., std::get<Ri>(B)...};
			}

			template <typename... Ls, typename R, auto... Li, std::size_t N, auto... Ri>
			constexpr auto tuple_append(std::tuple<Ls...> const& A, sequence<Li...>,
										std::array<R, N> const& B, sequence<Ri...>) noexcept {
				if constexpr (all_the_same_flat_c<Ls..., R>)
					return std::array {std::get<Li>(A)..., std::get<Ri>(B)...};
				else
					return std::tuple {std::get<Li>(A)..., std::get<Ri>(B)...};
			}

			template <typename L, std::size_t N, typename... Rs, auto... Li, auto... Ri>
			constexpr auto tuple_append(std::array<L, N> const& A, sequence<Li...>,
										std::tuple<Rs...> const& B, sequence<Ri...>) noexcept {
				if constexpr (all_the_same_flat_c<L, Rs...>)
					return std::array {std::get<Li>(A)..., std::get<Ri>(B)...};
				else
					return std::tuple {std::get<Li>(A)..., std::get<Ri>(B)...};
			}

			template <typename L, std::size_t N1, typename R, std::size_t N2, auto... Li,
					  auto... Ri>
			constexpr auto tuple_append(std::array<L, N1> const& A, sequence<Li...>,
										std::array<R, N2> const& B, sequence<Ri...>) noexcept {
				if constexpr (all_the_same_flat_c<L, R>)
					return std::array {std::get<Li>(A)..., std::get<Ri>(B)...};
				else
					return std::tuple {std::get<Li>(A)..., std::get<Ri>(B)...};
			}
		} // namespace hidden
		// end of namespace hidden

		template <typename... Ls, typename... Rs>
		constexpr auto tuple_append(std::tuple<Ls...> const& A,
									std::tuple<Rs...> const& B) noexcept {
			return hidden::tuple_append(A, create_sequence<sizeof...(Ls)> {}, B,
										create_sequence<sizeof...(Rs)> {});
		}

		template <typename... Ls, typename R, std::size_t N2>
		constexpr auto tuple_append(std::tuple<Ls...> const& A,
									std::array<R, N2> const& B) noexcept {
			return hidden::tuple_append(A, create_sequence<sizeof...(Ls)> {}, B,
										create_sequence<N2> {});
		}

		template <typename L, std::size_t N1, typename... Rs>
		constexpr auto tuple_append(std::array<L, N1> const& A,
									std::tuple<Rs...> const& B) noexcept {
			return hidden::tuple_append(A, create_sequence<N1> {}, B,
										create_sequence<sizeof...(Rs)> {});
		}

		template <typename L, std::size_t N1, typename R, std::size_t N2>
		constexpr auto tuple_append(std::array<L, N1> const& A,
									std::array<R, N2> const& B) noexcept {
			return hidden::tuple_append(A, create_sequence<N1> {}, B, create_sequence<N2> {});
		}

		template <typename... Ls, neither_array_nor_tuple_c... ArgTypes>
		constexpr auto tuple_append(std::tuple<Ls...> const& A, ArgTypes&&... args) noexcept {
			return for_stallion<sizeof...(Ls)>([&]<auto... ii_>(sequence<ii_...>) {
				if constexpr (all_the_same_flat_c<Ls..., ArgTypes...>)
					return std::array {std::get<ii_>(A)..., std::forward<ArgTypes>(args)...};
				else
					return std::tuple {std::get<ii_>(A)..., std::forward<ArgTypes>(args)...};
			});
		}

		template <typename L, std::size_t N, neither_array_nor_tuple_c... ArgTypes>
		constexpr auto tuple_append(std::array<L, N> const& A, ArgTypes&&... args) noexcept {
			return for_stallion<N>([&]<auto... ii_>(sequence<ii_...>) {
				if constexpr (all_the_same_flat_c<L, ArgTypes...>)
					return std::array {std::get<ii_>(A)..., std::forward<ArgTypes>(args)...};
				else
					return std::tuple {std::get<ii_>(A)..., std::forward<ArgTypes>(args)...};
			});
		}

		template <neither_array_nor_tuple_c... Types>
		constexpr auto tuple_append(Types&&... args) noexcept {
			if constexpr (all_the_same_flat_c<Types...>)
				return std::array {std::forward<Types>(args)...};
			else
				return std::tuple {std::forward<Types>(args)...};
		}

		// 1.
		// P. Provide: container, work, [args...]
		// S. Supplied: [index], element, and [args...]
		template <typename ContainerType = std::tuple<>,
				  long long END = std::tuple_size_v<std::remove_cvref_t<ContainerType>>,
				  typename WorkType = std::tuple<>, typename... ArgTypes>
		requires(tuple_flat_c<ContainerType> || std_array_flat_c<ContainerType>) void for_workhorse(
			ContainerType&& container, WorkType&& work, ArgTypes&&... args) requires requires {
			hidden::for_workhorse<long long, 0ll, END, 1ll>(
				std::forward<ContainerType>(container), std::forward<WorkType>(work),
				make_sequence<long long, 0ll, END, 1ll> {}, std::forward<ArgTypes>(args)...);
		}
		{
			hidden::for_workhorse<long long, 0ll, END, 1ll>(
				std::forward<ContainerType>(container), std::forward<WorkType>(work),
				make_sequence<long long, 0ll, END, 1ll> {}, std::forward<ArgTypes>(args)...);
		}

		// 2.
		// P. Provide: Container Type, work, [args...]
		// S. Supplied: indices, [args...]
		template <typename ContainerType = std::tuple<>, typename WorkType = std::tuple<>,
				  long long END = std::tuple_size_v<std::remove_cvref_t<ContainerType>>,
				  typename... ArgTypes>
		requires(
			variant_flat_c<ContainerType> || tuple_flat_c<ContainerType> ||
			std_array_flat_c<ContainerType> || c_array_flat_c<ContainerType> ||
			pair_flat_c<ContainerType>) void for_workhorse(WorkType&& work,
														   ArgTypes&&... args) requires requires {
			hidden::for_workhorse<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work),
				make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}
		{
			hidden::for_workhorse<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work),
				make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}

		// 3.
		// P. Provide: END, work, [args...]
		// S. Supplied: indices, [args...]
		template <int END, typename WorkType, typename... ArgTypes>
		void for_workhorse(WorkType&& work, ArgTypes&&... args) requires requires {
			hidden::for_workhorse<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work),
				make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}
		{
			hidden::for_workhorse<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work),
				make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}

		// 4.
		// P. Provide: START, END, work, [args...]
		// S. Supplied: indices, [args...]
		template <long long START, long long END, typename WorkType, typename... ArgTypes>
		void for_workhorse(WorkType&& work, ArgTypes&&... args) requires requires {
			hidden::for_workhorse < long long, START, END,
				START<END ? 1ll : -1ll>(std::forward<WorkType>(work), make_sequence < long long,
										START, END, START<END ? 1ll : -1ll> {},
										std::forward<ArgTypes>(args)...);
		}
		{
			hidden::for_workhorse < long long, START, END,
				START<END ? 1ll : -1ll>(std::forward<WorkType>(work), make_sequence < long long,
										START, END, START<END ? 1ll : -1ll> {},
										std::forward<ArgTypes>(args)...);
		}

		// 5.
		// P. Provide: START, END, STEP, work, [args...]
		// S. Supplied: indices, [args...]
		template <long long START, long long END, long long STEP, typename WorkType,
				  typename... ArgTypes>
		void for_workhorse(WorkType&& work, ArgTypes&&... args) requires requires {
			hidden::for_workhorse<long long, START, END, STEP>(
				std::forward<WorkType>(work),
				make_sequence<long long, START, END, STEP> {},
				std::forward<ArgTypes>(args)...);
		}
		{
			hidden::for_workhorse<long long, START, END, STEP>(
				std::forward<WorkType>(work),
				make_sequence<long long, START, END, STEP> {},
				std::forward<ArgTypes>(args)...);
		}

		/////////////////////////////////////////////////////////////////////////

		// 1A. stallion
		template <typename ContainerType, typename WorkType = std::tuple<>,
				  long long END = std::tuple_size_v<std::remove_cvref_t<ContainerType>>,
				  typename... ArgTypes>
		requires(variant_flat_c<ContainerType> || tuple_flat_c<ContainerType> ||
				 std_array_flat_c<ContainerType> || c_array_flat_c<ContainerType> ||
				 pair_flat_c<ContainerType>) constexpr decltype(auto)
			for_stallion(WorkType&& work, ArgTypes&&... args) requires requires {
			hidden::for_stallion<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work), make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}
		{
			return hidden::for_stallion<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work), make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}

		// 1B. stallion
		template <typename ContainerType, typename WorkType = std::tuple<>,
				  long long END = std::tuple_size_v<std::remove_cvref_t<ContainerType>>,
				  typename... ArgTypes>
		requires(variant_flat_c<ContainerType> || tuple_flat_c<ContainerType> ||
				 std_array_flat_c<ContainerType> || c_array_flat_c<ContainerType> ||
				 pair_flat_c<ContainerType>) constexpr decltype(auto)
			for_stallion(ContainerType&& container, WorkType&& work,
						 ArgTypes&&... args) requires requires {
			hidden::for_stallion<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work), make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}
		{
			return hidden::for_stallion<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work), make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}

		template <long long END, typename WorkType, typename... ArgTypes>
		constexpr decltype(auto) for_stallion(WorkType&& work,
											  ArgTypes&&... args) requires requires {
			hidden::for_stallion<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work), make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}
		{
			return hidden::for_stallion<long long, 0ll, END, 1ll>(
				std::forward<WorkType>(work), make_sequence<long long, 0ll, END, 1ll> {},
				std::forward<ArgTypes>(args)...);
		}

		template <long long START, long long END, typename WorkType, typename... ArgTypes>
		constexpr decltype(auto) for_stallion(WorkType&& work,
											  ArgTypes&&... args) requires requires {
			hidden::for_stallion < long long, START, END,
				START<END ? 1ll : -1ll>(std::forward<WorkType>(work), make_sequence < long long,
										START, END, START<END ? 1ll : -1ll> {},
										std::forward<ArgTypes>(args)...);
		}
		{
			return hidden::for_stallion < long long, START, END,
				   START < END
					   ? 1ll
					   : -1ll > (std::forward<WorkType>(work), make_sequence < long long, START,
								 END, START<END ? 1ll : -1ll> {}, std::forward<ArgTypes>(args)...);
		}

		// 8.
		// P. Provide: START, END, STEP, work, [args...]
		// S. Supplied: indices, [args...]
		template <long long START, long long END, long long STEP, typename WorkType,
				  typename... ArgTypes>
		constexpr decltype(auto) for_stallion(WorkType&& work,
											  ArgTypes&&... args) requires requires {
			hidden::for_stallion<long long, START, END, STEP>(
				std::forward<WorkType>(work), make_sequence<long long, START, END, STEP> {},
				std::forward<ArgTypes>(args)...);
		}
		{
			return hidden::for_stallion<long long, START, END, STEP>(
				std::forward<WorkType>(work), make_sequence<long long, START, END, STEP> {},
				std::forward<ArgTypes>(args)...);
		}

		template <auto head, auto... tails>
		constexpr auto drop_head(sequence<head, tails...>) {
			return sequence<tails...> {};
		}

		template <auto left, auto... lefts, auto head, auto... tails>
		constexpr auto compute_multipliers(sequence<left, lefts...> result,
										   sequence<head, tails...>) {
			if constexpr (sizeof...(tails) == 0)
				return drop_head(sequence<lefts * head..., head, left> {});
			else
				return compute_multipliers(sequence<left, lefts * head..., head> {},
										   sequence<tails...> {});
		}

		template <auto head, auto... tails>
		constexpr auto get_total(sequence<head, tails...>) {
			if constexpr (sizeof...(tails) == 0)
				return head;
			else
				return head * get_total(sequence<tails...> {});
		}

		template <auto ii, auto head, auto... tails>
		constexpr auto get(sequence<head, tails...>) {
			if constexpr (ii == 0)
				return head;
			else
				return get<ii - 1>(sequence<tails...> {});
		}

		template <auto... ms, auto... rs>
		constexpr auto reverse(sequence<ms...> mm, sequence<rs...>) {
			return sequence<get<rs>(mm)...> {};
		}

		template <auto kk, auto ii = 0, auto... ms, auto head, auto... indices>
		constexpr auto get_index(sequence<head, indices...> index, sequence<ms...> mm) {
			if constexpr (ii < sizeof...(ms)) {
				constexpr auto n = get<ii>(sequence<ms...> {});
				return get_index<kk % n, ii + 1>(sequence<head, indices..., kk / n> {}, mm);
			} else
				return sequence<indices...> {};
		}

		template <typename T, T... args>
		constexpr auto create_tuple_sequence(std::integer_sequence<T, args...> dimensions) {
			constexpr auto multipliers = compute_multipliers(sequence<T {1}> {}, dimensions);

			constexpr auto total = get_total(dimensions);

			return for_stallion<total>([multipliers]<auto... ii>(sequence<ii...>) {
				return std::tuple {get_index<ii>(sequence<1LL> {}, multipliers)...};
			});
		}

		namespace hidden {
			template <typename WorkType, typename... Indices, typename... ArgTypes>
			constexpr decltype(auto) for_stallion_tuple(WorkType&& work,
														std::tuple<Indices...> indices,
														ArgTypes&&... args) requires requires {
				work(indices, std::forward<ArgTypes>(args)...);
			}
			{ return work(indices, std::forward<ArgTypes>(args)...); }
		} // namespace hidden
		// end of namespace hidden

		template <long long... Ns, typename WorkType, typename... ArgTypes>
		constexpr decltype(auto) for_stallion_tuple(WorkType&& work,
													ArgTypes&&... args) requires requires {
			hidden::for_stallion_tuple(std::forward<WorkType>(work),
									   create_tuple_sequence(sequence<Ns...> {}),
									   std::forward<ArgTypes>(args)...);
		}
		{
			return hidden::for_stallion_tuple(std::forward<WorkType>(work),
											  create_tuple_sequence(sequence<Ns...> {}),
											  std::forward<ArgTypes>(args)...);
		}

		namespace array_tuple_hidden {
			template <tuple_flat_c TupleType>
			constexpr decltype(auto) tuple_to_array_recursive(TupleType&& tuple) {
				return for_stallion<decltype(tuple)>([&tuple]<auto... ii>(sequence<ii...>) {
					constexpr bool has_common_type =
						common_type_exists_c<decltype(std::get<ii>(tuple))...>;

					if constexpr (has_common_type) {
						using common_t = std::common_type_t<decltype(std::get<ii>(tuple))...>;

						if constexpr (numerical_c<common_t>) {
							using c_t = make_signed_t<common_t>;

							auto to_array = []<typename Type>(Type&& e) {
								if constexpr (tuple_flat_c<Type>)
									return tuple_to_array_recursive(std::forward<Type>(e));
								else
									return std::forward<Type>(e);
							};

							return std::array {static_cast<c_t>(to_array(std::get<ii>(tuple)))...};
						} else {
							auto to_array = []<typename Type>(Type&& e) {
								if constexpr (tuple_flat_c<Type>)
									return tuple_to_array_recursive(std::forward<Type>(e));
								else
									return std::forward<Type>(e);
							};

							return std::array {to_array(std::get<ii>(tuple))...};
						}
					} else {
						auto to_array = []<typename Type>(Type&& e) {
							if constexpr (tuple_flat_c<Type>)
								return tuple_to_array_recursive(std::forward<Type>(e));
							else
								return std::forward<Type>(e);
						};

						return std::tuple {to_array(std::get<ii>(tuple))...};
					}
				});
			}
			// end of tuple_to_array_recursive()

			template <tuple_flat_c TupleType>
			constexpr decltype(auto) tuple_to_array(TupleType&& tuple) {
				return for_stallion<TupleType>([&tuple]<auto... ii_>(sequence<ii_...>) {
					constexpr bool has_common_type =
						common_type_exists_c<decltype(std::get<ii_>(tuple))...>;

					if constexpr (has_common_type) {
						using common_t = std::common_type_t<decltype(std::get<ii_>(tuple))...>;

						if constexpr (numerical_c<common_t>) {
							using c_t = make_signed_t<common_t>;

							return std::array {static_cast<c_t>(std::get<ii_>(tuple))...};
						} else {
							return std::array {std::get<ii_>(tuple)...};
						}
					} else
						return std::forward<TupleType>(tuple);
				});
			}
		} // namespace array_tuple_hidden
		// end of namespace array_tuple_hidden

		template <tuple_flat_c TupleType>
		constexpr decltype(auto) tuple_to_array(TupleType&& tuple) {
			return array_tuple_hidden::tuple_to_array(std::forward<TupleType>(tuple));
		}

		template <tuple_flat_c TupleType>
		constexpr decltype(auto) tuple_to_array_recursive(TupleType&& tuple) {
			return array_tuple_hidden::tuple_to_array_recursive(std::forward<TupleType>(tuple));
		}
	} // namespace types
	// end of namespace types

} // end of namespace stlonic

#endif // end of file _STLONIC_TYPES_HPP