cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0079 NEW)


#[[

Buildfile for testing.  Most setup
is done in the libSWBF2 project,
and the relevant includes, options,
and links are automatically added to each test
that links to SWBF2.

]]

project(libSWBF2_TESTS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#SOURCES
add_executable(lghtTest testLights.cpp)
#add_executable(segmentsTest testSegments.cpp)
add_executable(splatmapTest testTerrainSplatMap.cpp)

#LINKING
target_link_libraries(lghtTest PUBLIC SWBF2)
#target_link_libraries(segmentsTest PUBLIC SWBF2)
target_link_libraries(splatmapTest PUBLIC SWBF2)