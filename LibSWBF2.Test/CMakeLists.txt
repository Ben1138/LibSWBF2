cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0079 NEW)


project(libSWBF2_TESTS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#SOURCES

add_executable(segmentsTest  	  testSegments.cpp)
add_executable(blendmapTest  	  testTerrainBlendMap.cpp)
add_executable(heightmapTest 	  testTerrainHeightMap.cpp)
add_executable(entitiesTest  	  testInstancesEntities.cpp)
add_executable(collisionTest 	  testCollision.cpp)
add_executable(basicContainerTest testContainerBasic.cpp)
add_executable(animBankTest 	  testAnimationBank.cpp)


#LINKING

target_link_libraries(segmentsTest  	  PUBLIC LibSWBF2_Static)
target_link_libraries(blendmapTest  	  PUBLIC LibSWBF2)
target_link_libraries(heightmapTest 	  PUBLIC LibSWBF2)
target_link_libraries(entitiesTest  	  PUBLIC LibSWBF2_Static)
target_link_libraries(collisionTest 	  PUBLIC LibSWBF2)
target_link_libraries(basicContainerTest  PUBLIC LibSWBF2)
target_link_libraries(animBankTest  	  PUBLIC LibSWBF2)
