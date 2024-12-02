cmake_minimum_required(VERSION 3.14.0)
project(aoc-cpp VERSION 0.1.0 LANGUAGES C CXX)

add_executable(aoc-cpp)
add_subdirectory(src)
set_property(TARGET aoc-cpp PROPERTY CXX_STANDARD 17)

if(MSVC)
  target_compile_options(aoc-cpp PRIVATE /W4 /WX)
else()
  target_compile_options(aoc-cpp PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
