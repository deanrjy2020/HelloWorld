add_library(lib2 STATIC
    lib2.cpp
)

# PUBLIC, lib2.h要给caller lib1用
target_include_directories(lib2
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# lib2 用 lib3 and lib4
# PUBLIC, lib3还给lib2的caller (lib1)用
target_link_libraries(lib2
    PUBLIC lib3
    PRIVATE lib4
)
