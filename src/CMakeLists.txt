add_library(foo SHARED foo.cpp foo.h)
target_link_libraries(foo ${PROFILE_TEST_LIBS})

add_subdirectory(test)
