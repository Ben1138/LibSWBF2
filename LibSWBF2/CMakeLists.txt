cmake_minimum_required(VERSION 3.1)

project(libswbf2)

option(BUILD_SHARED_LIB "Build static lib" OFF)
option(DEBUG "Debug build" OFF)



#SETTINGS

if (BUILD_SHARED_LIB)
	add_library(swbf2 SHARED)
else ()
	add_library(swbf2 STATIC)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
target_link_options(swbf2 PUBLIC -fPIC)

set_property(TARGET swbf2 PROPERTY CXX_STANDARD 20)
set_property(TARGET swbf2 PROPERTY CXX_STANDARD_REQUIRED ON)

if (DEBUG)
	set(CMAKE_BUILD_TYPE Debug)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()




#SOURCES

include_directories(.)

if(APPLE)
	include_directories(/usr/local/include)
endif()

file(GLOB CORE_FILES *.cpp)
file(GLOB LOGGING_FILES Logging/*.cpp)
file(GLOB TYPES_FILES Types/*.cpp)
file(GLOB WRAPPERS_FILES Wrappers/*.cpp)
file(GLOB DIRECTX_FILES DirectX/*.cpp)


target_sources(swbf2 PUBLIC ${CORE_FILES} 
							${DIRECTX_FILES}
							${WRAPPERS_FILES} 
							${LOGGING_FILES}
							${TYPES_FILES})

target_compile_definitions(swbf2 PUBLIC EXCLUDE_LVL)
add_subdirectory(Chunks)





#LINKING

if (APPLE)
	target_link_options(swbf2 PUBLIC -undefined dynamic_lookup)
else()
	target_link_libraries(swbf2 PUBLIC -ldl)
	#target_link_libraries(swbf2 PUBLIC "-Wl,--no-as-needed")
endif()

if (APPLE)
	target_link_directories(swbf2 PUBLIC /usr/local/lib/)
else()
	target_link_directories(swbf2 PUBLIC /usr/lib/x86_64-linux-gnu)
endif()

target_link_libraries(swbf2 PUBLIC chunkMSH)

target_link_libraries(swbf2 PUBLIC fmt)
target_link_libraries(swbf2 PUBLIC glm_static)
target_link_libraries(swbf2 PUBLIC -lpthread)
target_link_libraries(swbf2 PUBLIC m)