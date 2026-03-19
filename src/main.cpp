/*
   @file      main.cpp
   @author    Michael Haring
   @data      12/13/25

   This file contains non-class member functions, and main.
   This program is a simulation of our solar system.

   Thank you project for helping me get an internship!
 */

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <csignal>
#include <cstring>

#include "instanced_sphere_renderer.hpp"
#include "simulation.hpp"
#include "space-object.hpp"
#include "camera.hpp"
#include "keyboard.hpp"
#include "window_utils.hpp"

constexpr int SIGNAL_INIT_FAILED = 5;

constexpr int VSYNC_ON = 1;
constexpr int VSYNC_OFF = 0;

volatile std::sig_atomic_t sig_closeWindow = 0;

void handleSignal(int signal) {
    sig_closeWindow = signal;
}

bool registerSignals()
{
    struct sigaction sa;
    std::memset(&sa, 0, sizeof(sa));

    sa.sa_handler = handleSignal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa, nullptr) == -1 || 
        (sigaction(SIGTERM, &sa, nullptr) == -1) ||
        (sigaction(SIGHUP, &sa, nullptr) == -1) ||
        (sigaction(SIGQUIT, &sa, nullptr) == -1)) return false;

    return true;
}




int runProgram()
{
    const int WIDTH = 2560;
    const int HEIGHT = 1440;
    Camera camera(vec3(0.0f, 350.0f, 0.0f), vec3(0, 1, 0), -90.0f, -90.0f);
    Simulation solarSystem;

    GLFWwindow* window = loadLibsAndWindow(WIDTH, HEIGHT, VSYNC_OFF);
    if (!window) return GLFW_INIT_FAIL;
        
    solarSystem.buildStandardSS();

    {
        InstancedSphereRenderer renderer("shaders/vertex.glsl", "shaders/fragment.glsl");

        float dt = 0.01f;
        float lastFrame = 0.0f;

        double fpsTime = 0.0;
        int fpsFrames = 0;

        while (!glfwWindowShouldClose(window))
        {
            int fbWidth, fbHeight;
            float currentFrame = glfwGetTime();
            float deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            if (sig_closeWindow) {
                std::cerr << "signal received: " << sig_closeWindow << '\n';
                glfwSetWindowShouldClose(window, true);
            }

            show_frames(window, fpsTime, fpsFrames, deltaTime);

            glfwPollEvents();
            glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
            processKeyboardInput(window, camera, deltaTime);

            solarSystem.step(dt);

            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            renderer.render(solarSystem, camera, fbWidth, fbHeight);

            glfwSwapBuffers(window);
        }
    }
    glfwTerminate();
 
    return 0;
}

int main()
{
    using std::cerr;
    if (!registerSignals()) {
        std::cerr << "Signal setup failed\n";
        return SIGNAL_INIT_FAILED;
    }
    

    return runProgram();
}



