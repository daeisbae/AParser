cmake_minimum_required(VERSION 3.10)
project(AParser)

# Set to C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

# Include sub-directories
add_subdirectory(file)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(stringutil)
add_subdirectory(token)
add_subdirectory(operator)
add_subdirectory(test)

# Test - StringUtil
# add_executable(test_stringutil "${CMAKE_CURRENT_SOURCE_DIR}/test/test_stringutil.cpp")
# target_link_libraries(test_stringutil PRIVATE stringutil)

# Test - Token
# add_executable(test_token "${CMAKE_CURRENT_SOURCE_DIR}/test/test_token.cpp")
# target_link_libraries(test_token PRIVATE token file stringutil operator)

# Release Binary
add_executable(AParser "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(AParser PRIVATE token stringutil parser lexer file operator)