cmake_minimum_required(VERSION 3.15)
project(tp_c_cpp_iz1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(tp_c_cpp_iz1 src/main.c src/matrix.c src/input.c src/non_zero_matrix.c)