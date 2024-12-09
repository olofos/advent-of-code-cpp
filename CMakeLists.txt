cmake_minimum_required(VERSION 3.14.0)
project(aoc-cpp VERSION 0.1.0 LANGUAGES C CXX)

add_library(aoc)
add_executable(aoc-2024)
add_executable(aoc-2024-tests)

include(cmake/CPM.cmake)
CPMAddPackage("gh:catchorg/Catch2@3.4.0")

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(aoc-2024-tests)

add_dependencies(aoc-2024 aoc)
target_link_libraries(aoc-2024 aoc)
target_link_libraries(aoc-2024-tests aoc Catch2::Catch2WithMain)

add_subdirectory(aoc)
add_subdirectory(2024)

set_target_properties(aoc-2024-tests aoc-2024 aoc PROPERTIES CXX_STANDARD 20)

if(MSVC)
  add_compile_options(PRIVATE /W4)
else()
  add_compile_options(PRIVATE -Wall -Wextra -Wpedantic)
endif()
