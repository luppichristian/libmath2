cmake_minimum_required(VERSION 3.19)
project(libmath2 VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(LM2_BUILD_SHARED "Build as a shared library" OFF)
option(LM2_BUILD_TESTS "Build tests" ON)
option(LM2_GTEST_FETCH "Fetch GoogleTest if not found" ON)

# --- External Dependencies ---

# Include FetchContent module for external dependencies
include(FetchContent)

# Fetch a private copy of cute_c2 for collision detection. FetchContent names
# are global across a parent build, so using its generic upstream name would
# let an unrelated parent declaration replace the pinned source accidentally.
# Preserve explicit legacy source overrides while giving the namespaced one
# precedence when both are supplied.
if((NOT DEFINED FETCHCONTENT_SOURCE_DIR_LM2_CUTE_C2 OR FETCHCONTENT_SOURCE_DIR_LM2_CUTE_C2 STREQUAL "")
   AND DEFINED FETCHCONTENT_SOURCE_DIR_CUTE_C2 AND NOT FETCHCONTENT_SOURCE_DIR_CUTE_C2 STREQUAL "")
    # Declare the legacy path as a source rather than copying it into the new
    # override cache entry, so later changes to the legacy setting take effect.
    # Convert native Windows separators before FetchContent generates CMake
    # files; otherwise paths such as C:\Users can be parsed as escape sequences.
    file(TO_CMAKE_PATH "${FETCHCONTENT_SOURCE_DIR_CUTE_C2}" _lm2_legacy_cute_source)
    FetchContent_Declare(lm2_cute_c2 SOURCE_DIR "${_lm2_legacy_cute_source}")
else()
    FetchContent_Declare(
        lm2_cute_c2
        GIT_REPOSITORY https://github.com/RandyGaul/cute_headers.git
        GIT_TAG 8abda2c6e354d05fb654a7958252fc3abca1a641
    )
endif()
FetchContent_MakeAvailable(lm2_cute_c2)

# --- Library ---

file(GLOB LM2_SOURCES CONFIGURE_DEPENDS src/*/*.c)

if(LM2_BUILD_SHARED)
    add_library(libmath2 SHARED ${LM2_SOURCES})
    target_compile_definitions(libmath2 PRIVATE LM2_SHARED LM2_EXPORTS)
    target_compile_definitions(libmath2 INTERFACE LM2_SHARED)
    # Export only LM2_API symbols from shared libraries on visibility-aware
    # platforms; private backend symbols must not be interposable by clients.
    set_target_properties(libmath2 PROPERTIES C_VISIBILITY_PRESET hidden)
else()
    add_library(libmath2 STATIC ${LM2_SOURCES})
endif()

# Public headers require C11 as well; propagate the requirement to CMake
# consumers that add this project as a subdirectory.
target_compile_features(libmath2 PUBLIC c_std_11)

target_include_directories(libmath2 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(libmath2 SYSTEM PRIVATE
    ${lm2_cute_c2_SOURCE_DIR}
)

# C consumers need the math library transitively on Unix-like systems.
if(UNIX)
    target_link_libraries(libmath2 PUBLIC m)
endif()

# --- Tests ---

if(LM2_BUILD_TESTS)
    enable_language(CXX)
    enable_testing()

    find_package(GTest 1.14.0 QUIET)

    if(NOT GTest_FOUND AND LM2_GTEST_FETCH)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.14.0
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    file(GLOB_RECURSE LM2_TEST_SOURCES CONFIGURE_DEPENDS tests/**.cpp)

    add_executable(libmath2-tests ${LM2_TEST_SOURCES})
    target_link_libraries(libmath2-tests PRIVATE libmath2 GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(libmath2-tests)

    # Exercise the installed-facing umbrella header and linking from real C and
    # C++ translation units, including the opt-in and opt-out header switches.
    foreach(language IN ITEMS c cpp)
        if(language STREQUAL "c")
            set(consumer_source tests/consumer/consumer.c)
        else()
            set(consumer_source tests/consumer/consumer.cc)
        endif()
        set(configurations default no_extensions unprefixed no_extensions_unprefixed)
        if(language STREQUAL "cpp")
            # Each C++ extension can be disabled independently. Exercise the
            # other extension in each case, with aliases both off and on.
            list(APPEND configurations no_generics no_cpp_operators no_generics_unprefixed no_cpp_operators_unprefixed)
        endif()
        foreach(configuration IN LISTS configurations)
            set(consumer_target libmath2-consumer-${language}-${configuration})
            add_executable(${consumer_target} ${consumer_source})
            target_link_libraries(${consumer_target} PRIVATE libmath2)
            if(language STREQUAL "c")
                set_target_properties(${consumer_target} PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)
            endif()
            if(configuration MATCHES "^no_extensions" OR configuration MATCHES "^no_generics")
                target_compile_definitions(${consumer_target} PRIVATE LM2_NO_GENERICS)
            endif()
            if(configuration MATCHES "^no_extensions" OR configuration MATCHES "^no_cpp_operators")
                target_compile_definitions(${consumer_target} PRIVATE LM2_NO_CPP_OPERATORS)
            endif()
            if(configuration MATCHES "^no_generics")
                target_compile_definitions(${consumer_target} PRIVATE LM2_TEST_EXPECT_NO_GENERICS)
            elseif(configuration MATCHES "^no_cpp_operators")
                target_compile_definitions(${consumer_target} PRIVATE LM2_TEST_EXPECT_NO_OPERATORS)
            endif()
            if(configuration MATCHES "unprefixed$")
                target_compile_definitions(${consumer_target} PRIVATE LM2_ENABLE_UNPREFIXED_NAMES)
            endif()
            add_test(NAME ${consumer_target} COMMAND ${consumer_target})
        endforeach()
    endforeach()

    # A consumer may embed its own cute_c2 implementation. Verify that the
    # static archive links and the shared library cannot be interposed by it.
    add_executable(libmath2-consumer-cute-isolation tests/consumer/cute_isolation.c)
    target_include_directories(libmath2-consumer-cute-isolation PRIVATE ${lm2_cute_c2_SOURCE_DIR})
    target_link_libraries(libmath2-consumer-cute-isolation PRIVATE libmath2)
    add_test(NAME libmath2-consumer-cute-isolation COMMAND libmath2-consumer-cute-isolation)

    # Check FetchContent isolation and explicit local-source overrides without
    # network access, including when this library is consumed as a subproject.
    add_test(NAME libmath2-fetchcontent-isolation
        COMMAND ${CMAKE_COMMAND}
            "-DTEST_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
            "-DTEST_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}/fetchcontent-isolation"
            "-DTEST_CUTE_SOURCE=${lm2_cute_c2_SOURCE_DIR}"
            "-DTEST_GENERATOR=${CMAKE_GENERATOR}"
            "-DTEST_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
            "-DTEST_GENERATOR_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
            "-DTEST_C_COMPILER=${CMAKE_C_COMPILER}"
            "-DTEST_CTEST_COMMAND=${CMAKE_CTEST_COMMAND}"
            "-DTEST_LM2_SHARED=${LM2_BUILD_SHARED}"
            "-DTEST_CONFIG=$<CONFIG>"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/consumer/fetchcontent_isolation.cmake")

    # Compile each public header in isolation, so transitive includes from a
    # different header cannot hide a missing dependency.
    file(GLOB_RECURSE LM2_PUBLIC_HEADERS CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
    foreach(language IN ITEMS c cpp)
        set(header_sources)
        foreach(header IN LISTS LM2_PUBLIC_HEADERS)
            string(REPLACE "/" "_" source_name "${header}")
            set(source "${CMAKE_CURRENT_BINARY_DIR}/header-checks/${language}/${source_name}.${language}")
            # Macro-only headers can otherwise leave an empty translation
            # unit, which strict ISO C rejects even when the header is valid.
            file(GENERATE OUTPUT "${source}" CONTENT "#include <${header}>\ntypedef int lm2_header_isolation_translation_unit;\n")
            list(APPEND header_sources "${source}")
        endforeach()
        add_library(libmath2-headers-${language} OBJECT ${header_sources})
        target_link_libraries(libmath2-headers-${language} PRIVATE libmath2)
        if(language STREQUAL "c")
            set_target_properties(libmath2-headers-${language} PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)
        endif()
    endforeach()

    # LM2_UNSAFE is a library build setting. Build a separate complete copy
    # with the same linkage type so the consumer exercises all implementation
    # files without mixing checked and unchecked definitions in one process.
    if(LM2_BUILD_SHARED)
        add_library(libmath2-unsafe SHARED ${LM2_SOURCES})
        target_compile_definitions(libmath2-unsafe PRIVATE LM2_SHARED LM2_EXPORTS)
        target_compile_definitions(libmath2-unsafe INTERFACE LM2_SHARED)
        set_target_properties(libmath2-unsafe PROPERTIES C_VISIBILITY_PRESET hidden)
    else()
        add_library(libmath2-unsafe STATIC ${LM2_SOURCES})
    endif()
    target_compile_features(libmath2-unsafe PUBLIC c_std_11)
    target_include_directories(libmath2-unsafe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(libmath2-unsafe SYSTEM PRIVATE ${lm2_cute_c2_SOURCE_DIR})
    target_compile_definitions(libmath2-unsafe PRIVATE LM2_UNSAFE)
    if(UNIX)
        target_link_libraries(libmath2-unsafe PUBLIC m)
    endif()
    add_executable(libmath2-consumer-unsafe tests/consumer/unsafe.c)
    target_link_libraries(libmath2-consumer-unsafe PRIVATE libmath2-unsafe)
    add_test(NAME libmath2-consumer-unsafe COMMAND libmath2-consumer-unsafe)
endif()
