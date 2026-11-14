cmake_minimum_required(VERSION 3.19)
project(fetchcontent_parent LANGUAGES C)

include(FetchContent)
# This belongs to the parent and deliberately is not libmath2's dependency.
FetchContent_Declare(cute_c2 SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/other_backend")
set(LM2_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory("${TEST_SOURCE_DIR}" libmath2)

get_target_property(include_dirs libmath2 INCLUDE_DIRECTORIES)
list(FIND include_dirs "${TEST_CUTE_SOURCE}" found)
if(found EQUAL -1)
    message(FATAL_ERROR "libmath2 selected the parent's unrelated cute_c2: ${include_dirs}")
endif()

add_executable(fetch-parent-consumer "${TEST_SOURCE_DIR}/tests/consumer/consumer.c")
target_link_libraries(fetch-parent-consumer PRIVATE libmath2)
# Keep the executable next to the DLL on Windows, including multi-config
# generators, without modifying the test process's search path.
set_target_properties(fetch-parent-consumer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libmath2")
enable_testing()
add_test(NAME fetch-parent-consumer COMMAND fetch-parent-consumer)
