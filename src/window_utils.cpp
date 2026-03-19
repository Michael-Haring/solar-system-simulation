/*
* @file     window_utils.cpp
* @author   Michael Haring
* @date     3/18/26
* */

#include <glad/glad.h>
#include <iostream>
#include "window_utils.hpp"


void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}


void show_frames(GLFWwindow *window, double& fpsTime, int& fpsFrames, float deltaTime)
{
    ++fpsFrames;
    fpsTime += deltaTime;
    if (fpsTime >= 0.5)
    {
        double fps = fpsFrames / fpsTime;
        char title[128];
        snprintf(title, sizeof(title), "Gravity Simulation - FPS: %.2f", fps);
        glfwSetWindowTitle(window, title);
        fpsFrames = 0;
        fpsTime = 0.0;

    }
}


GLFWwindow* loadLibsAndWindow(int width, int height, int vsync_status)
{
    if (!glfwInit())
    {
        std::cerr << "glfw unable to initialize\n";
        exit(GLFW_INIT_FAIL);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Milky Way", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cerr << "unable to create glfw window\n";
        exit(GLFW_WINDOW_FAIL);
    }

    glfwMakeContextCurrent(window);
    // V-Sync
    glfwSwapInterval(vsync_status);
    // window resizing callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD \n";
        exit(GLAD_INIT_FAIL);
    }

    glEnable(GL_DEPTH_TEST);
    return window;
}
