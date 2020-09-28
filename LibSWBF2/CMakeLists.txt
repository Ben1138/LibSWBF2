cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0079 NEW)


#[[

This and the Chunks/CMakeLists.txt file are the only two used currently.
Globbing source files is bad practice in general, but the project is small and 
contributors are few, so the use is justified.  Just remember to 'touch' the two
build files if you add new source to trigger a reconfiguration.

Set an environment var "LIBSWBF2DIR" to the directory containing this file.
Be sure to run your builds in a subdir of this one called "build" to make
linking to the other libSWBF2 projects (lvlExplorer, msh2fbx, SWBF2-unity-import)
painless.  

]]



#SETTINGS

add_library(SWBF2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

#Setting a GLOBAL property seems to never work...
set_property(TARGET SWBF2 PROPERTY CXX_STANDARD 20)
set_property(TARGET SWBF2 PROPERTY CXX_STANDARD_REQUIRED ON)

if (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

target_compile_options(SWBF2 PUBLIC -Wno-attributes)



#SOURCES

if(APPLE)
	include_directories(/usr/local/include)
endif()

target_include_directories(SWBF2 PUBLIC .)
target_include_directories(SWBF2 PUBLIC DirectX)

add_subdirectory(Chunks)

#Lazy, should fix
file(GLOB CORE_FILES *.cpp)
file(GLOB LOGGING_FILES Logging/*.cpp)
file(GLOB TYPES_FILES Types/*.cpp)
file(GLOB WRAPPERS_FILES Wrappers/*.cpp)
file(GLOB_RECURSE DIRECTX_FILES DirectX/*.cpp DirectX/*.c)

target_sources(SWBF2 PRIVATE ${CORE_FILES} 
							${DIRECTX_FILES}
							${WRAPPERS_FILES} 
							${LOGGING_FILES}
							${TYPES_FILES})

#For XCodeProj generation

file(GLOB_RECURSE SWBF2_SOURCES *.cpp)
file(GLOB_RECURSE SWBF2_HEADERS *.h)
set(SWBF2_FILES "${SWBF2_SOURCES}")
list(APPEND SWBF2_FILES "${SWBF2_HEADERS}")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SWBF2_FILES})

#Needed for correct XCodeProj generation, ALL_HEADERS
#defined in root lists
target_sources(SWBF2 PUBLIC ${SWBF2_HEADERS})



#LINKING

#Redundant things I like to include in case someone has a 
#slightly underconfigured system

if (APPLE)
	target_link_options(SWBF2 PUBLIC -undefined dynamic_lookup)
	target_link_directories(SWBF2 PUBLIC /usr/local/lib/)
else()
	target_link_libraries(SWBF2 PUBLIC -ldl)
	target_link_directories(SWBF2 PUBLIC /usr/lib/x86_64-linux-gnu/)
endif()

target_sources(SWBF2 PRIVATE ${CHUNKS_SOURCES})

find_library(FMTLIB fmt)
find_library(GLMLIB glm_static)

target_link_libraries(SWBF2 PUBLIC ${FMTLIB} ${GLMLIB} pthread)