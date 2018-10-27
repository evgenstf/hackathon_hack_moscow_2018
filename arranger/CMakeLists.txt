cmake_minimum_required(VERSION 2.8.4)
project(arranger)

include(../base/common.cmake)
add_subdirectory(../base/logger logger)

add_library(arranger "algorithm_manager.cpp")
target_link_libraries(arranger logger)

add_executable(arranger_example "example.cpp")
target_link_libraries(arranger_example algorithm_manager)
set_target_properties(arranger_example PROPERTIES OUTPUT_NAME algorithm_manager)
