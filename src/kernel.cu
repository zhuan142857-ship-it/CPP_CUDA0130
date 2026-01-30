#include <cuda_runtime.h>
#include <stdio.h>

// 简单的 CUDA 核函数 - 生成渐变图像
__global__ void gradientKernel(float* data, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        int idx = (y * width + x) * 3;
        
        // 生成渐变色
        data[idx] = (float)x / width;           // R 通道：水平渐变
        data[idx + 1] = (float)y / height;      // G 通道：竖直渐变
        data[idx + 2] = 0.5f;                   // B 通道：固定值
    }
}

void cudaComputeKernel(float* data, int width, int height) {
    // 设备内存指针
    float* d_data;
    size_t imageSize = width * height * 3 * sizeof(float);

    // 分配设备内存
    cudaMalloc(&d_data, imageSize);

    // 配置线程块和网格
    dim3 blockSize(16, 16);
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x,
                  (height + blockSize.y - 1) / blockSize.y);

    // 运行核函数
    gradientKernel<<<gridSize, blockSize>>>(d_data, width, height);

    // 复制结果回主机内存
    cudaMemcpy(data, d_data, imageSize, cudaMemcpyDeviceToHost);

    // 释放设备内存
    cudaFree(d_data);
}

void cleanupCudaResources() {
    cudaDeviceReset();
}
