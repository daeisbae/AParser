project(testing)

# add_library(testing)

file(GLOB_RECURSE TESTING_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(test_main ${TESTING_CPP})
target_link_libraries(test_main gtest_main stringutil lexer token operator)
target_compile_options(test_main PRIVATE -Wall -Wextra -Wpedantic -Werror)

include(GoogleTest)
gtest_discover_tests(test_main)