cmake_minimum_required(VERSION 3.1)

project(logging)

add_library(logging STATIC)

target_sources(logging PRIVATE Logger.cpp LoggerEntry.cpp)
target_include_directories(logging PUBLIC .)
