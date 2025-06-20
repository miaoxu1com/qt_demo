cmake_minimum_required(VERSION 3.16)
project(demo1 LANGUAGES CXX)
# 设置CMake日志等级
set(CMAKE_MESSAGE_LOG_LEVEL "VERBOSE")
set(QWINDOWKIT_BUILD_EXAMPLES OFF CACHE BOOL "")
set(QWINDOWKIT_BUILD_STATIC ON CACHE BOOL "")
# 启用 CCache 加速编译
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
    # 设置 C 和 C++ 编译器使用 ccache
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
    message(WARNING "CCache not found, compilation will not be cached")
endif()

# 设置默认构建类型为 Debug（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
    # 可选的构建类型：Debug, Release, RelWithDebInfo, MinSizeRel
endif()

# 设置 Release 模式的编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release build detected, enabling optimizations")
    
    # 添加 -O3 优化标志
    # 注意：对于 MSVC 编译器，优化标志不同
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-O3)
    elseif(MSVC)
        add_compile_options(/O2)  # MSVC 的 /O2 近似于 GCC 的 -O3
    endif()
    
    # 其他 Release 模式下的优化选项
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(
            -march=native  # 启用特定 CPU 架构优化
            -flto         # 链接时优化
        )
    endif()
endif()

# 设置 Debug 模式的编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build detected, enabling debug symbols")
    
    # 添加调试符号和禁用优化
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-g -O0)
    elseif(MSVC)
        add_compile_options(/Zi /Od)
    endif()
endif()

# 启用并行构建
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N} CACHE STRING "Number of parallel jobs to run")
    message(STATUS "Setting parallel build level to ${N} (auto-detected)")
else()
    set(CMAKE_BUILD_PARALLEL_LEVEL 4 CACHE STRING "Number of parallel jobs to run")
    message(STATUS "Setting parallel build level to 4 (default)")
endif()

# Qt 相关设置
include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    demo1.ui
    demo1.h
    demo1.cpp
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

# 对于 Ninja 生成器，可以添加特定设置
if(CMAKE_GENERATOR STREQUAL "Ninja")
    # 设置 Ninja 特定选项
    set(CMAKE_NINJA_FORCE_RESPONSE_FILE 1 CACHE BOOL "Force Ninja to use response files")
endif()