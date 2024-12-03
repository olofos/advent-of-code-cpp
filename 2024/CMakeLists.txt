file(GLOB CPP_FILES "*.cpp")
file(GLOB H_FILES "*.h")

target_sources(aoc-2024 PRIVATE ${CPP_FILES} ${H_FILES} )
target_include_directories(aoc-2024 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
