cmake_minimum_required(VERSION 3.1)

project(swbf2)

option(BUILD_SHARED_LIB "Build shared lib" OFF)
option(BUILD_STATIC_LIB "Build static lib" OFF)
option(DEBUG "Debug build" OFF)



#SETTINGS

if (BUILD_STATIC_LIB)
	add_library(libswbf2 STATIC)
else ()
	add_library(libswbf2 SHARED)
endif ()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
target_link_options(libswbf2 PUBLIC -fPIC)

set_property(TARGET libswbf2 PROPERTY CXX_STANDARD 20)
set_property(TARGET libswbf2 PROPERTY CXX_STANDARD_REQUIRED ON)

if (DEBUG)
	set(CMAKE_BUILD_TYPE Debug)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()




#SOURCES

target_include_directories(libswbf2 PUBLIC .)

if(APPLE)
	target_include_directories(libswbf2 PUBLIC /usr/local/include)
endif()

file(GLOB_RECURSE SOURCE_FILES *.cpp)

message(STATUS "Sources found: ${SOURCE_FILES}")


#add_subdirectories(Logging)

target_sources(libswbf2 PUBLIC ${SOURCE_FILES})





#LINKING

if (APPLE)
	target_link_options(libswbf2 PUBLIC -undefined dynamic_lookup)
else()
	target_link_libraries(libswbf2 PUBLIC -ldl)
	target_link_libraries(libswbf2 PUBLIC "-Wl,--no-as-needed")
endif()

if (APPLE)
	target_link_directories(libswbf2 PUBLIC /usr/local/lib/)
else()
	target_link_directories(libswbf2 PUBLIC /usr/lib/x86_64-linux-gnu)
endif()

target_link_libraries(libswbf2 PUBLIC fmt)
target_link_libraries(libswbf2 PUBLIC glm_static)
target_link_libraries(libswbf2 PUBLIC -lpthread)
target_link_libraries(libswbf2 PUBLIC m)
