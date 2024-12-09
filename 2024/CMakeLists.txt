file(GLOB CPP_FILES "day*.cpp")
file(GLOB CPP_TEST_FILES "test_*.cpp")
file(GLOB H_FILES "*.h")

target_sources(aoc-2024 PRIVATE ${CPP_FILES} main.cpp ${H_FILES} )
target_include_directories(aoc-2024 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(aoc-2024-tests PRIVATE ${CPP_FILES} ${CPP_TEST_FILES} ${H_FILES} )
target_include_directories(aoc-2024-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
