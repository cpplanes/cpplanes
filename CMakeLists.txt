cmake_minimum_required(VERSION 2.6.0)

# set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(cpplanes)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Include header files
# include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB SOURCES src/*.cxx)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
# file(GLOB HEADERS include/*.h)
# install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
