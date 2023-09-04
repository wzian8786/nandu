include_directories(${nandu_SOURCE_DIR}/sat/public)

file(GLOB sat_test_files "${nandu_SOURCE_DIR}/test/sat/*.cc")
add_executable(sat_tests ${sat_test_files})
target_link_libraries(sat_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                                sat_lib)

add_test(run_sat_tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sat_tests)
