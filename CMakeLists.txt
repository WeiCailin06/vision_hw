cmake_minimum_required(VERSION 3.10)
project(VisionHomework)

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(include)

# 生成可执行文件（把 main.cpp 和 reprojection.cpp 一起编译）
add_executable(vision_hw
    src/main.cpp
    src/reprojection.cpp
)