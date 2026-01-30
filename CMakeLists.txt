cmake_minimum_required(VERSION 3.21)

# 首先只启用 C++
project(CudaOpenGLApp CXX)

# 暂时禁用 CUDA，后续单独编译
# enable_language(CUDA)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件（暂时不包含 CUDA）
set(SOURCES
    src/main.cpp
    src/render.cpp
)

# 查找 OpenGL
find_package(OpenGL REQUIRED)

# 查找 vcpkg 安装的库
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

# 创建可执行文件
add_executable(CudaOpenGLApp ${SOURCES})

# 链接库（暂不包含 CUDA）
target_link_libraries(CudaOpenGLApp
    PRIVATE
    opengl32
    glfw
    GLEW::GLEW
)

# 编译选项
if(MSVC)
    target_compile_options(CudaOpenGLApp PRIVATE /W4)
else()
    target_compile_options(CudaOpenGLApp PRIVATE -Wall -Wextra)
endif()

# CUDA 编译选项
set_target_properties(CudaOpenGLApp PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

message(STATUS "CUDA found: ${CUDA_FOUND}")
message(STATUS "CUDA libraries: ${CUDA_LIBRARIES}")
message(STATUS "OpenGL found: ${OPENGL_FOUND}")
message(STATUS "Build directory: ${CMAKE_BINARY_DIR}")
