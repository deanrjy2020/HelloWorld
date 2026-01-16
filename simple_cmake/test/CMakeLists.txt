cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp)

# 假设 driver 已经在 ../driver/build 生成 libdriver.so
set(DRIVER_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../driver/build")

# 添加头文件路径（driver 的 include 路径）
target_include_directories(test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../driver
)

# 链接已编译好的 driver.so
target_link_libraries(test
    PRIVATE ${DRIVER_LIB_PATH}/libdriver.so
)

# 设置 RPATH，运行时能自动找到 driver.so
set_target_properties(test PROPERTIES
    BUILD_RPATH ${DRIVER_LIB_PATH}
)
