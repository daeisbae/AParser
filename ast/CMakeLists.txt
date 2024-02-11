project(ast)

add_library(ast)

file(GLOB_RECURSE AST_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(ast PRIVATE ${AST_CPP})
target_include_directories(ast PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(ast PUBLIC token)