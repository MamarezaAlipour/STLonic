# STLonic: Modern C++ STL Utilities Library

STLonic is a modern, header-only C++ library providing a rich set of utilities and functional-style algorithms for containers, ranges, and strings. It is designed to extend the C++ Standard Library (STL) with expressive, Pythonic, and convenient operations, making everyday coding more productive and enjoyable.

## Features

- **Header-only**: Just include what you need, no linking required.
- **C++17 and later**: Leverages modern C++ features for safety and performance.
- **Functional utilities**: Map, filter, enumerate, zip, chunk, flatten, group_by, and more.
- **Container helpers**: Contains, contains_key, erase_if, unique, reverse, sliding_window, partition, etc.
- **String utilities**: Join, conversion between UTF-8/UTF-16/Windows codepages.
- **Range adaptors**: Pythonic range operations for any STL container.
- **Tested with DocTest**: Ensures reliability and correctness.

## Installation

STLonic is header-only. Simply copy the `STLonic/` directory into your project and include the headers you need:

```cpp
#include "STLonic/container_utils.hpp"
#include "STLonic/range_adaptors.hpp"
// ...and others as needed
```

Requires a C++17 compatible compiler (e.g., GCC 8+, Clang 8+, MSVC 2017+).

## Library Overview

### 1. `container_utils.hpp`

- `contains`, `contains_key`: Check for existence in containers/maps.
- `erase_if`: Remove elements by predicate.
- `to_vector`, `to_set`, `to_unordered_set`, `to_map`, `to_unordered_map`: Convert between container types.
- `for_each`, `all_of`, `any_of`, `none_of`: Functional algorithms.
- `find_or`, `index_of`, `reverse`, `unique`, `min_element`, `max_element`.
- `sliding_window`, `partition`, `group_by`, `take`, `drop`.

### 2. `range_adaptors.hpp`

- `filter`: Select elements by predicate.
- `map`: Transform elements by function.

### 3. `find_index.hpp`

- `find_index`, `find_index_if`: Find index of value or by predicate.
- `find_last_index`: Find last occurrence index.

### 4. `zip_object.hpp`

- `zip`: Iterate over two containers in parallel, yielding pairs.

### 5. `repeat_cycle.hpp`

- `repeat`: Create a vector with repeated values.
- `cycle`: Repeat a container multiple times.

### 6. `value_or.hpp`

- `value_or`: Get value from optional or provide a default.

### 7. `is_one_of.hpp`

- `is_one_of`, `is_one_of_v`: Type trait to check if a type is among a list.

### 8. `flatten.hpp`

- `flatten`: Flatten a container of containers into a single vector.

### 9. `chunk.hpp`

- `chunk`: Split a container into chunks of given size.

### 10. `enumerate.hpp`

- `enumerate`: Iterate with index and value, like Python's `enumerate`.

### 11. `string_utils.hpp`

- `join`: Concatenate elements into a string with a separator.

### 12. `pretty_print.hpp`

- Overloads for pretty-printing containers (e.g., `std::map`).

### 13. `conversion.hpp`

- String encoding conversions: UTF-8, UTF-16, Windows codepage.
- Locale utilities.

### 14. `cartesian_product.hpp`

- `cartesian_product`: Compute the Cartesian product of two containers.

## Usage Examples

```cpp
#include "STLonic/container_utils.hpp"
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto even = stlonic::filter(v, [](int x) { return x % 2 == 0; });
    auto squares = stlonic::map(v, [](int x) { return x * x; });
    for (auto [i, val] : stlonic::enumerate(v)) {
        std::cout << i << ": " << val << std::endl;
    }
}
```

## Testing

STLonic uses [DocTest](https://github.com/onqtam/doctest) for unit testing. To run tests, build and execute the test binary:

```sh
# Example (adjust for your build system)
cmake .
make
./test_stlonic
```

## Contributing

Contributions, bug reports, and feature requests are welcome! Please:

- Fork the repository
- Create a feature branch
- Add tests for new features
- Open a pull request

## License

This project is licensed under the MIT License.

## Author

Geek pww

---

For more details, see the source code and inline documentation in each header.
