cmake_minimum_required(VERSION 3.14)
project(CoverageDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启 coverage flags
option(COVERAGE "Enable coverage reporting" ON)
if(COVERAGE)
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping -O0 -g)
    add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif()

# src
add_library(math_utils STATIC src/math_utils.cpp)

# test
add_executable(test_math tests/test_math.cpp)
target_link_libraries(test_math PRIVATE math_utils)
# 告诉编译器去 src/ 找头文件
target_include_directories(test_math PRIVATE ${PROJECT_SOURCE_DIR}/src)
