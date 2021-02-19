cmake_minimum_required(VERSION 3.10)

if(POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
    set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
endif()

if(POLICY CMP0075)
    cmake_policy(SET CMP0075 NEW)
endif()

if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

project(nand2tetris LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard to conform to")
add_subdirectory(projects)