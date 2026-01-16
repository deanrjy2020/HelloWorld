cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# lldb debug
set(CMAKE_BUILD_TYPE Debug)

# 1. googletest 放到当前repo的外面, 加进来
add_subdirectory(../../googletest googletest-build)
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

enable_testing()

# 2. 你的测试可执行文件
add_executable(
  hello_test
  hello_test.cc
  hello_mock.cc
)

# 3. 链接 gtest_main
target_link_libraries(
  hello_test
  GTest::gmock
  GTest::gtest_main
)

# 4. 让 CTest 自动发现测试
include(GoogleTest)
gtest_discover_tests(hello_test)