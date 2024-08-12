CreateTrivialExe(
        name "unit_tests"
        path "/unit_tests"
)
target_link_libraries(${unit_tests_exe} PUBLIC gtest gtest_main)
target_link_libraries(${unit_tests_exe} PUBLIC ${library_module})

add_test(${unit_tests_exe} ${unit_tests_exe})
unset (unit_tests_exe)
