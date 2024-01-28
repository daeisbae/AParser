cmake_minimum_required(VERSION 3.10)
project(file)
set(CMAKE_CXX_STANDARD 17)

add_library(file)

file(GLOB_RECURSE File_CPPS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(file PRIVATE ${File_CPPS})
target_include_directories(file PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(file PUBLIC stringutil)