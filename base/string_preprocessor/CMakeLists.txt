cmake_minimum_required(VERSION 2.8.4)
project(string_preprocessor)
include(../common.cmake)

file(GLOB SOURCES "*.cpp")

add_library(string_preprocessor ${SOURCES})
