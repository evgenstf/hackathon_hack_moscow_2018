cmake_minimum_required(VERSION 2.8.4)
project()

include(base/common.cmake)
add_subdirectory(base/logger logger)

add_library( "algorithm_manager.cpp")
target_link_libraries(algorithm_manager logger)

add_executable(algorithm_manager_example "example.cpp")
target_link_libraries(algorithm_manager_example algorithm_manager)
set_target_properties(algorithm_manager_example PROPERTIES OUTPUT_NAME algorithm_manager)
