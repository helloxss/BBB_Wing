# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDES
    ${INCLUDES}
    ${INTERNAL_INCLUDES}
PARENT_SCOPE)
    
# Sources
file(GLOB_RECURSE INTERNAL_SOURCES "*.h" "*.cpp")
set(SOURCES 
    ${SOURCES} 
    ${INTERNAL_SOURCES}
PARENT_SCOPE)

# Libraries
set(LIBRARIES
    ${LIBRARIES}
# ZeroMQ
    zmq
PARENT_SCOPE
)
