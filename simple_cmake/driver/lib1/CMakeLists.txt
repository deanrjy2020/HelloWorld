# 添加子库
add_subdirectory(lib2)

add_library(lib1 STATIC
    src/lib1.cpp
)

target_include_directories(lib1
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# lib1 只用 lib2 (但是lib2 public了lib3, 可用)
# PRIVATE表示lib2里面的函数只是给lib1里面用, 不会给lib1的caller(api)用
target_link_libraries(lib1
    PRIVATE lib2
)
