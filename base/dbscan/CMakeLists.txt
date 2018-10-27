cmake_minimum_required(VERSION 2.8.4)
project(dbscan)
include(../common.cmake)

file(GLOB SOURCES "*.cpp")

add_library(dbscan ${SOURCES})
