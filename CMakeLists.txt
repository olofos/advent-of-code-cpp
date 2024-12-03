cmake_minimum_required(VERSION 3.14.0)
project(aoc-cpp VERSION 0.1.0 LANGUAGES C CXX)

add_executable(aoc-cpp)
add_subdirectory(src)
set_property(TARGET aoc-cpp PROPERTY CXX_STANDARD 20)

if(MSVC)
  target_compile_options(aoc-cpp PRIVATE /W4)
else()
  target_compile_options(aoc-cpp PRIVATE -Wall -Wextra -Wpedantic)
endif()
