cmake_minimum_required(VERSION 3.5.1)
project(test-code)

set(CMAKE_CXX_STANDARD 14)
add_compile_options("-Wall" "-Werror")

add_subdirectory(opencl)
add_subdirectory(cpp)
