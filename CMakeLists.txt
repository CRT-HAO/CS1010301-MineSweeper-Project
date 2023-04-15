project(MineSweeper C CXX)

cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR "src")
set(INCLUDE_DIR "include")

add_library(Board STATIC ${SRC_DIR}/core/Board.cpp)
target_include_directories(Board PRIVATE ${INCLUDE_DIR})

add_library(Console STATIC ${SRC_DIR}/console/Console.cpp)
target_include_directories(Console PRIVATE ${INCLUDE_DIR})

add_library(Game STATIC ${SRC_DIR}/game/Game.cpp)
target_include_directories(Game PRIVATE ${INCLUDE_DIR})
target_link_libraries(Game PRIVATE Board)
target_link_libraries(Game PRIVATE Console)

add_executable(Minesweeper ${SRC_DIR}/main.cpp)
target_include_directories(Minesweeper PRIVATE ${INCLUDE_DIR})
target_link_libraries(Minesweeper PRIVATE Game)