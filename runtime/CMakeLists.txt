project(runtime)

add_library(runtime)

file(GLOB_RECURSE RUNTIME_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(runtime PRIVATE ${RUNTIME_CPP})
target_include_directories(runtime PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(runtime PUBLIC ast parser)