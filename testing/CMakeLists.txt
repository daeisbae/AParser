cmake_minimum_required(VERSION 3.10)
project(testing)
set(CMAKE_CXX_STANDARD 17)

# add_library(testing)

add_executable(test_stringutil test_stringutil.cpp)
target_link_libraries(test_stringutil gtest_main stringutil)
target_compile_options(test_stringutil PRIVATE -Wall -Wextra -Wpedantic -Werror)

include(GoogleTest)
gtest_discover_tests(test_stringutil)