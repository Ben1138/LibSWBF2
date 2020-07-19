cmake_minimum_required(VERSION 3.1)

project(chunks)

#Dummy targets for adding sources to libswbf2 easily.
#Will be used to include lvl and/or msh functionality in build
add_library(chunkMSH INTERFACE)
add_library(chunkLVL INTERFACE)


function(getSources chunk CUR_CHUNK_FILES)
	file(GLOB_RECURSE SOURCE_FILES ${chunk}/*.cpp)
	set(${CUR_CHUNK_FILES} ${SOURCE_FILES} PARENT_SCOPE)
endfunction()

#Below doesn't cause duplicate compiles of CHUNK_FILE sources
file(GLOB CHUNK_FILES *.cpp)

getSources(MSH MSH_FILES)
target_sources(chunkMSH INTERFACE ${MSH_FILES})
target_sources(chunkMSH INTERFACE ${CHUNK_FILES})

getSources(LVL LVL_FILES)
target_sources(chunkLVL INTERFACE ${LVL_FILES})
target_sources(chunkLVL INTERFACE ${CHUNK_FILES})