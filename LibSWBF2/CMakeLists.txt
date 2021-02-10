cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0079 NEW)


#[[

This and the Chunks/CMakeLists.txt file are the only two used currently.
Globbing source files is bad practice in general, but the project is small and 
contributors are few, so the use is justified.  Just remember to 'touch' the two
build files if you add new source to trigger a reconfiguration.

]]


#SETTINGS

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

if (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

add_library(LibSWBF2 SHARED)
add_library(LibSWBF2_Static STATIC)



######## Compile objects shared by static and shared libs

add_library(LibSWBF2_Objects OBJECT)

target_compile_options(LibSWBF2_Objects PUBLIC -Wno-attributes)
target_include_directories(LibSWBF2_Objects PRIVATE . DirectX)
target_compile_options(LibSWBF2_Objects PUBLIC -Wno-deprecated-volatile)


add_subdirectory(Chunks)

#Lazy, should fix
file(GLOB CORE_FILES *.cpp)
file(GLOB LOGGING_FILES Logging/*.cpp)
file(GLOB TYPES_FILES Types/*.cpp)
file(GLOB WRAPPERS_FILES Wrappers/*.cpp)
file(GLOB_RECURSE DIRECTX_FILES DirectX/*.cpp DirectX/*.c)

target_sources(LibSWBF2_Objects PRIVATE ${CORE_FILES} 
									 ${DIRECTX_FILES}
									 ${WRAPPERS_FILES} 
									 ${LOGGING_FILES}
									 ${TYPES_FILES}
									 ${CHUNKS_SOURCES})




######### For XCodeProj generation

file(GLOB_RECURSE LIBSWBF2_SOURCES *.cpp)
file(GLOB_RECURSE LIBSWBF2_HEADERS *.h)
set(LIBSWBF2_FILES "${LIBSWBF2_SOURCES}")
list(APPEND LIBSWBF2_FILES "${LIBSWBF2_HEADERS}")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LIBSWBF2_FILES})

#Needed for correct XCodeProj generation, ALL_HEADERS
#defined in root lists
target_sources(LibSWBF2 PRIVATE ${LIBSWBF2_HEADERS})

######### End XCodeProj stuff



target_include_directories(
  LibSWBF2
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include/LibSWBF2>)

target_include_directories(
  LibSWBF2_Static
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include/LibSWBF2>)



#LINKING

#Redundant things I like to include in case someone has a 
#slightly underconfigured system

if (APPLE)
	target_include_directories(LibSWBF2 PUBLIC /usr/local/include)
	target_link_options(LibSWBF2 PUBLIC -undefined dynamic_lookup)
	target_link_directories(LibSWBF2 PUBLIC /usr/local/lib/)
	target_include_directories(LibSWBF2_Static PUBLIC /usr/local/include)
	target_link_directories(LibSWBF2_Static PUBLIC /usr/local/lib/)
else()
	target_link_libraries(LibSWBF2 PUBLIC -ldl)
	target_link_directories(LibSWBF2 PUBLIC /usr/lib/x86_64-linux-gnu/)
endif()



target_sources(LibSWBF2 PRIVATE $<TARGET_OBJECTS:LibSWBF2_Objects>)
target_sources(LibSWBF2_Static PRIVATE $<TARGET_OBJECTS:LibSWBF2_Objects>)


find_library(FMTLIB fmt)
find_library(GLMLIB glm_static)


target_link_libraries(LibSWBF2 PUBLIC ${FMTLIB} ${GLMLIB} pthread)
target_link_libraries(LibSWBF2_Static PUBLIC ${FMTLIB} ${GLMLIB} pthread)


install(DIRECTORY . DESTINATION include/LibSWBF2 FILES_MATCHING PATTERN "*.h")
install(TARGETS LibSWBF2 LibSWBF2_Static DESTINATION lib EXPORT LibSWBF2)



include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/LibSWBF2ConfigVersion.cmake"
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)


configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/LibSWBF2Config.cmake.in
  "${PROJECT_BINARY_DIR}/LibSWBF2Config.cmake"
  INSTALL_DESTINATION lib/cmake/LibSWBF2
)

install(EXPORT LibSWBF2
        FILE LibSWBF2.cmake
        NAMESPACE LibSWBF2::
        DESTINATION lib/cmake/LibSWBF2
)

install(FILES "${PROJECT_BINARY_DIR}/LibSWBF2ConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/LibSWBF2Config.cmake"
        DESTINATION lib/cmake/LibSWBF2)

