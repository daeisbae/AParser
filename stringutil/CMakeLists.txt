cmake_minimum_required(VERSION 3.10)
project(stringutil)

add_library(stringutil)

file(GLOB_RECURSE STRINGUTIL_CPPS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(stringutil PRIVATE ${STRINGUTIL_CPPS})
target_include_directories(stringutil PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")