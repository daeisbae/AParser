project(parser)

add_library(parser)

file(GLOB_RECURSE PARSER_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(parser PRIVATE ${PARSER_CPP})
target_include_directories(parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(parser PUBLIC token ast)