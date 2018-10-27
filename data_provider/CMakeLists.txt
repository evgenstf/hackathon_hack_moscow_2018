cmake_minimum_required(VERSION 2.8.4)
project(data_provider)
include(../base/common.cmake)

file(GLOB SOURCES "data_provider.cpp")

add_library(data_provider ${SOURCES})
add_subdirectory(csv_parser csv_parser)

add_executable(data_provider_example "example.cpp")
target_link_libraries(data_provider_example csv_parser data_provider)
set_target_properties(data_provider_example PROPERTIES OUTPUT_NAME data_provider)
