# STLonic: Modern C++ STL Utilities and Type Systems Library

## Project Purpose and Motivation

STLonic is a comprehensive, modern C++17 header-only library that extends the Standard Template Library (STL) with powerful type utilities, functional programming constructs, and convenient container operations. It bridges the gap between low-level C++ features and high-level programming paradigms, offering a rich set of tools for:

- Type-safe operations and transformations
- Functional programming patterns
- Container manipulation and algorithms
- String and encoding utilities
- Safe numeric operations
- Advanced tuple and array operations

STLonic makes C++ development more productive and safer while maintaining the performance characteristics of modern C++.

## Core Features

### 1. Type System and Safety
- **Safe Operations**: Type-safe numeric operations with overflow detection
- **Type Traits**: Advanced type traits and concepts for meta-programming
- **Type Utilities**: 
  - `type_container` for type list manipulation
  - `is_one_of` type trait
  - Common type deduction utilities
  - Safe casting operations
  - Sequence generation utilities

### 2. Container Operations
- **Functional Adaptors**:
  - `map`: Transform container elements
  - `filter`: Select elements by predicate
  - `enumerate`: Python-like enumeration
  - `zip`: Parallel iteration over containers
  - `chunk`: Split containers into chunks
  - `flatten`: Flatten nested containers
  
- **Container Utilities**:
  - `contains`, `contains_key`
  - `erase_if`
  - `to_vector`, `to_set`, `to_unordered_set`, `to_map`
  - `for_each`, `all_of`, `any_of`, `none_of`
  - `sliding_window`, `partition`, `group_by`
  - `take`, `drop`
  - `unique`, `reverse`

### 3. Array and Tuple Operations
- **Array Operations**: 
  - Safe array transformations
  - Multi-dimensional array helpers
  - Array-tuple conversions
  
- **Tuple Utilities**:
  - Tuple manipulation functions
  - Type-safe tuple operations
  - Tuple concatenation

### 4. String and Encoding
- `join`: Concatenate strings with separator
- Rich Unicode support:
  - UTF-8/UTF-16/UTF-32 conversions
  - Windows codepage support
  - Locale utilities

### 5. Numeric Safety
- Safe binary operations (`sbo`)
- Integral overflow detection
- Division by zero protection
- Type-safe numeric casting

### 6. Meta-programming Utilities
- Index sequence utilities
- Compile-time type lists
- Type transformations
- SFINAE-friendly concepts

## Installation

STLonic is header-only. Simply copy the `STLonic/` directory into your project:

```cpp
#include "STLonic/types.hpp"           // Core type utilities
#include "STLonic/container_utils.hpp" // Container operations
#include "STLonic/range_adaptors.hpp" // Functional adaptors
// ...other headers as needed
```

Requirements:
- C++17 compatible compiler (GCC 8+, Clang 8+, MSVC 2017+)
- Optional: DocTest for running tests

## Detailed API Overview

### Type System (`types.hpp`)
```cpp
// Type traits and concepts
concept numerical_c;              // Check for numerical types
concept vector_c;                // Check for vector types
concept tuple_c;                 // Check for tuple types
concept iterator_available_c;    // Check for iterator support

// Safe operations
template<long long DebugMode = 2, typename T = int>
auto sbo(T&& value);            // Safe binary operation

// Type containers and transformations
template<typename... Types>
struct type_container;           // Type list utility

// Sequence utilities
template<auto... Args>
using create_sequence;           // Create index sequences
```

### Container Utilities (`container_utils.hpp`)
```cpp
// Container operations
template<typename Container, typename T>
bool contains(const Container& c, const T& value);

template<typename Container, typename Predicate>
void erase_if(Container& c, Predicate pred);

// Functional algorithms
template<typename Container>
auto reverse(const Container& c);

template<typename Container>
auto unique(const Container& c);
```

### Range Adaptors (`range_adaptors.hpp`)
```cpp
// Functional transformations
template<typename Iterable, typename Predicate>
auto filter(const Iterable& iter, Predicate pred);

template<typename Iterable, typename Func>
auto map(const Iterable& iter, Func f);
```

## Usage Examples

### Safe Numeric Operations
```cpp
using namespace stlonic;
auto result = sbo(42) + sbo(-7);  // Safe addition with overflow check
```

### Container Operations
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};

// Functional operations
auto even = filter(v, [](int x) { return x % 2 == 0; });
auto doubled = map(v, [](int x) { return x * 2; });

// Container utilities
auto chunks = chunk(v, 2);  // {{1,2}, {3,4}, {5}}
auto flat = flatten(std::vector{{1,2}, {3,4}});  // {1,2,3,4}
```

### Type Utilities
```cpp
// Type traits
static_assert(is_one_of_v<int, float, int, double>);

// Type containers
using types = type_container<int, float, double>;
```

### String Operations
```cpp
std::vector<std::string> words = {"Hello", "World"};
auto joined = join(words, ", ");  // "Hello, World"

// UTF conversions
auto utf16 = conversion::utf8_to_utf16(utf8_string);
```

## Advanced Features

### Tuple Operations
```cpp
// Tuple manipulation
auto t1 = std::make_tuple(1, "hello");
auto t2 = std::make_tuple(2.0, 'x');
auto combined = tuple_append(t1, t2);
```

### Multi-dimensional Indexing
```cpp
// Row-column indexing
using indices = create_row_column_value_t<3, 4>;  // 3x4 grid
```

### Safe Type Casting
```cpp
// Safe numeric casting
auto opt_val = numeric_cast<int>(large_unsigned_value);
if (opt_val) {
    // Safe to use value
}
```

## Testing
STLonic uses DocTest for unit testing:
```bash
cmake -B build
cmake --build build
cd build && ctest
```

## Contributing
1. Fork the repository
2. Create a feature branch
3. Add tests for new features
4. Submit a pull request

## License
MIT License

## Author
Mamareza Alipour

---
For detailed API documentation, see the inline documentation in each header file.
