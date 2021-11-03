add_library(foo SHARED foo.cpp ${CMAKE_SOURCE_DIR}/include/unit_test_coverage/foo.h)
target_link_libraries(foo ${PROFILE_TEST_LIBS})
