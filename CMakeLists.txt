cmake_minimum_required (VERSION 3.10)
project (fd_algos)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_FLAGS "-std=c11 -g -O0 -Wall")

include(CTest) # this is for, ctest -T memcheck, to work
add_subdirectory(src)
add_subdirectory(test)
enable_testing()

add_test(test_fd_ht test test_fd_ht)
