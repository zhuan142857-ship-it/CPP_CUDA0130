#pragma once

// CUDA 核心函数声明
void cudaComputeKernel(float* data, int width, int height);
void cleanupCudaResources();
