cmake_minimum_required(VERSION 3.14.0)
project(aoc-cpp VERSION 0.1.0 LANGUAGES C CXX)

add_library(aoc)
add_executable(aoc-2024)

add_dependencies(aoc-2024 aoc)
target_link_libraries(aoc-2024 aoc)

add_subdirectory(aoc)
add_subdirectory(2024)

set_property(TARGET aoc PROPERTY CXX_STANDARD 20)
set_property(TARGET aoc-2024 PROPERTY CXX_STANDARD 20)

if(MSVC)
  target_compile_options(aoc PRIVATE /W4)
  target_compile_options(aoc-2024 PRIVATE /W4)
else()
  target_compile_options(aoc PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(aoc-2024 PRIVATE -Wall -Wextra -Wpedantic)
endif()
