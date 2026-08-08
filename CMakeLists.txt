cmake_minimum_required(VERSION 3.14)
project(memorymanager VERSION 1.0.0 LANGUAGES CXX)

# Define the memorymanager library target
add_library(memorymanager STATIC
    RMemoryManager.cpp
    RFixedPool.cpp
)
add_library(memorymanager::memorymanager ALIAS memorymanager)

# Enforce C++17 for memorymanager and its consumers
target_compile_features(memorymanager PUBLIC cxx_std_17)

# Enable Position Independent Code (required if linked into shared libraries)
set_target_properties(memorymanager PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Export include directory so consumer targets automatically inherit include paths
target_include_directories(memorymanager
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<INSTALL_INTERFACE:include>
)

# Build standalone test executable only when memorymanager is the top-level project
# if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
#     if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
#         add_executable(memorymanager_test main.cpp)
#         target_link_libraries(memorymanager_test PRIVATE memorymanager)
#     endif()
# endif()