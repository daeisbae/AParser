cmake_minimum_required(VERSION 3.10)
project(lexer)

add_library(lexer)

file(GLOB_RECURSE LEXER_CPPS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(lexer PRIVATE ${LEXER_CPPS})
target_include_directories(lexer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(lexer PUBLIC token stringutil file operator)