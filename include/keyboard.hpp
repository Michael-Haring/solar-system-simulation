/*
* @file     keyboard.hpp
* @author   Michael Haring
* @date     3/17/26
* */

#pragma once

struct GLFWwindow;
class Camera;


/*
   Processes camera movement and rotation inputs from user
   @param   *window:        current window
            &camera:        camera being moved
            deltaTime:      change in time
 */
void processKeyboardInput(GLFWwindow *window, Camera &camera, float deltaTime);
