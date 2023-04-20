project(MineSweeper C CXX)

cmake_minimum_required(VERSION 3.18)

set(SRC_DIR "src")
set(CMAKE_DIR "cmake")
set(INCLUDE_DIR "include")
set(APP_NAME ${CMAKE_PROJECT_NAME})

include(${CMAKE_DIR}/Ultralight.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${INCLUDE_DIR})

add_library(BoardFile STATIC ${SRC_DIR}/core/BoardFile.cpp)

add_library(Board STATIC ${SRC_DIR}/core/Board.cpp)
target_link_libraries(Board PRIVATE BoardFile)

link_libraries(Board)

add_library(Console STATIC ${SRC_DIR}/console/Console.cpp)

add_library(GUI STATIC ${SRC_DIR}/gui/GUI.cpp)
target_link_libraries(GUI PRIVATE BoardFile)

add_library(Game STATIC ${SRC_DIR}/game/Game.cpp)
target_link_libraries(Game PRIVATE Console)
target_link_libraries(Game PRIVATE GUI)

if(PORT MATCHES "UltralightLinux")
    SET(CMAKE_SKIP_BUILD_RPATH FALSE)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "$\{ORIGIN\}")
endif()

if(PORT MATCHES "UltralightMac")
    SET(CMAKE_SKIP_BUILD_RPATH FALSE)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "@executable_path/")
endif()

add_executable(${APP_NAME} MACOSX_BUNDLE ${SRC_DIR}/main.cpp)

# add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${SRC_DIR}/main.cpp)
target_link_libraries(${APP_NAME} PRIVATE Game)

if(APPLE)
    # Enable High-DPI on macOS through our custom Info.plist template
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist.in)
endif()

if(MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

# Copy all binaries to target directory
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_BINARY_DIR}" $<TARGET_FILE_DIR:${APP_NAME}>)

# Set the assets path to "/assets" or "/../Resources/assets" on macOS
if(APPLE)
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/assets")
else()
    set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/assets")
endif()

# Copy assets to assets path
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/" "${ASSETS_PATH}")

if(${ENABLE_INSPECTOR})
    # Copy inspector to assets directory
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_INSPECTOR_DIR}" "${ASSETS_PATH}/inspector")
endif()

# Copy resources to assets directory
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_RESOURCES_DIR}" "${ASSETS_PATH}/resources")

add_dependencies(${APP_NAME} UltralightSDK)