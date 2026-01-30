#include <iostream>
#include <cstdlib>
#include "../include/render.h"

const int WIDTH = 800;
const int HEIGHT = 600;

// 临时的 CUDA 计算函数（后续用真实 CUDA 替换）
void cudaComputeKernel(float* data, int width, int height) {
    // 生成简单的渐变图像
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * 3;
            data[idx] = (float)x / width;           // R 通道：水平渐变
            data[idx + 1] = (float)y / height;      // G 通道：竖直渐变
            data[idx + 2] = 0.5f;                   // B 通道：固定值
        }
    }
}

void cleanupCudaResources() {
    // 暂时为空
}

int main()
{
    std::cout << "=== CUDA + OpenGL Image Display ===" << std::endl;
    std::cout << "Initializing OpenGL..." << std::endl;

    // 初始化 OpenGL
    GLFWwindow* window = initOpenGL(WIDTH, HEIGHT);
    if (!window) {
        std::cerr << "Failed to initialize OpenGL window" << std::endl;
        return -1;
    }

    std::cout << "OpenGL initialized successfully" << std::endl;

    // 分配图像数据
    float* imageData = new float[WIDTH * HEIGHT * 3];

    std::cout << "Running rendering loop..." << std::endl;
    std::cout << "Close the window to exit" << std::endl;

    // 主循环
    while (!shouldClose(window)) {
        // 运行 CUDA 计算（暂时用 CPU 代替）
        cudaComputeKernel(imageData, WIDTH, HEIGHT);

        // 渲染帧
        renderFrame(imageData, WIDTH, HEIGHT);
    }

    // 清理
    delete[] imageData;
    cleanupOpenGL(window);
    cleanupCudaResources();

    std::cout << "Program finished successfully" << std::endl;
    return 0;
}
