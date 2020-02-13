cmake_minimum_required(VERSION 2.8)

project(synfig-studio)

# Set default build type if not specified
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE) # TODO(ice0): Check with GUI
endif()


# Definitions for build types.
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    # Do not allow function inlining in debug mode.
    add_compile_options(-fno-inline-functions -fno-inline -g -O0 -Wall)
    add_definitions(-D_DEBUG)
    add_definitions(-DSHOW_EXTRA_INFO) # Show extra info in the about dialog
    # TODO(ice0): move to synfig-studio?
    add_definitions(-DETL_VERSION="1.3.12" -DPACKAGE_VERSION="1.5.0" -DVERSION="1.5.0")
    message(STATUS "Debug: On")

elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-O3 -ffast-math -DNDEBUG=1)
endif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

add_subdirectory(ETL)
include_directories(ETL)
include_directories(${PROJECT_BINARY_DIR}/ETL) # to find the generated etl_profile.h
add_subdirectory(synfig-core)

include_directories(synfig-core/src)
add_subdirectory(synfig-studio)