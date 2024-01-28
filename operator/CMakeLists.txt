cmake_minimum_required(VERSION 3.10)
project(operator)
set(CMAKE_CXX_STANDARD 17)

add_library(operator)

file(GLOB_RECURSE OPERATOR_CPPS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(operator PRIVATE ${OPERATOR_CPPS})
target_include_directories(operator PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")