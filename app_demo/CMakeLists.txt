cmake_minimum_required(VERSION 3.14)

# 设置项目名称和版本
project(app_demo VERSION 1.0)

# 设置CMake日志等级
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MESSAGE_LOG_LEVEL "VERBOSE")
set(QWINDOWKIT_BUILD_EXAMPLES OFF CACHE BOOL "")
set(QWINDOWKIT_BUILD_STATIC ON CACHE BOOL "")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# 包含Qt模块 ui界面资源处理
set(CMAKE_AUTOMOC ON) # 自动处理moc
set(CMAKE_AUTORCC ON) # 自动处理资源文件
set(CMAKE_AUTOUIC ON) # 自动处理UI文件
# set(CMAKE_PREFIX_PATH "D:/Qt/6.9.1/msvc2022_64")
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

# 对于 Ninja 生成器，可以添加特定设置
if(CMAKE_GENERATOR STREQUAL "Ninja")
    # 设置 Ninja 特定选项
    set(CMAKE_NINJA_FORCE_RESPONSE_FILE 1 CACHE BOOL "Force Ninja to use response files")
endif()

# 设置C++标准为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    excelwriter.cpp
    app_demo.cpp
    main.cpp
    xmindparser.cpp
)
set(HEADERS
    app_demo.h
    excelwriter.h
    stdafx.h
    testcase.h
    xmindparser.h
)

# 查找Qt6安装位置
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Xml)
add_subdirectory(QXlsx)
# 定义可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
# 设置子系统为 Windows，不设置会显示控制台
set_target_properties(${PROJECT_NAME} PROPERTIES 
    WIN32_EXECUTABLE TRUE
)
# 添加源文件目录
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Xml)
target_link_libraries(${PROJECT_NAME} PRIVATE QXlsx::QXlsx)


# 如果有资源文件（如图标、图片等），可以添加如下：
# qt_add_resources(${PROJECT_NAME} "resources.qrc")

# 输出构建信息
message(STATUS "Project ${PROJECT_NAME} configured successfully.")