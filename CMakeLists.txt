cmake_minimum_required (VERSION 3.7 FATAL_ERROR)

project (SessionOpenCL)
# CXX language
enable_language(CXX)
# binary produced
add_executable(sessioncl src/sessioncl.cpp)
# Version
set (sessioncl_VERSION_MAJOR 0)
set (sessioncl_VERSION_MINOR 0)
set (sessioncl_VERSION_PATCH 0)
# Configuration file
configure_file (
  "${PROJECT_SOURCE_DIR}/src/sessioncl.h.in"
  "${PROJECT_BINARY_DIR}/build/sessioncl.h" )
# Include directory for configuration file
include_directories("${PROJECT_BINARY_DIR}/build")
# CMAKE modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# find libclang
find_package(LibClang REQUIRED)
  # Set compiler flags
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIBCLANG_CXXFLAGS}")
  # Set linker libraries
  target_link_libraries(sessioncl "${LIBCLANG_LIBRARY}")

# find libclang
find_package(Boost COMPONENTS system filesystem)
if(${Boost_SYSTEM_FOUND})
if(${Boost_FILESYSTEM_FOUND})
    add_definitions(-DBOOST_FILESYSTEM)
    target_link_libraries(sessioncl "${Boost_SYSTEM_LIBRARY}"
                                    "${Boost_FILESYSTEM_LIBRARY}")
endif()
endif()
