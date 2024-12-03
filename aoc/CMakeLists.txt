file(GLOB CPP_FILES "*.cpp")
file(GLOB H_FILES "*.h")

target_sources(aoc PRIVATE ${CPP_FILES} PUBLIC ${H_FILES})
target_include_directories(aoc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
