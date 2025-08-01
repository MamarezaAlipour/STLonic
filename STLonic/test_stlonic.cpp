// STLonic test file: tests all STLonic hpp headers for basic inclusion and usage
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <optional>
#include "container_utils.hpp"
#include "conversion.hpp"
#include "string_utils.hpp"
#include "pretty_print.hpp"
#include "range_adaptors.hpp"
#include "enumerate.hpp"
#include "chunk.hpp"
#include "flatten.hpp"
#include "is_one_of.hpp"
#include "value_or.hpp"
#include "repeat_cycle.hpp"
#include "cartesian_product.hpp"
#include "find_index.hpp"
// Add more includes as needed

int main() {
    // container_utils
    std::vector<int> v = {1,2,3,4,5,2,3};
    std::set<int> s = {1,2,3};
    std::map<int, std::string> m = {{1,"a"},{2,"b"}};
    stlonic::contains(v, 2);
    stlonic::contains<std::vector<int>, int>(v, 2);
    stlonic::contains_key(m, 1);
    stlonic::erase_if(v, [](int x){return x==2;});
    stlonic::to_vector(s);
    stlonic::to_set(v);
    stlonic::to_unordered_set(v);
    stlonic::to_map(std::vector<std::pair<int,int>>{{1,2},{3,4}});
    stlonic::to_unordered_map(std::vector<std::pair<int,int>>{{1,2},{3,4}});
    stlonic::for_each(v, [](int){});
    stlonic::all_of(v, [](int x){return x>0;});
    stlonic::any_of(v, [](int x){return x==3;});
    stlonic::none_of(v, [](int x){return x<0;});
    stlonic::find_or(m, 1, std::string("none"));
    stlonic::index_of(v, 3);
    stlonic::reverse(v);
    stlonic::unique(v);
    stlonic::min_element(v);
    stlonic::max_element(v);
    stlonic::sliding_window(v, 2);
    stlonic::partition(v, [](int x){return x%2==0;});
    stlonic::group_by(v, [](int x){return x%2;});
    stlonic::take(v, 3);
    stlonic::drop(v, 2);

    // conversion
    std::string utf8 = "سلام";
    std::wstring utf16 = stlonic::conversion::utf8_to_utf16(utf8);
    stlonic::conversion::utf16_to_utf8(utf16);

    // string_utils
    stlonic::join(v, ",");

    // range_adaptors
    stlonic::filter(v, [](int x){return x>2;});
    stlonic::map(v, [](int x){return x*2;});

    // enumerate
    for (auto [i, val] : stlonic::enumerate(v)) { (void)i; (void)val; }

    // chunk
    stlonic::chunk(v, 2);

    // flatten
    std::vector<std::vector<int>> vv = {{1,2},{3,4}};
    stlonic::flatten(vv);

    // is_one_of
    static_assert(stlonic::is_one_of<int, float, int, double>::value, "");

    // value_or
    std::optional<int> opt = 5;
    stlonic::value_or(opt, 0);

    // repeat_cycle
    stlonic::repeat(1, 3);
    stlonic::cycle(v, 2);

    // cartesian_product
    stlonic::cartesian_product(v, v);

    // find_index
    stlonic::find_index(v, 3);
    stlonic::find_index_if(v, [](int x){return x==3;});
    stlonic::find_last_index(v, 3);

    std::cout << "All STLonic headers included and basic usage tested." << std::endl;
    return 0;
}
