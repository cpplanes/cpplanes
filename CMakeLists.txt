cmake_minimum_required(VERSION 2.6.0)

# Check existence of the dependencies
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps)
	message( FATAL_ERROR "Please run ./scripts/fetch_deps.sh" )
endif(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps)

# set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(cpplanes)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Include header files
set(EIGEN3_ROOT ${CMAKE_SOURCE_DIR}/deps/eigen)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})


file(GLOB_RECURSE SOURCES src/*.cpp)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
# file(GLOB HEADERS include/*.h)
# install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
