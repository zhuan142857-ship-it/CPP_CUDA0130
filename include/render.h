#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// OpenGL 渲染函数声明
GLFWwindow* initOpenGL(int width, int height);
void renderFrame(float* imageData, int width, int height);
void cleanupOpenGL(GLFWwindow* window);
bool shouldClose(GLFWwindow* window);
