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




project(libSWBF2)



#SETTINGS

add_library(SWBF2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set_property(TARGET SWBF2 PROPERTY CXX_STANDARD 20)
set_property(TARGET SWBF2 PROPERTY CXX_STANDARD_REQUIRED ON)

if (NOT ${CMAKE_BUILD_TYPE} EQUAL "DEBUG")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

target_compile_options(SWBF2 PUBLIC -Wno-attributes)



#SOURCES

target_include_directories(SWBF2 PUBLIC .)
target_include_directories(SWBF2 PUBLIC DirectX)

add_subdirectory(Chunks)

if(APPLE)
	include_directories(/usr/local/include)
endif()

#Lazy, should fix
file(GLOB CORE_FILES *.cpp)
file(GLOB LOGGING_FILES Logging/*.cpp)
file(GLOB TYPES_FILES Types/*.cpp)
file(GLOB WRAPPERS_FILES Wrappers/*.cpp)
file(GLOB_RECURSE DIRECTX_FILES DirectX/*.cpp)

target_sources(SWBF2 PUBLIC ${CORE_FILES} 
							${DIRECTX_FILES}
							${WRAPPERS_FILES} 
							${LOGGING_FILES}
							${TYPES_FILES})


#For XCodeProj generation
#[[
file(GLOB_RECURSE ALL_SOURCES *.cpp)
file(GLOB_RECURSE ALL_HEADERS *.h)
set(PROJECT_FILES "${ALL_SOURCES}")
list(APPEND PROJECT_FILES "${ALL_HEADERS}")

#Need this in order for XCode to index header files,
#doesn't change compilation at all...
]]
target_sources(SWBF2 PUBLIC ${ALL_HEADERS})
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_FILES})





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

target_link_libraries(SWBF2 PUBLIC chunkMSH chunkLVL
								   chunkBNK chunkTERR)

find_library(FMTLIB fmt)
find_library(GLMLIB glm_static)

target_link_libraries(SWBF2 PUBLIC ${FMTLIB} ${GLMLIB})