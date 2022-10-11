# STLonic - A Collection of STL Extensions
For more comfort, stability, endurance and less code!

## Table of Contents

- [What is STLonic](#about)
- [What is the goal](#target)
- [Why STLonic](#why)
- [Environment](#environment)
- [Links](#links)
- [Simple examples](#example)
- [License](#license)
- [Hotfix](#Hotfix)

<a id="about"></a>

## What is STLonic 

In my opinion, the STL library at first glance tries to reduce the complexities of C style programming, but after working with this library for a while, you will say to yourself, "I wish I had continued with C style and not got involved in all this complexity". We must admit that the STL library in C++ is far more incomplete and complex than other libraries in other languages ​​(for example, C# System libraries).
In my opinion, one of the reasons that keep developers away from learning C++ and hate this language, is the complexity of the standard library.
The standard committee doesn't think about it, why don't we?
I decided to provide a library containing a variety of extensions to cover the shortcomings of the STL library.
STLonic is a header-only and cross-platform library written in C++20 and can be compiled on Windows, Linux and Mac.

<a id="target"></a>

## What is the goal

The purpose of this project is simply to facilitate the use of the STL library and to focus the programmer on his main concern, not to get involved with Move semantics, references, pointers, lambda, and any complexity that distracts the programmer from his main goal and concern, and ultimately leads to He hates this language.
Now the languages ​​are moving in the direction of better communication with the assembler, bringing more comfort to the programmer, such as Rust or Carbon or Go, which have recently become very popular.
But unfortunately, the standards committee is only thinking of making things more complicated for programmers. Each standard that is published brings a whole new feature that requires a very long time to learn and how to use all of them and makes this language more complicated than before.

<a id="why"></a>

## Why STLonic

Learning modern C++ programming is very challenging for both beginners and advanced C++ programmers. They say a new C++ Standard is released every 3 years. Each iteration of the new C++ standard differs from its predecessors. For example, the C++11 standard is completely different from the C++17 standard, and the C++23 standard (due to be released in 2023) will be very different from the C++20 standard.

Keeping up with the new C++ standard is very difficult for most C++ programmers. Through these extensions, I hope to help my audience learn modern C++ programming with less effort.

And also a part of this library depends on OneTBB library (for parallel programming), which is referenced in the source codes.

<a id="environment"></a>

## Environment

C++ programming environment:
- Microsoft Visual Studio ``2017 or higher``
- GNU GCC/G++ version ``8.0 or higher``
- Clang++ version ``8.0 or higher``

<a id="example"></a>

## Simple examples
Suppose you want to print a `std::tuple`. Assuming you are using the C++17 version, you must completely overload `operator<<` or use Fold expressions, which will take a lot of time in both cases.
for example:
```cpp
template<typename Type, unsigned N, unsigned Last>
struct tuple_printer {

    static void print(std::ostream& out, const Type& value) {
        out << std::get<N>(value) << ", ";
        tuple_printer<Type, N + 1, Last>::print(out, value);
    }
};

template<typename Type, unsigned N>
struct tuple_printer<Type, N, N> {

    static void print(std::ostream& out, const Type& value) {
        out << std::get<N>(value);
    }

};

template<typename...Types>
std::ostream& operator<<(std::ostream& out, const std::tuple<Types...>& value) {
    out << "(";
    tuple_printer<std::tuple<Types...>, 0, sizeof...(Types) - 1>::print(out, value);
    out << ")";
    return out;
}
```
or with Fold expressions:
```cpp
template<class TupType, size_t... I>
void print(const TupType& _tup, std::index_sequence<I...>)
{
    std::cout << "(");
    (..., (std::cout << (I == 0? "" : ", ") << std::get<I>(_tup)));
    std::cout << ")\n";
}

template<class... T>
void print(const std::tuple<T...>& _tup)
{
    print(_tup, std::make_index_sequence<sizeof...(T)>());
}
```
In both cases, you are faced with a bunch of very long and boring code that will only take your time.

### What will this library help you?

There is no need to write any of the above code, there is no need to call a specific prototype or function.
Just write your code (with any kind of parameter-list) and then print it without loops and without any extra work. Same for `std::array` and `std::vector`.

The example above using the STLonic library:
```cpp

#include "std_extensions.hpp"

int main() {
	std::array<int, 5> m = {1, 2, 3, 4, 5};
	std::vector<int> n = {1, 2, 3, 4, 5};
	std::tuple<int, std::string, bool> foo {10, "Hello, world!", false};
	std::cout << m << std::endl;
	std::cout << n << std::endl;
	std::cout << foo << std::endl;
}
```
Just like that!

You don't even need that much code to convert types (for example, to convert an array to a `std::tuple`):
```cpp
template<typename tuple_t>
constexpr auto tuple_to_array(tuple_t&& tuple)
{
    constexpr auto get_array = [](auto&& ... x){ return std::array{std::forward<decltype(x)>(x) ... }; };
    return std::apply(get_array, std::forward<tuple_t>(tuple));
}
```
The code above is in the condition that you use C++17, if you use the C++11, the situation will be much more complicated.
But in STLonic we have done all this for you in a much more precise way. Again, just write your own code and call only `tuple_to_array` or `array_to_tuple` (for the opposite condition):

```cpp
#include "std_extensions.hpp"
#include "std_array_tuple_operations.hpp"

int main() {
	std::array<int, 5> m = {1, 2, 3, 4, 5};
	std::tuple<double, double, double> tup(1.5, 2.5, 4.5);
	auto arr = tuple_to_array(tup);
	auto tupl = array_to_tuple(m);

	std::cout << arr << std::endl;
	std::cout << tupl << std::endl;
}
```
<a id="links"></a>
## Links

For more information about Developer:

- Contact [Parisa Khaleghi in linkedin](https://www.linkedin.com/in/parisakhaleghi)
- Access to articles [Official website](https://parikhaleghi.ir/)
- Access to CppReference articles [Contributions of cpp reference](https://en.cppreference.com/mwiki/index.php?limit=50&tagfilter=&title=Special%3AContributions&contribs=user&target=Parisakhaleghi&namespace=&year=&month=-1)

<a id="license"></a>

## License

The STLonic library is licensed under the terms of the MIT License. See [LICENSE](https://github.com/PariKhaleghi/STLonic/blob/master/LICENSE.txt) for mo5re information.

<p><br></p>


<details id="Hotfix">
<summary>Hotfix</summary>
<br>
<div align="center">
    <img src="./29-hotfix.png" alt="" height="500" width="500">
</div>
</details>
