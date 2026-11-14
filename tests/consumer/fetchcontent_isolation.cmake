if(NOT TEST_SOURCE_DIR OR NOT TEST_BINARY_DIR OR NOT TEST_CUTE_SOURCE OR NOT TEST_GENERATOR)
    message(FATAL_ERROR "Missing FetchContent isolation test arguments")
endif()
file(TO_CMAKE_PATH "${TEST_CUTE_SOURCE}" TEST_CUTE_SOURCE)
set(other_backend "${TEST_SOURCE_DIR}/tests/consumer/fetchcontent_parent/other_backend")

set(generator_args -G "${TEST_GENERATOR}")
if(TEST_GENERATOR_PLATFORM)
    list(APPEND generator_args -A "${TEST_GENERATOR_PLATFORM}")
endif()
if(TEST_GENERATOR_TOOLSET)
    list(APPEND generator_args -T "${TEST_GENERATOR_TOOLSET}")
endif()
if(TEST_C_COMPILER)
    list(APPEND generator_args "-DCMAKE_C_COMPILER=${TEST_C_COMPILER}")
endif()

function(check_configure case_name source_dir legacy_override private_override expected_source)
    set(private_args)
    if(private_override STREQUAL "CLEAR")
        list(APPEND private_args -U FETCHCONTENT_SOURCE_DIR_LM2_CUTE_C2)
    elseif(NOT private_override STREQUAL "INHERIT")
        list(APPEND private_args "-DFETCHCONTENT_SOURCE_DIR_LM2_CUTE_C2=${private_override}")
    endif()
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -S "${source_dir}" -B "${TEST_BINARY_DIR}/${case_name}"
            ${generator_args}
            "-DLM2_BUILD_TESTS=OFF"
            "-DLM2_BUILD_SHARED=${TEST_LM2_SHARED}"
            "-DFETCHCONTENT_FULLY_DISCONNECTED=ON"
            "-DFETCHCONTENT_SOURCE_DIR_CUTE_C2=${legacy_override}"
            ${private_args}
            "-DTEST_SOURCE_DIR=${TEST_SOURCE_DIR}"
            "-DTEST_CUTE_SOURCE=${TEST_CUTE_SOURCE}"
            --trace-expand "--trace-source=${TEST_SOURCE_DIR}/CMakeLists.txt"
        RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE trace)
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "${case_name} configure failed (${result}):\n${output}\n${trace}")
    endif()
    string(FIND "${trace}" "target_include_directories(libmath2 SYSTEM PRIVATE ${expected_source}" found)
    if(found EQUAL -1)
        message(FATAL_ERROR "${case_name} did not select ${expected_source}:\n${trace}")
    endif()
endfunction()

# Direct use keeps the previous offline override; the namespaced override wins
# when both are set. Parent use must ignore the generic declaration and must
# continue honoring an explicitly supplied legacy source override.
check_configure(direct_legacy "${TEST_SOURCE_DIR}" "${TEST_CUTE_SOURCE}" "CLEAR" "${TEST_CUTE_SOURCE}")
# An implicit namespaced cache value must not freeze the legacy override on a
# later configure of the same build directory.
check_configure(direct_legacy "${TEST_SOURCE_DIR}" "${other_backend}" "INHERIT" "${other_backend}")
if(WIN32)
    # The common Windows command-line form contains backslashes. FetchContent
    # must not interpret those characters as CMake string escapes.
    file(TO_NATIVE_PATH "${TEST_CUTE_SOURCE}" native_cute_source)
    check_configure(direct_native_legacy "${TEST_SOURCE_DIR}" "${native_cute_source}" "" "${TEST_CUTE_SOURCE}")
endif()
check_configure(direct_precedence "${TEST_SOURCE_DIR}" "${other_backend}" "${TEST_CUTE_SOURCE}" "${TEST_CUTE_SOURCE}")
check_configure(parent_isolation "${TEST_SOURCE_DIR}/tests/consumer/fetchcontent_parent" "" "${TEST_CUTE_SOURCE}" "${TEST_CUTE_SOURCE}")
check_configure(parent_legacy "${TEST_SOURCE_DIR}/tests/consumer/fetchcontent_parent" "${TEST_CUTE_SOURCE}" "" "${TEST_CUTE_SOURCE}")

# Verify the parent can actually build, link and run a public C consumer, not
# just configure successfully with the expected include directory.
if(NOT TEST_CTEST_COMMAND)
    message(FATAL_ERROR "Missing CTest executable")
endif()
if(NOT TEST_CONFIG)
    set(TEST_CONFIG Debug)
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build "${TEST_BINARY_DIR}/parent_isolation"
                        --config "${TEST_CONFIG}" --target fetch-parent-consumer --parallel 4
    RESULT_VARIABLE build_result OUTPUT_VARIABLE build_output ERROR_VARIABLE build_error)
if(NOT build_result EQUAL 0)
    message(FATAL_ERROR "Parent consumer build failed (${build_result}):\n${build_output}\n${build_error}")
endif()
execute_process(COMMAND "${TEST_CTEST_COMMAND}" --test-dir "${TEST_BINARY_DIR}/parent_isolation"
                        -C "${TEST_CONFIG}" -R "^fetch-parent-consumer$" --output-on-failure --no-tests=error
    RESULT_VARIABLE test_result OUTPUT_VARIABLE test_output ERROR_VARIABLE test_error)
if(NOT test_result EQUAL 0)
    message(FATAL_ERROR "Parent consumer failed (${test_result}):\n${test_output}\n${test_error}")
endif()
