cmake_minimum_required(VERSION 2.8.4)
project(arranger)

include(../base/common.cmake)
add_subdirectory(../base/csv_parser csv_parser)

add_library(arranger "arranger.cpp")
target_link_libraries(arranger csv_parser)

add_executable(arranger_example "example.cpp")
target_link_libraries(arranger_example arranger)
set_target_properties(arranger_example PROPERTIES OUTPUT_NAME arranger)
