cmake_minimum_required(VERSION 3.16)
project(STLonicTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the main test file
add_executable(test_stlonic
    test_stlonic.cpp
)

# If you have other STLonic headers in the same directory, add include path
# (Assuming all headers are in STLonic/)
target_include_directories(test_stlonic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(test_stlonic PRIVATE cxx_std_20)
