cmake_minimum_required(VERSION 3.1)

project(chunks)

add_library(chunkMSH INTERFACE)
add_library(chunkLVL INTERFACE)


#set_property(TARGET chunkMSH PROPERTY CXX_STANDARD 20)
#set_property(TARGET chunkLVL PROPERTY CXX_STANDARD_REQUIRED ON)


function(getSources chunk CUR_CHUNK_FILES)
	file(GLOB_RECURSE SOURCE_FILES ${chunk}/*.cpp)
	set(${CUR_CHUNK_FILES} ${SOURCE_FILES} PARENT_SCOPE)
endfunction()


file(GLOB CHUNK_FILES *.cpp)


getSources(MSH MSH_FILES)
message(STATUS "Sources for MSH = ${MSH_FILES}")

target_sources(chunkMSH INTERFACE ${MSH_FILES})
target_sources(chunkMSH INTERFACE ${CHUNK_FILES})
target_compile_definitions(chunkMSH INTERFACE EXCLUDE_LVL)

getSources(LVL LVL_FILES)
message(STATUS "Sources for LVL = ${LVL_FILES}")

target_sources(chunkLVL INTERFACE ${LVL_FILES})
target_sources(chunkLVL INTERFACE ${CHUNK_FILES})
