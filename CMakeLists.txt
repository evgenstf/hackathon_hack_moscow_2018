cmake_minimum_required(VERSION 2.8.4)
project(score_calculator)

include(base/common.cmake)
include_directories(.)

add_subdirectory(base/command_parser command_parser)
add_subdirectory(data_provider data_provider)
add_subdirectory(algorithm_manager algorithm_manager)
add_subdirectory(arranger arranger)

add_executable(score_calculator_bin "launcher.cpp")
target_link_libraries(score_calculator_bin logger command_parser data_provider algorithm_manager
  arranger)
set_target_properties(score_calculator_bin PROPERTIES OUTPUT_NAME score_calculator)
