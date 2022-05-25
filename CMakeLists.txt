# Minimum CMAKE version
cmake_minimum_required (VERSION 3.7)
project (unit_test_coverage LANGUAGES CXX)

# Enable ExternalProject CMake module
include(ExternalProject)

include_directories(include)

# Download and install GoogleTest
if (WIN32)
  # probabli ichange relwithdebinfo
  set(GTEST_LIB ${CMAKE_CURRENT_BINARY_DIR}/gtest/src/gtest-build/lib/RelWithDebInfo/gtest.lib)
  set(GTEST_LIB_MAIN ${CMAKE_CURRENT_BINARY_DIR}/gtest/src/gtest-build/lib/RelWithDebInfo/gtest_main.lib)
else()
  set(GTEST_LIB ${CMAKE_CURRENT_BINARY_DIR}/gtest/src/gtest-build/lib/libgtest.a gcov)
  set(GTEST_LIB_MAIN ${CMAKE_CURRENT_BINARY_DIR}/gtest/src/gtest-build/lib/libgtest_main.a)
endif()
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    BUILD_BYPRODUCTS ${GTEST_LIB} ${GTEST_LIB_MAIN}
    # Disable install step
    INSTALL_COMMAND ""
)
set(PROFILE_TEST_LIBS ${GTEST_LIB} ${GTEST_LIB_MAIN} pthread)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)
include_directories(${source_dir}/googletest/include)

if (UNIX)
  # Find tools for coverage report
  find_program(GCOV_PATH gcov)
  find_program(LCOV_PATH NAMES lcov lcov.bat lcov.exe lcov.perl)
  find_program(GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat)
  if(NOT GCOV_PATH)
    message(FATAL_ERROR "gcov not found!")
  else()
    message(STATUS "gcov found!")
  endif()
  if(NOT LCOV_PATH)
    message(FATAL_ERROR "lcov not found!")
  else()
    message(STATUS "lcov found!")
  endif()
  if(NOT GENHTML_PATH)
    message(FATAL_ERROR "genhtml not found!")
  else()
    message(STATUS "genhtml found!")
  endif()

endif()

enable_testing()

# Set output
set(CMAKE_BIN "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BIN})
if (UNIX)
  set(CMAKE_LIB "${CMAKE_BINARY_DIR}/lib")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIB})
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
  add_compile_options(--coverage -fprofile-arcs -ftest-coverage -fno-inline)
else()
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BIN}")
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BIN}")
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BIN}")
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BIN}")
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BIN}")
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BIN}")
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BIN}")
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BIN}")
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BIN}")
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BIN}")
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BIN}")
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BIN}")
endif()

# Add code
add_subdirectory(src)
add_subdirectory(test)

# Generate coverage
add_custom_target(run_tests
  COMMAND ctest
  COMMAND lcov --rc lcov_branch_coverage=1 --capture --directory ${CMAKE_SOURCE_DIR} --output-file ${CMAKE_BINARY_DIR}/gtest_demo.info --test-name gtest_demo --no-external
  COMMAND genhtml --branch-coverage gtest_demo.info --output-directory ${CMAKE_BINARY_DIR}/coverage_report --title "Code coverage report" --show-details --legend
  COMMAND echo "Coverage report in ${CMAKE_BINARY_DIR}/coverage_report/index.html"
  DEPENDS unit_test
)
