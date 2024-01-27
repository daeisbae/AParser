cmake_minimum_required(VERSION 3.10)
project(Parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR})

# Add executable
add_executable(Parser main.cpp file.cpp lexer/lexer.cpp parser/parser.cpp token/token.cpp token/operator.cpp)