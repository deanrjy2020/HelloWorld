# build both
( cd driver && rm -rf build && cmake -S . -B build -G Ninja && cmake --build build ) && ( cd test && rm -rf build && cmake -S . -B build -G Ninja && cmake --build build && ./build/test )


api 用 lib1
lib1 用 lib2
lib2 用 lib3, lib4