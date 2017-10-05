cmake_minimum_required (VERSION 3.7 FATAL_ERROR)

project (SessionOpenCL)
# CXX language
enable_language(CXX)

add_executable(sessioncl src/sessioncl.cpp src/log.cpp)

### Configure and set up libraries
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package (Threads)
target_link_libraries(sessioncl ${CMAKE_THREAD_LIBS_INIT})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(sessioncl gtest gtest_main)

# find llvm
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
set(Clang_DIR "${LLVM_DIR}")
message("NEW CMAKE MODULE PATH ${CMAKE_MODULE_PATH}")
message(STATUS "LLVM include directories ${LLVM_INCLUDE_DIRS}")
include_directories(${LLVM_INCLUDE_DIRS})
message(STATUS "LLVM link directories ${LLVM_LIBRARY_DIRS}")
link_directories(${LLVM_LIBRARY_DIRS})
message(STATUS "LLVM definitions ${LLVM_DEFINITIONS}")
add_definitions(${LLVM_DEFINITIONS})

target_link_libraries(sessioncl
  "${LLVM_LIBRARY_DIRS}/libclangFrontend.a"
  "${LLVM_LIBRARY_DIRS}/libclangSerialization.a"
  "${LLVM_LIBRARY_DIRS}/libclangDriver.a"
  "${LLVM_LIBRARY_DIRS}/libclangParse.a"
  "${LLVM_LIBRARY_DIRS}/libclangSema.a"
  "${LLVM_LIBRARY_DIRS}/libclangAnalysis.a"
  "${LLVM_LIBRARY_DIRS}/libclangAST.a"
  "${LLVM_LIBRARY_DIRS}/libclangBasic.a"
  "${LLVM_LIBRARY_DIRS}/libclangEdit.a"
  "${LLVM_LIBRARY_DIRS}/libclangLex.a"
  "${LLVM_LIBRARY_DIRS}/libclangTooling.a"
  "${LLVM_LIBRARY_DIRS}/libLLVM-3.9.1.so"

)

# find Boost
find_package(Boost COMPONENTS system filesystem)
if(${Boost_SYSTEM_FOUND})
if(${Boost_FILESYSTEM_FOUND})
    add_definitions(-DBOOST_FILESYSTEM)
    target_link_libraries(sessioncl "${Boost_SYSTEM_LIBRARY}"
                                    "${Boost_FILESYSTEM_LIBRARY}")
endif()
endif()


### binary
set (CMAKE_CXX_FLAGS "-Wall -pedantic")
# Version
set (sessioncl_VERSION_MAJOR 0)
set (sessioncl_VERSION_MINOR 0)
set (sessioncl_VERSION_PATCH 0)
# Configuration file
configure_file (
  "${PROJECT_SOURCE_DIR}/src/sessioncl.h.in"
  "${PROJECT_BINARY_DIR}/build/sessioncl.h" )
# Include directory for configuration file
include_directories("${PROJECT_BINARY_DIR}/src")
include_directories("${PROJECT_BINARY_DIR}/build")
