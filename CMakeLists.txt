if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code directory and call cmake from there")
endif()

cmake_minimum_required(VERSION 2.8)
project(testgles)

add_definitions(-std=c++11)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# SDL2
include_directories(${CMAKE_SOURCE_DIR}/DEPS/SDL2-2.0.2/include)
link_directories(${CMAKE_SOURCE_DIR}/DEPS/SDL2-2.0.2/lib/x86)

# opengl es 2.0 (angle)
include_directories(${CMAKE_SOURCE_DIR}/DEPS/angle-e49d2/include)
link_directories(${CMAKE_SOURCE_DIR}/DEPS/angle-e49d2/lib)

add_executable(emptySDL emptySDL.cc)
target_link_libraries(emptySDL SDL2)
target_link_libraries(emptySDL GLESv2)


# copy lib files to build folder
set(library_FILES
        DEPS/SDL2-2.0.2/lib/x86/SDL2.dll
        DEPS/angle-e49d2/lib/d3dcompiler_46.dll
        DEPS/angle-e49d2/lib/libEGL.dll
        DEPS/angle-e49d2/lib/libGLESv2.dll)
foreach(library_path ${library_FILES})
    get_filename_component(library_name "${library_path}" NAME)
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${library_name}"
        COMMAND cmake -E copy
            "${CMAKE_CURRENT_SOURCE_DIR}/${library_path}"
            "${CMAKE_CURRENT_BINARY_DIR}/${library_name}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${library_path}")
    list(APPEND library_files_dest
        "${CMAKE_CURRENT_BINARY_DIR}/${library_name}")
endforeach()
add_custom_target(CopyLibraryFiles ALL DEPENDS ${library_files_dest} emptySDL)
