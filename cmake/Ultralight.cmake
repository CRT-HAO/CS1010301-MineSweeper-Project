set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(SDK_ROOT "${CMAKE_BINARY_DIR}/SDK/")
set(ULTRALIGHT_INCLUDE_DIR "${SDK_ROOT}/include")
set(ULTRALIGHT_BINARY_DIR "${SDK_ROOT}/bin")
set(ULTRALIGHT_RESOURCES_DIR "${SDK_ROOT}/resources")
set(ULTRALIGHT_INSPECTOR_DIR "${SDK_ROOT}/inspector")

if(UNIX)
    if(APPLE)
        set(PORT UltralightMac)
        set(PLATFORM "mac")
        set(ULTRALIGHT_LIBRARY_DIR "${SDK_ROOT}/bin")
    else()
        set(PORT UltralightLinux)
        set(PLATFORM "linux")
        set(ULTRALIGHT_LIBRARY_DIR "${SDK_ROOT}/bin")
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(PORT UltralightWin)
    set(PLATFORM "win")
    set(ULTRALIGHT_LIBRARY_DIR "${SDK_ROOT}/lib")
else()
    message(FATAL_ERROR "Unknown OS '${CMAKE_SYSTEM_NAME}'")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE "x64")
else()
    set(ARCHITECTURE "x86")
endif()

set(S3_DOMAIN ".sfo2.cdn.digitaloceanspaces.com")

ExternalProject_Add(UltralightSDK
    URL https://ultralight-sdk${S3_DOMAIN}/ultralight-sdk-latest-${PLATFORM}-${ARCHITECTURE}.7z
    SOURCE_DIR "${SDK_ROOT}"
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

include_directories("${ULTRALIGHT_INCLUDE_DIR}")
link_directories("${ULTRALIGHT_LIBRARY_DIR}")
link_libraries(UltralightCore AppCore Ultralight WebCore)