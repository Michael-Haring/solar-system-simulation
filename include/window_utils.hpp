/*
* @file     window_utils.hpp
* @author   Michael Haring
* @date     3/18/26
*
* Classless functions for main.cpp. Functions created and moved here for modularity.
* */

#pragma once
#include <GLFW/glfw3.h>

constexpr int GLFW_INIT_FAIL = 2;
constexpr int GLAD_INIT_FAIL = 3;
constexpr int GLFW_WINDOW_FAIL = 4;

/*
   callback method for resizing window. glfw handles the rest
   with their glfwPollEvents().
   @param     *window : not needed for me, required by glfw
                width : width of window
                height : height of window
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

/*
*   Calculates framerate for performance approximations
*   @param      *window:      window showing frames on
*               fpsTime:      used to calculate fps
*               fpsFrames:    used to calculate fps
*               deltaTime:    used to calculate fps
* */
void show_frames(GLFWwindow *window, double& fpsTime, int& fpsFrames, float deltaTime);

/*
*   Loads libraries and creates window. Originally made just to remove bloat
*   from main.cpp
*   @param      width:      width of screen
*               height:     height of screen
*               vsync_status:   VSYNC_ON and VSYNC_OFF defined in main.cpp
* */
GLFWwindow* loadLibsAndWindow(int width, int height, int vsync_status);
