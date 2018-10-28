cmake_minimum_required(VERSION 2.8.4)
project(clusterizator_analyzer)

include(base/common.cmake)
include_directories(.)

add_subdirectory(base/command_parser command_parser)
add_subdirectory(base/logger logger)
add_subdirectory(data_provider data_provider)
add_subdirectory(clusterizator_manager clusterizator_manager)
add_subdirectory(arranger arranger)
add_subdirectory(statistics statistics)

add_executable(clusterizator_analyzer_bin "launcher.cpp")
target_link_libraries(clusterizator_analyzer_bin logger command_parser data_provider clusterizator_manager
  arranger statistics boost_system boost_filesystem)
set_target_properties(clusterizator_analyzer_bin PROPERTIES OUTPUT_NAME clusterizator_analyzer)
add_custom_target(create_data_symlink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ../data data)

