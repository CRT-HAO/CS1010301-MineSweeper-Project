project(MineSweeper C CXX)

cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Board STATIC "src/core/Board.cpp")

add_executable(Minesweeper "src/main.cpp")
target_link_libraries(Minesweeper PRIVATE Board)