cmake_minimum_required(VERSION 3.22)

project(Sudoku VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_compile_definitions(NCURSES_STATIC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Sudoku ${SOURCES})

target_link_libraries(Sudoku PUBLIC ncurses)
