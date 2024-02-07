cmake_minimum_required(VERSION 3.10)
project(token)

add_library(token)

file(GLOB_RECURSE TOKEN_CPPS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(token PRIVATE ${TOKEN_CPPS})
target_include_directories(token PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(token PUBLIC file operator)