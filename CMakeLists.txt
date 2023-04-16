project(MineSweeper C CXX)

cmake_minimum_required(VERSION 3.18)

set(SRC_DIR "src")
set(CMAKE_DIR "cmake")
set(INCLUDE_DIR "include")

include(${CMAKE_DIR}/GUI.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${INCLUDE_DIR})

add_library(Board STATIC ${SRC_DIR}/core/Board.cpp)

add_library(Console STATIC ${SRC_DIR}/console/Console.cpp)

add_library(GUI STATIC ${SRC_DIR}/gui/GUI.cpp)

add_library(Game STATIC ${SRC_DIR}/game/Game.cpp)
target_link_libraries(Game PRIVATE Board)
target_link_libraries(Game PRIVATE Console)
target_link_libraries(Game PRIVATE GUI)

# add_executable(Minesweeper ${SRC_DIR}/main.cpp)
set(SOURCES ${SRC_DIR}/main.cpp)

add_app("${SOURCES}")

target_link_libraries(${APP_NAME} PRIVATE Game)