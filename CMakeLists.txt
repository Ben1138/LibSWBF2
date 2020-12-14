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
add_compile_options(-Wfatal-errors)

project(libSWBF2)

add_compile_options(-Wfatal-errors)


#For XCodeProj generation

file(GLOB_RECURSE ALL_SOURCES *.cpp)
file(GLOB_RECURSE ALL_HEADERS *.h)
set(PROJECT_FILES "${ALL_SOURCES}")
list(APPEND PROJECT_FILES "${ALL_HEADERS}")

if(APPLE)
	include_directories(/usr/local/include)
endif()

add_subdirectory(LibSWBF2)
add_subdirectory(LibSWBF2.Test)




#Need this in order for XCode to index header files,
#doesn't change compilation at all...

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_FILES})