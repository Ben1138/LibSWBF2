cmake_minimum_required(VERSION 3.1)


function(getSources chunk CUR_CHUNK_FILES)
	file(GLOB_RECURSE SOURCE_FILES ${chunk}/*.cpp)
	set(${CUR_CHUNK_FILES} ${SOURCE_FILES} PARENT_SCOPE)
endfunction()


#Below doesn't cause duplicate compiles of CHUNK_FILE sources
file(GLOB CHUNK_FILES *.cpp)
getSources(MSH MSH_FILES)
getSources(LVL LVL_FILES)
getSources(BNK BNK_FILES)
getSources(TERR TERR_FILES)

set(CHUNKS_SOURCES_T "${CHUNK_FILES}")
list(APPEND CHUNKS_SOURCES_T "${MSH_FILES}")
list(APPEND CHUNKS_SOURCES_T "${LVL_FILES}")
list(APPEND CHUNKS_SOURCES_T "${BNK_FILES}")
list(APPEND CHUNKS_SOURCES_T "${TERR_FILES}")

set(CHUNKS_SOURCES "${CHUNKS_SOURCES_T}" PARENT_SCOPE)