/*
* @file     keyboard.cpp
* @author   Michael Haring
* @date     3/18/26
* */


#include <GLFW/glfw3.h>
#include "keyboard.hpp"
#include "camera.hpp"

static bool qPressedLastFrame = false;

void processKeyboardInput(GLFWwindow *window, Camera &camera, float deltaTime)
{
	// Movement - WASD
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processMovement(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processMovement(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processMovement(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processMovement(RIGHT, deltaTime);
	bool qPressedNow = (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
    if (qPressedNow && !qPressedLastFrame)
        glfwSetWindowShouldClose(window, true);

    qPressedLastFrame = qPressedNow;

	// Rotation - ARROW KEYS
	float xDir = 0.0f, yDir = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		xDir = -1.0f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		xDir = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		yDir = -1.0f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		yDir = 1.0f;

	if (xDir != 0.0f || yDir != 0.0f)
		camera.processRotation(xDir, yDir, deltaTime);
}
