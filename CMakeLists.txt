cmake_minimum_required(VERSION 3.19)
project(libmath2 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(LIBMATH2_BUILD_SHARED "Build as a shared library" OFF)
option(LIBMATH2_BUILD_TESTS "Build tests" ON)
option(LIBMATH2_GTEST_FETCH "Fetch GoogleTest if not found" ON)

# --- Library ---

file(GLOB LIBMATH2_SOURCES src/*.c)

if(LIBMATH2_BUILD_SHARED)
    add_library(libmath2 SHARED ${LIBMATH2_SOURCES})
    target_compile_definitions(libmath2 PRIVATE LIBMATH2_SHARED LIBMATH2_EXPORTS)
    target_compile_definitions(libmath2 INTERFACE LIBMATH2_SHARED)
else()
    add_library(libmath2 STATIC ${LIBMATH2_SOURCES})
endif()

target_include_directories(libmath2 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# --- Tests ---

if(LIBMATH2_BUILD_TESTS)
    enable_testing()

    find_package(GTest 1.14.0 QUIET)

    if(NOT GTest_FOUND AND LIBMATH2_GTEST_FETCH)
        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.14.0
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    file(GLOB LIBMATH2_TEST_SOURCES tests/*.cpp)

    add_executable(libmath2-tests ${LIBMATH2_TEST_SOURCES})
    target_link_libraries(libmath2-tests PRIVATE libmath2 GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(libmath2-tests)
endif()
