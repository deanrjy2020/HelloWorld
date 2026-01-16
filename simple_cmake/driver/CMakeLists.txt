cmake_minimum_required(VERSION 3.17)
project(driver)

#set(CMAKE_CXX_STANDARD 17)

# 生成.so时要加上-fPIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 定义子库, 后面用的时候在link_lib里面加.
# 在add_subdirectory后, 里面的程序才被执行, e.g.里面的变量才能被定义. 如果lib3要用lib1里面的变量, 未定义=空
add_subdirectory(lib1)
add_subdirectory(lib3)
add_subdirectory(lib4)

# 构建共享库 driver.so
add_library(driver SHARED api.cpp)

# 链接内部库, api只用lib1
target_link_libraries(driver
    PRIVATE lib1
)

# 让 test 工程能包含 driver 的头文件（如果有）
# target_include_directories(driver 
#     PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
# )
