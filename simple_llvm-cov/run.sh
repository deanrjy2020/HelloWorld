
#sudo apt install llvm

cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++
cmake --build build

#run
./build/test_math
#or
# LLVM_PROFILE_FILE="my_file.profraw" ./build/test_math

#合并 Profile 数据, 生成 .profdata 文件，llvm-cov 会用它生成 report
llvm-profdata merge -sparse default.profraw -o default.profdata

#生成 Coverage Report
# llvm-cov report ./build/test_math -instr-profile=default.profdata
#用这个生成html格式, 更清晰
llvm-cov show ./build/test_math -instr-profile=default.profdata -format=html -o coverage_report