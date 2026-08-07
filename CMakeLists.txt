cmake_minimum_required(VERSION 3.14)
project(memorymanager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the memorymanager library target
add_library(memorymanager STATIC
    RMemoryManager.cpp
    RFixedPool.cpp
)

# Export include directory so consumer targets automatically inherit include paths
target_include_directories(memorymanager
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<INSTALL_INTERFACE:include>
)

# Build standalone test executable if memorymanager is the top-level project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_executable(memorymanager_test main.cpp)
    target_link_libraries(memorymanager_test PRIVATE memorymanager)
endif()
