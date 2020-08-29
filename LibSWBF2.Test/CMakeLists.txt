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


#SOURCES
add_executable(lght_TEST testLights.cpp)
add_executable(segments_TEST testSegments.cpp)


#SETTINGS
set_property(TARGET lght_TEST PROPERTY CXX_STANDARD 20)
set_property(TARGET lght_TEST PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET segments_TEST PROPERTY CXX_STANDARD 20)
set_property(TARGET segments_TEST PROPERTY CXX_STANDARD_REQUIRED ON)

#LINKING
target_link_libraries(lght_TEST PUBLIC SWBF2)
target_link_libraries(segments_TEST PUBLIC SWBF2)