# Add test cpp file
add_executable(unit_test
  unit_test.cpp
)
add_dependencies(unit_test gtest)

# Link test executable against gtest & gtest_main
target_link_libraries(unit_test foo ${PROFILE_TEST_LIBS} foo)
if (WIN32)
  target_compile_options(unit_test PRIVATE /MT)
endif()

add_test(
    NAME unit_test
    COMMAND unit_test
)
