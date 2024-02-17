# C++20 Requires 3.12, While C++23 Requires 3.20
cmake_minimum_required(VERSION 3.20)
project(AParser)

# Set to C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Include sub-directories
add_subdirectory(ast)
add_subdirectory(file)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(runtime)
add_subdirectory(stringutil)
add_subdirectory(token)
add_subdirectory(operator)
add_subdirectory(testing)

# Test
include(FetchContent)
FetchContent_Declare(
  googletest
  DOWNLOAD_EXTRACT_TIMESTAMP false
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Release Binary
add_executable(AParser "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(AParser PRIVATE token stringutil parser lexer file operator ast runtime)
target_compile_options(AParser PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Find clang-format executable
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)

if(NOT CLANG_FORMAT_EXECUTABLE)
  message(STATUS "clang-format not found.")
else()
  file(GLOB_RECURSE CPP_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
  file(GLOB_RECURSE HPP_FILES ${PROJECT_SOURCE_DIR}/*.hpp)

  # Combine the lists of .cpp and .hpp files
  set(ALL_SOURCE_FILES ${CPP_FILES} ${HPP_FILES})

  # Define a custom target named clang-format
  add_custom_target(
    clang-format
    COMMAND
      ${CLANG_FORMAT_EXECUTABLE} -i -style=google ${ALL_SOURCE_FILES}
    VERBATIM
  )
endif()