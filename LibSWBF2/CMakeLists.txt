cmake_minimum_required(VERSION 3.1)

project(libswbf2)



#SETTINGS

add_library(swbf2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set_property(TARGET swbf2 PROPERTY CXX_STANDARD 20)
set_property(TARGET swbf2 PROPERTY CXX_STANDARD_REQUIRED ON)

if (NOT ${CMAKE_BUILD_TYPE} EQUAL "DEBUG")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()




#SOURCES

include_directories(.)
include_directories(DirectX)

if(APPLE)
	include_directories(/usr/local/include)
endif()

#Lazy, should fix
file(GLOB CORE_FILES *.cpp)
file(GLOB LOGGING_FILES Logging/*.cpp)
file(GLOB TYPES_FILES Types/*.cpp)
file(GLOB WRAPPERS_FILES Wrappers/*.cpp)
file(GLOB_RECURSE DIRECTX_FILES DirectX/*.cpp)


target_sources(swbf2 PUBLIC ${CORE_FILES} 
							${DIRECTX_FILES}
							${WRAPPERS_FILES} 
							${LOGGING_FILES}
							${TYPES_FILES})
add_subdirectory(Chunks)



#LINKING

#Redundant things I like to include in case someone has a 
#slightly underconfigured system
if (APPLE)
	target_link_options(swbf2 PUBLIC -undefined dynamic_lookup)
	target_link_directories(swbf2 PUBLIC /usr/local/lib/)
else()
	target_link_libraries(swbf2 PUBLIC -ldl)
	target_link_directories(swbf2 PUBLIC /usr/lib/x86_64-linux-gnu/)
endif()

target_link_libraries(swbf2 PUBLIC chunkMSH chunkLVL fmt glm_static)