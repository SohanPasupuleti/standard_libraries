cmake_minimum_required(VERSION 3.20)
project(main C CXX Fortran)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/dependencies.cmake)
include(cmake/tools/copy_dll.cmake)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE
    sqlite3
    glad
    sdl3
    math_data_structure
    standard_data_structure
    standard_utility
)

if(WIN32)
    copy_target_dll(main sdl3)
endif()