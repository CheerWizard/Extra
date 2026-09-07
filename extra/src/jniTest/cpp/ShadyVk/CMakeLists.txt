cmake_minimum_required(VERSION 3.22.1)
project(ShadyVulkan LANGUAGES C CXX)

# print project info
message("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message("CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
message("CMAKE_SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}")

# configurations
add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Android")
    if(NOT DEFINED ENV{JAVA_HOME})
        message(FATAL_ERROR "Please set JAVA_HOME to your JDK")
    endif()

    set(JAVA_INCLUDE_DIR "$ENV{JAVA_HOME}/include")
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(PLATFORM_DIR "linux")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(PLATFORM_DIR "darwin")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(PLATFORM_DIR "win32")
    else()
        message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
    endif()
    set(JAVA_INCLUDE_DIR_PLATFORM "$ENV{JAVA_HOME}/include/${PLATFORM_DIR}")

    include_directories(${JAVA_INCLUDE_DIR} ${JAVA_INCLUDE_DIR_PLATFORM})
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/desktopMain/resources/jni/windows-${CMAKE_SYSTEM_PROCESSOR})
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/desktopMain/resources/jni/linux-${CMAKE_SYSTEM_PROCESSOR})
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/desktopMain/resources/jni/macos-${CMAKE_SYSTEM_PROCESSOR})
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/desktopMain/resources/jni/ios-${CMAKE_SYSTEM_PROCESSOR})
endif()

include_directories(.)
include_directories(vendor)

include(FetchContent)
FetchContent_Declare(
        volk
        GIT_REPOSITORY https://github.com/zeux/volk.git
        GIT_TAG 1.3.270
)
FetchContent_MakeAvailable(volk)

# include all sources and exclude platform specific sources
file(GLOB_RECURSE src "src/*.cpp" "core/*.cpp")

macro(build_windows)
    target_compile_definitions(volk PUBLIC VK_USE_PLATFORM_WIN32_KHR)
    file(GLOB_RECURSE PLATFORM_SRC jni/*.cpp)
    add_library(${PROJECT_NAME} SHARED ${SRC} ${PLATFORM_SRC})
    target_link_libraries(${PROJECT_NAME} PRIVATE
            volk
    )
endmacro()

macro(build_linux)
    target_compile_definitions(volk PUBLIC VK_USE_PLATFORM_XLIB_KHR)
    file(GLOB_RECURSE PLATFORM_SRC jni/*.cpp)
    add_library(${PROJECT_NAME} SHARED ${SRC} ${PLATFORM_SRC})
    target_link_libraries(${PROJECT_NAME} PRIVATE
            volk
    )
endmacro()

macro(build_macos)
    target_compile_definitions(volk PUBLIC VK_USE_PLATFORM_METAL_EXT)
    file(GLOB_RECURSE PLATFORM_SRC jni/*.cpp)
    add_library(${PROJECT_NAME} SHARED ${SRC} ${PLATFORM_SRC})
    target_link_libraries(${PROJECT_NAME} PRIVATE
            volk
            MoltenVK
    )
endmacro()

macro(build_android)
    add_definitions(-DVK_USE_PLATFORM_ANDROID_KHR=1)
    target_compile_definitions(volk PUBLIC VK_USE_PLATFORM_ANDROID_KHR)
    file(GLOB_RECURSE PLATFORM_SRC jni/*.cpp)
    add_library(${PROJECT_NAME} SHARED ${SRC} ${PLATFORM_SRC})
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-z,max-page-size=16384")
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-z,common-page-size=16384")
    target_link_libraries(${PROJECT_NAME} PRIVATE
            volk
            android
    )
endmacro()

macro(build_ios)
    target_compile_definitions(volk PUBLIC VK_USE_PLATFORM_METAL_EXT)
    add_library(${PROJECT_NAME} SHARED ${SRC} ${PLATFORM_SRC})
    target_link_libraries(${PROJECT_NAME} PRIVATE
            volk
            MoltenVK
    )
endmacro()

# defines for OS
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-DWINDOWS)
    build_windows()
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_definitions(-DLINUX)
    build_linux()
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    add_definitions(-DANDROID)
    build_android()
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_definitions(-DMACOS)
    build_macos()
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    add_definitions(-DIOS)
    build_ios()
endif ()

# optionally enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)