cmake_minimum_required(VERSION 3.30)
project(Aerial VERSION 0.1.0)

# Set C++ standard to 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif()

if(MSVC)
    add_compile_options(/utf-8)
endif()

# Add subdirectories
add_subdirectory(Aerial)
add_subdirectory(Sandbox)