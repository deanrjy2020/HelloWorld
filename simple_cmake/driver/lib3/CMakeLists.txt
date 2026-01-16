add_library(lib3 STATIC
    lib3.cpp
)

# PUBLIC, lib3.h要给caller lib2用
target_include_directories(lib3
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
