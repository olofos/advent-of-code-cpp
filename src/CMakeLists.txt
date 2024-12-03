file(GLOB CPP_FILES "*.cpp")
file(GLOB H_FILES "*.h")

target_sources(aoc-cpp PRIVATE ${CPP_FILES} ${H_FILES})
target_include_directories(aoc-cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
